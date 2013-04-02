int gcd(int p, int q, int *x, int *y) {
	int x1,y1;                     
  int g;                         
  if (q > p) return gcd(q,p,y,x);
  if (q == 0) {
  	*x = 1;
    *y = 0;
    return p;
  }
  g = gcd(q, p%q, &x1, &y1);
  *x = y1;
  *y = (x1 - (p/q)*y1);
  return g;
}
