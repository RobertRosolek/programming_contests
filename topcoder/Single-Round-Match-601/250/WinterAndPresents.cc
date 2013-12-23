
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

class WinterAndPresents {
public:
   long long getNumber(vector <int> apple, vector <int> orange) {
      int mn = int(1e7);
      int n = apple.size();
      for (int i = 0; i < n; ++i)
         mn = min(mn, apple[i] + orange[i]);
      long long res = 0;
      for (int x = 1; x <= mn; ++x) {
         int a = 0, b = 0;
         for (int i = 0; i < n; ++i) {
            int app = max(0, x - orange[i]), org = max(0, x - apple[i]);
            int appMax = x - org;
            a += app;
            b += appMax;
         }
         res += b - a + 1;
      }
      return res;
   }
};

