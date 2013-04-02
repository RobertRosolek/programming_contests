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


const int DBG = 0, INF = 1000000000;

const int MAXN = 1000;


struct Graph {

  int N;
  VI V[MAXN];

  int przepust[MAXN][MAXN], dst[MAXN], q[MAXN];
  vector<int>::iterator pocz[MAXN];


  Graph(int N) : N(N) {
    REP(i,N) REP(j,N)
      przepust[i][j] = 0;
  }


  void addEdge(int a, int b, int d = INF) {
    przepust[a][b] += d;
    V[a].PB(b);
    V[b].PB(a);
  }


  int flowBfs(int s, int t) {
    REP(i,N)
      dst[i] = -1;
    dst[s] = 0;
    int left = 0, right = 0;
    q[right++] = s;
    while (left < right) {
      int k = q[left++];
      FORE(it,V[k])
        if (przepust[k][*it] > 0 && dst[*it] == -1) {
          dst[*it] = dst[k] + 1;
          q[right++] = *it;
        }
    }
    return dst[t] != -1;
  }

  int flowDfs(int x,int t,int minimum){
    int res = 0;
    if (x == t || minimum == 0) return minimum;
    for(vector<int>::iterator &it = pocz[x]; it != V[x].end(); ++it){
      if (dst[x] + 1 == dst[*it] && przepust[x][*it] > 0) {
        int y = flowDfs(*it, t, min(minimum, przepust[x][*it]));
        przepust[x][*it] -= y; 
        przepust[*it][x] += y;
        minimum -= y; 
        res += y;
        if (minimum == 0) 
          break;
      }
    }
    return res;
  }
  
  int maxFlow(int s, int t){
    int res = 0;
    while (flowBfs(s,t)){
     REP(i,N) 
       pocz[i]=V[i].begin();
     res += flowDfs(s,t,INF);
    }
    return res;
  }


  
};

int main() {
  ios_base::sync_with_stdio(0);

  return 0;
}
