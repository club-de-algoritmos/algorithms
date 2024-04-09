/**
 * Descripcion: crea un segment tree donde guarda sus
 * formas pasadas cuando se hace una actualizacion
 * Tiempo: log(n)
 */

#define oper(a,b) (min(a, b))
#define NEUT 0
struct STree { // persistent segment tree for min over integers
  vector<int> st, L, R; int n, sz, rt;
  STree(int n) : st(1, NEUT), L(1, 0), R(1, 0), n(n), rt(0), sz(1) {}
  int new_node(int v, int l = 0, int r = 0) {
    int ks = SZ(st);
    st.pb(v);L.pb(l);R.pb(r);
    return ks;
  }
  int init(int s, int e, vi &a) { // not necessary in most cases
    if (s + 1 == e)return new_node(a[s]);
    int m = (s + e) / 2, l = init(s, m, a), r = init(m, e, a);
    return new_node(oper(st[l], st[r]), l, r);
  }
  int upd(int k, int s, int e, int p, int v) {
    int ks = new_node(st[k], L[k], R[k]);
    if (s + 1 == e) { st[ks] = v; return ks; }
    int m = (s + e) / 2, ps;
    if (p < m) ps = upd(L[ks], s, m, p, v), L[ks] = ps;
    else ps = upd(R[ks], m, e, p, v), R[ks] = ps;
    st[ks] = oper(st[L[ks]], st[R[ks]]);
    return ks;
  }
  int query(int k, int s, int e, int a, int b) {
    if (e <= a || b <= s)return NEUT;
    if (a <= s && e <= b)return st[k];
    int m = (s + e) / 2;
    return oper(query(L[k], s, m, a, b), query(R[k], m, e, a, b));
  }
  int init(vi &a) { return init(0, n, a); }
  int upd(int k, int p, int v) { return rt = upd(k, 0, n, p, v); }
  int upd(int p, int v) { return upd(rt, p, v); } // update on last root, returns new root
  int query(int k, int a, int b) { return query(k, 0, n, a, b); }; // [a, b)
  // k -> starting root
};
