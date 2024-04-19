/**
 * Descripcion: es una variante del BST, que ademas
 * soporta 2 operaciones extra ademas de insercion,
 * busqueda y eliminacion: Select(i) - find_by_order:
 * encontrar el i-esimo elemento (0-indexado) del
 * conjunto ordenado de los elementos, retorna un
 * iterador. Rank(x) - order_of_key: numero de elementos
 * estrictamente menores a x Uso: oset<int> OST Funciona
 * como un set, por lo que nativamente no soporta
 * elementos repetidos. Si se necesitan repetidos, pero
 * no eliminar valores, cambiar la funcion comparadora
 * por less_equal<T>. Si se necesitan repetidos y
 * tambien la eliminacion, agregar una dimension a T en
 * en donde el ultimo parametro sea el diferenciador
 * (por ejemplo, si estamos con enteros, utilizar un
 * pair donde el second sea unico). Modificar el primer
 * y tercer parametro (tipo y funcion comparadora), si
 * se necesita un mapa, en lugar de null_type, escribir
 * el tipo a mapear.
 * Tiempo: O(log n)
 */
#include <bits/extc++.h>
using namespace __gnu_pbds;

template <class T>
using oset = tree<T, null_type, less<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;
