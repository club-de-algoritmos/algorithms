/*
 * Mos Algorithm
 * Descripcion: Es usado para responder consultas en
 * intervalos (L,R) de manera offline con base a un orden
 * especial basado en bloques moviendose de una consulta a
 * la siguiente anadiendo/removiendo puntos en el inicio o
 * el final.
 * Tiempo: O((N + Q) sqrt(Q))
 */

void add(int idx, int end) {
  ...
}  // add a[idx] (end = 0 or 1)
void del(int idx, int end) { ... }  // remove a[idx]
int calc(){...}  // compute current answer

vi mosAlgo(vector<pi> Q) {
  int L = 0, R = 0, blk = 350;  // ~N/sqrt(Q)
  vi s(SZ(Q)), res = s;
#define K(x) \
  pi(x.first / blk, x.second ^ -(x.first / blk & 1))
  iota(ALL(s), 0);
  sort(ALL(s),
       [&](int s, int t) { return K(Q[s]) < K(Q[t]); });
  for (int qi : s) {
    pi q = Q[qi];
    while (L > q.first) add(--L, 0);
    while (R < q.second) add(R++, 1);
    while (L < q.first) del(L++, 0);
    while (R > q.second) del(--R, 1);
    res[qi] = calc();
  }
  return res;
}