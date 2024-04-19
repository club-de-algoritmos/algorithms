/*
 * Descripcion: Usando la tecnica de la pila monotona para
 * calcular para cada indice, el elemento menor a la
 * izquierda
 * Tiempo: O(n)
 */

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);

  int n = 12,
      heights[n] = {1, 8, 4, 9, 9, 10, 3, 2, 4, 8, 1, 13},
      leftSmaller[n];
  stack<int> st;
  FOR(i, 0, n) {
    while (!st.empty() && heights[st.top()] > heights[i])
      st.pop();
    if (st.empty())
      leftSmaller[i] = -1;
    else
      leftSmaller[i] = st.top();
    st.push(i);
  }
}