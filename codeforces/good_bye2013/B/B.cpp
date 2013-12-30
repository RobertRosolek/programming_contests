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
   vector<int>a(n); for (auto& x: a) cin >> x;
   int mx = *max_element(a.begin(), a.end());
   for (int q = 0; q < mx; ++q) {
      for (int i = 0; i < n; ++i) {
         if (a[i] > 0) {
            cout << "P";
            --a[i];
         }
         if (i < n - 1) cout << "R";
      }
      for (int i = 0; i < n - 1; ++i) cout << "L";
   }
   cout << endl;
   return 0;
}

