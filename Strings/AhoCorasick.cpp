/*
 * Descripcion: Construye un automata que te permite buscar rapidamente
 * multiples patrones en un texto.
 * Uso:
 * - Se inicializa con AhoCorasick ac(patrones)
 * - find(word): regresa por cada posicion de word el indice de la palabra
 *   mas larga que termina ahi o -1 si no existe
 * - findAll(pat, word) encuentra todas las palabras que empiezan por cada
 *   posicion de word (las mas cortas primero)
 * Notas:
 * - Patrones duplicados son permitidos (afecta en tiempo)
 * - Patrones vacios no permitidos
 * - El nodo de inicio del automata esta en el indice 0
 * - Para encontrar las palabras mas grande en cada posicion, invierte la entrada
 * Tiempo:
 * - Contruccion: O(26N)
 * - find(x): O(N)
 * - findAll: O(NM) o hasta O(N sqrt(N)) si no hay patrones duplicados
 */

struct AhoCorasick {
  enum { alpha = 26,
         first = 'a' };
  struct Node {
    int back, next[alpha], start = -1, end = -1, nmatches = 0;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  vi backp;
  void insert(string& s, int j) {
    assert(!s.empty());
    int n = 0;
    for (char c : s) {
      int& m = N[n].next[c - first];
      if (m == -1) {
        n = m = SZ(N);
        N.emplace_back(-1);
      } else
        n = m;
    }
    if (N[n].end == -1) N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    N[n].nmatches++;
  }
  AhoCorasick(vector<string>& pat) : N(1, -1) {
    FOR(i, 0, SZ(pat))
    insert(pat[i], i);
    N[0].back = SZ(N);
    N.emplace_back(0);

    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
      int n = q.front(), prev = N[n].back;
      FOR(i, 0, alpha) {
        int &ed = N[n].next[i], y = N[prev].next[i];
        if (ed == -1)
          ed = y;
        else {
          N[ed].back = y;
          (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
          N[ed].nmatches += N[y].nmatches;
          q.push(ed);
        }
      }
    }
  }
  vi find(string word) {
    int n = 0;
    vi res;  // ll count = 0;
    for (char c : word) {
      n = N[n].next[c - first];
      res.push_back(N[n].end);
      // count += N[n].nmatches;
    }
    return res;
  }
  vector<vi> findAll(vector<string>& pat, string word) {
    vi r = find(word);
    vector<vi> res(SZ(word));
    FOR(i, 0, SZ(word)) {
      int ind = r[i];
      while (ind != -1) {
        res[i - SZ(pat[ind]) + 1].push_back(ind);
        ind = backp[ind];
      }
    }
    return res;
  }
};