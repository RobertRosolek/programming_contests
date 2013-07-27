// {{{ Boilerplate Code <--------------------------------------------------
// vim:filetype=cpp:foldmethod=marker:foldmarker={{{,}}}

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

#define FOR(I,A,B) for(int I = (A); I < (B); ++I)
#define REP(I,N)   FOR(I,0,N)
#define ALL(A)     (A).begin(), (A).end()

using namespace std;

// }}}

const double EPS = 1e-8;

bool isEq(double a, double b) {
   return -EPS <= a - b && a - b <= EPS;
}

int sols(vector<int> Y, double y) {
   int rs = isEq(Y[0], y);
   int n = Y.size();
   for (int i = 1; i < n; ++i)
      rs += (Y[i - 1] < y && y <= Y[i]) || (Y[i - 1] > y && y >= Y[i]);
   return rs;
}

class PiecewiseLinearFunction {
public:
   int maximumSolutions(vector <int> Y) {
      vector<double> vals;
      int n = Y.size();
      for (int i = 1; i < n; ++i)
         if (Y[i - 1] == Y[i])
            return -1;
      vals.push_back(Y[0]);
      for (int i = 1; i < n; ++i)
         vals.push_back(Y[i]);
      vector<int> W = Y;
      sort(W.begin(), W.end());
      for (int i = 1; i < n; ++i)
         vals.push_back( (double(W[i - 1]) + W[i]) / 2);
      int rs = 1;
      for (vector<double>::iterator it = vals.begin(); it != vals.end(); ++it)
         rs = max(rs, sols(Y, *it));
      return rs;
   }
};


// Edited by VimCoder 0.3.5
// http://github.com/chazmcgarvey/vimcoder
