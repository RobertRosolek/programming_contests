#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int DBG = 0, INF = int(1e9);

typedef long long LL;

bool isPrime(LL n) {
   if (n <= 1) return false;
   for (LL i = 2; i * i <= n; ++i) if (n % i == 0) return false;
   return true;
}

LL gcd(LL m, LL n) {
   return m == 0 ? n : gcd(n % m, m);
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);
   int t; cin >> t;
   while (t--) {
      LL n; cin >> n;
      LL p = n; while (!isPrime(p)) --p;
      LL q = n + 1; while (!isPrime(q)) ++q;
      LL den = 2 * p * q;
      LL nom = p * q - 2 * q + (n - p + 1) * 2;
      LL g = gcd(den, nom);
      cout << nom / g << "/" << den / g << endl;
   }
   return 0;
}

