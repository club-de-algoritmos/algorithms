/**
 * Descripcion: rutinas para realizar calculos sobre fechas,
 * en estas rutinas, los meses son expresados como enteros
 * desde el 1 al 12, los dias como enteros desde el 1 al 31,
 * y los anios como enteros de 4 digitos.
 */
string dayOfWeek[] = {"Mon", "Tue", "Wed", "Thu",
                      "Fri", "Sat", "Sun"};

// Convierte fecha Gregoriana a entero (fecha Juliana)
int dateToInt(int m, int d, int y) {
  return 1461 * (y + 4800 + (m - 14) / 12) / 4 +
         367 * (m - 2 - (m - 14) / 12 * 12) / 12 -
         3 * ((y + 4900 + (m - 14) / 12) / 100) / 4 + d -
         32075;
}

// Convierte entero (fecha Juliana) a Gregoriana: M/D/Y
void intToDate(int jd, int &m, int &d, int &y) {
  int x, n, i, j;

  x = jd + 68569;
  n = 4 * x / 146097;
  x -= (146097 * n + 3) / 4;
  i = (4000 * (x + 1)) / 1461001;
  x -= 1461 * i / 4 - 31;
  j = 80 * x / 2447;
  d = x - 2447 * j / 80;
  x = j / 11;
  m = j + 2 - 12 * x;
  y = 100 * (n - 49) + i + x;
}

// Convierte entero (fecha Juliana) a dia de la semana
string intToDay(int jd) { return dayOfWeek[jd % 7]; }

int main() {
  int jd = dateToInt(3, 24, 2004);
  int m, d, y;
  intToDate(jd, m, d, y);
  string day = intToDay(jd);

  // Salida esperada:
  // 2453089
  // 3/24/2004
  // Wed
  cout << jd << endl
       << m << "/" << d << "/" << y << endl
       << day << endl;
}