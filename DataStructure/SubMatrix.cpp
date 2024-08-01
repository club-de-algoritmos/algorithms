/*
 * Descripcion: Calcula la suma de una submatriz rapidamente, dada
 * la esquina superior izquierda e inferior derecha
 * Uso:
 * SubMatrix<int> m(matriz);
 * m.sum(0,0,2,2); // 4 elemento arriba a la izquierda
 * Tiempo: O(N^2)
 */

template <class T>
struct SubMatrix {
  vector<vector<T>> p;
  SubMatrix(vector<vector<T>>& v) {
    int R = sz(v), C = sz(v[0]);
    p.assign(R + 1, vector<T>(C + 1));
    FOR(r, 0, R)
    FOR(c, 0, C)
    p[r + 1][c + 1] = v[r][c] + p[r][c + 1] + p[r + 1][c] - p[r][c];
  }
  T sum(int u, int l, int d, int r) {
    return p[d][r] - p[d][l] - p[u][r] + p[u][l];
  }
};