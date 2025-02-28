/*
 * Descripcion: Calcula con base en un plano un sistemas de coordenadas
 * para puntos 3D a 2D
 */

struct Coords {
  P3 o, dx, dy, dz;

  // De 3 puntos PQR en el plano
  Coords(P3 p, P3 q, P3 r) : o(p) {
    dx = (q - p).unit();
    dz = dx.cross(r - p).unit();
    dy = dz.cross(dx);
  }

  // De 4 puntos PQRS
  Coords(P3 p, P3 q, P3 r, P3 s) : o(p), dx(q - p), dy(r - p), dz(s - p) {}

  Point pos2D(P3 p) { return {(p - o).dot(dx), (p - o).dot(dy)}; }
  P3 pos3D(P3 p) { return {(p - o).dot(dx), (p - o).dot(dy), (p - o).dot(dz)}; }
};