#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <sstream>
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

   string s;
   cin >> s;
   map<char, int> m;
   for (char c: s) m[c]++;
   assert(m['1']-- > 0 && m['6']-- > 0 && m['8']-- > 0 && m['9']-- > 0);
   s = "";
   for (auto it : m) if (it.first != '0') while (it.second--) s += it.first;
   s += '1'; s += '6'; s += '8'; s += '9';
   int n = s.size();
   vector<int> pat = {1, 3, 2, -1, -3, -2};
   int ps = pat.size();
   do {
      int sm = 0;
      for (int i = 0; i < n; ++i) sm += pat[i % ps] * (s[n - i - 1] - '0');
      if (sm % 7 == 0) {
         while (m['0']-- > 0) s += '0';
         cout << s << endl;
         return 0;
      }
   } while (next_permutation(s.end() - 4, s.end()));
   assert(false);
   return 0;
}

