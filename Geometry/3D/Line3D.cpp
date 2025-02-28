struct Line3D {
  P3 d, o;

  // De dos puntos P, Q
  Line3D(P3 p, P3 q) : d(q - p), o(p) {}

  // De dos planos p1, p2 (requiere double)
  Line3D(Plane p1, Plane p2) {
    d = p1.n.cross(p2.n);
    o = (p2.n * p1.d - p1.n * p2.d).cross(d) / d.sq();
  }

  // Distancia de un punto a la linea
  double sqDist(P3 p) { return d.cross(p - o).sq() / d.sq(); }
  double dist(P3 p) { return sqrt(sqDist(p)); }

  // Compara dos puntos acorde a su posicion en la linea
  bool cmpProj(P3 p, P3 q) { return d.dot(p) < d.dot(q); }

  P3 proj(P3 p) { return o + d * (d.dot(p - o)) / d.sq(); }
  P3 refl(P3 p) { return proj(p) * 2 - p; }

  // Retorna el punto de un interseccion de la linea con el plano
  P3 inter(Plane p) { return o - d * (p.side(o)) / (p.n.dot(d)); }
};

// Menor distancia entre dos lineas
double dist(Line3D l1, Line3D l2) {
  P3 n = l1.d.cross(l2.d);
  if (n == P3{0, 0, 0})  // Es paralelo
    return l1.dist(l2.o);
  return abs((l2.o - l1.o).dot(n)) / n.norm();
}

// Retorna el punto mas cercano de la linea L1 con la linea L2
P3 closestOnL1(Line3D l1, Line3D l2) {
  P3 n2 = l2.d.cross(l1.d.cross(l2.d));
  return l1.o + l1.d * ((l2.o - l1.o).dot(n2)) / (l1.d.dot(n2));
}

double angle(Line3D l1, Line3D l2) { return angle(l1.d, l2.d); }
bool isParallel(Line3D l1, Line3D l2) {
  return l1.d.cross(l2.d) == P3{0, 0, 0};
}
bool isPerpendicular(Line3D l1, Line3D l2) { return l1.d.dot(l2.d) == 0; }

// Entre un plano y una linea
double angle(Plane p, Line3D l) { return M_PI / 2 - angle(p.n, l.d); }
bool isParallel(Plane p, Line3D l) { return p.n.dot(l.d) == 0; }
bool isPerpendicular(Plane p, Line3D l) {
  return p.n.cross(l.d) == P3{0, 0, 0};
}