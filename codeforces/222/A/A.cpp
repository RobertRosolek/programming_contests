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

int n, m, k, ch;
vector<string> b;
int vis[500 + 2][500 + 2];

void dfs(int x, int y) {
   if (b[x][y] != '.' || vis[x][y]) return;
   vis[x][y] = true;
   for (int i = 0; i < 4; ++i) dfs(x + dx[i], y + dy[i]);
   if (ch == k) return;
   ++ch;
   b[x][y] = 'X';
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   cin >> n >> m >> k;
   b.resize(n + 2);
   for (int i = 0; i < m + 2; ++i) b[0] += '#';
   b[n + 1] = b[0];
   for (int i = 1; i <= n; ++i) {
      string line; cin >> line;
      b[i] = "#" + line + "#";
   }
   int x, y;
   for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) if (b[i][j] == '.') x = i, y = j;
   for (int i = 0; i < n + 2; ++i) for (int j = 0; j < m + 2; ++j) vis[i][j] = false;
   ch = 0;
   dfs(x, y);
   for (int i = 1; i <= n; ++i) cout << b[i].substr(1, m) << endl;

   return 0;
}

