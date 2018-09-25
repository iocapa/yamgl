#ifndef _Y_LINE_HPP_
#define _Y_LINE_HPP_

#include "y_types.hpp"
#include "y_point.hpp"
#include "y_platform.hpp"

namespace yamgl {

/// @brief Simple point class
class y_line {
public:
    Y_DECL_CONSTEXPR y_line();
    Y_DECL_CONSTEXPR y_line(const y_point& p1, const y_point& p2);
    Y_DECL_CONSTEXPR y_line(y_int16 x1, y_int16 y1, y_int16 x2, y_int16 y2);

    Y_DECL_CONSTEXPR inline y_point p1() const;
    Y_DECL_CONSTEXPR inline y_point p2() const;

private:
    y_point _p1;
    y_point _p2;    
};

/// @brief Default constructor
Y_DECL_CONSTEXPR inline y_line::y_line()
    : _p1(0, 0),
    _p2(0, 0) {}

/// @brief Argument constructor
Y_DECL_CONSTEXPR inline y_line::y_line(const y_point& p1, const y_point& p2)
    : _p1(p1),
    _p2(p2) {}

/// @brief Argument constructor
Y_DECL_CONSTEXPR inline y_line::y_line(y_int16 x1, y_int16 y1, y_int16 x2, y_int16 y2)
    : _p1(x1, y1),
    _p2(x2, y2) {}

/// @brief Getter
Y_DECL_CONSTEXPR inline y_point y_line::p1() const {
    return _p1;
}

/// @brief Getter
Y_DECL_CONSTEXPR inline y_point y_line::p2() const {
    return _p2;
}    

} //yamgl

#endif