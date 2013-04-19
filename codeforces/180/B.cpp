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

   int n,m,k;
   cin >> n >> m >> k;

   VI A(n), B(m);

   REP(i,n)
      cin >> A[i];
   REP(i,m)
      cin >> B[i];

   sort(ALL(A));
   sort(ALL(B));

   bool ok = false;

   if (n > m) 
      ok = true;
   else {
      REP(i,n)
         if (A[n - 1 - i] > B[m - 1 - i])
            ok = true;   
   }

   if (ok)
      cout << "YES\n";
   else
      cout << "NO\n";

   return 0;
}	
