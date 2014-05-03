#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <tuple>
#include <map>
#include <unordered_map>

using namespace std;

const int DBG = 0, INF = int(1e9);

void read_weight(int& x)
{
   string s;
   cin >> s;
   stringstream ss;
   ss << s.substr(2);
   ss >> x;
}

int war(const std::vector<int>& a, const std::vector<int>& b)
{
   set<int> x(b.begin(), b.end());
   int res = 0, n = a.size();
   for (int i = 0; i < n; ++i)
      if (a[i] > *x.rbegin()) ++res;
      else x.erase(x.lower_bound(a[i]));
   return res;
}

const int MAXN = 1000;

struct dec_war {
   std::vector<int> a, b;
   int dp[MAXN][MAXN];

   dec_war(const std::vector<int>& a, const std::vector<int>& b): a(a), b(b) {
      for (int i = 0; i < MAXN; ++i) for (int j = 0; j < MAXN; ++j) dp[i][j] = -1;
   }

   int solve(int a1, int a2, int b1, int b2) {
      if (a1 > a2) return 0;
      auto& res = dp[a1][b1];
      if (res != -1) return res;
      if (a[a1] > b[b1]) res = 1 + solve(a1 + 1, a2, b1 + 1, b2);
      res = max(res, solve(a1 + 1, a2, b1, b2 - 1));
      return res;
   }
};

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int T; cin >> T;
   for (int q = 1; q <= T; ++q) {
      int n;
      cin >> n;
      std::vector<int> a(n), b(n);
      for (auto& x: a) read_weight(x);
      for (auto& x: b) read_weight(x);
      sort(a.begin(), a.end());
      sort(b.begin(), b.end());
      cout << "Case #" << q << ": " << dec_war(a, b).solve(0, n - 1, 0, n - 1)  << " " << war(a, b) << endl;
   }
   return 0;
}
