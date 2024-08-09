/**
 * Descripcion: Corre un callback para todos los cliques
 * maximales en un grafo (dado como una matriz simetrica
 * de bitset; aristas propias no permitidas). El callback
 * recibe un bitset representando al clique maximal.
 * Tiempo: O(3^{V/3}), mucho mas veloz para grafos dispersos.
 */
/// Posible optimizacion: en el mayor nivel de recursion
/// ignora 'cands' y muevete hacia nodos en orden de grado
/// creciente, donde los los grados bajan al eliminar nodos
/// (en su mayoria irrelevante dado MaximumClique)

typedef bitset<128> B;
template<class F>
void cliques(vector<B>& eds, F f, B P = ~B(), B X={}, B R={}) {
	if (!P.any()) { if (!X.any()) f(R); return; }
	auto q = (P | X)._Find_first();
	auto cands = P & ~eds[q];
	rep(i,0,sz(eds)) if (cands[i]) {
		R[i] = 1;
		cliques(eds, f, P & eds[i], X & eds[i], R);
		R[i] = P[i] = 0; X[i] = 1;
	}
}