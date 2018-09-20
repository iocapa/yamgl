#ifndef _Y_WIDGET_HPP_
#define _Y_WIDGET_HPP_

#include "y_surface.hpp"
#include "y_device.hpp"
#include "y_list_forward.hpp"

namespace yamgl {

/// @brief Base widget class
class y_widget : public y_surface {
public:
    constexpr y_widget(y_widget* parent = 0);

    constexpr void add_child(y_widget* child);
    constexpr void attach_device(y_device& dev);

    void redraw_all();

    virtual void paint_event();

private:
    y_list_forward<y_widget*>::node _node;
    y_list_forward<y_widget*> _children;

    y_widget* _parent;
};

/// @brief Called on chaining widgets
constexpr y_widget::y_widget(y_widget* parent)
    : y_surface(parent),
    _node(this),
    _parent(parent) {
        if (parent) { parent->add_child(this); }
    }

/// @brief Attach a device to al children
constexpr void y_widget::attach_device(y_device& dev) {
    set_device(dev);
    for (auto it = _children.begin(); it.is_valid(); ++it) {
        (*it)->attach_device(dev);
    }
}

/// @brief Add a child
constexpr void y_widget::add_child(y_widget* child) {
    _children.add_node(child->_node);
}

} //yamgl

#endif