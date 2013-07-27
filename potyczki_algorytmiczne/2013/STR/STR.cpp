#include <iomanip>
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

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> PII;
typedef double LD;

/* CHECKLIST 
 * 1) long longs 
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

struct edge {
   int a, b, w, p;
};

const int DBG = 0, INF = int(1e9);

int n, m, k;

vector<edge> e;

// in[i]/out[i] contains indices of edges
// coming into/out of node i
vector<VI> in, out;

// topologically sorted list of nodes
VI nodes;
// nodes[rev[i]] = i
VI rev; 

// earliest possible time a train can departure from a given node
VI dep_time;

void read_data() {
   cin >> n >> m >> k;

   e = vector<edge>(m);
   in = vector<VI>(n);
   out = vector<VI>(n);

   for (int i = 0; i < m; ++i) {
      cin >> e[i].a >> e[i].b >> e[i].w >> e[i].p;
      --e[i].a;
      --e[i].b;
      in[e[i].b].push_back(i);
      out[e[i].a].push_back(i);
   }
}

void topo_sort() {
   vector<int> in_degree(n);
   VI S;
   S.reserve(n);
   for (int i = 0; i < n; ++i) {
      in_degree[i] = (int) in[i].size();
      if (in_degree[i] == 0)
         S.push_back(i);
   }

   nodes.reserve(n);
   rev = VI(n);
   while (!S.empty()) {
      int v = S.back();
      S.pop_back();
      rev[v] = (int) nodes.size();
      nodes.push_back(v);
      for (VI::const_iterator it = out[v].begin(); it != out[v].end(); ++it) {
         if (--in_degree[e[*it].b] == 0)
            S.push_back(e[*it].b);
      }
   }
   assert((int) nodes.size() == n);
}

void count_dep_time() {
   dep_time = VI(n);
   for (int v = 0; v < n; ++v) {
      int latest = -INF;
      for (VI::const_iterator it = in[v].begin(); it != in[v].end(); ++it) 
         latest = max(latest, e[*it].w + e[*it].p);
      dep_time[v] = latest;
   }
}

LL count_delay(int first_delayed) {
   LL res = 0;

   VI new_dep_time = dep_time;
   new_dep_time[first_delayed] += k;
   res += k;

   for (int i = rev[first_delayed] + 1; i < n; ++i) {
      int v = nodes[i];
      for (VI::const_iterator it = in[v].begin(); it != in[v].end(); ++it) {
         edge& ed = e[*it];
         int dep = max(ed.w, new_dep_time[ed.a]);
         int arr = dep + ed.p;
         res += arr - (ed.w + ed.p);
         new_dep_time[v] = max(new_dep_time[v], arr);
      }
   }
   
   return res;
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   read_data();
   topo_sort();
   count_dep_time();

   LL res = 0;
   // for each node try to delay (only) the latest train
   // coming to it
   for (int v = 0; v < n; ++v) 
         res = max(res, count_delay(v));

   cout << res << endl;

   return 0;
}	
