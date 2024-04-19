/**
 * Descripcion: cuando se trabaja con caminos en un arbol,
 * es util descomponer a este recursivamente en sub-arboles
 * formados al eliminar su centroide, el centroide de un
 * arbol es un nodo u tal que si lo eliminas, este se divide
 * en sub-arboles con un numero de nodos no mayor a la mitad
 * del original, todos los arboles tienen un centroide, y a
 * lo mas 2. Esto provoca que el arbol sea dividido en
 * sub-arboles de distintos niveles de descomposicion, por
 * comodidad, un nodo v es un centroide ancestro de otro
 * nodo u, si v, en algun nivel, fue el centroide que separo
 * al componente de u en sub-arboles. Todo camino del arbol
 * original se puede expresar como la concatenacion de dos
 * caminos del tipo: (u, A(u)), (u, A(A(u))), (u,
 * A(A(A(u))))..., etc. Ya que en cada nivel k el numero de
 * nodos de algun componente es a lo mas |V| / 2^k, un nodo
 * puede estar en log |V| componentes, es decir, puede tener
 * como maximo log |V| ancestros.
 * Tiempo: O(|V| log |V|)
 */
vector<int> g[MAX];
bool is_removed[MAX];
int subtree_size[MAX];

int get_subtree_size(int u, int parent = -1) {
  subtree_size[u] = 1;
  for (int v : g[u]) {
    if (v == parent || is_removed[v]) continue;
    subtree_size[u] += get_subtree_size(v, u);
  }
  return subtree_size[u];
}

int get_centroid(int u, int tree_size, int parent = -1) {
  for (int v : g[u]) {
    if (v == parent || is_removed[v]) continue;
    if (subtree_size[v] * 2 > tree_size)
      return get_centroid(v, tree_size, u);
  }
  return u;
}

void build_centroid_decomposition(int u = 0) {
  int centroid = get_centroid(u, get_subtree_size(u));

  // do something

  is_removed[centroid] = true;

  for (int v : g[centroid]) {
    if (is_removed[v])
      continue build_centroid_decomposition(v);
  }
}
