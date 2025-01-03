/**
 * Descripcion: algoritmo para resolver el problema de la
 * subsecuencia creciente mas larga de un arreglo (LIS) a
 * partir de una estrategia de divide y venceras. Si no
 * es necesario recuperar la subsecuencia, ignorar p.
 * Tiempo: O(n log n)
 */

void getPath(int i, vector<int>& p, vector<int>& path) {
  if (p[i] != -1) {
    getPath(p[i], p, path);
  }
  path.push_back(i);
}
vector<int> getPath(int lisEnd, vector<int>& p) {
  vector<int> path;
  getPath(lisEnd, p, path);
  return path;
} 

int solveLIS(vector<int>& a) {
  int n = (int)a.size();

  vector<int> l(n), lId(n), p(n, -1);
  int lisSz = 0, lisEnd = 0;

  for (int i = 0; i < n; i++) {
    int pos = lower_bound(l.begin(), l.begin() + lisSz, a[i]) - l.begin();
    l[pos] = a[i];
    lId[pos] = i;

    p[i] = pos ? lId[pos - 1] : -1;

    if (pos == lisSz) {
      lisSz = pos + 1;
      lisEnd = i;
    }
  }
  return lisSz;
}
