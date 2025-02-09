/*
 * Descripcion: en aritmetica modular, un numero g es llamado
 * una raiz primitiva modulo n si cada numero coprimo con n es
 * congruente a una potencia de g modulo n. Matematicamente, esto
 * es equivalente a decir que para cada entero a tal que
 * gcd(a, n) = 1, existe un entero k tal que:
 *  g**k = a (mod n)
 * Entonces, k es llamado el indice o logaritmo discreto de a en
 * la base g modulo n. g tambien es llamado el generador del grupo
 * multiplicativo de enteros modulo n.
 * En particular, cuando n es primo, las potencias de la raiz
 * primitiva van por todos los numeros desde 1 hasta n - 1
 * Una raiz primitiva modulo n existe si y solo si:
 *    n es 1, 2, 4 o
 *    n es una potencia de un primo impar (n = p**k) o
 *    n es 2 veces la potencia de un primo impar (n = 2 * p**k)
 * Nota. El codigo asume que el modulo p es un primo. Para hacerlo
 * funcionar para cualquier p, agregar calculo de phi(p)
 * Tiempo: O(p * |factores de p| * log p)
 */

int generator (int p) {
  vector<int> fact;
  int phi = p - 1,  n = phi;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      fact.push_back(i);
      while (n % i == 0) {
        n /= i;
      }
    }
  }
  if (n > 1) {
    fact.push_back(n);
  }

  for (int res = 2; res <= p; ++res) {
    bool ok = true;
    for (int i = 0; i < fact.size() && ok; ++i) {
      ok &= be(res, phi / fact[i], p) != 1;
    }
    if (ok) {
      return res;
    }
  }
  return -1;
}