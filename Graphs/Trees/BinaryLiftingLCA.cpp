/**
 * Descripcion: siendo jump[i][j] el ancestro 2^j del nodo i,
 * el binary liftingnos permite obtener el k-esimo ancestro
 * de cualquier nodo en tiempo logaritmico, una aplicacion de
 * esto es para obtener el ancestro comun mas bajo (LCA).
 * Importante inicializar jump[i][0] para todo i.
 * Tiempo: O(n log n) en construccion y O(log n) por consulta
 */

const MAX = 1e5 + 5, LOG_MAX = 28;
vector<int> g[MAX];
int jump[MAX][LOG_MAX];
int depth[MAX];

void dfs(int u, int p = -1, int d = 0) {
  depth[u] = d;
  jump[u][0] = p;
  for (auto &v : g[u]) if (v != p) dfs(v, u, d + 1);
}

void build(int n) {
  memset(jump, -1, sizeof jump);

  dfs(0);

  for (int i = 1; i < LOG_MAX; i++)
    for (int u = 0; u < n; u++)
      if (jump[u][i - 1] != -1)
        jump[u][i] = jump[jump[u][i - 1]][i - 1];
}

int LCA(int p, int q) {
  if (depth[p] < depth[q])
    swap(p, q);

  int dist = depth[p] - depth[q];
  for (int i = LOG_MAX - 1; i >= 0; i--)
    if ((dist >> i) & 1)
      p = jump[p][i];

  if (p == q)
    return p;

  for (int i = LOG_MAX - 1; i >= 0; i--)
    if (jump[p][i] != jump[q][i]) {
      p = jump[p][i];
      q = jump[q][i];
    }

  return jump[p][0];
}

int dist(int u, int v) {
  return depth[u] + depth[v] - 2 * depth[LCA(u, v)];
}
