#ifndef _Y_PIXMAP_HPP_
#define _Y_PIXMAP_HPP_

#include "y_types.hpp"
#include "y_bitmap.hpp"
#include "y_platform.hpp"

namespace yamgl {

/// @brief Pixmap object
class y_pixmap {
public:
    Y_DECL_CONSTEXPR y_pixmap(const y_bitmap& bmap);

    Y_DECL_CONSTEXPR inline y_int16 w() const;
    Y_DECL_CONSTEXPR inline y_int16 h() const;

    Y_DECL_CONSTEXPR inline y_bitmap bitmap() const;
    Y_DECL_CONSTEXPR inline const y_bitmap& r_bitmap() const;
    Y_DECL_CONSTEXPR inline const y_bitmap* p_bitmap() const;

private:
    const y_bitmap& _bitmap;
};

/// @brief Default constructor
Y_DECL_CONSTEXPR inline y_pixmap::y_pixmap(const y_bitmap& bmap)
    : _bitmap(bmap) {}

/// @brief Getter
Y_DECL_CONSTEXPR inline y_int16 y_pixmap::w() const {
    return _bitmap.w;
}

/// @brief Getter
Y_DECL_CONSTEXPR inline y_int16 y_pixmap::h() const {
    return _bitmap.h;
} 

/// @brief Copy
Y_DECL_CONSTEXPR inline y_bitmap y_pixmap::bitmap() const {
    return _bitmap;
}

/// @brief Reference  
Y_DECL_CONSTEXPR inline const y_bitmap& y_pixmap::r_bitmap() const {
    return _bitmap;
}

/// @brief Pointer
Y_DECL_CONSTEXPR inline const y_bitmap* y_pixmap::p_bitmap() const {
    return &_bitmap;
}

} //yamgl

#endif