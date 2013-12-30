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

const int DBG = 0, INF = int(1e9);

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int n; cin >> n;
   vector<pair<int,int>> a(n); for (auto& x: a) cin >> x.first;
   for (int i = 0; i < n; ++i) a[i].second = i;
   int cur = 1, res = 0;
   sort(a.begin(), a.end());
   vector<int> result(n);
   for (auto x: a) {
      cur = max(cur, x.first);
      res += cur;
      result[x.second] = cur;
      ++cur;
   }
   for (auto x: result) cout << x << " ";
   cout << endl;
   return 0;
}

