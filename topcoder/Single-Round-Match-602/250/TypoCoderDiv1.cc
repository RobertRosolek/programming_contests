
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

void maxify(int& a, int x) {
   a = max(a, x);
}

class TypoCoderDiv1 {
public:
   int getmax(vector <int> D, int X) {
      int n = D.size();
      int dp[n + 1][2200];
      for (int i = 0; i < n + 1; ++i) for (int j = 0; j < 2200; ++j) dp[i][j] = -1;
      dp[0][X] = 0;
      int res = 0;
      for (int i = 0; i < n; ++i) for (int j = 0; j < 2200; ++j) if (dp[i][j] != -1) {
         maxify(res, dp[i][j]);
         maxify(dp[i + 1][max(j - D[i], 0)], dp[i][j]);
         if (j + D[i] < 2200) maxify(dp[i + 1][j + D[i]], dp[i][j]);
         if (i < n - 1) {
            int next = max(j + D[i] - D[i + 1], 0);
            if (next < 2200) {
               maxify(dp[i + 2][next], dp[i][j] + 2 * (j + D[i] >= 2200));
               maxify(res, dp[i + 2][next]);
            }
         }
         if (i == n - 1) {
            int next = j + D[i];
            if (next >= 2200) maxify(res, dp[i][j] + 1);
         }
      }
      return res;
   }
};

