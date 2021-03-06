
// {{{ Boilerplate Code <--------------------------------------------------
// vim:filetype=cpp:foldmethod=marker:foldmarker={{{,}}}

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

// }}}

typedef long long LL;

const LL P = int(1e9) + 7;

LL mob(int n) {
   int odd = 0;
   for (int i = 2; i * i <= n; ++i) {
      if (n % i == 0) {
         if (n % (i * i) == 0) return 0;
         n /= i;
         ++odd;
      }
   }
   if (n > 1) ++odd;
   return odd % 2 == 1 ? -1 : 1;
}

LL powk(int k, int n) {
   if (n == 0) return 1;
   LL b = powk(k, n / 2);
   b = (b * b) % P;
   if (n % 2 == 1) return (b * k) % P;
   return b;
}

LL prim(int k, int div) {
   LL words = 0;
   for (int d = 1; d * d <= div; ++d) if (div % d == 0) {
      words = (words + mob(div / d) * powk(k, d)) % P;
      if (d != div / d) words = (words + mob(d) * powk(k, div / d)) % P;
   }
   return (words * div) % P;
}

class PairsOfStrings {
public:
   int getNumber(int n, int k) {
      LL res = 0;
      res += k;
      for (int i = 2; i * i <= n; ++i) if (n % i == 0) {
         res = (res + prim(k, i)) % P;
         if (i != n / i) res = (res + prim(k, n / i)) % P;
      }
      if (n != 1) res = (res + prim(k, n)) % P;
      if (res < 0) res += P;
      return res;
   }
};

