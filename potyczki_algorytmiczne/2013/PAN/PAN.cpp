#include <iomanip>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

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

int main() {
   ios_base::sync_with_stdio(0);

   int n, m;
   scanf("%d %d", &n, &m);

   VI row(n), col(m);

   for (int i = 0; i < n; ++i)
      scanf("%d", &row[i]);
   for (int i = 0; i < m; ++i)
      scanf("%d", &col[i]);

   if (* max_element(row.begin(), row.end()) != * max_element(col.begin(), col.end())) 
      cout << "NIE\n";
   else {
      sort(row.begin(), row.end());
      sort(col.begin(), col.end());
      LL sm = 0, left = n, res = 0;
      for (VI::const_iterator cit = col.begin(), rit = row.begin(); cit != col.end(); ++cit) {
         while (rit != row.end() && *rit <= *cit) {
            sm += *rit;
            ++rit;
            --left;
         }
         res += sm;
         res += left * (*cit);
      }

      cout << res << endl;
   }  

   return 0;
}	
