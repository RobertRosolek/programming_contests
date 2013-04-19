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

   string a, b;
   cin >> a >> b;
   
   int x = count(a.begin(), a.end(), '1'), y = count(b.begin(), b.end(), '1');

   if ( (x + 1) / 2 >= (y + 1) / 2)
      cout << "YES\n";
   else
      cout << "NO\n";

   return 0;
}	
