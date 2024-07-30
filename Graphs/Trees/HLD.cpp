/*
 * Heavy-Light Decomposition
 * Descripcion: descompone un arbol en caminos pesados y aristas
 * ligeras de tal manera que un camino de cualquier hoja a la raiz
 * contiene a lo mucho log(n) aristas ligeras. Raiz debe ser 0
 * Si el valor lo contiene las aristas, asignar VALS_EDGES true
 * Tiempo: O((log N)^2)
 */

// Incluir Lazy Segment Tree

template <bool VALS_EDGES>
struct HLD {
  int N, tim = 0;
  vector<vi> adj;
  vi par, siz, head, pos;
  LazySegmentTree<int> tree;
  HLD(vector<vi> adj_)
      : N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1), head(N), pos(N) {
    tree.init(N);
    dfsSz(0);
    dfsHld(0);
  }
  void dfsSz(int v) {
    if (par[v] != -1) adj[v].erase(find(ALL(adj[v]), par[v]));
    for (int& u : adj[v]) {
      par[u] = v;
      dfsSz(u);
      siz[v] += siz[u];
      if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
    }
  }
  void dfsHld(int v) {
    pos[v] = tim++;
    for (int u : adj[v]) {
      head[u] = (u == adj[v][0] ? head[v] : u);
      dfsHld(u);
    }
  }
  template <class B>
  void process(int u, int v, B op) {
    for (; head[u] != head[v]; v = par[head[v]]) {
      if (pos[head[u]] > pos[head[v]]) swap(u, v);
      op(pos[head[v]], pos[v] + 1);
    }
    if (pos[u] > pos[v]) swap(u, v);
    op(pos[u] + VALS_EDGES, pos[v] + 1);
  }
  void modifyPath(int u, int v, int val) {
    process(u, v, [&](int l, int r) { tree.add(l, r, val); });
  }
  int queryPath(int u, int v) {
    int res = -1e9;
    process(u, v, [&](int l, int r) { res = max(res, tree.query(l, r)); });
    return res;
  }
  int querySubtree(int v) {  // modifySubtree es similar
    return tree.query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
  }
};