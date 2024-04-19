/**
 * Descripcion: funciones hash utiles, ya que
 * std::unordered_map no las provee nativamente, es
 * recomendable usar la segunda cuando se trate de un
 * pair<int, int>
 */

struct hash_pair {
  template <class T1, class T2>
  size_t operator()(const pair<T1, T2>& p) const {
    auto hash1 = hash<T1>{}(p.first);
    auto hash2 = hash<T2>{}(p.second);

    if (hash1 != hash2) {
      return hash1 ^ hash2;
    }
    return hash1;
  }
};
unordered_map<pair<int, int>, bool, hash_pair> um;
struct HASH {
  size_t operator()(const pair<int, int>& x) const {
    return (size_t)x.first * 37U + (size_t)x.second;
  }
};
unordered_map<pair<int, int>, int, HASH> xy;
