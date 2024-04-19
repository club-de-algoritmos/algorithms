/*
 * Descripcion: El prefix function para un string S es
 * definido como un arreglo phi donde phi[i] es la longitud
 * del prefijo propio de S mas largo de la subcadena S[0..i]
 * el cual tambien es sufijo de esta subcadena
 * Tiempo: O(|s| + |pat|)
 */

vi PI(const string& s) {
  vi p(SZ(s));
  FOR(i, 1, SZ(s)) {
    int g = p[i - 1];
    while (g && s[i] != s[g]) g = p[g - 1];
    p[i] = g + (s[i] == s[g]);
  }
  return p;
}

// Concatena s + \0 + pat para encontrar las ocurrencias
vi KMP(const string& s, const string& pat) {
  vi phi = PI(pat + '\0' + s), res;
  FOR(i, SZ(phi) - SZ(s), SZ(phi))
  if (phi[i] == SZ(pat)) res.push_back(i - 2 * SZ(pat));
  return res;
}

// A partir del phi de patron busca las ocurrencias en s
int KMP(const string& s, const string& pat) {
  vi phi = PI(pat);
  int matches = 0;
  for (int i = 0, j = 0; i < SZ(s); ++i) {
    while (j > 0 && s[i] != pat[j]) j = phi[j - 1];
    if (s[i] == pat[j]) ++j;
    if (j == SZ(pat)) {
      matches++;
      j = phi[j - 1];
    }
  }
  return matches;
}

/*
 * Automaton KMP
 * El estado en el es el valor actual de la prefix function,
 * y la transicion de un estado a otro se realiza a traves
 * del siguiente caracter Uso: aut[state][nextCharacter]
 * Tiempo: O(|s|*C)
 */
// Automaton O(|s|*C)
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