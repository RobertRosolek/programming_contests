#include <cstdio>
#include <iostream>
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

/* CHECKLIST 
 * 1) long longs 
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

const int DBG = 0, INF = int(1e9);

inline int smallestBin(int n) {
   int res = 1;
   while (res < n)
      res *= 2;
   return res;
}

class SegmentTreeOne {
   int M;
   VI w;

   public:
      SegmentTreeOne(int n) : M(smallestBin(n)), w(VI(2 * smallestBin(n))) {}

      int query(int x) {
         int v = M + x;
         int res = w[v];
         while (v != 1) {
            v /= 2;
            res += w[v];
         }
         return res;
      }

      void insert(int a, int b, int val) {
         int va = M + a, vb = M + b;
         w[va] += val;
         if (va != vb)
            w[vb] += val;
         while (va / 2 != vb / 2) {
            if (va % 2 == 0)
               w[va + 1] += val;
            if (vb % 2 == 1)
               w[vb - 1] += val;
            va /= 2;
            vb /= 2;
         }
      }
};

// two dimensional segment tree
class SegmentTree {
   int M;
   vector<map<int,PII> > T;

   void debug() {
      cout << M << endl;
      cout << T.size() << endl;
   }

   void insert2(map<int, PII> &w, int x, int y, int val) {
      int v = M + y;
      w[v] = make_pair(INF - val, x);
      while (v != 1) {
         v /= 2;
         w[v] = max(w[2 * v], w[2 * v + 1]);
      }
   }

   PII query2(map<int, PII> &w, int ya, int yb) {
      int va = M + ya, vb = M + yb;
      PII res = w[va];
      if (va != vb)
         res = max(res, w[vb]);
      while (va / 2 != vb / 2) {
         if (va % 2 == 0)
            res = max(res, w[va + 1]);
         if (vb % 2 == 1)
            res = max(res, w[vb - 1]);
         va /= 2;
         vb /= 2;
      }
      return res;
   }

   public:
      // we will be given points from range [0..n-1] x [0..n-1]
      SegmentTree(int n) : M(smallestBin(n)), T(vector<map<int,PII> >(2 * smallestBin(n))) {}

      void insert(int x, int y, int val) {
         int v = M + x;
         insert2(T[v], x, y, val);
         while (v != 1) {
            v /= 2;
            insert2(T[v], x, y, val);
         }
      }

      int query(int xa, int xb, int ya, int yb) {
         PII res = make_pair(1,-1);
         int va = M + xa, vb = M + xb;
         res = max(res, query2(T[va], ya, yb));
         if (va != vb) 
            res = max(res, query2(T[vb], ya, yb));
         while (va / 2 != vb / 2) {
            if (va % 2 == 0)
               res = max(res, query2(T[va + 1], ya, yb));
            if (vb % 2 == 1) 
               res = max(res, query2(T[vb - 1], ya, yb));
            va /= 2;
            vb /= 2;
         }
         if (res.second == -1) 
            cout << xa << " " << xb << " " << ya << " " << yb << endl;
         assert(res.second != -1);
         return res.second;
      }
};

// rev - will allow later for unscaling
void scale(vector<VI>& A, int n, VI &rev) {
   VI u = A[0];
   sort(u.begin(), u.end());
   vector<PII> v;
   v.reserve(n);
   int cur = u[0], cnt = 1;
   for (int i = 1; i < n; ++i)
      if (u[i] != cur) {
         v.push_back(make_pair(cur, cnt));
         cur = u[i];
         cnt = 1;
      }
      else
         ++cnt;
   v.push_back(make_pair(cur, cnt));
   int sm  = 1;
   for (vector<PII>::iterator it = v.begin(); it != v.end(); ++it) {
      int x = it->second;
      it->second = sm;
      sm += x;
   }
   /*for (int i = 0; i < (int) v.size(); ++i)
      cout << v[i].first << " " << v[i].second << endl;*/
   vector<PII> mem = v;
   rev = VI(n + 1, -1);
   for (int q = 0; q < 2; ++q) {
      for (int i = 0; i < n; ++i) {
         vector<PII>::iterator lit = lower_bound(v.begin(), v.end(), make_pair(A[q][i], 0));
         assert(lit != v.end());
         assert(lit->first == A[q][i]);
         assert(rev[lit->second] == -1 || rev[lit->second] == A[q][i]);
         rev[lit->second] = A[q][i];
         A[q][i] = lit->second;
         ++lit->second;
      }
      v = mem;
   }
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int n;
   LL k, l;
   cin >> n >> k >> l;
   //scanf("%d %lld %lld", &n, &k, &l);

   vector<VI> A(2, VI(n));
   for (int q = 0; q < 2; ++q)
      for (int i = 0; i < n; ++i)
         cin >> A[q][i];
         //scanf("%d", &A[q][i]);

   VI rev;
   scale(A, n, rev);
   /*for (int q = 0; q < 2; ++q) {
      for (int i = 0; i < n; ++i)
         printf("%d ", A[q][i]);
      printf("\n");
   }*/
   /*cout << "Rev: ";
   for (VI::iterator it = rev.begin(); it != rev.end(); ++it)
      cout << *it << " ";
   cout << endl;*/

   // inverted A[1] table
   VI inv(n + 1);
   for (int i = 0; i < n; ++i)
      inv[A[1][i]] = i;

   // finalDest[i] - where guy A[0][i] will eventually land in A[1]
   VI finalDest(n);
   for (int i = 0; i < n; ++i)
      finalDest[i] = inv[A[0][i]];
   //for (int i = 0; i < n; ++i)
   //   cout << i << " " << rev[A[0][i]] << " " << finalDest[i] << endl;

   SegmentTree t(n);

   

   vector<VI> links(n);
   // for each guy A[0][i] we calculate guy we have to wait for 
   // to be ready for us to be rweady (or it mark it as 
   // "ready" to enter the leftmost field)
   //VI s;
   set<PII> S;

   VI in_fringe(n, 0);
   for (int i = 0; i < n; ++i) {
      S.insert(make_pair(finalDest[i], i));
      set<PII>::iterator it = S.find(make_pair(finalDest[i], i));
      if (it == S.begin()) {
         t.insert(i, finalDest[i], A[0][i]);
         in_fringe[i] = 1;
         //cout << i << " " << finalDest[i] << " " << rev[A[0][i]] << endl;
      }
      else {
         --it;
         assert(it->first < finalDest[i]);
         links[it->second].push_back(i);
      }
      
      /*while (!s.empty() && finalDest[s.back()] > finalDest[i])
         s.pop_back();
      if (s.empty()) {
         //cout << i << " " << finalDest[i] << " " << A[0][i] << endl;
         t.insert(i, finalDest[i], A[0][i]);
         // TODO - add it to the structure with "ready" guys
      }
      else {
         assert(finalDest[s.back()] < finalDest[i]);
         links[s.back()].push_back(i);
      }
      s.push_back(i);*/
   }

   /*int pos = t.query(0, 2, 0, 2);
   cout << pos << " " << A[0][pos] << endl;

   pos = t.query(0, 0, 0, 1);
   cout << pos << " " << A[0][pos] << endl;*/

   VI res;
   res.reserve(n);
   k = k - l;
   swap(k, l);
   SegmentTreeOne new_pos(n);
   for (int i = 0; i < n; ++i)
      new_pos.insert(i, i, i);
   VI active(n, 1);
   for (int i = 0; i < n; ++i) {
      //cerr << i << endl;
      //cout << "k = " << k << " l = " << l << endl;
      int best_pos = t.query(0, (int) min(k + i, LL(n - 1)), 0, (int) min(l + i, LL(n - 1)) );
      active[best_pos] = 0;
      //cout << best_pos << " " << rev[A[0][best_pos]] << endl;
      res.push_back(rev[A[0][best_pos]]);
      //cout << res[i] << " ";
      //if (i == 20) 
      //   break;
      int cur_pos = new_pos.query(best_pos);
      assert(cur_pos >= i);
      new_pos.insert(0, best_pos, 1);
      k -= cur_pos - i;
      //assert(finalDest[best_pos] >= i);
      l -= (max(finalDest[best_pos] - i, 0)); // TODO think about this
      //for (VI::iterator it = links[best_pos].begin(); it != links[best_pos].end(); ++it) {
         //cout << best_pos << " links to " << *it << " " << finalDest[*it] << " " << rev[A[0][*it]] << endl;
        // t.insert(*it, finalDest[*it], A[0][*it]);
      //}
      int mn = INF;
      for (int j = 0; j < n; ++j)
         if (active[j]) {
            if (finalDest[j] < mn) {
               mn = finalDest[j];
               if (!in_fringe[j]) {
                  in_fringe[j] = 1;
                  t.insert(j, finalDest[j], A[0][j]);
               }
            }
         }
      t.insert(best_pos, finalDest[best_pos], INF);
   }

   //cout << "Result: \n";
   for (VI::iterator it = res.begin(); it != res.end(); ++it)
      cout << *it << " ";
   cout << endl;


   return 0;
}	
