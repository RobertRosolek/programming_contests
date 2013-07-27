
      int pos = Q.top().second;
      // this position was already used
      if (a[1][pos] == INF) {
         Q.pop();
         continue;
      }
      res += Q.top().first;
      assert(left_range[pos] != -1 && right_range[pos] != -1);
      int pair_pos = t[0].query(left_range[pos], right_range[pos]);
      //cout << "pos = " << pos << " pair_pos = " << pair_pos << " sum = " << Q.top().first << endl;
      assert(a[0][pair_pos] != INF);
      assert(a[0][pair_pos] + a[1][pos] == Q.top().first);
      Q.pop();
      t[1].insert(pos, INF);
      t[0].insert(pair_pos, INF);
      --k;
      if (k == 0)
         break;

      int new_pos = t[1].query(left_range[pos], n - 1);

      if (new_pos <= right_range[pos]) {
         assert(new_pos < right_range[pos]);
         left_range[new_pos] = left_range[pos];
         right_range[new_pos] = right_range[pos];
         int best_value = a[0][ t[0].query(left_range[new_pos], right_range[new_pos]) ]; 
         Q.push(make_pair(a[1][new_pos] + best_value, new_pos));
      }
      else if (right_range[pos] < n - 1) {
         int next_pos = right_range[pos] + 1;
         left_range[next_pos] = left_range[pos];
         int best_value = a[0][ t[0].query(left_range[next_pos], right_range[next_pos]) ];
         Q.push(make_pair(a[1][next_pos] + best_value, next_pos));
      }

      // mark as used
      a[0][pair_pos] = INF;
      a[1][pos] = INF;
