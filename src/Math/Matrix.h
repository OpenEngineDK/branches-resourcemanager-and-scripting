// Math matrix
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <string>
#include <sstream>
#include <boost/static_assert.hpp>

#include <Math/Vector.h>

namespace OpenEngine {
namespace Math {

/**
 * Matrix.
 *
 * @class Matrix Matrix.h Math/Matrix.h
 * @param M Number of rows
 * @param N Number of columns
 * @param T Type of elements
 */
template <int M, int N, class T>
class Matrix {
private:
    // matrix elements
    T elm[M][N];

public:
    /**
     * Create identity matrix.
     * If the dimension is not NxN zero-rows will appear.
     *
     * @code
     * Matrix<3,3,int> m;   // [(1, 0, 0), (0, 1, 0), (0, 0, 1)]
     * @endcode
     */
    Matrix() {
        for (int i=0; i<M; i++)
            for (int j=0; j<N; j++)
                elm[i][j] = (i==j)?(T)1:(T)0;
    }
    /**
     * Create matrix from scalar.
     * @code
     * Matrix<2,3,int> m(7);   // [(7, 7, 7), (7, 7, 7)]
     * @endcode
     *
     * @param s Scalar value in all indexes
     */
    explicit Matrix(const T s) {
        for (int i=0; i<M; i++)
            for (int j=0; j<N; j++)
                elm[i][j] = s;
    }
    /**
     * Copy constructor.
     *
     * @param m Matrix to copy
     */
    Matrix(const Matrix<M,N,T>& m) {
        for (int i=0; i<M; i++)
            for (int j=0; j<N; j++)
                elm[i][j] = m.elm[i][j];
    }
    /**
     * Create matrix form array.
     *
     * @param a Array to create from
     */
    explicit Matrix(const T a[M*N]) {
        for (int i=0; i<M; i++)
            for (int j=0; j<N; j++)
                elm[i][j] = a[i*N + j];
    }
    /**
     * Create a Mx3 matrix from 3 M-length vectors.
     */
    Matrix(const Vector<M,T> x, const Vector<M,T> y, const Vector<M,T> z) {
        BOOST_STATIC_ASSERT(N==3);
        x.ToArray(elm[0]);
        y.ToArray(elm[1]);
        z.ToArray(elm[2]);
    }
    /**
     * Constructor for a 2x2 matrix.
     */
    Matrix(const T a, const T b, const T c, const T d) {
        BOOST_STATIC_ASSERT(M==2 && N==2);
        elm[0][0]=a; elm[0][1]=b;
        elm[1][0]=c; elm[1][1]=d;
    }
    /**
     * Constructor for a 3x3 matrix.
     */
    Matrix(const T a, const T b, const T c, 
           const T d, const T e, const T f, 
           const T g, const T h, const T i) {
        BOOST_STATIC_ASSERT(M==3 && N==3);
        elm[0][0]=a; elm[0][1]=b; elm[0][2]=c;
        elm[1][0]=d; elm[1][1]=e; elm[1][2]=f;
        elm[2][0]=g; elm[2][1]=h; elm[2][2]=i;
    }
    /**
     * Constructor for a 4x4 matrix.
     */
    Matrix(const T a, const T b, const T c, const T d, 
           const T e, const T f, const T g, const T h,
           const T i, const T j, const T k, const T l, 
           const T o, const T p, const T q, const T r) {
        BOOST_STATIC_ASSERT(M==4 && N==4);
        elm[0][0]=a; elm[0][1]=b; elm[0][2]=c; elm[0][3]=d;
        elm[1][0]=e; elm[1][1]=f; elm[1][2]=g; elm[1][3]=h;
        elm[2][0]=i; elm[2][1]=j; elm[2][2]=k; elm[2][3]=l;
        elm[3][0]=o; elm[3][1]=p; elm[3][2]=q; elm[3][3]=r;
    }
    /**
     * Index access to matrix elements.
     * @code
     * Matrix<2,2,int> m(1,2, 3,4);   // [(1, 2), (3, 4)]
     * m(1,0)                         // 3
     * @endcode
     *
     * @param i Row index
     * @param j Column index
     * @return Element at index \a (i,j)
     */
    T& operator()(const int i, const int j) {
        if (i < 0 || i >= M)
            throw IndexOutOfBounds(i,0,M);
        if (j < 0 || j >= N)
            throw IndexOutOfBounds(j,0,N);
        return elm[i][j];
    }
    /**
     * Matrix equality.
     * True if all index element are identical.
     */
    bool operator==(const Matrix<M,N,T>& m) const {
        for (int i=0; i<M; i++)
            for (int j=0; j<N; j++)
                if (elm[i][j] != m.elm[i][j])
                    return false;
        return true;
    }
    /**
     * Matrix inequality.
     * True if one or more index elements differ.
     */
    bool operator!=(const Matrix<M,N,T>& m) const {
        return !(*this == m);
    }
    /**
     * Matrix multiplication.
     * @code
     * Matrix<2,2,int> a(1,2,3,4);     // [(1,  2), ( 3,  4)]
     * a * a;                          // [(7, 10), (15, 22)]
     * @endcode
     */
    const Matrix<M,M,T> operator*(const Matrix<N,M,T> m) {
        Matrix<M,M,T> r;
        for (int i=0; i<M; i++) 
            for (int j=0; j<M; j++) {
                T s = 0;
                for (int t=0; t<N; t++)
                    s += elm[i][t] * m.elm[t][j];
                r.elm[i][j] = s;
            }
        return r;
    }
    /**
     * Get matrix row vector.
     * @code
     * Matrix<2,2,int> m(1,2, 3,4);   // [(1, 2), (3, 4)]
     * m[1]                           // [3, 4]
     * @endcode
     *
     * @see GetRow()
     * @param i Row index
     * @return Row vector
     */
    Vector<N,T> operator[](const int i) {
        return this->GetRow(i);
    }
    /**
     * Get matrix row vector.
     *
     * @param i Row index
     * @return Row vector
     */
    Vector<N,T> GetRow(const int i) {
        return Vector<N,T>(elm[i]);
    }
    /**
     * Get matrix column vector.
     *
     * @param j Column index
     * @return Column vector
     */
    Vector<M,T> GetColumn(const int j) {
        Vector<M,T> v;
        for (int i=0; i<M; i++)
            v[i] = elm[i][j];
        return v;
    }
    /**
     * Matrix trace.
     * Only defined for NxN matrices.
     *
     * @return Sum of elements in the main diagonal
     */
    T Trace() {
        BOOST_STATIC_ASSERT(N==M);
        T t = 0;
        for (int i=0; i<M; i++)
            t += elm[i][i];
        return t;
    }
    /**
     * Transpose matrix.
     * Note that this is a destructive operation and only works on
     * square matrices.
     */
    void Transpose() {
        BOOST_STATIC_ASSERT(M==N);
        T tmp;
        for (int i=1; i<M; i++)
            for (int j=0; j<i; j++) {
                tmp = elm[i][j];
                elm[i][j] = elm[j][i];
                elm[j][i] = tmp;
            }
    }
    /**
     * Get a matrix expanded by one column and one row.
     * The column and row will consist of zero elements and a one in
     * the diagonal entry.
     *
     * @code
     * Matrix<2,2,int> m(1,2, 3,4);  // [(1,2), (3,4)]
     * m.GetExpanded()               // [(1,2,0), (3,4,0), (0,0,1)]
     * @endcode
     *
     * @return Reduced matrix.
     */
    Matrix<M+1,N+1,T> GetExpanded() {
        Matrix<M+1,N+1,T> m;
        for (int i=0; i < M; i++)
            for (int j=0; j < N; j++)
                m(i,j) = elm[i][j];
        return m;
    }
    /**
     * Get a matrix reduced by one column and one row.
     *
     * @code
     * Matrix<3,3,int> m(1,2,3, 4,5,6, 7,8,9);  // [(1,2,3), (4,5,6), (7,8,9)]
     * m.GetReduced()                           // [(1,2), (4,5)]
     * @endcode
     *
     * @return Reduced matrix.
     */
    Matrix<M-1,N-1,T> GetReduced() {
        Matrix<M-1,N-1,T> m;
        for (int i=0; i < M-1; i++)
            for (int j=0; j < N-1; j++)
                m(i,j) = elm[i][j];
        return m;
    }
    /**
     * Create array of matrix.
     *
     * @param a Array to populate
     */
    void ToArray(T a[M*N]) const {
        for (int i=0; i<M; i++)
            for (int j=0; j<N; j++)
                a[i*N + j] = elm[i][j];
    }
    /**
     * String representation.
     * Ex. [(1, 2), (3, 4)]
     *
     * @return Matrix as string
     */
    std::string ToString() const {
        std::ostringstream out;
        out << "[";
        for (int i=0; i<M-1; i++) {
            out << "(";
            for (int j=0; j<N-1; j++)
                out << elm[i][j] << ", ";
            out << elm[i][N-1] << "), ";
        }
        out << "(";
        for (int j=0; j<N-1; j++)
            out << elm[M-1][j] << ", ";
        out << elm[M-1][N-1] << ")]";
        return out.str();
    }

}; // Matrix

/**
 * Stream operator to ease the use of ToString method.
 */
template <int M, int N, class T>
std::ostream& operator<<(std::ostream& os, const Matrix<M,N,T> e) {
    os<<e.ToString();
    return os;
}

}  // NS OpenEngine
}  // NS Math

#endif // _MATRIX_H_
