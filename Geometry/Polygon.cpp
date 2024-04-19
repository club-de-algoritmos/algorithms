
// Retorna el area de un triangulo
double areaTriangle(Point a, Point b, Point c) {
  return abs((b - a).cross(c - a)) / 2.0;
}

// Retorna si el punto esta dentro del triangulo
bool pointInTriangle(Point a, Point b, Point c, Point p) {
  T s1 = abs(a.cross(b, c));
  T s2 = abs(p.cross(a, b)) + abs(p.cross(b, c)) +
         abs(p.cross(c, a));
  return s1 == s2;
}

// Retorna el area del poligono
double areaPolygon(vector<Point> p) {
  double area = 0.0;
  int n = SZ(p);
  FOR(i, 0, n) { area += p[i].cross(p[(i + 1) % n]); }
  return abs(area) / 2.0;
}

// Retorna si el poligono es convexo
bool isConvex(vector<Point> p) {
  bool hasPos = false, hasNeg = false;
  for (int i = 0, n = SZ(p); i < n; i++) {
    int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
    if (o > 0) hasPos = true;
    if (o < 0) hasNeg = true;
  }
  return !(hasPos && hasNeg);
}

// Retorna 1/0/-1 si el punto p esta dentro/sobre/fuera de
// cualquier poligono P concavo/convexo
// Tiempo: O(n)
int inPolygon(vector<Point> poly, Point p) {
  int n = SZ(poly), ans = 0;
  FOR(i, 0, n) {
    Point p1 = poly[i], p2 = poly[(i + 1) % n];
    if (p1.y > p2.y) swap(p1, p2);
    if (onSegment(p1, p2, p)) return 0;
    ans ^=
        (p1.y <= p.y && p.y < p2.y && p.cross(p1, p2) > 0);
  }
  return ans ? -1 : 1;
}

// Retorna el centroide del poligono
Point polygonCenter(vector<Point>& v) {
  Point res{0, 0};
  double A = 0;
  for (int i = 0, j = SZ(v) - 1; i < SZ(v); j = i++) {
    res = res + (v[i] + v[j]) * v[j].cross(v[i]);
    A += v[j].cross(v[i]);
  }
  return res / A / 3;
}

// Determina si un punto P se encuentra dentro de un
// poligono convexo ordenado en ccw y sin puntos colineares
// (Convex hull) Tiempo O(log n)
bool inPolygonCH(vector<Point>& l, Point p,
                 bool strict = true) {
  int a = 1, b = SZ(l) - 1, r = !strict;
  if (SZ(l) < 3) return r && onSegment(l[0], l.back(), p);
  if (orient(l[0], l[a], l[b]) > 0) swap(a, b);
  if (orient(l[0], l[a], p) >= r ||
      orient(l[0], l[b], p) <= -r)
    return false;
  while (abs(a - b) > 1) {
    int c = (a + b) / 2;
    (orient(l[0], l[c], p) > 0 ? b : a) = c;
  }
  return sgn(l[a].cross(l[b], p)) < r;
}

// Retorna los dos puntos con mayor distancia en un poligono
// convexo ordenado en ccw y sin puntos colineares (Convex
// hull) Tiempo O(n)
array<Point, 2> hullDiameter(vector<Point> S) {
  int n = SZ(S), j = n < 2 ? 0 : 1;
  pair<ll, array<Point, 2>> res({0, {S[0], S[0]}});
  FOR(i, 0, j) {
    for (;; j = (j + 1) % n) {
      res = max(res, {(S[i] - S[j]).sq(), {S[i], S[j]}});
      if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >=
          0)
        break;
    }
  }
  return res.second;
}

// Retorna el poligono que se encuentra a la izquierda de la
// linea que va de s a e despues del corte
vector<Point> polygonCut(vector<Point>& poly, Point s,
                         Point e) {
  vector<Point> res;
  FOR(i, 0, SZ(poly)) {
    Point cur = poly[i],
          prev = i ? poly[i - 1] : poly.back();
    bool side = s.cross(e, cur) < 0;
    if (side != (s.cross(e, prev) < 0)) {
      Point p;
      areIntersect(Line(s, e), Line(cur, prev), p);
      res.push_back(p);
    }
    if (side) res.push_back(cur);
  }
  return res;
}