#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <memory>

using namespace std;

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * */

const int DBG = 0, INF = int(1e9), MAXN = int(1e5);

template<class T>
class AvlTree {
   struct Node {
      Node(T val, shared_ptr<const Node> left, shared_ptr<const Node> right, int height, int size):
         val(val), left(left), right(right), height(height), size(size) {}
      T val;
      shared_ptr<const Node> left, right;
      int height;
      int size; // number of elements in a subtree
   };
   typedef shared_ptr<const Node> Tree;
   friend inline int height(const Tree& t) {
      if (!t) return 0;
      return t->height;
   }
   friend inline int siz(const Tree& t) {
      if (!t) return 0;
      return t->size;
   }
   friend inline int rootCount(const Tree& t) {
      if (!t) return 0;
      return t->size - siz(t->left) - siz(t->right);
   }
   friend inline bool isBalanced(const Tree& t) {
      if (!t) return true;
      return abs(height(t->left) - height(t->right)) <= 2;
   }
   friend inline Tree create(const Tree& left, T val, int count, const Tree& right) {
      //assert(isBalanced(left));
      //assert(isBalanced(right));
      //assert(!left || maxElem(left) < val); // TODO comment out, this is costly
      //assert(!right || val < minElem(right)); // TODO comment out, this is costly
      //assert(abs(height(left) - height(right)) <= 2);
      return make_shared<Node>(val, left, right, max(height(left), height(right)) + 1,
         siz(left) + siz(right) + count);
   }
   friend Tree createAndBalance(const Tree& left, T val, int count, const Tree& right) {
      //assert(isBalanced(left));
      //assert(isBalanced(right));
      //assert(!left || maxElem(left) < val); // TODO comment out, this is costly
      //assert(!right || val < minElem(right)); // TODO comment out, this is costly
      //assert(abs(height(left) - height(right)) <= 3);
      if (height(left) > height(right) + 2) {
         //assert(left);
         if (height(left->left) >= height(left->right)) return
            create(
               left->left,
               left->val,
               rootCount(left),
               create(left->right, val, count, right)
            );
         //assert(left->right);
         return create(
            create(left->left, left->val, rootCount(left), left->right->left),
            left->right->val,
            rootCount(left->right),
            create(left->right->right, val, count, right)
         );
      }
      if (height(left) + 2 < height(right)) {
         //assert(right);
         if (height(right->left) <= height(right->right)) return
            create(
               create(left, val, count, right->left),
               right->val,
               rootCount(right),
               right->right
            );
         //assert(right->left);
         return create(
            create(left, val, count, right->left->left),
            right->left->val,
            rootCount(right->left),
            create(right->left->right, right->val, rootCount(right), right->right)
         );
      }
      // inline expansion of create for better speed in the most frequent case
      // where no rebalancing is required
      return make_shared<Node>(val, left, right, max(height(left), height(right)) + 1,
         siz(left) + siz(right) + count);
   }

   friend Tree add(const Tree& t, T val) {
      if (!t) return make_shared<Node>(val, shared_ptr<Node>(), shared_ptr<Node>(), 1, 1);
      if (val == t->val) return make_shared<Node>(val, t->left, t->right,
         t->height, t->size + 1);
      if (val < t->val) return
         createAndBalance(add(t->left, val), t->val, rootCount(t), t->right);
      return createAndBalance(t->left, t->val, rootCount(t), add(t->right, val));
   }

   friend T minElem(const Tree& t) {
      //assert(t);
      if (!t->left) return t->val;
      return minElem(t->left);
   }

   friend T maxElem(const Tree& t) {
      //assert(t);
      if (!t->right) return t->val;
      return maxElem(t->right);
   }

   // number of occurences of smallest element in the t
   friend int minElemOccur(const Tree& t) {
      //assert(t);
      if (!t->left) return rootCount(t);
      return minElemOccur(t->left);
   }

   // remove ALL occurences of the smallest element in the t
   friend Tree removeMinElem(const Tree& t) {
      //assert(t);
      if (!t->left) return t->right;
      return createAndBalance(removeMinElem(t->left), t->val, rootCount(t), t->right);
   }

   friend Tree merge(const Tree& t1, const Tree& t2) {
      //assert(!t1 || !t2 || maxElem(t1) < minElem(t2));
      //assert(abs(height(t1) - height(t2)) <= 2);
      if (!t1) return t2;
      if (!t2) return t1;
      return createAndBalance(t1, minElem(t2), minElemOccur(t2), removeMinElem(t2));
   }

   friend int count(const Tree& t, T val) {
      if (!t) return 0;
      if (t->val == val) return rootCount(t);
      if (val < t->val) return count(t->left, val);
      return count(t->right, val);
   }

   friend int countSmall(const Tree& t, T val) {
      if (!t) return 0;
      if (t->val == val) return siz(t->left);
      if (val < t->val) return countSmall(t->left, val);
      return siz(t->left) + rootCount(t) + countSmall(t->right, val);
   }

   friend int countBig(const Tree& t, T val) {
      if (!t) return 0;
      if (val == t->val) return siz(t->right);
      if (t->val < val) return countBig(t->right, val);
      return siz(t->right) + rootCount(t) + countBig(t->left, val);
   }

   friend Tree remove(const Tree& t, T val) {
      if (!t) return t;
      if (val < t->val)
         return createAndBalance(remove(t->left, val), t->val, rootCount(t), t->right);
      if (val > t->val)
         return createAndBalance(t->left, t->val, rootCount(t), remove(t->right, val));
      if (rootCount(t) > 1)
         return make_shared<Node>(t->val, t->left, t->right, t->height, t->size - 1);
      return merge(t->left, t->right);
   }

   shared_ptr<const Node> t;

   explicit AvlTree(shared_ptr<const Node> node) : t(node) {}

   public:
      AvlTree(): t(shared_ptr<const Node>()) {}
      int size() const { return siz(t); }
      bool empty() const { return t ? false : true; }
      int count(T val) const { return count(t, val); }
      int countSmaller(T val) const { return countSmall(t, val); }
      int countBigger(T val) const { return countBig(t, val); }
      AvlTree insert(T val) const { return AvlTree(add(t, val)); }
      AvlTree erase(T val) const { return AvlTree(remove(t, val)); }

      friend void swap(AvlTree<T>& s1, AvlTree<T>& s2) { swap(s1.t, s2.t); }
};

struct str {
   map<int, int> m;
   AvlTree<int> s;
   void insert(int col, int much) {
      if (m[col] > 0)  s = s.erase(m[col]);
      m[col] += much;
      s = s.insert(m[col]);
   }
   int query(int k) {
      return s.countBigger(k - 1);
   }
};

void swap(str& s1, str& s2) {
   swap(s1.m, s2.m);
   swap(s1.s, s2.s);
}

void merge(str& s1, str& s2) {
   if (s1.m.size() < s2.m.size()) swap(s1, s2);
   for (auto it: s2.m) s1.insert(it.first, it.second);
}

int n, m;
vector<int> v[MAXN], c, result;
vector<pair<int, int>> q[MAXN];
vector<bool> vis;

void dfs(str& s, int u) {
   vis[u] = true;
   for (auto child: v[u]) if (!vis[child]) {
      str* cs = new(str);
      dfs(*cs, child);
      merge(s, *cs);
      delete(cs);
   }
   s.insert(c[u], 1);
   for (auto query: q[u]) {
      int pos = query.second, k = query.first;
      result[pos] = s.query(k);
   }
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   cin >> n >> m;
   c = vector<int>(n);
   vis = vector<bool>(n, false);
   for (auto& x: c) cin >> x;
   for (int i = 0; i < n - 1; ++i) {
      int a, b; cin >> a >> b; --a, --b;
      v[a].push_back(b);
      v[b].push_back(a);
   }
   for (int i = 0; i < m; ++i) {
      int v, k; cin >> v >> k; --v;
      q[v].push_back(make_pair(k, i));
   }
   result = vector<int>(m);
   str s;
   dfs(s, 0);
   for (auto r: result) cout << r << endl;
   return 0;
}

