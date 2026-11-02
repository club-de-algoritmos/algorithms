/**
 * Descripcion: Segment tree para suma en rango y
 * actualizacion en punto. Rangos semiabiertos [l, r).
 * Uso:
 * STree st(n);
 * st.upd(i, val);
 * int sum = st.query(l, r);
 * Tiempo: O(\log n)
 */

struct STree {
  int n;
  vi st;

  STree(int n) : n(n), st(4 * n) {}

  int query(int v, int tl, int tr, int l, int r) {
    if (tr <= l || r <= tl) return 0;
    if (l <= tl && tr <= r) return st[v];
    int tm = (tl + tr) / 2;
    return query(2 * v + 1, tl, tm, l, r) +
           query(2 * v + 2, tm, tr, l, r);
  }
  int query(int l, int r) { return query(0, 0, n, l, r); }

  void upd(int v, int tl, int tr, int i, int val) {
    if (tl + 1 == tr) { st[v] = val; return; }
    int tm = (tl + tr) / 2;
    if (i < tm) upd(2 * v + 1, tl, tm, i, val);
    else upd(2 * v + 2, tm, tr, i, val);
    st[v] = st[2 * v + 1] + st[2 * v + 2];
  }
  void upd(int i, int val) { upd(0, 0, n, i, val); }
};
