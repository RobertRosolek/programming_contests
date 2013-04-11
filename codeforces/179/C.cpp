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

const int P = 1000000007;

struct three {
   int a,b,c;
   three (int a, int b, int c) : a(a), b(b), c(c) {}
};

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int n,k;
   cin >> n >> k;
   int a = 0, b = 0;
   REP(i,n) {
      int x;
      cin >> x;
      if (x == 50)
         ++a;
      else
         ++b;
   }
   int dst[a + 1][b + 1][2];
   REP(i,a + 1) REP(j,b + 1) REP(k,2)
      dst[i][j][k] = -1;
   dst[0][0][1] = 0;
   queue<three> S;
   vector<three> M;
   S.push(three(0,0,1));
   while (!S.empty()) {
      three nxt = S.front(); 
      S.pop();
      M.PB(nxt);
      int side = nxt.c, cur_a = nxt.a, cur_b = nxt.b;
      if (side == 0) {
         for (int i = 0; i <= cur_a && i * 50 <= k; ++i)
            for (int j = 0; j <= cur_b && i * 50 + j * 100 <= k; ++j)
               if (i + j > 0) {
                  three nw(cur_a - i, cur_b - j, 1);
                  if (dst[nw.a][nw.b][nw.c] == -1) {
                     dst[nw.a][nw.b][nw.c] = dst[cur_a][cur_b][side] + 1;
                     S.push(nw);
                  }
               }
      }
      else {
         for (int i = 0; i <= a - cur_a && i * 50 <= k; ++i)
            for (int j = 0; j <= b - cur_b && i * 50 + j * 100 <= k; ++j) 
               if (i + j > 0) {
                  three nw(cur_a + i, cur_b + j, 0);
                  if (dst[nw.a][nw.b][nw.c] == -1) {
                     dst[nw.a][nw.b][nw.c] = dst[cur_a][cur_b][side] + 1;
                     S.push(nw);
                  } 
               }
      }
   }

   cout << dst[a][b][0] << endl;

   int cnt[a + 1][b + 1][2];
   REP(i,a + 1) REP(j,b + 1) REP(k,2)
      cnt[i][j][k] = 0;
   cnt[0][0][1] = 1;

   int m = max(a,b) + 1;
   int newt[m][m];
   REP(i,m) REP(j,m)
      newt[i][j] = 0;
   REP(i,m)
      newt[i][0] = 1;
   FOR(i,1, m - 1) FOR(j,1,i)
      newt[i][j] = (newt[i - 1][j - 1] + newt[i - 1][j]) % P;
  //REP(i,m) REP(j,m)
  // cout << i << " " << j << " " << newt[i][j] << endl;
   

   FORE(it,M) {
      // UGLY COPY PASTE HERE !!
      three nxt = *it; 
      int side = nxt.c, cur_a = nxt.a, cur_b = nxt.b;
      if (side == 0) {
         for (int i = 0; i <= cur_a && i * 50 <= k; ++i)
            for (int j = 0; j <= cur_b && i * 50 + j * 100 <= k; ++j)
               if (i + j > 0) {
                  three nw(cur_a - i, cur_b - j, 1);
                  if (dst[nw.a][nw.b][nw.c] == dst[cur_a][cur_b][side] + 1) {
                     int mult = (LL(newt[cur_a][i]) * newt[cur_b][j]) % P;
                     int add = (LL(mult) * cnt[cur_a][cur_b][side]) % P;
                     cnt[nw.a][nw.b][nw.c] = (cnt[nw.a][nw.b][nw.c] + add) % P;
                  }
               }
      }
      else {
         for (int i = 0; i <= a - cur_a && i * 50 <= k; ++i)
            for (int j = 0; j <= b - cur_b && i * 50 + j * 100 <= k; ++j) 
               if (i + j > 0) {
                  three nw(cur_a + i, cur_b + j, 0);
                  if (dst[nw.a][nw.b][nw.c] == dst[cur_a][cur_b][side] + 1) { 
                     int mult = (LL(newt[a - cur_a][i]) * newt[b - cur_b][j]) % P;
                     int add = (LL(mult) * cnt[cur_a][cur_b][side]) % P;
                     cnt[nw.a][nw.b][nw.c] = (cnt[nw.a][nw.b][nw.c] + add) % P;
                  }
               }
      }

   }

   cout << cnt[a][b][0] << endl;



   return 0;
}	
