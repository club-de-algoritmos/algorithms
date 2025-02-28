/**
 * Descripcion: encuentra la envolvente convexa de un conjunto
 * de puntos 3D. Es el menor poliedro convexo que contiene
 * todos los puntos dados.
 * Te retorna un vector de caras en el que guarda el vector
 * normal del plano y los indices de los 3 puntos que forma
 * el triangulo.
 * Nota: Ningun conjunto de 4 puntos deben ser coplanar
 * Tiempo: O(n^2)
 */

struct PR {
  void ins(int x) { (a == -1 ? a : b) = x; }
  void rem(int x) { (a == x ? a : b) = -1; }
  int cnt() { return (a != -1) + (b != -1); }
  int a, b;
};

struct F {
  P3 q;
  int a, b, c;
};

vector<F> hull3d(const vector<P3>& A) {
  assert(SZ(A) >= 4);
  vector<vector<PR>> E(SZ(A), vector<PR>(SZ(A), {-1, -1}));
#define E(x, y) E[f.x][f.y]
  vector<F> FS;
  auto mf = [&](int i, int j, int k, int l) {
    P3 q = (A[j] - A[i]).cross((A[k] - A[i]));
    if (q.dot(A[l]) > q.dot(A[i])) q = q * -1;
    F f{q, i, j, k};
    E(a, b).ins(k);
    E(a, c).ins(j);
    E(b, c).ins(i);
    FS.push_back(f);
  };
  FOR(i, 0, 4) FOR(j, i + 1, 4) FOR(k, j + 1, 4) mf(i, j, k, 6 - i - j - k);

  FOR(i, 4, SZ(A)) {
    FOR(j, 0, SZ(FS)) {
      F f = FS[j];
      if (f.q.dot(A[i]) > f.q.dot(A[f.a])) {
        E(a, b).rem(f.c);
        E(a, c).rem(f.b);
        E(b, c).rem(f.a);
        swap(FS[j--], FS.back());
        FS.pop_back();
      }
    }
    int nw = SZ(FS);
    FOR(j, 0, nw) {
      F f = FS[j];
#define C(a, b, c) \
  if (E(a, b).cnt() != 2) mf(f.a, f.b, i, f.c);
      C(a, b, c);
      C(a, c, b);
      C(b, c, a);
    }
  }
  for (F& it : FS)
    if ((A[it.b] - A[it.a]).cross(A[it.c] - A[it.a]).dot(it.q) <= 0)
      swap(it.c, it.b);
  return FS;
};