#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <map>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/range/irange.hpp>

using namespace std;

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * */

const int DBG = 0, INF = int(1e9);

typedef boost::multiprecision::int128_t LL;

LL pow(LL x, int k) {
   LL res = 1;
   for (int i : boost::irange(0, k)) res *= x;
   return res;
}

class Solve {
   string L;
   LL l;

   int getLen(LL& n) {
      int len = 1;
      LL p = l;
      while (p < n) {
         n -= p;
         ++len;
         p *= l;
      }
      return len;
   }

   string walk(int len, LL n) {
      if (len == 0) { assert(n == 1); return ""; }
      LL p = pow(l, len - 1);
      for (char c: L) {
         if (n <= p) return c + walk(len - 1, n);
         n -= p;
      }
      assert(false);
   }

   public:
   string solve() {
      LL n;
      cin >> L >> n;
      l = L.size();
      int len = getLen(n);
      return walk(len, n);
   }
};

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int T; cin >> T;
   for (int q: boost::irange(1, T + 1)) cout << "Case #" << q << ": " << Solve().solve() << endl;

   return 0;
}

