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
typedef pair<LL,LL> PII;
typedef double LD;

/* CHECKLIST 
 * 1) long longs */

const int DBG = 0, INF = int(1e9);

PII position(LL x, LL a, LL n) {
   LL x_1 = x - (a + 1) / 2, x_2 = x + a / 2;

   if (x_2 > n) {
      x_1  = n - a;
      x_2 = n;
      assert(x_1 >= 0);
   }
   else if (x_1 < 0) {
      x_1 = 0;
      x_2 = a;
      assert(x_2 <= n);
   }

   return make_pair(x_1,x_2);
}

LL gcd(LL a, LL b) {
   if (a > b)
      swap(a,b);
   if (a == 0)
      return b;
   else
      return gcd(a, b % a);
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   LL n, m, x, y, a, b;
   cin >> n >> m >> x >> y >> a >> b;

   LL g = gcd(a,b);
   a /= g;
   b /= g;
   LL k = min(n / a, m / b);
   a *= k, b *= k;

   PII X = position(x, a, n), Y = position(y, b, m);

   cout << X.first << " " << Y.first << " " << X.second << " " << Y.second << endl;

   return 0;
}	
