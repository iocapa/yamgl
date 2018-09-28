#ifndef _Y_POINT_HPP_
#define _Y_POINT_HPP_

#include "y_types.hpp"
#include "y_platform.hpp"

namespace yamgl {

/// @brief Simple point class
class y_point {
public:
    Y_DECL_CONSTEXPR y_point();
    Y_DECL_CONSTEXPR y_point(y_int16 x, y_int16 y);

    Y_DECL_CONSTEXPR inline y_int16 x() const;
    Y_DECL_CONSTEXPR inline y_int16 y() const;
    Y_DECL_CONSTEXPR inline void set_x(y_int16 x);
    Y_DECL_CONSTEXPR inline void set_y(y_int16 y);

    Y_DECL_CONSTEXPR inline y_point& operator+=(const y_point& p);
    Y_DECL_CONSTEXPR inline y_point& operator-=(const y_point& p);

    friend Y_DECL_CONSTEXPR inline const y_point operator+(const y_point& p1, const y_point& p2);
    friend Y_DECL_CONSTEXPR inline const y_point operator-(const y_point& p1, const y_point& p2);

    friend Y_DECL_CONSTEXPR inline bool operator!=(const y_point& p1, const y_point& p2);
    friend Y_DECL_CONSTEXPR inline bool operator==(const y_point& p1, const y_point& p2);

private:
    y_int16 _x;
    y_int16 _y;
};

/// @brief Default constructor
Y_DECL_CONSTEXPR inline y_point::y_point() 
    : _x(0), _y(0) {}

/// @brief Argument constructor
Y_DECL_CONSTEXPR inline y_point::y_point(y_int16 x, y_int16 y) 
    : _x(x), _y(y) {}

/// @brief Getter for X value
Y_DECL_CONSTEXPR inline y_int16 y_point::x() const {
    return _x;
}

/// @brief Getter for Y value
Y_DECL_CONSTEXPR inline y_int16 y_point::y() const {
    return _y;
}

/// @brief X setter
Y_DECL_CONSTEXPR inline void y_point::set_x(y_int16 x) {
    _x = x;
}

/// @brief Y setter
Y_DECL_CONSTEXPR inline void y_point::set_y(y_int16 y) {
    _y = y;
}

/// @brief Overload for += operator
Y_DECL_CONSTEXPR inline y_point& y_point::operator+=(const y_point& p) {
    _x += p._x;
    _y += p._y;
    return *this;
}

/// @brief Overload for -= operator
Y_DECL_CONSTEXPR inline y_point& y_point::operator-=(const y_point& p) {
    _x -= p._x;
    _y -= p._y;
    return *this;
}

/// @brief Sum of 2 points
Y_DECL_CONSTEXPR inline const y_point operator+(const y_point& p1, const y_point& p2) {
    return y_point(p1._x + p2._x, p1._y + p2._y);
}

/// @brief Difference of 2 points
Y_DECL_CONSTEXPR inline const y_point operator-(const y_point& p1, const y_point& p2) {
    return y_point(p1._x - p2._x, p1._y - p2._y);
}

/// @brief p1 != p2
Y_DECL_CONSTEXPR inline bool operator!=(const y_point& p1, const y_point& p2) {
    return (p1._x != p2._x) || (p1._y != p2._y);
}

/// @brief p1 == p2
Y_DECL_CONSTEXPR inline bool operator==(const y_point& p1, const y_point& p2) {
    return (p1._x == p2._x) && (p1._y == p2._y);
}

} //yamgl

#endif