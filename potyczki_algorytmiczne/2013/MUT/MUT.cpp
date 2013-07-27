#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

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

const int INF = int(1e9);
int DBG = 0;

// number of random hash functions
const int M = 72;

const int primes_no = 9 * 8;
const int primes[] = {  979683989, 979683997, 979684001, 979684021, 979684031, 979684049, 979684051, 979684067, 
                        980266181, 980266201, 980266219, 980266241, 980266333, 980266379, 980266403, 980266423, 
                        976193843, 976193851, 976193891, 976193921, 976193927, 976193929, 976193957, 976193963, 
                        969140027, 969140041, 969140089, 969140099, 969140111, 969140113, 969140129, 969140143, 
                        978454441, 978454453, 978454493, 978454511, 978454513, 978454531, 978454549, 978454553, 
                        976599137, 976599181, 976599191, 976599209, 976599257, 976599263, 976599271, 976599277, 
                        962028763, 962028773, 962028791, 962028839, 962028863, 962028883, 962028887, 962028901, 
                        962864521, 962864527, 962864533, 962864549, 962864563, 962864587, 962864593, 962864599, 
                        970742081, 970742107, 970742111, 970742137, 970742141, 970742161, 970742173, 970742189,};

int P;
LL X = 6e5 + 37;

struct hash {
   int n;
   VI h;
   VI pow_x;
   hash(VI& a, VI& hash_function) : n((int) a.size()), h(VI((int) a.size())), pow_x(VI((int) a.size() + 1)) {
      h[n - 1] = hash_function[a[n - 1]];
      for (int i = n - 2; i >= 0; --i) {
         h[i] = (int) ((h[i + 1] * X + hash_function[a[i]]) % P);
         //assert(h[i] >= 0);
      }
      pow_x[0] = 1;
      for (int i = 1; i <= n; ++i) {
         pow_x[i] = (int) ((pow_x[i - 1] * X) % P);
         //assert(pow_x[i] >= 0);
      }
   }
   int query(int i, int j) {
      int res;
      if (j == n - 1)
         res = h[i];
      else 
         res = (int) (h[i] + P - (LL(h[j + 1]) * pow_x[j - i + 1]) % P) % P;
      return res;
   }
};

enum STATUS {MAYBE, YES, NO};

struct query {
   int a,b,l;
   int from, to;
   int num;
   STATUS status; 
};

// return max value after scaling
int rescale(vector<VI>& u) {
   VI values;
   values.reserve(u[0].size() + u[1].size());

   for (int q = 0; q < 2; ++q)
      for (VI::iterator it = u[q].begin(); it != u[q].end(); ++it)
         values.push_back(*it);
   sort(values.begin(), values.end());
   values.erase(unique(values.begin(), values.end()), values.end());

   for (int q = 0; q < 2; ++q)
      for (VI::iterator it = u[q].begin(); it != u[q].end(); ++it) {
         VI::iterator lit = lower_bound(values.begin(), values.end(), *it);
         *it = (int) (lit - values.begin());
      }
   return values.back();
}

void read_sequence(VI& u) {
   int n;
   scanf("%d", &n);
   u = VI(n);
   for (int i = 0; i < n; ++i)
      scanf("%d", &u[i]);
}

int main() {

   unsigned int seed = (unsigned) time(0);
   seed = 17;
   srand(seed);
   P = primes[rand() % primes_no];

   vector<VI> u(2);
   for (int i = 0; i < 2; ++i)
      read_sequence(u[i]);

   int range = rescale(u) + 1;

   /*for (int q = 0; q < 2; ++q) {
      for (int i = 0; i < (int)u[q].size(); ++i)
         cout << u[q][i] << " ";
      cout << endl;
   }*/

   VI id(range);
   for (int i = 0; i < range; ++i)
      id[i] = i;
   hash  h1(u[0], id),
         h2(u[1], id);

   int q;
   scanf("%d", &q);
   vector<query> Q(q);
   for (int i = 0; i < q; ++i)
      scanf("%d %d %d", &Q[i].a, &Q[i].b, &Q[i].l);

   //cerr << range << endl;
   // positions[i] - all positions of value i in u[1], sorted increasinly
   vector<VI> positions(range);
   for (int i = 0, n_ = (int) u[1].size(); i < n_; ++i)
      positions[u[1][i]].push_back(i);
   for (int i = 0; i < range; ++i)
      positions[i].push_back(INF);

   for (int i = 0; i < q; ++i) {
      Q[i].status = MAYBE;
      Q[i].num = i;

      --Q[i].a; 
      --Q[i].b;

      //cout << Q[i].a << " " << Q[i].b << " " << Q[i].l << endl;
      //cout << u[0][Q[i].a] << " " << u[0][Q[i].a + Q[i].l - 1] << endl;
      //cout << u[1][Q[i].b] << " " << u[1][Q[i].b + Q[i].l - 1] << endl;

      if (h1.query(Q[i].a, Q[i].a + Q[i].l - 1) == h2.query(Q[i].b, Q[i].b + Q[i].l - 1)) {
         Q[i].status = YES;
      }
      else {
         // binary search for first difference
         int left = 0, right = Q[i].l - 1;
         while (left < right) {
            //cout << "left = " << left << " right = " << right << endl;
            int s = (left + right) / 2;
            if (h1.query(Q[i].a, Q[i].a + s) == h2.query(Q[i].b, Q[i].b + s)) {
               //cout << h1.query(Q[i].a, Q[i].a + s) << endl;
               //cout << h2.query(Q[i].b, Q[i].b + s) << endl;
               //cout << "WRONG\n";
               left = s + 1;
            }
            else
               right = s;
         }
         //assert(u[0][Q[i].a + right] != u[1][Q[i].b + right]); 
         /*if (right > 0) {
            //cout << i << " " << right << endl;
            assert(u[0][Q[i].a + right - 1] == u[1][Q[i].b + right - 1]);
         }*/
         Q[i].from = u[0][Q[i].a + right];
         Q[i].to = u[1][Q[i].b + right];

         // if Q[i].from is somewhere inside segment u[1][Q[i].b] ... u[1][Q[i].b + Q[i].l - 1]
         // then we know the answer is "NIE" since all occurences must be transformed
         VI::iterator lit = lower_bound(positions[Q[i].from].begin(), positions[Q[i].from].end(), Q[i].b);
         //assert(lit != positions[Q[i].from].end());
         if (*lit <= Q[i].b + Q[i].l - 1)
            Q[i].status = NO;

         //cout << i << " " << Q[i].from << " " << Q[i].to << endl;
      }
   }
   
   int remaining = q;

   for (int i = 0; i < remaining; )
      if (Q[i].status != MAYBE) {
         swap(Q[i], Q[remaining - 1]);
         --remaining;
      }
      else
         ++i;
   VI hash_function(range);
   for (int rep = 0; rep < M && remaining > 0; ++rep) {
      // random hash function
      for (int i = 0; i < range; ++i)
         hash_function[i] = rand() % 2;

      hash hash1(u[0], hash_function), hash2(u[1], hash_function);
      for (int i = 0; i < remaining; ++i) 
         if (hash_function[Q[i].from] == hash_function[Q[i].to] && hash1.query(Q[i].a, Q[i].a + Q[i].l - 1) != hash2.query(Q[i].b, Q[i].b + Q[i].l - 1)) {
            Q[i].status = NO;
            //DBG = 1;
            //cout << "NO " << Q[i].num << " " << Q[i].from << " " << Q[i].to << " " << hash1.query(Q[i].a, Q[i].a + Q[i].l - 1) << 
            //        " " << hash2.query(Q[i].b, Q[i].b + Q[i].l - 1) << endl;
         }

      for (int i = 0; i < remaining; )
         if (Q[i].status != MAYBE) {
            swap(Q[i], Q[remaining - 1]);
            --remaining;
         }
         else
            ++i;
   }

   VI res(q);
   for (int i = 0; i < q; ++i)
      if (Q[i].status == NO)
         res[Q[i].num] = 0;
      else
         res[Q[i].num] = 1;

   for (VI::iterator it = res.begin(); it != res.end(); ++it)
      if (*it)
         printf("TAK\n");
      else
         printf("NIE\n");

   return 0;
}
