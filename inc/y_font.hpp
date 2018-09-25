#ifndef _Y_FONT_HPP_
#define _Y_FONT_HPP_

#include "y_types.hpp"
#include "y_bitmap.hpp"
#include "y_platform.hpp"

namespace yamgl {
    
/// @brief Glyph data structure
struct y_glyph {
    const y_bitmap bitmap;
    const y_int8 left;
    const y_int8 top;
    const y_int8 advance;
};

/// @brief Single unicode map
struct y_unicode_map {
    const y_uint16 from;
    const y_uint16 to;
};

/// @brief Font data structure
struct y_font_data {
    const y_glyph* glyphs;
    const y_unicode_map* maps;
    const y_uint16 n_glyphs;
    const y_uint16 n_maps;
    const y_int16 advance;
};

/// @brief Font object
class y_font {
public:
    Y_DECL_CONSTEXPR y_font(const y_font_data &data);
    
    Y_DECL_CONSTEXPR inline y_int16 advance() const;

    y_glyph glyph(y_uint16 unicode);
    const y_glyph& r_glyph(y_uint16 unicode);
    const y_glyph* p_glyph(y_uint16 unicode);
    

private:
    const y_font_data& _data;
    y_int32 _coffset;
    y_uint16 _cindex;
};

/// #brief Default constructor
Y_DECL_CONSTEXPR inline y_font::y_font(const y_font_data& data)
    : _data(data), _cindex(0), _coffset(-data.maps[0].from) {}

/// #brief Get font vertical advance
Y_DECL_CONSTEXPR inline y_int16 y_font::advance() const {
    return _data.advance;
}    

} //yamgl

#endif