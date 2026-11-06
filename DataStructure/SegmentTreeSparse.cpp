/**
 * Descripcion: Segment tree esparcido (dinamico) para suma en rango
 * y actualizacion en punto. Memoria O(q \log n).
 * Rangos semiabiertos [l, r).
 * Uso:
 * STree st(n);
 * st.upd(i, val);
 * int sum = st.query(l, r);
 * Tiempo: O(\log n)
 */

#define NEUT 0

struct STree {
  int n;
  vi lc, rc, val;

  int newNode() {
    lc.pb(0);
    rc.pb(0);
    val.pb(NEUT);
    return SZ(val) - 1;
  }

  STree(int n) : n(n) {
    newNode();
    newNode();
  }

  int query(int v, int tl, int tr, int l, int r) {
    if (!v || tr <= l || r <= tl) return NEUT;
    if (l <= tl && tr <= r) return val[v];
    int tm = (tl + tr) / 2;
    return query(lc[v], tl, tm, l, r) +
           query(rc[v], tm, tr, l, r);
  }
  int query(int l, int r) { return query(1, 0, n, l, r); }

  int upd(int v, int tl, int tr, int i, int x) {
    if (!v) v = newNode();
    if (tl + 1 == tr) { val[v] = x; return v; }
    int tm = (tl + tr) / 2;
    if (i < tm) lc[v] = upd(lc[v], tl, tm, i, x);
    else rc[v] = upd(rc[v], tm, tr, i, x);
    val[v] = val[lc[v]] + val[rc[v]];
    return v;
  }
  void upd(int i, int x) { upd(1, 0, n, i, x); }
};
