/**
 * Descripcion: algoritmo que resuelve un problema de DP de
 * digitos. La DP de digitos se requiere cuando se trabaja
 * sobre cadenas (normalmente numeros) de una gran cantidad
 * de digitos y se requiere saber cuantos numeros en un
 * rango cumplen con cierta propiedad. Enunciado del
 * problema resuelto: Dada una cadena s que contiene numeros
 * y caracteres ? encontrar el minimo entero, tal que se
 * forme asignandole valores a los ? y ademas sea divisible
 * por D; si no existe, imprimir un *
 * Tiempo: O(n^2)
 */

string s;
int D;
stack<int> st;

bool dp[MAXN][MAXN];  // He pasado por aqui?
bool solve(int i, int residuo) {
  if (dp[i][residuo]) return false;
  if (i == s.length()) return residuo == 0;

  if (s[i] == '?') {
    for (int k = (i == 0); k <= 9; k++) {
      if (solve(i + 1, (residuo * 10 + k) % D)) {
        st.push(k);
        return true;
      }
    }
  } else {
    if (solve(i + 1, (residuo * 10 + (s[i] - '0')) % D)) {
      st.push(s[i] - '0');
      return true;
    }
  }
  dp[i][residuo] = true;
  return false;
}

int main() {
  cin >> s >> D;

  if (solve(0, 0)) {
    while (!st.empty()) {
      cout << st.top();
      st.pop();
    }
    cout << ENDL;
  } else
    cout << "*\n";

  return 0;
}
