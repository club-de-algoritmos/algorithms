/**
 * Descripcion: Estos 2 algoritmos encuentran por medio de la Criba
 * de Eratostenes todos los numeros primos menor o iguales a n, difieren
 * por su estrategia y por consecuente su complejidad temporal.
 * Tiempo metodo #1: O(n log(log n))
 * Tiempo metodo #2: O(n)
 */
ll sieve_size;
vl primes;
void sieve(int n) {
  vector<bool> is_prime(n + 1, 1);

  is_prime[0] = is_prime[1] = 0;
  for (ll p = 2; p <= n; p++) {
    if (is_prime[p]) {
      for (ll i = p * p; i <= n; i += p) is_prime[i] = 0;
      primes.push_back(p);
    }
  }
}
void sieve(int N) {
  vector<int> lp(N + 1);
  vector<int> pr;

  for (int i = 2; i <= N; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; i * pr[j] <= N; ++j) {
      lp[i * pr[j]] = pr[j];
      if (pr[j] == lp[i]) {
        break;
      }
    }
  }
}

/*
 *Descripcion: Calcular todos los factores primos de N
 */
vi primeFactors(ll N) {
  vi factors;
  for (int i = 0; i < (int)primes.size() && primes[i] * primes[i] <= N; ++i)
    while (N % primes[i] == 0) {
      N /= primes[i];
      factors.push_back(primes[i]);
    }
  if (N != 1) factors.push_back(N);
  return factors;
}

/**
 * Descripcion: Calcula la funcion de Mobius
 * para todo entero menor o igual a n
 * Tiempo: O(N)
 */
void preMobius(int N) {
  memset(check, false, sizeof(check));
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
      } else {
        mu[i * prime[j]] = -mu[i];
      }
    }
  }
}

// Primos menores a 1000:
//      2     3     5     7    11    13    17    19    23    29    31    37
//     41    43    47    53    59    61    67    71    73    79    83    89
//     97   101   103   107   109   113   127   131   137   139   149   151
//    157   163   167   173   179   181   191   193   197   199   211   223
//    227   229   233   239   241   251   257   263   269   271   277   281
//    283   293   307   311   313   317   331   337   347   349   353   359
//    367   373   379   383   389   397   401   409   419   421   431   433
//    439   443   449   457   461   463   467   479   487   491   499   503
//    509   521   523   541   547   557   563   569   571   577   587   593
//    599   601   607   613   617   619   631   641   643   647   653   659
//    661   673   677   683   691   701   709   719   727   733   739   743
//    751   757   761   769   773   787   797   809   811   821   823   827
//    829   839   853   857   859   863   877   881   883   887   907   911
//    919   929   937   941   947   953   967   971   977   983   991   997

// Otros primos:
//    El primo mas grande menor que 10 es 7.
//    El primo mas grande menor que 100 es 97.
//    El primo mas grande menor que 1000 es 997.
//    El primo mas grande menor que 10000 es 9973.
//    El primo mas grande menor que 100000 es 99991.
//    El primo mas grande menor que 1000000 es 999983.
//    El primo mas grande menor que 10000000 es 9999991.
//    El primo mas grande menor que 100000000 es 99999989.
//    El primo mas grande menor que 1000000000 es 999999937.
//    El primo mas grande menor que 10000000000 es 9999999967.
//    El primo mas grande menor que 100000000000 es 99999999977.
//    El primo mas grande menor que 1000000000000 es 999999999989.
//    El primo mas grande menor que 10000000000000 es 9999999999971.
//    El primo mas grande menor que 100000000000000 es 99999999999973.
//    El primo mas grande menor que 1000000000000000 es 999999999999989.
//    El primo mas grande menor que 10000000000000000 es 9999999999999937.
//    El primo mas grande menor que 100000000000000000 es 99999999999999997.
//    El primo mas grande menor que 1000000000000000000 es 999999999999999989.
