/**
 * Descripcion: arbol de segmentos esparcido, es util cuando
 * el rango usado es bastante largo. Lo que cambia es que
 * solo se crean los nodos del arbol que se van utilizando,
 * por lo que se utilizan 2 punteros para los hijos de cada
 * nodo. Uso: node ST();
 * Complejidad: O(log n)
 */

const int SZ = 1 << 17;
template <class T>
struct node {
  T val = 0;
  node<T>* c[2];
  node() { c[0] = c[1] = NULL; }
  void upd(int ind, T v, int L = 0, int R = SZ - 1) {
    if (L == ind && R == ind) {
      val += v;
      return;
    }
    int M = (L + R) / 2;
    if (ind <= M) {
      if (!c[0]) c[0] = new node();
      c[0]->upd(ind, v, L, M);
    } else {
      if (!c[1]) c[1] = new node();
      c[1]->upd(ind, v, M + 1, R);
    }
    val = 0;
    for (int i = 0; i < 2; i++)
      if (c[i]) val += c[i]->val;
  }
  T query(int lo, int hi, int L = 0,
          int R = SZ - 1) {  // [l, r]
    if (hi < L || R < lo) return 0;
    if (lo <= L && R <= hi) return val;
    int M = (L + R) / 2;
    T res = 0;
    if (c[0]) res += c[0]->query(lo, hi, L, M);
    if (c[1]) res += c[1]->query(lo, hi, M + 1, R);
    return res;
  }
};
