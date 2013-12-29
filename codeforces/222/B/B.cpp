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
typedef pair<int, int> PII;

const int DBG = 0, INF = int(1e9);

int n, m;
LL s;
vector<PII> a;
vector<int> res, cap;
vector<pair<PII, LL>> stud;

bool canDo(int t) {
   cap = vector<int>(n, t);
   set<pair<LL, int>> S;
   int si = n - 1;
   LL cost = 0;
   for (auto& ait: a) {
      while (si >= 0 && stud[si].first.first >= ait.first) {
         S.insert(make_pair(stud[si].second, si));
         --si;
      }
      if (S.empty()) return false;
      int next = S.begin()->second, newCost = S.begin()->first; S.erase(S.begin());
      res[ait.second] = stud[next].first.second;
      cost += newCost;
      cap[next]--;
      if (cap[next] > 0) S.insert(make_pair(0, next));
   }
   return cost <= s;
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   cin >> n >> m >> s;
   a = vector<PII>(m); res = vector<int>(m); for (auto& x: a) cin >> x.first;
   for (int i = 0; i < m; ++i) a[i].second = i;
   stud = vector<pair<PII, LL>>(n);
   for (auto& it: stud) cin >> it.first.first;
   for (auto& it: stud) cin >> it.second;
   for (int i = 0; i < n; ++i) stud[i].first.second = i;
   sort(a.begin(), a.end());
   reverse(a.begin(), a.end());
   sort(stud.begin(), stud.end());

   int left = 1, right = m + 1;
   while (left < right) {
      int mid = (left + right) / 2;
      if (canDo(mid)) right = mid;
      else left = mid + 1;
   }
   if (left == m + 1) {
      cout << "NO\n";
      return 0;
   }
   cout << "YES\n";
   assert(canDo(left));
   for (int i = 0; i < m; ++i) cout << res[i] + 1 << " ";
   cout << endl;

   return 0;
}

