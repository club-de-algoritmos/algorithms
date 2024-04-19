/*
 * Descripcion: El Arbol de Li-Chao es una estructura de
 * datos utilizada en algoritmos de programacion dinamica y
 * geometrica para realizar consultas de maximo (o minimo)
 * en un conjunto de puntos en una linea (o un plano).
 * Tiempo :
 *   Construccion : O(N log N)
 *   Insercion y Consultas : O(log N)
 */

class LiChao {
  vector<ll> m, b;
  int n, sz;
  ll *x;
#define gx(i) (i < sz ? x[i] : x[sz - 1])
  void update(int t, int l, int r, ll nm, ll nb) {
    ll xl = nm * gx(l) + nb, xr = nm * gx(r) + nb;
    ll yl = m[t] * gx(l) + b[t], yr = m[t] * gx(r) + b[t];
    if (yl >= xl && yr >= xr) return;
    if (yl <= xl && yr <= xr) {
      m[t] = nm, b[t] = nb;
      return;
    }
    int mid = (l + r) / 2;
    update(t << 1, l, mid, nm, nb);
    update(1 + (t << 1), mid + 1, r, nm, nb);
  }

 public:
  LiChao(ll *st, ll *en) : x(st) {
    sz = int(en - st);
    for (n = 1; n < sz; n <<= 1)
      ;
    m.assign(2 * n, 0);
    b.assign(2 * n, -INF);
  }
  void insert_line(ll nm, ll nb) {
    update(1, 0, n - 1, nm, nb);
  }
  ll query(int i) {
    ll ans = -INF;
    for (int t = i + n; t; t >>= 1)
      ans = max(ans, m[t] * x[i] + b[t]);
    return ans;
  }
};
