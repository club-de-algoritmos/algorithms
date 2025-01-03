/**
 * Descripcion: lazy segment tree para suma y
 * actualizacion en rango. Rangos no inclusivos a la der.
 * [a,b) es el rango de la query y [s, e) el del nodo
 * Si los incrementos pueden ser negativos o cero, 
 * utilizar arreglo extra has_lazy, o buscar otro neutral
 * Uso: STree st;st.init(arr);st.upd(0, n, 3);st.query(0, n);
 * Tiempo de construccion: O(n)
 * Tiempo de consulta y actualizacion: O(log n)
 * Status: testeado en CSES Range Update Queries
 */
struct STree {
  #define ls (k << 1) + 1
  #define rs (k << 1) + 2
  #define lp ls, s, m
  #define rp rs, m, e

  int n;
  vector<int> st, lazy;

  STree(int n) : n(n), st((n << 2) + 5), lazy((n << 2) + 5) {}

  int merge(int x, int y) {
    return x + y;
  }

  void pull(int k) {
    st[k] = merge(st[ls], st[rs]);
  }

  void apply(int k, int s, int e, int v) {
    st[k] += (e - s) * v;
    lazy[k] += v;
  }

  void push(int k, int s, int e) {
    if (lazy[k]) {
      int m = (s + e) >> 1;
      apply(lp, lazy[k]);
      apply(rp, lazy[k]);
      lazy[k] = 0;
    }
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
    push(k, s, e);
    int m = (s + e) >> 1;
    if (a >= m) {
      return query(rp, a, b);
    }
    if (b <= m) {
      return query(lp, a, b);
    }
    return merge(query(lp, a, b), query(rp, a, b));
  }

  void upd(int k, int s, int e, int a, int b, int v) {
    if (a <= s && e <= b) {
      apply(k, s, e, v);
      return;
    }
    push(k, s, e);
    int m = (s + e) >> 1;
    if (a < m) {
      upd(lp, a, b, v);
    }
    if (b > m) {
      upd(rp, a, b, v);
    }
    pull(k);
  }

  int query(int a, int b) {
    return query(0, 0, n, a, b);
  }
  void upd(int a, int b, int v) {
    upd(0, 0, n, a, b, v);
  }
  void build(vector<int>& a) {
    build(0, 0, n, a);
  }
};