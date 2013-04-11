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

const int DBG = 0, INF = int(1e9);

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   
   int n;
   cin >> n;
   int adj[n][n];
   REP(i,n) REP(j,n)
      cin >> adj[i][j];

   VI x(n);
   REP(i,n)
      cin >> x[i];

   vector<LL> res(n);

   int d[n][n];
   REP(i,n) REP(j,n)
      d[i][j] = adj[x[i] - 1][x[j] - 1];

   FORD(k,n - 1, 0) {
      LL rs = 0;
      REP(i,n) REP(j,n) {
         d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
         if (i >= k && j >= k && i != j)
            rs += d[i][j];
      }
      res[k] = rs;
   }

   FORE(it,res)
      cout << *it << " ";
   cout << endl;

   return 0;
}	
