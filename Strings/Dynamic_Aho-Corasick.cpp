/*
 * Descripcion: Si tenemos N cadenas en el diccionario,
 * mantenga log(N) Aho Corasick automatas. El i-esimo
 * automata contiene las primeras 2^k cadenas no incluidas
 * en el automatas anteriores. Por ejemplo, si tenemos N =
 * 19, necesitamos 3 automatas: {s[1]...s[16]},
 * {s[17]...s[18]} y {s[19]}. Para responder a la consulta,
 * podemos atravesar los automatas logN. utilizando la
 * cadena de consulta dada. Para manejar la insercion,
 * primero construya un automata usando una sola cadena y
 * luego Si bien hay dos automatas con el mismo numero de
 * cadenas, los fusionamos mediante un nuevo automata usando
 * fuerza bruta. Para manejar la eliminacion, simplemente
 * insertamos un valor -1 para almacenar en los puntos
 * finales de cada cadena agregada.
 * Tiempo: O(m*log(numero_de_inserciones))
 */

class AhoCorasick {
 public:
  struct Node {
    map<char, int> ch;
    vector<int> accept;
    int link = -1;
    int cnt = 0;

    Node() = default;
  };

  vector<Node> states;
  map<int, int> accept_state;

  explicit AhoCorasick() : states(1) {}

  void insert(const string& s, int id = -1) {
    int i = 0;
    for (char c : s) {
      if (!states[i].ch.count(c)) {
        states[i].ch[c] = states.size();
        states.emplace_back();
      }
      i = states[i].ch[c];
    }
    ++states[i].cnt;
    states[i].accept.push_back(id);
    accept_state[id] = i;
  }

  void clear() {
    states.clear();
    states.emplace_back();
  }

  int get_next(int i, char c) const {
    while (i != -1 && !states[i].ch.count(c))
      i = states[i].link;
    return i != -1 ? states[i].ch.at(c) : 0;
  }

  void build() {
    queue<int> que;
    que.push(0);
    while (!que.empty()) {
      int i = que.front();
      que.pop();

      for (auto [c, j] : states[i].ch) {
        states[j].link = get_next(states[i].link, c);
        states[j].cnt += states[states[j].link].cnt;

        auto& a = states[j].accept;
        auto& b = states[states[j].link].accept;
        vector<int> accept;
        set_union(a.begin(), a.end(), b.begin(), b.end(),
                  back_inserter(accept));
        a = accept;

        que.push(j);
      }
    }
  }

  long long count(const string& str) const {
    long long ret = 0;
    int i = 0;
    for (auto c : str) {
      i = get_next(i, c);
      ret += states[i].cnt;
    }
    return ret;
  }

  // list of (id, index)
  vector<pair<int, int>> match(const string& str) const {
    vector<pair<int, int>> ret;
    int i = 0;
    for (int k = 0; k < (int)str.size(); ++k) {
      char c = str[k];
      i = get_next(i, c);
      for (auto id : states[i].accept) {
        ret.emplace_back(id, k);
      }
    }
    return ret;
  }
};

class DynamicAhoCorasick {
  vector<vector<string>> dict;
  vector<AhoCorasick> ac;

 public:
  void insert(const string& s) {
    int k = 0;
    while (k < (int)dict.size() && !dict[k].empty()) ++k;
    if (k == (int)dict.size()) {
      dict.emplace_back();
      ac.emplace_back();
    }

    dict[k].push_back(s);
    ac[k].insert(s);

    for (int i = 0; i < k; ++i) {
      for (auto& t : dict[i]) {
        ac[k].insert(t);
      }
      dict[k].insert(dict[k].end(), dict[i].begin(),
                     dict[i].end());
      ac[i].clear();
      dict[i].clear();
    }

    ac[k].build();
  }

  long long count(const string& str) const {
    long long ret = 0;
    for (int i = 0; i < (int)ac.size(); ++i)
      ret += ac[i].count(str);
    return ret;
  }
};
