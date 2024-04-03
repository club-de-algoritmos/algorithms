/*
 * Descripcion: El Arbol de Li-Chao es una estructura de datos utilizada en
 * algoritmos de programacion dinamica y geometrica para realizar
 * consultas de maximo (o minimo) en un conjunto de puntos en una línea (o un plano).
 * Tiempo :
 *   Construccion : O(N log N)
 *   Insercion y Consultas : O(log N)
 * Alternativa, construcion dinamica mas eficiente.
 * **Cuidado con la memoria dinamica pude causar errores si no se tiene cuidado.
 * **Recomendacion: No hacer declaraciones globales
 */

struct Line {
  ll m, c;
  ll eval(int x) {
    return m * x + c;
  }
};
struct node {
  Line line;
  node* left = nullptr;
  node* right = nullptr;
  node(Line line) : line(line) {}
  void add_segment(Line nw, ll l, ll r, ll L, ll R) {
    if (l > r || r < L || l > R) return;
    ll m = (l + 1 == r ? l : (l + r) / 2);
    if (l >= L and r <= R) {
      bool lef = nw.eval(l) < line.eval(l);
      bool mid = nw.eval(m) < line.eval(m);
      if (mid) swap(line, nw);
      if (l == r) return;
      if (lef != mid) {
        if (left == nullptr)
          left = new node(nw);
        else
          left->add_segment(nw, l, m, L, R);
      } else {
        if (right == nullptr)
          right = new node(nw);
        else
          right->add_segment(nw, m + 1, r, L, R);
      }
      return;
    }
    if (max(l, L) <= min(m, R)) {
      if (left == nullptr) left = new node({0, inf});
      left->add_segment(nw, l, m, L, R);
    }
    if (max(m + 1, L) <= min(r, R)) {
      if (right == nullptr) right = new node({0, inf});
      right->add_segment(nw, m + 1, r, L, R);
    }
  }
  ll query_segment(ll x, ll l, ll r, ll L, ll R) {
    if (l > r || r < L || l > R) return inf;
    ll m = (l + 1 == r ? l : (l + r) / 2);
    if (l >= L and r <= R) {
      ll ans = line.eval(x);
      if (l < r) {
        if (x <= m && left != nullptr) ans = min(ans, left->query_segment(x, l, m, L, R));
        if (x > m && right != nullptr) ans = min(ans, right->query_segment(x, m + 1, r, L, R));
      }
      return ans;
    }
    ll ans = inf;
    if (max(l, L) <= min(m, R)) {
      if (left == nullptr) left = new node({0, inf});
      ans = min(ans, left->query_segment(x, l, m, L, R));
    }
    if (max(m + 1, L) <= min(r, R)) {
      if (right == nullptr) right = new node({0, inf});
      ans = min(ans, right->query_segment(x, m + 1, r, L, R));
    }
    return ans;
  }
};

struct LiChaoTree {  // the input values for lichaotree are boundaries of x values you can use to query with
  int L, R;
  node* root;
  LiChaoTree() : L(numeric_limits<int>::min() / 2), R(numeric_limits<int>::max() / 2), root(nullptr) {}
  LiChaoTree(int L, int R) : L(L), R(R) {
    root = new node({0, inf});
  }
  void add_line(Line line) {
    root->add_segment(line, L, R, L, R);
  }
  // y = mx + b: x in [l, r]
  void add_segment(Line line, int l, int r) {
    root->add_segment(line, L, R, l, r);
  }
  ll query(int x) {
    return root->query_segment(x, L, R, L, R);
  }
  ll query_segment(int x, int l, int r) {
    return root->query_segment(x, l, r, L, R);
  }
};
