/**
 * Descripcion: algoritmo para obtener el orden topologico
 * de un grafo dirigido, definido como el ordenamiento de
 * sus vertices tal que para cada arista (u, v), u este
 * antes que v en el ordenamiento. Si existen ciclos, dicho
 * ordenamiento no existe.
 * Tiempo: O(V + E)
 */

int V;
vi graph[MAXN];
vi sorted_nodes;
bool visited[MAXN];

void dfs(int u) {
  visited[u] = true;
  for (auto v : graph[u])
    if (!visited[v]) dfs(v);
  sorted_nodes.push(u);
}

void toposort() {
  for (int i = 0; i < V; i++)
    if (!visited[i]) dfs(i);
  reverse(ALL(sorted_nodes));

  assert(sorted_nodes.size() == V);
}

void lexicographic_toposort() {
  priority_queue<int> q;
  for (int i = 0; i < V; i++)
    if (in_degree[i] == 0) q.push(-i);

  while (!q.empty()) {
    int u = -q.top();
    q.pop();
    sorted_nodes.push_back(u);
    for (int v : graph[u]) {
      in_degree[v]--;
      if (in_degree[v] == 0) q.push(-v);
    }
  }

  assert(sorted_nodes.size() == V);
}