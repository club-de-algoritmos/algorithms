/*
 * Descripcion: Calcula un EerTree el cual es un arbol que permite
 * un rapido acceso a todos los palindromos contenidos en un
 * string como encontrar el palindromo mas largo en un substring
 * Uso: Considerar a s como el string original y p el palindromo
 * asociado al nodo u
 * - et[u].l: la longitud de p
 * - et[u].cnt: es el numero de veces que aparece p como el sufijo
 *   palindromo mas largo de un prefijo s[0:i]. Despues de llamar
 *   computeFrecuency() es el numero de veces en el que p aparece en s
 * - et[u].link: es el nodo que correspondiente al palindromo propio
 *   mas largo de p
 * Tiempo: O(N)
 */

constexpr short alpha = 26;
constexpr char offset = 'a';
struct state {
  int l, link, cnt;
  array<int, alpha> go;
  state() {
    l = cnt = 0;
    go.fill(0);
  }
};
struct PalindromicTree {
  int n = 2;
  int last = 1;
  vector<state> et;
  string s;
  PalindromicTree() {
    et.resize(2);
    et[0].link = et[1].link = 1;
    et[1].l = -1;
  }
  int palSuff(int x) {
    while (s[SZ(s) - 2 - et[x].l] != s.back()) x = et[x].link;
    return x;
  }
  int add(char ch) {
    s.pb(ch);
    last = palSuff(last);
    bool new_pal = !et[last].go[ch - offset];
    if (new_pal) {
      et.pb(state());
      et[last].go[ch - offset] = n++;
      et.back().link = et[palSuff(et[last].link)].go[ch - offset];
      et.back().l = et[last].l + 2;
      if (et.back().l == 1) et.back().link = 0;
    }
    last = et[last].go[ch - offset];
    // Do something with last, maybe if new_pal
    et[last].cnt++;
    if (et[last].l == SZ(s)) last = et[last].link;
    return new_pal;
  }
  void computeFrequency() {
    for (int i = n - 1; i > 1; i--) et[et[i].link].cnt += et[i].cnt;
  }
};