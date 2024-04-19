struct Point {
  double x, y, z;
  Point() {}
  Point(double xx, double yy, double zz) {
    x = xx, y = yy, z = zz;
  }
  /// scalar operators
  Point operator*(double f) {
    return Point(x * f, y * f, z * f);
  }
  Point operator/(double f) {
    return Point(x / f, y / f, z / f);
  }
  /// p3 operators
  Point operator-(Point p) {
    return Point(x - p.x, y - p.y, z - p.z);
  }
  Point operator+(Point p) {
    return Point(x + p.x, y + p.y, z + p.z);
  }
  Point operator%(Point p) {
    return Point(y * p.z - z * p.y, z * p.x - x * p.z,
                 x * p.y - y * p.x);
  }  /// (|p||q|sin(ang))* normal
  double operator|(Point p) {
    return x * p.x + y * p.y + z * p.z;
  }
  /// Comparators
  bool operator==(Point p) {
    return tie(x, y, z) == tie(p.x, p.y, p.z);
  }
  bool operator!=(Point p) { return !operator==(p); }
  bool operator<(Point p) {
    return tie(x, y, z) < tie(p.x, p.y, p.z);
  }
};
Point zero = Point(0, 0, 0);

/// BASICS
double sq(Point p) { return p | p; }
double abs(Point p) { return sqrt(sq(p)); }
Point unit(Point p) { return p / abs(p); }

/// ANGLES
double angle(Point p, Point q) {  ///[0, pi]
  double co = (p | q) / abs(p) / abs(q);
  return acos(max(-1.0, min(1.0, co)));
}
double small_angle(Point p, Point q) {  ///[0, pi/2]
  return acos(min(abs(p | q) / abs(p) / abs(q), 1.0))
}

/// 3D - ORIENT
double orient(Point p, Point q, Point r, Point s) {
  return (q - p) % (r - p) | (s - p);
}
bool coplanar(Point p, Point q, Point r, Point s) {
  return abs(orient(p, q, r, s)) < eps;
}
bool skew(
    Point p, Point q, Point r,
    Point s) {  /// skew := neither intersecting/parallel
  return abs(orient(p, q, r, s)) > eps;  /// lines: PQ, RS
}
double orient_norm(
    Point p, Point q, Point r,
    Point n) {  /// n := normal to a given plane PI
  retrurn(q - p) % (r - p) |
      n;  /// equivalent to 2D cross on PI (of ortogonal
          /// proj)
}
