
// {{{ Boilerplate Code <--------------------------------------------------
// vim:filetype=cpp:foldmethod=marker:foldmarker={{{,}}}

#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

// }}}

const int DBG = 0, INF = 1000000000;

#include <queue>
struct Graph {
   int n;
   vector<vector<int>> V;

   vector<vector<int>> przepust;
   vector<int> dst;
   vector<vector<int>::iterator> pocz;

   int flowBfs(int s, int t) {
      fill(dst.begin(), dst.end(), -1);
      dst[s] = 0;
      queue<int> q;
      q.push(s);
      while (!q.empty()) {
         int u = q.front(); q.pop();
         for (auto v: V[u])
            if (przepust[u][v] > 0 && dst[v] == -1) {
               dst[v] = dst[u] + 1;
               q.push(v);
            }
      }
      return dst[t] != -1;
   }

   int flowDfs(int x, int t, int minimum) {
      int res = 0;
      if (x == t || minimum == 0) return minimum;
      for (auto &it = pocz[x]; it != V[x].end(); ++it) {
         if (dst[x] + 1 == dst[*it] && przepust[x][*it] > 0) {
            int y = flowDfs(*it, t, min(minimum, przepust[x][*it]));
            przepust[x][*it] -= y; 
            przepust[*it][x] += y;
            minimum -= y; 
            res += y;
            if (minimum == 0) break;
         }
      }
      return res;
   }

   public:

   Graph(int n) : n(n) , V(vector<vector<int>>(n)), przepust(vector<vector<int>>(n, vector<int>(n, 0))),
      dst(vector<int>(n)), pocz(vector<vector<int>::iterator>(n)) {}

   void addEdge(int a, int b, int d = INF) {
      assert(a < n && b < n);
      przepust[a][b] += d;
      V[a].push_back(b);
      V[b].push_back(a);
   }


   int maxFlow(int s, int t) {
      int res = 0;
      while (flowBfs(s,t)) {
         for (int i = 0; i < n; ++i) pocz[i]=V[i].begin();
         res += flowDfs(s,t,INF);
      }
      return res;
   }

};

class FoxAndGo3 {
public:
   int maxEmptyCells(vector <string> board) {
      map<pair<int,int>, int> id;
      int n = board.size(), nextId = 1;
      for (auto i = 0; i < n; ++i) for (auto j = 0; j < n; ++j) if (board[i][j] != 'x') id[make_pair(i, j)] = nextId++;
      int m = id.size();
      Graph g(m + 2);
      for (auto i = 0; i < n; ++i) for (auto j = 0; j < n; ++j) {
         auto p = make_pair(i, j);
         switch (board[i][j]) {
         case '.':
            g.addEdge(id[p], m + 1, 1);
            break;
         case 'o':
            g.addEdge(0, id[p], 1);
            vector<int> dx = {1, -1, 0, 0}, dy = {0, 0, -1, 1};
            for (auto k = 0; k < 4; ++k) {
               int x = i + dx[k], y = j + dy[k];
               if (x < 0 || x == n || y < 0 || y == n) continue;
               if (board[x][y] == '.') g.addEdge(id[p], id[make_pair(x, y)], 1);
            }
         }
      }
      return id.size() - g.maxFlow(0, m + 1);
   }
};

