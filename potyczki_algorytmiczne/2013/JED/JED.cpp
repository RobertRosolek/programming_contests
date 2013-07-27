#include <iomanip>
#include <cstdio>
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

int main() {
   ios_base::sync_with_stdio(0);

   int n;
   scanf("%d", &n);

   VI A[3];
   for (int i = 0; i < 3; ++i)
      A[i] = VI(n);

   for (int i = 0; i < 3; ++i)
      for (int j = 0; j < n; ++j)
         scanf("%d", &A[i][j]);

   for (int i = 0; i < 3; ++i)
      for (int j = 0; j < n; ++j)
         --A[i][j];

   // A[0][rev[i]] = i
   VI rev(n, -1);
   for (int j = 0; j < n; ++j)
      rev[A[0][j]] = j;
   for (int j = 0; j < n; ++j)
      assert(rev[j] != -1 && A[0][rev[j]] == j);

   // shifts[i] is equal to shifs that need to be made 
   // on arrays 1 and 2 so that value i is in one row
   vector<PII> shifts(n);
   for (int j = 0; j < n; ++j) {
      shifts[A[1][j]].first =  (rev[A[1][j]] - j + n) % n;
      shifts[A[2][j]].second = (rev[A[2][j]] - j + n) % n;
   }

   sort(shifts.begin(), shifts.end());
   int max_plateau = 1, cur = 1;
   for (int j = 1; j < n; ++j)
      if (shifts[j] == shifts[j - 1]) {
         ++cur;
         max_plateau = max(max_plateau, cur);
      }
      else 
         cur = 1;

   printf("%d\n", max_plateau);

   return 0;
}	
