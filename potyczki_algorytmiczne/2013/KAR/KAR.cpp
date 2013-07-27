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

int DBG = 0;
const int INF = int(1e9), MAXN = 2500;

struct tree {
   int w, h;
   vector<tree*> sons;
   int start;
   tree(int w_ = -1, int h_ = -1) : w(w_), h(h_), sons(vector<tree*>()), start(-3) {}
};

int n, m;
char board[MAXN][MAXN + 1];
char tmp_board[MAXN][MAXN];
int prefix_sums[MAXN][MAXN];

void calc_prefix_sums() {
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
         prefix_sums[i][j] = (board[i][j] == '_');
   for (int i = 0; i < n; ++i)
      for (int j = 1; j < m; ++j)
         prefix_sums[i][j] += prefix_sums[i][j - 1];
}

bool is_empty(int row, int col_b, int col_e) {
   if (row == n)
      return false;
   if (col_b > col_e)
      return true;
   if (col_b == 0)
      return (prefix_sums[row][col_e] == 0);
   return (prefix_sums[row][col_e] - prefix_sums[row][col_b - 1] == 0);
}

// space[i][j] - how many consecutive 'X' fields there
// are starting from space[i][j], space[i - 1][j] ...
int space[MAXN][MAXN];

void debugSet(set<PII>& A) {
   cout << "Set begin:\n";
   for (set<PII>::iterator it = A.begin(); it != A.end(); ++it)
      cout << it->second << " " << it->first << endl;
   cout << "###\n\n";
}

int DBG2 = 0;
// merge B to A
void merge(set<PII>& A, set<PII>& B) {
   if (DBG) cout << "MERGE:\n";
   if (DBG) debugSet(A);
   if (DBG) debugSet(B);
   set<PII>::iterator itA = A.begin(), itB = B.begin();
   for (; itA != A.end() && itB != B.end();) {
      if (itA->second > itB->second) {
         swap(itA, itB);
         swap(A, B);
         if (DBG2)
            cout << "SWAP\n";
      }
      if (*itA == *itB) {
         ++itA;
         B.erase(itB++);
      }
      else if ((itA->second == itB->second && itA->first < itB->first) ||
              (itA->second < itB->second && itA->first < itB->first))  {
         itA = A.upper_bound(make_pair(itB->first, INF));
      }
      else if (itA->second < itB->second && itA->first == itB->first) {
         itA = A.upper_bound(make_pair(itB->first, INF));
         B.erase(itB++);
      }
      else if (itA->second == itB->second && itA->first > itB->first) {
         itB = B.upper_bound(make_pair(itA->first, INF));
      }
      else if (itA->second < itB->second && itA->first > itB->first) {
         int lw = -1, lh = -1;
         while (itB != B.end() && itB->second >= itA->second) {
            lw = itB->second;
            lh = itB->first;
            B.erase(itB++);
         }
         assert(lw != -1 && lh != -1);
         if (lh >= itA->first) {
            B.insert(make_pair(lh, lw));
            itB = B.find(make_pair(lh, lw));
         }
         else {
            A.insert(make_pair(lh, itA->second));
         }
      }
      if (DBG2) {
         cout << "ITERATION END\n";
         debugSet(A);
         if (itA != A.end())
            cout << itA->second << " itA " << itA->first << endl;
         debugSet(B);
         if (itB != B.end())
            cout << itB->second << " itB " << itB->first << endl;
      }   
   }
   DBG2 = 0;
   while (itA != A.end())
      A.erase(itA++);
   while (itB != B.end())
      B.erase(itB++);
   if (A.size() < B.size())
      swap(A, B);
   for (set<PII>::iterator it = B.begin(); it != B.end(); ++it)
      A.insert(*it);
   if (DBG) {
      cout << "Result:\n";
      debugSet(A);
      cout << "@@@@@@@\n\n";
   }
}

void flatten(tree *t, set<PII>& res) {
   assert(t != NULL);
   for (vector<tree*>::iterator it = t->sons.begin(); it != t->sons.end(); ++it) 
      if (res.empty())
         flatten(*it, res);
      else {
         set<PII> tmp;
         flatten(*it, tmp);
         merge(res, tmp);
      } 
   if (t->h != 0) {
      res.insert(make_pair(t->h, t->w));
      assert(*res.begin() == make_pair(t->h, t->w));
   }
}

void outputTree(tree* t, string tab) {
   assert(t != NULL);
   cout << tab << t->w << " " << t->h << endl;
   for (vector<tree*>::iterator it = t->sons.begin(); it != t->sons.end(); ++it)
      outputTree(*it, tab + "  ");
}

tree* build_rect_tree() {
   // stack of rectangles 
   vector<tree*> r(1, new tree(MAXN + 1, 0));
   for (int i = 0; i < n; ++i) {

      vector<pair<PII, int> >v;

      for (int j = 0; j < m; ++j) {
         int pos = j;
         while (r.back()->h > space[i][j]) {
            tree* t = r.back();
            r.pop_back();
            pos = t->w;
            if (is_empty(i + 1, pos, j - 1)) {
            }
            else
               v.push_back(make_pair(make_pair(pos, (j - 1)), t->h));
            t->w = j - t->w;
         }
         if (r.back()->h < space[i][j]) {
            // temporarily we set w to start column index
            tree *t = new tree(pos, space[i][j]);
            r.push_back(t);
         }
      }
      while (r.size() > 1) {
         tree *t = r.back();
         r.pop_back();
         if (is_empty(i + 1, t->w, m - 1)) {
         }
         else
            v.push_back(make_pair(make_pair(t->w, (m - 1)), t->h));
         t->w = m - t->w;
      }
      for (int k = 0, n_ = (int) v.size(); k < n_; ++k)
         v[k].first.second *= -1;
      sort(v.begin(), v.end());
      for (int k = 0, n_ = (int) v.size(); k < n_; ++k)
         v[k].first.second *= -1;

      vector<pair<PII, int> >s;

      for (int k = 0, n_ = (int) v.size(); k < n_; ++k) {
         while (!s.empty() && v[k].first.first > s.back().first.second) {
            s.pop_back();
            tree* t = r.back();
            r.pop_back();
            
            {
              int beg = t->start; 
              for (vector<tree*>::iterator it = t->sons.begin(); it != t->sons.end(); ++it) {
                  int nxt = (*it)->start;
                  if (!is_empty(i + 1, beg, nxt - 1)) {
                     t->sons.clear();
                     break;
                  }
                  beg = (*it)->start + (*it)->w;
              }
              if (!is_empty(i + 1, beg, t->start + t->w - 1))
               t->sons.clear();
            }
            
         }
         assert(s.empty() || v[k].first.second <= s.back().first.second);
         tree* t = new tree(v[k].first.second - v[k].first.first + 1, v[k].second);
         t->start = v[k].first.first;
         r.back()->sons.push_back(t);
         r.push_back(t);
         s.push_back(v[k]);
      }
   
      while (r.size() > 1) {
         tree* t = r.back();
         r.pop_back();
         
         {
            int beg = t->start; 
            for (vector<tree*>::iterator it = t->sons.begin(); it != t->sons.end(); ++it) {
               int nxt = (*it)->start;
               if (!is_empty(i + 1, beg, nxt - 1)) {
                  t->sons.clear();
                  break;
               }
               beg = (*it)->start + (*it)->w;
            }
            if (!is_empty(i + 1, beg, t->start + t->w - 1)) {
               t->sons.clear();
            }
         }
         
      }
   }

   return r[0];
}

void count_space() {
   for (int j = 0; j < m; ++j) {
      int cur = 0;
      for (int i = 0; i < n; ++i) {
         if (board[i][j] == '_')
            cur = 0;
         else
            ++cur;
         space[i][j] = cur;
      }
   }
}

void read_data() {
   scanf("%d %d", &n, &m);

   for (int i = 0; i < n; ++i)
      scanf("%s", board[i]);
}


int main() {   

   read_data();

   set<PII> T[4];
   for (int q = 0; q < 4; ++q) {
      if (DBG + 0) {
         for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
               cout << board[i][j];
            cout << endl;
         }
      }
      calc_prefix_sums();
      count_space();
      tree* t = build_rect_tree();
      if (DBG + 0)
         outputTree(t, "");
      //set<PII> S;
      flatten(t, T[q]);

      for (int j = 0; j < m; ++j) {
         int left = 0, right = n - 1;
         while (left < right) {
            swap(board[left][j], board[right][j]);
            ++left;
            --right;
         }
      }
      if (q == 1) { // transpose
         for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
               tmp_board[j][i] = board[i][j];
         for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
               board[j][i] = tmp_board[j][i];
         swap(n,m);
      }
   }
   for (int i = 2; i < 4; ++i) {// transpose sets
      set<PII> rs;
      for (set<PII>::iterator it = T[i].begin(); it != T[i].end(); ++it)
         rs.insert(make_pair(it->second, it->first));
      swap(rs, T[i]);
   }
   //for (int i = 0; i < 4; ++i)
   //   debugSet(T[i]);
   for (int i = 1; i < 4; ++i)
      merge(T[0], T[i]);
   int mx = 0, a = 0, b = 0;
   for (set<PII>::iterator it = T[0].begin(); it != T[0].end(); ++it)
      if (it->first * it->second > mx) {
         mx = it->first * it->second;
         a = it->first;
         b = it->second;
      }
   cout << a << " " << b << endl;

   return 0;
}	
