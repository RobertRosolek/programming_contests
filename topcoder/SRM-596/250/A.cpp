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

int len(int x) {
	int k = 0;
	while (x > 0) {
		x /= 2;
		++k;
	}
	return k;
}

class IncrementAndDoubling {
public:
   int getMin(vector <int> desiredArray) {
   	int bits = 0, mlen = 0;
   	for (int x: desiredArray) {
   		bits += __builtin_popcount(x);
   		mlen = max(mlen, len(x) - 1);
   	}
   	return mlen + bits;
   }
};
