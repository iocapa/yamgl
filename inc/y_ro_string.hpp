#ifndef _Y_RO_STRING_HPP_
#define _Y_RO_STRING_HPP_

#include "y_types.hpp"
#include "y_platform.hpp"

namespace yamgl {

/// @brief Read-Only class
class y_ro_string {
public:
    Y_DECL_CONSTEXPR y_ro_string();
    Y_DECL_CONSTEXPR y_ro_string(const char* string);

    class iterator {
    public:
        Y_DECL_CONSTEXPR iterator();
        Y_DECL_CONSTEXPR iterator(const char* current);
        Y_DECL_CONSTEXPR inline iterator& operator++();
        Y_DECL_CONSTEXPR inline bool is_valid() const;
        Y_DECL_CONSTEXPR inline y_uint16 operator*() const;
    
    private:
        const char* _current;
    };

    Y_DECL_CONSTEXPR inline iterator begin() const;

private:
    const char* _string;
};

/// @brief Implicit constructor
Y_DECL_CONSTEXPR inline y_ro_string::y_ro_string()
    : _string(nullptr) {}

/// @brief Explicit constructor
Y_DECL_CONSTEXPR inline y_ro_string::y_ro_string(const char* string)
    : _string(string) {}

/// @brief Begin iterator
Y_DECL_CONSTEXPR inline y_ro_string::iterator y_ro_string::begin() const {
    return y_ro_string::iterator(_string);
}

/// @brief Iterator
Y_DECL_CONSTEXPR inline y_ro_string::iterator::iterator()
    : _current(nullptr) {}

/// @brief Iterator
Y_DECL_CONSTEXPR inline y_ro_string::iterator::iterator(const char* current)
    : _current(current) {}

/// @brief Interator increment
Y_DECL_CONSTEXPR inline y_ro_string::iterator& y_ro_string::iterator::operator++() {
    y_uint8* lcur = (y_uint8*)_current;
    
    if (*lcur >= 0xF0) {
        _current += 4;
    } else if (*lcur >= 0xE0) {
        _current += 3;
    } else if (*lcur >= 0xB0) {
        _current += 2;
    } else {
        _current += 1;
    }
}

/// @brief True if valid
Y_DECL_CONSTEXPR inline bool y_ro_string::iterator::is_valid() const {
    return (*_current != '\0');
}

/// @brief Get unicode code (0x0 - 0xFFFF)
Y_DECL_CONSTEXPR inline y_uint16 y_ro_string::iterator::operator*() const {
    y_uint16 unicode = 0;
    y_uint8* lcur = (y_uint8*)_current; 

    if (*lcur >= 0xE0) {
        unicode = (*lcur & 0x0F) << 12;
        unicode |= (*lcur++ & 0x3F) << 6;
        unicode |= (*lcur & 0x3F);
    } else if (*lcur >= 0xB0) {
        unicode = (*lcur++ & 0x1F) << 6;
        unicode |= (*lcur & 0x3F);
    } else {
        unicode = (*lcur & 0x7F);
    }

    return unicode;
}

} //End yamgl   

#endif