#include <stdio.h>      
#include <ctype.h>
#include <math.h>

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <stack>
using namespace std;

#define ALL(x) x.begin(), x.end()
#define VAR(a,b) __typeof (b) a = b
#define REP(i,n) for (int _n=(n), i=0; i<_n; ++i)
#define FOR(i,a,b) for (int _b=(b), i=(a); i<=_b; ++i)
#define FORD(i,a,b) for (int _b=(b), i=(a); i>=_b; --i)
#define FORE(i,a) for (VAR(i,a.begin ()); i!=a.end (); ++i) 
#define PB push_back
#define MP make_pair
#define ST first
#define ND second

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> PII;
typedef double LD;

/* CHECKLIST 
 * 1) long longs */

/* O*(2^n) solution, fast enough only for small input*/

const int DBG = 0, INF = int(1e9);

int dst[1<<(20)], par[1<<(20)];

string solve() {
   int k,n;
   cin >> k >> n;

   VI start_keys(k);
   REP(i,k)
      cin >> start_keys[i];

   VI chest_open_key(n);
   vector<VI> chest_keys_inside(n);
   REP(i,n) {
      int keys_inside;
      cin >> chest_open_key[i] >> keys_inside;
      chest_keys_inside[i].resize(keys_inside);
      REP(j,keys_inside)
         cin >> chest_keys_inside[i][j];
   }
   REP(i,(1<<n))
      dst[i] = -1;
   dst[0] = 0;
   par[0] = -1;
   queue<int> q;
   q.push(0);
   while (!q.empty()) {
      int msk = q.front();
      q.pop();

      map<int,int> keys;
      FORE(it,start_keys)
         keys[*it]++;
      REP(i,n)
         if (msk & (1<<i)) {
            FORE(it,chest_keys_inside[i])
               keys[*it]++;
            keys[chest_open_key[i]]--;
         }

      REP(i,n)
         if (!(msk & (1<<i)) && keys[chest_open_key[i]] > 0) {
            int nxt_msk = msk | (1<<i);
            if (dst[nxt_msk] == -1) {
               dst[nxt_msk] = dst[msk] + 1;
               par[nxt_msk] = i;
               q.push(nxt_msk);
            }
         }
   }
   int fin_msk = (1<<n) - 1;
   if (dst[fin_msk] == -1)
      return "IMPOSSIBLE";
   VI solution;
   int msk = fin_msk;
   while (msk != 0) {
      solution.PB(par[msk]);
      msk ^= (1<<par[msk]);
   }
   reverse(ALL(solution));
   stringstream ss;
   FORE(it,solution)
      ss << *it + 1 << " ";
   string res = ss.str();
   return res.substr(0, res.size() - 1);
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int T;
   cin >> T;
   REP(q,T) {
      string res = solve();
      printf("Case #%d: %s\n", q + 1, res.c_str());
   }

   return 0;
}	
