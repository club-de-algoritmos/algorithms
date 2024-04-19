/*
 * Heavy-Light Decomposition
 * Descripcion: descompone un arbol en caminos pesados y
 * aristas ligeras de tal manera que un camino de cualquier
 * hoja a la raiz contiene a lo mucho log(n) aristas
 * ligeras. Raiz debe ser 0 Si el peso lo contiene las
 * aristas, asignar el valor a los "hijos" de los nodos y
 * cambiar lo del comentario
 * Tiempo: O((log N)^2)
 */

vi parent, depth, heavy, head, pos;
int cur_pos;

int dfs(int v) {
  int size = 1;
  int max_c_size = 0;
  for (int c : g[v]) {
    if (c != parent[v]) {
      parent[c] = v, depth[c] = depth[v] + 1;
      // Aqui puedes asignar el peso de la arista al hijo
      // cost[c] = w;
      int c_size = dfs(c);
      size += c_size;
      if (c_size > max_c_size)
        max_c_size = c_size, heavy[v] = c;
    }
  }
  return size;
}

void decompose(int v, int h) {
  head[v] = h, pos[v] = cur_pos++;
  // Aqui se puede realizar la actualizacion al segment tree
  // st.update(pos[v], cost[v]);
  if (heavy[v] != -1) decompose(heavy[v], h);
  for (int c : g[v]) {
    if (c != parent[v] && c != heavy[v]) decompose(c, c);
  }
}

void init() {
  int n = g.size();
  parent = vector<int>(n);
  depth = vector<int>(n);
  heavy = vector<int>(n, -1);
  head = vector<int>(n);
  pos = vector<int>(n);
  cur_pos = 0;

  dfs(0);
  decompose(0, 0);
}

// Pro-tip: si se quiere actualizar un camino con cierto
// valor utilizar esta misma funcion solo que en igual de
// igualar a res, realizar la actualizacion a un lazy
// segment tree
int query(int a, int b) {
  int res = 0;
  for (; head[a] != head[b]; b = parent[head[b]]) {
    if (depth[head[a]] > depth[head[b]]) swap(a, b);
    res = max(res, st.query(pos[head[b]], pos[b]));
  }
  if (depth[a] > depth[b]) swap(a, b);
  res = max(res, st.query(pos[a],
                          pos[b]));  // sumar pos[a]+1 si se
                                     // trabaja con aristas
  return res;
}