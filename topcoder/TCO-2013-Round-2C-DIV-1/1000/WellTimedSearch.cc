
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

class WellTimedSearch {
public:
   double getProbability(int N, int A, int B) {
      int good = 0, all = 0;
      vector<int> S(1, 1);
      while (!S.empty()) {
         int depth = S.back(); S.pop_back();
         if (all == N) break;
         if (B < depth) continue;
         ++all;
         if (A <= depth) ++good;
         for (int i = 0; i < 2; ++i) S.push_back(depth + 1);
      }
      return double(good) / N;
   }
};

