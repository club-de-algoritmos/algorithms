/*
 * Descripcion: Este algoritmo te permite buscar rapidamente
 * multiples patrones en un texto
 * Tiempo: O(mk)
 */

// Utilizar esta implementacion cuando las letras permitidas
// sean pocas
struct AhoCorasick {
  enum { alpha = 26, first = 'a' };  // change this!
  struct Node {
    // (nmatches is optional)
    int back, next[alpha], start = -1, end = -1,
                           nmatches = 0;
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
  // O(sum|pat| * C)
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
          (N[ed].end == -1 ? N[ed].end
                           : backp[N[ed].start]) = N[y].end;
          N[ed].nmatches += N[y].nmatches;
          q.push(ed);
        }
      }
    }
  }

  // O(|word|)
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

class Aho {
  struct Vertex {
    unordered_map<char, int> children;
    bool leaf;
    int parent, suffixLink, wordID, endWordLink;
    char parentChar;

    Vertex() {
      children.clear();
      leaf = false;
      parent = suffixLink = wordID = endWordLink = -1;
    }
  };

 private:
  vector<Vertex*> Trie;
  vector<int> wordsLength;
  int size, root;

  void calcSuffixLink(int vertex) {
    // Procesar root
    if (vertex == root) {
      Trie[vertex]->suffixLink = root;
      Trie[vertex]->endWordLink = root;
      return;
    }
    // Procesamiento de hijos de la raiz
    if (Trie[vertex]->parent == root) {
      Trie[vertex]->suffixLink = root;
      if (Trie[vertex]->leaf) {
        Trie[vertex]->endWordLink = vertex;
      } else {
        Trie[vertex]->endWordLink =
            Trie[Trie[vertex]->suffixLink]->endWordLink;
      }
      return;
    }

    // Para calcular el suffix link del vertice actual,
    // necesitamos el suffix link del padre del vertice y el
    // personaje que nos movio al vertice actual.
    int curBetterVertex =
        Trie[Trie[vertex]->parent]->suffixLink;
    char chVertex = Trie[vertex]->parentChar;
    while (true) {
      if (Trie[curBetterVertex]->children.count(chVertex)) {
        Trie[vertex]->suffixLink =
            Trie[curBetterVertex]->children[chVertex];
        break;
      }
      if (curBetterVertex == root) {
        Trie[vertex]->suffixLink = root;
        break;
      }
      curBetterVertex = Trie[curBetterVertex]->suffixLink;
    }

    if (Trie[vertex]->leaf) {
      Trie[vertex]->endWordLink = vertex;
    } else {
      Trie[vertex]->endWordLink =
          Trie[Trie[vertex]->suffixLink]->endWordLink;
    }
  }

 public:
  Aho() {
    size = root = 0;
    Trie.pb(new Vertex());
    size++;
  }

  void addString(string s, int wordID) {
    int curVertex = root;
    FOR(i, 0, s.length()) {  // Iteracion sobre los
                             // caracteres de la cadena
      char c = s[i];
      if (!Trie[curVertex]->children.count(c)) {
        Trie.pb(new Vertex());
        Trie[size]->suffixLink = -1;
        Trie[size]->parent = curVertex;
        Trie[size]->parentChar = c;
        Trie[curVertex]->children[c] = size;
        size++;
      }
      curVertex = Trie[curVertex]
                      ->children[c];  // Mover al nuevo
                                      // vertice en el trie
    }
    // Marcar el final de la palabra y almacene su ID
    Trie[curVertex]->leaf = true;
    Trie[curVertex]->wordID = wordID;
    wordsLength.pb(s.length());
  }

  void prepareAho() {
    queue<int> vertexQueue;
    vertexQueue.push(root);
    while (!vertexQueue.empty()) {
      int curVertex = vertexQueue.front();
      vertexQueue.pop();
      calcSuffixLink(curVertex);
      for (auto key : Trie[curVertex]->children) {
        vertexQueue.push(key.second);
      }
    }
  }

  int processString(string text) {
    int currentState = root;
    int result = 0;
    FOR(j, 0, text.length()) {
      while (true) {
        if (Trie[currentState]->children.count(text[j])) {
          currentState =
              Trie[currentState]->children[text[j]];
          break;
        }
        if (currentState == root) break;
        currentState = Trie[currentState]->suffixLink;
      }
      int checkState = currentState;
      // Tratar de encontrar todas las palabras posibles de
      // este prefijo
      while (true) {
        checkState = Trie[checkState]->endWordLink;

        // Si estamos en el vertice raiz, no hay mas
        // coincidencias
        if (checkState == root) break;

        result++;
        int indexOfMatch =
            j + 1 - wordsLength[Trie[checkState]->wordID];

        // Tratando de encontrar todos los patrones
        // combinados de menor longitud
        checkState = Trie[checkState]->suffixLink;
      }
    }
    return result;
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);

  vector<string> patterns = {"abc", "bcd", "abcd"};
  string text = "abcd";
  Aho ahoAlg;
  FOR(i, 0, patterns.size()) {
    ahoAlg.addString(patterns[i], i);
  }
  ahoAlg.prepareAho();
  cout << ahoAlg.processString(text) << ENDL;

  return 0;
}