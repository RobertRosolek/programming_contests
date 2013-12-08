#include <iostream>

#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/irange.hpp>

using namespace std;

int solve() {
   int n, k, c; cin >> n >> k >> c;
   auto canDo = [=] (int misses) {
      int not_misses = n - misses,
          not_misses_height = k / not_misses,
          not_misses_sum = not_misses_height * not_misses,
          misses_sum = (not_misses_height - 1) * misses;
      return c <= not_misses_sum + misses_sum;
   };
   return c + *boost::find_if(boost::irange(0, n), canDo);
}

int main() {
   int T; cin >> T;
   for (int q : boost::irange(1, T + 1)) cout << "Case #" << q << ": " << solve() << endl;
   return 0;
}

