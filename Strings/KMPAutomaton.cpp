/*
 * Descripcion: Construye un automata del KMP donde el estado es el valor actual
 * de la funcion phi
 * Uso: aut[state][nextCharacter]
 * Tiempo: O(|s|*C)
 */
vector<vector<int>> aut;
void compute_automaton(string s) {
  s += '#';
  int n = s.size();
  vector<int> phi = PI(s);
  aut.assign(n, vector<int>(26));
  FOR(i, 0, n) {
    FOR(c, 0, 26) {
      if (i > 0 && 'a' + c != s[i])
        aut[i][c] = aut[phi[i - 1]][c];
      else
        aut[i][c] = i + ('a' + c == s[i]);
    }
  }
}