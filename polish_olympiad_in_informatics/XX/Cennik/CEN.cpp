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

const int DBG = 0, INF = int(1e9);

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int n,m,k,a,b;
   cin >> n >> m >> k >> a >> b;
   --k;

   vector<VI> V(n);

   REP(i,m) {
      int u,v;
      cin >> u >> v;
      --u, --v;
      V[u].PB(v);
      V[v].PB(u);
   }

   queue<int> q;
   VI dst(n,-1);

   q.push(k);
   dst[k] = 0;

   while (!q.empty()) {
      int v = q.front();
      q.pop();
      FORE(it,V[v])
         if (dst[*it] == -1) {
            dst[*it] = dst[v] + 1;
            q.push(*it);
         }
   }

   REP(i,n)
      cout << min((dst[i] / 2) * b + (dst[i] % 2) * a, dst[i] * a) << endl;

   return 0;
}	
