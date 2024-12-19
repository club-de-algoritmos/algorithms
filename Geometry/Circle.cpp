
// Retorna el punto central del circulo que pasa por A,B,C
// Si se busca el radio solo sacar la distancia entre el centro
// y cualquier punto A,B,C
Point circumCenter(const Point& A, const Point& B, const Point& C) {
  Point b = C - A, c = B - A;
  return A + (b * c.sq() - c * b.sq()).perp() / b.cross(c) / 2;
}

// Retorna el punto que se encuentra en el circulo dado el angulo
Point circlePoint(Point c, double r, double ang) {
  return Point{c.x + cos(ang) * r, c.y + sin(ang) * r};
}

// Retorna el numero de intersecciones de la linea l con el circulo (o,r)
// y los pone en out. Si solo hay una interseccion el par de out es igual
int circleLine(Point o, double r, Line l, pair<Point, Point>& out) {
  double h2 = r * r - l.sqDist(o);
  if (h2 >= 0) {
    Point p = l.proj(o);
    Point h = l.v * sqrt(h2) / l.v.norm();
    out = {p - h, p + h};
  }
  return 1 + sgn(h2);
}

// Retorna las intersecciones entre dos circulos. Funciona igual que
// la interseccion con una linea
int circleCircle(Point o1, double r1, Point o2, double r2,
                 pair<Point, Point>& out) {
  Point d = o2 - o1;
  double d2 = d.sq();
  if (d2 == 0) {
    assert(r1 != r2);  // los circulos son iguales
    return 0;
  }
  double pd = (d2 + r1 * r1 - r2 * r2) / 2;
  double h2 = r1 * r1 - pd * pd / d2;
  if (h2 >= 0) {
    Point p = o1 + d * pd / d2, h = d.perp() * sqrt(h2 / d2);
    out = {p - h, p + h};
  }
  return 1 + sgn(h2);
}

// Retorna un booleano indicando si los dos circulos intersectan o no
bool circleCircle(Point o1, double r1, Point o2, double r2) {
  double dx = o1.x - o2.x, dy = o1.y - o2.y, rs = r1 + r2;
  return dx * dx + dy * dy <= rs * rs;
}

// Retorna el area de la interseccion de un circulo con
// un poligono ccw
// Tiempo O(n)
#define arg(p, q) atan2(p.cross(q), p.dot(q))
double circlePoly(Point c, double r, vector<Point> ps) {
  auto tri = [&](Point p, Point q) {  // area de interseccion con cpq
    auto r2 = r * r / 2;
    Point d = q - p;
    auto a = d.dot(p) / d.sq(), b = (p.sq() - r * r) / d.sq();
    auto det = a * a - b;
    if (det <= 0) return arg(p, q) * r2;
    auto s = max(0., -a - sqrt(det)), t = min(1., -a + sqrt(det));
    if (t < 0 || 1 <= s) return arg(p, q) * r2;
    Point u = p + d * s, v = p + d * t;
    return arg(p, u) * r2 + u.cross(v) / 2 + arg(v, q) * r2;
  };
  auto sum = 0.0;
  FOR(i, 0, SZ(ps))
  sum += tri(ps[i] - c, ps[(i + 1) % SZ(ps)] - c);
  return sum;
}

// Retorna el numero de tangentes de tipo especifico (inner, outer)
// * Si hay 2 tangentes. Out se llena con 2 pares de puntos:
//   los pares de puntos de tangencia de cada circulo (P1,P2)
// * Si solo hay 1 tangente, los circulo son tangentes en algun
//   punto P, out contiene P 4 veces y la linea tangente puede ser
//   encontrada como line(o1,p).perp(p)
// * Si hay 0 tangentes, no hace nada
// * Si los circulos son identicos, aborta
int tangents(Point o1, double r1, Point o2, double r2, bool inner,
             vector<pair<Point, Point>>& out) {
  if (inner) r2 = -r2;
  Point d = o2 - o1;
  double dr = r1 - r2, d2 = d.sq(), h2 = d2 - dr * dr;
  if (d2 == 0 || h2 < 0) {
    assert(h2 != 0);
    return 0;
  }
  for (double sign : {-1, 1}) {
    Point v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
    out.push_back({o1 + v * r1, o2 + v * r2});
  }
  return 1 + (h2 > 0);
}
