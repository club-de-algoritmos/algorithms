typedef ll T;
struct Line {
  Point v;
  T c;

  // De vector direccional v y offset c
  Line(Point v, T c) : v(v), c(c) {}

  // De la ecuacion ax+by=c
  Line(T a, T b, T c) : v({b, -a}), c(c) {}

  // De punto P a punto Q
  Line(Point p, Point q) : v(q - p), c(v.cross(p)) {}

  // 0 si se encuentra en la linea, > 0 arriba, < 0 abajo
  T side(Point p) { return v.cross(p) - c; }

  double dist(Point p) { return abs(side(p)) / v.norm(); }
  double sqDist(Point p) {
    return side(p) * side(p) / (double)v.sq();
  }  // si se trabaja con enteros
  Line perp(Point p) { return {p, p + v.perp()}; }
  Line translate(Point t) { return {v, c + v.cross(t)}; }
  Line shiftLeft(double dist) {
    return {v, c + dist * v.norm()};
  }

  Point proj(Point p) {
    return p - v.perp() * side(p) / v.sq();
  }  // Punto en linea mas cercano a P
  Point refl(Point p) {
    return p - v.perp() * 2 * side(p) / v.sq();
  }

  // Sirve para comparar si un punto A esta antes de B en
  // una linea
  bool cmpProj(Point p, Point q) {
    return v.dot(p) < v.dot(q);
  }
};

bool areParallel(Line l1, Line l2) {
  return (l1.v.cross(l2.v) == 0);
}
bool areIntersect(Line l1, Line l2, Point& p) {
  T d = l1.v.cross(l2.v);
  if (d == 0)
    return false;  // cambiar a epsilon si es double
  p = (l2.v * l1.c - l1.v * l2.c) / d;  // requiere double
  return true;
}

// Un angulo bisector de dos lineas es una linea que forma
// angulos iguales con l1 y l2
Line bisector(Line l1, Line l2, bool interior) {
  assert(l1.v.cross(l2.v) !=
         0);  // l1 y l2 no pueden ser paralelas
  double sign = interior ? 1 : -1;
  return {l2.v / l2.v.norm() + l1.v / l1.v.norm() * sign,
          l2.c / l2.v.norm() + l1.c / l1.v.norm() * sign};
}