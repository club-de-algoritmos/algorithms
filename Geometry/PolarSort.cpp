
/*
 * Descripcion: ordena los puntos segun el angulo.
 * Comienza a partir de la izquierda en contra de las
 * manecillas
 */

int half(Point p) {
  return p.y > 0 || (p.y == 0 && p.x < 0);
}

// Pro-tip: si los puntos se encuentran en la misma
// direccion son considerados iguales, entonces se ordenaran
// arbitrariamente. Si se busca un desempate, se puede usar
// la magnitud sq(v)
void polarSort(vector<Point> &v) {
  sort(ALL(v), [](Point v, Point w) {
    return make_tuple(half(v), 0) <
           make_tuple(half(w), v.cross(w));
  });
}

void polarSortAround(Point o, vector<Point> &v) {
  sort(ALL(v), [](Point v, Point w) {
    return make_tuple(half(v - o), 0) <
           make_tuple(half(w - o), (v - o).cross(w - o));
  });
}

// Si se quiere modificar que el primer angulo del polar
// sort sea el vector v utilizar esta implementacion
Point v = {/* el que sea menos {0,0} */};
bool half(Point p) {
  return v.cross(p) < 0 ||
         (v.cross(p) == 0 && v.dot(p) < 0);
}