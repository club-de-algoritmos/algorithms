/**
 * Descripcion: lazy segment tree para suma y
 * actualizacion en rango. Rangos no inclusivos a la der.
 * Tiempo: O(log n)
 * Status: testeado en CSES Range Update Queries
 */
struct STree {
  #define ls 2 * v + 1
  #define rs 2 * v + 2
  #define lp ls, tl, tm
  #define rp rs, tm, tr
  #define NEUT 0

  int n;
  vector<int> st, lazy;

  STree(int n) : n(n), st(4 * n), lazy(4 * n) {}

  void apply(int v, int tl, int tr, int val) {
    st[v] += val * (tr - tl);
    lazy[v] += val;
  }

  void push(int v, int tl, int tr) {
    if (lazy[v]) {
      int tm = (tl + tr) / 2;
      apply(lp, lazy[v]), apply(rp, lazy[v]);
      lazy[v] = 0;
    }
  }

  int query(int v, int tl, int tr, int l, int r) {
    if (tr <= l || r <= tl) return NEUT;
    if (l <= tl && tr <= r) return st[v];
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    return query(lp, l, r) + query(rp, l, r);
  }
  
  void upd(int v, int tl, int tr, int l, int r, int val) {
    if (tr <= l || r <= tl) return;
    if (l <= tl && tr <= r) { apply(v, tl, tr, val); return; }
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    upd(lp, l, r, val), upd(rp, l, r, val);
    st[v] = st[ls] + st[rs];
  }
 
  int query(int l, int r) {
    return query(0, 0, n, l, r);
  }
  void upd(int l, int r, int val) {
    upd(0, 0, n, l, r, val);
  }
};