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
   int not_used = 0, used = 0; cin >> not_used;
   int b; cin >> b;
   int res = 0;
   while (not_used > 0 || used >= b) {
      res += not_used;
      used += not_used;
      not_used = 0;
      not_used += used / b;
      used %= b;
   }
   cout << res << endl;
   return 0;
}

