/*
 * Descripcion: Dado un conjunto de semiplanos calcula la interseccion
 * de estos representandolos en un poligono convexo. Donde cada punto
 * dentro del poligono esta dentro de todos los semiplanos
 * - Cada semiplano apunta en su region izquierda
 * - Se asume que no hay semiplanos paralelos
 * Tiempo: O(N Log N)
 */

typedef double T;
const double EPS = 1e-9;
const double INF = 1e9;

struct HalfPlane {
  Point p, pq;
  T angle;
  HalfPlane() {}
  HalfPlane(Point _p, Point _q)
      : p(_p), pq(_q - _p), angle(atan2(pq.y, pq.x)) {}
  bool operator<(HalfPlane b) const { return angle < b.angle; }
  bool out(Point q) { return pq.cross(q - p) < EPS; }
  Point intersect(HalfPlane l) {
    if (abs(pq.cross(l.pq)) < EPS) return Point{INF, INF};
    return l.p + l.pq * ((p - l.p).cross(pq) / l.pq.cross(pq));
  }
};

vector<Point> intersect(vector<HalfPlane> b) {
  vector<Point> bx = {Point{INF, INF}, Point{-INF, INF}, Point{-INF, -INF},
                      Point{INF, -INF}};
  for (int i = 0; i < 4; ++i) b.emplace_back(bx[i], bx[(i + 1) % 4]);
  sort(b.begin(), b.end());
  int n = b.size(), q = 1, h = 0;
  vector<HalfPlane> c(b.size() + 10);
  for (int i = 0; i < n; ++i) {
    while (q < h && b[i].out(c[h].intersect(c[h - 1]))) h--;
    while (q < h && b[i].out(c[q].intersect(c[q + 1]))) q++;
    c[++h] = b[i];
    if (q < h && abs(c[h].pq.cross(c[h - 1].pq)) < EPS) {
      if (c[h].pq.dot(c[h - 1].pq) <= 0) return {};
      h--;
      if (b[i].out(c[h].p)) c[h] = b[i];
    }
  }
  while (q < h - 1 && c[q].out(c[h].intersect(c[h - 1]))) h--;
  while (q < h - 1 && c[h].out(c[q].intersect(c[q + 1]))) q++;
  if (h - q <= 1) return {};
  c[h + 1] = c[q];
  vector<Point> s;
  for (int i = q; i < h + 1; ++i) s.push_back(c[i].intersect(c[i + 1]));
  return s;
}