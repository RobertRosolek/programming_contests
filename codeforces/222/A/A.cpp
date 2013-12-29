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

const int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1};

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int n, m, k; cin >> n >> m >> k;
   vector<string> b(n + 2);
   for (int i = 0; i < m + 2; ++i) b[0] += '#';
   b[n + 1] = b[0];
   for (int i = 1; i <= n; ++i) {
      string line; cin >> line;
      b[i] = "#" + line + "#";
   }
   int deg[n + 2][m + 2]; for (int a = 0; a < n + 2; ++a) for (int b = 0; b < m + 2; ++b) deg[a][b] = 0;
   set<pair<int, pair<int, int>>> s;
   for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) if (b[i][j] == '.') {
      for (int q = 0; q < 4; ++q) {
         int x = i + dx[q], y = j + dy[q];
         if (b[x][y] == '.') deg[i][j]++;
      }
      s.insert(make_pair(deg[i][j], make_pair(i, j)));
   }
   for (int i = 0; i < k; ) {
      int dg = s.begin()->first, x = s.begin()->second.first, y = s.begin()->second.second; s.erase(*s.begin());
      if (dg > deg[x][y]) continue;
      ++i;
      b[x][y] = 'X';
      for (int q = 0; q < 4; ++q) {
         int nx = x + dx[q], ny = y + dy[q];
         if (b[nx][ny] != '.') continue;
         deg[nx][ny]--;
         s.insert(make_pair(deg[nx][ny], make_pair(nx, ny)));
      }
   }
   for (int i = 1; i <= n; ++i) cout << b[i].substr(1, m) << endl;

   return 0;
}

