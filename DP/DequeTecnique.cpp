/**
 * Descripcion: algoritmo que resuelve el problema de el
 * minimo o maximo valor de cada sub-array de longitud fija.
 * Enunciado:
 * Dado un arreglo de numeros A de longitud n y un numero k
 * <= n. Encuentra el minimo para cada sub-array contiguo de
 * longitud k. La estrategia se basa en el uso de una bicola
 * monotona, en donde en cada iteracion sacamos del final de
 * la bicola hasta que este vacia o nos encontremos con un
 * A[j] > A[i], luego agregamos i, manteniendose de manera
 * decreciente, si el frente se sale del rango, lo sacamos y
 * el nuevo frente seria el mayor en el rango (A[i]...A[i +
 * k - 1]). Este algoritmo gana fuerza cuando se generaliza
 * a mas dimensiones: digamos que queremos el mayor en una
 * sub-matriz dada, se puede precalcular el B para cada fila
 * y luego volvemos a correr el algoritmo sobre dichos
 * valores. Retorna un vector B, en donde B[i] = j, tal que
 * A[j] >= A[i], ..., A[i + k - 1]
 * Tiempo: O(n)
 */

vector<int> solve(vector<int>& A, int k) {
  vector<int> B(A.size() - k + 1);
  deque<int> dq;
  for (int i = 0; i < A.size(); i++) {
    while (!dq.empty() && A[dq.back()] <= A[i])
      dq.pop_back();
    dq.pb(i);
    if (dq.front() <= i - k) dq.pop_front();

    if (i + 1 >= k) B[i + 1 - k] = A[dq.front()];
  }
}
