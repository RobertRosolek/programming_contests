#include <iostream>
#include <sstream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> PII;
typedef double LD;
typedef pair<PII, int> point;

/* CHECKLIST 
 * 1) long longs 
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

const int DBG = 0, INF = int(1e9);
const LD EPS = LD(1e-8);

const int MAXN = 3000;


enum TYPE {POINT, RECT};

// first coordinate is number of clockwise 90 degrees 
// rotations applied to data points
//LL upper_right_area[4][MAXN][MAXN];
vector<vector<vector<LL> > > upper_right_area;//(4, vector<vector<LL> >(MAXN, vector<LL>(MAXN)));

bool isZero(LD x) {
  return -EPS < x && x < EPS;
}

// double the area actually
LL triangle_area(const PII &a, const PII &b, const PII &c) {
   return LL(b.first - a.first) * (c.second - a.second) - LL(c.first - a.first) * (b.second - a.second);
}

string toString(int i) {
   stringstream ss;
   ss << i;
   string res;
   ss >> res;
   return res;
}

string toString(point& p) {
   return "Point no " + toString(p.second) + " = (" + toString(p.first.first) + ", " + toString(p.first.second) + ")";
}

inline LL det(const PII& p, const PII& q, const PII& r) {
   return p.first * q.second + q.first * r.second + r.first * p.second
         -p.first * r.second - r.first * q.second - q.first * p.second;
}

inline LD dist (const PII &p, const PII &q) {
  return sqrt( LL(p.first - q.first) * (p.first - q.first) + LL(p.second - q.second) * (p.second - q.second) );
}

struct polarComparator {
  PII O;
  polarComparator(const PII &p = make_pair(0,0)) : O(p) {}
  bool operator() (const point &p, const point &q) { 
    LL d = det(O,p.first,q.first);
    if (d == 0)
      return dist(p.first,O) > dist(q.first,O);   
    return d > 0;
  }
};

int smallestBin(int n) {
   int rs = 1;
   while (rs < n)
      rs *= 2;
   return rs;
}

class SegmentTree {
   int M;
   vector<PII> w;

   public:
      SegmentTree(int n) : M(smallestBin(n)), w(vector<PII>(2 * smallestBin(n), make_pair(0, -1))) { 
      }
      void insert(int x, int val, int index) {
         int v = M + x;
         w[v] = make_pair(val, index);
         while (v != 1) {
            v >>= 1;
            w[v] = max(w[v<<1], w[(v<<1) | 1]);
         }
      }
      int query(int a, int b) {
         int va = M + a, vb = M + b;
         PII res = max(w[va], w[vb]);
         while ( (va >> 1) != (vb >> 1) ) {
            if ( (va & 1) == 0)
               res = max(res, w[va ^ 1]);
            if ( (vb & 1) == 1)
               res = max(res, w[vb ^ 1]);
            va >>= 1;
            vb >>= 1;
         }
         assert(res.second != -1);
         return res.second;
      }
};

struct event {
   TYPE type;
   int index;
   int y;
   event(TYPE type_, int index_, int y_) : type(type_), index(index_), y(y_) {}
   bool operator<(const event& e) const {
      if (y != e.y)
         return y < e.y;
      return type == POINT;
   }
};

inline void rotate_points(vector<point>& p) {
   for (vector<point>::iterator it = p.begin(); it != p.end(); ++it) 
      it->first = make_pair(it->first.second, -it->first.first);
}

inline void rotate_rects(vector<pair<PII,PII> >& rect) {
   for (vector<pair<PII,PII> >::iterator it = rect.begin(); it != rect.end(); ++it) 
      *it = make_pair(it->second, make_pair(-it->first.second, -it->first.first));
}

int main() {
   ios_base::sync_with_stdio(0);

   int k, n;
   scanf("%d %d", &k, &n);

   vector<point> p(n);
   for (int i = 0; i < n; ++i)
      scanf("%d %d", &p[i].first.first, &p[i].first.second);
   for (int i = 0; i < n; ++i)
      p[i].second = i;

   upper_right_area = vector<vector<vector<LL> > >(4, vector<vector<LL> >(n, vector<LL>(n)));

   vector<point> a;
   a.reserve(n);

   for (int rot = 0; rot < 4; ++rot)
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            upper_right_area[rot][i][j] = 0;
      
   for (int rot = 0; rot < 4; ++rot) {
      if (DBG) cout << "#### ROTATE " << rot << " ########\n";
      for (int i = 0; i < n; ++i) {
         for (int j = 0; j < n; ++j)
            if (i != j && p[i].first.first <= p[j].first.first && p[i].first.second <= p[j].first.second)
               a.push_back(p[j]);

         polarComparator comp(p[i].first);
         sort(a.begin(), a.end(), comp);
         set<point> S;
         S.insert(make_pair(make_pair(INF, INF), INF));
         if (DBG) cout << "Calculating areas for " << toString(p[i]) << endl;
         for (vector<point>::iterator it = a.begin(); it != a.end(); ++it) {
            set<point>::iterator lit = S.lower_bound(*it);
            assert(lit != S.end());
            if (lit == S.begin()) {
               upper_right_area[rot][i][it->second] = 0;//triangle_area(p[i].first, it->first, make_pair(p[i].first.first, it->first.second));
               if (DBG) cout << "Area to point " << toString(*it) << " goes there directly. Area = " << upper_right_area[rot][i][it->second] << endl;
            }
            else {
               --lit;
               upper_right_area[rot][i][it->second] = upper_right_area[rot][i][lit->second] + triangle_area(p[i].first, lit->first, it->first);
               if (DBG) cout  << "Area to point " << toString(*it) << " goes through point " << toString(p[lit->second]) 
                     << ". Area = " << upper_right_area[rot][i][it->second] << endl;
            }
            
            S.insert(*it);
         }
         a.clear();
      }
   
      rotate_points(p);
   }

   int m;
   scanf("%d", &m);
   vector<pair<PII,PII> > rect(m);
   for (int i = 0; i < m; ++i)
      scanf("%d %d %d %d", &rect[i].first.first, &rect[i].first.second, 
            &rect[i].second.first, &rect[i].second.second);

   // border_point[rot][q] - highest point inside rect[q] after rot rotations
   // 90 degrees clockwise
   vector<VI> border_point(4, VI(m));
   
   for (int rot = 0; rot < 4; ++rot) {
      vector<event> events;
      events.reserve(m + n);

      for (int i = 0; i < n; ++i)
         events.push_back(event(POINT, i, p[i].first.second));

      for (int i = 0; i < m; ++i)
         events.push_back(event(RECT, i, rect[i].second.second));

      sort(events.begin(), events.end());

      SegmentTree t(2 * k + 10);

      for (vector<event>::iterator it = events.begin(); it != events.end(); ++it) 
         if (it->type == POINT) 
            t.insert(p[it->index].first.first + k, it->y + k, it->index);
         else {
            border_point[rot][it->index] = t.query(rect[it->index].first.first + k, rect[it->index].first.second + k);
            //if (rot == 0)
            //   cout << it->index << " -- " << border_point[rot][it->index] << endl;
         }

      rotate_points(p);
      rotate_rects(rect);
   }
   
   // we've got all the info we need :)
   VI border(4);
   for (int i = 0; i < m; ++i) {
      LL res = 0;
      for (int rot = 0; rot < 4; ++rot)
         border[rot] = border_point[rot][i];
      swap(border[0], border[2]);
      swap(border[1], border[3]);
      if (DBG) cout  << i << " " << toString(p[border[0]]) << " " 
                     << toString(p[border[1]]) << " " 
                     << toString(p[border[2]]) << " " << toString(p[border[3]]) << endl;
      for (int rot = 0; rot < 4; ++rot) 
         res += upper_right_area[rot][border[rot]][border[(rot + 1) % 4]];

      for (int rot = 0; rot < 4; rot += 2) 
         res += triangle_area(p[border[rot]].first, p[border[(rot + 1) % 4]].first,p[border[(rot + 2) % 4]].first);

      cout << res / 2 << "." << (res % 2 == 0 ? "0" : "5") << endl;
   }

   return 0;
}	
