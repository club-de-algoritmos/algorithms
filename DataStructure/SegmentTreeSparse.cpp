/**
 * Descripcion: segment tree esparcido. Para suma en rango y
 * actualizacion en punto. Util para algoritmos online.
 * Tiempo: O(log n)
 * Memoria total: O(qlog(n))
 * Status: testeado en CSES Salary Queries
 */
struct STree {
  #define ls st[v].l
  #define rs st[v].r
  #define lp ls, tl, tm
  #define rp rs, tm, tr
  #define NEUT 0

  struct Node {
    int l, r, val;
    Node() : l(-1), r(-1), val(NEUT) {}
  };

  int n;
  vector<Node> st;

  STree(int n) : n(n), st(1) {}

  int value(int v) {
    return v == -1 ? NEUT : st[v].val;
  }

  int query(int v, int tl, int tr, int l, int r) {
    if (tr <= l || r <= tl || v == -1) return NEUT;
    if (l <= tl && tr <= r) return st[v].val;
    int tm = (tl + tr) / 2;
    return query(lp, l, r) + query(rp, l, r);
  }
  
  int upd(int v, int tl, int tr, int i, int val) {
    if (v == -1) {
      v = int(st.size());
      st.emplace_back();
    }
    if (tl + 1 == tr) return st[v].val = val, v;
    int tm = (tl + tr) / 2;
    if (i < tm) ls = upd(lp, i, val);
    else rs = upd(rp, i, val);
    st[v].val = value(ls) + value(rs);
    return v;
  }
 
  int query(int l, int r) {
    return query(0, 0, n, l, r);
  }
  void upd(int i, int val) {
    upd(0, 0, n, i, val);
  }
};