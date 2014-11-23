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

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * */

const int DBG = 0, INF = int(1e9);

class Solve {
   vector<int> A[2];
   int n[2];
   set<int> notcov[2];
   set<int> e[2];
   int pos[2];
   LL res;

   void read() {
      int x1, a1, b1, c1, r1,
         x2, a2, b2, c2, r2;

      cin >> n[0] >> n[1] >> x1 >> a1 >> b1 >> c1 >> r1 >> x2 >> a2 >> b2 >> c2 >> r2;

      for (int i = 0; i < 2; ++i) A[i] = vector<int>(n[i]);
      A[0][0] = x1;
      A[1][0] = x2;
      for (int i = 1; i < max(n[0],n[1]); ++i) {
         if (i < n[0]) A[0][i] = (a1 * A[0][(i-1) % n[0]] + b1 * A[1][(i-1) % n[1]] + c1) % r1;
         if (i < n[1]) A[1][i] = (a2 * A[0][(i-1) % n[0]] + b2 * A[1][(i-1) % n[1]] + c2) % r2;
      }
      if (false) for (int i = 0; i < 2; ++i) {
         for (int j = 0; j < n[i]; ++j)
            cout << A[i][j] << " ";
         cout << endl;
      }
   }

   public:
   LL solve() {
      read();
      res = 0;
      pos[0] = pos[1] = 0;
      while (pos[0] < n[0] && pos[1] < n[1]) {
         //cout << pos[0] << " " << pos[1] << endl;
         for (int i = 0; i < 2; ++i) {
            int x = A[i][pos[i]];
            if (!e[i].count(x)) {
               e[i].insert(x);
               notcov[i].insert(x);
            }
         }
         for (int i = 0; i < 2; ++i)
            while (!notcov[i].empty()) {
               int x = *notcov[i].begin();
               if (e[1 - i].count(x)) notcov[i].erase(x);
               else break;
            }
         if (!notcov[0].empty()) pos[1]++;
         else if (!notcov[1].empty()) pos[0]++;
         else {
            //assert(e[0] == e[1]); // TODO comment out
            LL cnt[2];
            cnt[0] = cnt[1] = 0;
            for (int i = 0; i < 2; ++i)
            for (int j = pos[i]; j < n[i]; ++j)
               if (e[i].count(A[i][j])) cnt[i]++;
               else break;
            assert(cnt[0] >= 1 && cnt[1] >= 1);
            res += cnt[0] * cnt[1];
            for (int i = 0; i < 2; ++i) pos[i] += cnt[i];
         }
      }

      return res;
   }
};

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int T; cin >> T;
   for (int q = 0; q < T; ++q) cout << "Case #" << q + 1 << ": " << Solve().solve() << endl;
   return 0;
}

