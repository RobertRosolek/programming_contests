#include <stdio.h>      
#include <ctype.h>
#include <math.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> PII;
typedef double LD;

/* CHECKLIST 
 * 1) long longs */

const int DBG = 0, INF = int(1e9);

const int M = 1e6;

int P[M + 1];

void sieve() {
   for (int i = 0; i <= M; ++i)
      P[i] = i;
   for (int i = 2; i <= M; ++i)
      if (P[i] == i) 
         for (LL x = LL(i) * i; x <= M; x += i)
            if (P[x] == x)
               P[x] = i;
}

void generate(const vector<PII> &primes, int step, int n, int cur, VI &dividers) {
   if (step == n)
      dividers.push_back(cur);
   else {
      int mlt = 1;
      for (int i = 0; i <= primes[step].second; ++i) {
         generate(primes, step + 1, n, cur * mlt, dividers);
         mlt *= primes[step].first;
      }   
   }
}

void get_dividers(int k, VI &dividers) {
   VI primes;
   //cout << k << " ";
   while (k > 1) {
      primes.push_back(P[k]);
      k /= P[k];
   }
   primes.push_back(M + 2);
   vector<PII> primes_2;
   int prim = -1, cnt = 0;
   for (int i = 0, _n = primes.size(); i < _n; ++i) 
      if (primes[i] == prim)
         ++cnt;
      else {
         if (prim != -1)
            primes_2.push_back(make_pair(prim,cnt));
         prim = primes[i];
         cnt = 1;
      }
   /*for (int i = 0; i < primes_2.size(); ++i)
      cout << primes_2[i].first << " " << primes_2[i].second << " ";
   cout << endl;*/
   generate(primes_2, 0, primes_2.size(), 1, dividers);
}

bool check(int m, int n, int k, map<int, vector<PII> > &mp) {
   vector<VI> v(n);
   for (int i = 0, _n = mp[m].size(); i < _n; ++i) {
      v[mp[m][i].first].push_back(mp[m][i].second);
      v[mp[m][i].second].push_back(mp[m][i].first);
   }
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   sieve();

   int n,k;
   cin >> n >> k;

   VI a(n);
   for (int i = 0; i < n; ++i)
      cin >> a[i];

   sort(a.begin(), a.end());

   map<int, vector<PII> > mp;

   for (int i = 0; i < n; ++i)
      for (int j = 0; j < i; ++j) {
         int dif = a[i] - a[j];
         VI dividers;
         get_dividers(dif, dividers);
         /*cout << dif << " ";
         for (int i = 0; i < dividers.size(); ++i)
            cout << dividers[i] << " ";
         cout << endl;*/
         for (int i = 0, _n = dividers.size(); i < _n; ++i)
            if (dividers[i] >= n - k - 10)
               mp[dividers[i]].push_back(make_pair(i,j));
      }

   for (int m = max(0, n - k - 10); ; ++m)
      if (check(m, n, k, mp)) {
         cout << m << endl;
         return 0;
      }

   return 0;
}	
