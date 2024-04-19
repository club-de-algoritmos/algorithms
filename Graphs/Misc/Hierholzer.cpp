/*
 * Descripcion: busca un camino euleriano en el grafo dado.
 * Un camino euleriano se define como el recorrido de un
 * grafo que visita cada arista del grafo exactamente una
 * vez Un grafo no dirigido es euleriano si, y solo si: es
 * conexo y todos los vertices tienen un grado par Un grafo
 * dirigido es euleriano si, y solo si: es conexo y todos
 * los vertices tienen el mismo numero de aristas entrantes
 * y salientes. Si hay, exactamente, un vertice u que tenga
 * una arista saliente adicional y, exactamente, un vertice
 * v que tenga una arista entrante adicional, el grafo
 * contara con un camino euleriano de u a v
 * Tiempo: O(E)
 */

int N;
vector<vi> graph;  // Grafo dirigido

vi hierholzer(int s) {
  vi ans, idx(N, 0), st;
  st.pb(s);
  while (!st.empty()) {
    int u = st.back();
    if (idx[u] < (int)graph[u].size()) {
      st.pb(graph[u][idx[u]]);
      ++idx[u];
    } else {
      ans.pb(u);
      st.pop_back();
    }
  }
  reverse(all(ans));
  return ans;
}