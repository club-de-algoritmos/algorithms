/**
 * Descripcion: crea un segment tree donde guarda sus
 * formas pasadas cuando se hace una actualizacion
 * soporta consultas y actualizaciones en rango
 * Tiempo: log(n)
 */

template<class T, int SZ> struct pseg {
    static const int LIMIT = 1e7; // adjust
    int l[LIMIT], r[LIMIT], has_lazy[LIMIT], nex = 0;
    T val[LIMIT], lazy[LIMIT];
    //// HELPER
    int copy(int cur) {
        int x = nex++;
        val[x]=val[cur],l[x]=l[cur],r[x]=r[cur],lazy[x]=lazy[cur];
        return x;
    }
    T comb(T a, T b) { return a + b; }
    void pull(int x) { val[x] = comb(val[l[x]],val[r[x]]); } 
    void push(int cur, int L, int R) { 
        if (!has_lazy[cur]) return;
        val[cur] += 1ll * (R - L + 1) * lazy[cur];
        if (L != R) {
            l[cur] = copy(l[cur]);
            lazy[l[cur]] = lazy[cur];
            r[cur] = copy(r[cur]);
            lazy[r[cur]] = lazy[cur];
            has_lazy[l[cur]] = has_lazy[r[cur]] = 1;
        }
        has_lazy[cur] = 0;
    }
    //// MAIN FUNCTIONS
    T query(int cur, int lo, int hi, int L, int R) {  
        push(cur, L, R);
        if (R < lo || hi < L) return 0;
        if (lo <= L && R <= hi) return val[cur];

        int M = (L+R)/2;    
    
        return comb(query(l[cur],lo,hi,L,M),
                    query(r[cur],lo,hi,M+1,R));
    }
    int upd(int cur, int lo, int hi, T v, int L, int R) {
      push(cur, L, R);
      if (R < lo || hi < L) return cur;
        int x = copy(cur);
        if (lo <= L && R <= hi) { 
            lazy[x]  = v;
            has_lazy[x] = 1;
              push(x, L, R);
            return x; 
        }
        push(x, L, R);
        int M = (L+R)/2;
        l[x] = upd(l[x],lo,hi,v,L,M);
        r[x] = upd(r[x],lo,hi,v,M+1,R);
        pull(x); return x;
    }
    int build(vector<T>& arr, int L, int R) {
        int cur = nex++;
        if (L == R) {
            if (L < sz(arr)) val[cur] = arr[L];
            return cur;
        }
        int M = (L+R)/2;
        l[cur] = build(arr,L,M), r[cur] = build(arr,M+1,R);
        pull(cur); return cur;
    }
    //// PUBLIC
    vi loc;
    int upd(int time , int lo, int hi, T v) { 
        loc.pb(upd(loc[time],lo,hi,v,0,SZ-1));
        return loc.size() - 1;
    }
    T query(int ti, int lo, int hi) { 
        return query(loc[ti],lo,hi,0,SZ-1); }
    void build(vector<T>& arr) { loc.pb(build(arr,0,SZ-1)); }
};
