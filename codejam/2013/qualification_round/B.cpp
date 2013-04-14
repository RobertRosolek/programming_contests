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

string solve() {
   int n,m;
   cin >> n >> m;
   int pat[n][m];
   REP(i,n) REP(j,m)
      cin >> pat[i][j];
   
   PII mx = MP(0,0);
   REP(i,n) REP(j,m)
      if (pat[i][j] > pat[mx.ST][mx.ND])
         mx = MP(i,j);
   VI x(n), y(m);
   REP(i,n)
      x[i] = pat[i][mx.ND];
   REP(i,m)
      y[i] = pat[mx.ST][i];
   REP(i,n) REP(j,m)
      if (min(x[i], y[j]) != pat[i][j])
         return "NO";
   return "YES";
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
