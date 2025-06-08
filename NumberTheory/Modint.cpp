/**
 * Descripcion: Template para manejar enteros
 * bajo un modulo sin complicaciones
 * Para calcular el inverso, se asume que MOD
 * es primo (si no, usar gcd extendido)
 * Ejemplos de uso:
 *   modint res = a * b * c * d; 
 *   res += modint(x) * x * a[j] * a[j] * (r - l);
 * Tiempo: O(1)
 */
template<int MOD> struct mi {
  int v; 
  mi():v(0) {}
  mi(ll _v):v(int(_v%MOD)) { v += (v<0)*MOD; }
  mi& operator+=(mi o) { 
    if ((v += o.v) >= MOD) v -= MOD; 
    return *this; }
  mi& operator-=(mi o) { 
    if ((v -= o.v) < 0) v += MOD; 
    return *this; }
  mi& operator*=(mi o) { 
    v = int((ll)v*o.v%MOD); return *this; }
  friend mi be(mi a, ll p) { assert(p >= 0);
    return p==0?1:be(a*a,p/2)*(p&1?a:1); }
  friend mi inv(mi a) { assert(a.v != 0); return be(a,MOD-2); }
  friend mi operator+(mi a, mi b) { return a += b; }
  friend mi operator-(mi a, mi b) { return a -= b; }
  friend mi operator*(mi a, mi b) { return a *= b; }
};
using modint = mi<998244353>;