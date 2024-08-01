/**
 * Problema: Dado a, b y n. Encuentra 'x' y 'y' que satisfagan la ecuacion ax + by = n.
 * Imprimir cualquiera de las 'x' y 'y' que la satisfagan.
 */

void solution(int a, int b, int n) {
  int x0, y0, g = euclid(a, b, x0, y0);
  if (n % g != 0) {
    cout << "No Solution Exists" << ENDL;
    return;
  }
  x0 *= n / g;
  y0 *= n / g;
  // single valid answer
  cout << "x = " << x0 << ", y = " << y0 << ENDL;

  // other valid answers can be obtained through...
  // x = x0 + k*(b/g)
  // y = y0 - k*(a/g)
  for (int k = -3; k <= 3; k++) {
    int x = x0 + k * (b / g);
    int y = y0 - k * (a / g);
    cout << "x = " << x << ", y = " << y << ENDL;
  }
}
