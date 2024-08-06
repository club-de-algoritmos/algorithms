/**
 * Descripcion: siendo jmp[i][j] el ancestro 2^j del nodo i,
 * el binary liftingnos permite obtener el k-esimo ancestro
 * de cualquier nodo en tiempo logaritmico, una aplicacion de
 * esto es para obtener el ancestro comun mas bajo (LCA).
 * Importante inicializar jmp[i][0] para todo i.
 * Tiempo: O(n log n) en construccion y O(log n) por consulta
 */

constexpr int maxlog = 25;
void dfs(vector<vi>& g, vector<vi>& jmp, vi& depth, int u, int p = -1, int d = 0) {
  depth[u]=d;
  jmp[u][0]=p;
  for (auto &v:g[u])if(v!=p)dfs(g,jmp,depth,v,u,d+1);
}
pair<vector<vi>,vi> build(vector<vi>& g) {
  int n = SZ(g);
  vi depth(n);
  vector<vi> jmp(n, vi(maxlog, -1));
  dfs(g, jmp, depth, 0);
  for(int i=1;i<maxlog;i++)for(int u=0;u<n;u++)if(jmp[u][i-1]!=-1)
    jmp[u][i]=jmp[jmp[u][i-1]][i-1];
  return {jmp, depth};
}
int LCA(vector<vi>& jmp, vi& depth, int p, int q) {
  if (depth[p] < depth[q]) swap(p, q);
  int dist = depth[p] - depth[q];
  for(int i=maxlog-1;i>=0;i--)if((dist>>i)&1)p = jmp[p][i];
  if (p == q)return p;
  for(int i=maxlog-1;i>=0;i--)if(jmp[p][i]!=jmp[q][i])p=jmp[p][i],q=jmp[q][i];
  return jmp[p][0];
}
int dist(vector<vi>& jpm, vi& depth, int u, int v) {
  return depth[u] + depth[v] - 2 * depth[LCA(jmp, depth, u, v)];
}
