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
   vector<pair<int, int>> v(n);
   for (auto& x: v) cin >> x.first;
   for (int i = 0; i < n; ++i) v[i].second = i;
   sort(v.begin(), v.end());
   vector<int> a(n);
   a[0] = 0;
   int pos = 1;
   for (auto i = 0; i < (n + 2) / 3; ++i, ++pos) if (pos < n) a[pos] = 0;
   int mem = pos - 1;
   for (auto i = 0; i < (n + 2) / 3; ++i, ++pos) if (pos < n) a[pos] = v[pos].first;
   for (;pos < n; ++pos, --mem) a[pos] = mem;
   cout << "YES" << endl;
   vector<int> resA(n), resB(n);
   for (auto i = 0; i < n; ++i) resA[v[i].second] = a[i], resB[v[i].second] = v[i].first - a[i];
   for (auto x: resA) cout << x << " ";
   cout << endl;
   for (auto x: resB) cout << x << " ";
   cout << endl;
   return 0;
}

