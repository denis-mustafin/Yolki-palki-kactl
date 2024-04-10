/**
 * Author: Almost Retired
 * Description: Dynamic CHT for maximum and integer quries
 * Time: O(\log N)
 */
// kx + b , query for maximum


struct tline {
    mutable long long k, b, p;
    bool operator <(const tline & o) const {
        return k < o.k;
    }
    bool operator <(long long x) const {
        return p < x;
    }
};

struct tdqht : multiset<tline, less<>> {
    // ( for doubles , use inf = 1/.0, div (a, b) = a/b)
    static const long long inf = LLONG_MAX;
    static long long div(long long a, long long b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect (iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->b > y->b ? inf : -inf;
        else x->p = div(y->b - x->b, x->k - y->k);
        return x->p >= y->p;
    }
    void add ( long long k , long long b) {
        auto z = insert({k, b, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    long long query (long long x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.b;
    }
};
