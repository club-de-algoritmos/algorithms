typedef double T;

struct P3 {
  T x, y, z;

  // Operaciones Punto - Punto
  P3 operator+(P3 p) const { return {x + p.x, y + p.y, z + p.z}; }
  P3 operator-(P3 p) const { return {x - p.x, y - p.y, z - p.z}; }

  // Operacion Punto - Numero
  P3 operator*(T d) const { return {x * d, y * d, z * d}; }
  P3 operator/(T d) const { return {x / d, y / d, z / d}; }

  // Operaciones de comparacion para flotantes
  bool operator<(P3 p) const {
    return x < p.x - EPS || (abs(x - p.x) <= EPS && y < p.y - EPS) ||
           (abs(x - p.x) <= EPS && abs(y - p.y) <= EPS && z < p.z - EPS);
  }
  bool operator==(P3 p) const {
    return abs(x - p.x) <= EPS && abs(y - p.y) <= EPS && abs(z - p.z) <= EPS;
  }
  bool operator!=(P3 p) const { return !(*this == p); }

  // Operaciones de comparacion para enteros
  bool operator<(P3 p) const { return tie(x, y, z) < tie(p.x, p.y, p.z); }
  bool operator==(P3 p) const { return tie(x, y, z) == tie(p.x, p.y, p.z); }

  // Operaciones generales
  T sq() { return x * x + y * y + z * z; }
  double norm() { return sqrt(sq()); }
  P3 unit() { return *this / norm(); }
  T dot(P3 p) { return x * p.x + y * p.y + z * p.z; }
  P3 cross(P3 p) {
    return {y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x};
  }
  P3 cross(P3 a, P3 b) { return (a - *this).cross(b - *this); }

  friend ostream &operator<<(ostream &os, P3 p) {
    return os << "(" << p.x << "," << p.y << "," << p.z << ")";
  }
};

double dist(P3 p1, P3 p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) +
              (p1.z - p2.z) * (p1.z - p2.z));
}

bool areCollinear(P3 a, P3 b, P3 c) {
  P3 normal = (b - a).cross(c - a);
  return (normal.x == 0 && normal.y == 0 && normal.z == 0);
}

// Si > 0 S esta sobre el plano PQR
// Si = 0 S esta en el plano PQR
// Si < 0 S esta bajo el plano PQR
// Nota: |orient| es igual a 6 veces el volumen de un tetraedro PQRS
T orient(P3 p, P3 q, P3 r, P3 s) { return ((q - p).cross(r - p)).dot(s - p); }

// > 0 -> left | 0 -> aligned | < 0 -> right
T orientByNormal(P3 p, P3 q, P3 r, P3 n) {
  return ((q - p).cross(r - p)).dot(n);
}

// Angulo entre dos vectores [0, PI]
double angle(P3 v, P3 w) {
  double cosTheta = v.dot(w) / v.norm() / w.norm();
  return acos(max(-1.0, min(1.0, cosTheta)));
}
// Angulo aob
double angle(P3 o, P3 a, P3 b) { return angle(a - o, b - o); }