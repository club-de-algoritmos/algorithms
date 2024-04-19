/**
 * Descripcion: encuentra un valor entre un rango de numeros
 * Busqueda Binaria: divide el intervalo en 2 hasta
 * encontrar el valor minimo correcto Busqueda ternaria:
 * divide el intervalo en 3 para buscar el minimo/maximo de
 * una funcion.
 * Tiempo: O(log n)
 */

int binary_search(int l, int r) {
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (f(m)) {
      r = m;
    } else {
      l = m;
    }
  }
  return l;
}

double ternary_search(double l, double r) {
  while (r - l > EPS) {
    double m1 = l + (r - l) / 3;
    double m2 = r - (r - l) / 3;
    double f1 = f(m1);
    double f2 = f(m2);
    if (f1 < f2)  // Maximo de f(x)
      l = m1;
    else
      r = m2;
  }
  return f(l);
}