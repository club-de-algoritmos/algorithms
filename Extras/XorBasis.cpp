/*
 * Descripcion: calcula el XOR basis para un conjunto de numeros.
 * Cada elemento en el basis tiene su bit significativo diferente.
 * El elemento con el i-esimo bit activado se guarda
 * en basis[i] (si existe)
 * El numero de elementos distintos se calcula con (1ll << sz)
 * Tiempo: O(D)
 */
const int D = 60;
struct XorBasis {
  ll basis[D];
  int sz = 0;

  void insert(ll k) {
    for (int i = D - 1; i >= 0; i--) {
      if (!(k >> i & 1)) continue;
      if (!basis[i]) {
        basis[i] = k;
        sz++;
        return;
      }
      k ^= basis[i];
    }
  }

  // k-th smallest
  ll get_kth(ll k) {
    ll x = 0;
    int pref = sz;
    for (ll i = D - 1; i >= 0; i--) {
      if (!basis[i]) continue;
      ll p2 = 1ll << (pref - 1);
      ll mini_leq = 1;
      ll maxi_leq = p2;
      if (!(x >> i & 1)) mini_leq += p2, maxi_leq += p2;
      if (mini_leq <= k && maxi_leq >= k) {
        if (!(x >> i & 1)) k -= p2;
        x ^= basis[i];
      } else if (x >> i & 1)
        k -= p2;
      pref--;
    }
    return x;
  }

  // Checa si se puede formar el valor K
  bool check(ll k) {
    for (int i = D - 1; i >= 0; i--) {
      if (!(k >> i & 1)) continue;
      if (!basis[i]) {
        return false;
      }
      k ^= basis[i];
    }
    return true;
  }

  void merge(const XorBasis &other) { FOR(i, 0, D) insert(other.basis[i]); }
  void merge(const XorBasis &a, const XorBasis &b) {
    *this = a;
    merge(b);
  }
};