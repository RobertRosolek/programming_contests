#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
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

VI set_cycles(int inc, int mod, int step) {
	VI cycle = VI(mod, -1);
	int start = (inc == 1) ? 0 : (mod - 1);
	for (int i = start, cnt = 0; cnt < mod; i += inc, ++cnt) 
		if (cycle[i] == -1) {
			int c = i;
			while (cycle[c] == -1) {
				cycle[c] = i;
				c = (c + step) % mod;
			}
		}
	return cycle;
}

class FruitTrees {
	public:
		int maxDist(int apple, int kiwi, int grape) {
			int res = 0;
			if (kiwi > apple)
				swap(kiwi, apple);
			if (grape > apple)
				swap(grape, apple);
			if (grape > kiwi)
				swap(grape, kiwi);
			VI kiwi_in_apple_up = set_cycles(1, apple, kiwi),
			   kiwi_in_apple_down = set_cycles(-1, apple, kiwi),
			   grape_in_apple_up = set_cycles(1, apple, grape),
			   grape_in_apple_down = set_cycles(-1, apple, grape),
			   grape_in_kiwi_up = set_cycles(1, kiwi, grape),
			   grape_in_kiwi_down = set_cycles(-1, kiwi, grape);

			REP(a,kiwi) REP(b,grape) if (a > 0 && b > 0) {
				VI v;
				v.reserve(6);
				v.PB(kiwi_in_apple_up[a]);
				v.PB(apple - kiwi_in_apple_down[a]);
				v.PB(grape_in_apple_up[b]);
				v.PB(apple - grape_in_apple_down[b]);
				int st = (b >= a) ? (b - a) % kiwi : (b - (a - kiwi)) % kiwi;
				v.PB(grape_in_kiwi_up[st]);
				v.PB(kiwi - grape_in_kiwi_down[st]);
				int cur = 20000;
				FORE(it, v)
					cur = min(cur, *it);
				res = max(res, cur);
			}

			return res;
		}
};
