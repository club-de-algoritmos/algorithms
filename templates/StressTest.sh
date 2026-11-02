# Script de stress testing para verificar soluciones contra una solucion de fuerza bruta
# mediante generacion aleatoria de casos de prueba.

set -e
source ~/.bashrc

g++-14 -Wall -Wconversion -Wfatal-errors -g -std=c++23 -fsanitize=undefined,address sol.cpp -o sol
g++-14 -Wall -Wconversion -Wfatal-errors -g -std=c++23 -fsanitize=undefined,address brute.cpp -o brute
g++-14 -Wall -Wconversion -Wfatal-errors -g -std=c++23 -fsanitize=undefined,address gen.cpp -o gen
# g++-14 -Wall -Wconversion -Wfatal-errors -g -std=c++23 -fsanitize=undefined,address checker.cpp -o checker

for((i = 1; ; ++i)); do
    ./gen $i > input_file
    ./sol < input_file > myAnswer
    ./brute < input_file > correctAnswer

    # Validacion por respuesta exacta (diff) o por verificador (checker)
    diff -Z myAnswer correctAnswer > /dev/null || break
    # ./checker > checker_log || break

    echo "Passed test: "  $i
done

echo "WA on the following test:"
cat input_file
echo "Your answer is:"
cat myAnswer
echo "Correct answer is:"
cat correctAnswer
# cat checker_log
