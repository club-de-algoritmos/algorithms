/**
 * Descripcion: Encuentra los vertices en el minimum vertex
 * cover de un grafo bipartito, si solo se quiere la cardinalidad
 * leer teoria.
 * Tiempo: depende el algoritmo de matching que se use
 */
 
#include "Kuhn.h" // o hopcroft karp

vi cover(vector<vi>& g, int n, int m) {
	auto [res, btoa] = kuhn(g, m);
	vector<bool> lfound(n, true), seen(m);
	for (int it : btoa) if (it != -1) lfound[it] = false;
	vi q, cover;
	FOR (i,0,n) if (lfound[i]) q.push_back(i);
	while (!q.empty()) {
		int u = q.back(); q.pop_back();
		lfound[u] = 1;
		for (int v : g[u]) if (!seen[v] && btoa[v] != -1) {
			seen[v] = true;
			q.push_back(btoa[v]);
		}
	}
	FOR (i,0,n) if (!lfound[i]) cover.push_back(i);
	FOR (i,0,m) if (seen[i]) cover.push_back(n+i);
	assert(sz(cover) == res);
	return cover;
}