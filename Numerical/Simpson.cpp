/*
 * Descripcion: Calcula el valor de una integral definida
 * Tiempo: O(pasos)
 */

const int N = 1000 * 1000;  // numero de pasos (entre mas grande mas preciso)

double simpson_integration(double a, double b) {
  double h = (b - a) / N;
  double s = f(a) + f(b);
  for (int i = 1; i <= N - 1; ++i) {
    double x = a + h * i;
    s += f(x) * ((i & 1) ? 4 : 2);
  }
  s *= h / 3;
  return s;
}