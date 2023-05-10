// Let A be an n*n order matrix and k the exponent, we can calculate A^k in O(log k * n^3)
typedef vector<vi> vvi;
// A * B = C, O(n^3)
vvi matrixMultiplication(vvi &A, vvi &B) {
    int n = A.size(), m = A[0].size(), k = B[0].size();
    vvi C(n, vi(k, 0));

    FOR(i, n)
    FOR(j, k)
    FOR(l, m)
    C[i][j] += (A[i][l] * B[l][j]) % MOD;
    return C;
}
// A^k, O(log k * n^3)
vvi matrixExponentiation(vvi &A, ll k) {
    int n = A.size();
    // ret -> identity matrix
    vvi ret(n, vi(n)), B = A;
    FOR(i, n)
    ret[i][i] = 1;

    while (k) {
        if (k & 1)
            ret = matrixMultiplication(ret, B);
        k >>= 1;
        B = matrixMultiplication(B, B);
    }
    return ret;
}
// Si el problema es el tiempo, implementar struct Matrix

/*
Approach para calcular el n-esimo fibonacci en O(log n):
  Utilizar la matriz de fibonacci:
A = {1, 1} ^ n
    {1, 0}
Donde
A = {F[n+1], F[n]  }
    {F[n]  , F[n-1]}
Utilizar exponenciacion binaria de la matriz, con 4 variables para que sea veloz.
*/
