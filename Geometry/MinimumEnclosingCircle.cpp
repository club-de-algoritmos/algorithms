/*
 * Descripcion: calcula el circulo minimo que encierra
 * un conjunto de puntos con el algoritmo de Welzl
 * Tiempo: esperado O(n)
 */

pair<Point, double> mec(vector<Point> pts) {
  shuffle(ALL(pts), mt19937(time(0)));
  Point o = pts[0];
  double r = 0, EPS = 1 + 1e-8;
  FOR(i, 0, SZ(pts)) if ((o - pts[i]).norm() > r * EPS) {
    o = pts[i], r = 0;
    FOR(j, 0, i) if ((o - pts[j]).norm() > r * EPS) {
      o = (pts[i] + pts[j]) / 2;
      r = (o - pts[i]).norm();
      FOR(k, 0, j) if ((o - pts[k]).norm() > r * EPS) {
        o = circumCenter(pts[i], pts[j], pts[k]);
        r = (o - pts[i]).norm();
      }
    }
  }
  return {o, r};
}