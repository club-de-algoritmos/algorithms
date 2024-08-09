/**
 * Descripcion: estructura para manejar fracciones.
 * Se asume que el denominador no es cero.
 * Tiempo por operacion: O(1)
 */
struct Frac {
  int num, den;

  Frac(int num, int den) {
    int g = gcd(num, den);
    this->num = num / g;
    this->den = den / g;
  }

  Frac operator*(Frac& f) const { return Frac(num * f.num, den * f.den); }
  Frac operator/(Frac& f) const { return (*this) * Frac(f.den, f.num );  }
  Frac operator+(Frac& f) const { return Frac(num * f.den + den * f.num , den * f.den); }
  Frac operator-(Frac& f) const { return Frac(num * f.den - den * f.num , den * f.den); }
  bool operator<(Frac& other) const { return num * other.den < other.num  * den; }
  bool operator==(Frac& other) const { return num == other.num  && den == other.den; }
  bool operator!=(Frac& other) const { return !(*this == other); }
};