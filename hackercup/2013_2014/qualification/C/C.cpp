#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

const int MAXK = 100;

struct prob {
   LL x;
   explicit prob(LL x = -1) : x(x) {}
};

const prob ONE = prob(1e9);

prob operator*(prob p1, prob p2) {
   return prob((p1.x * p2.x) / ONE.x);
}

prob& operator+=(prob& p1, prob p2) {
   p1.x = min(ONE.x, p1.x + p2.x);
   return p1;
}

prob operator+(prob p1, prob p2) {
   prob res = p1;
   return res += p2;
}

prob operator-(prob p1, prob p2) {
   return prob(max(0LL, p1.x - p2.x));
}

bool operator<(const prob& p1, const prob& p2) {
   return p1.x < p2.x;
}

bool operator==(const prob& p1, const prob& p2) {
   return ! (p1 < p2 || p2 < p1);
}

istream& operator>>(istream& stream, prob& p) {
   int integral, fractional;
   char dot;
   stream >> integral >> dot >> fractional;
   assert(integral == 0 || integral == 1);
   assert(dot == '.');
   assert(0 <= fractional && fractional < 1000);
   p.x = integral * ONE.x + fractional * (ONE.x / 1000);
   return stream;
}

ostream& operator<<(ostream& stream, prob p) {
   auto toString = [] (LL x) { stringstream ss; ss << x; string p; ss >> p; return p; };
   int integral = p.x / ONE.x;
   int fractional = (p.x % ONE.x) / 100;
   if (fractional % 10 < 5) fractional /= 10;
   else fractional = fractional / 10 + 1;
   if (fractional >= 1e6) {
      assert(integral == 0);
      integral = 1;
      assert(fractional == 1e6);
      fractional = 0;
   }
   auto leadZeros = [] (string s) { while (s.size() != 6) s = "0" + s; return s; };
   return stream << toString(integral) << "." << leadZeros(toString(fractional));
}

struct Solve {
   prob winSunnyProb, winRainyProb, incSunny, incSunnyProb, decSunny, decSunnyProb;
   map<prob,prob> dp[MAXK + 1][MAXK + 1];
   prob solve(int toWin, int toLose, prob sunnyProb) {
      //cerr << toWin << " " << toLose << " " << sunnyProb.x << endl;
      if (toWin == 0) return ONE;
      if (toLose == 0) return prob(0);
      prob res = dp[toWin][toLose][sunnyProb];
      if (!(res== prob(-1))) return res;
      res = prob(0);
      prob winProb[2] = {winRainyProb, winSunnyProb}; // depends on whether it's sunny or rainy
      struct changeProb {
         prob change, p;
         bool inc;
         changeProb(prob change, prob p, bool inc) : change(change), p(p), inc(inc) {}
      };
      changeProb changeSunnyProb[2] = // depends on whether we win or lose
      { changeProb(decSunny, decSunnyProb, false), changeProb(incSunny, incSunnyProb, true) };
      for (int isSunny = 0; isSunny <= 1; ++isSunny) for (int win = 0; win <= 1; ++win) for (int change = 0; change <= 1; ++change) {
         prob newProb = sunnyProb;
         if (change == 1) {
            if (changeSunnyProb[win].inc) newProb += changeSunnyProb[win].change;
            else newProb = newProb - changeSunnyProb[win].change;
         }
         auto setProb = [] (bool plus, prob p) { return plus ? p : ONE - p; };
         prob weatherProb = setProb(isSunny, sunnyProb),
              resultProb = setProb(win, winProb[isSunny]),
              sunnyChangeProb = setProb(change, changeSunnyProb[win].p);
         res += weatherProb * resultProb * sunnyChangeProb * solve(toWin - win, toLose - (1 - win), newProb);
      }
      return dp[toWin][toLose][sunnyProb] = res;
   }
   prob result() {
      prob initialSunnyProb;
      int k;
      cin >> k >> winSunnyProb >> winRainyProb >> initialSunnyProb >> incSunny >> incSunnyProb >> decSunny >> decSunnyProb;
      return solve(k, k, initialSunnyProb);
   }
};

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int T; cin >> T;
   for (int q = 0; q < T; ++q) cout << "Case #" << (q + 1) << ": " << Solve().result() << endl;

   return 0;
}

