/**
 * Descripcion: algoritmo para precalcular los
 * numeros primos menor o iguales a N.
 * Tiempo: O(n log(log n))
 */
void sieve(int n) {
  vector<bool> is_prime(n + 1, 1);
  is_prime[0] = is_prime[1] = 0;
  for (ll p = 2; p <= n; p++) {
    if(!is_prime[p])continue;
    for(ll i=p*p;i<=n;i+=p)is_prime[i]=0;
    primes.push_back(p);
  }
}