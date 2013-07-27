
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
#include <cassert>

class History {

typedef pair<int, int> PII;
static const int INF = 1e8;

int n;
vector<int> dyn[26];

pair<PII, PII> decode(const string& x) {
   assert(x.size() == 5 && x[2] == '-');
   return make_pair( make_pair(x[0] - 'A', x[1]  - '0'), make_pair(x[3] - 'A', x[4] - '0'));
}

bool solvable(vector<pair<PII, PII> > bats) {
   int bound[n][n];
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         bound[i][j] = INF;
   for (vector<pair<PII, PII> >::iterator it = bats.begin(); it != bats.end(); ++it) {
      int dynastyA = it->first.first, dynastyB = it->second.first,
         kingA = it->first.second, kingB = it->second.second;
      int begA = dyn[dynastyA][kingA], endA = dyn[dynastyA][kingA + 1] - 1,
         begB = dyn[dynastyB][kingB], endB = dyn[dynastyB][kingB + 1] - 1;
      bound[dynastyA][dynastyB] = min(bound[dynastyA][dynastyB], endB - begA);
      bound[dynastyB][dynastyA] = min(bound[dynastyB][dynastyA], endA - begB);
   }

   bool change = true;
   while (change) {
      change = false;
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n;  ++j)
            if (bound[i][j] + bound[j][i] < 0)
               return false;
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
               if (bound[i][j] + bound[j][k] < bound[i][k]) {
                  change = true;
                  bound[i][k] = bound[i][j] + bound[j][k];
               }
   }

   return true;
}

public:
   string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries) {
      n = dynasties.size();
      for (int i = 0; i < n; ++i) {
         stringstream ss(dynasties[i]);
         int x;
         while (ss >> x)
            dyn[i].push_back(x);
      }
      vector<pair<PII, PII> > bats;
      string s = "";
      for (vector<string>::iterator it = battles.begin(); it != battles.end(); ++it)
         s += *it;
      stringstream ss(s);
      string x;
      while (ss >> x)
         bats.push_back(decode(x));
      string res = "";
      for (vector<string>::iterator it = queries.begin(); it != queries.end(); ++it) {
         bats.push_back(decode(*it));
         res += solvable(bats) ? 'Y' : 'N';
         bats.pop_back();
      }
      return res;
   }
};

