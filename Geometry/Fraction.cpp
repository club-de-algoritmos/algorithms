/**
 * Descripcion: estructura para manejar fracciones, es util
 * cuando necesitamos gran precision y solo usamos
 * fracciones.
 * Tiempo: O(1)
 */
struct Frac {
  int a, b;

  Frac() {}
  Frac(int _a, int _b) {
    assert(_b > 0);
    if ((_a < 0 && _b < 0) || (_a > 0 && _b < 0)) {
      _a = -_a;
      _b = -_b;
    }
    int GCD = gcd(abs(_a), abs(_b));
    a = _a / GCD;
    b = _b / GCD;
  }

  Frac operator*(Frac f) const {
    return Frac(a * f.a, b * f.b);
  }
  Frac operator/(Frac f) const {
    return (*this) * Frac(f.b, f.a);
  }
  Frac operator+(Frac f) const {
    return Frac(a * f.b + b * f.a, b * f.b);
  }
  Frac operator-(Frac f) const {
    return Frac(a * f.b - b * f.a, b * f.b);
  }
  bool operator<(Frac& other) const {
    return a * other.b < other.a * b;
  }
  bool operator==(Frac& other) const {
    return a == other.a && b == other.b;
  }
  bool operator!=(Frac& other) const {
    return !(*this == other);
  }
};
