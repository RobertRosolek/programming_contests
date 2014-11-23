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

const int P = 1000002013;

inline int incres(int n, int dst, int cnt) { 
   LL res = 2 * LL(n) - dst + 1;
   if (res % 2 == 0) {
      res /= 2;
      res = (res * dst) % P;
      assert(res >= 0);
   }
   else {
      assert(dst % 2 == 0);
      res = res % P;
      res = (res * (dst / 2)) % P;
      assert(res >= 0);
   }
   res = (res * cnt) % P;
   if (res < 0)
      cerr << n << " " << dst << " " << cnt << endl;
   assert(res >= 0);
   return res;
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int T;
   cin >> T;
   for (int q = 0; q < T; ++q) {
      cout << "Case #" << q + 1 << ": ";
      int n, m;
      cin >> n >> m;
      vector<PII> v;
      v.reserve(2 * m);
      LL res = 0, normal = 0;
      for (int i = 0; i < m; ++i) {
         int o, e, p;
         cin >> o >> e >> p;
         int dst = e - o;
         normal = (normal + incres(n, dst, p) ) % P;
         assert(normal >= 0);
         v.push_back(make_pair(o,-p));
         v.push_back(make_pair(e, p));
      }  
      sort(v.begin(), v.end());

      map<int, int> M;

      cerr << q << endl;
      for (vector<PII>::iterator it = v.begin(); it != v.end(); ++it) {
         if (it->second < 0)
            M[it->first] = (M[it->first] -it->second) % P;
         else {
            LL cnt = it->second;
            while (cnt > 0) {
               map<int, int>::reverse_iterator fit = M.rbegin();
               int c = min(cnt, fit->second), dst = it->first - fit->first;
               //if (c < 0)
               //   cerr << fit->second << " " << M[fit->first] << " " << cnt << endl;
               assert(c >= 0);
               res = (res + incres(n, dst, c % P)) % P;
               assert(res >= 0);
               cnt -= c;
               M[fit->first] -= c;
               assert(M[fit->first] >= 0);
               for(map<int,int>::iterator it = M.begin(); it != M.end(); ++it)
                  assert(it->second >= 0);
               if (M[fit->first] == 0)
                  M.erase(fit->first);
            }
         }
      }
      cout << ((normal - res + P) % P) << endl;
   }

   return 0;
}	
