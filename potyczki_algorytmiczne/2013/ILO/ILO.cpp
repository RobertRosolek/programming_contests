#include <cstdio>
#include <iostream>
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
 * 1) long longs 
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

const int DBG = 0, INF = int(1e9);

const int MAXK = 12;
int fact[MAXK + 1];

const int MAXP = 4e4;
VI primes;

/*vector<VI> num_parts;


void walk(int n, int k, VI& sol) {
   if (k == 1) {
      assert(n >= 0);
      sol.push_back(n);
      num_parts.push_back(sol);
      sol.pop_back();
      return;
   }
   int bound;
   if (sol.empty() || 1)
      bound = n;
   else
      bound = min(sol.back(), n);
   for (int i = bound; i >= 0; --i) 
      if (k * i < n && 0)
         return;
      else {
         sol.push_back(i);
         walk(n - i, k - 1, sol);
         sol.pop_back();
      }
}

void gen_num_parts(int n, int k) {
   num_parts.clear();
   VI sol;
   walk(n, k, sol);
}*/

// TODO - remove sol
bool walk2(VI &v, VI &w, int step1, int step2, set<PII>& in, set<PII> fringe, int k/*, set<VI> sol*/) {
   if (v.size() <= 1)
      return false;
   if (in.empty()) {
      for (int i = 1; i <= w[step1]; ++i)
         in.insert(make_pair(i, 0));
      for (int i = 1; i <= w[step2]; ++i)
         in.insert(make_pair(0, i));
      fringe.insert(make_pair(1,1));
   }

   if (DBG)
   {
      cerr << "K = " << k << " step1 = " << step1 << " step2 = " << step2 << endl;
      for (VI::iterator it = v.begin(); it != v.end(); ++it)
         cerr << *it << " -- ";
      cerr << endl;
      for (VI::iterator it = w.begin(); it != w.end(); ++it)
         cerr << *it << " ";
      cerr << endl;
      for (set<PII>::iterator it = in.begin(); it != in.end(); ++it)
         cerr << it->first << " *** " << it->second;
      cerr << endl;
      for (set<PII>::iterator it = fringe.begin(); it != fringe.end(); ++it)
         cerr << it->first << " %%% " << it->second;

      cerr << endl;
   }

   if (k == 0) {
      //cerr << "BINGO\n";
      return true; // TODO change that
   }

   while (!fringe.empty())  {
      int a = fringe.begin()->first, b = fringe.begin()->second;
      fringe.erase(fringe.begin());
      if (v[step1] >= a && v[step2] >= b) {
         in.insert(make_pair(a, b));
         v[step1] -= a;
         v[step2] -= b;
         if (in.count(make_pair(a + 1, b - 1)))
            fringe.insert(make_pair(a + 1, b));
         if (in.count(make_pair(a - 1, b + 1)))
            fringe.insert(make_pair(a, b + 1));
         if (walk2(v, w, step1, step2, in, fringe, k - 1/*,sol*/)) { 
            return true;
         }
         v[step1] += a;
         v[step2] += b;
         fringe.erase(make_pair(a + 1, b));
         fringe.erase(make_pair(a, b + 1));
         in.erase(make_pair(a, b));
      }
   } 

   set<PII> in2;
   if (++step2 == (int) v.size()) {
      ++step1;
      assert(step1 < (int) v.size());
      step2 = step1 + 1;
      if (step2 == (int) v.size())
         return false;
   }
   return walk2(v, w, step1, step2, in2, set<PII>(), k/*,sol*/);
}


bool walk1(VI &v, VI &w, int step, int k/*,set<VI> sol*/) {
   if (DBG) cerr << step << " " << k << " " << v.size() << endl;
   if (k == 0) 
      return true; // TODO change that
   if (step == (int) v.size()) {
      set<PII> in;
      return walk2(v, w, 0, 1, in, set<PII>(), k/*,sol*/);
   }
   if (walk1(v, w, step + 1, k/*,sol*/))
      return true;
   int c = 2;
   int mem = v[step];
   while (c <= v[step]) {
      v[step] -= c;
      w[step] = c;
      k -= 1;
      ++c;
      if (walk1(v, w, step + 1, k/*,sol*/))
         return true;
   }

   v[step] = mem;
   w[step] = 1;
   return false;
}

bool solve(int n, int k) {
   if (k == 1)
      return true;
   if (k > MAXK)
      return false;
   if (fact[k] > n)
      return false;

   VI v;
   int N = n;
   for (VI::iterator it = primes.begin(); it != primes.end() && (*it) * (*it) <= N; ++it)
      if (N % *it == 0) {
         v.push_back(0);
         while (N % *it == 0) {
            ++v.back();
            N /= *it;
         }
      }
   if (N > 1)
      v.push_back(1);
   sort(v.begin(), v.end());
   
   reverse(v.begin(), v.end());
   k -= (int) v.size() + 1;
   for (VI::iterator it = v.begin(); it != v.end(); ++it)
      *it -= 1;
   while (!v.empty() && v.back() == 0) {
      v.pop_back();
   }

   if (k <= 0)
      return true;

   if (DBG + 0) {
      cerr << "BEGIN!!!!!\n";
      for (VI::iterator it = v.begin(); it != v.end(); ++it)
         cerr << *it << " -- ";
      cerr << endl;
      cerr << k << endl;
   }
   VI w(v.size(), 1);
   bool found = walk1(v, w, 0, k/*,set<VI>()*/);

   if (!found) {
      if (v.size() >= 3 && v[2] >= 3) {
         v[0] -= 1;
         v[1] -= 1;
         v[2] -= 1;
         found = walk1(v, w, 0,  k - 1/*,set<VI>()*/);
      }
   }

   return found;
}

void sieve() {
   VI P(MAXP, 1);
   P[0] = P[1] = 0;
   for (int i = 2; i < MAXP; ++i)
      if (P[i]) {
         primes.push_back(i);
         for (int x = i * i; x < MAXP; x += i)
            P[x] = 0;
      }

}

int main() {

   sieve();
   //printf("%d\n", (int) primes.size());

   fact[0] = 1;
   for (int i = 1; i <= MAXK; ++i)
      fact[i] = i * fact[i - 1];

   //for (int i = 0; i <= MAXK; ++i)
   //   printf("%d\n", fact[i]);
   
   //for (int i = 0; i < 4000; ++i)
   //   gen_num_parts(10, 6);
   /*for(vector<VI>::iterator it = num_parts.begin(); it != num_parts.end(); ++it) {
      for (VI::iterator jt = it->begin(); jt != it->end(); ++jt)
         cerr << *jt << " ";
      cerr << endl;
   }*/
   //cerr << num_parts.size() << endl;
   //return 0;

   int t;
   scanf("%d", &t);

   for (int q = 0; q < t; ++q) {
      int n, k;
      scanf("%d %d", &n, &k);
      bool res = solve(n, k);
      //for (int i = 0; i < 4000; ++i)
      //   res = solve(n, k);
      if (res)
         printf("TAK\n");
      else
         printf("NIE\n");
   }

   return 0;
}	
