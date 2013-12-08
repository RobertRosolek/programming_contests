#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>

#include <boost/range/algorithm/sort.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/numeric.hpp>

using boost::irange;
using namespace std;

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * */

const vector<int> P = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

const vector<int> B = {53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127};
int b = 16;

const int INF = 30000, MAXM = 121, BITS = 15;

int fac[MAXM + 1];
void init() {
   assert(BITS == P.size());
   assert(b == B.size());
   fac[1] = 0;
   for (int n: irange(2, MAXM + 1)) {
      fac[n] = -1;
      for (int i: irange(0, int(P.size()))) if (n % P[i] == 0) {
         if (fac[n / P[i]] == -1) break;
         fac[n] = fac[n / P[i]] | (1 << i);
         break;
      }
   }
}

class Solve {
   int n;
   vector<int> a;
   unordered_map<int, short> mem[20];

   int walk(int step, int prev, int msk) {
      if (step == n) return 0;
      int bits = __builtin_popcount(msk);
      //if (1 < a[step] && BITS - bits < n - step) return INF;
      if (mem[step][msk] != 0) return mem[step][msk];
      int res = INF;
      for (int i: irange(a[step], MAXM + 1)) {
         int f = fac[i];
         if (f == -1) continue;
         if (f & msk) continue;
         res = min(res, i + walk(step + 1, i, f | msk));
      }
      return mem[step][msk] = res;
  }

   int best_pay() {
      // special case
      if (a[0] == 0 && a[n - 1] <= 1) {
         return n - 1;
      }
      for (int& x: a) if (x == 0) x = 1;
      int res = INF;
      int N = n;
      for (int primes: irange(0, min(n, b))) {
         int cur = 0;
         for (int i : irange(0, primes)) cur += B[i];
         n -= primes;
         //cout << n << endl;
         for (int i: irange(0, n)) mem[i].clear();
         res = min(res, cur + walk(0, 1, 0));
         n = N;
      }
      return res;
      //return walk(0, 1, 0);
   }

   public:
   int solve() {
      int k;
      cin >> n >> k;
      a = vector<int>(n);
      for (int& x: a) cin >> x;
      int sum = boost::accumulate(a, 0);
      boost::sort(a);
      for (int& x: a) x = (x + k - 1) / k;
      return k * best_pay() - sum;
   }
};

int main() {
   ios_base::sync_with_stdio(0);
   init();
   int T; cin >> T;
   for (int q: irange(1, T +1)) cout << "Case #" << q << ": " << Solve().solve() << endl;
   return 0;
}

