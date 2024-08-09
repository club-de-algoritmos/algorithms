/**
 * Descripcion: segment tree esparcido. Para suma en
 * rango y actualizacion en punto.
 * Un segment tree es esparcido cuando sus nodos se van 
 * creando conforme se vayan utilizando, lo que permite
 * manejar grandes rangos de indices. Es util cuando en
 * esta situacion necesitas un algoritmo online (no se
 * puede realizar compresion de coordenadas). 
 * Rangos no inclusivos a la der.
 * Para mejorar velocidad, usar arreglos.
 * [a,b) es el rango de la query y [s, e) el del nodo
 * Uso: STree st(1e18);st.upd(6, 3);st.query(5, 1e12);
 * Tiempo de consulta y actualizacion: O(log n)
 * Memoria total: O(qlog(n))
 * Status: testeado en CSES Salary Queries
 */
#define NEUT 0
struct STree {
  int n; vi st, L, R;
  STree(int n) : st(1, NEUT), L(1, -1), R(1, -1), n(n) {}
  int comb(int x, int y) { return x + y; }
  int new_node(){st.pb(NEUT);L.pb(-1);R.pb(-1);return SZ(st)-1;}
  int query(int k, int s, int e, int a, int b) {
    if (k == -1 || e <= a || s >= b) return NEUT;
    if (a <= s && e <= b) return st[k];
    int m = s + (e - s) / 2;
    return comb(query(L[k],s,m,a,b),query(R[k],m,e,a,b));
  }
  int upd(int k, int s, int e, int i, int v) {
    if (e <= i || s > i) return k;
    if (k == -1) {k = new_node();}
    if (s+1 == e) { st[k] = v; return k; }
    int m=s+(e-s)/2,le=L[k]==-1?0:st[L[k]],ri=R[k]==-1?0:st[R[k]];
    if (i < m) L[k] = upd(L[k],s,m,i,v), le = st[L[k]];
    else R[k] = upd(R[k],m,e,i,v), ri = st[R[k]];
    st[k] = comb(le, ri);
    return k;
  }
  int query(int a, int b) { return query(0, 0, n, a, b); }
  void upd(int i, int v) { upd(0, 0, n, i, v); }
};