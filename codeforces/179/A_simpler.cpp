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

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int n, m, k; cin >> n >> m >> k;
   auto a = vector<LL>(n, 0);
   for (auto& x: a) cin >> x;
   auto op = vector<pair<LL, PII>>(m);
   for (auto& it: op) {
      cin >> it.second.first >> it.second.second >> it.first;
      --it.second.first, --it.second.second;
   }
   auto q = vector<PII>(k);
   for (auto& it: q) {
      cin >> it.first >> it.second;
      --it.first, --it.second;
   }

   auto opsCnt = vector<LL>(m + 1, 0);
   for (auto& it: q) ++opsCnt[it.first], --opsCnt[it.second + 1];
   partial_sum(opsCnt.begin(), opsCnt.end(), opsCnt.begin());

   auto delta = vector<LL>(n + 1, 0);
   for (auto i = 0; i < m; ++i) delta[op[i].second.first] += op[i].first * opsCnt[i], delta[op[i].second.second + 1] -= op[i].first * opsCnt[i];
   partial_sum(delta.begin(), delta.end(), delta.begin());
   for (auto i = 0; i < n; ++i) cout << a[i] + delta[i] << " ";
   cout << endl;

   return 0;
}

