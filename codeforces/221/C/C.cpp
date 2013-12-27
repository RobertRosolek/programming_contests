#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <map>

using namespace std;

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * */

const int DBG = 0, INF = int(1e8);

const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, -1, 1};

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int n, m; cin >> n >> m;
   auto b = vector<string>(n);
   for (auto& line: b) cin >> line;
   int t = 0; char mc = '1';
   for (auto& line: b) for (auto c: line) if ('1' <= c && c <= '8') {
      mc = max(mc, c);
      ++t;
   }
   auto cost = vector<int>(t);
   for (auto& x: cost) cin >> x;
   for (auto& line: b) for (auto& c: line) if (c == 'B') {
      c = ++mc;
      cost.push_back(-3000);
   }
   t = cost.size();

   int sr, sc;
   for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (b[i][j] == 'S') {
      sr = i, sc = j;
      b[i][j] = '.';
   }

   auto changeMask = vector<vector<int>>(n, vector<int>(m, 0));
   for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if ('1' <= b[i][j] && b[i][j] <= '8') {
      int ind = b[i][j] - '1';
      for (int k = j; k < m; ++k) changeMask[i][k] ^= (1 << ind);
   }

   auto dist = vector<vector<vector<int>>>((1<<t), vector<vector<int>>(n, vector<int>(m, -1)));
   dist[0][sr][sc] = 0;
   queue<pair<int, pair<int, int>>> q;
   q.push(make_pair(0, make_pair(sr, sc)));
   while (!q.empty()) {
      int mask = q.front().first, x = q.front().second.first, y = q.front().second.second; q.pop();
      for (int i = 0; i < 4; ++i) {
         int nx = x + dx[i], ny = y + dy[i];
         if (nx < 0 || nx == n || ny < 0 || ny == m || b[nx][ny] != '.') continue;
         int nmask = mask;
         if (i == 0) nmask ^= changeMask[x][y];
         if (i == 1) nmask ^= changeMask[nx][ny];
         if (dist[nmask][nx][ny] == -1) {
            dist[nmask][nx][ny] = dist[mask][x][y] + 1;
            q.push(make_pair(nmask, make_pair(nx, ny)));
         }
      }
   }
   int result = 0;
   for (int mask = 0; mask < (1 << t); ++mask) if (dist[mask][sr][sc] != -1) {
      int val = 0;
      for (int ind = 0; ind < t; ++ind) if (mask & (1<<ind)) val += cost[ind];
      result = max(result, val - dist[mask][sr][sc]);
   }
   cout << result << endl;

   return 0;
}

