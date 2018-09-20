#ifndef _Y_RECT_HPP_
#define _Y_RECT_HPP_

#include "y_types.hpp"
#include "y_size.hpp"
#include "y_point.hpp"
#include "y_func.hpp"
#include "y_assert.hpp"

namespace yamgl {

/// @brief y_rectangle class
class y_rect {
public:
    constexpr y_rect();
    constexpr y_rect(y_int16 x, y_int16 y, y_int16 w, y_int16 h);
    constexpr y_rect(const y_point& p, const y_size& s);  
    constexpr y_rect(const y_point& p1, const y_point& p2);

    constexpr inline y_int16 x1() const;
    constexpr inline y_int16 x2() const;
    constexpr inline y_int16 y1() const;
    constexpr inline y_int16 y2() const;

    constexpr inline bool is_valid() const;
    constexpr inline bool contains(const y_point& p) const;

    constexpr inline void set_top_left(const y_point& p);
    constexpr inline void set_top_right(const y_point& p);
    constexpr inline void set_bottom_left(const y_point& p);
    constexpr inline void set_bottom_right(const y_point& p);

    constexpr inline y_point top_left() const;
    constexpr inline y_point top_right() const;
    constexpr inline y_point bottom_left() const;
    constexpr inline y_point bottom_right() const;

    constexpr inline void move_to(const y_point& p);
    constexpr inline void translate(const y_point& p);

    constexpr inline void set_size(const y_size& s);
    constexpr inline y_size size() const;

    constexpr inline y_rect& operator&=(const y_rect& r);
    constexpr inline y_rect& operator|=(const y_rect& r);

private:
    y_int16 _x1;
    y_int16 _y1;
    y_int16 _x2;
    y_int16 _y2;
};

/// @brief Default constructor
constexpr y_rect::y_rect()
    : _x1(0), _y1(0), _x2(-1), _y2(-1) {};

/// @brief Construct by corner integers
constexpr y_rect::y_rect(y_int16 x, y_int16 y, y_int16 w, y_int16 h)
    : _x1(x), _y1(y), _x2(x + w - 1), _y2(y + h - 1) {}

/// @brief Construct by corner and size
constexpr y_rect::y_rect(const y_point& p, const y_size& s)
    : _x1(p.x()), _y1(p.y()), 
        _x2(p.x() + s.w() - 1),
        _y2(p.y() + s.h() - 1) {}

/// @brief Construct by corner y_points
constexpr y_rect::y_rect(const y_point& p1, const y_point& p2)
    : _x1(p1.x()), _y1(p1.y()),
    _x2(p2.x()), _y2(p2.y()) {}

/// @brief Getter
constexpr y_int16 y_rect::x1() const {
    return _x1;
}

/// @brief Getter
constexpr y_int16 y_rect::x2() const {
    return _x2;
}

/// @brief Getter
constexpr y_int16 y_rect::y1() const {
    return _y1;
}

/// @brief Getter
constexpr y_int16 y_rect::y2() const {
    return _y2;
}

/// @brief Return true if the y_rectangle is valid
constexpr bool y_rect::is_valid() const {
    return (_x2 >= _x1) && (_y2 >= _y1);
}

/// @brief Return true if y_point is contained inside the area
constexpr bool y_rect::contains(const y_point& p) const {
    return (p.x() >= _x1) && (p.x() <= _x2) && (p.y() >= _y1) && (p.y() <= _y2);
}

/// @brief Set corner
constexpr void y_rect::set_top_left(const y_point& p) {
    _x1 = p.x();
    _y1 = p.y();
}

/// @brief Set corner
constexpr void y_rect::set_top_right(const y_point& p) {
    _x2 = p.x();
    _y1 = p.y();
}

/// @brief Set corner
constexpr void y_rect::set_bottom_left(const y_point& p) {
    _x1 = p.x();
    _y2 = p.y();
}

/// @brief Set corner
constexpr void y_rect::set_bottom_right(const y_point& p) {
    _x2 = p.x();
    _y2 = p.y();
}

/// @brief Get corner
constexpr y_point y_rect::top_left() const {
    return y_point(_x1, _y1);
}

/// @brief Get corner
constexpr y_point y_rect::top_right() const {
    return y_point(_x2, _y1);
}

/// @brief Get corner
constexpr y_point y_rect::bottom_left() const {
    return y_point(_x1, _y2);
}

/// @brief Get corner
constexpr y_point y_rect::bottom_right() const {
    return y_point(_x2, _y2);
}

/// @brief Move by dragging left corner
constexpr void y_rect::move_to(const y_point& p) {
    _x2 += p.x() - _x1;
    _y2 += p.y() - _y1;
    _x1 = p.x();
    _y1 = p.y();
}

/// @brief Translate by offset
constexpr inline void y_rect::translate(const y_point& p) {
    _x1 += p.x();
    _x2 += p.x();
    _y1 += p.y();
    _y2 += p.y();
}

/// @brief Set rectangle size
constexpr void y_rect::set_size(const y_size& s) {
    _x2 = _x1 + s.w() - 1;
    _y2 = _y1 + s.h() - 1;
}  

/// @brief Return rectangle's size
constexpr y_size y_rect::size() const {
    return y_size(_x2 - _x1 + 1, _y2 - _y1 + 1);
}

/// @brief Intersection of 2 y_rectangles
constexpr y_rect& y_rect::operator&=(const y_rect& r) {
    //Trivially reject invalids
    if ((r._x1 > _x2) || (_x1 > r._x2) //X not intersecting
    || (r._y1 > _y2) || (_y1 > r._y2) //Y not intersecting
    || (_x2 < _x1) || (r._x2 < r._x1) //X invalid
    || (_y2 < _y1) || (r._y2 < r._y1)) { //Y invalid
        _x2 = _x1 - 1;
        _y2 = _y1 - 1;
    } else {
        _x1 = y_max(_x1, r._x1);
        _x2 = y_min(_x2, r._x2);
        _y1 = y_max(_y1, r._y1);
        _y2 = y_min(_y2, r._y2);
    }
    return *this;
}

/// @brief Union of 2 y_rectangles
constexpr y_rect& y_rect::operator|=(const y_rect& r) {
    //TODO Implement
    y_assert(false);
}

} //yamgl

#endif