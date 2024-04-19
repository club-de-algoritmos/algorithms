/**
 * Descripcion: encuentra la envolvente convexa de un
 * conjunto de puntos dados. Una envolvente convexa es la
 * minima region convexa que contiene a todos los puntos del
 * conjunto.
 * Tiempo: O(n log n)
 */

vector<Point> convexHull(vector<Point> pts) {
  if (SZ(pts) <= 1) return pts;
  sort(ALL(pts));
  vector<Point> h(SZ(pts) + 1);
  int s = 0, t = 0;
  for (int it = 2; it--; s = --t, reverse(ALL(pts)))
    for (Point p : pts) {
      while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0)
        t--;  // quitar = si se incluye colineares
      h[t++] = p;
    }
  return {h.begin(),
          h.begin() + t - (t == 2 && h[0] == h[1])};
}