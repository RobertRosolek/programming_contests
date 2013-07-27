
void regroup_group_on_dip_enter(int group, int dip, int tm) {
   int left_position = get_ants_position(group, g[group].left, tm),
      right_position = get_ants_position(group, g[group].right, tm);
   // no destination, this is only possible if there are no 
   // drops now and there is only one group active now
   if (g[group].dest == -1) {
      assert(group == all_group);
      if (right_position < dips[dip].pos) {
         g[group].dest = dips[dip].pos;
         g[group].dest_dip = dip;
         g[group].time_stamp = tm;
         assert(dips[dip].left_group == -1);
         dips[dip].left_group = group;
         Q.push(make_pair( make_pair(tm + dips[dip].pos - right_position, group), 
                           make_pair(g[group].cur_walk_id, ARRIVAL) 
                        ) );
      }
      else if (dips[dip].pos < left_position) {
         g[group].dest = dips[dip].pos;
         g[group].dest_dip = dip;
         g[group].time_stamp = tm;
         assert(dips[dip].right_group == -1);
         dips[dip].right_group = group;
         Q.push(make_pair( make_pair(tm + left_position - dips[dip].pos, group), 
                           make_pair(g[group].cur_walk_id, ARRIVAL) 
                        ) );
      }
      // dip in the middle
      else {
         //binary search for the last ant before or at dip
         int left = g[group].left, right = g[group].right;
         while (left < right) {
            int s = (left + right + 1) / 2;
            if (get_ants_position(group, s, tm) > dips[dip].pos)
               right = s - 1;
            else
               left = s;
         }
         int pos = left;
         assert(pos < g[group].right);
         int pos_position = get_ants_position(group, pos, tm);

         // dip hit the ant, nothing happens
         if (pos_position == dips[dip].pos) {
            dip_set.erase(make_pair(dips[dip].pos, dip));
            return;
         }

         int nxt = group_slots.back(); group_slots.pop_back();
         g[nxt].dest = dips[dip].pos;
         g[nxt].dest_dip = dip;
         g[nxt].left = pos + 1;
         g[nxt].right = g[group].right;
         g[nxt].time_stamp = tm;
         g[nxt].loc = get_ants_position(group, pos + 1, tm);
         //g[nxt].cur_walk_id = 0; by design we do not zero out this guy
         ++g[nxt].cur_walk_id; // TODO - maybe we do not need this
         int shift = t.query(pos + 1);
         t.insert(pos + 1, g[nxt].right, -shift);
         dips[dip].right_group = nxt;
         Q.push(make_pair( make_pair(tm + g[nxt].loc - dips[dip].pos, nxt), 
                           make_pair(g[nxt].cur_walk_id, ARRIVAL) 
                        ) );

         g[group].dest = dips[dip].pos;
         g[group].dest_dip = dip;
         g[group].right = pos;
         g[group].time_stamp = tm;
         dips[dip].left_group = group;
         Q.push(make_pair( make_pair(tm + dips[dip].pos - pos_position, group), 
                           make_pair(g[group].cur_walk_id, ARRIVAL) 
                        ));
      }
   }
   // two dips in the same place or dip hits the ant - nothing happens
   else if (dips[dip].pos ==  g[group].dest ||  right_position == dips[dip].pos || left_position == dips[dip].pos) {
      dip_set.erase(make_pair(dips[dip].pos, dip));
      return;
   }
   else if (right_position < dips[dip].pos && dips[dip].pos < g[group].dest) {
      dips[g[group].dest_dip].left_group = -1;
      dips[dip].left_group = group;
      g[group].dest = dips[dip].pos;
      g[group].dest_dip = dip;
      g[group].loc = left_position;
      g[group].time_stamp = tm;
      ++g[group].cur_walk_id;
      Q.push(make_pair( make_pair(tm + dips[dip].pos - right_position, group), 
                        make_pair(g[group].cur_walk_id, ARRIVAL) 
                     ));
   }
   else if (right_position < g[group].dest && g[group].dest < dips[dip].pos) {
      // this group ignores this dip for now
   }
   else if (dips[dip].pos < g[group].dest && g[group].dest < left_position)  {
      // as above
   }
   else if (g[group].dest < dips[dip].pos && dips[dip].pos < left_position) {
      dips[g[group].dest_dip].right_group = -1;
      dips[dip].right_group = group;
      g[group].dest = dips[dip].pos;
      g[group].dest_dip = dip;
      g[group].loc -= tm - g[group].time_stamp;
      g[group].time_stamp = tm;
      ++g[group].cur_walk_id;
      Q.push(make_pair( make_pair(tm + left_position - dips[dip].pos, group), 
                        make_pair(g[group].cur_walk_id, ARRIVAL) 
                     ));
   }
   else if (dips[dip].pos < left_position && right_position < g[group].dest) {
      int dist = g[group].dest - dips[dip].pos;

      // range of left dip (dip)
      int range = dips[dip].pos + dist / 2;
      if (range < left_position) {
         // this group is not interested in this dip for now
      }
      else if (right_position <= range) {
         // move whole to group to the left dip
         dips[g[group].dest_dip].left_group = -1;
         if (dips[dip].right_group != -1) {
            // merge to this group
            int group_2 = dips[dip].right_group;
            int left_position_2 = get_ants_position(group_2, g[group_2].left, tm);
            t.insert(g[group].left, g[group].right, left_position - left_position_2);
            g[group_2].right = g[group].right;

            ++g[group].cur_walk_id; // on design g[group] - invalidate any group events
            group_slots.push_back(group); // put to trash

         }
         else {
            dips[dip].right_group = group;
            g[group].dest = dips[dip].pos;
            g[group].dest_dip = dip;
            g[group].loc += tm - g[group].time_stamp;
            g[group].time_stamp = tm;
            ++g[group].cur_walk_id;
            Q.push(make_pair( make_pair(tm + left_position - dips[dip].pos, group), 
                              make_pair(g[group].cur_walk_id, ARRIVAL) 
                           ));
         }
      }
      else {
         // split group into two
         
         // binary search for the last position in the left group
         int left = g[group].left, right = g[group].right;
         while (left < right) {
            int s = (left + right + 1) / 2;
            if (get_ants_position(group, s, tm) > range)
               right = s - 1;
            else
               left = s;
         }
         int pos = left;

         // new group going to new left dip
         if (dips[dip].right_group != -1) {
            // merge new group into this group
            int group_2 = dips[dip].right_group;
            int left_position_2 = get_ants_position(group_2, g[group_2].left, tm);
            t.insert(g[group].left, pos, left_position - left_position_2);
            g[group_2].right = g[group].right;
         }
         else {
            int nxt = group_slots.back(); group_slots.pop_back();
            g[nxt].dest = dips[dip].pos; 
            g[nxt].dest_dip = dip; 
            g[nxt].left = g[group].left; 
            g[nxt].right = pos;
            g[nxt].time_stamp = tm; 
            g[nxt].loc = left_position;
            //g[nxt].cur_walk_id = 0; by design we do not zero out this guy
            ++g[nxt].cur_walk_id; // TODO - maybe we do not need this
            dips[dip].right_group = nxt;
            Q.push(make_pair( make_pair(tm + left_position - dips[dip].pos, nxt), 
                              make_pair(g[nxt].cur_walk_id, ARRIVAL) 
                           ) );
         }

         // update old group
         g[group].left = pos + 1;
         g[group].loc = get_ants_position(group, pos + 1, tm);
         g[group].time_stamp = tm;
         int shift = t.query(pos + 1);
         t.insert(pos + 1, g[group].right, -shift);
      }

   }
   else if (g[group].dest < left_position && right_position < dips[dip].pos) {
      int dist = dips[dip].pos - g[group].dest;
      // range of left dip (g[group].dest_dip)
      // TODO - check this one out if there are some problems
      int range = g[group].dest + dist / 2;
      if (right_position <= range) {
         // this group is not interested in this dip for now
      }
      else if (range < left_position) {
         // move whole group to the right dip
         dips[g[group].dest_dip].right_group = -1;
         if (dips[dip].left_group != -1) {
            // merge with this group
            int group_2 = dips[dip].left_group;
            int left_position_2 = get_ants_position(group_2, g[group_2].left, tm);
            t.insert(g[group_2].left, g[group_2].right, left_position_2 - left_position);
            g[group_2].left = g[group].left;
            g[group_2].loc = left_position;
            g[group_2].time_stamp = tm;

            ++g[group].cur_walk_id; // on design g[group] - invalidate any group events
            group_slots.push_back(group); // put to trash
         }
         else {
            g[group].dest = dips[dip].pos;
            g[group].dest_dip = dip;
            g[group].loc -= tm - g[group].time_stamp;
            g[group].time_stamp = tm;
            dips[dip].left_group = group;
            ++g[group].cur_walk_id;
            Q.push(make_pair( make_pair(tm + dips[dip].pos - right_position, group), 
                              make_pair(g[group].cur_walk_id, ARRIVAL) 
                           ));
         }
      }
      else {
         // split the group into two

         // binary search for the last position in the left group
         int left = g[group].left, right = g[group].right;
         while (left < right) {
            int s = (left + right + 1) / 2;
            if (get_ants_position(group, s, tm) > range)
               right = s - 1;
            else
               left = s;
         }
         int pos = left;

         // new group going to new right dip
         if (dips[dip].left_group != -1) {
            // merge new group into this group
            int group_2 = dips[dip].left_group;
            int left_position_2 = get_ants_position(group_2, g[group_2].left, tm);
            int shift = t.query(pos + 1);
            int next_left_position = get_ants_position(group, pos + 1, tm);// do not put lower without thinking about it !!!!!!
            t.insert(pos + 1, g[group].right, -shift);
            t.insert(g[group_2].left, g[group_2].right, left_position_2 - next_left_position);
            g[group_2].left = pos + 1;
            g[group_2].loc = next_left_position;
            g[group_2].time_stamp = tm;
         }
         else {
            int nxt = group_slots.back(); group_slots.pop_back();
            g[nxt].dest = dips[dip].pos;
            g[nxt].dest_dip = dip;
            g[nxt].left = pos + 1;
            g[nxt].right = g[group].right;
            g[nxt].time_stamp = tm;
            g[nxt].loc = get_ants_position(group, pos + 1, tm);
            //g[nxt].cur_walk_id = 0; by design we do not zero out this guy
            ++g[nxt].cur_walk_id; // TODO - maybe we do not need this
            int shift = t.query(pos + 1);
            t.insert(pos + 1, g[nxt].right, -shift);
            dips[dip].left_group = nxt;
            Q.push(make_pair( make_pair(tm + dips[dip].pos - right_position, nxt), 
                              make_pair(g[nxt].cur_walk_id, ARRIVAL) 
                           ) );
         }

         // update old group
         g[group].right = pos;
      }
   }
   else if (g[group].dest < left_position) {
      assert(left_position < dips[dip].pos && dips[dip].pos < right_position);

      //binary search for the last position to the left or at dip position
      int left = g[group].left, right = g[group].right;
      while (left < right) {
         int s = (left + right + 1) / 2;
         if (get_ants_position(group, s, tm) > dips[dip].pos)
            right = s - 1;
         else
            left = s;
      }
      int pos = left;

      if (pos == dips[dip].pos) {
         dip_set.erase(make_pair(dips[dip].pos, dip));
         return;
      }

      // all guys on the right are heading to new dip 
      int nxt = group_slots.back(); group_slots.pop_back();
      g[nxt].left = pos + 1;
      g[nxt].right = g[group].right;
      int shift = t.query(pos + 1);
      t.insert(pos + 1, g[nxt].right, -shift);
      int next_left_position = get_ants_position(group, pos + 1, tm);
      g[nxt].loc = next_left_position;
      g[nxt].time_stamp = tm;
      ++g[nxt].cur_walk_id;
      g[nxt].dest = dips[dip].pos;
      g[nxt].dest_dip = dip;
      dips[dip].right_group = nxt;
      Q.push(make_pair( make_pair(tm + next_left_position - dips[dip].pos, nxt), 
                        make_pair(g[nxt].cur_walk_id, ARRIVAL) 
                     ) );

      // split the rest
      right_position = get_ants_position(group, pos, tm);
      g[group].right = pos;

      int dist = dips[dip].pos - g[group].dest;
      // range of left old group
      int range = g[group].dest + dist / 2;
      if (right_position <= range) {
         // this part of group ignores new dip for now
      }
      else if (range < left_position) {
         // tranfer whole group to new right dip
         dips[g[group].dest_dip].right_group = -1;
         g[group].dest = dips[dip].pos;
         g[group].dest_dip = dip;
         g[group].loc = left_position;
         g[group].time_stamp = tm;
         ++g[group].cur_walk_id;
         Q.push(make_pair( make_pair(tm + dips[dip].pos - right_position, group), 
                           make_pair(g[group].cur_walk_id, ARRIVAL) 
                        ) );
      }
      else {
         // binary search for last ant going left to old dip
         int l = g[group].left, r = g[group].right;
         while (l < r) {
            int s = (l + r + 1) / 2;
            if (get_ants_position(group, s, tm) > range)
               r = s - 1;
            else
               l = s;
         }
         int pos_2 = l;
         
         // new group heading right to new dip
         int nxt_2 = group_slots.back(); group_slots.pop_back();
         g[nxt_2].left = pos_2 + 1;
         g[nxt_2].right = g[group].right;
         g[nxt_2].dest = dips[dip].pos;
         g[nxt_2].dest_dip = dip;
         dips[dip].left_group = nxt_2;
         int shift = t.query(pos_2 + 1);
         int new_left_position_2 = get_ants_position(group, pos_2 + 1, tm);
         t.insert(pos_2 + 1, g[nxt_2].right, -shift);
         g[nxt_2].loc = new_left_position_2;
         g[nxt_2].time_stamp = tm;
         Q.push(make_pair( make_pair(tm + dips[dip].pos - right_position, nxt_2), 
                           make_pair(g[nxt_2].cur_walk_id, ARRIVAL) 
                        ) );

         // update old group
         g[group].right = pos_2;
      }
   }
   else {
      assert(right_position < g[group].dest);
      assert(left_position < dips[dip].pos && dips[dip].pos < right_position);
      
      //binary search for the last position to the left or at dip position
      int left = g[group].left, right = g[group].right;
      while (left < right) {
         int s = (left + right + 1) / 2;
         if (get_ants_position(group, s, tm) > dips[dip].pos)
            right = s - 1;
         else
            left = s;
      }
      int pos = left;

      if (pos == dips[dip].pos) {
         dip_set.erase(make_pair(dips[dip].pos, dip));
         return;
      }

      // all guys on the left are heading right to new dip 
      int nxt = group_slots.back(); group_slots.pop_back();
      g[nxt].left = g[group].left;
      g[nxt].right = pos;
      g[nxt].loc = left_position;
      g[nxt].time_stamp = tm;
      ++g[nxt].cur_walk_id;

      // TODO - after this needs rewrite complete

      g[nxt].left = pos + 1;
      g[nxt].right = g[group].right;
      int shift = t.query(pos + 1);
      t.insert(pos + 1, g[nxt].right, -shift);
      int next_left_position = get_ants_position(group, pos + 1, tm);
      g[nxt].loc = next_left_position;
      g[nxt].time_stamp = tm;
      ++g[nxt].cur_walk_id;
      g[nxt].dest = dips[dip].pos;
      g[nxt].dest_dip = dip;
      dips[dip].right_group = nxt;
      Q.push(make_pair( make_pair(tm + next_left_position - dips[dip].pos, nxt), 
                        make_pair(g[nxt].cur_walk_id, ARRIVAL) 
                     ) );

      // split the rest
      right_position = get_ants_position(group, pos, tm);
      g[group].right = pos;

      int dist = dips[dip].pos - g[group].dest;
      // range of left old group
      int range = g[group].dest + dist / 2;
      if (right_position <= range) {
         // this part of group ignores new dip for now
      }
      else if (range < left_position) {
         // tranfer whole group to new right dip
         dips[g[group].dest_dip].right_group = -1;
         g[group].dest = dips[dip].pos;
         g[group].dest_dip = dip;
         g[group].loc = left_position;
         g[group].time_stamp = tm;
         ++g[group].cur_walk_id;
         Q.push(make_pair( make_pair(tm + dips[dip].pos - right_position, group), 
                           make_pair(g[group].cur_walk_id, ARRIVAL) 
                        ) );
      }
      else {
         // binary search for last ant going left to old dip
         int l = g[group].left, r = g[group].right;
         while (l < r) {
            int s = (l + r + 1) / 2;
            if (get_ants_position(group, s, tm) > range)
               r = s - 1;
            else
               l = s;
         }
         int pos_2 = l;
         
         // new group heading right to new dip
         int nxt_2 = group_slots.back(); group_slots.pop_back();
         g[nxt_2].left = pos_2 + 1;
         g[nxt_2].right = g[group].right;
         g[nxt_2].dest = dips[dip].pos;
         g[nxt_2].dest_dip = dip;
         dips[dip].left_group = nxt_2;
         int shift = t.query(pos_2 + 1);
         int new_left_position_2 = get_ants_position(group, pos_2 + 1, tm);
         t.insert(pos_2 + 1, g[nxt_2].right, -shift);
         g[nxt_2].loc = new_left_position_2;
         g[nxt_2].time_stamp = tm;
         Q.push(make_pair( make_pair(tm + dips[dip].pos - right_position, nxt_2), 
                           make_pair(g[nxt_2].cur_walk_id, ARRIVAL) 
                        ) );

         // update old group
         g[group].right = pos_2;
      }
   }
}
