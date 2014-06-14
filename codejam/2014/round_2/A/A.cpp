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

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * */

const int DBG = 0, INF = int(1e9);

void solve()
{
   int n, x;
   cin >> n >> x;
   vector<int> v(n);
   for (auto& c: v) cin >> c;
   sort(v.begin(), v.end());
   int res = 0;
   auto left = v.begin(), right = --v.end();
   while (left < right) {
      ++res;
      if (*left + *right <= x)
         ++left;
      --right;
   }
   if (left == right)
      ++res;
   cout << res;
   return;
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
