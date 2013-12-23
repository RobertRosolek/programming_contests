
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
#include <unordered_set>
#include <map>

using namespace std;

// }}}

const int MAXN = 50;

vector<pair<short, short>> v[MAXN][MAXN];

class ScotlandYard {
public:
   int maxMoves(vector <string> taxi, vector <string> bus, vector <string> metro) {
      auto n = taxi.size();
      auto toSingle = vector<vector<bool>>(n, vector<bool>(n));
      vector<pair<short, short>> states;
      for (auto a = 0; a < n; ++a) for (auto b = a + 1; b < n; ++b) states.push_back(make_pair(a, b));
      for (auto state: states) {
         auto a = state.first, b = state.second;
         auto addNeighbours = [&](vector<string>& u) {
            set<int> s;
            auto add = [&](int source) { for (int i = 0; i < n; ++i) if (u[source][i] == 'Y') s.insert(i); };
            add(a);
            add(b);
            vector<int> sv(s.begin(), s.end());
            auto m = sv.size();
            for (auto c = 0; c < m; ++c) for (auto d = c + 1; d < m; ++d) v[a][b].push_back(make_pair(sv[c], sv[d]));
            if (m == 1) toSingle[a][b] = 1;
         };
         addNeighbours(taxi);
         addNeighbours(bus);
         addNeighbours(metro);
      }
      vector<pair<short, short>> s, order;
      auto inDeg = vector<vector<short>>(n, vector<short>(n, 0));
      for (auto state: states) for (auto it: v[state.first][state.second]) inDeg[it.first][it.second]++;
      for (auto state: states) {
         auto a = state.first, b = state.second;
         if (inDeg[a][b] == 0) s.push_back(make_pair(a, b));
      }
      while (!s.empty()) {
         auto nxt = s.back(); s.pop_back();
         order.push_back(nxt);
         for (auto it: v[nxt.first][nxt.second]) {
            auto a = it.first, b = it.second;
            if (--inDeg[a][b] == 0) s.push_back(make_pair(a, b));
         }
      }
      if (order.size() != states.size()) return -1;
      auto longest = vector<vector<short>>(n, vector<short>(n, 0));
      int res = 0;
      for (auto state: order) {
         auto a = state.first, b = state.second;
         res = max(res, longest[a][b] + toSingle[a][b]);
         for (auto it: v[a][b]) {
            auto c = it.first, d = it.second;
            longest[c][d] = max(longest[c][d], (short) (longest[a][b] + 1));
         }
      }
      return res;
   }
};

