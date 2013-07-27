#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> PII;
typedef double LD;

/* CHECKLIST 
 * 1) long longs 
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

const int DBG = 0, INF = int(1e9);

const int MAXP = int(1e7);

// number of random iterations of the algorithm
const int ITER = 10;

int P[MAXP];

int primes_no;
VI primes;
 
VI cnt;

void sieve() {
   P[0] = P[1] = -1;
   for (int i = 2; i < MAXP; ++i)
      P[i] = 0;
   for (int i = 2; i < MAXP; ++i)
      if (P[i] == 0) {
         P[i] = i;
         for (LL x = LL(i) * i; x < MAXP; x += i)
            if (!P[x])
               P[x] = i;
      }
   primes_no = 0;
   for (int i = 2; i < MAXP; ++i)
      if (P[i] == i)
         ++primes_no;
   primes.reserve(primes_no);
   for (int i = 2; i< MAXP; ++i)
      if (P[i] == i)
         primes.push_back(i);
}

// if p is smallest prime divisor of k (with multiplicity m) 
// then D[k] = k / p^m
int D[MAXP];

void count_D() {
   D[1] = 1;
   for (int i = 2; i < MAXP; ++i) 
      if ( (i / P[i]) % P[i] != 0)
         D[i] = i / P[i];
      else
         D[i] = D[i / P[i]];
}

int main() {
   unsigned int seed = 32543;
   srand(seed);

   int n;
   scanf("%d", &n);

   VI w(n);
   for (int i = 0; i < n; ++i)
      scanf("%d", &w[i]);
      
   sort(w.begin(), w.end());

   sieve();
   count_D();

   cnt = VI(primes.size(), 0);

   set<PII> best_primes_set;
   VI best_primes, members;
   int k = 0;

   cnt = VI(MAXP, 0);
   for (int q = 0; q < ITER; ++q) {
      int pos = rand() % n;
      
      int add = 0;
      for (int i = 0; i < n; ++i)
         if (w[pos] == w[i]) 
            ++add;
         else
            for (int dif = abs(w[pos] - w[i]); dif > 1; dif = D[dif]) 
               ++cnt[P[dif]];


      for (int i = 0; i < primes_no; ++i) {
         int p = primes[i];
         cnt[p] += add;
         if (cnt[p] > k) {
            k = cnt[p];
            best_primes = VI(1, p);
            members = VI(1, w[pos]);
            best_primes_set.clear();
            best_primes_set.insert(make_pair(p, w[pos] % p));
         }
         else if (cnt[p] == k) {
            if (best_primes_set.count(make_pair(p, w[pos] % p)) == 0) {
               best_primes_set.insert(make_pair(p, w[pos] % p));
               best_primes.push_back(p);
               members.push_back(w[pos]);
            }
         }
         cnt[p] = 0;
      }

   }

   w.erase(unique(w.begin(), w.end()), w.end());

   int cands = (int) best_primes.size(), m = *(max_element(best_primes.begin(), best_primes.end()));

   VI selected;
   selected.reserve(w.size());
   for (int c = 0; c < cands; ++c) {
      //cout << best_primes[c] << " " << members[c] << endl;
      selected.clear();
      for (VI::iterator it = w.begin(); it != w.end(); ++it)
         if ( (*it - members[c]) % best_primes[c] == 0)
            selected.push_back(*it);
      
      int g = 0;
      for (int i = 1, n_ = (int) selected.size(); i < n_; ++i) {
         int a = g, b = selected[i] - selected[i - 1];
         if (a > b)
            swap(a,b);
         while (a > 0) {
            int tmp = b % a;
            b = a;
            a = tmp;
         }
         g = b;
      }

      m = max(m, g);
   }

   printf("%d %d\n", k, m);



   return 0;
}	
