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

const int B = 60;

class BitwiseAnd {
public:
	vector<long long> lexSmallest(vector<long long> subset, int N) {
   		vector<long long> res = subset;
   		int m = subset.size();

   		set<int> fb; for (int i = 0; i < B; ++i) fb.insert(i);
   		vector<set<int>> av(N);
   		for (int i = 0; i < m; ++i) for (int j = 0; j < B; ++j) if (subset[i]&(1<<j)) { fb.erase(j); av[i].insert(j); }

   		for (int a = 0; a < m; ++a) for (int b = 0; b < m; ++b) if (a != b) {
   			int nd = subset[a] & subset[b];
   			if (nd == 0) return vector<long long>();
   			for (int j = 0; j < B; ++j) if (nd & (1<<j)) av[a].erase(j), av[b].erase(j);
   		}
   		for (auto x: subset) for (auto y: subset) if (x != y) for (auto z: subset) if (x != z && y != z && (x&y&z) != 0) return vector<long long>();
   		for (; m < N; ++m) {
   			int k = 0;
   			for (int i = 0; i < m; ++i) {
   				if (av[i].empty()) return vector<long long>();
   				int j = *av[i].begin(); av[i].erase(av[i].begin());
   				k |= 1<<j;
   			}
   			int rem = N -m - 1;
   			if (fb.size() < rem) return vector<long long>();
   			for (int q = 0; q < rem; ++q) {
   				int j = *fb.begin(); fb.erase(fb.begin());
   				av[m].insert(j);
   				k |= 1<<j;
   			}
   			res.push_back(k);
   		}

   		sort(res.begin(), res.end());
   		return res;
	}
};
