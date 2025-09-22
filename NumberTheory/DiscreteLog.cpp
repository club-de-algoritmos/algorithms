/*
 * Descripcion: retorna el x mas chico tal que x > 0 y a^x = b (mod m),
 * o -1 si no existe tal x. discreteLog(a,1,m) puede ser usado para
 * calcular el orden de a.
 * Tiempo: O(sqrt(m))
 *
 * Detalles: Este algoritmo utiliza el metodo baby-step giant-step para
 * encontrar (i,j) tal que a^(n * i) = b * a^j (mod m), donde n > sqrt(m)
 * y 0 < i, j <= n. Si a y m son coprimos entonces a^j tiene inverso modular,
 * lo que significa que a^(i * n - j) = b (mod m).
 *
 * Sin embargo, esta implementación particular del baby-step giant-step funciona incluso
 * sin suponer que a y m sean coprimos, usando la siguiente idea:
 *
 * Supongamos que p^x es un divisor primo de m. Entonces tenemos 3 casos
 *	 1. b es divisible por p^x
 *	 2. b es divisible sólo por alguna p^y, 0<y<x
 *	 3. b no es divisible por p
 * Lo importante a notar es que en el caso 2, modLog(a,b,m) (si
 * existe) no puede ser > sqrt(m) (técnicamente no puede ser >= log2(m)).
 * Así que, una vez comprobados todos los exponentes de a que son <= sqrt(m),
 * el caso 2 ya no puede darse. El caso 2 es el único caso delicado.
 *
 * Por tanto, la modificación que permite entrada no coprima consiste en comprobar todos
 * los exponentes de a que sean <= n, y después manejar los casos no delicados mediante
 * una comprobación simple gcd(a^n,m) == gcd(b,m).
 */


int solve(int a, int b, int m) {
	int n = int(sqrt(m)) + 1, e = 1, f = 1, j = 1;
	unordered_map<ll, ll> A;
	while (j <= n && (e = f = e * a % m) != b % m)
		A[e * b % m] = j++;
	if (e == b % m) return j;
	if (gcd(m, e) == gcd(m, b)) 
		for (int i = 2; i <= n + 1; ++i)
      if (A.count(e = e * f % m)) return n * i - A[e];
	return -1;
}