#ifndef _Y_LINE_HPP_
#define _Y_LINE_HPP_

#include "y_types.hpp"
#include "y_point.hpp"

namespace yamgl {

/// @brief Simple point class
class y_line {
public:
    constexpr y_line();
    constexpr y_line(const y_point& p1, const y_point& p2);
    constexpr y_line(y_int16 x1, y_int16 y1, y_int16 x2, y_int16 y2);

    constexpr inline y_point p1() const;
    constexpr inline y_point p2() const;

private:
    y_point _p1;
    y_point _p2;    
};

/// @brief Default constructor
constexpr y_line::y_line()
    : _p1(0, 0),
    _p2(0, 0) {}

/// @brief Argument constructor
constexpr y_line::y_line(const y_point& p1, const y_point& p2)
    : _p1(p1),
    _p2(p2) {}

/// @brief Argument constructor
constexpr y_line::y_line(y_int16 x1, y_int16 y1, y_int16 x2, y_int16 y2)
    : _p1(x1, y1),
    _p2(x2, y2) {}

/// @brief Getter
constexpr y_point y_line::p1() const {
    return _p1;
}

/// @brief Getter
constexpr y_point y_line::p2() const {
    return _p2;
}    

} //yamgl

#endif