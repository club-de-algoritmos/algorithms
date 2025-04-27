/**
 * Descripcion: segment tree para suma en rango y
 * actualizacion en punto. Rangos no inclusivos a la der.
 * Tiempo: O(log n)
 * Status: testeado en CSES Pizzeria Queries
 */
struct STree {
  #define ls 2 * v + 1
  #define rs 2 * v + 2
  #define lp ls, tl, tm
  #define rp rs, tm, tr
  #define NEUT 0

  int n;
  vector<int> st;

  STree(int n) : n(n), st(4 * n) {}

  int query(int v, int tl, int tr, int l, int r) {
    if (tr <= l || r <= tl) return NEUT;
    if (l <= tl && tr <= r) return st[v];
    int tm = (tl + tr) / 2;
    return query(lp, l, r) + query(rp, l, r);
  }
  
  void upd(int v, int tl, int tr, int i, int val) {
    if (tl + 1 == tr) { st[v] = val; return; }
    int tm = (tl + tr) / 2;
    if (i < tm) upd(lp, i, val);
    else upd(rp, i, val);
    st[v] = st[ls] + st[rs];
  }
 
  int query(int l, int r) {
    return query(0, 0, n, l, r);
  }
  void upd(int i, int val) {
    upd(0, 0, n, i, val);
  }
};