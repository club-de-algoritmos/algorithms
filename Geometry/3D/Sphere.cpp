// Retorna el punto de la esfera centrada en el origen con la posicion
// representada por coordenadas de latitud y longitud
P3 sph(double r, double lat, double lon) {
  lat *= M_PI / 180, lon *= M_PI / 180;
  return {r * cos(lat) * cos(lon), r * cos(lat) * sin(lon), r * sin(lat)};
}

// Retorna el numero de puntos de interseccion de la linea en la
// esfera y los guarda en out
int sphereLine(P3 o, double r, Line3D l, pair<P3, P3> &out) {
  double h2 = r * r - l.sqDist(o);
  if (h2 < 0) return 0;  // La linea no toca la esfera
  P3 p = l.proj(o);
  P3 h = l.d * sqrt(h2) / l.d.norm();
  out = {p - h, p + h};
  return 1 + (h2 > 0);
}

// Retorna la distancia mas corta entre los puntos A y B de la esfera
double greatCircleDist(P3 o, double r, P3 a, P3 b) {
  return r * angle(a - o, b - o);
}

// Checa si solo existe un segmento mas corto entre A y B en la esfera
bool validSegment(P3 a, P3 b) {
  return a.cross(b) != P3{0, 0, 0} || a.dot(b) > 0;
}

// Retorna el punto de interseccion de los segmentos AB y CD que pasan
// a traves de una esfera
bool properInter(P3 a, P3 b, P3 c, P3 d, P3 &out) {
  P3 ab = a.cross(b), cd = c.cross(d);
  int oa = sgn(cd.dot(a));
  int ob = sgn(cd.dot(b));
  int oc = sgn(ab.dot(c));
  int od = sgn(ab.dot(d));
  out = ab.cross(cd) * od;
  return (oa != ob && oc != od && oa != oc);
}

// Checa si el punto P pasa por el segmento AB que pasan por la esfera
bool onSphSegment(P3 a, P3 b, P3 p) {
  P3 n = a.cross(b);
  if (n == P3{0, 0, 0}) return a.cross(p) == P3{0, 0, 0} && a.dot(p) > 0;
  return n.dot(p) == 0 && n.dot(a.cross(p)) >= 0 && n.dot(b.cross(p)) <= 0;
}

// Retorna el angulo que se forma en el vector AB y el vector AC
double angleSph(P3 a, P3 b, P3 c) { return angle(a.cross(b), a.cross(c)); }
double orientedAngleSph(P3 a, P3 b, P3 c) {
  if (a.cross(b).dot(c) >= 0) return angleSph(a, b, c);
  return 2 * M_PI - angleSph(a, b, c);
}

// Retorna el area que se forma en los puntos P con la esfera de radio r
double areaOnSphere(double r, vector<P3> p) {
  int n = SZ(p);
  double sum = -(n - 2) * M_PI;
  FOR(i, 0, n) sum += orientedAngleSph(p[(i + 1) % n], p[(i + 2) % n], p[i]);
  return r * r * sum;
}