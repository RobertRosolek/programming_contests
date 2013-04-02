#include <stdio.h>      
#include <ctype.h>
#include <math.h>

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <stack>
using namespace std;

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

const int DBG = 0, INF = 1000000000;

typedef double LD;

struct point {
  LD x,y,z;
  point (LD x = 0, LD y = 0, LD z = 0) : x(x), y(y), z(z) {}
  point (const point &p) :x(p.x), y(p.y), z(p.z) {}
  const point& operator=(const point &p) {
      x = p.x;
      y = p.y;
      z = p.z;
  }
};

struct line {
  point A,B;
  line (const point &A, const point &B) : A(A), B(B) {}  
};

struct vect {
  LD x,y,z;
  vect (LD x, LD y, LD z) : x(x), y(y), z(z) {}
  vect (const point &A, const point &B) : x(B.x - A.x), y(B.y - A.y), z(B.z - A.z) {}
};

struct surface {
  point A,B,C;
  surface(const point &A, const point &B, const point &C) : A(A), B(B), C(C) {}
};


// norma wektora
inline LD norm(const vect &v) {
  return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

// iloczyn wektorowy
inline vect vectProduct(const vect &u, const vect &v) {
  return vect(u.y*v.z - v.y*u.z, v.x*u.z - u.x*v.z, u.x*v.y - v.x*u.y);  
} 

// pole trojkata
inline LD triangleArea(const point &A, const point &B, const point &C) {
  return norm(vectProduct(vect(A,B), vect(A,C))) * 0.5;
}


// wyznacznik macierzy, ktorej wierszami są wektory
inline LD det(const vect &V1, const vect &V2, const vect &V3) {
  return V1.x * V2.y * V3.z + V1.y * V2.z * V3.x + V2.x * V3.y * V1.z
         - V3.x * V2.y * V1.z - V3.y * V2.z * V1.x - V2.x * V1.y * V3.z;
}


// po ktorej strony plaszczyzny znajduje sie punkt - 0 jesli lezy na plaszczyznie
inline LD pointSurfacePosition(const surface &S, const point &p) {
  vect V1(S.B,S.A), V2(S.C,S.A), V3(p,S.A);
  return det(V1,V2,V3);
}

int main() {
  ios_base::sync_with_stdio(0);
  cout << triangleArea(point(1,2,3), point(0,-1,-1), point(1,0,1)) << endl;
  surface S(point(0,0,0), point(0,0,1), point(0,1,0));
  cout << pointSurfacePosition(S,point(2,2,2)) << endl;
  return 0;
}
