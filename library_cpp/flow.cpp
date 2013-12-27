#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <stack>
using namespace std;

#define VAR(a,b) __typeof (b) a = b
#define REP(i,n) for (int _n=(n), i=0; i<_n; ++i)
#define FOR(i,a,b) for (int _b=(b), i=(a); i<=_b; ++i)
#define FORD(i,a,b) for (int _b=(b), i=(a); i>=_b; --i)
#define FORE(i,a) for (VAR(i,a.begin ()); i!=a.end (); ++i)
#define PB push_back
#define MP make_pair
#define ST first
#define ND second

typedef vector<int> VI;
typedef long long LL;

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

int main() {
  ios_base::sync_with_stdio(0);

  return 0;
}
