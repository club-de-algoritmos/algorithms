/**
 * Descripcion: tiene como principal funcion calcular la
 * suma del peso de las aristas del arbol minimo de
 * expansion (MST) de un grafo no dirigido, la estrategia es
 * ir construyendo gradualmente el MST, donde iterativamente
 * se coloca la arista disponible con menor peso y ademas no
 * conecte 2 nodos que pertenezcan al mismo componente.
 * Tiempo: O(E log E)
 */

#include <../Data Structure/DSU.h>

int kruskal(int V, vector<tuple<int, int, int>>
                       edges) {  // Arista {w, u, v}
  DSU dsu;
  dsu.init(V);

  sort(ALL(edges));

  int totalWeight = 0;
  for (int i = 0; i < SZ(edges) && V > 1; i++) {
    auto [w, u, v] = edges[i];
    if (!dsu.sameSet(u, v)) {
      totalWeight += w;
      V -= dsu.unite(u, v);
    }
  }
  return totalWeight;
}