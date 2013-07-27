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

/* CHECKLIST 
 * 1) long longs 
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

struct tree {
   int w, h;
   tree* son;
   tree(int w_, int h_, tree* son_ = NULL) : w(w_), h(h_), son(son_) {}
};

const int DBG = 0, INF = int(1e9), MAXN = 2500;

int n, m;
char board[MAXN][MAXN + 1];

// space[i][j] - how many consecutive 'X' fields there
// are starting from space[i][j], space[i - 1][j] ...
int space[MAXN][MAXN];

void merge(tree* parent, tree* new_son) {
   if (parent->son == NULL) 
      parent->son = new_son;
   else 
      while (new_son != NULL) {
         if (parent->son->w > new_son->w)
            swap(parent->son, new_son);

         int pw = parent->son->w, ph = parent->son->h;

         int h = -1;
         while (new_son != NULL && new_son->w >= pw) {
            assert(new_son->h > h);
            h = new_son->h;
            tree* t = new_son->son;
            delete(new_son);
            new_son = t;
         }
         parent->son
      }
}

void build_rect_tree() {
   vector<tree*> r(1, new tree(MAXN + 1, 0));

   for (int i = 0; i < n; ++i) {
      VI S(1, 0);
      r.push_back(new tree(-1, 0));
      for (int j = 0; j < m; ++j) {
         while (S.back() > space[i][j]) {
            int start = r.back()->w;
            r.back()->w = j - start;
            r.back()->h = S.back();
            S.pop_back();
            tree* t = r.back();
            r.pop_back();
            assert(!r.empty());
            if (r.back()->son == NULL)
               r.back()->son = t;
            else
               merge(r.back(), t);
         }
      }
   }
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
   /*for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j)
         printf("%d ", space[i][j]);
      printf("\n");
   }*/
}

void read_data() {
   scanf("%d %d", &n, &m);

   for (int i = 0; i < n; ++i)
      scanf("%s", board[i]);
}


int main() {   

   read_data();
   count_space();
   build_rect_tree();


   return 0;
}	
