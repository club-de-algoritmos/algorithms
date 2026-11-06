/**
 * Descripcion: longitud de la subsecuencia estrictamente creciente
 * mas larga (LIS). d[k] es el menor valor en el que puede terminar
 * una subsecuencia creciente de longitud k + 1.
 * Para no decreciente usar upper_bound en vez de lower_bound.
 * Reconstruccion: guardar p[i] = posicion donde se coloco a[i] en d.
 * Recorrer de derecha a izquierda tomando el primer i con p[i] = k,
 * luego el primero con p[i] = k - 1 y a[i] < ultimo tomado, etc.
 * Tiempo: O(n log n)
 */

int lis(const vi& a) {
  vi d;
  for (int x : a) {
    auto it = lower_bound(ALL(d), x);
    if (it == end(d)) d.pb(x);
    else *it = x;
  }
  return SZ(d);
}
