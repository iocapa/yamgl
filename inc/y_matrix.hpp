#ifndef _Y_MATRIX_HPP_
#define _Y_MATRIX_HPP_

#include "y_types.hpp"
namespace yamgl {

/// @brief 2x2 matrix
class y_matrix {
public:
    constexpr y_matrix();
    constexpr y_matrix(y_int32 m11, y_int32 m12, y_int32 m21, y_int32 m22);

    constexpr y_int32 a11() const;
    constexpr y_int32 a12() const;
    constexpr y_int32 a21() const;
    constexpr y_int32 a22() const;

    constexpr bool is_identity() const;
    
    constexpr y_matrix operator*(const y_matrix& m);
    constexpr y_matrix& operator*=(const y_matrix& m);
    constexpr y_point operator*(const y_point& p);
    constexpr bool operator==(const y_matrix& m);

private:
    y_int32 _a[2][2];
};

/// @brief Constructor
constexpr y_matrix::y_matrix()
    : _a{} {}

/// @brief Constructor
constexpr y_matrix::y_matrix(y_int32 m11, y_int32 m12, y_int32 m21, y_int32 m22)
    : _a{{m11, m12}, {m21, m22}} {}

/// @brief Getter
constexpr y_int32 y_matrix::a11() const {
    return _a[0][0];
}

/// @brief Getter
constexpr y_int32 y_matrix::a12() const {
    return _a[0][1];
}

/// @brief Getter
constexpr y_int32 y_matrix::a21() const {
    return _a[1][0];
}

/// @brief Getter
constexpr y_int32 y_matrix::a22() const {
    return _a[1][1];
}

/// @brief True if is identity
constexpr bool y_matrix::is_identity() const {
    return (y_matrix((1 << 12), 0, 0, (1 << 12)) == *this);
}

/// @brief Matrix multiplication
constexpr y_matrix y_matrix::operator*(const y_matrix& m) {
    y_matrix lm;
    for (y_uint32 i = 0; i < 2; i++) {
        for (y_uint32 j = 0; j < 2; j++) {
            for (y_uint32 k = 0; k < 2; k++) {
                lm._a[i][j] += _a[i][k] * m._a[k][j];
            }
            lm._a[i][j] >>= 12;
        }
    }
    return lm;
}

/// @brief Matrix multiplication
constexpr y_matrix& y_matrix::operator*=(const y_matrix& m) {
    *this = *this * m;
    return *this;
}

/// @brief Vector multiplication
constexpr y_point y_matrix::operator*(const y_point& p) {
    y_int16 px = ((_a[0][0] * p.x()) + (_a[0][1] * p.y())) >> 12; 
    y_int16 py = ((_a[1][0] * p.x()) + (_a[1][1] * p.y())) >> 12;
    return y_point(px, py);
}

/// @brief Equality
constexpr bool y_matrix::operator==(const y_matrix& m) {
    for (y_uint32 i = 0; i < 2; i++) {
        for (y_uint32 j = 0; j < 2; j++) {
            if (_a[i][j] != m._a[i][j]) { return false; }
        }
    }
    return true;
}

} //yamgl

#endif