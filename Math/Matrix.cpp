/**
 * Descripcion: estructura de matriz con algunas operaciones
 * basicas se suele utilizar para la multiplicacion y/o
 * exponenciacion de matrices Aplicaciones: Calcular el
 * n-esimo fibonacci en tiempo logaritmico, esto es posible
 * ya que para la matriz M = {{1, 1},{1, 0}}, se cumple que
 * M^n = {{F[n + 1], F[n]}, {F[n], F[n - 2]}} Dado un grafo,
 * su matriz de adyacencia M, y otra matriz P tal que P =
 * M^k, se puede demostrar que P[i][j] contiene la cantidad
 * de caminos de longitud k que inician en el i-esimo nodo y
 * terminan en el j-esimo.
 * Tiempo: O(n^3 * log p) para la exponenciacion y O(n^3)
 * para la multiplicacion
 */

template <typename T>
struct Matrix {
  using VVT = vector<vector<T>>;

  VVT M;
  int n, m;

  Matrix(VVT aux) : M(aux), n(M.size()), m(M[0].size()) {}

  Matrix operator*(Matrix& other) const {
    int k = other.M[0].size();
    VVT C(n, vector<T>(k, 0));
    FOR(i, 0, n)
    FOR(j, 0, k)
    FOR(l, 0, m)
    C[i][j] =
        (C[i][j] + M[i][l] * other.M[l][j] % MOD) % MOD;
    return Matrix(C);
  }

  Matrix operator^(ll p) const {
    assert(p >= 0);
    Matrix ret(VVT(n, vector<T>(n))), B(*this);
    FOR(i, 0, n)
    ret.M[i][i] = 1;

    while (p) {
      if (p & 1) ret = ret * B;
      p >>= 1;
      B = B * B;
    }
    return ret;
  }
};