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
   int n; cin >> n;
   vector<int> a(n);
   for (auto& x: a) cin >> x;
   int left = 0, right = n - 1, res;
   while (left <= right) {
      int m = left;
      for (int i = left; i <= right; ++i) if (a[i] < a[m]) m = i;
      if (m - left <= right - m) {
         res += m - left;
         for (int i = m - 1; i >= left; --i)
            swap(a[i], a[i + 1]);
         ++left;
      } else {
         res += right - m;
         for (int i = m + 1; i <= right; ++i)
            swap(a[i - 1], a[i]);
         --right;
      }
   }
   cout << res;
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
