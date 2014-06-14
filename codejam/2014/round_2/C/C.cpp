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

const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

void solve()
{
   int w, h, b; cin >> w >> h >> b;
   int r[100][500];
   for (auto i: irange(0, w)) for (auto j: irange(0, h)) r[i][j] = 0;
   for (auto i: irange(0, b)) {
      int x_0, y_0, x_1, y_1; cin >> x_0 >> y_0 >> x_1 >> y_1;
      for (int x = x_0; x <= x_1; ++x) for (int y = y_0; y <= y_1; ++y)
         r[x][y] = 1;
   }
   int res = 0;
   auto is_good = [&](int x, int y) { return 0 <= x && x < w && 0 <= y && y < h && r[x][y] != 1; };
   for (auto qq: irange(0, w)) {
      int x = qq, y = 0, dir = 0;
      auto prev_dir = [&]() { return (dir + 3) % 4; };
      auto next_dir = [&]() { return (dir + 1) % 4; };
      auto op_dir = [&]() { return (dir + 2) % 4; };
      if (r[x][y]) continue;
      int sx = x, sy = y;
      r[x][y] = 2;
      while (true) {
         //cout << "(" << x << ", " << y << ") ";
         int lx = x + dx[prev_dir()], ly = y + dy[prev_dir()];
         int nx = x + dx[dir], ny = y + dy[dir];
         int rx = x + dx[next_dir()], ry = y + dy[next_dir()];
         int px = x + dx[op_dir()], py = y + dy[op_dir()];
         if (is_good(lx, ly)) x = lx, y = ly, dir = prev_dir();
         else if (is_good(nx, ny)) x = nx, y = ny;
         else if (is_good(rx, ry)) x = rx, y = ry, dir = next_dir();
         else if (is_good(px, py)) x = px, y = py, dir = op_dir();
         else break;
         r[x][y] = 2;
         if (y == h - 1 || (y == sy && x == sx)) break;
      }
      //cout << endl << endl;
      int ok = (y == h - 1);
      for (auto i: irange(0, w)) for (auto j: irange(0, h)) if (r[i][j] == 2) r[i][j] = ok;
      res += ok;
   }
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
