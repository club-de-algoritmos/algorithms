/*
    En C++14 se puede utilizar el metodo de algorithm
    __gcd(m,n)

    A partir de C++17 se puede utilizar el metodo de numeric
    gcd(m,n)
    lcm(m,n)
*/
int gcd(int a, int b) { return (b ? gcd(b, a % b) : a); }
ll lcm(int a, int b) { return ((a * b) / gcd(a, b)); }

// (a^b) mod m, O(log n)
ll fastpow(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;
    while (b) {
        if (b & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

// Codigo para calcular (a^-1)%m (si es que existe), O(log n)

// Si m es primo
int modInverse(int b, int m) { return fastpow(b, m - 2, m) % m; }

// Si m NO es primo
using iii = tuple<int, int, int>;

iii extendedGCD(int a, int b) {
    if (b == 0)
        return iii({a, 1, 0});
    auto [d, x, y] = extendedGCD(b, a % b);
    return {d, y, x - a / b * y};
}

int modInverse(int a, int m) {
    auto [d, x, y] = extendedGCD(a, m);
    if (d > 1)
        return 0;  // Si no existe
    return (x + m) % m;
}

// Coeficientes binomiales (Combinatoria) - O(n + n log p)
ll C(int n, int k) {  // O(log p)
    if (n < k)
        return 0;
    return fact[n] * modInverse(fact[k]) % p * modInverse(fact[n - k]) % p;
}
