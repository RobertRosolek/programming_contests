
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

class MaxMinTreeGame {
public:
   int findend(vector <int> edges, vector <int> costs) {
      int n = costs.size();
      vector<bool> isLeaf(n, true);
      for (auto v: edges) isLeaf[v] = false;
      int deg_zero = 0;
      for (auto v: edges) if (v == 0) ++deg_zero;
      int result = 0;
      if (deg_zero == 1) result = max(result, costs[0]);
      for (int i = 0; i < n; ++i) if (isLeaf[i]) result = max(result, costs[i]);
      return result;
   }
};

