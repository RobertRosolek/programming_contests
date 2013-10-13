#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

const int DBG = 0, INF = int(1e9);

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int n, k;
   cin >> n >> k;

   vector<int> a(n);
   for (int i = 0; i < n; ++i)
      cin >> a[i];

   int mx = a[0], mn = a[0];
   for (int i = 1; i < n; ++i)
      mx = max(mx, a[i]), mn = min(mn, a[i]);

   vector<int> sm(mx + 2, 0);
   for (int i = 0; i < n; ++i)
      if (a[i] > k) {
         sm[a[i] - k] += 1;
         sm[a[i] + 1] -= 1;
      }

   for (int i = 1; i <= mx; ++i)
      sm[i] += sm[i - 1];

   for (int j = mx; j > k; --j) {
      int cnt = 0, x = j;
      while (x <= mx) {
         cnt += sm[x];
         x += j;
      }
      if (cnt == n) {
         cout << j << endl;
         return 0;
      }
   }

   assert(mn <= k);
   cout << mn << endl;

   return 0;
}

