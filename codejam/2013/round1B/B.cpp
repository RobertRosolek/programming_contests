#include <stdio.h>      
#include <ctype.h>
#include <math.h>

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
 * 1) long longs */

const int DBG = 0, INF = int(1e9);

int n,x,y;

int all, good;

void walk(int step, int X, int Y, vector<PII> v) {
   if (step < n) {
      int left = 0, right = 0, down = 0;
      for (vector<PII>::iterator it = v.begin(); it != v.end(); ++it) 
         if (it->first == X - 1 && it->second == Y - 1) 
            ++left;
         else if (it->first == X + 1 && it->second == Y - 1)
            ++right;
         else if (it->first == X && it->second == Y - 2)
            ++down;
      if ((left && right) || Y == 0) {
         v.push_back(make_pair(X, Y));
         walk(step + 1, 0, 20, v);
      }
      else if (left) 
         walk(step, X + 1, Y - 1, v);
      else if (right)
         walk(step, X - 1, Y - 1, v);
      else if (down) {
         walk(step, X + 1, Y - 1, v);
         walk(step, X - 1, Y - 1, v);
      }
      else
         walk(step, X, Y - 1, v);
   }
   else {
      bool ok = false;
      ++all;
      for (vector<PII>::const_iterator it = v.begin(); it != v.end(); ++it) 
         if (*it == make_pair(x,y))
            ok = true;
      /*for (vector<PII>::const_iterator it = v.begin(); it != v.end(); ++it) 
         cout << it->first << "-" << it->second << " ";      
      cout << endl;*/
      if (ok)
         ++good;
   }
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int T;
   cin >> T;
   for (int q = 0; q < T; ++q) {
      cin >> n >> x >> y;
      all = good = 0;
      walk(0, 0, 20, vector<PII>());
      LD res = LD(good) / LD(all);
      cout << "Case #" << q + 1 << ": " << setprecision(10) << res << endl;
   }

   return 0;
}	
