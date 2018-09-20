#ifndef _Y_POINT_HPP_
#define _Y_POINT_HPP_

#include "y_types.hpp"

namespace yamgl {

/// @brief Simple point class
class y_point {
public:
    constexpr y_point();
    constexpr y_point(y_int16 x, y_int16 y);

    constexpr inline y_int16 x() const;
    constexpr inline y_int16 y() const;
    constexpr inline void set_x(y_int16 x);
    constexpr inline void set_y(y_int16 y);

    constexpr inline y_point& operator+=(const y_point& p);
    constexpr inline y_point& operator-=(const y_point& p);

    friend constexpr inline const y_point operator+(const y_point& p1, const y_point& p2);
    friend constexpr inline const y_point operator-(const y_point& p1, const y_point& p2);

    friend constexpr inline bool operator!=(const y_point& p1, const y_point& p2);
    friend constexpr inline bool operator==(const y_point& p1, const y_point& p2);

private:
    y_int16 _x;
    y_int16 _y;
};

/// @brief Default constructor
constexpr y_point::y_point() 
    : _x(0), _y(0) {}

/// @brief Argument constructor
constexpr y_point::y_point(y_int16 x, y_int16 y) 
    : _x(x), _y(y) {}

/// @brief Getter for X value
constexpr y_int16 y_point::x() const {
    return _x;
}

/// @brief Getter for Y value
constexpr y_int16 y_point::y() const {
    return _y;
}

/// @brief X setter
constexpr void y_point::set_x(y_int16 x) {
    _x = x;
}

/// @brief Y setter
constexpr void y_point::set_y(y_int16 y) {
    _y = y;
}

/// @brief Overload for += operator
constexpr y_point& y_point::operator+=(const y_point& p) {
    _x += p._x;
    _y += p._y;
    return *this;
}

/// @brief Overload for -= operator
constexpr y_point& y_point::operator-=(const y_point& p) {
    _x -= p._x;
    _y -= p._y;
    return *this;
}

/// @brief Sum of 2 points
constexpr const y_point operator+(const y_point& p1, const y_point& p2) {
    return y_point(p1._x + p2._x, p1._y + p2._y);
}

/// @brief Difference of 2 points
constexpr const y_point operator-(const y_point& p1, const y_point& p2) {
    return y_point(p1._x - p2._x, p1._y - p2._y);
}

/// @brief p1 != p2
constexpr bool operator!=(const y_point& p1, const y_point& p2) {
    return (p1._x != p2._x) || (p1._y != p2._y);
}

/// @brief p1 == p2
constexpr bool operator==(const y_point& p1, const y_point& p2) {
    return (p1._x == p2._x) && (p1._y == p2._y);
}

} //yamgl

#endif