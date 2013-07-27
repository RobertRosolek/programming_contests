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

const int DBG = 0, INF = int(1e9);

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   LL n;
   int k;
   cin >> n >> k;

   VI a(k);
   for (int i = 0; i < k; ++i) 
      cin >> a[i];

   // Binary search for last moment in which 
   // all guys are doing at least one compartment.
   // Equivalently this is the time first guy finishes
   // his whole work (the are no compartments left to check out)
   // This moment is at most max(a[0], ..., a[k]) time away
   // from end of whole procedure
   LL left = 0, right = n * ( *min_element(a.begin(), a.end()));
   while (left < right) {
      LL s = (left + right + 1) / 2;

      LL compartments_no = 0;
      for (VI::iterator it = a.begin(); it != a.end(); ++it)
         compartments_no += (s + *it - 1) / *it; // ceil(s / *it)
      
      if (compartments_no <= n)
         left = s;
      else
         right = s - 1;
   }
   LL t = left;

   //cout << t << endl;
      
   priority_queue<PII, vector<PII>, greater<PII> > Q;

   for (int i = 0; i < k; ++i)
      if (t % a[i] == 0)
         Q.push(make_pair(a[i], -i));
      else
         Q.push(make_pair(t % a[i], -i));

   vector<LL> res(k, -1);
   int rem = k;
   // next compartment to take in backward simulation
   LL cur_compartment = n;

   // there might be some guys that start their last compartment
   // at time t
   LL compartments_started_before_t = 0;
   for (VI::iterator it = a.begin(); it != a.end(); ++it)
      compartments_started_before_t += (t + *it - 1) / *it;
   LL compartments_left = n - compartments_started_before_t;
   cur_compartment -= compartments_left;
   assert(compartments_left >= 0);
   for (int i = 0; i < k && compartments_left > 0; ++i)
      if (t % a[i] == 0) {
         res[i] = n - compartments_left + 1;
         --rem;
         --compartments_left;
      }

   // backward simulation from time t
   while (rem > 0) {
      int cur_t = Q.top().first;
      while (Q.top().first == cur_t) {
         int i = -Q.top().second;
         if (res[i] == -1) {
            res[i] = cur_compartment;
            --rem;
            if (rem == 0)
               break;
         }
         --cur_compartment;
         //assert(cur_compartment >= 0);
         Q.pop();
         Q.push(make_pair(cur_t + a[i], -i));
      }
   }

   for (int i = 0; i < k; ++i)
      if (i < k - 1)
         cout << res[i] << " ";
      else
         cout << res[i] << endl;


   return 0;
}	
