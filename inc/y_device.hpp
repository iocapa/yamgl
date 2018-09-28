#ifndef _Y_DEVICE_HPP_
#define _Y_DEVICE_HPP_

#include "y_types.hpp"
#include "y_size.hpp"
#include "y_platform.hpp"

namespace yamgl {

/// @brief Device class
class y_device {
public:
    Y_DECL_CONSTEXPR y_device(y_int16 w, y_int16 h);
    
    Y_DECL_CONSTEXPR inline y_size size() const;
    Y_DECL_CONSTEXPR inline const y_size& r_size() const;
    Y_DECL_CONSTEXPR inline const y_size* p_size() const;

    virtual void plot_pixel(y_uint16 x, y_uint16 y, y_color color) = 0;
    virtual void fill_area(y_uint16 x1, y_uint16 y1, y_uint16 x2, y_uint16 y2, y_color color);

private:
    y_size _size;
};

/// @brief Constructor
Y_DECL_CONSTEXPR inline y_device::y_device(y_int16 w, y_int16 h)
    : _size(w, h) {}

/// @brief A size copy
Y_DECL_CONSTEXPR inline y_size y_device::size() const {
    return _size;
}

// /// @brief A size reference
Y_DECL_CONSTEXPR inline const y_size& y_device::r_size() const {
    return _size;
}

/// @brief A size pointer
Y_DECL_CONSTEXPR inline const y_size* y_device::p_size() const {
    return &_size;
}

} //yamgl

#endif