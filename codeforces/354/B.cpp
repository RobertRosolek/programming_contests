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

const int DBG = 0, INF = int(1e9), MAXN = 20, MAXB = 1<<MAXN;

vector<string> T;
int n;

int dp[2 * MAXN + 1][MAXB];

vector<PII> getPos(int r, int msk) {
   vector<PII> res;
   for (int i = 0; i < n; ++i) {
      int j = r - i;
      if (j < 0)
         break;
      if (msk & (1<<j))
         res.push_back(make_pair(i, j));
   }
   return res;
}

int getMask(vector<PII>& v) {
   int res = 0;
   for (vector<PII>::iterator it = v.begin(); it != v.end(); ++it)
      res |= 1<<(it->second);
   return res;
}

int solve(int r, int msk) {
   if (r == 2 * MAXN + 1)
      return 0;
   if (dp[r][msk] != INF)
      return dp[r][msk];
   vector<PII> pos = getPos(r, msk);
   int bal = 0;
   if (T[pos[0].first][pos[0].second] == 'a')
      bal = 1;
   else if (T[pos[0].first][pos[0].second] == 'b')
      bal = -1;
   if (r % 2 == 1)
      bal *= -1;
   int res = 
   for (char c = 'a'; c <= 'z'; ++c) {
      set<PII> newPos;
      for (vector<PII>::iterator it = pos.begin(); it != pos.end(); ++it) {
         if (it->first + 1 < n && T[it->first + 1][it->second] == c)
            newPos.insert(make_pair(it->first + 1, it->second));
         if (it->second + 1 < n && T[it->first][it->second + 1] == c)
            newPos.insert(make_pair(it->first + 1, it->second));
      }
      vector<PII> vPos;
      for (set<PII>::iterator it = newPos.begin(); it != newPos.end(); ++it)
         vPos.push_back(*it);
      int val = solve(r + 1, getMask(vPos));
   }
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   cin >> n;
   T = vector<string>(n);
   for (int i = 0; i < n; ++i)
      cin >> T[i];

   for (int i = 0; i < 2 * MAXN + 1; ++i)
      for (int j = 0; j < MAXB; ++j)
         dp[i][j] = INF;

   int res = solve(0, 1);

   return 0;
}

