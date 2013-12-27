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

typedef long long LL;

using namespace std;

const int MAXN = 50;

int dp[MAXN + 1][MAXN + 1];

int bigCom(vector<LL>& A, vector<LL>& B) {

	int a = A.size(), b = B.size();

	for (int i = 0; i <= a; ++i)
		for (int j = 0; j <= b; ++j)
			dp[i][j] = 0;

	for (int i = 1; i <= a; ++i)
		for (int j = 1; j <= b; ++j)
			if (A[i - 1] == B[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
	return dp[a][b];
}

class AstronomicalRecords {
public:
   int minimalPlanets(vector<int> A, vector<int> B) {
   	  int a = A.size(), b = B.size();
   	  int res = a + b;
   	  for (int i = 0; i < a; ++i)
   	  	for (int j = 0; j < b; ++j) {
   	  		vector<LL> A2(a), B2(b);
   	  		for (int x = 0; x < a; ++x)
   	  			A2[x] = A[x] * LL(B[j]);
   	  		for (int x = 0; x < b; ++x)
   	  			B2[x] = B[x] * LL(A[i]);
   	  		 res = min(res, a + b - bigCom(A2, B2));
   	  	}
      return res;
   }
};
