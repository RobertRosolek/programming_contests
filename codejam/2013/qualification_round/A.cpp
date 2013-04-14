#include <stdio.h>      
#include <ctype.h>
#include <math.h>

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
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

/* CHECKLIST 
 * 1) long longs */

const int DBG = 0, INF = int(1e9);

string solve() {
   vector<string> board(10, "");
   // board[0] - board[3] - rows
   REP(i,4)
      cin >> board[i];
   // board[4] - board[7] - columns
   REP(i,4) REP(j,4)
      board[4 + i] += board[j][i];

   // board[8] - main diagonal
   board[8] = "";
   REP(i,4)
      board[8] += board[i][i];

   // board[9] - second diagonal
   board[9] = "";
   REP(i,4)
      board[9] += board[i][3 - i];

   string symbols = "XO";
   for (const char& symbol: symbols)  
      REP(i,10)
         if (count_if(board[i].begin(), board[i].end(), [symbol](char c) {return c == symbol || c == 'T';}) == 4)
            return string("") + symbol + " won";

   REP(i,4)
      if (count(board[i].begin(), board[i].end(), '.') > 0)
         return "Game has not completed";

   return "Draw";
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int T;
   cin >> T;

   REP(q,T) {
      string res = solve();
      printf("Case #%d: %s\n", q + 1, res.c_str());
   }

   return 0;
}	
