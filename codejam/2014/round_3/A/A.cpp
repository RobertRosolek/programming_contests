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
#include <boost/range/numeric.hpp>

using namespace std;
using namespace boost;

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * */

const int DBG = 0, INF = int(1e9);
using ll = long long int;

void solve()
{
   int n;
   ll p, q, r, s; cin >> n >> p >> q >> r >> s;
   vector<ll> v(n), u(n);
   for (auto i = 0; i < n; ++i)
      v[i] = (i * p + q) % r + s;
   boost::partial_sum(v, u.begin());
   ll sum = u.back(), tail = sum, res = sum;
   for (auto i: irange(0, n)) {
      tail -= v[i];
      auto prev = u[i];
      auto it = std::lower_bound(u.begin(), u.end(), prev / 2);
      assert(it <= u.begin() + i);
      auto check = [&](decltype(u.begin()) it) {
         auto cur = max(*it, max(prev - *it, tail));
         res = min(res, cur);
      };
      check(it);
      if (it < u.begin() + i) check(it + 1);
      if (it > u.begin()) check(it - 1);
   }
   cout << setprecision(12) << double(sum - res) / sum;
}

int main()
{
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int tt; cin >> tt;
   for (auto i: irange(0, tt)) {
      cout << "Case #" << i + 1 << ": ";
      solve();
      cout << std::endl;
   }
   return 0;
}
