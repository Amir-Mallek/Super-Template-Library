# Cyclic Data Structure

```cpp
template<int M>
struct cyclic {
    int x;

    cyclic() : x(0) {}
    cyclic(const ll& _x) {
        if (0 <= _x && _x < M) x = _x;
        else if (_x >= M) x = _x % M;
        else x = (_x % M + M) % M;
    }

    explicit operator int() const { return x; }

    cyclic operator+(const cyclic& other) const { return cyclic(1ll*x + other.x); }
    cyclic operator-(const cyclic& other) const { return cyclic(1ll*x - other.x + M); }
    cyclic operator*(const cyclic& other) const { return cyclic(1ll*x * other.x); }
    cyclic operator/(const cyclic& other) const { return (*this) * other.inv(); }
    cyclic operator-() const { return cyclic(M-x); }
    cyclic& operator++() { x = (x + 1) % M; return *this; }
    cyclic& operator--() { x = (x - 1 + M) % M; return *this; }
    cyclic operator++(int) {
        cyclic temp = *this;
        ++(*this);
        return temp;
    }
    cyclic operator--(int) {
        cyclic temp = *this;
        --(*this);
        return temp;
    }
    cyclic& operator+=(const cyclic& other) { x = (1ll*x + other.x) % M; return *this; }
    cyclic& operator-=(const cyclic& other) { x = (1ll*x - other.x + M) % M; return *this; }
    cyclic& operator*=(const cyclic& other) { x = 1ll*x * other.x % M; return *this; }
    cyclic& operator/=(const cyclic& other) { return *this *= other.inv(); }

    bool operator==(const cyclic& other) const { return x == other.x; }
    bool operator!=(const cyclic& other) const { return x != other.x; }

    static cyclic pow(const cyclic& x, ll p) {
        cyclic res(1), base = x;
        while (p > 0) {
            if (p & 1) res *= base;
            base *= base;
            p >>= 1;
        }
        return res;
    }
    static cyclic inv(const cyclic& a) {
        assert(a.x != 0);
        return pow(a, M-2);
    }
    cyclic pow(const ll& p) const { return pow(*this, p); }
    cyclic inv() const { return inv(*this); }

    friend istream& operator>>(istream& is, cyclic& c) {
        ll val; is >> val;
        c = cyclic(val);
        return is;
    }
    friend ostream& operator<<(ostream& os, const cyclic& c) { return os << c.x; }
};

constexpr int MOD = 1e9 + 7;
typedef cyclic<MOD> cint;
```
