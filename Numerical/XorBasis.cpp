/*
 * Descripcion: calcula el XOR basis en Row Echelon Form.
 * El K-esimo menor elemento (0-indexed) es el mapeo 
 * binario de K a los elementos del basis.
 * Si no se requiere getKth(), se puede omitir el segundo for 
 * dentro de insert() y la insercion lineal, cambiandolo
 * simplemente por un `basis.pb(x)`.
 * Los elementos se mantienen ordenados descendentemente.
 * Tiempo: O(D), donde D es el numero de bits del maximo valor.
 */
struct XorBasis {
  vector<int> basis;

  void insert(int x) {
    for (int b : basis) x = min(x, x ^ b);
    if (!x) return;
    
    for (int& b : basis) b = min(b, b ^ x);
    basis.insert(lower_bound(ALL(basis), x, greater<>()), x);
  }

  int getKth(int k) {
    int x = 0;
    for (int i = 0; i < SZ(basis); i++) {
      if ((k >> (SZ(basis) - 1 - i)) & 1) {
        x ^= basis[i];
      }
    }
    return x;
  }
};