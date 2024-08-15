/**
 * Descripcion: tiene como principal funcion calcular la suma del
 * peso de las aristas del arbol minimo de expansion (MST) de un grafo
 * no dirigido, la estrategia es ir construyendo gradualmente el MST, 
 * donde iterativamente se coloca la arista disponible con menor peso y
 * ademas no conecte 2 nodos que pertenezcan al mismo componente.
 * Tiempo: O(E log E)
 * Status: testeado en ICPC LATAM 2017 - Imperial Roads 
 */

#include <../Data Structure/DSU.h>

int kruskal(int n, vector<tuple<int, int, int>>& e) {
  sort(ALL(e));
  DSU dsu;
  dsu.init(n);
  int mst = 0;
  for (auto &[w, u, v]:e)if(dsu.get(u)!=dsu.get(v)){
    mst += w;
    dsu.join(u, v);
    if (--n == 1) break;
  }
  return mst;  
}