/**
 * Descripcion: Calcula la funcion de Mobius
 * para todo entero menor o igual a n
 * Tiempo: O(N)
 */
void mobius(int N) {
  vi mu(N), check(N);
  mu[1] = 1;
  int tot = 0;
  FOR(i, 2, N) {
    if (!check[i]) {  // i es primo
      prime[tot++] = i;
      mu[i] = -1;
    }
    FOR(j, 0, tot) {
      if (i * prime[j] > N) break;
      check[i * prime[j]] = true;
      if (i % prime[j] == 0) {
        mu[i * prime[j]] = 0;
        break;
      } else mu[i*prime[j]]=-mu[i];
    }
  }
}