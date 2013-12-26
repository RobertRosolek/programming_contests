#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <stack>
using namespace std;

#define ALL(x) x.begin(), x.end()
#define VAR(a,b) __typeof (b) a = b
#define REP(i,n) for (int _n=(n), i=0; i<_n; ++i)
#define FOR(i,a,b) for (int _b=(b), i=(a); i<=_b; ++i)
#define FORD(i,a,b) for (int _b=(b), i=(a); i>=_b; --i)
#define FORE(i,a) for (VAR(i,a.begin ()); i!=a.end (); ++i)
#define PB push_back
#define MP make_pair
#define ST first
#define ND second

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> PII;
typedef double LD;

const int DBG = 0, INF = int(1e9);

struct SegmentTree {
   vector<LL> tab;
   int N;
   int M;
   SegmentTree(const vector<LL>& v) {
      M = v.size();
      N = 2 * M;
      tab = vector<LL>(N,0);
      for (int i = 0; i < M; ++i)
         tab[M + i] = v[i];
   }

   void insert(int a, int b, LL d) {
      int va = M + a, vb = M + b;
      tab[va] += d;
      if (va != vb)
         tab[vb] += d;
      while (va / 2 != vb / 2) {
         if (va % 2 == 0)
            tab[va + 1] += d;
         if (vb % 2 == 1)
            tab[vb - 1] += d;
         va /= 2;
         vb /= 2;
      }
   }

   LL query(int x) {
      int v = M + x;
      LL res = tab[v];
      while (v != 1) {
         v /= 2;
         res += tab[v];
      }
      return res;
   }
};


int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int n,m,k;
   cin >> n >> m >> k;

   vector<LL> a(n);
   REP(i,n)
      cin >> a[i];
   VI l(m),r(m),d(m);
   REP(i,m)
      cin >> l[i] >> r[i] >> d[i];
   int M = 1;
   while (M < m)
      M *= 2;
   int N = 1;
   while (N < n)
      N *= 2;
   vector<LL> A(N,0);
   REP(i,n)
      A[i] = a[i];
   vector<LL> O(M,0);
   SegmentTree t(O);
   REP(i,k) {
      int x,y;
      cin >> x >> y;
      t.insert(x - 1, y - 1, 1);
   }
   SegmentTree T(A);
   REP(i,m) {
      LL mult = t.query(i);
      T.insert(l[i] - 1, r[i] - 1, mult * d[i]);
   }
   REP(i,n)
      cout << T.query(i) << " ";
   cout << endl;

   return 0;
}
