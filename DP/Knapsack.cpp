/**
 * Descripcion: algoritmo para resolver el problema de la
 * mochila: se cuenta con una coleccion de N objetos donde
 * cada uno tiene un peso y un valor asignado, y una mochila
 * con capacidad maxima C. Se necesita maximizar la suma de
 * valores que se puede lograr sin que se exceda C.
 * Tiempo: O(NC)
 */

int peso[MAXN], valor[MAXN], dp[MAXN][MAXC];
int N, C;

int solve(int i, int c) {
  if (c < 0) return -INF;
  if (i == N) return 0;
  int &ans = dp[i][c];
  if (ans != -1) return ans;

  return dp[i][c] =
             max(solve(i + 1, c), opcion2,
                 valor[i] + solve(i + 1, c - peso[i]));
}