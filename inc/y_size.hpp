#ifndef _Y_SIZE_HPP_
#define _Y_SIZE_HPP_

#include "y_types.hpp"

namespace yamgl {

/// @brief Simple size class
class y_size {
public:
    constexpr y_size();
    constexpr y_size(y_int16 w, y_int16 h);

    constexpr inline y_int16 w() const;
    constexpr inline y_int16 h() const;
    constexpr y_int16 set_w(y_int16 w);
    constexpr y_int16 set_h(y_int16 h);

    friend constexpr inline bool operator!=(const y_size& s1, const y_size& s2);
    friend constexpr inline bool operator==(const y_size& s1, const y_size& s2);

private:
    y_int16 _w;
    y_int16 _h;
};

/// @brief Default constructor
constexpr y_size::y_size() 
    : _w(0), _h(0) {}

/// @brief Argument constructor
constexpr y_size::y_size(y_int16 w, y_int16 h) 
    : _w(w), _h(h) {}

/// @brief Width getter
constexpr y_int16 y_size::w() const {
    return _w;
}

/// @brief Heigth getter
constexpr y_int16 y_size::h() const {
    return _h;
}

/// @brief Width setter
constexpr y_int16 y_size::set_w(y_int16 w) {
    _w = w;
}

/// @brief Heigth setter
constexpr y_int16 y_size::set_h(y_int16 h) {
    _h = h;
}

/// @brief s1 != s2
constexpr bool operator!=(const y_size& s1, const y_size& s2) {
    return (s1._w != s2._w) || (s1._h != s2._h);
}

/// @brief s1 == s2
constexpr bool operator==(const y_size& s1, const y_size& s2) {
    return (s1._w == s2._w) && (s1._h == s2._h);
}

} //yamgl

#endif