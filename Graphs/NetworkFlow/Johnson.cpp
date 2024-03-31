/**
 * Descripcion: maximo flujo de coste minimo. Asume costos negativos, 
 * pero no soporta ciclos negativos.
*/

struct MCMF {
	using F = ll; using C = ll; // tipo de flujo y de costo
	struct Edge { int to, rev; F flo, cap; C cost; };
	int N0;
    const ll  INF = 1e18; 
	vector<C> p, dist;
	vii pre;
	vector<vector<Edge>> adj;

	void init(int _N) { 
	    N0 = _N;
		p.resize(N0); dist.resize(N0); pre.resize(N0); adj.resize(N0);
    }
	void ae(int u, int v, F cap, C cost) { //Agregar arista
	    assert(cap >= 0);
		adj[u].push_back({v,(int) adj[v].size(), 0, cap, cost});
		adj[v].push_back({u,(int) adj[u].size() - 1, 0, 0, -cost});
	}
	bool path(int s, int t) { 
		dist.assign(N0,INF);
		using T = pair<C, int>;     
		priority_queue<T, vector<T>, greater<T>> todo;
		todo.push({dist[s] = 0,s});
		while (todo.size()) { 
			T x = todo.top(); todo.pop();
			if (x.first > dist[x.second]) continue;
			for(auto e : adj[x.second]) { 
				if(e.flo < e.cap && ( dist[e.to] > x.first + e.cost + p[x.second] - p[e.to])){
					dist[e.to] = x.first + e.cost + p[x.second]-p[e.to];
					pre[e.to] = {x.second, e.rev};
					todo.push({dist[e.to],e.to});
				}
			}
		} 
		return dist[t] != INF; 
	}

	pair<F,C> calc(int s, int t, bool hasNegCost = false) {
	    assert(s != t);
	    if(hasNegCost) { // Se encarga de costos negativos
            for(int k=0; k<N0; k++) for(int i=0; i<N0; i++) for(auto e : adj[i]) // Bellman-Ford, 0 index
                if (e.cap && (p[e.to] > p[i]+e.cost) ) p[e.to] = p[i]+e.cost;
	    }

		F totFlow = 0; C totCost = 0;
		while (path(s,t)) { 
			for(int i=0; i<N0; i++) p[i] += dist[i]; 
			F df = INF;
			for (int x = t; x != s; x = pre[x].first) {
				Edge& e = adj[pre[x].first][adj[x][pre[x].second].rev];
				if(df > e.cap-e.flo) df = e.cap-e.flo;
            }
            
			totFlow += df; totCost += (p[t]-p[s])*df;
			for (int x = t; x != s; x = pre[x].first) {
				Edge& e = adj[x][pre[x].second];
				e.flo -= df;
				adj[pre[x].first][e.rev].flo += df;
			}
		} // Retorna el maximo flujo, costo minimo
		return {totFlow, totCost};
	}
};
