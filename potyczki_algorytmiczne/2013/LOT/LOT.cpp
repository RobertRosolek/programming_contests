#include <iomanip>
#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef long long int LL;
typedef pair<int,int> PII;
typedef double LD;

/* CHECKLIST 
 * 1) long longs 
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

const int DBG = 0, INF = int(1e9), MAXN = int(5e5);

void read_data(int &n, VI &v) {
   scanf("%d", &n);

   char s[MAXN + 1];
   scanf("%s", s);

   assert(strlen(s) == (unsigned int) n);

   v = VI(n);
   for (int i = 0; i < n; ++i)
      v[i] = s[i] - 'A';
}

int main() {
   ios_base::sync_with_stdio(0);

   int n;
   VI v;
   read_data(n, v);

   // dp[i][a] - minimal number of letter changes in fragment v[0]...v[i] 
   // to make it valid and so that last element is equal to a
   vector<VI> dp(n, VI(3));
   for (int a = 0; a < 3; ++a)
      dp[0][a] = (v[0] != a);
   for (int i = 1; i < n; ++i) 
      for (int a = 0; a < 3; ++a)
         dp[i][a] = min(dp[i - 1][(a + 1) % 3], dp[i - 1][(a + 2) % 3]) + (v[i] != a);

   int res = INF;
   for (int a = 0; a < 3; ++a)
      res = min(res, dp[n - 1][a]);

   printf("%d\n", res);

   return 0;
}	
