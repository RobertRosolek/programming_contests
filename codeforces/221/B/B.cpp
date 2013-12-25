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

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int n, m; cin >> n >> m;
   vector<string> b(n);
   for (auto& line: b) cin >> line;
   auto v = vector<vector<int>>(n, vector<int>(m));
   for (auto i = 0; i < n; ++i) {
      int cnt = 0;
      for (int j = m - 1; j >= 0; --j) {
         if (b[i][j] == '0') cnt = 0;
         else ++cnt;
         v[i][j] = cnt;
      }
   }
   int res = 0;
   for (auto j = 0; j < m; ++j) {
      vector<int> u;
      for (auto i = 0; i < n; ++i) u.push_back(v[i][j]);
      sort(u.begin(), u.end());
      for (auto i = n - 1; i >= 0; --i) res = max(res, u[i] * (n - i));
   }
   cout << res << endl;

   return 0;
}

