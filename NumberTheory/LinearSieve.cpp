/**
 * Descripcion: algoritmo para precalcular los
 * numeros primos menor o iguales a N.
 * Sirve como guia para calcular funciones
 * multiplicativas
 * Tiempo: O(n)
 */
void sieve(int N) {
  vi lp(N + 1), pr;
  for (int i = 2; i <= N; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; i * pr[j] <= N; ++j) {
      lp[i * pr[j]] = pr[j];
      if (pr[j] == lp[i]) break;
    }
  }
}