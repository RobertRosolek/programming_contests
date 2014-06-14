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

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * */

const int DBG = 0, INF = int(1e9);
using pii = pair<int, int>;

void solve()
{
   int pr, tow, n; cin >> pr >> tow >> n;
   vector<pii> u(n);
   for (auto& it: u) cin >> it.first >> it.second;
   map<int, int> cur, nxt;
   cur[1] = 0;
   for (auto i: irange(0, n)) {
      int h = u[i].first, val = u[i].second;
      for (auto it: cur) {
         int sum_moves = it.first, sum_val = it.second;
         auto update = [&](int moves, int val) {
            auto& x = nxt[moves];
            x = max(x, val);
         };
         // not kill
         {
            auto moves = (h + tow - 1) / tow;
            update(sum_moves + moves, sum_val);
         }
         // kill after a tow moves and b pr moves
         for (int a = 0; a < 11; ++a) for (int b = 1; b <= a + sum_moves; ++b) {
            int pre_sum = a * tow + (b - 1) * pr;
            if (pre_sum >= h) break;
            int post_sum = pre_sum + pr;
            if (post_sum < h) continue;
            update(a + sum_moves - b, sum_val + val);
         }
      }
      swap(cur, nxt);
      nxt.clear();
      //for (auto it: cur)
      //   cout << endl << i + 1 << " " << it.first << " " << it.second << endl;
   }
   int res = 0;
   for (auto it: cur)
      res = max(res, it.second);
   cout << res;
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
