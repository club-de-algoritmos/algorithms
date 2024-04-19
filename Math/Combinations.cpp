/**
 * Descripcion: Utilizando el metodo de ModOperations.cpp,
 * calculamos de manera eficiente los inversos modulares de
 * x (arreglo inv) y de x! (arreglo invfact), para toda x <
 * MAXN, se utiliza el hecho de que comb(n, k) = (n!) / (k!
 * * (n - k)!)
 * Tiempo: O(MAXN) en el precalculo de inversos modulares y
 * O(1) por query.
 */
ll invfact[MAXN];
void precalc_invfact() {
  precalc_inv();
  invfact[1] = 1;
  for (int i = 2; i < MAXN; i++)
    invfact[i] = invfact[i - 1] * inv[i] % MOD;
}

ll comb(int n, int k) {
  if (n < k) return 0;
  return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
}

/**
 * Descripcion: Se basa en el teorema de lucas, se puede
 * utilizar cuando tenemos una MAXN larga y un modulo m
 * relativamente chico. Tiempo: O(m log_m(n))
 */
ll comb(int n, int k) {
  if (n < k || k < 0) return 0;
  if (n == k) return 1;
  return comb(n % MOD, k % MOD) * comb(n / MOD, k / MOD) %
         MOD;
}

/*
 * Descripcion: Se basa en el triangulo de pascal, vale la
 * pena su uso cuando no trabajamos con modulos (pues no
 * tenemos una mejor opcion), usa DP. Tiempo: O(n^2)
 */
ll dp[MAXN][MAXN];
ll comb(int n, int k) {
  if (k > n || k < 0) return 0;
  if (n == k || k == 0) return 1;
  if (dp[n][k] != -1) return dp[n][k];
  return dp[n][k] = comb(n - 1, k) + comb(n - 1, k - 1);
}

void calc_comb() {
  FOR(i, 0, MAXN) {
    comb[i][0] = comb[i][i] = 1;
    FOR(j, 1, i)
    comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
  }
}