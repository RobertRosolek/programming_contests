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

using namespace std;

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

   int T;
   cin >> T;
   for (int q = 0; q < T; ++q) {
      int a,n;
      cin >> a >> n;
      VI V(n);
      for (int i = 0; i < n; ++i) 
         cin >> V[i];
      sort(V.begin(), V.end());
      int res = n, cnt = 0;
      if (a > 1) 
         for (int i = 0; i < n; ++i) {
            while (a <= V[i]) {
               a += a - 1;
               ++cnt;
            }
            a += V[i];
            res = min(res, cnt + n - i - 1);
         }
      printf("Case #%d: %d\n", q + 1, res);
   }

   return 0;
}	
