#ifndef _Y_BITMAP_HPP_
#define _Y_BITMAP_HPP_

#include "y_types.hpp"

namespace yamgl {

/// @brief Bitmap data structure
struct y_bitmap {
    const y_uint8* buf;
    const y_int16 w;
    const y_int16 h;

    inline y_color pixel(y_int32 x, y_int32 y) const;
};

y_color y_bitmap::pixel(y_int32 x, y_int32 y) const {
    bool ret;

    if ((x < 0) || (y < 0) || (x >= w) || (y >= h)) {
        ret = false;
    } else {
        y_int32 start = (y * w) + x;
        ret = ((buf[start >> 3] << (start & 7)) & 0x80u) != 0;
    }

    return ret;
}

} //yamgl

#endif