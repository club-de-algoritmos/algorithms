struct Plane {
  P3 n;
  T d;

  // De vector normal n y offset
  Plane(P3 n, T d) : n(n), d(d) {}

  // De vector normal n y punto P
  Plane(P3 n, P3 p) : n(n), d(n.dot(p)) {}

  // De 3 puntos no colineares PQR
  Plane(P3 p, P3 q, P3 r) : Plane((q - p).cross(r - p), p) {}

  // 0 si esta en el plano | > 0 sobre | < 0 debajo
  T side(P3 p) { return n.dot(p) - d; }

  double dist(P3 p) { return abs(side(p)) / n.norm(); }
  Plane translate(P3 t) { return {n, d + (n.dot(t))}; }

  // Mueve el plano perpendicularmente en direccion del vector n
  Plane shiftUp(double dist) { return {n, d + dist * n.norm()}; }

  P3 proj(P3 p) { return p - n * side(p) / n.sq(); }
  P3 refl(P3 p) { return p - n * 2 * side(p) / n.sq(); }
};

bool isParallel(Plane p1, Plane p2) { return p1.n.cross(p2.n) == P3{0, 0, 0}; }
bool isPerpendicular(Plane p1, Plane p2) { return (p1.n.dot(p2.n) == 0); }
double angle(Plane p1, Plane p2) { return angle(p1.n, p2.n); }

// Retorna la linea perpendicular a el plano que pasa por el punto O
Line3D perpThrough(Plane p, P3 o) { return Line3D(o, o + p.n); }

// Retorna el plano perpendicular a la linea l que pasa por el punto O
Plane perpThrough(Line3D l, P3 o) { return Plane(l.d, o); }