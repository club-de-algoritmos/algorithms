/**
 * Descripcion: Segment tree 2D para suma en un
 * rectangulo y actualizacion en punto. 
 * Implementacion iterativa con 4x menos memoria.
 * Uso:
 * STree st(n, m); st.build(a);
 * st.upd(x, y, v);
 * int ans = st.query(x0, y0, x1, y1);
 * Tiempo: O(nm) construccion, O(\log n \log m) consulta y actualizacion
 */

struct STree {
  int n, m;
  vector<vi> st;
  STree(int n, int m) : n(n), m(m), st(2 * n, vi(2 * m, 0)) {}
  int comb(int x, int y) { return x + y; }
  void build(vector<vi>& a) {
    FOR (i, 0, n) FOR (j, 0, m)
      st[i + n][j + m] = a[i][j];
    FOR (i, 0, n) for (int j = m - 1; j; --j)
      st[i + n][j] = comb(st[i + n][j << 1], st[i + n][j << 1 | 1]);
    for (int i = n - 1; i; --i) FOR (j, 0, 2 * m)
      st[i][j] = comb(st[i << 1][j], st[i << 1 | 1][j]);
  }
  void upd(int x, int y, int v) {
    st[x + n][y + m] = v;
    for (int j = y + m; j > 1; j >>= 1) st[x + n][j >> 1] = comb(st[x + n][j], st[x + n][j ^ 1]);
    for (int i = x + n; i > 1; i >>= 1) for (int j = y + m; j; j >>= 1)
      st[i >> 1][j] = comb(st[i][j], st[i ^ 1][j]);
  }
  int query(int x0, int y0, int x1, int y1) {
    int r = 0;
    for (int i0 = x0 + n, i1 = x1 + n; i0 < i1; i0 >>= 1, i1 >>= 1) {
      int t[4], q = 0;
      if (i0 & 1) t[q++] = i0++;
      if (i1 & 1) t[q++] = --i1;
      FOR (k, 0, q) for (int j0 = y0 + m, j1 = y1 + m; j0 < j1; j0 >>= 1, j1 >>= 1) {
        if (j0 & 1) r = comb(r, st[t[k]][j0++]);
        if (j1 & 1) r = comb(r, st[t[k]][--j1]);
      }
    }
    return r;
  }
};
