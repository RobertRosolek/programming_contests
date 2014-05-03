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

using ll = long long int;
using ui = unsigned int;
using prt = pair<ui, ui>;

const int DBG = 0, INF = int(1e9), B = 31;

inline auto andi(ui m, int i) { return m & (1 << i); }
inline auto xori(ui m, int i) { return m ^ (1 << i); }
inline auto upi(ui m, int i) { return m & (~( (1 << i) - 1)); };

auto fac(ui a)
{
   vector<prt> res;
   for (int i = B - 1; i >= 0; --i)
      if (andi(a, i)) res.emplace_back(upi(a, i + 1), i);
   return res;
}

auto fac2(ui k)
{
   vector<prt> res(1, make_pair(k, 0));
   for (int i = B - 1; i >= 0; --i)
      if (!andi(k, i)) res.emplace_back(xori(upi(k, i), i), i);
   return res;
}

auto solve(prt a, prt b, prt k)
{
   ll res = 1;
   auto mask_a = a.first, mask_b = b.first, mask_k = k.first;
   auto pos_a = a.second, pos_b = b.second, pos_k = k.second;
   for (int i = B - 1; i >= 0; --i) {
      auto ba = andi(mask_a, i), bb = andi(mask_b, i), bk = andi(mask_k, i);
      if (i >= pos_k) {
         if (i >= pos_a && i >= pos_b) {
            if ((ba & bb) != bk) return 0ll;
            continue;
         }
         auto proc = [&](ui bt) {
            if (bk && !bt) return true;
            if (!bk && !bt) res *= 2;
            return false;
         };
         if (i >= pos_a) {
            if (proc(ba)) return 0ll;
            continue;
         }
         if (i >= pos_b) {
            if (proc(bb)) return 0ll;
            continue;
         }
         if (!bk) res *= 3;
         continue;
      }
      if (i < pos_a) res *= 2;
      if (i < pos_b) res *= 2;
   }
   return res;
}

int main()
{
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int t; cin >> t;
   for (auto q: irange(1, t + 1)) {
      cout << "Case #" << q << ": ";
      ui a, b, k;
      cin >> a >> b >> k;
      ll res = 0;
      auto fa = fac(a), fb = fac(b);
      auto fk = fac2(k);
      for (auto ita: fa) for (auto itb: fb) for (auto itk: fk)
         res += solve(ita, itb, itk);
      cout << ll(a) * ll(b) - res << endl;
   }
   return 0;
}
