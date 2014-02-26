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

const int DBG = 0, INF = int(1e9), P = INF + 7;

map<int, int> m;

void facNum(LL x) {
   if (x <= 1) return;
   for (LL a = 2; a * a <= x; ++a) {
      while (x % a == 0) m[a]++, x /= a;
   }
   if (x > 1) m[x]++;
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int n; cin >> n;
   vector<LL> v(n); for (LL& a : v) cin >> a;
   for (LL a: v) facNum(a);
   LL res = 1;
   int N = n;
   LL dp[2][16000];
   for (int n = 0; n <= N; ++n)
   for (int k = 0; k < 16000; ++k) {
      int nm = n % 2, nr = nm ^ 1;
      if (k == 0) { dp[nm][0] = 1; continue; }
      if (n == 0) { dp[0][k] = 0; continue; }
      dp[nm][k] = (dp[nm][k - 1]+ dp[nr][k]) % P;
   }
   for (auto it: m) {
      int cnt = it.second;
      res = (res * (dp[n % 2][cnt])) % P;
   }
   cout << res << endl;
   return 0;
}

