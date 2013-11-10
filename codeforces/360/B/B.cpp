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

const int DBG = 0, INF = int(1e9), MAXN = 2000;

int n, k;
LL delta;

int dp[MAXN + 1][MAXN + 1];

vector<int> a;

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   cin >> n >> k;
   a = vector<int>(n);
   for (int i = 0; i < n; ++i) cin >> a[i];
   LL left = 0, right = 2 * INF;
   while (left < right) {
      LL delta = (left + right) / 2;
      for (int seg = 0; seg <= n; ++seg) dp[n][seg] = 0;
      for (int i = n - 1; i >= 0; --i) {
         dp[i][0] = min(1 + dp[i + 1][0], dp[i + 1][1]);
         for (int seg = 1; seg <= i; ++seg) {
            LL low = a[i - seg] - seg * delta, up = a[i - seg] + seg * delta;
            dp[i][seg] = 1 + dp[i + 1][seg + 1];
            if (low <= a[i] && a[i] <= up)
               dp[i][seg] = min(dp[i][seg], dp[i + 1][1]);
         }
      }
      int r = dp[0][0];
      if (r <= k)
         right = delta;
      else
         left = delta + 1;
   }
   cout << left << endl;

   return 0;
}

