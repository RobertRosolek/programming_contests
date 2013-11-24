#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int T;
   cin >> T;
   for (int q = 0; q < T; ++q) {
      int n;
      cin >> n;
      vector<string> board(n);
      for (string& row: board) cin >> row;
      int sumBlack = 0;
      for (const string& row: board) sumBlack += count(row.begin(), row.end(), '#');
      int minRow = n, minCol = n, maxRow = 0, maxCol = 0;
      auto accMinMax = [](int& mn, int& mx, int val) { mn = min(mn, val); mx = max(mx, val); };
      for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)  if (board[i][j] == '#') {
         accMinMax(minRow, maxRow, i);
         accMinMax(minCol, maxCol, j);
      }
      auto len = [](int mn, int mx) { return mx - mn + 1; };
      int height = len(minRow, maxRow), width = len(minCol, maxCol);
      bool isSquare = height == width && sumBlack == height * width;
      cout << "Case #" << (q + 1) << ": " << (isSquare ? "YES" : "NO") << endl;
   }

   return 0;
}

