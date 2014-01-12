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

int bin(int n) {
   int m = 1;
   while (m <= n) m *= 2;
   return m;
}

class CountTree {
   int M;
   vector<int> w;
   public:
   CountTree(int n) : M(bin(n)), w(vector<int>(2 * bin(n))) {}
   void insert(int v) {
      v += M;
      while (v > 0) {
         w[v]++;
         v /= 2;
      }
   }
   int query(int a, int b) {
      a += M, b += M;
      int res = w[a];
      if (a != b) res += w[b];
      while (a / 2 != b / 2) {
         if (a % 2 == 0) res += w[a + 1];
         if (b % 2 == 1) res += w[b - 1];
         a /= 2, b /= 2;
      }
      return res;
   }
};

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   string s; cin >> s;
   int m; cin >> m;
   vector<pair<pair<int, int>, int>> q(m);
   for (auto& it: q) cin >> it.first.first >> it.first.second;
   for (int i = 0; i < m; ++i) q[i].second = i;
   for (auto& it: q) swap(--it.first.first, --it.first.second);
   sort(q.begin(), q.end());
   CountTree matches(s.size());
   vector<int> st;
   int pos = 0;
   vector<int> result(m);
   for (auto& it: q) {
      int l = it.first.second, r = it.first.first, tc = it.second;
      for (; pos <= r; ++pos) {
         if (s[pos] == '(') {
            st.push_back(pos);
            continue;
         }
         if (st.empty()) continue;
         matches.insert(st.back());
         st.pop_back();
      }
      result[tc] = 2 * matches.query(l, r);
   }
   for (auto it: result) cout << it << endl;
   return 0;
}

