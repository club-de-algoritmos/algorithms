/**
 * Descripcion: segment tree esparcido. Para suma en rango y
 * actualizacion en punto.
 * Un segment tree es esparcido cuando sus nodos se van creando
 * conforme se vayan utilizando, lo que permite manejar grandes
 * rangos de indices. Es util cuando en esta situacion necesitas
 * un algoritmo online (no se puede realizar compresion de
 * coordenadas). 
 * Para mejorar velocidad, usar arreglos.
 * [a,b) es el rango de la query y [s, e) el del nodo
 * Uso: STree st(1e18);st.upd(6, 3);st.query(5, 1e12);
 * Tiempo de consulta y actualizacion: O(log n)
 * Memoria total: O(qlog(n))
 * Status: testeado en CSES Salary Queries
 */
struct STree {
  #define ls st[k].l
  #define rs st[k].r
  #define lp ls, s, m
  #define rp rs, m, e
  #define NEUT 0
 
  struct Node {
    int v, l, r;
    Node() : v(NEUT), l(-1), r(-1) {}
  };
 
  int n;
  vector<Node> st;
 
  STree(int n) : n(n), st(1) {}
 
  int merge(int x, int y) {
    return x + y;
  }
 
  int get(int k) {
    return k == -1 ? NEUT : st[k].v;
  }
 
  void pull(int k) {
    st[k].v = merge(get(ls), get(rs));
  }
 
  int addNode() {
    st.emplace_back();
    return (int)st.size() - 1;
  }
 
  int query(int k, int s, int e, int a, int b) {
    if (k == -1 || e <= a || s >= b) {
      return NEUT;
    }
    if (a <= s && e <= b) {
      return st[k].v;
    }
    int m = (s + e) >> 1;
    return merge(query(lp, a, b), query(rp, a, b));
  }
 
  void upd(int k, int s, int e, int i, int v) {
    if (s + 1 == e) {
      st[k].v += v;
      return;
    }
    int m = (s + e) >> 1;
    if (i < m) {
      if (ls == -1) {
        ls = addNode();
      }
      upd(lp, i, v);
    } else {
      if (rs == -1) {
        rs = addNode();
      }
      upd(rp, i, v);
    }
    pull(k);
  }
 
  int query(int a, int b) {
    return query(0, 0, n, a, b);
  }
  void upd(int i, int v) {
    upd(0, 0, n, i, v);
  }
};