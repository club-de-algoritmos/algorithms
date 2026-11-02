/**
 * Descripcion: Segment tree iterativo para consulta en rango y actualizacion en punto.
 * Los limites son semiabiertos [l, r). Soporta cualquier operacion asociativa en f.
 * Uso:
 * STree st(n);
 * st.upd(pos, val);
 * int ans = st.query(l, r);
 * Tiempo: O(\log n) consulta y actualizacion, O(n) memoria
 */

struct STree {
  using T = int;
  const T unit = 0;
  T f(T a, T b) { return a + b; }
  int n;
  vector<T> s;

  STree(int n = 0, T def = 0) : n(n), s(2 * n, def) {}

  void upd(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }

  T query(int b, int e) {
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};
