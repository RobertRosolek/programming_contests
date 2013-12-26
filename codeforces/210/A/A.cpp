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

typedef long long LL;
typedef pair<int,int> PII;

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

const int DBG = 0, INF = int(1e9);

struct op {
   int t, l, r, m;
};

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int n, m;
   cin >> n >> m;

   vector<int> delta(n, 0), bound(n, INF);

   vector<op> ops;

   for (int q = 0; q < m; ++q) {
      op o;
      cin >> o.t >> o.l >> o.r >> o.m;
      --o.l, --o.r;
      ops.push_back(o);
      if (o.t == 1) {
         for (int i = o.l; i <= o.r; ++i) delta[i] += o.m;
         continue;
      }
      for (int i = o.l; i <= o.r; ++i) bound[i] = min(bound[i], o.m - delta[i]);
   }

   bool ok = true;
   for (int i = 0; i < n; ++i) if (bound[i] < -INF) ok = false;
   vector<int> result = bound;
   for (vector<op>::const_iterator it = ops.begin(); it != ops.end(); ++it) {
      op o = *it;
      if (o.t == 1) {
         for (int i = o.l; i <= o.r; ++i) bound[i] += o.m;
         continue;
      }
      bool found = false;
      for (int i = o.l; i <= o.r; ++i) if (bound[i] == o.m) found = true;
      if (!found) ok = false;
   }

   if (!ok) {
      cout << "NO\n";
      return 0;
   }
   cout << "YES\n";
   for (int i = 0; i < n; ++i)
      cout << result[i] << " ";
   cout << endl;

   return 0;
}

