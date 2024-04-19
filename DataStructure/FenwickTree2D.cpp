/**
 * Descripcion: arbol binario indexado 2D, util para
 * consultas en un espacio 2D como una matriz Tiempo:
 * Construir el BIT: O(NM log(N)*log(M))
 * Consultas y Actualizaciones: O(log(N)*log(M))
 */

int ft[MAX + 1][MAX + 1];
void upd(int i0, int j0, int v) {
  for (int i = i0 + 1; i <= MAX; i += i & -i)
    for (int j = j0 + 1; j <= MAX; j += j & -j)
      ft[i][j] += v;
}
int get(int i0, int j0) {
  int r = 0;
  for (int i = i0; i; i -= i & -i)
    for (int j = j0; j; j -= j & -j) r += ft[i][j];
  return r;
}
int get_sum(int i0, int j0, int i1, int j1) {
  return get(i1, j1) - get(i1, j0) - get(i0, j1) +
         get(i0, j0);
}
