/**
 * Descripcion: Precalculo de modulos
 * inversos para toda x <= MAX.
 * Se asume que LIM <= m y que m es primo
 * Tiempo: O(MAX)
 */
ll inv[MAX];
void precalc_inverse(int m) {
  inv[1] = 1;
  FOR(i, 2, MAX) {
    inv[i] = m - (m/i) * inv[m%i] % m;
  }
}
/**
 * Descripcion: Precalculo de un solo
 * inverso, usa el primer metodo si m
 * es primo, y el segundo en otro caso.
 * Tiempo: O(log m)
 */
#include "Euclid.h"
ll inverse(ll b){return be(b,MOD-2)%MOD;}
ll inverse(ll a){
  ll x, y, d = euclid(a, MOD, x, y);
  assert(d == 1);
  return (x + MOD) % MOD;
}
