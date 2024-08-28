/*
 * Descripcion: Construye un automata finito que reconoce todos los
 * sufijos de una cadena. len corresponde a la longitud maxima de un
 * sufijo con el estado actual, link corresponde al estado del
 * siguiente sufijo mas largo del estado actual
 * Tiempo: O(n log sum)
 */

struct SuffixAutomaton {
  struct state {
    int len, link;
    map<char, int> next;
  };
  vector<state> st;
  int sz, last;
  SuffixAutomaton(int MAX = 1e5) {
    st.resize(MAX);
    last = st[0].len = 0;
    sz = 1;
    st[0].link = -1;
  }
  void extend(char c) {
    int k = sz++, p;
    st[k].len = st[last].len + 1;
    for (p = last; p != -1 && !st[p].next.count(c); p = st[p].link) st[p].next[c] = k;
    if (p == -1)
      st[k].link = 0;
    else {
      int q = st[p].next[c];
      if (st[p].len + 1 == st[q].len)
        st[k].link = q;
      else {
        int w = sz++;
        st[w].len = st[p].len + 1;
        st[w].next = st[q].next;
        st[w].link = st[q].link;
        for (; p != -1 && st[p].next[c] == q; p = st[p].link) st[p].next[c] = w;
        st[q].link = st[k].link = w;
      }
    }
    last = k;
  }
};
