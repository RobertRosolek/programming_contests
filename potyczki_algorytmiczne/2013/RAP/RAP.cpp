#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> PII;
typedef double LD;
typedef unsigned int UI;
typedef vector<UI> VU;
typedef pair<UI, int> PUI;

/* CHECKLIST 
 * 1) long longs 
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

const int DBG = 0;

const UI INF = UI(1e9) * 2 + 10;

int smallestBin(int n) {
   int rs = 1;
   while (rs < n)
      rs *= 2;
   return rs;
}

const int SINF = int(1e6);

class MinSegmentTree {
   int M;
   VI w, U;
   VI infty;

   public:
      MinSegmentTree(int n) : M(smallestBin(n)), w(VI (2 * smallestBin(n), 0)), U( VI( 2 * smallestBin(n), SINF)), infty(VI(smallestBin(n), 1)) {
         for (int a = 0; a < M; ++a)
            w[M + a] = SINF;
      }
      void rem_infty(int a) {
         if (infty[a]) {
            int va = M + a;
            w[va] -= SINF;
            U[va] = w[va];
            va >>= 1;
            while (va > 0) {
               U[va] = w[va] + min(U[va<<1], U[(va<<1) | 1]);
               va >>= 1;
            }
            infty[a] = 0;
         }
      }
      bool empty(int a) {
         if (!infty[a])
            return false;
         int va = M + a;
         int sum_a = 0;
         for (int v = va >> 1; v > 0; v >>= 1)
            sum_a += w[v];
         int res = U[va] + sum_a;
         return res == SINF;
      }
      void insert(int a, int b, int c) {
         int va = M + a, vb = M + b;
         w[va] += c;
         U[va] = w[va];
         if ( va != vb) {
            w[vb] += c;
            U[vb] = w[vb];
         }
         while ( (va >> 1) != (vb >> 1)) {
            if ( (va & 1) == 0) {
               w[va ^ 1] += c;
               U[va ^ 1] += c;
            }
            if ( (vb & 1) == 1) {
               w[vb ^ 1] += c;
               U[vb ^ 1] += c;
            }
            va >>= 1;
            vb >>= 1;
            U[va] = w[va] + min(U[va<<1], U[(va<<1) | 1]);
            U[vb] = w[vb] + min(U[vb<<1], U[(vb<<1) | 1]);
         }
         va >>= 1;
         while (va > 0) {
            U[va] = w[va] + min(U[va<<1], U[(va<<1) | 1]);
            va >>= 1;
         }
      }

      int query(int a, int b) {
         int va = M + a, vb = M + b;
         int sum_a = 0, sum_b = 0;
         for (int v = va >> 1; v > 0; v >>= 1)
            sum_a += w[v];
         for (int v = vb >> 1; v > 0; v >>= 1)
            sum_b += w[v];
         int res = min(U[va] + sum_a, U[vb] + sum_b);
         while ( (va >> 1) != (vb >> 1) ) {
            if ( (va & 1) == 0) 
               res = min(res, U[va ^ 1] + sum_a);
            if ( (vb & 1) == 1)
               res = min(res, U[vb ^ 1] + sum_b);
            va >>= 1;
            vb >>= 1;
            sum_a -= w[va];
            sum_b -= w[vb];
         }
         //assert(res >= 0);
         return res;
      }
};

class SegmentTree {
   int M;
   vector<PUI> w;

   public:
      SegmentTree() : M(0), w(vector<PUI>()) {}
      SegmentTree(VU& a) : M(smallestBin((int) a.size())), w(vector<PUI>(2 * smallestBin((int) a.size()), make_pair(INF, -1))) { 
         int n = (int) a.size();
         for (int i = 0; i < n; ++i)
            w[M + i] = make_pair(a[i], i);
         for (int i = M - 1; i > 0; --i)
            w[i] = min(w[i<<1], w[(i<<1) | 1]);
      }
      void insert(int x, int val) {
         int v = M + x;
         w[v] = make_pair(val, x);
         while (v != 1) {
            v >>= 1;
            w[v] = min(w[v<<1], w[(v<<1) | 1]);
         }
      }
      int query(int a, int b) {
         int va = M + a, vb = M + b;
         PUI res = min(w[va], w[vb]);
         while ( (va >> 1) != (vb >> 1) ) {
            if ( (va & 1) == 0)
               res = min(res, w[va ^ 1]);
            if ( (vb & 1) == 1)
               res = min(res, w[vb ^ 1]);
            va >>= 1;
            vb >>= 1;
         }
         //assert(res.second != -1);
         return res.second;
      }
};


int main() {
   int n, k;
   scanf("%d %d", &n, &k);
   vector<VU> a(2, VU(n + 1));
   for (int q = 0; q < 2; ++q)
      for (int i = 0; i < n; ++i)
         scanf("%u", &a[q][i]);
   a[0][n] = a[1][n] = INF;
   //k = n;
   ++n;

   vector<SegmentTree> t(2);
   for (int q = 0; q < 2; ++q)
      t[q] = SegmentTree(a[q]);

   
   VI left_range(n, -1), right_range(n, -1);

   priority_queue<PUI, vector<PUI>, greater<PUI> > Q;

   for (int left = 0; left < n;) {
      int pos = t[1].query(left, n - 1);
      left_range[pos] = left;
      right_range[pos] = pos;
      UI best_value = a[0][ t[0].query(left, pos) ];
      Q.push(make_pair(a[1][pos] + best_value, pos));
      left = pos + 1;
   }

   MinSegmentTree depths(n);

   LL res = 0;
   while (k > 0) {
      assert(!Q.empty());
      UI value = Q.top().first;
      int pos = Q.top().second;
      Q.pop();
      // expired record in Q
      if (a[1][pos] == INF)
         continue;
      res += value;
      --k;
      int pair_pos = t[0].query(left_range[pos], right_range[pos]);
      assert(a[0][pair_pos] != INF && a[0][pair_pos] + a[1][pos] == value);

      depths.rem_infty(pair_pos);
      depths.rem_infty(pos);
      
      if (pair_pos < pos) 
         depths.insert(pair_pos, pos - 1, 1);
      else if (pos < pair_pos) {
         depths.insert(pos, pair_pos - 1, -1);
         //assert(depths.query(pos, pair_pos) >= 0);
      }

      a[0][pair_pos] = a[1][pos] = INF;
      t[0].insert(pair_pos, INF + 10);
      t[1].insert(pos, INF + 10);

      int left = left_range[pos];
      while (left <= right_range[pos]) {
         int new_pos = t[1].query(left, n - 1); 
         if (new_pos > right_range[pos]) {
            //assert(left_range[new_pos] != -1);
            left_range[new_pos] = left;
            UI best_value = a[0][ t[0].query(left, right_range[new_pos]) ];
            Q.push(make_pair(a[1][new_pos] + best_value, new_pos));
            break;
         }
         else {
            //assert(left_range[new_pos] == -1);
            left_range[new_pos] = left;

            //assert(depths.query(new_pos, new_pos) != 0);
            if (depths.query(new_pos, right_range[pos]) != 0 || depths.empty(new_pos) )
               right_range[new_pos] = new_pos;
            else {
               // binary search for closest zero depth to the right of new_pos
               int l = new_pos, r = right_range[pos];
               while (l < r) {
                  int s = (l + r) >> 1;
                  if (depths.query(new_pos, s) == 0)
                     r = s;
                  else
                     l = s + 1;
               }
               right_range[new_pos] = l;
            }
            left = right_range[new_pos] + 1;
            UI best_value = a[0][ t[0].query(left_range[new_pos], right_range[new_pos]) ];
            Q.push(make_pair(a[1][new_pos] + best_value, new_pos));
         }
      }
   }
   cout << res << endl;

   return 0;
}	
