#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <map>

#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/irange.hpp>

using namespace std;
using boost::irange;

const int MAXN = 500, INF = MAXN * MAXN * MAXN;

int isEmpty(char c) {
   return c == '.';
}

void maxify(int& acc, int e) { acc = max(acc, e); }

typedef vector<vector<int>> matrix;

matrix init(int n, int v) {
   return matrix(n, vector<int>(n, v));
}

class Solve {
   vector<string> B;
   matrix sum = init(MAXN, -1), from = init(MAXN, -1), to = init(MAXN, -1);

   int n, m;

   int getSum(int i, int j) {
      if (i < 0 || j < 0) return 0;
      if (sum[i][j] == -1) sum[i][j] = !isEmpty(B[i][j]) + getSum(i - 1, j) + getSum(i, j - 1) - getSum(i - 1, j - 1);
      return sum[i][j];
   }

   int rectSum(int i, int j, int i2, int j2) {
      assert(i <= i2 && j <= j2);
      return getSum(i2, j2) - getSum(i - 1, j2) - getSum(i2, j - 1) + getSum(i - 1, j - 1);
   }

   bool isHorizontalEmpty(int i, int j1, int j2) { return rectSum(i, j1, i, j2) == 0; }
   bool isVerticalEmpty(int i1, int j, int i2) { return rectSum(i1, j, i2, j) == 0; }

   int getFrom(int i, int j) {
      if (i < 0 || j < 0) return -INF;
      if (i == 0 && j == 0) return 1;
      if (from[i][j] == -1) from[i][j] = isEmpty(B[i][j]) ? 1 + max(getFrom(i - 1, j), getFrom(i, j - 1)) : -INF;
      return from[i][j];
   }

   int getTo(int i, int j) {
      if (n <= i || m <= j) return 0;
      if (to[i][j] == -1) to[i][j] = isEmpty(B[i][j]) ? 1 + max(getTo(i + 1, j), getTo(i, j + 1)) : 0;
      return to[i][j];
   }

   public:
      int solve() {
         cin >> n >> m;
         B = vector<string>(n);
         for (string& row: B) cin >> row;
         assert(isEmpty(B[0][0]));

         int result = 1;

         // no leftwards and upwards fragments
         for (int i: irange(0, n)) for (int j: irange(0, m)) maxify(result, getFrom(i, j));

         auto len = [] (int i, int j) { return abs(j - i) + 1; };
         auto horLen = [=] (int i, int j1, int j2) { return isHorizontalEmpty(i, j1, j2) ? len(j1, j2) : -INF; };
         auto verLen = [=] (int i1, int j, int i2) { return isVerticalEmpty(i1, j, i2) ? len(i1, i2) : -INF; };

         // leftward fragment from (i, j1) to (i, j2), j2 < j1
         for (int i: irange(0, n)) for (int j1: irange(0, m)) for (int j2: irange(0, j1)) {
            maxify(result, getFrom(i - 1, j1) + horLen(i, j2, j1) + getTo(i + 1, j2));
         }

         // upward fragment from (i1, j) to (i2, j), i2 < i1
         for (int i1: irange(0, n)) for (int j: irange(0, m)) for (int i2: irange(0, i1)) {
            maxify(result, getFrom(i1, j - 1) + verLen(i2, j, i1) + getTo(i2, j + 1));
         }

         return result;
      }
};

int main() {
   ios_base::sync_with_stdio(0);
   int T; cin >> T;
   for (int q: irange(1, T + 1)) cout << "Case #" << q << ": " << Solve().solve() << endl;
   return 0;
}

