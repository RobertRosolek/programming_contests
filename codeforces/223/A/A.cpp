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

const int MAXL = int(1e5);

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int m; cin >> m;
   vector<int> prefix;
   vector<pair<int, int>> v;
   for (int q = 0; q < m; ++q) {
      int t; cin >> t;
      if (t == 1) {
         int x; cin >> x;
         if (prefix.size() < MAXL) prefix.push_back(x);
         else v.push_back(make_pair(-1, x));
         continue;
      }
      int l, c; cin >> l >> c;
      while (prefix.size() < MAXL && c > 0)  {
         for (int i = 0; i < l; ++i) prefix.push_back(prefix[i]);
         --c;
      }
      if (c > 0) v.push_back(make_pair(c, l));
   }
   int p = 0;
   LL passed = prefix.size();
   int n; cin >> n;
   for (int q = 0; q < n; ++q) {
      LL y; cin >> y; --y;
      if (y < prefix.size()) {
         cout << prefix[y] << " ";
         continue;
      }
      while (true) {
         LL cur = y - passed;
         if (v[p].first == -1) {
            if (cur == 0) {
               cout << v[p].second << " ";
               break;
            }
            ++passed;
            ++p;
            continue;
         }
         if (cur < LL(v[p].first) * v[p].second) {
            cout << prefix[cur % v[p].second] << " ";
            break;
         }
         passed += LL(v[p].first) * v[p].second;
         ++p;
      }
   }

   return 0;
}

