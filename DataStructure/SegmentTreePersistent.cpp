/**
 * Descripcion: Segment tree persistente para suma en rango.
 * Cada actualizacion genera una nueva raiz sin modificar versiones previas.
 * Rangos semiabiertos [l, r).
 * Uso:
 * STree st(n);
 * int root1 = st.upd(root0, i, val);
 * int ans = st.query(root1, l, r);
 * Tiempo: O(\log n)
 */

#define NEUT 0

struct STree {
  int n;
  vi lc, rc, val;

  int newNode(int l = 0, int r = 0, int v = NEUT) {
    lc.pb(l);
    rc.pb(r);
    val.pb(v);
    return SZ(val) - 1;
  }

  STree(int n) : n(n) { newNode(); }

  int query(int v, int tl, int tr, int l, int r) {
    if (!v || tr <= l || r <= tl) return NEUT;
    if (l <= tl && tr <= r) return val[v];
    int tm = (tl + tr) / 2;
    return query(lc[v], tl, tm, l, r) +
           query(rc[v], tm, tr, l, r);
  }
  int query(int root, int l, int r) { return query(root, 0, n, l, r); }

  int upd(int v, int tl, int tr, int i, int x) {
    int u = newNode(lc[v], rc[v], val[v]);
    if (tl + 1 == tr) { val[u] = x; return u; }
    int tm = (tl + tr) / 2;
    if (i < tm) lc[u] = upd(lc[u], tl, tm, i, x);
    else rc[u] = upd(rc[u], tm, tr, i, x);
    val[u] = val[lc[u]] + val[rc[u]];
    return u;
  }
  int upd(int root, int i, int x) { return upd(root, 0, n, i, x); }
};
