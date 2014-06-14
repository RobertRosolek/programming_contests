#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <map>

#include <boost/range/irange.hpp>

using namespace std;
using namespace boost;

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * */

const int DBG = 0, INF = int(1e9);

int m, n;
vector<string> s;
int x, y;
unordered_set<string> w[4];

void walk(int pos) {
   if (pos == m) {
      int cur = 0;
      for (int i = 0; i < n; ++i)
         cur += w[i].size();
      for (int i = 0; i < n; ++i)
         if (w[i].size() == 0)
            return;
      if (cur > x) x = cur, y = 0;
      if (cur == x)
         ++y;
      return;
   }
   for (int i = 0; i < n; ++i) {
      vector<string> added;
      int sz = s[pos].size();
      for (int j = 0; j <= sz; ++j) {
         auto sub = s[pos].substr(0, j);
         if (!w[i].count(sub)) {
            added.push_back(sub);
            w[i].insert(sub);
         }
      }
      walk(pos + 1);
      for (auto& x: added)
         w[i].erase(x);
   }
}

void solve()
{
   cin >> m >> n;
   s = vector<string>(m);
   for (auto& x: s) cin >> x;
   x = -1;
   walk(0);
   cout << x << " " << y;
}

int main()
{
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int tt; cin >> tt;
   for (auto i: irange(0, tt)) {
      cout << "Case #" << i + 1 << ": ";
      solve();
      cout << std::endl;
   }
   return 0;
}
