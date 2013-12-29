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

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * */

const int DBG = 0, INF = int(1e9);

const int MAXN = 20;
int dp[MAXN][1<<MAXN];
bool calc[MAXN][1<<MAXN];

int n, m;
vector<int> s;
vector<pair<char, int>> a;

int walk(int step, int mask) {
   if (step == m) return 0;
   assert(mask > 0);
   int& res = dp[step][mask];
   if (calc[step][mask]) return res;
   calc[step][mask] = true;
   if (a[step].first == 'p') for (int j = 0; ; ++j) if (mask & (1<<j)) {
      res = walk(step + 1, mask ^ (1<<j)) + s[j] * (a[step].second == 1 ? 1 : -1);
      return res;
   }
   if (a[step].second == 1) res = -INF; else res = INF;
   for (int j = 0; j < n; ++j) if (mask & (1<<j)) {
      int cur = walk(step + 1, mask ^ (1<<j));
      if (a[step].second == 1) res = max(res, cur); else res = min(res, cur);
   }
   return res;
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   cin >> n;
   s.resize(n); for (auto& x: s) cin >> x;
   cin >> m;
   a.resize(m); for (auto& it: a) cin >> it.first >> it.second;
   sort(s.begin(), s.end());
   reverse(s.begin(), s.end());
   while (s.size() > 20) s.pop_back();
   n = s.size();
   for (int i = 0; i < m; ++i) for (int j = 0; j < (1<<n); ++j) calc[i][j] = false;
   cout << walk(0, (1<<n) - 1) << endl;
   return 0;
}

