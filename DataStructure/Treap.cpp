/**
 * Descripcion: poderoso arbol auto-balanceado.
 * Es un treap implicito, por lo que actua como
 * un contenedor dinamico secuencial que soporta
 * separaciones y uniones. Es facil de mejorar
 * con mas datos.
 *  Se usa 0-indexacion
 *  Tiene muchos ejemplos y atributos para
 *  suma y reverseo
 *  Rangos [l, r)
 * Tiempo: O(log n)
 * Status: testeado en CSES Reversals and Sums
 */

struct Node {
  Node *l = 0, *r = 0;
  int val, y, c = 1;
  int s;
  bool rev;
  Node(int val) : val(val), y(rand()), s(val), rev(false) {}
  void recalc();
};

int sum(Node *n) { return n ? n->s : 0ll; }
int cnt(Node* n) { return n ? n->c : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; s = val + sum(l) + sum(r); }

void apply(Node* n) {
  if (n) {
    n->rev ^= 1;
    swap(n->l, n->r);
  }
}

void push(Node* n) {
  if (n && n->rev) {
    apply(n->l);
    apply(n->r);
    n->rev = false;
  }
}

pair<Node*, Node*> split(Node* n, int k) {
  if (!n) return {};
  push(n);
  if (cnt(n->l) >= k) { // "n->val >= k" para usar lower_bound(k)
    auto [L,R] = split(n->l, k);
    n->l = R;
    n->recalc();
    return {L, n};
  } else {
    auto [L,R] = split(n->r,k - cnt(n->l) - 1); // y solo "k"
    n->r = L;
    n->recalc();
    return {n, R};
  }
}

Node* merge(Node* l, Node* r) {
  push(l);
  push(r);
  if (!l) return r;
  if (!r) return l;
  if (l->y > r->y) {
    l->r = merge(l->r, r);
    return l->recalc(), l;
  } else {
    r->l = merge(l, r->l);
    return r->recalc(), r;
  }
}

Node* ins(Node* t, Node* n, int pos) {
  auto [l,r] = split(t, pos);
  return merge(merge(l, n), r);
}

void move(Node*& n, int l, int r, int k) {
  Node *a, *b, *c;
  tie(a,b) = split(n, l); tie(b,c) = split(b, r - l);
  if (k <= l) n = merge(ins(a, b, k), c);
  else n = merge(a, ins(c, b, k - r));
}

void shift(Node*& n, int l, int r) {
  if (l + 1 == r) return;
  Node *a, *b, *c, *d;
  tie(a, b) = split(n, l); tie(b, d) = split(b, r - l);
  tie(b, c) = split(b, r - l - 1);
  n = merge(merge(merge(a, c), b), d);
}

void reverse(Node*& n, int l, int r) {
  if (l + 1 == r) return;
  Node *a, *b, *c;
  tie(a, b) = split(n, l); tie(b, c) = split(b, r - l);
  apply(b);
  n = merge(merge(a, b), c);
}

int sum(Node* n, int l, int r) {
  Node *a, *b, *c;
  tie(a, b) = split(n, l); tie(b, c) = split(b, r - l);
  int ret = b->s;
  n = merge(merge(a, b), c);
  return ret;
}

int kth(Node* n, int k) {
  push(n);
  if (cnt(n->l) > k) return kth(n->l, k);
  else if (cnt(n->l) < k) return kth(n->r, k - cnt(n->l) - 1);
  return n->val;
}