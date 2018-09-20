#include "y_types.hpp"
#include "y_font.hpp"
#include "y_bitmap.hpp"

namespace yamgl {
    
/// @brief Return a pointer to a glyph pointed by unicode
const y_glyph* y_font::p_glyph(y_uint16 unicode) {
    const y_glyph* ret;

    while (true) {
        if (unicode > _data.maps[_cindex].to) { //Search up
            if (_cindex < (_data.n_maps - 1)) {
                _coffset += (y_int32)_data.maps[_cindex].to + 1;
                _cindex++; 
                _coffset -= (y_int32)_data.maps[_cindex].from;
                if (unicode < _data.maps[_cindex].from) {
                    ret = &_data.glyphs[_data.n_glyphs - 1]; //Invalid glyph
                    break;
                }
            } else {
                ret = &_data.glyphs[_data.n_glyphs - 1]; //Invalid glyph
                break;
            }
        } else if (unicode < _data.maps[_cindex].from) { //Search down
            if (_cindex > 0) { 
                _coffset += (y_int32)_data.maps[_cindex].from;
                _cindex--;
                _coffset -= (y_int32)_data.maps[_cindex].to + 1;
                if (unicode > _data.maps[_cindex].to) {
                    ret = &_data.glyphs[_data.n_glyphs - 1]; //Invalid glyph
                    break;
                }
            } else {
                ret = &_data.glyphs[_data.n_glyphs - 1]; //Invalid glyph
                break;
            }
        } else {
            ret = &_data.glyphs[unicode + _coffset]; //Found one!!!
            break;
        }
    }
    return ret;
}

/// @brief Return a copy to a glyph pointed by unicode
y_glyph y_font::glyph(y_uint16 unicode) {
    return *p_glyph(unicode);
}

/// @brief Return a reference to a glyph pointed by unicode
const y_glyph& y_font::r_glyph(y_uint16 unicode) {
    return *p_glyph(unicode);
}

} //yamgl