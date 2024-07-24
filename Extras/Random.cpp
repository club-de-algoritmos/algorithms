/*
 * Descripcion: Basado en Mersenne Twister genera un
 * numero pseudoaleatorio de 32 bits mucho mas rapido que
 * la funcion rand() de c++.
 * Si necesita hasta 64 bits usar mt19937_64 en su lugar
 */

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Aplicaciones

// Mezclar un arreglo
shuffle(ALL(a), rng);

// Generar un numero entero en el intervalo [l,r]
uniform_int_distribution<int>(l, r)(rng)