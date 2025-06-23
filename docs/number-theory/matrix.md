# Matrix Manipulation

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

## Notes

- If you have $q$ queries and in each query you will calculate $A \cdot M^n$ ($A$ is a column vector), the complexity will be $\mathcal{O}(Q \cdot N^3 \cdot \log_2 N)$.
To improve this, precompute for every $0 \leq i \leq \log_2 N$, the matrices $M^{2^i}$, and then to answer each query multiply the column vector by the corresponding powers of two from the binary representation of $n$.
Example: $((A \cdot M^2) \cdot M^8) \cdot M^{16}$. The time complexity will now be $\mathcal{O}(N^3 \cdot \log_2 N + Q \cdot N^2 \cdot \log_2 N)$

- To calculate this:

$a_i = (c_1 \cdot a_{i-1} + c_2 \cdot a_{i-2} + \cdots + c_n \cdot a_{i-n}) + p + i \cdot q + i^2 \cdot r$

$
\begin{bmatrix}
c_1 & c_2 & \cdots & c_{n-1} & c_n & 1 & 1 & 1 \\
1   & 0   & \cdots & 0   & 0 & 0 & 0 & 0 \\
0   & 1   & \cdots & 0   & 0 & 0 & 0 & 0 \\
\vdots & \vdots & \ddots & \vdots & \vdots & \vdots & \vdots & \vdots \\
0 & 0 & \cdots & 1 & 0 & 0 & 0 & 0 \\
0 & 0 & \cdots & 0 & 0 & 1 & 0 & 0 \\
0 & 0 & \cdots & 0 & 0 & 1 & 1 & 0 \\
0 & 0 & \cdots & 0 & 0 & 1 & 2 & 1
\end{bmatrix}
\cdot
\begin{bmatrix}
a_{i-1} \\
a_{i-2} \\
a_{i-3} \\
\vdots \\
a_{i-n} \\
1 \\
i \\
i^2
\end{bmatrix}
$

- If you prove if some $(S, \oplus, \otimes)$ is a semi-ring than you can use these new operation in the matrix multiplication.

example: $S = \mathbb{Z}_{< \text{LLMAX}}$,  $a \oplus b := \min(a, b)$, $\quad a \otimes b := a + b$.

- If you want to convert a problem to a matrix exponentiation problem you need to make it so `new_dp[i] = some linear function of prev_dp[j]` 

- Practise problems in ascending difficulty: [https://codeforces.com/gym/102644]