/**
 * Descripcion: Algunas operaciones utiles con desplazamiento de bits, si no trabajamos
 * con numeros enteros, usar 1LL o 1ULL, siendo la primer parte
 * operaciones nativas y la segunda del compilador GNU (GCC), si no se
 * trabaja con enteros, agregar ll al final del nombre del metodo
 * Tiempo por operacion: O(1)
 */

#define isOn(S, j) ((S >> j) & 1)
#define setBit(S, j) (S |= (1 << j))
#define clearBit(S, j) (S &= ~(1 << j))
#define toggleBit(S, j) (S ^= (1 << j))
#define lowBit(S) (S & (-S))
#define setAll(S, n) (S = (1 << n) - 1)
#define modulo(S, N) ((S) & (N - 1))  // Siendo N potencia de 2
#define isOdd(S) (s & 1)
#define isPowerOfTwo(S) (!(S & (S - 1)))
#define nearestPowerOfTwo(S) (1 << lround(log2(S)))
#define turnOffLastBit(S) ((S) & (S - 1))
#define turnOnLastZero(S) ((S) | (S + 1))
#define turnOffInRange(S, i, j) s &= (((~0) << (j + 1)) | ((1 << i) - 1));
#define turnOffLastConsecutiveBits(S) ((S) & (S + 1))
#define turnOnLastConsecutiveZeroes(S) ((S) | (S - 1))

#define countBitsOn(n) __builtin_popcount(x);
#define firstBitOn(n) __builtin_ffs(x);
#define countLeadingZeroes(n) __builtin_clz(n)
#define log2Floor(n) 31 - __builtin_clz(n)
#define countTrailingZeroes(n) __builtin_ctz(n)

/**
 * Descripcion: Si n <= 20 y manejamos subconjuntos, podemos revisar
 * cada uno de ellos representandolos como una mascara de bits, en
 * donde el i-esimo elemento es tomado si el i-esimo bit esta encendido
 * Tiempo: O(2^n)
 */
int MX_MSK = 1 << n;
for (int i = 0; i < MX_MSK; i++) {
}
