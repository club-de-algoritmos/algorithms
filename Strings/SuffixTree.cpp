/**
 * Descripcion: Algoritmo de Ukkonen para arbol de sufijos.
 * El sufijo no unico mas largo de S tiene longitud
 * len[p]+lef despues de cada llamada a add. Cada iteracion
 * del bucle dentro de add esta cantidad disminuye en uno
 * Tiempo: O(n log sum)
 */

struct SuffixTree {
  string s;
  int N = 0;
  vi pos, len, lnk;
  vector<map<char, int>> to;

  SuffixTree(string _s) {
    make(-1, 0);
    int p = 0, lef = 0;
    for (char c : _s) add(p, lef, c);
    add(p, lef, '$');
    s.pop_back();  // terminal char
  }

  int make(int POS, int LEN) {  // lnk[x] is meaningful when
    // x!=0 and len[x] != MOD
    pos.pb(POS);
    len.pb(LEN);
    lnk.pb(-1);
    to.emplace_back();
    return N++;
  }
  void add(int& p, int& lef, char c) {  // longest
    // non-unique suffix is at node p with lef extra chars
    s += c;
    ++lef;
    int lst = 0;
    for (; lef; p ? p = lnk[p]
                  : lef--) {  // if p != root then lnk[p]
      // must be defined
      while (lef > 1 && lef > len[to[p][s[SZ(s) - lef]]])
        p = to[p][s[SZ(s) - lef]], lef -= len[p];
      // traverse edges of suffix tree while you can
      char e = s[SZ(s) - lef];
      int& q = to[p][e];
      // next edge of suffix tree
      if (!q)
        q = make(SZ(s) - lef, MOD), lnk[lst] = p, lst = 0;
      // make new edge
      else {
        char t = s[pos[q] + lef - 1];
        if (t == c) {
          lnk[lst] = p;
          return;
        }  // suffix not unique
        int u = make(pos[q], lef - 1);
        // new node for current suffix-1, define its link
        to[u][c] = make(SZ(s) - 1, MOD);
        to[u][t] = q;
        // new, old nodes
        pos[q] += lef - 1;
        if (len[q] != MOD) len[q] -= lef - 1;
        q = u, lnk[lst] = u, lst = u;
      }
    }
  }

  int maxPre(
      string x) {  // max prefix of x which is substring
    for (int p = 0, ind = 0;;) {
      if (ind == SZ(x) || !to[p].count(x[ind])) return ind;
      p = to[p][x[ind]];
      FOR(i, 0, len[p]) {
        if (ind == SZ(x) || x[ind] != s[pos[p] + i])
          return ind;
        ind++;
      }
    }
  }
  vi sa;  // generate suffix array
  void genSa(int x = 0, int Len = 0) {
    if (!SZ(to[x]))
      sa.pb(pos[x] - Len);  // found terminal node
    else
      for (auto t : to[x]) genSa(t.second, Len + len[x]);
  }
};