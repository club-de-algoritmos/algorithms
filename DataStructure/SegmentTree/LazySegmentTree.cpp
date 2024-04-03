/**
 * Descripcion: arbol de segmentos, bastante poderoso para
 * realizar consultas de suma en un rango y actualizaciones
 * de suma en un rango de manera eficiente. El metodo add
 * agrega x a todos los numeros en el rango [start, end].
 * Uso: LazySegmentTree ST(arr)
 * Tiempo: O(log n)
 */

template <class T>
class LazySegmentTree {
<<<<<<< HEAD
 private:
  int n;
  const T neutral = 0;  // Cambiar segun la operacion
  vector<T> A, st, lazy;
=======
    private:
    int n;
    const T neutral = 0; //Cambiar segun la operacion
    vector<T> A, st, lazy;
>>>>>>> 3b2a189d25985250513367206919c1da1e5fce06

    inline int l(int p) { return (p << 1) + 1; }  // ir al hijo izquierdo
    inline int r(int p) { return (p << 1) + 2; }  // ir al hijo derecho

<<<<<<< HEAD
  // Cambiar segun la operacion
  T merge(T a, T b) {
    return a + b;
  }

  // Nota: Si se utiliza para el minimo o maximo de un rango no se le agrega el (end - start + 1)
  void propagate(int index, int start, int end, T dif) {
    st[index] += (end - start + 1) * dif;
    if (start != end) {
      lazy[l(index)] += dif;
      lazy[r(index)] += dif;
    }
    lazy[index] = 0;
  }

  void add(int index, int start, int end, int i, int j, T val) {
    if (lazy[index]) {
      propagate(index, start, end, lazy[index]);
    }

    if ((end < i) || (start > j))
      return;

    if (start >= i && end <= j) {
      propagate(index, start, end, val);
      return;
=======
    //Cambiar segun la operacion
    T merge(T a, T b)
    {
        return a + b;
    }

    // Nota: Si se utiliza para el minimo o maximo de un rango no se le agrega el (end - start + 1)
    void propagate(int index, int start, int end, T dif) {
        st[index] += (end - start + 1) * dif;
        if (start != end) {
            lazy[l(index)] += dif;
            lazy[r(index)] += dif;
        }
        lazy[index] = 0;
    }

    void add(int index, int start, int end, int i, int j, T val) {
        if(lazy[index]){
            propagate(index, start, end, lazy[index]);
        }
        
        if ((end < i) || (start > j))
            return;

        if (start >= i && end <= j) {
            propagate(index, start, end, val);
            return;
        }
        int mid = (start + end) / 2;

        add(l(index), start, mid, i, j, val);
        add(r(index), mid + 1, end, i, j, val);

        st[index] = merge(st[l(index)], st[r(index)]);
>>>>>>> 3b2a189d25985250513367206919c1da1e5fce06
    }

<<<<<<< HEAD
    add(l(index), start, mid, i, j, val);
    add(r(index), mid + 1, end, i, j, val);

    st[index] = merge(st[l(index)], st[r(index)]);
  }

  T query(int index, int start, int end, int i, int j) {
    if (lazy[index]) {
      propagate(index, start, end, lazy[index]);
    }

    if (end < i || start > j)
      return neutral;
    if ((i <= start) && (end <= j))
      return st[index];
=======
    T query(int index, int start, int end, int i, int j) {
        if(lazy[index]){
            propagate(index, start, end, lazy[index]);
        }

        if (end < i || start > j)
            return neutral;
        if ((i <= start) && (end <= j))
            return st[index];

        int mid = (start + end) / 2;
>>>>>>> 3b2a189d25985250513367206919c1da1e5fce06

        return merge(query(l(index), start, mid, i, j), query(r(index), mid + 1, end, i, j));
    }

<<<<<<< HEAD
    return merge(query(l(index), start, mid, i, j), query(r(index), mid + 1, end, i, j));
  }

 public:
  LazySegmentTree(int sz) : n(sz), st(4 * n), lazy(4 * n) {}
  // [i, j]
  void add(int i, int j, T val) { add(0, 0, n - 1, i, j, val); }  // [i, j]
  T query(int i, int j) { return query(0, 0, n - 1, i, j); }      // [i, j]
};
=======
    public:
    LazySegmentTree(int sz) : n(sz), st(4 * n), lazy(4 * n) {}
    // [i, j]
    void add(int i, int j, T val) { add(0, 0, n - 1, i, j, val); }  // [i, j]
    T query(int i, int j) { return query(0, 0, n - 1, i, j); }      // [i, j]
};
>>>>>>> 3b2a189d25985250513367206919c1da1e5fce06
