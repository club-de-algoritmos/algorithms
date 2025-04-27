/**
 * Descripcion: segment tree persistente para consulta de
 * minimos en un rango. Un segment tree es persistente si
 * mantiene datos viejos disponible tras actualizaciones.
 * init y upd retornan la nueva raiz, rt es la ultima raiz
 * Para mejorar velocidad, usar arreglos.
 * Uso: STree st;st.init(arr);
 * vi roots;roots.pb(0);roots.pb(st.upd(roots.back(),0,3));st.query(roots[1], 0, n);
 * Tiempo: log(n)
 * Status: testeado en SWERC 2020 - H. Figurines
 */

 struct STree {
  #define ls st[v].l
  #define rs st[v].r
  #define lp ls, tl, tm
  #define rp rs, tm, tr
  #define NEUT 0

  struct Node {
    int l, r, val;
    Node(int l, int r, int val) : l(l), r(r), val(val) {}
  };

  int n;
  vector<Node> st;

  STree(int n) : n(n), st(1, Node(0, 0, NEUT)) {}

  int query(int v, int tl, int tr, int l, int r) {
    if (tr <= l || r <= tl) return NEUT;
    if (l <= tl && tr <= r) return st[v].val;
    int tm = (tl + tr) / 2;
    return query(lp, l, r) + query(rp, l, r);
  }
  
  int upd(int v, int tl, int tr, int i, int val) {
    st.emplace_back(st[v].l, st[v].r, st[v].val);
    v = int(st.size()) - 1;
    if (tl + 1 == tr) return st[v].val = val, v;
    int tm = (tl + tr) / 2;
    if (i < tm) ls = upd(lp, i, val);
    else rs = upd(rp, i, val);
    st[v].val = st[ls].val + st[rs].val;
    return v;
  }
 
  int query(int root, int l, int r) {
    return query(root, 0, n, l, r);
  }
  int upd(int root, int i, int val) {
    return upd(root, 0, n, i, val);
  }
};
