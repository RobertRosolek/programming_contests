#include <iomanip>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;

/* CHECKLIST
 * 1) long longs
 * 2) lower_bound etc - out of bound
 * 3) multiple inputs- data structures cleared
 * */

const int DBG = 0, INF = int(1e9);

struct player {
   string name;
   int shot, height, minutes, draft;
   player() : minutes(0) {}
};

typedef function<bool(const player&, const player&)> comparator;

template<class Funct>
comparator functorToComparator(const Funct& f) {
   return [&f] (const player& p1, const player& p2) { return f(p1) < f(p2); };
}

template<class Comparator>
player popMinimum(vector<player>& players, Comparator&& comp) {
   assert(!players.empty());
   auto it = min_element(players.begin(), players.end(), comp);
   player p = *it;
   players.erase(it);
   return p;
}

template<class Comparator>
player movePlayer(vector<player>& from, vector<player>& to, Comparator&& comp) {
   player p = popMinimum(from, comp);
   to.push_back(p);
   return p;
}

int main() {
   ios_base::sync_with_stdio(0);
   cout.setf(ios::fixed);

   int T;
   cin >> T;
   for (int q = 0; q < T; ++q) {
      // read data
      int N, M, P;
      cin >> N >> M >> P;
      vector<player> players(N);
      for (player& p: players) cin >> p.name >> p.shot >> p.height;

      // draft ordering
      auto draftOrder = functorToComparator([] (const player& p) { return make_pair(-p.shot, -p.height); });
      sort(players.begin(), players.end(), draftOrder);
      for (int i = 0; i < N; ++i) players[i].draft = i;

      // construct teams
      struct team { vector<player> bench, field; };
      vector<team> teams(2);
      for (const player& p: players) teams[p.draft % 2].bench.push_back(p);

      // simulate game
      auto takeOffPlayer = [] (team& t) {
         auto fromFieldOrder = functorToComparator([] (const player& p) { return make_pair(-p.minutes, -p.draft); });
         return movePlayer(t.field, t.bench, fromFieldOrder);
      };
      auto bringInPlayer = [] (team& t) {
         auto fromBenchOrder = functorToComparator([] (const player& p) { return make_pair(p.minutes, p.draft); });
         return movePlayer(t.bench, t.field, fromBenchOrder);
      };
      for (team& t: teams) for (int i = 0; i < P; ++i) bringInPlayer(t);
      for (int i = 0; i < M; ++i) for (team& t: teams) {
         for (player& p : t.field) ++p.minutes;
         takeOffPlayer(t);
         bringInPlayer(t);
      }

      // output name of the players on the field
      vector<string> names;
      names.reserve(2 * P);
      for (team &t: teams) for (int i = 0; i < P; ++i) names.push_back(takeOffPlayer(t).name);
      sort(names.begin(), names.end());
      cout << "Case #" << (q + 1) << ":";
      for (string name: names) cout << " " << name;
      cout << endl;
   }
   return 0;
}

