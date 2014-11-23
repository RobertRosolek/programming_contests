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

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int T;
   cin >> T;
   for (int q = 0; q < T; ++q) {
      cout << "Case #" << q + 1 << ": ";
      int n;
      cin >> n;
      VI A(n), B(n);
      for (int i = 0; i < n; ++i)
         cin >> A[i];
      for (int i = 0; i < n; ++i)
         cin >> B[i];
      int R[n][n];
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            R[i][j] = 0;
      for (int j = 0; j < n; ++j) {
         bool first = true;
         for (int i = j - 1; i >= 0; --i)
            if (A[i] >= A[j])
               R[j][i] = 1;
            else if (first) {
               first = false;
               R[i][j] = 1;
            }
      }
      for (int i = 0; i < n; ++i) {
         bool first = true;
         for (int j = i + 1; j < n; ++j) 
            if (B[i] <= B[j])
               R[i][j] = 1;
            else if (first) {
               first = false;
               R[j][i] = 1;
            }
      }
      set<int> S;
      VI smaller(n);
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            if (R[i][j])
               smaller[j]++;
      for (int i = 0; i < n; ++i)
         if (smaller[i] == 0)
            S.insert(i);
      VI res;
      while (!S.empty()) {
         int k = *S.begin();
         S.erase(S.begin());
         res.push_back(k);
         for (int i = 0; i < n; ++i)
            if (R[k][i]) {
               smaller[i]--;
               if (smaller[i] == 0)
                  S.insert(i);
            }
      }
      assert(res.size() == n);
      VI rs(n);
      for (int i = 0; i < n; ++i)
         rs[res[i]] = i;
      for (VI::iterator it = rs.begin(); it != rs.end(); ++it)
         cout << " " << *it + 1;
      cout << endl;
   }

   return 0;
}	
