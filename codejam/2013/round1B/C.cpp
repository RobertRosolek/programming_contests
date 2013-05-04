#include <stdio.h>      
#include <ctype.h>
#include <math.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
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
 * 1) long longs */

const int DBG = 0, INF = int(1e9);

ifstream fin("garbled_email_dictionary.txt");

string s;
int n;
vector<string> v;

map<string, vector<string> > m[6];

const int MAXN = 4000;  
int dp[5][MAXN];

int walk(int ch, int k) {
   if (k == n)
      return 0;
   if (dp[ch][k] == -1) {
      dp[ch][k] = INF;
      /*for (vector<string>::iterator it = v.begin(); it != v.end(); ++it) 
         if (it->size() <= n - k) {
            int m = it->size(), nx = ch, cnt = 0;
            bool ok = true;
            for (int i = 0; i < m; ++i)
               if (s[k + i] != (*it)[i]) {
                  if (i < nx) {
                     ok = false;
                     break;
                  }
                  else {
                     ++cnt;
                     nx = max(nx, i + 5);
                  }
               }
            if (!ok)
               continue;
            dp[ch][k] = min(dp[ch][k], cnt + walk(max(nx - m,0), k + m));
         }*/
      int sz = min(5, n - k);
      for (int q = 1; q <= sz; ++q) {
         for (int j = 0; j < q; ++j) {
            string c = "";
            for (int p = 0; p < q; ++p)
               if (p != j)
                  c += s[k + p];
            sort(c.begin(), c.end());
            vector<string>::iterator it = m[q][c].begin(), ite = m[q][c].end();
            for(; it != ite; ++it) {
               int m = it->size(), nx = ch, cnt = 0;
               bool ok = true;
               for (int i = 0; i < m; ++i)
                  if (s[k + i] != (*it)[i]) {
                     if (i < nx) {
                        ok = false;
                        break;
                     }
                     else {
                        ++cnt;
                        nx = max(nx, i + 5);
                     }
                  }
               if (!ok)
                  continue;
               dp[ch][k] = min(dp[ch][k], cnt + walk(max(nx - m,0), k + m));
            }
         }
      }
   }
   //cout << ch << " " << k << " " << dp[ch][k] << endl;
   return dp[ch][k];
}

int main(){
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int M = 521196;
   v.resize(M);
   for (int i = 0; i < M; ++i) {
      fin >> v[i];
      int s = v[i].size();
      int k = min(s, 5);
      for (int j = 0; j < k; ++j) {
         string c = "";
         for (int q = 0; q < k; ++q)
            if (q != j)
               c += v[i][q];
         sort(c.begin(), c.end());
         m[k][c].push_back(v[i]);
      }
   }

   int T;
   cin >> T;

   for (int q = 0; q < T; ++q) {
      cin >> s;
      n = s.size();
      for (int i = 0; i < 5; ++i) 
         for (int j = 0; j < n; ++j)
            dp[i][j] = -1;
      int res = walk(0,0);
      assert(res != INF);
      printf("Case #%d: %d\n", q + 1, res);
   }

   return 0;
}	
