#include "y_widget.hpp"

namespace yamgl {

/// @brief Redraw this and all children
void y_widget::redraw_all() {
    if (active()) {
        update_view(_parent);
        if (visible()) {
            paint_event();
            for (auto it = _children.begin(); it.is_valid(); ++it) {
                (*it)->redraw_all();
            }
        }
    }
}

/// @brief Dummy paint event
void y_widget::paint_event() {

}

} //yamgl