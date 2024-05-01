// Retorna si el Punto P se encuentra dentro del circulo entre A y B
bool inDisk(Point a, Point b, Point p) { return (a - p).dot(b - p) <= 0; }

// Retorna si el punto P se encuentra en el segmento de puntos S a E
bool onSegment(Point a, Point b, Point p) {
  return a.cross(b, p) == 0 && inDisk(a, b, p);
}

// SEGMENTO - SEGMENTO INTERSECCION
bool properInter(Point a, Point b, Point c, Point d, Point& p) {
  if(a == c || a == d){
	  p = a;
	  return true;
  }
  if(b == c || b == d){
	  p = b;
	  return true;
  }
  double oa = orient(c, d, a),
         ob = orient(c, d, b),
         oc = orient(a, b, c),
         od = orient(a, b, d);
  if (oa * ob < 0 && oc * od < 0) {
    p = (a * ob - b * oa) / (ob - oa);
    return true;
  }
  return false;
}
// Si existe un punto de interseccion unico entre los segmentos de linea que van de A a B y de C a D, se devuelve.
// Si no existe ningun punto de interseccion, se devuelve un vector vacio.
// Si existen infinitos, se devuelve un vector con 2 elementos, que contiene los puntos finales del segmento de linea comun.
vector<Point> segInter(Point a, Point b, Point c, Point d) {
  Point p;
  if (properInter(a, b, c, d, p)) return {p};
  set<Point> s;
  if (onSegment(c, d, a)) s.insert(a);
  if (onSegment(c, d, b)) s.insert(b);
  if (onSegment(a, b, c)) s.insert(c);
  if (onSegment(a, b, d)) s.insert(d);
  return {ALL(s)};
}

// SEGMENTO - PUNTO DISTANCIA
double segPoint(Point a, Point b, Point p) {
  if (a != b) {
    Line l(a, b);
    if (l.cmpProj(a, p) && l.cmpProj(p, b))
      return l.dist(p);
  }
  return min((p - a).norm(), (p - b).norm());
}

// SEGMENTO - SEGMENTO DISTANCIA
double segSeg(Point a, Point b, Point c, Point d) {
  Point dummy;
  if (properInter(a, b, c, d, dummy)) return 0;
  return min({segPoint(a, b, c), segPoint(a, b, d),
              segPoint(c, d, a), segPoint(c, d, b)});
}
