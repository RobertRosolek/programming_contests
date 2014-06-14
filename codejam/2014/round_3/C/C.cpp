#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <map>

#include <boost/range/irange.hpp>

using namespace std;
using namespace boost;

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * */

const int DBG = 0, INF = int(1e9);

using pii = pair<int, int>;

void solve()
{
   int n; cin >> n;
   vector<int> ue, ul;
   map<int, vector<pair<int,char>>> v;
   for (auto i: irange(0, n)) {
      char c; cin >> c;
      int id; cin >> id;
      if (id == 0) {
         if (c == 'E') ue.push_back(i); else assert(c == 'L'), ul.push_back(i);
         continue;
      }
      v[id].emplace_back(i, 'E');
   }
   vector<pii> e, l;
   vector<int> unused_l, unused_e, known_l, known_e;
   for (auto it: v) {
      auto& seq = it.second;
      int m = seq.size();
      for (auto i : irange(1, m))
         if (seq[i].second == seq[i - 1].second) {
            auto seg = make_pair(seq[i - 1].first, seq[i].first);
            if (seq[i].second == 'E') e.push_back(seg);
            else l.push_back(seg);
         }
      if (seq.front().second == 'L')
         known_l.push_back(seq.front().first);
      if (seq.back().second == 'E')
         known_e.push_back(seq.back().first);
   }

   auto flip = [](vector<pii>& v) { for (auto& x: v) swap(x.first, x.second); };
   const string err = "CRIME TIME";

   flip(e);
   sort(e.begin(), e.end());
   flip(e);
   {
      auto sit = e.begin();
      for (auto p: ul) {
         if (sit == e.end()) {unused_l.push_back(p); continue;}
         int l = sit->first, r = sit->second;
         cout << p << " " << l << " " << r << endl;
         if (p < l) {unused_l.push_back(p); continue;}
         if (p > r) {cout << err; return;}
         ++sit;
      }
      if (sit != e.end()) { cout << err; return; }
   }

   auto neg_sec = [](vector<pii>& v) { for (auto& x: v) x.second *= -1; };
   neg_sec(l);
   sort(l.begin(), l.end());
   reverse(l.begin(), l.end());
   neg_sec(l);
   reverse(ue.begin(), ue.end());
   {
      auto sit = l.begin();
      for (auto p: ue) {
         if (sit == l.end()) {unused_e.push_back(p); continue;}
         int l = sit->first, r = sit->second;
         if (p > r) {unused_e.push_back(p); continue;}
         if (p < l) {cout << err; return;}
         ++sit;
      }
      if (sit != l.end()) { cout << err; return; }
   }
   vector<pii> L, R;
   for (auto x: unused_e)
      L.emplace_back(x, 0);
   for (auto x: unused_l)
      R.emplace_back(x, 0);
   for (auto x: known_e)
      L.emplace_back(x, 1);
   for (auto x: known_l)
      R.emplace_back(x, 1);
   bal = L.size();
   sort(L.begin(), L.end());
   sort(R.begin(), R.end());
   int sl = L.size(), pl = 0;
   int sr = R.size(), pr = sr - 1;
   while (pl <= pr) {

   }
   cout << bal;

}

int main()
{
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int tt; cin >> tt;
   for (auto i: irange(0, tt)) {
      cout << "Case #" << i + 1 << ": ";
      solve();
      cout << std::endl;
      exit(0);
   }
   return 0;
}
