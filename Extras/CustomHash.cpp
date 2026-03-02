/**
 * Descripcion: Hash Maps/Sets ultra-rapidos (PBDS) resistentes a hacks. 
 * Filosofia: Key Compression. Nunca usar structs (pair, vector) como llaves. 
 * Codificarlas a uint64_t o u128 usando Encoder antes de insertar.
 * Uso:
 * FastMap<int> mp; mp.resize(N);        // Mapa de uint64_t -> int
 * uint64_t k = Encoder::p64(x, y);      // Comprimir par (x, y) o punto 2D
 * mp[k]++;                              // O(1) amortizado
 * FastSet128 st;                        // Set de 128 bits (Doble Hash)
 * u128 k2 = Encoder::s128(vec);         // Comprimir vector/string
 * st.insert(k2);
 * Notas:
 * - FastMap (gp): Usa Probing. Muy rapido, mas memoria.
 * - MemMap (cc) : Usa Chaining. Mas lento, menos memoria (usar en limites < 128MB).
 * - resize(N)   : Evita rehash costosos. Usar siempre si N > 10^5.
 * - clear()     : O(capacidad). En multi-casos, declarar mapa adentro del while(t--).
 * Tiempo: O(1) amortizado por operacion.
 */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using u128 = __uint128_t;
static const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count();

struct SafeHash {
    static uint64_t sm64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const { return sm64(x + SEED); }
    size_t operator()(u128 x) const {
        uint64_t t = (uint64_t)(x >> 64), b = (uint64_t)x;
        return sm64(t ^ b ^ SEED);
    }
};

template<class K, class V, class H>
using gp_base = gp_hash_table<K, V, H, equal_to<K>, direct_mask_range_hashing<>, 
    linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, 
    hash_load_check_resize_trigger<>, true>>;

template<class K, class V, class H>
using cc_base = cc_hash_table<K, V, H, equal_to<K>, direct_mask_range_hashing<>, 
    hash_standard_resize_policy<hash_exponential_size_policy<>, 
    hash_load_check_resize_trigger<>, true>>;

template<class V> using FastMap = gp_base<uint64_t, V, SafeHash>;
template<class V> using MemMap = cc_base<uint64_t, V, SafeHash>;
using FastSet = FastMap<null_type>;

template<class V> using FastMap128 = gp_base<u128, V, SafeHash>;
using FastSet128 = FastMap128<null_type>;

namespace Encoder {
    inline uint64_t c64(uint64_t h, uint64_t v) {
        return h ^ (v + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2));
    }
    template<class T1, class T2>
    uint64_t p64(T1 a, T2 b) { return c64(hash<T1>{}(a), hash<T2>{}(b)); }
    template<class I>
    uint64_t s64(const I& s) {
        uint64_t h = 0;
        for (const auto& x : s) h = c64(h, hash<typename I::value_type>{}(x));
        return h;
    }
    template<class T1, class T2>
    u128 p128(T1 a, T2 b) {
        uint64_t h1 = p64(a, b), h2 = c64(hash<T2>{}(b) + 0xABCDE, hash<T1>{}(a));
        return ((u128)h1 << 64) | h2;
    }
    inline u128 pack(uint64_t h1, uint64_t h2) { return ((u128)h1 << 64) | h2; }
}