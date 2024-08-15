/**
 * Descripcion: siendo jmp[i][j] el ancestro 2^j del nodo i,
 * el binary liftingnos permite obtener el k-esimo ancestro
 * de cualquier nodo en tiempo logaritmico, una aplicacion de
 * esto es para obtener el ancestro comun mas bajo (LCA).
 * Importante inicializar jmp[i][0] para todo i.
 * Tiempo: O(n log n) en construccion y O(log n) por consulta
 * Status: testeado en ICPC LATAM 2017 - Imperial Roads 
 */
vi g[maxn];
int jmp[maxn][maxlog], d[maxn];
void dfs(int u, int p = -1) {
  jmp[u][0]=p;
  for (auto &v:g[u])if(v!=p)d[v]=d[u]+1,dfs(v,u);
}
void build() {
  int n = SZ(g);
  dfs(0);
  for(int i=1;i<maxlog;i++)for(int u=0;u<n;u++)if(jmp[u][i-1]!=-1)
    jmp[u][i]=jmp[jmp[u][i-1]][i-1];
}
int LCA(int u, int v) {
  if (d[u] < d[v]) swap(u, v);
  int dist = d[u] - d[v];
  for(int i=maxlog-1;i>=0;i--)if((dist>>i)&1)u=jmp[u][i];
  if(u==v)return u;
  for(int i=maxlog-1;i>=0;i--)if(jmp[u][i]!=jmp[v][i])u=jmp[u][i],v=jmp[v][i];
  return jmp[u][0];
}
int dist(int u, int v) { return d[u] + d[v] - 2 * d[LCA(u, v)]; }
