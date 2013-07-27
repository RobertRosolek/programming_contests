
      cout << "#########\n\n";
      LL res = 0;
      for (int rot = 0; rot < 4; ++rot)
         border[rot] = border_point[rot][i];
      swap(border[0], border[2]);
      swap(border[1], border[3]);
      cout << i << " " << toString(p[border[0]]) << " " << toString(p[border[1]]) << " " << toString(p[border[2]]) << " " << toString(p[border[3]]) << endl;
      for (int rot = 0; rot < 4; ++rot) {
         res += upper_right_area[rot][border[rot]][border[(rot + 1) % 4]];
         res -= triangle_area(p[border[rot]].first, p[border[(rot + 1) % 4]].first, 
                              make_pair(p[border[rot]].first.first, p[border[(rot + 1) % 4]].first.second));
      }
      cout << res << endl;
      for (int rot = 0; rot < 4; rot += 2) 
         res += triangle_area(p[border[rot]].first, p[border[(rot + 1) % 4]].first,p[border[(rot + 2) % 4]].first);
      cout << res << endl;
