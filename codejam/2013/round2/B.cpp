#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> PII;
typedef double LD;

/* CHECKLIST 
 * 1) long longs 
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

const int DBG = 0, INF = int(1e9);


LL simulate_high(LL n, LL m) {
   LL bigger = (1LL << n) - m, smaller = m - 1, all = (1LL << n);
   for (LL i = 0; i < n; ++i, all /= 2) {
      assert(bigger + 1 + smaller == all);
      //cout << n << " " << m << " " << i << " " << smaller << " " << bigger << endl;
      if (bigger == 0)
         return smaller + 1;
      if (smaller == 0)
         return 1;
      bigger -= 1;
      if (bigger % 2 == 0) {
         bigger /= 2;
         assert(smaller % 2 == 0);
         smaller /= 2;
      }
      else {
         assert(smaller % 2 == 1);
         smaller = (smaller + 1) / 2;
         bigger = bigger / 2;
      }
   }
   //cout << n << " " << m << " " << smaller << " " << bigger << endl;
   assert(false);
}

LL simulate_low(LL n, LL m) {
   m = (1LL << n) + 1 - m;
   LL pos = simulate_high(n, m);
   return (1LL << n) + 1 - pos;
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int T;
   cin >> T;
   for (int q = 0; q < T; ++q) {
      cout << "Case #" << q + 1 << ": ";
      LL n, p;
      cin >> n >> p;
      {
         LL left = 1, right = (1LL << n);
         while (left < right) {
            LL m = (left + right + 1) / 2;
            LL pos = simulate_low(n, m);
            if (pos > p)
               right = m - 1;
            else
               left = m;
         }
         cout << left - 1 << " ";
      }
      {
         LL left = 1, right = (1LL << n);
         while (left < right) {
            LL m = (left + right + 1) / 2;
            LL pos = simulate_high(n, m);
            if (pos <= p)
               left = m;
            else
               right = m - 1;
         } 
         cout << left - 1 << endl;
      }
   }

   return 0;
}	
