/*
 * Descripcion: Encuentra una solución x que satisfaga el
 * siguiente sistema de congruencias lineales:
 * x = a_1 (mod n_1)
 * . . .
 * x = a_k (mod n_k)
 * El Teorema Chino del Resto establece que para un conjunto
 * donde los modulos son coprimos entre pares, existe una
 * solucion unica modulo N, donde N es el producto de las N_i
 * A su vez, establece que para modulos no coprimos, si para
 * todo par de (i, j) se cumple que a_i = a_j (mod g), entonces
 * existe una solucion unica modulo l (y si no, no existe), donde
 * g = gcd(m_1, ..., m_k) y l = lcm(m_1, ..., m_k)
 * Tiempo en general: O(k)
 * Tiempo para 2 congruencias: O(log n)
 */

int crt(int a, int m, int b, int n) {
  if (n > m) swap(a, b), swap(m, n);
  int x, y, g = euclid(m, n, x, y);
  if ((a - b) % g) return NO_SOLUTION;
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m * n / g : x;
}

struct CRT {
  vector<pair<int, int>> equations;

	void clear() { equations.clear(); }

	void addEquation(int r, int m) { equations.push_back({r, m}); }

	pair<int, int> solve() {
		if (equations.empty()) return {-1, -1};

		int m1 = equations[0].second, a1 = equations[0].first % m1;
		for (int i = 1; i < equations.size(); i++ ) {
			int m2 = equations[i].second, a2 = equations[i].first % m2;

			int g = gcd(m1, m2);
			if (a1 % g != a2 % g) return {-1, -1};

			int p, q;
			euclid(m1/g, m2/g, p, q);

			int mod = m1 / g * m2;
			mint<mod> x = mint<mod>(a1)*(m2/g)*q + mint<mod>(a2)*(m1/g)*p;

			a1 = x.v, m1 = mod;
		}
		return {a1, m1};
	}
};
