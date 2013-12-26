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

const int DBG = 0, INF = int(1e9), MAXOVERFLOW = 10;

vector<int> d;
int k;
int dp[20][MAXOVERFLOW];
vector<LL> dps[20][MAXOVERFLOW];

void setDigits(LL n) {
   d.clear();
   while (n > 0) {
      d.push_back(n % 10);
      n /= 10;
   }
   k = d.size();
   for (int i = 0; i < 20; ++i)
      for (int j = 0; j < MAXOVERFLOW; ++j)
         dp[i][j] = -1;
}

int solve(int pos, int overflow, vector<LL>& res) {
   if (pos == k) {
      if (overflow != 0)
         return -1;
      res = vector<LL>(6, 0);
      return 1;
   }
   if (dp[pos][overflow] != -1) {
      res = dps[pos][overflow];
      return dp[pos][overflow];
   }
   for (int a = 0; a <= 6; ++a)
      for (int b = 0; a + b <= 6; ++b) {
         if ( (a * 7 + b * 4 + overflow) % 10 != d[pos])
            continue;
         int newOverflow = (a * 7 + b * 4 + overflow) / 10;
         int ok = solve(pos + 1, newOverflow, res);
         if (ok != -1) {
            dp[pos][overflow] = ok;
            for (int i = 0; i < 6; ++i) {
               res[i] *= 10;
               if (i < a)
                  res[i] += 7;
               else if (i < a + b)
                  res[i] += 4;
            }
            dps[pos][overflow] = res;
            return ok;
         }
      }
   return -1;
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int t;
   cin >> t;

   for (int q = 0; q < t; ++q) {
      LL n;
      cin >> n;
      setDigits(n);
      vector<LL> sol;
      int ok = solve(0, 0, sol);
      if (ok == -1) {
         cout << -1 << endl;
         continue;
      }
      cout << sol[0];
      for (int i = 1; i < 6; ++i)
         cout << " " << sol[i];
      cout << endl;
   }

   return 0;
}

