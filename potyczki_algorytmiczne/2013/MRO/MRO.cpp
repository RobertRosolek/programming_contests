#include <cstdio>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;

enum TYPE {DIP, ARRIVAL};

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> PII;
typedef double LD;

typedef pair<PII, pair<int, TYPE> > event;

/* CHECKLIST 
 * 1) long longs 
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

const int DBG = 0, INF = int(1e9);

int smallestBin(int n) {
   int rs = 1;
   while (rs < n)
      rs *= 2;
   return rs;
}

class SegmentTree {
   int M;
   VI w;

   public:
      SegmentTree() : M(0), w(VI()) {}
      SegmentTree(int n) : M(smallestBin(n)), w(VI(2 * smallestBin(n), 0)) { 
      }
      void insert(int a, int b, int val) {
         int va = M + a, vb = M + b;
         w[va] += val;
         if (vb != va)
            w[vb] += val;
         while ( (va >> 1) != (vb >> 1) ) {
            if ( (va & 1) == 0)
               w[va ^ 1] += val;
            if ( (vb & 1) == 1)
               w[vb ^ 1] += val;
            va >>= 1;
            vb >>= 1;
         }   
      }
      int query(int x) {
         int v = M + x;
         int res = w[v];
         while (v != 1) {
            v >>= 1;
            res += w[v];
         }
         return res;
      }
};

int n;

struct group {
   int left, right, dest, dest_dip, time_stamp, loc, cur_walk_id;
   //group(int left_, int right_, int dest_, int time_stamp_, int loc_) :
   //   left(left_), right(right_), dest(dest_), time_stamp(time_stamp_), loc(loc_) {}
};

struct dip {
   int pos, left_group, right_group;
   dip(int pos_): pos(pos_), left_group(-1), right_group(-1) {}
   bool operator<(const dip& d) {
      return pos < d.pos;
   }
};

SegmentTree t;

VI group_slots;
vector<group> g;
int all_group;
set<PII> group_set;

vector<dip> dips;
set<PII> dip_set;

priority_queue<event, vector<event>, greater<event> > Q;

int tm;



inline int get_ants_position(int group, int index, int tm) {
   //cout << "get\n";
   //cout << index << " query = " << t.query(index) << " loc = " << g[group].loc << " dest = " << g[group].dest << endl;
   if (g[group].dest == -1) 
      return t.query(index) + g[group].loc;
   else if (g[group].dest > g[group].loc)
      return t.query(index) + g[group].loc + (tm - g[group].time_stamp);
   else
      return t.query(index) + g[group].loc - (tm - g[group].time_stamp);
      
}

void output_group(int group) {
   cout << "Group no " << group << " left = " << g[group].left << " right = " << g[group].right << " " << " loc = " << g[group].loc
      << " timestamp = " << g[group].time_stamp << " cur_walk_id = " << g[group].cur_walk_id << " dest = " << g[group].dest << " " 
      << " dest no = " << g[group].dest_dip << " cur tm = " << tm << " left_pos = " << get_ants_position(group, g[group].left, tm) << 
      "right_pos = " << get_ants_position(group, g[group].right, tm) << endl;
}
void full_debug() {
   cout << "Groups: \n";
   for (set<PII>::iterator it = group_set.begin(); it != group_set.end(); ++it)
      output_group(it->second);
}
void add_left_group(int group, int dip, int tm) {
   int left_position = get_ants_position(group, g[group].left, tm);

   if (dips[dip].right_group != -1) {
      // MERGE
      int group_2 = dips[dip].right_group;
      int left_position_2 = get_ants_position(group_2, g[group_2].left, tm);
      t.insert(g[group].left, g[group].right, left_position - left_position_2);
      g[group_2].right = g[group].right;

      // move to trash
      group_set.erase(make_pair(g[group].loc, group));
      group_slots.push_back(group);
   }
   else {
      dips[dip].right_group = group;
      g[group].dest = dips[dip].pos;
      g[group].dest_dip = dip;
      ++g[group].cur_walk_id;
      Q.push(make_pair( make_pair(tm + left_position - dips[dip].pos, -group),
                        make_pair(++g[group].cur_walk_id, ARRIVAL)));
   }
}

void add_right_group(int group, int dip, int tm) {
   int left_position = get_ants_position(group, g[group].left, tm);

   if (dips[dip].left_group != -1) {
      // MERGE
      int group_2 = dips[dip].left_group;
      int left_position_2 = get_ants_position(group_2, g[group_2].left, tm);
      t.insert(g[group_2].left, g[group_2].right, left_position_2 - left_position);
      g[group_2].left = g[group].left;
      group_set.erase(make_pair(g[group_2].loc, group_2));
      g[group_2].loc = left_position;
      group_set.insert(make_pair(g[group_2].loc, group_2));
      g[group_2].time_stamp = tm;


      // move to trash
      group_set.erase(make_pair(g[group].loc, group));
      group_slots.push_back(group);
   }
   else {
      int right_position = get_ants_position(group, g[group].right, tm);
      dips[dip].left_group = group;
      g[group].dest = dips[dip].pos;
      g[group].dest_dip = dip;
      ++g[group].cur_walk_id;
      Q.push(make_pair( make_pair(tm + dips[dip].pos - right_position, -group),
                        make_pair(++g[group].cur_walk_id, ARRIVAL)));
   }

}

int split(int group, int pos, int tm) {
   int nxt = group_slots.back(); group_slots.pop_back();
   //assert(nxt < n);
   g[nxt].left = pos + 1;
   g[nxt].right = g[group].right;
   g[nxt].loc = get_ants_position(group, pos + 1, tm);
   group_set.insert(make_pair(g[nxt].loc, nxt));
   int shift = t.query(pos + 1);
   t.insert(pos + 1, g[nxt].right, -shift);
   group_set.insert(make_pair(g[nxt].loc, nxt));
   g[nxt].time_stamp = tm;
   ++g[nxt].cur_walk_id;
   g[nxt].dest = g[nxt].dest_dip = -1;
   
   g[group].right = pos;

   //assert(nxt < n);
   return nxt;
}

void reset(int group, int tm) {
   int left_position = get_ants_position(group, g[group].left, tm);
   int right_position = get_ants_position(group, g[group].right, tm);
   group_set.erase(make_pair(g[group].loc, group));
   g[group].loc = left_position;
   group_set.insert(make_pair(g[group].loc, group));
   g[group].time_stamp = tm;
   ++g[group].cur_walk_id;
   if (g[group].dest != -1 && dip_set.count(make_pair(g[group].dest, g[group].dest_dip)) ) {
      if (right_position < g[group].dest)
         dip[g[group].dest].left_group = -1;
      else {
         assert(g[group].dest < left_position);
         dips[g[group].dest].right_group = -1;
      }
   }
   g[group].dest = -1;
}


void regroup_group(int group, int tm) {
   int left_position = get_ants_position(group, g[group].left, tm);
   int right_position = get_ants_position(group, g[group].right, tm);
   //assert(group < n);
   cout << "regroup group " << group << endl;
   cout << "left_position = " << left_position << " right_position = " << right_position << endl;
   assert(left_position <= right_position); 
   reset(group, tm);

   if (dip_set.empty())
      return;

   set<PII>::iterator lit = dip_set.lower_bound(make_pair(left_position, -1));
   // only dip on the left
   if (lit == dip_set.end()) {
      --lit;
      add_left_group(group, lit->second, tm);
      return;
   }
   int dip = lit->second;
   cout << "dip = " << dips[dip].pos << endl;
   if (left_position <= dips[dip].pos && dips[dip].pos <= right_position) {
      int left = g[group].left, right = g[group].right;
      // binary search for last postition <= dip
      while (left < right) {
         int s = (left + right + 1) / 2;
         if (get_ants_position(group, s, tm) > dips[dip].pos)
            right = s - 1;
         else
            left = s;
      }
      int pos = left;
      cout << "POS = " << pos << endl;
      if (get_ants_position(group, pos, tm) == dips[dip].pos) {
         dip_set.erase(lit);
         regroup_group(group, tm);
         return;
      }
      // split into two groups and recourse
      int nxt = split(group, pos, tm);
      regroup_group(nxt, tm);
      regroup_group(group, tm);
      return;
   }

   assert(right_position < dips[dip].pos);
   if (lit == dip_set.begin()) {
      add_right_group(group, dip, tm);
      return;
   }
   
   int left_dip = (--lit)->second;

   cout << "left dip = " << dips[left_dip].pos << endl;
   
   int dist = dips[dip].pos - dips[left_dip].pos;
   int range = dips[left_dip].pos + dist / 2;

   int left = g[group].left, right = g[group].right;
   while (left < right) {
      int s = (left + right + 1) / 2;
      if (get_ants_position(group, s, tm) > range)
         right = s - 1;
      else
         left = s;
   }
   int pos = left;

   // split into 2 group and recourse
   int nxt = split(group, pos, tm);
   regroup_group(nxt, tm);
   regroup_group(group, tm);

}

void merge(int group_a, int group_b, int tm) {
   int left_position_a = get_ants_position(group_a, g[group_a].left, tm);
   //int right_position_a = get_ants_position(group_a, g[group_a].right, tm);
   int left_position_b = get_ants_position(group_b, g[group_b].left, tm);
   //int right_position_b = get_ants_position(group_b, g[group_b].right, tm);

   assert(left_position_a <= left_position_b);
   reset(group_a, tm);
   reset(group_b, tm);

   t.insert(g[group_b].left, g[group_b].right, left_position_b - left_position_a);
   g[group_a].right = g[group_b].right;

   // move to trash
   group_set.erase(make_pair(g[group_b].loc, group_b));
   group_slots.push_back(group_b);

   regroup_group(group_a, tm);
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   scanf("%d", &n);
   VI x(n);
   for (int i = 0; i < n; ++i)
      scanf("%d", &x[i]);


   int m;
   scanf("%d", &m);
   for (int i = 0; i < m; ++i) {
      int tm, y;
      scanf("%d %d", &tm, &y);
      Q.push(make_pair(make_pair(tm, y), make_pair(-1, DIP))); 
   }

   t = SegmentTree(n);
   for (int i = 0; i < n; ++i) 
      t.insert(i, i, x[i] - x[0]);

   
   group_slots.resize(5 * n);
   for (int i = 0; i < 5 * n; ++i)
      group_slots[i] = i;

   g.resize(5 * n);
   int grp = group_slots.back();
   group_slots.pop_back();
   g[grp].left = 0;
   g[grp].right = n - 1;
   g[grp].dest = -1;
   g[grp].dest_dip = -1;
   g[grp].time_stamp = 0;
   g[grp].loc = x[0];
   g[grp].cur_walk_id = 0;
   group_set.insert(make_pair(x[0], grp));

   dips.reserve(m);

   while (!Q.empty()) {
      tm = Q.top().first.first;
      cout << tm << endl;
      TYPE type = Q.top().second.second;
      if (type == DIP) {
         int y = Q.top().first.second;
         cout << "DIP " << y << endl;
         Q.pop();
         int dip_no = (int) dips.size();
         dips.push_back(dip(y));
         dip_set.insert(make_pair(y, dip_no));

         set<PII>::iterator lit = group_set.lower_bound(make_pair(y, -1));
         if (lit != group_set.end()) {
            cout << lit->first << " &&&& " << lit->second << endl;
            regroup_group(lit->second, tm);
            if (dip_set.count(make_pair(y, dip_no)) == 0)
               continue;
         }
         if (lit != group_set.begin()) {
            int group = (--lit)->second;
            cout << "gruppe " << group << endl;
            regroup_group( (--lit)->second, tm);
         }
         cout << "count = " << dip_set.count(make_pair(y, dip_no)) << endl;

      }
      else /* type == ARRIVAL */ {
         cout << "ARRIVAL\n";
         int group = -Q.top().first.second, walk_id = Q.top().second.first;
         Q.pop();
         // event no longer valid
         if (g[group].cur_walk_id != walk_id)
            continue;
         
         int left_position = get_ants_position(group, g[group].left, tm),
               right_position = get_ants_position(group, g[group].right, tm);
         set<PII>::iterator fit = group_set.find(make_pair(g[group].loc, group));
         assert(fit != group_set.end());
         dip_set.erase(make_pair(g[group].dest, g[group].dest_dip));
         if (g[group].dest < g[group].loc) {
            cout << "arrive left " << group << endl;;
            //g[group].dest = -1;
            if (fit == group_set.begin()) {
               cout << "wrong\n";
               regroup_group(group, tm);
            }
            else {
               merge(fit->second, group, tm);
            }
         }
         else {
            //cout << left_position << " " << right_position << " " << g[group].dest << endl;
            assert(g[group].dest == right_position);
            //g[group].dest = -1;
            ++fit;
            if (fit == group_set.end())
               regroup_group(group, tm);
            else
               merge(group, fit->second, tm);
         }
      }
      full_debug();
   }

   VI res(n, -1);
   while (!group_set.empty()) {
      int group = group_set.begin()->second;
      cout << "HEY " << group << " " << g[group].left << " " << g[group].right << endl;
      group_set.erase(group_set.begin());
      for (int i = g[group].left; i <= g[group].right; ++i)
         res[i] = get_ants_position(group, i, tm);
   }  

   for (int i = 0; i < n; ++i)
      if (i < n - 1)
          printf("%d ", res[i]);
      else
         printf("%d\n", res[i]);
         

   return 0;
}	
