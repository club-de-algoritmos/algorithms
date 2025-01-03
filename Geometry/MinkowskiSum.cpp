/*
 * Descripcion: calcula la suma de Minkowski de dos poligonos
 * convexos (eliminar colineales primero).
 * La respuesta es retornada en orden CCW
 * Tiempo: esperado O(|p| + |q|)
 */

void reorder(vector<Point>& p) {
  if (orient(p[0], p[1], p[2]) < -EPS) reverse(ALL(p));
  int pos = 0;
  FOR(i, 1, SZ(p))
  if (Point{p[i].y, p[i].x} < Point{p[pos].y, p[pos].x}) pos = i;
  rotate(p.begin(), p.begin() + pos, p.end());
}
vector<Point> minkowski_sum(vector<Point> p, vector<Point> q) {
  if (min(SZ(p), SZ(q)) < 3) {
    vector<Point> v;
    for (Point pp : p)
      for (Point qq : q) v.pb(pp + qq);
    return convexHull(v);
  }
  reorder(p);
  reorder(q);
  FOR(i, 0, 2) p.pb(p[i]), q.pb(q[i]);
  vector<Point> r;
  int i = 0, j = 0;
  while (i + 2 < SZ(p) || j + 2 < SZ(q)) {
    r.pb(p[i] + q[j]);
    auto cross = (p[i + 1] - p[i]).cross(q[j + 1] - q[j]);
    i += cross >= -EPS;
    j += cross <= EPS;
  }
  return r;
}