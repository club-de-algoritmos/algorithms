/**
 * Descripcion: Segment tree con lazy propagation para suma
 * y actualizacion en rango. Rangos semiabiertos [l, r).
 * Uso:
 * STree st(n);
 * st.upd(l, r, val);
 * int sum = st.query(l, r);
 * Tiempo: O(\log n)
 */

#define NEUT 0

struct STree {
  int n;
  vi st, lazy;

  STree(int n) : n(n), st(4 * n), lazy(4 * n) {}

  void apply(int v, int tl, int tr, int val) {
    st[v] += val * (tr - tl);
    lazy[v] += val;
  }

  void push(int v, int tl, int tr) {
    if (lazy[v]) {
      int tm = (tl + tr) / 2;
      apply(2 * v + 1, tl, tm, lazy[v]);
      apply(2 * v + 2, tm, tr, lazy[v]);
      lazy[v] = 0;
    }
  }

  int query(int v, int tl, int tr, int l, int r) {
    if (tr <= l || r <= tl) return NEUT;
    if (l <= tl && tr <= r) return st[v];
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    return query(2 * v + 1, tl, tm, l, r) +
           query(2 * v + 2, tm, tr, l, r);
  }
  int query(int l, int r) { return query(0, 0, n, l, r); }

  void upd(int v, int tl, int tr, int l, int r, int val) {
    if (tr <= l || r <= tl) return;
    if (l <= tl && tr <= r) { apply(v, tl, tr, val); return; }
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    upd(2 * v + 1, tl, tm, l, r, val);
    upd(2 * v + 2, tm, tr, l, r, val);
    st[v] = st[2 * v + 1] + st[2 * v + 2];
  }
  void upd(int l, int r, int val) { upd(0, 0, n, l, r, val); }
};
