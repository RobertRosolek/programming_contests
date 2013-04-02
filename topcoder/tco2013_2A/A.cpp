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

string a,b;
int n;

/*
 *  Status: ACC
 *  Description: semi greedy solution - after choosing first index 
 *               there is at most one branch later */

string walk(int pos, string &left, string &right) {
	if (pos == n)
		return left + right;
	char mx = 'a';
	FOR(i,pos, n - 1)
		mx = max(mx, a[i]);
	if (mx < right[0])
		return left + right;
	if (mx == right[0]) {
		char nxt = right[0];
		FORE(it,right)
			if (*it != right[0]) {
				nxt = *it;
				break;
			}
		if (nxt == right[0]) {
			pair<char,char> p = MP('a','a');
			FOR(i,pos,n - 1)
				p = max(p, MP(a[i], b[i]));
			if (p > MP(mx,mx)) 
				FOR(i,pos,n-1)
					if (MP(a[i],b[i]) == p) {
						left += a[i];
						right += b[i];
						return walk(i + 1,left, right);
					}
			FOR(i,pos,n - 1)
				if (a[i] == mx) {
					if (MP(a[i],b[i]) == p) {
						left += a[i];
						right += b[i];
						return walk(i + 1, left, right);
					}
					else {
						string mleft = left, mright = right;
						string res2 = walk(i + 1, mleft, mright);
						left += a[i];
						right += b[i];
						return max(res2, walk(i + 1, left, right));
					}
				}
		}
		if (nxt > mx)
			return left + right;
	}
	int last = -1;
	FOR(i,pos, n - 1)
		if (a[i] == mx) {
			left += a[i];
			right += b[i];
			last = i;
		}
	assert(last != -1);
	return walk(last + 1, left, right);
}

class TheLargestString {
	public:
		string find(string s, string t) {
			a = s, b = t;
			n = a.size();
			string res = "";
			REP(i,n) {
				string left,right;
				left += a[i];
				right += b[i];
				res = max(res, walk(i + 1, left, right));
			}
			return res;
		}
};
