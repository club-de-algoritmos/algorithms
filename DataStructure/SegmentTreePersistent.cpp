/**
 * Descripcion: segment tree persistente para consulta de
 * minimos en un rango. Un segment tree es persistente si
 * mantiene datos viejos disponible tras actualizaciones.
 * init y upd retornan la nueva raiz, rt es la ultima raiz
 * Para mejorar velocidad, usar arreglos.
 * Uso: STree st;st.init(arr);
 * vi roots;roots.pb(st.upd(0,3));st.query(roots[1], 0, n);
 * Tiempo: log(n)
 * Status: testeado en SWERC 2020 - H. Figurines
 */
struct STree {
  #define ls st[k].l
  #define rs st[k].r
  #define lp ls, s, m
  #define rp rs, m, e
  #define NEUT 0
 
  struct Node {
    int v, l, r;
    Node() : v(NEUT), l(0), r(0) {}
    Node(int _v, int _l, int _r) {
      v = _v;
      l = _l;
      r = _r;
    }
  };
 
  int n, lastRoot;
  vector<Node> st;
 
  STree(int n) : n(n), st(1) {}
 
  int merge(int x, int y) {
    return x + y;
  }
 
  void pull(int k) {
    st[k].v = merge(st[ls].v, st[rs].v);
  }
 
  int cloneNode(Node node) {
    st.emplace_back(node.v, node.l, node.r);
    return (int)st.size() - 1;
  }

  int build(int k, int s, int e, vector<int>& a) {
    k = cloneNode(st[k]);
    if (s + 1 == e) {
      st[k].v = a[s];
      return k;
    }
    int m = (s + e) >> 1;
    ls = build(lp, a);
    rs = build(rp, a);
    pull(k);
    return k;
  }
 
  int query(int k, int s, int e, int a, int b) {
    if (e <= a || s >= b) {
      return NEUT;
    }
    if (a <= s && e <= b) {
      return st[k].v;
    }
    int m = (s + e) >> 1;
    return merge(query(lp, a, b), query(rp, a, b));
  }
 
  int upd(int k, int s, int e, int i, int v) {
    k = cloneNode(st[k]);
    if (s + 1 == e) {
      st[k].v = v;
      return k;
    }
    int m = (s + e) >> 1;
    if (i < m) {
      ls = upd(lp, i, v);
    } else {
      rs = upd(rp, i, v);
    }
    pull(k);
    return k;
  }
	
  int build(vector<int>& a) {
    return lastRoot = build(0, 0, n, a);
  }
  int query(int k, int a, int b) {
    return query(k, 0, n, a, b);
  }
  int upd(int k, int i, int v) {
    return lastRoot = upd(k, 0, n, i, v);
  }
};