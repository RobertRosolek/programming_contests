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

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * */

typedef long long LL;

const int DBG = 0, INF = int(1e9);
const LL M = INF + 7;

LL bin(int k) {
   if (k == 0) return 1;
   LL b = bin(k / 2);
   if (k % 2 == 0) { return (b * b) % M; }
   return ((b * b) % M * 2) % M;
}

class Solve {
   int n;
   vector<int> A;
   vector<vector<int> > R;

   LL dfs(int k, int lim) {
      if (k >= lim) return 0;
      LL sum = 1;
      for (int v: R[k])
         sum += dfs(v, lim);
      return sum;
   }

   public:
   LL solve() {
      cin >> n;
      A = vector<int>(n);
      R = vector<vector<int>>(n);
      for (int i = 1; i < n; ++i) {
         cin >> A[i];
         R[A[i]].push_back(i);
      }
      LL res = 1;
      for (int i = n - 1; i > 0; --i) {
         int j = A[i];
         vector<LL> G;
         for (int k: R[j]) G.push_back(dfs(k, i));
         LL sum = 0;
         for (LL x: G) sum += x;
         LL mult = bin(sum);
         mult = (mult + bin(sum)) % M;
         for (LL x: G) mult = (mult + M - bin(x)) % M;
         mult = (mult + G.size() - 1) % M;
         res = (res * mult) % M;
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

