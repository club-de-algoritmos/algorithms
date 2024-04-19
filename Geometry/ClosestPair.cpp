/*
 * Descripcion: Dado un arreglo de N puntos en el plano,
 * encontrar el par de puntos con la menor distancia entre
 * ellos Utilizar con long long de preferencia
 * Tiempo: O(n log n)
 */

typedef Point P;
pair<Point, Point> closest(vector<Point> &v) {
  set<Point> S;
  sort(ALL(v), [](Point a, Point b) { return a.y < b.y; });
  pair<ll, pair<Point, Point>> ret{LLONG_MAX,
                                   {P{0, 0}, P{0, 0}}};
  int j = 0;
  for (Point p : v) {
    Point d{1 + (ll)sqrt(ret.first), 0};
    while (v[j].y <= p.y - d.x) S.erase(v[j++]);
    auto lo = S.lower_bound(p - d),
         hi = S.upper_bound(p + d);
    for (; lo != hi; ++lo)
      ret = min(ret, {(*lo - p).sq(), {*lo, p}});
    S.insert(p);
  }
  return ret.second;
}