/**
 * Descripcion: algunas funciones multiplicativas.
 * Para arbitrarias, es bueno basarse en la criba lineal.
 * Tiempo: O(N)
 */

void linear_sieve(int N) {
  vector<int> lp(N + 1), pr;
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

void mobius(int N) {
  vector<int> mu(N), check(N);
  mu[1] = 1;
  int tot = 0;
  for (int i = 2; i < N; ++i) {
    if (!check[i]) {
      prime[tot++] = i;
      mu[i] = -1;
    }
    for (int j = 0; j < tot; ++j) {
      if (i*prime[j] > N) break;
      check[i*prime[j]] = true;
      if (i % prime[j] == 0) {
        mu[i*prime[j]] = 0;
        break;
      } else mu[i*prime[j]]=-mu[i];
    }
  }
}