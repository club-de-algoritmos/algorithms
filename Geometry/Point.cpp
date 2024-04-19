constexpr double EPS =
    1e-9;  // 1e-9 es suficiente para problemas de precision
           // doble
constexpr double PI = acos(-1.0);

inline double DEG_to_RAD(double d) {
  return (d * PI / 180.0);
}
inline double RAD_to_DEG(double r) {
  return (r * 180.0 / PI);
}

typedef double T;

int sgn(T x) { return (T(0) < x) - (x < T(0)); }

struct Point {
  T x, y;

  // Operaciones Punto - Punto
  Point operator+(Point p) const {
    return {x + p.x, y + p.y};
  }
  Point operator-(Point p) const {
    return {x - p.x, y - p.y};
  }
  Point operator*(Point b) const {
    return {x * b.x - y * b.y, x * b.y + y * b.x};
  }

  // Operaciones Punto - Numero
  Point operator*(T d) const { return {x * d, y * d}; }
  Point operator/(T d) const {
    return {x / d, y / d};
  }  // Solo para punto flotante

  // Operaciones de comparacion para punto flotante
  bool operator<(Point p) const {
    return x < p.x - EPS ||
           (abs(x - p.x) <= EPS && y < p.y - EPS);
  }
  bool operator==(Point p) const {
    return abs(x - p.x) <= EPS && abs(y - p.y) <= EPS;
  }
  bool operator!=(Point p) const { return !(*this == p); }

  // Operaciones de comparacion para enteros
  bool operator<(Point p) const {
    return tie(x, y) < tie(p.x, p.y);
  }
  bool operator==(Point p) const {
    return tie(x, y) == tie(p.x, p.y);
  }

  T sq() { return x * x + y * y; }
  double norm() { return sqrt(sq()); }
  Point unit() { return *this / norm(); }

  // Operaciones generales:
  Point translate(Point v) { return *this + v; }
  Point scale(Point c, double factor) {
    return c + (*this - c) * factor;
  }
  Point rotate(double ang) {
    return {x * cos(ang) - y * sin(ang),
            x * sin(ang) + y * cos(ang)};
  }
  Point rot_around(double ang, Point c) {
    return c + (*this - c).rotate(ang);
  }
  Point perp() { return {-y, x}; }

  T dot(Point p) { return x * p.x + y * p.y; }
  T cross(Point p) const { return x * p.y - y * p.x; }
  T cross(Point a, Point b) const {
    return (a - *this).cross(b - *this);
  }
  double angle() const { return atan2(y, x); }

  friend ostream& operator<<(ostream& os, Point p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};

// Vector: p2-p1
double dist(Point p1, Point p2) {
  return hypot(p1.x - p2.x, p1.y - p2.y);
}
bool isPerp(Point v, Point w) { return v.dot(w) == 0; }
//-1 -> left / 0 -> collinear / +1 -> right
T orient(Point a, Point b, Point c) {
  return a.cross(b, c);
}
bool cw(Point a, Point b, Point c) {
  return orient(a, b, c) < EPS;
}
bool ccw(Point a, Point b, Point c) {
  return orient(a, b, c) > -EPS;
}

// ANGULOS
// Para c++17
double angle(Point v, Point w) {
  return acos(
      clamp(v.dot(w) / v.norm() / w.norm(), -1.0, 1.0));
}
// C++14 o menor
double angle(Point v, Point w) {
  double cosTheta = v.dot(w) / v.norm() / w.norm();
  return acos(max(-1.0, min(1.0, cosTheta)));
}
// angulo aob
double angle(Point o, Point a, Point b) {
  return angle(a - o, b - o);
}
double orientedAngle(Point o, Point a, Point b) {
  if (ccw(o, a, b))
    return angle(a - o, b - o);
  else
    return 2 * PI - angle(a - o, b - o);
}
bool inAngle(Point o, Point a, Point b, Point p) {
  assert(orient(o, a, b) != 0);
  if (cw(o, a, b)) swap(b, c);
  return ccw(o, a, p) && cw(o, c, p);
}
