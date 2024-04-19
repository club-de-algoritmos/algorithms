/**
 * Descripcion: arbol de segmentos esparcido, es util cuando
 * el rango usado es bastante largo, y que ademas haya
 * operaciones de rango. Uso: Inicializar el nodo 1 como la
 * raiz -> segtree[1] = {0, 0, 1, 1e9} utilizar los metodos
 * update y query
 * Complejidad: O(log n)
 */

struct Node {
  int sum, lazy, tl, tr, l, r;
  Node() : sum(0), lazy(0), l(-1), r(-1) {}
};

const int MAXN = 123456;
Node segtree[64 * MAXN];
int cnt = 2;

void push_lazy(int node) {
  if (segtree[node].lazy) {
    segtree[node].sum =
        segtree[node].tr - segtree[node].tl + 1;
    int mid = (segtree[node].tl + segtree[node].tr) / 2;
    if (segtree[node].l == -1) {
      segtree[node].l = cnt++;
      segtree[segtree[node].l].tl = segtree[node].tl;
      segtree[segtree[node].l].tr = mid;
    }
    if (segtree[node].r == -1) {
      segtree[node].r = cnt++;
      segtree[segtree[node].r].tl = mid + 1;
      segtree[segtree[node].r].tr = segtree[node].tr;
    }
    segtree[segtree[node].l].lazy =
        segtree[segtree[node].r].lazy = 1;
    segtree[node].lazy = 0;
  }
}

void update(int node, int l, int r) {  // [l, r]
  push_lazy(node);
  if (l == segtree[node].tl && r == segtree[node].tr) {
    segtree[node].lazy = 1;
    push_lazy(node);
  } else {
    int mid = (segtree[node].tl + segtree[node].tr) / 2;
    if (segtree[node].l == -1) {
      segtree[node].l = cnt++;
      segtree[segtree[node].l].tl = segtree[node].tl;
      segtree[segtree[node].l].tr = mid;
    }
    if (segtree[node].r == -1) {
      segtree[node].r = cnt++;
      segtree[segtree[node].r].tl = mid + 1;
      segtree[segtree[node].r].tr = segtree[node].tr;
    }

    if (l > mid)
      update(segtree[node].r, l, r);
    else if (r <= mid)
      update(segtree[node].l, l, r);
    else {
      update(segtree[node].l, l, mid);
      update(segtree[node].r, mid + 1, r);
    }

    push_lazy(segtree[node].l);
    push_lazy(segtree[node].r);
    segtree[node].sum = segtree[segtree[node].l].sum +
                        segtree[segtree[node].r].sum;
  }
}

int query(int node, int l, int r) {  // [l, r]
  push_lazy(node);
  if (l == segtree[node].tl && r == segtree[node].tr)
    return segtree[node].sum;
  else {
    int mid = (segtree[node].tl + segtree[node].tr) / 2;
    if (segtree[node].l == -1) {
      segtree[node].l = cnt++;
      segtree[segtree[node].l].tl = segtree[node].tl;
      segtree[segtree[node].l].tr = mid;
    }
    if (segtree[node].r == -1) {
      segtree[node].r = cnt++;
      segtree[segtree[node].r].tl = mid + 1;
      segtree[segtree[node].r].tr = segtree[node].tr;
    }

    if (l > mid)
      return query(segtree[node].r, l, r);
    else if (r <= mid)
      return query(segtree[node].l, l, r);
    else
      return query(segtree[node].l, l, mid) +
             query(segtree[node].r, mid + 1, r);
  }
}
