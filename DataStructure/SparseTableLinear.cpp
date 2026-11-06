/**
 * Descripcion: RMQ en arreglo inmutable con construccion lineal.
 * Divide en bloques de B = 30; mask[i] guarda (bit k -> posicion i - k)
 * los candidatos a minimo de las ventanas que terminan en i, asi el
 * minimo de una ventana de tamano <= B sale con un msb. Sobre los
 * minimos de los bloques se arma un sparse table normal.
 * Para maximo cambiar < por > en op.
 * Uso:
 * RMQ<int> rmq(a);
 * int mn = rmq.query(l, r); // [l, r)
 * int pos = rmq.idx(l, r);
 * Tiempo: O(n) construccion, O(1) consulta
 */

template <class T>
struct RMQ {
  static const int B = 30;
  int n, m;
  vector<T> v;
  vi mask, t;

  int op(int x, int y) { return v[x] < v[y] ? x : y; }
  int msb(int x) { return 31 - __builtin_clz(x); }
  // indice del minimo en [r - sz + 1, r], sz <= B
  int small(int r, int sz = B) { return r - msb(mask[r] & ((1 << sz) - 1)); }

  RMQ(const vector<T>& a) : n(SZ(a)), m(n / B), v(a), mask(n), t(n) {
    for (int i = 0, at = 0; i < n; mask[i++] = at |= 1) {
      at = (at << 1) & ((1 << B) - 1);
      while (at && op(i, i - msb(at & -at)) == i) at ^= at & -at;
    }
    FOR (i, 0, m) t[i] = small(B * i + B - 1);
    for (int j = 1; (1 << j) <= m; j++) FOR (i, 0, m - (1 << j) + 1)
      t[m * j + i] = op(t[m * (j - 1) + i], t[m * (j - 1) + i + (1 << (j - 1))]);
  }

  int idx(int l, int r) { // [l, r)
    if (r - l <= B) return small(r - 1, r - l);
    int x = l / B + 1, y = (r - 1) / B - 1;
    int ans = op(small(l + B - 1), small(r - 1));
    if (x > y) return ans;
    int j = msb(y - x + 1);
    return op(ans, op(t[m * j + x], t[m * j + y - (1 << j) + 1]));
  }
  T query(int l, int r) { return v[idx(l, r)]; }
};
