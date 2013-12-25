
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

const int P = int(1e9) + 7;

inline void inc(int&a, int x) {
   a += x;
   if (a >= P) a -= P;
}

class WinterAndSnowmen {
public:
   int getNumber(int N, int M) {
      int b = 0;
      int n = max(N, M);
      while ((1<<b) <= n) ++b;
      int result = 0;
      auto dp = vector<vector<vector<int>>>(n + 1, vector<vector<int>>(1<<b, vector<int>(2, 0)));
      for (int q = 0; q < b; ++q) {
            int bits = b - q;
            for (int i = 0; i <= n; ++i) for (int mask = 0; mask < (1<<bits); ++mask) for (int b = 0; b < 2; ++b) dp[i][mask][b] = 0;
            dp[0][0][0] = 1;
            for (int i = 1; i <= n; ++i) for (int mask = 0; mask < (1<<bits); ++mask) for (int b = 0; b < 2; ++b) {
               dp[i][mask][b] = dp[i - 1][mask][b];
               if (i <= N) inc(dp[i][mask][b], dp[i - 1][mask ^ (i>>q)][((i >> q) & 1) ^ b]);
               if (i <= M) inc(dp[i][mask][b], dp[i - 1][mask ^ (i>>q)][b]);
            }
            inc(result, dp[n][1][0]);
      }  
      return result;
   }
};

