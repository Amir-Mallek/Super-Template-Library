# Rational Number Template

```cpp
struct rat {
    // den always positive
    ll num, den;

    rat() : num(0), den(1) {}
	rat(ll _num) : num(_num), den(1) {}
    rat(ll _num, ll _den) {
        assert(_den != 0);
        ll g = gcd(_num, _den);
        num = _num / g;
        den = _den / g;
        if (den < 0) {
            num = -num;
            den = -den;
        }
    }

    rat operator+(const rat &other) const {
        return rat(num*other.den + other.num*den, den*other.den);
    }
    rat operator-(const rat &other) const {
        return rat(num*other.den - other.num*den, den*other.den);
    }
    rat operator*(const rat &other) const {
        return rat(num * other.num, den * other.den);
    }
    rat operator/(const rat &other) const {
        assert(other.num != 0);
        return rat(num * other.den, den * other.num);
    }
    rat operator-() const { return rat(-num, den); }
    rat operator+(const ll &other) const { return rat(num + other * den, den); }
    rat operator-(const ll &other) const { return rat(num - other * den, den); }
    rat operator*(const ll &other) const { return rat(num * other, den); }
    rat operator/(const ll &other) const {
        assert(other != 0);
        return rat(num, den * other);
    }

    bool operator==(const rat &other) const { return num == other.num && den == other.den; }
    bool operator!=(const rat &other) const { return !(*this == other); }
    bool operator<(const rat &other) const { return num * other.den < other.num * den; }
    bool operator<=(const rat &other) const { return num * other.den <= other.num * den; }
    bool operator>(const rat &other) const { return num * other.den > other.num * den; }
    bool operator>=(const rat &other) const { return num * other.den >= other.num * den; }

    explicit operator ll() const { return num / den; }
    explicit operator double() const { return (double)num / den; }
};

ostream& operator<<(ostream &os, const rat &f) {
    if (f.den == 1) return os << f.num;
    return os << f.num << "/" << f.den;
}

istream& operator>>(istream& is, rat& c) {
    ll val; is >> val;
    c = rat(val);
    return is;
}

double sqrt(rat f) { return sqrt((double)f); }
int sign(rat f) { return (f.num > 0) - (f.num < 0); }
rat abs(rat f) { return rat(abs(f.num), f.den); }
```