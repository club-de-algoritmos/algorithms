/*
 * Descripcion: con la pila monotona, calcula para cada i,
 * el j mas cercano a la izquierda tal que a[j] < a[i]
 * Tiempo: O(n)
 */

void monotonickStack(vector<int>& a, vector<int>& leftSmaller) {
  stack<int> st;
  for (int i = 0; i < n; ++i) {
    while (!st.empty() && a[st.top()] > a[i]) {
      st.pop();
    }
    leftSmaller[i] = st.empty() ? -1 : st.top();
    st.push(i);
  }
}