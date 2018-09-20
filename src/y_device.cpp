#include "y_device.hpp"
#include "y_func.hpp"

namespace yamgl {

/// @brief Fill a device region
void y_device::fill_area(y_uint16 x1, y_uint16 y1, y_uint16 x2, y_uint16 y2, y_color color) {
    //x2/y2 have to be > than x1/y1
    for (y_uint16 y = y1; y <= y2; y++) {
        for (y_uint16 x = x1; x <= x2; x++) {
            plot_pixel(x, y, color);
        }
    }
}

} //yamgl