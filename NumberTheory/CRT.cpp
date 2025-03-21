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

ll crt(ll a, ll m, ll b, ll n) {
  if (n > m) swap(a, b), swap(m, n);
  ll x, y, g = euclid(m, n, x, y);
  assert((a - b) % g == 0);  // else no solution
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m * n / g : x;
}

using pll = pair<ll, ll>;
class ChineseRemainderTheorem {
  vector<pll> equations;

public:
	void clear() {
		equations.clear();
	}

	void addEquation(ll r, ll m ) {
		equations.push_back({r, m});
	}

	ll ext_gcd(ll a, ll b, ll &x, ll &y) {
		if(b == 0) {
			x = 1; y = 0;
			return a;
		}
		ll ret = ext_gcd(b, a%b, y, x);
		y -= x*(a / b);
		return ret;
	}

	pll solve() {
		if (equations.size() == 0) return {-1,-1};

		ll a1 = equations[0].first;
		ll m1 = equations[0].second;
		a1 %= m1;

		for (int i = 1; i < equations.size(); i++ ) {
			ll a2 = equations[i].first;
			ll m2 = equations[i].second;

			ll g = __gcd(m1, m2);
			if (a1 % g != a2 % g) return {-1,-1};

			ll p, q;
			ext_gcd(m1/g, m2/g, p, q);

			ll mod = m1 / g * m2;
			ll x = ( (__int128)a1 * (m2/g) % mod *q % mod + (__int128)a2 * (m1/g) % mod * p % mod ) % mod;

			a1 = x;
			if ( a1 < 0 ) a1 += mod;
			m1 = mod;
		}
		return {a1, m1};
	}
};
