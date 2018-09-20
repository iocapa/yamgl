#ifndef _Y_PIXMAP_HPP_
#define _Y_PIXMAP_HPP_

#include "y_types.hpp"
#include "y_bitmap.hpp"

namespace yamgl {

/// @brief Pixmap object
class y_pixmap {
public:
    constexpr y_pixmap(const y_bitmap& bmap);

    constexpr inline y_int16 w() const;
    constexpr inline y_int16 h() const;

    constexpr y_bitmap bitmap() const;
    constexpr const y_bitmap& r_bitmap() const;
    constexpr const y_bitmap* p_bitmap() const;

private:
    const y_bitmap& _bitmap;
};

/// @brief Default constructor
constexpr y_pixmap::y_pixmap(const y_bitmap& bmap)
    : _bitmap(bmap) {}

/// @brief Getter
constexpr y_int16 y_pixmap::w() const {
    return _bitmap.w;
}

/// @brief Getter
constexpr y_int16 y_pixmap::h() const {
    return _bitmap.h;
} 

/// @brief Copy
constexpr y_bitmap y_pixmap::bitmap() const {
    return _bitmap;
}

/// @brief Reference  
constexpr const y_bitmap& y_pixmap::r_bitmap() const {
    return _bitmap;
}

/// @brief Pointer
constexpr const y_bitmap* y_pixmap::p_bitmap() const {
    return &_bitmap;
}

} //yamgl

#endif