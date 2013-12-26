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

#define ALL(x) x.begin(), x.end()
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
typedef pair<int,int> PII;
typedef double LD;

const int DBG = 0, INF = int(1e9);

const int P = int(1e9) + 7;

void inc(LL& a, LL x) {
   a = (a + x) % P;
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int n, m; cin >> n >> m;
   // pyr[y][x] how many pyramids with base of length x and height y
   LL pyr[n + 1][m + 1];
   for (int i = 0; i < n + 1; ++i) for (int j = 0; j < m + 1; ++j) pyr[i][j] = 0;
   for (int x = 2; x <= m; ++x) pyr[1][x] = 1;
   LL prevSum[m + 1];
   for (int y = 2; y <= n; ++y) {
      partial_sum(pyr[y - 1], pyr[y - 1] + m + 1, prevSum);
      for (int x = 2; x <= m; ++x) {
         pyr[y][x] = (pyr[y - 1][x] + pyr[y][x - 1]) % P;
         pyr[y][x] += prevSum[x - 1];
         pyr[y][x] %= P;
      }
   }
   // accumulate, pyr[y][x] how many pyramids with base of length x and height <= y
   for (int y = 2; y <= n; ++y) for (int x = 1; x <= m; ++x) inc(pyr[y][x], pyr[y - 1][x]);
   LL res = 0;
   for (int baseLen = 2; baseLen <= m; ++baseLen) {
      inc(res, (pyr[n][baseLen] * (m - baseLen + 1)) % P);
      for (int row = 2; row <= n; ++row) {
         LL mult = pyr[row][baseLen] - pyr[row - 1][baseLen] + P;
         mult %= P;
         mult *= pyr[n - row + 1][baseLen];
         mult %= P;
         mult *= m - baseLen + 1;
         mult %= P;
         inc(res, mult);
      }
   }
   cout << res << endl;
   return 0;
}
