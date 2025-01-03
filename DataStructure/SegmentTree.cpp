/**
 * Descripcion: segment tree para suma en rango y
 * actualizacion en punto. Rangos no inclusivos a la der.
 * [a,b) es el rango de la query y [s, e) el del nodo
 * Uso: STree st;st.build(arr);st.upd(0, 3);st.query(0, n);
 * Tiempo de construccion: O(n)
 * Tiempo de consulta y actualizacion: O(log n)
 * Memoria total: O(n + qlog(n))
 * Status: testeado en CSES Pizzeria Queries
 */
struct STree {
  #define ls (k << 1) + 1
  #define rs (k << 1) + 2
  #define lp ls, s, m
  #define rp rs, m, e

  int n;
  vector<int> st;

  STree(int n) : n(n), st((n << 2) + 5) {}

  int merge(int x, int y) {
    return x + y;
  }

  void pull(int k) {
    st[k] = merge(st[ls], st[rs]);
  }

  void build(int k, int s, int e, vector<int>& a) {
    if (s + 1 == e) {
      st[k] = a[s];
      return;
    }
    int m = (s + e) >> 1;
    build(lp, a);
    build(rp, a);
    pull(k);
  }

  int query(int k, int s, int e, int a, int b) {
    if (a <= s && e <= b) {
      return st[k];
    }
    int m = (s + e) >> 1;
    if (a >= m) {
      return query(rp, a, b);
    }
    if (b <= m) {
      return query(lp, a, b);
    }
    return merge(query(lp, a, b), query(rp, a, b));
  }

  void upd(int k, int s, int e, int i, int v) {
    if (s + 1 == e) {
      st[k] = v;
      return;
    }
    int m = (s + e) >> 1;
    if (i < m) {
      upd(lp, i, v);
    } else {
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
  void build(vector<int>& a) {
    build(0, 0, n, a);
  }
};