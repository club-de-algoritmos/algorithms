/**
 * Descripcion: lazy segment tree para suma y
 * actualizacion en rango. Rangos no inclusivos a la der.
 * [a,b) es el rango de la query y [s, e) el del nodo
 * Si los incrementos pueden ser negativos o cero, 
 * utilizar arreglo extra has_lazy, o buscar otro neutral
 * Uso: STree st;st.init(arr);st.upd(0, n, 3);st.query(0, n);
 * Tiempo de construccion: O(n)
 * Tiempo de consulta y actualizacion: O(log n)
 * Status: testeado en CSES 1651
 */
#define LAZY_NEUT 0
#define VAL_NEUT 0
struct STree {
  int n; vector<int> st, lazy;
  STree(int n):st(4*n+5,VAL_NEUT),lazy(4*n+5,LAZY_NEUT),n(n){}
  int comb(int x, int y) { return x + y; }
  void init(int k, int s, int e, vi& a) {
    if (s + 1 == e) { st[k] = a[s]; return; }
    int m = (s+e)/2;
    init(2*k+1, s, m, a); init(2*k+2, m, e, a);
    st[k] = comb(st[2*k+1], st[2*k+2]);
  }
  void push(int k, int s, int e) { 
    if (lazy[k] == LAZY_NEUT) return;
    st[k] += (e - s) * lazy[k];
    if(s+1!=e)lazy[2*k+1]+=lazy[k],lazy[2*k+2]+=lazy[k];
    lazy[k] = LAZY_NEUT;
  }
  int query(int k, int s, int e, int a, int b) {
    push(k, s, e);
    if (a <= s && e <= b) return st[k];
    if (e <= a || s >= b) return VAL_NEUT;
    int m = (s+e)/2;
    return comb(query(2*k+1,s,m,a,b),query(2*k+2,m,e,a,b));
  }
  void upd(int k, int s, int e, int a, int b, int v) {
    push(k, s, e);
    if (e <= a || s >= b) return;
    if (a<=s && e<=b){lazy[k] += v;push(k,s,e);return;}
    int m = (s+e)/2;
    upd(2*k+1,s,m,a,b,v); upd(2*k+2,m,e,a,b,v);
    st[k] = comb(st[2*k+1], st[2*k+2]);
  }
  int query(int a, int b) { return query(0, 0, n, a, b); }
  void upd(int a, int b, int v) { upd(0, 0, n, a, b, v); }
  void init(vi& a) { init(0, 0, n, a); }
};