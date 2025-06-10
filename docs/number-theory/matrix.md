```cpp
template<typename T, int N, int M>
struct Matrix {
    array<array<T, M>, N> data;

    Matrix() : data() {}
    Matrix(const array<array<T, M>, N>& init) : data(init) {}

    static Matrix identity() {
        static_assert(N == M, "Identity matrix requires square dimensions");
        Matrix result;
        for (int i = 0; i < N; ++i) {
            result.data[i][i] = T(1);
        }
        return result;
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    template<int P>
    Matrix<T, N, P> operator*(const Matrix<T, M, P>& other) const {
        Matrix<T, N, P> result;
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < M; ++k) {
                for (int j = 0; j < P; ++j) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix& operator+=(const Matrix& other) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    Matrix& operator-=(const Matrix& other) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                data[i][j] -= other.data[i][j];
            }
        }
        return *this;
    }

    template<int P>
    Matrix<T, N, P>& operator*=(const Matrix<T, M, P>& other) {
        *this = *this * other;
        return *this;
    }

    Matrix operator+(const T& scalar) const {
        Matrix result = *this;
        for (int i = 0; i < N; ++i) result.data[i][i] += scalar;
        return result;
    }

    Matrix& operator+=(const T& scalar) {
        for (int i = 0; i < N; ++i) data[i][i] += scalar;
        return *this;
    }

    Matrix operator-(const T& scalar) const {
        return (*this) + (-scalar);
    }

    Matrix& operator-=(const T& scalar) {
        return *this += -scalar;
    }

    Matrix operator*(const T& scalar) const {
        Matrix result;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    Matrix& operator*=(const T& scalar) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                data[i][j] *= scalar;
            }
        }
        return *this;
    }

    array<T, M>& operator[](int row) { return data[row]; }

    Matrix operator-() const {
        return (*this) * -1;
    }

    Matrix pow(ll exponent) const {
        static_assert(N == M, "Matrix exponentiation requires square matrices");

        Matrix result = Matrix::identity();
        Matrix base = *this;

        while (exponent > 0) {
            if (exponent & 1)
                result *= base;
            base *= base;
            exponent >>= 1;
        }
        return result;
    }

    void print() const {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};
```