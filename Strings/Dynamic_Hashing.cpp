/*
 * Hashing Dinamico
 * Descripcion: Convierte strings en hashes para compararlos
 * eficientemente
 * - Util para comparar strings o un substring de este
 * - Tambien puede cambiar un caracter del string
 * eficientemente Uso:
 * - hash.get(inicio, fin); [inicio, fin)
 *   comparar dos string hash.get(l, f) == hash.get(l, f)
 * - set(posicion, caracter) indexado en 0
 *   Cambia el caracter de una posicion en el string
 * Aplicaciones:
 * - Checar si substrings de un string son palindromos
 * Complejidad:
 * - Construccion O(n log(n))
 * - Query y update O(log(n))
 */

#include <bits/stdc++.h>
// Pura gente del coach moy
using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

const ll MOD = 998244353;
const ii BASE = {1e9 + 7, 1e9 + 9};

ii operator+(const ii a, const ii b) {
  return {(a.first + b.first) % MOD,
          (a.second + b.second) % MOD};
}

ii operator+(const ii a, const ll b) {
  return {(a.first + b) % MOD, (a.second + b) % MOD};
}

ii operator-(const ii a, const ii b) {
  return {(MOD + a.first - b.first) % MOD,
          (MOD + a.second - b.second) % MOD};
}

ii operator*(const ii a, const ii b) {
  return {(a.first * b.first) % MOD,
          (a.second * b.second) % MOD};
}

ii operator*(const ii a, const ll b) {
  return {(a.first * b) % MOD, (a.second * b) % MOD};
}

inline ll modpow(ll x, ll p) {
  if (!p) return 1;
  return (modpow(x * x % MOD, p >> 1) * (p % 2 ? x : 1)) %
         MOD;
}

inline ll modinv(ll x) { return modpow(x, MOD - 2); }

struct Hash_Bit {
  int N;
  string S;
  vector<ii> fen, pp, ipp;

  Hash_Bit(string S_) {
    S = S_;
    N = S.size();
    fen.resize(N + 1);
    pp.resize(N);
    ipp.resize(N);
    pp[0] = ipp[0] = {1, 1};
    const ii ibase = {modinv(BASE.first),
                      modinv(BASE.second)};

    for (int i = 1; i < N; i++) {
      pp[i] = pp[i - 1] * BASE;
      ipp[i] = ipp[i - 1] * ibase;
    }

    for (int i = 0; i < N; i++) {
      update(i, S[i]);
    }
  }

  void update(int i, ll x) {
    ii p = pp[i] * x;
    for (++i; i <= N; i += i & -i) {
      fen[i] = fen[i] + p;
    }
  }

  ii query(int i) {
    ii ret = {0, 0};
    for (; i; i -= i & -i) {
      ret = (ret + fen[i]);
    }
    return ret;
  }

  void set(int idx, char c) {
    int d = (MOD + c - S[idx]) % MOD;
    S[idx] = c;
    update(idx, d);
  }

  ii get(int start, int end) {
    return (query(end) - query(start)) * ipp[start];
  }
};

int main() {
  string s;
  cin >> s;

  int sz = s.size();
  Hash_Bit hash(s);

  return 0;
}
