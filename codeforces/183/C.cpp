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

const int MAXN = int(1e6);

bool walk(const vector<pair<int, int>>& forbidden, int step, vector<bool>& erased, int eraseLimit) {
   if (step == forbidden.size()) return true;
   int a = forbidden[step].first, b = forbidden[step].second;
   if (erased[a] || erased[b]) return walk(forbidden, step + 1, erased, eraseLimit);
   if (eraseLimit == 0) return false;
   erased[a] = true;
   bool ok = walk(forbidden, step + 1, erased, eraseLimit - 1);
   erased[a] = false;
   if (ok) return true;
   erased[b] = true;
   ok = walk(forbidden, step + 1, erased, eraseLimit - 1);
   erased[b] = false;
   if (ok) return true;
   if (eraseLimit == 1) return false;
   erased[a] = erased[b] = true;
   ok = walk(forbidden, step + 1, erased, eraseLimit - 2);
   erased[a] = erased[b] = false;
   return ok;
}



int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int n, k; cin >> n >> k;
   vector<int> a(n);
   for (auto& x: a) cin >> x;
   int mx = *max_element(a.begin(), a.end());
   sort(a.begin(), a.end());
   reverse(a.begin(), a.end());
   vector<int> cnt(mx + 1, 0);
   for (auto i = 0; i < n; ++i) for (auto j = 0; j < i; ++j) ++cnt[a[j] - a[i]];
   vector<vector<pair<int,int>>> v(mx + 1);
   for (auto i = 0; i < mx + 1; ++i) if (cnt[i] <= 10) v[i].reserve(cnt[i]);
   for (auto i = 0; i < n; ++i) for (auto j = 0; j < i; ++j) {
      int x = a[j] - a[i];
      if (cnt[x] <= 10) v[x].push_back(make_pair(i, j));
   }
   for (int m = 1; m <= mx + 1; ++m) {
      vector<pair<int, int>> forbidden;
      forbidden.reserve(10);
      bool ok = true;
      for (int x = m; ok && x <= mx; x += m) if (v[x].size() > 4 || cnt[x] > 10) ok = false; else copy(v[x].begin(), v[x].end(), back_inserter(forbidden));
      if (!ok) continue;
      vector<bool> erased(n, false);
      if (walk(forbidden, 0, erased, k)) {
         cout << m << endl;
         return 0;
      }
   }
   assert(false);
   return 0;
}

