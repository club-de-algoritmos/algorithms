/**
 * Descripcion: crea un segment tree donde guarda sus
 * formas pasadas cuando se hace una actualizacion
 * soporta consultas y actualizaciones en rango
 * Tiempo: log(n)
 */

template <class T, int SZ>
struct pseg {
  static const int LIM = 1e7;
  struct node {
    int l, r;
    T val = 0, lazy = 0;
    void inc(T x) { lazy += x; }
    T get() { return val + lazy; }
  };
  node d[LIM];
  int nex = 0;
  int copy(int c) {
    d[nex] = d[c];
    return nex++;
  }
  T comb(T a, T b) { return a + b; }
  void pull(int c) {
    d[c].val = comb(d[d[c].l].get(), d[d[c].r].get());
  }
  //// MAIN FUNCTIONS
  T query(int c, int lo, int hi, int L, int R) {
    if (lo <= L && R <= hi) return d[c].get();
    if (R < lo || hi < L) return 0;
    int M = (L + R) / 2;
    return d[c].lazy +
           comb(query(d[c].l, lo, hi, L, M),
                query(d[c].r, lo, hi, M + 1, R));
  }
  int upd(int c, int lo, int hi, T v, int L, int R) {
    if (R < lo || hi < L) return c;
    int x = copy(c);
    if (lo <= L && R <= hi) {
      d[x].inc(v);
      return x;
    }
    int M = (L + R) / 2;
    d[x].l = upd(d[x].l, lo, hi, v, L, M);
    d[x].r = upd(d[x].r, lo, hi, v, M + 1, R);
    pull(x);
    return x;
  }
  int build(const vector<T>& arr, int L, int R) {
    int c = nex++;
    if (L == R) {
      if (L < SZ(arr)) d[c].val = arr[L];
      return c;
    }
    int M = (L + R) / 2;
    d[c].l = build(arr, L, M),
    d[c].r = build(arr, M + 1, R);
    pull(c);
    return c;
  }
  vi loc;  //// PUBLIC
  void upd(int lo, int hi, T v) {
    loc.push_back(upd(loc.back(), lo, hi, v, 0, SZ - 1));
  }
  T query(int ti, int lo, int hi) {
    return query(loc[ti], lo, hi, 0, SZ - 1);
  }
  void build(const vector<T>& arr) {
    loc.push_back(build(arr, 0, SZ - 1));
  }
};
