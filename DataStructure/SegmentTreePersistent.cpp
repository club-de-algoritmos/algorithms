/**
 * Descripcion: segment tree persistente para consulta de
 * minimos en un rango. Un segment tree es persistente si
 * mantiene datos viejos disponible tras actualizaciones.
 * init y upd retornan la nueva raiz, rt es la ultima raiz
 * Para mejorar velocidad, usar arreglos.
 * Uso: STree st;st.init(arr);
 * vi roots;roots.pb(st.upd(0,3));st.query(roots[1], 0, n);
 * Tiempo: log(n)
 * Status: testeado en OmegaUp Campo Inestable
 */

#define NEUT 0
struct STree {
  vi st, L, R; int n, sz, rt;
  STree(int n):st(1,NEUT),L(1,0),R(1,0),n(n),rt(0),sz(1){}
  int comb(int x, int y) { return min(x, y); }
  int new_node(int v, int l = 0, int r = 0) {
    int ks = SZ(st); st.pb(v);L.pb(l);R.pb(r);
    return ks;
  }
  int init(int s, int e, vi &a) {
    if (s + 1 == e)return new_node(a[s]);
    int m = (s+e)/2, l = init(s,m,a), r = init(m,e,a);
    return new_node(comb(st[l], st[r]), l, r);
  }
  int upd(int k, int s, int e, int p, int v) {
    int ks = new_node(st[k], L[k], R[k]);
    if (s + 1 == e) { st[ks] = v; return ks; }
    int m = (s + e) / 2, ps;
    if (p < m) ps = upd(L[ks], s, m, p, v), L[ks] = ps;
    else ps = upd(R[ks], m, e, p, v), R[ks] = ps;
    st[ks] = comb(st[L[ks]], st[R[ks]]);
    return ks;
  }
  int query(int k, int s, int e, int a, int b) {
    if (e <= a || b <= s)return NEUT;
    if (a <= s && e <= b)return st[k];
    int m = (s + e) / 2;
    return comb(query(L[k],s,m,a,b),query(R[k],m,e,a,b));
  }
  int init(vi &a) { return init(0, n, a); }
  int upd(int k, int p, int v){return rt=upd(k,0,n,p,v);}
  int upd(int p, int v){return rt=upd(rt, p, v);}
  int query(int k, int a, int b){return query(k,0,n,a,b);};
};
