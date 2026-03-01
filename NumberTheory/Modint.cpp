/**
 * Descripcion: Template para manejar enteros
 * bajo un modulo sin complicaciones
 * Para calcular el inverso, se asume que MOD
 * es primo (si no, usar gcd extendido)
 * Nota: Si se requiere instanciar para multiples MODs,
 * cambiar a `template<int MOD> struct mint { ...` 
 * y en las inicializaciones usar `mi<MOD>` o `modint`.
 * Ejemplos de uso:
 *   mint res = a * b * c * d; 
 *   res += mint(x) * x * a[j] * a[j] * (r - l);
 * Tiempo: O(1)
 */
const int MOD = 998244353;

struct mint {
  int v; 
  mint():v(0) {}
  mint(ll _v):v(int(_v%MOD)) { v += (v<0)*MOD; }
  mint& operator+=(mint o) { 
    if ((v += o.v) >= MOD) v -= MOD; 
    return *this; }
  mint& operator-=(mint o) { 
    if ((v -= o.v) < 0) v += MOD; 
    return *this; }
  mint& operator*=(mint o) { 
    v = int((ll)v*o.v%MOD); return *this; }
  friend mint be(mint a, ll p) { assert(p >= 0);
    return p==0?1:be(a*a,p/2)*(p&1?a:1); }
  friend mint inv(mint a) { assert(a.v != 0); return be(a,MOD-2); }
  friend mint operator+(mint a, mint b) { return a += b; }
  friend mint operator-(mint a, mint b) { return a -= b; }
  friend mint operator*(mint a, mint b) { return a *= b; }
};