/**
 * Problema: Dado a, b y n. Encuentra x,y que 
 * satisfagan la ecuacion ax + by = n.
 * Encuentra una de las soluciones, otras validas
 * pueden obtenerse por medio de:
 * x = x0 + k*(b/g), y = y0 - k*(a/g)
 * Tiempo: O(log n)
 */
pi linear_diophantine(int a, int b, int n) {
  int x0, y0, g = euclid(a, b, x0, y0);
  if(n%g)return {-1,-1}; // no solution exists
  x0 *= n / g, y0 *= n / g;
  return {x0, y0};
}
