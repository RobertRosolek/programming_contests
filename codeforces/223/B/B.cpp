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

typedef pair<int, int> PII;

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int n, m; cin >> n >> m;
   set<pair<PII, PII>> ops;
   for (int q = 0; q < m; ++q) {
      int c; cin >> c;
      if (c == 1) {
         int t, l, r, x; cin >> t >> l >> r >> x;
         ops.insert(make_pair(make_pair(t, x), make_pair(l, r)));
         continue;
      }
      int t, v; cin >> t >> v;
      set<int> s;
      int lev = t, l = v, r = v;
      auto it = ops.begin();
      while (it != ops.end()) {
         int op_lev = it->first.first, op_x = it->first.second, op_l = it->second.first, op_r = it->second.second;
         //cout << lev << " " << l << " " << r << " " << op_lev << " " << op_l << " " << op_r << endl;
         if (lev < op_lev) {
            auto find_bef = [](int lev, int v) {
               int bef = v - 1;
               int pow_bef = 32 - __builtin_clz(v); if (__builtin_popcount(v) == 1) --pow_bef;
               //cout << v << " " << pow_bef << endl;
               return bef + pow_bef;
            };
            l = find_bef(lev, l) + 1;
            if (__builtin_popcount(r) == 1) r = find_bef(lev, r) + 2; else r = find_bef(lev, r) + 1;
            ++lev;
            continue;
         }
         if (op_lev < lev) {
            ++it;
            continue;
         }
         if (op_r < l || r < op_l) {
            ++it;
            continue;
         }
         s.insert(op_x);
         ++it;
      }
      cout << s.size() << endl;
   }
   return 0;
}

