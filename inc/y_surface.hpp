#ifndef _Y_SURFACE_HPP_
#define _Y_SURFACE_HPP_

#include "y_rect.hpp"
#include "y_device.hpp"

namespace yamgl {

/// @brief Surface class (to be painted on)
class y_surface {
public:
    constexpr y_surface(y_surface* parent = 0);

    constexpr bool visible() const;
    constexpr bool active() const;
    constexpr bool transparent() const;
    constexpr bool inverted() const;

    constexpr void set_active(bool state);
    constexpr void set_transparent(bool state);
    constexpr void set_inverted(bool state);

    constexpr y_size size() const;
    constexpr y_point position() const;
    constexpr y_point scroll() const;

    constexpr void set_position(const y_point& p);

protected:
    constexpr void set_scroll(const y_point& p);
    constexpr void set_size(const y_size& s);

    constexpr void update_view(const y_surface* master);
    constexpr void set_device(y_device& dev);

private:
    friend class y_painter;

    y_device* _device;

    bool _visible;
    bool _active;
    bool _transparent;
    bool _inverted;

    //Actual requested
    y_rect _viewport;
    y_point _scroll;

    //Processed (in real device space)
    y_rect _clip;
    y_point _offset;
};

/// @brief Explicit constructor (by child)
constexpr y_surface::y_surface(y_surface* parent)
    : _device(parent ? parent->_device : nullptr),
    _visible(parent ? parent->_visible : false), 
    _active(parent ? parent->_active : true), 
    _transparent(parent ? parent->_transparent : false), 
    _inverted(parent ? parent->_inverted : false) {}

/// @brief Return true if is visible
constexpr bool y_surface::visible() const {
    return _visible;
}

/// @brief Return true if active  
constexpr bool y_surface::active() const {
    return _active;
}

/// @brief return true if is transparent
constexpr bool y_surface::transparent() const {
    return _transparent;
}

/// @brief Return true if is inverted
constexpr bool y_surface::inverted() const {
    return _inverted;
}

/// @brief Enable view
constexpr void y_surface::set_active(bool state) {
    _active = state;
}

/// @brief Set transparency
constexpr void y_surface::set_transparent(bool state) {
    _transparent = state;
}

/// @brief Set inversion
constexpr void y_surface::set_inverted(bool state) {
    _inverted = state;
}

/// @brief Get window size
constexpr y_size y_surface::size() const {
    return _viewport.size();
}

/// @brief Get position
constexpr y_point y_surface::position() const {
    return _viewport.top_left();
}

/// @brief Get scroll
constexpr y_point y_surface::scroll() const {
    return _scroll;
}

/// @brief Set position
constexpr void y_surface::set_position(const y_point& p) {
    _viewport.move_to(p);
}

/// @brief
constexpr void y_surface::set_scroll(const y_point& p) {
    _scroll = p;
}

/// @brief
constexpr void y_surface::set_size(const y_size& s) {
    _viewport.set_size(s);
}

/// @brief Setup the attached device
constexpr void y_surface::set_device(y_device& dev) {
    _device = &dev;
}

/// @brief Update viewport and clip data
constexpr void y_surface::update_view(const y_surface* master) {

    //Copy the requested viewport
    _clip = _viewport;

    //Actual viewport top left corner
    _offset = _clip.top_left();

    if (master) {
        //Offset with master's viewport
        _offset += master->_offset;

        //Reset origin to offset
        _clip.move_to(_offset);

        //Clip against master
        _clip &= master->_clip;
    } else {
        //In case we have no master, just clip against the display area
        _clip &= y_rect(y_point(0, 0), _device->r_size());
    }

    //Offset here for child and painter;
    _offset += _scroll;

    _visible = _clip.is_valid();
}

} //yamgl

#endif