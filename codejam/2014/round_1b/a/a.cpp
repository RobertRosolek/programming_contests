#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <map>

#include <boost/range/irange.hpp>

using namespace std;
using namespace boost;

const int DBG = 0, INF = int(1e9);

vector<pair<char, int>> convert(const string& s)
{
   vector<pair<char, int>> result;
   auto emit = [&](char c, int n) { result.push_back(make_pair(c, n)); };
   char last = '0';
   int cnt = 0;
   for (auto c: s)
      if (c == last) ++cnt;
      else {
         if (cnt > 0) emit(last, cnt);
         last = c;
         cnt = 1;
      }
   assert(cnt > 0);
   emit(last, cnt);
   return result;
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int t; cin >> t;
   for (auto q: irange(1, t + 1)) {
      cout << "Case #" << q << ": ";
      int n; cin >> n;
      vector<string> v(n);
      for (auto& s: v) cin >> s;
      vector<vector<pair<char, int>>> u;
      for (auto&s: v) u.emplace_back(convert(s));
      bool bad = false;
      for (auto& s: u) if (s.size() != u[0].size()) bad = true;
      int res = 0;
      if (!bad) for (auto i: irange(0, (int) u[0].size())) {
         for (auto& s: u) if (s[i].first != u[0][i].first) bad = true;
         if (bad) break;
         vector<int> cnts;
         for (auto&s: u) cnts.push_back(s[i].second);
         sort(cnts.begin(), cnts.end());
         int med = cnts[cnts.size() / 2];
         for (auto x: cnts) res += abs(x - med);
      }
      if (bad) cout << "Fegla Won\n";
      else cout << res << endl;
   }
   return 0;
}
