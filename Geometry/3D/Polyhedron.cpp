/*
 * Un poliedro es un cuerpo geométrico tridimensional
 * con caras planas que encierra un volumen finito
 */

// Retorna el vector area * 2 (evita decimales)
P3 vectorArea2(vector<P3> &p) {
  P3 S = {0, 0, 0};
  int n = SZ(p);
  FOR(i, 0, n) S = S + p[i].cross(p[(i + 1) % n]);
  return S;
}

double area(vector<P3> &p) { return vectorArea2(p).norm() / 2.0; }

// Dado un vector de caras planas retorna el volumen
double volume(vector<vector<P3>> faces) {
  double vol6 = 0.0;
  for (auto face : faces) {
    vol6 += vectorArea2(face).dot(face[0]);
  }
  return abs(vol6) / 6.0;
}