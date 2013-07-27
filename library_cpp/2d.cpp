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

// ****************
// ****  Typy  ****
// ****************

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> PII;
typedef double LD;

// *****************
// ****  Stale  ****
// *****************

const int DBG = 0, INF = 1e9;
const LD EPS = 1e-8, PI = 2 * asinl(1);

// **************************
// ****  Funkcje ogolne  ****
// **************************

LD abs(LD x) {
	if (x < 0)
		return -x;
	return x;
}

bool isZero(LD x) {
  return -EPS < x && x < EPS;
}

// wyznacznik macierzy
// | a b c |
// | d e f |
// | g h i |
inline LD det(LD a, LD b, LD c, LD d, LD e, LD f, LD g, LD h , LD i) {
	return a*e*i + b*f*g + d*h*c - g*e*c - a*h*f - b*d*i;
}

//	wyznacznik macierzy
//	| a b 1 |
//  | c d 1 |
//  | e f 1 |
inline LD det(LD a, LD b, LD c, LD d, LD e, LD f) {
	return det(a,b,1,c,d,1,e,f,1);
}

// *****************
// ****  Punkt  ****
// *****************

struct point {

  LD x,y;

  point (LD x = 0, LD y = 0) : x(x), y(y) {}
  point (const point &p) : x(p.x), y(p.y) {}

  const point& operator= (const point &p) {
      x = p.x;
      y = p.y;
      return *this;
  }

  bool operator< (const point &p) const {
    if (x != p.x)
      return x < p.x;
    return y < p.y;
  }
};

ostream& operator << (ostream& out, const point &p) {
  out << "(" << p.x << "," << p.y << ")";
  return out;
}

inline point operator+ (const point &p, const point &q) {
  return point(p.x + q.x, p.y + q.y);
}

inline point operator- (const point &p, const point &q) {
  return point(p.x - q.x, p.y - q.y);
}

inline point operator* (const LD &a, const point &p) {
  return point(p.x * a, p.y * a);
}

inline point operator* (const point &p, const LD &a) {
	return point(p.x * a, p.y * a);
}

inline bool operator== (const point &p, const point &q) {
  return isZero(p.x - q.x) && isZero(p.y - q.y);
}

inline bool operator!= (const point &p, const point &q) {
  return !isZero(p.x - q.x) || !isZero(p.y - q.y);
}


inline LD dist (const point &p, const point &q) {
  return sqrt( (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y) );
}

inline LD scalarProduct(const point &p, const point &q) {
  return p.x * q.x + p.y * q.y;
}

inline LD norm (const point &p) {
  return dist(point(0,0),p);
}

// obrot wzgledem poczatku ukladu przeciwny do wskazowek zegara
inline point rotateOrigin (LD alpha, const point &p) {
  LD sinus = sinl(alpha), cosinus = cosl(alpha);
  return point(p.x * cosinus - p.y * sinus, p.x * sinus + p.y * cosinus);
}

// dowolny obrot o srodku w O
inline point rotate(LD alpha, const point &p, const point &O) {
  return O + rotateOrigin(alpha, p - O);
}

// obrot o 90 wzgledem srodka, przeciwnie do wskazowek
inline point rotateRightOrigin (const point &p) {
  return point(-p.y, p.x);
}

// obrot o 90 stopni przeciwnie do wskazowek
inline point rotateRight (const point &p, const point &O) {
  return rotateRightOrigin(p - O) + O;
}

inline LD det(const point &p, const point &q, const point &r) {
  return det(p.x, p.y, q.x, q.y, r.x, r.y);
}


// > 0 jeśli p jest na prawo od wektora od q do r, 0 jeśli wspóliniowy, < 0 wpp
inline LD getPosition(const point &p, const point &q, const point &r) {
  return det(r,q,p);
}

// czy 3 punkty sa wspolliniowe
inline bool colinear(const point &p, const point &q, const point &r) {
	return isZero(getPosition(p,q,r));
}

// czy punkt p znajduje sie wewnatrz trojkata ABC (punkty w kolejnosci przeciwnej do wskazowek)
inline bool insideTriangle(const point &p, const point &A, const point &B, const point &C) {
	assert(A != B && B != C && C != A);
	//cout << A << " " << B << " " << C << endl;
	//cout << "BONUS " << getPosition(A,A,B) << " " << getPosition(A,B,C) << " " <<  getPosition(A,C,A) << " END\n";
	return (getPosition(p,A,B) < EPS) && (getPosition(p,B,C) < EPS) && (getPosition(p,C,A) < EPS);
}

// ***************************
// ****  Prosta, Odcinek  ****
// ***************************

// odcinek AB
struct segment {

	point A,B;

	segment () {}
	segment (const point &A, const point &B) : A(A), B(B) {}
	segment (const segment &s) : A(s.A), B(s.B) {}

	const segment& operator = (const segment &s) {
		A = s.A;
		B = s.B;
		return *this;
	}

};

// prosta przechodzaca przez punkty A i B
struct line {

  point A,B;

  line ()  {}
  line (const point &A, const point &B) : A(A), B(B) {}
  line (const line &l) : A(l.A), B(l.B) {}
	line (const segment &s) : A(s.A), B(s.B) {}

  const line& operator= (const line &l) {
    A = l.A;
    B = l.B;
    return *this;
  }

};

// prosta o rownaniu Ax + By + C = 0
struct eqLine {

  LD A,B,C;

  eqLine(LD A, LD B, LD C) : A(A), B(B), C(C) {}
  eqLine(const eqLine &l) : A(l.A), B(l.B), C(l.C) {}
  eqLine(const line &l) : A(l.B.y - l.A.y), B(-l.B.x + l.A.x), C(-A * l.A.x - B * l.A.y) {}
	eqLine(const segment &s) : A(s.B.y - s.A.y), B(-s.B.x + s.A.x), C(-A * s.A.x - B * s.A.y) {}
  eqLine(const point &p, LD alpha); // prosta przecinajaca os OX pod katem alpha
																		// przechodzaca przez punkt p

  const eqLine& operator= (const eqLine &l) {
    A = l.A;
    B = l.B;
    C = l.C;
    return *this;
  }
};

// implementacja konstruktora
eqLine::eqLine(const point &p, LD alpha) {

  assert(alpha >= 0 && alpha < 2 * PI);

  if (isZero(alpha) || isZero(alpha - PI)) {
    A = 0;
    B = 1;
    C = -p.y;
  }
  else if (isZero(alpha - PI * 0.5) || isZero(alpha - PI * 1.5)) {
    A = 1;
    B = 0;
    C = -p.x;
  }
  else {
    A = - tan(alpha * PI / 180.);
    B = 1;
    C = -A * p.x - p.y;
  }

}

ostream& operator << (ostream& out, const eqLine &l) {
  out << "[" << l.A << "x + " << l.B <<  "y + " << l.C << " = 0]";
  return out;
}

// zwraca czy proste nie sa rownolegle (czyli falsz gdy rowne)
bool cross(const eqLine &l1, const eqLine &l2) {
  return l1.A * l2.B != l1.B * l2.A;
}

// musi byc cross(l1,l2) == true
point crossPoint(const eqLine &l1, const eqLine &l2) {

  LD w = l1.A * l2.B - l1.B * l2.A;
	LD wX = -l1.C * l2.B  + l2.C * l1.B;
	LD wY = -l1.A * l2.C + l2.A * l1.C;

  return point(wX / w, wY / w);
}

bool onLine(const eqLine &l, const point &p) {
	return isZero(l.A * p.x + l.B * p.y + l.C);
}


// czy punkty p i q sa po tej samej stronie prostej l
bool sameSide(const point &p, const point &q, const eqLine &l) {
	LD u = l.A * p.x + l.B * p.y + l.C;
	LD v = l.A * q.x + l.B * q.y + l.C;
	return isZero(u) || isZero(v) || (u > 0 == v > 0);
}

ostream& operator << (ostream& out, const line &l) {
  out << "[" << l.A << "," << l.B << "]";
  return out;
}

// rzut punktu na prosta
inline point projection(const point& p, const line& l) {
  return (scalarProduct(p - l.A, l.B - l.A) / scalarProduct(l.A - l.B,l.A - l.B)) * (l.B - l.A)  + l.A;
}

// odleglosc punktu od prostej
inline LD dist(const point &p, const line &l) {
  return dist(p, projection(p, l));
}

// Prosta prostopadla do wektora D przez dany punkt p
line right (const point &p, const point &D) {
  return line(p, p + point(D.y, -D.x));
}

// symetralna odcinka pq
line bisector (const point &p, const point &q) {
	return right(0.5 * (p + q), q - p);
}


// zwraca czy proste nie sa rownolegle (czyli false dla rownych)
bool cross(const line &l1, const line &l2 ) {
	return cross(eqLine(l1), eqLine(l2));
}

// przeciecie prostych (nie moga byc rownolegle)
point crossPoint(const line &l1, const line &l2) { // UNTESTED
	return crossPoint(eqLine(l1), eqLine(l2));
}

// czy punkty p i q sa po tej samej stronie prostej l
bool sameSide(const point &p, const point &q, const line &l) {
	LD u = getPosition(p,l.A,l.B), v = getPosition(q,l.A,l.B);
	return isZero(u) || isZero(v) || (u > 0 == v > 0);
}

ostream& operator << (ostream& out, const segment &s) {
  out << "[" << s.A << "," << s.B << "]";
  return out;
} 

inline LD length (const segment &s) {
  return dist(s.A, s.B);
}

// czy punkt lezacy na prostej wyznaczonej przez s
// lezy na odcinku s
inline int inside (const point &p, const segment &s) {
  return min(s.A.x, s.B.x) - EPS <= p.x && p.x <= max(s.A.x, s.B.x) + EPS &&
         min(s.A.y, s.B.y) - EPS <= p.y && p.y <= max(s.A.y, s.B.y) + EPS;
}


// czy odcinki przecinaja sie w 1 punkcie
bool cross(const segment &s1, const segment &s2) {

	if (! cross(line(s1), line(s2)))
		return false;

	point x = crossPoint(eqLine(s1), eqLine(s2));

	return inside(x, s1) && inside(x, s2);

}

// punkt przeciecia odcinkow - musi byc cross(s1,s2) == true
point crossPoint(const segment &s1, const segment &s2) {
	return crossPoint(eqLine(s1), eqLine(s2));
}

// czy odcinek przecina sie z prosta (false dla odcinka na prostej)
bool cross(const segment &s, const line &l) {

	if (! cross(line(s), l))
		return false;

	point x = crossPoint(line(s), l);

	return inside(x,s);
}

// odleglosc punktu od odcinka
inline LD distSeg(const point &p, const segment &s) {
  point q = projection(p,line(s));
  if (inside(q,s))
    return dist(p,q);
  return min( dist(p, s.A), dist(p, s.B) );
}

// punkt z danego odcinka ktory jest najblizszy do danego punktu
inline point closestPoint(const point &p, const segment &s) {
	point q = projection(p, line(s));
	if (inside(q,s))
		return q;
	if (dist(p,s.A) < dist(p, s.B))
		return s.A;
	return s.B;
}

// punkt przeciecia odcinka z prosta - musi byc cross(s,l) == true
point crossPoint(const segment &s, const line &l) {
	return crossPoint(line(s), l);
}

// *****************
// ****  Okrag  ****
// *****************

struct circle {

  point O;
  LD r;

  circle(const point &O, LD r) : O(O), r(r) {}
  circle(const circle &c) : O(c.O), r(c.r) {}
	circle(const point &A, const point &B, const point &C) { // A,B,C sa niewspolliniowe
		LD a = det(A,B,C),
		d = - det(scalarProduct(A,A), A.y, scalarProduct(B,B), B.y, scalarProduct(C,C), C.y),
		e = det(scalarProduct(A,A), A.x, scalarProduct(B,B), B.x, scalarProduct(C,C), C.x);
		O.x = - d / (2. * a);
		O.y = - e / (2. * a);
		r = dist(A,O);
	}

  const circle& operator= (const circle &c) {
    O = c.O;
    r = c.r;
    return *this;
  }
};

ostream& operator << (ostream& out, const circle &c) {
  out << "B[" << c.O << "," << c.r << "]";
  return out;
}

// sprawdza czy prosta przecina sie z okregiem
inline bool cross(const line &l, const circle &c) {
  return c.r >= dist(c.O, l);
}

// sprawdza czy punkt lezy na okregu
inline bool onCircle(const point &p, const circle &c) {
  return isZero(dist(p, c.O) - c.r);
}

inline LD inCircle(point &a, point &b, point &c, point &d) {
	return det(b.x,b.y,scalarProduct(b,b),c.x,c.y,scalarProduct(c,c),d.x,d.y,scalarProduct(d,d))
				-det(a.x,a.y,scalarProduct(a,a),c.x,c.y,scalarProduct(c,c),d.x,d.y,scalarProduct(d,d))
				+det(a.x,a.y,scalarProduct(a,a),b.x,b.y,scalarProduct(b,b),d.x,d.y,scalarProduct(d,d))
				-det(a.x,a.y,scalarProduct(a,a),b.x,b.y,scalarProduct(b,b),c.x,c.y,scalarProduct(c,c));
}

// wyznacza punkty przeciecia prostej z okregiem
// NIE DZIALA DLA STYCZNEJ PROSTEJ
int intersect(const line &l, const circle &c, point &A, point &B) {
  point M = projection(c.O, l);
  LD d = dist(M, c.O);
  if (d >= c.r)
    return 0;
  if (d < EPS) {
    A = c.O + (c.r / norm(l.B)) * l.B;
    B = c.O - (c.r / norm(l.B)) * l.B;
    return 2;
  }
  LD alpha = acosl(d / c.r);
  M = (c.r / d) * (M - c.O) + c.O;
  A = rotate(alpha, M, c.O);
  B = rotate(-alpha, M, c.O);
  return 2;
}

// sprawdza czy odcinek przecina się z okręgiem
inline int segmentCross(const segment &s, const circle &c) {
  point A, B;
  if (!intersect(line(s),c, A, B))
    return 0;
  return inside(A,s) || inside(B,s);
}

// styczne do okregu przez dany punkt, A i B to styczne
int tangentLines (const point &p, const circle &c, line &A, line &B) {
  if (onCircle(p,c)) { // styczna przez punkt na okregu jest styczna w tym punkcie
    A = B = right(p,c.O - p);
    swap(A.A, A.B);
    swap(B.A, B.B);
    return 1;
  }
  LD d = dist(p, c.O);
  if (d <= c.r)
    return 0;
  LD alpha = asinl(c.r / d);
  point temp = (sqrt(d*d - c.r*c.r) / d) * (c.O - p) + p;
  B = line(p, rotate(alpha, temp, p));
  A = line(p, rotate(-alpha, temp, p));
  return 2;
}

// dlugosc krotszego luku okregu wyznaczonego przez A i B
LD curveLength (const point &A, const point &B, const circle &c) {
  point P = A - c.O, Q = B - c.O;
  LD cosAlpha = scalarProduct(P, Q) / (c.r * c.r);
  LD alpha = acosl(cosAlpha);
  if (alpha < 0)
    alpha = - alpha;
  return c.r * min(alpha, 2 * PI - alpha);
}

// *********************
// ****  Algorytmy  ****
// *********************

// obiekt porownujący punkty polarnie względem punktu O
struct polarComparator {
  point O;
  polarComparator(const point &p = point(0,0)) : O(p) {}
  bool operator() (const point &p, const point &q) {
    LD d = det(O,p,q);
    if (isZero(d))
      return dist(p,O) > dist(q,O);   // najpierw bardziej odlegly punkt - pozniej usuwamy duplikaty i chcemy zostawic najbardziej odlegly punkt
    return d >= -EPS;
  }
};

// obiekt stwierdzajacy czy dwa punkty sa wspolliniowe z O
struct equalPolar {
  point O;
  equalPolar(const point &p = point(0,0)) : O(p) {}
  bool operator() (const point &p, const point &q) {
    return isZero(det(O,p,q));
  }
};

// sortuje punkty polarnie wokol punktu p
void sortPolar(const point &p, const vector<point> &W, vector<point> &res) {
  vector<point> A, B, C;
  FORE(it,W) {
    if (it->y < p.y - EPS)
      A.PB(*it);
    else if (isZero (it->y - p.y))
      C.PB(*it);
    else
      B.PB(*it);
  }
  sort(C.begin(), C.end());
  while (C.size() && C.back().x >= p.x - EPS) {
    if (! isZero(C.back().x - p.x))
      res.PB(C.back());
    C.pop_back();
  }
  polarComparator comparator(p);
  sort(B.begin(), B.end(), comparator);
  FORE(it,B)
    res.PB(*it);
  while (C.size()) {
    res.PB(C.back());
    C.pop_back();
  }
  sort(A.begin(), A.end(), comparator);
  FORE(it,A)
    res.PB(*it);
}



// algorytm Grahama
void convexHull(const vector<point> &V, vector<point> &res) {
  vector<point> W = V;
  sort(W.begin(), W.end());
  W.erase(unique(W.begin(), W.end()), W.end()); // usuwamy duplikaty punktow
  polarComparator comparator(W[0]);
  sort(++W.begin(), W.end(), comparator);
  equalPolar equalComparator(W[0]);
  W.erase(unique(++W.begin(), W.end(), equalComparator), W.end()); // usuwamy duplikaty wzgledem wspolrzednych polarnych i zostawiamy te najodleglejsze
  if (W.size() <= 3) {
    res = W;
    return;
  }
  res.PB(W[0]);
  res.PB(W[1]);
  res.PB(W[2]);
  FOR(i,3,W.size() - 1) {
    while (res.size() > 1 && det(res.back(), W[i], res[res.size() - 2]) <= EPS)
      res.pop_back();
    res.PB(W[i]);
  }
}

// zaburza uklad punktow przesuwajac je w losowym kierunku maksymalnie o eps w normie supremum
void perturb(vector<point> &V, LD eps) {
  static bool first = true;
  if (first)
    srand( (unsigned)time( NULL ) );
  first = false;
  FORE(it,V) {
    LD dx = (rand() % 1000) - 500;
    dx *= eps / 1000.0;
    LD dy = (rand() % 1000) - 500;
    dy *= eps / 1000.0;
    it->x += dx;
    it->y += dy;
  }
}

// ********************
// ****  Wielokat  ****
// ********************

// obwod wielokata
LD perimeter(const vector<point> &W) {
  LD res = dist(W[0], W.back());
  FOR(i, 1, W.size() - 1)
    res += dist(W[i], W[i - 1]);
  return res;
}

// pole wielokata
LD area(const vector<point> &W) {

	int n = W.size();

	if (n < 3)
		return 0;

	LD res = W[n - 1].x * W[0].y - W[0].x * W[n - 1].y;

	REP(i, n - 1)
		res += W[i].x * W[i + 1].y - W[i + 1].x * W[i].y;

	return res * 0.5;
}


// odleglosc punktu od (obwodu) wielokata
inline LD dist(const point &p, const vector<point> &W) {
  LD res = distSeg(p, segment(W[0], W.back()));
  FOR(i, 1, W.size() - 1)
    res = min(res, distSeg(p, segment(W[i], W[i - 1])));
  return res;
}



// czy punkt jest wewnątrz wielokąta wypuklego (punkty w wielokacie musza byc w kolejnosci przeciwnej do wskazowek zegara
inline bool insideConvex(const point &p, const vector<point> &W) {
  REP(i,W.size()) {
    int j = (i + 1) % W.size();
    if (getPosition(p,W[i],W[j]) > -EPS)
      return false;
  }
  return true;
}


// przecięcie wielokąta wypuklego z polplaszczyzna
// wyznaczona przez prosta l i punkt p
void crossPolyPlane(vector<point> &V, const line &l, const point &p) {

	int n = V.size();

	vector<point> W;

	REP(i,n) {

		int j = (i + n - 1) % n;

		if (cross(segment(V[j], V[i]), l)) {

			point x = crossPoint(segment(V[j], V[i]), l);

			if (x != V[j] && x != V[i])
				W.PB(x);

		}

		W.PB(V[i]);

	}

	V.clear();

	FORE(it,W)
		if (sameSide(*it,p,l))
			V.PB(*it);

}

/*struct three {

	int a,b,c;

	three (int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c) {}
	three (const three &t) : a(t.a), b(t.b), c(t.c) {}

	three& operator= (const three &t) {
		a = t.a; b = t.b; c = t.c;
		return *this;
	}

	bool operator< (const three &t) const {
		if (a != t.a)
			return a < t.a;
		if (b != t.b)
			return b < t.b;
		return c < t.c;
	}

	bool contains(int x) const {
		return a == x || b == x || c == x;
	}

	int getThird(int x, int y) const {
		if (a != x && a != y)
			return a;
		if (b != x && b != y)
			return b;
		return c;
	}

};

const int MAXN = 2 * 10e5;

VI W[MAXN];  // wynikowy graf triangulacji

int n;

vector<pair<point,int> > P; // druga wspolrzedna zawiera numer punktu w V
vector<three> T; // trojkaty triangulacji
vector<bool> act; // czy trojkat T[i] jest aktywny
vector<list<int> > inPoints; // inPoints[i] - numery (w P) punktow wewnatrz trojkata T[i]
vector<list<int> > linkTree; // linkTree[i] - numery trojkatow zawierajacych punkt P[i].ST

void swapTest(int p, int a, int b) {
	if (a < 3 && b < 3)  // krawedz zewnetrzna
		return;

	int d = -1; // pierwszy punkt na prawo od odcinka ab
				 //(drugi punkt poza p ktory jest w trojkacie z punktami a i b)

	FORE(it,linkTree[a]) {
		if (T[*it].contains(b) && ! T[*it].contains(p)) {
			assert(T[*it].contains(a));
			d = T[*it].getThird(a,b);
		}
	}

	assert (d != -1);

	if (inCircle(P[p].ST,P[a].ST,P[b].ST,P[d].ST) < 0) {

		// zamien krawedz ab na pd

		T.PB(three(p,a,d));
		T.PB(three(p,d,b));
		act.PB(true); act.PB(true);

		REP(j,2)
			inPoints.PB(list<int>());

		list<int>::iterator it = linkTree[a].begin();
		while (it != linkTree[a].end()) {
			if (! T[*it].contains(b))
				++it;
			else {
				assert(T[*it].contains(a));
				assert(T[*it].contains(p) || T[*it].contains(d));
				act[*it] = false;

				FORE(jt, inPoints[*it]) if (*jt != a && *jt != b && *jt != p && *jt != d)
					FORD(j,T.size() - 1, T.size() - 2)
						if (insideTriangle(P[*jt].ST, P[T[j].a].ST, P[T[j].b].ST, P[T[j].c].ST)) {
							inPoints[j].PB(*jt);
							linkTree[*jt].clear();
							linkTree[*jt].PB(j);
						}
				linkTree[a].erase(it++);
			}
		}

		it = linkTree[b].begin();
		while (it != linkTree[b].end())
			if (T[*it].contains(a))
				linkTree[b].erase(it++);
			else
				++it;

		it = linkTree[p].begin();
		while (it != linkTree[p].end())
			if (T[*it].contains(a) && T[*it].contains(b))
				linkTree[p].erase(it++);
			else
				++it;

		it = linkTree[d].begin();
		while (it != linkTree[d].end())
			if (T[*it].contains(a) && T[*it].contains(b))
				linkTree[d].erase(it++);
			else
				++it;

		inPoints[T.size() - 2].PB(p); inPoints[T.size() - 2].PB(a); inPoints[T.size() - 2].PB(d);
		inPoints[T.size() - 1].PB(p); inPoints[T.size() - 1].PB(b); inPoints[T.size() - 1].PB(d);
		linkTree[a].PB(T.size() - 2);
		linkTree[p].PB(T.size() - 1); linkTree[p].PB(T.size() - 2);
		linkTree[b].PB(T.size() - 1);
		linkTree[d].PB(T.size() - 1); linkTree[d].PB(T.size() - 2);

		swapTest(p,a,d);
		swapTest(p,d,b);
	}
}

// oczekiwany czas dzialania O(n lgn)
void triangulationDelaunay(const vector<point> &V) {

	static bool first = true;
  if (first)
    srand( (unsigned)time( NULL ) );
  first = false;

	LD M = 0;

	FORE(it,V)
		M = max(M,max(abs(it->y), abs(it->x)));

	// trojkat ABC zawiera wszystkie dane punkty
	point A(-3 * M, -3 * M), B(3 * M, 0), C (0, 3 * M);



	REP(i,V.size())
		P.PB(MP(V[i], i));

	random_shuffle(ALL(P));
	P.PB(MP(C, - 3)); P.PB(MP(B,-2)); P.PB(MP(A, - 1));
	reverse(ALL(P));

	n = P.size();

	linkTree = vector<list<int> >(n);

	T.PB(three(0,1,2));
	act.PB(true);
	inPoints.PB(list<int>());
	REP(i,n)
		inPoints[0].PB(i);
	REP(i,n)
		linkTree[i].PB(0);

	// dodanie punktu P[i].ST
  FOR(i,3,n - 1) {

		assert(linkTree[i].size() == 1);

		int k = *(linkTree[i].begin()); // trojkat zawierajacy punkt P[i].ST

		act[k] = false;

		T.PB(three(i,T[k].a, T[k].b));		assert(i != T[k].a && i != T[k].b && T[k].a != T[k].b);
		T.PB(three(i,T[k].b, T[k].c));    assert(i != T[k].b && i != T[k].c && T[k].b != T[k].c);
		T.PB(three(i,T[k].c, T[k].a));    assert(i != T[k].c && i != T[k].a && T[k].c != T[k].a);
		act.PB(true); act.PB(true); act.PB(true);
		REP(j,3)
			inPoints.PB(list<int>());

		FORE(it, inPoints[k]) if (! T[k].contains(*it) && *it != i) {
			FORD(j,T.size() - 1, T.size() - 3)
				if (insideTriangle(P[*it].ST, P[T[j].a].ST, P[T[j].b].ST, P[T[j].c].ST)) {
					inPoints[j].PB(*it);
					linkTree[*it].clear();
					linkTree[*it].PB(j);
				}
		}

		inPoints[T.size() - 1].PB(i); inPoints[T.size() - 1].PB(T[k].c); inPoints[T.size() - 1].PB(T[k].a);
		inPoints[T.size() - 2].PB(i); inPoints[T.size() - 2].PB(T[k].b); inPoints[T.size() - 2].PB(T[k].c);
		inPoints[T.size() - 3].PB(i); inPoints[T.size() - 3].PB(T[k].a); inPoints[T.size() - 3].PB(T[k].b);

		linkTree[i].clear();
		list<int>::iterator it = linkTree[T[k].a].begin();
		while (it != linkTree[T[k].a].end())
			if (T[*it].contains(T[k].b) && T[*it].contains(T[k].c)) {
				linkTree[T[k].a].erase(it);
				break;
			}
			else
				++it;
		it = linkTree[T[k].b].begin();
		while (it != linkTree[T[k].b].end())
			if (T[*it].contains(T[k].a) && T[*it].contains(T[k].c)) {
				linkTree[T[k].b].erase(it);
				break;
			}
			else
				++it;
		it = linkTree[T[k].c].begin();
		while (it != linkTree[T[k].c].end())
			if (T[*it].contains(T[k].a) && T[*it].contains(T[k].b)) {
				linkTree[T[k].c].erase(it);
				break;
			}
			else
				++it;

		REP(j,3)
			linkTree[i].PB(T.size() - j - 1);

		linkTree[T[k].a].PB(T.size() - 1); linkTree[T[k].a].PB(T.size() - 3);
		linkTree[T[k].b].PB(T.size() - 2); linkTree[T[k].b].PB(T.size() - 3);
		linkTree[T[k].c].PB(T.size() - 1); linkTree[T[k].c].PB(T.size() - 2);

		swapTest(i,T[k].a, T[k].b);
		swapTest(i,T[k].b,T[k].c);
		swapTest(i,T[k].c,T[k].a);

	}

	// transformacja triangulacji do grafu

	FOR(i,3,n - 1) {
		FORE(it,linkTree[i]) {
			assert(act[*it]);
			if (T[*it].a != i && T[*it].a > 2)
				W[P[i].ND].PB(P[T[*it].a].ND);
			if (T[*it].b != i && T[*it].b > 2)
				W[P[i].ND].PB(P[T[*it].b].ND);
			if (T[*it].c != i && T[*it].c > 2)
				W[P[i].ND].PB(P[T[*it].c].ND);
		}

		sort(ALL(W[P[i].ND]));
		W[P[i].ND].erase(unique(ALL(W[P[i].ND])), W[P[i].ND].end());
	}

}*/


int main() {
  	ios_base::sync_with_stdio(0);
  	cout.setf(ios::fixed);

	return 0;
}
