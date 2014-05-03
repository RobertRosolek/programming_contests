#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <map>

#include <boost/range/irange.hpp>

using namespace std;
using namespace boost;

const int DBG = 0, INF = int(1e9);

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int t; cin >> t;
   for (auto q: irange(1, t + 1)) {
      cout << "Case #" << q << ": ";
      int a, b, k;
      cin >> a >> b >> k;
      int res = 0;
      for (auto i: irange(0, a)) for (auto j: irange(0, b))
         res += (i & j) < k;
      cout << res << endl;
   }
   return 0;
}
