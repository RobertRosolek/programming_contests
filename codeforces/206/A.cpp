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

const int DBG = 0, INF = int(1e9);


int n, l, r, ql, qr;
vector<int> w, sm;

int solve(int left, int right, int lastLeft) {
   if (left > right)
      return 0;
   if (left == right)
      return min(w[left] * l + lastLeft * ql, w[right] * r + (1 - lastLeft) * qr);
   int sum = sm[right];
   if (left > 0)
      sum -= sm[left - 1];
   if (lastLeft) {
      int res = solve(left, right - 1, 0) + w[right] * r;
      return min(res, sum * l + (right - left + 1) * ql);
   }
   int res = solve(left + 1, right, 1) + w[left] * l;
   return min(res, sum * r + (right - left + 1) * qr);
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   cin >> n >> l >> r >> ql >> qr;

   w = vector<int>(n);
   for (int i = 0; i < n; ++i)
      cin >> w[i];

   sm = vector<int>(n);
   sm[0] = w[0];
   for (int i = 1; i < n; ++i)
      sm[i] = w[i] + sm[i - 1];

   int res = min(solve(1, n - 1, 1) + w[0] * l, solve(0, n - 2, 0) + w[n - 1] * r);

   cout << res << endl;

   return 0;
}

