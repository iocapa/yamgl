#include "y_painter.hpp"
#include "y_func.hpp"

namespace yamgl {

/// @brief Constructor
y_painter::y_painter(y_surface* base) 
    : _base(base),
    _font(nullptr),
    _fill(base->_inverted), _brush(!base->_inverted),
    _row_mult(1 << 8) /*,
    _tflags(left_right)*/ {

    // Fill background
    if (!_base->_transparent) {
        _base->_device->fill_area(_base->_clip.x1(), _base->_clip.y1(),
                                   _base->_clip.x2(), _base->_clip.y2(),
                                   _fill);
    }
}

/// @brief Internal bitmap.
void y_painter::p_draw_bitmap(const y_point& p, const y_bitmap& bmap) {

    //Setup
    y_rect barea((p.x() - (bmap.w >> 1)), (p.y() - (bmap.h >> 1)), (bmap.w + 1), (bmap.h + 1));
    y_rect bounds = _affine.map_rect(barea);
    bounds.translate(_base->_offset);
    bounds &= _base->_clip;

    //Clip
    if (bounds.is_valid()) {
        for (y_int32 x = bounds.x1(); x <= bounds.x2(); x++) {
            for (y_int32 y = bounds.y1(); y <= bounds.y2(); y++) {

                //Map
                y_point lp = _affine.map_inv(y_point(x, y) - _base->_offset) - barea.top_left();

                if (bmap.pixel(lp.x(), lp.y())) {
                    _base->_device->plot_pixel(x, y, _brush);
                } 
            }
        }
    }
}

/// @brief Draw a text run
void y_painter::p_draw_text_run(const y_point& p, y_ro_string::iterator& it, y_uint16 count) {
    y_point lp = p;

    while (count--) {
        const y_glyph* gl = _font->p_glyph(*it);
        y_point px = lp + y_point(gl->left, gl->top);
        p_draw_bitmap(px, gl->bitmap);
        lp += y_point(gl->advance, 0);
        ++it;
    }
}

/// @brief Set used font
void y_painter::set_font(y_font& font) {
    _font = &font;
}

/// @brief Set text mode flags
void y_painter::set_text_mode(y_uint16 flags) {
    _tflags = flags;
}

/// @brief Set row distance multiplier (8.8 signed fixed point)
void y_painter::set_row_modifier(y_int16 multiplier) {
    _row_mult = multiplier;
}

/// @brief Set brush color
void y_painter::set_brush(bool color) {
    _brush = color;
}

/// @brief Set fill color
void y_painter::set_fill(bool color) {
    _fill = color;
}

/// @brief Set transform
void y_painter::set_transform(const y_affine& aff) {
    _affine = aff;
}

/// @brief Reset transform
void y_painter::reset_transform() {
    _affine = y_affine(); 
}

/// @brief Draw a point
void y_painter::draw_point(y_int16 x, y_int16 y) {
    draw_point(y_point(x, y));
}

/// @brief Draw a point
void y_painter::draw_point(const y_point& point) {
    y_point lp = _affine.map(point) + _base->_offset;
    
    //Clip
    if (_base->_clip.contains(lp)) {
        _base->_device->plot_pixel(lp.x(), lp.y(), _brush);
    }
}

/// @brief Draw some points
void y_painter::draw_points(const y_point* points, y_uint16 count) {
    for (y_int32 i = 0; i < count; i++) {
        draw_point(points[i]);
    }
}

/// @brief Draw a line
void y_painter::draw_line(const y_line& line) {
    draw_line(line.p1(), line.p2());
}

/// @brief Draw a line
void y_painter::draw_line(const y_point& p1, const y_point& p2) {
    y_point lp1 = _affine.map(p1) + _base->_offset;
    y_point lp2 = _affine.map(p2) + _base->_offset;

    // Points
    y_int32 x1 = lp1.x() << 8;
    y_int32 y1 = lp1.y() << 8;
    y_int32 x2 = lp2.x() << 8;
    y_int32 y2 = lp2.y() << 8;

    // Clip region
    y_int32 cx1 = _base->_clip.x1() << 8;
    y_int32 cy1 = _base->_clip.y1() << 8;
    y_int32 cx2 = _base->_clip.x2() << 8;
    y_int32 cy2 = _base->_clip.y2() << 8;

    bool accept = false;

    // Cohen - Sutherland code
    auto cs_code = [cx1, cy1, cx2, cy2](y_int32 x, y_int32 y) {
        y_uint8 code = 0;
        if (y < cy1) { code |= 1; } // Top
        else if (y > cy2) { code |= 2; } // Bottom
        if (x < cx1) { code |= 4; } // Left
        else if (x > cx2) { code |= 8; } //Right
        return code;
    };

    // Fractionalline plotter
    auto plot_line = [this](y_int32 x1, y_int32 y1, y_int32 x2, y_int32 y2) {
        y_int32 dx = x2 - x1;
        y_int32 dy = y2 - y1;

        y_int32 steps = y_max(y_abs(dx), y_abs(dy));

        y_int32 x = x1 + (1 << 7);
        y_int32 y = y1 + (1 << 7);

        y_int32 xinc = (steps != 0) ? ((dx << 8) / steps) : 0;
        y_int32 yinc = (steps != 0) ? ((dy << 8) / steps) : 0;

        for (y_int32 i = 0; i < (steps >> 8); i++) {
            this->_base->_device->plot_pixel((x >> 8), (y >> 8), this->_brush);
            x += xinc;
            y += yinc;
        }
    };

    y_uint8 c1 = cs_code(x1, y1);
    y_uint8 c2 = cs_code(x2, y2);

    while (true) {
        if (!(c1 | c2)) { //Inside
            accept = true;
            break;
        } else if (c1 & c2) { //Outside
            break;
        } else {
            y_int32 x, y;

            y_uint8 oc = c1 ? c1 : c2; // First code

            // Cut
            if (oc & 1) {
                y = cy1;
                x = (((x2 - x1) * (cy1 - y1)) / (y2 - y1)) + x1;
            } else if (oc & 2) {
                y = cy2;
                x = (((x2 - x1) * (cy2 - y1)) / (y2 - y1)) + x1;
            } else if (oc & 4) {
                x = cx1;
                y = (((y2 - y1) * (cx1 - x1)) / (x2 - x1)) + y1;
            } else if (oc & 8) {
                x = cx2;
                y = (((y2 - y1) * (cx2 - x1)) / (x2 - x1)) + y1;
            }

            // Swap
            if (oc == c1) {
                x1 = x; y1 = y;
                c1 = cs_code(x1, y1);
            } else {
                x2 = x; y2 = y;
                c2 = cs_code(x2, y2);
            }
        }
    }

    if (accept) { plot_line(x1, y1, x2, y2); }
}

/// @brief Draw a line
void y_painter::draw_line(y_int16 x1, y_int16 y1, y_int16 x2, y_int16 y2) {
    draw_line(y_point(x1, y1), y_point(x2, y2));
}

/// @brief Draw some lines
void y_painter::draw_lines(const y_line* lines, y_uint16 count) {
    for (y_int32 i = 0; i < count; i++) {
        draw_line(lines[i].p1(), lines[i].p2());
    }
}

/// @brief Draw some lines (in pairs)
void y_painter::draw_lines(const y_point* pairs, y_uint16 count) {
    for (y_int32 i = 1; i < (count * 2); i += 2) {
        draw_line(pairs[i], pairs[i - 1]);
    }
}

/// @brief Draw a polyline
void y_painter::draw_polyline(const y_point* points, y_uint16 count) {
    for (y_int32 i = 1; i < count; i++) {
        draw_line(points[i - 1], points[i]);
    }
}

/// @brief Draw a pixmap
void y_painter::draw_pixmap(y_int16 x, y_int16 y, const y_pixmap& pixmap) {
    y_point lp = y_point(x, y);
    draw_pixmap(lp, pixmap);
}

/// @brief Draw a pixmap
void y_painter::draw_pixmap(const y_point& origin, const y_pixmap& pixmap) {
    p_draw_bitmap(origin, pixmap.r_bitmap());
}

/// @brief Draw text at given position
void y_painter::draw_text(const y_point& pos, const y_ro_string& text) {
    y_point lp = pos;
    y_uint16 count;
    
    auto it = text.begin();
    auto nit = it;

    while (it.is_valid()) {
        count = 0;
        while (*it != '\n' && it.is_valid()) {
            ++it;
            count++;
        }
        ++it;
        p_draw_text_run(lp, nit, count);
        lp += y_point(0, (_font->advance() * _row_mult) >> 8);
        nit = it;
    } 
}

/// @brief Draw text at given position
void y_painter::draw_text(y_int16 x, y_int16 y, const y_ro_string& text) {
    draw_text(y_point(x, y), text);
}

/// @brief Draw rectangle aligned text
void y_painter::draw_text(const y_rect& rect, const y_ro_string& text, y_uint16 flags) {
    y_int16 n_rows = 0;
    y_int16 curr_w = 0;
    y_int16 max_h = 0;
    
    //Count rows
    for (auto it = text.begin(); it.is_valid(); ++it) {
        if (*it == '\n') {
            n_rows++;
            curr_w = 0;
        } else {
            const y_glyph* gl = _font->p_glyph(*it);
            curr_w += gl->advance;
            max_h = y_max(max_h, gl->bitmap.h);

            if ((flags & char_wrap) && (curr_w >= rect.w())) {
                n_rows++;
                curr_w = 0;
            }
        }
    }

    //Scaled row size
    y_int16 row_size = (_font->advance() * _row_mult) >> 8;

    //Align vertically
    y_int16 row_y;
    if (flags & align_v_center) {
        row_y = rect.y1() + ((rect.h() - ((row_size * n_rows) + max_h)) >> 1) + max_h;
    } else if (flags & align_bottom) {
        row_y = rect.y2() - (row_size * n_rows);
    } else { //align_top
        row_y = rect.y1() + max_h;
    }

    //X alignment
    auto comp_x = [&rect, &flags](y_int16 width) {
        y_int16 val;
        if (flags & align_h_center) {
            val = rect.x1() + ((rect.w() - width) >> 1);
        } else if (flags & align_right) {
            val = rect.x2() - width;
        } else { //align_left
            val = rect.x1();
        }
        return val;
    };

    //Interate again
    auto nit = text.begin();
    y_int16 curr_count = 0;
    curr_w = 0;

    //Draw
    for (auto it = nit; it.is_valid(); ++it) {
        y_uint16 ucode = *it;

       if (ucode == '\n') {
            p_draw_text_run(y_point(comp_x(curr_w), row_y), nit, curr_count);
            nit = it;
            ++nit;
            row_y += row_size;
            curr_w = 0;
            curr_count = 0;
        } else {
            const y_glyph* gl = _font->p_glyph(ucode);
            curr_count++;
            curr_w += gl->advance;

            if ((flags & char_wrap) && (curr_w >= rect.w())) {
                p_draw_text_run(y_point(comp_x(curr_w), row_y), nit, curr_count);
                nit = it;
                ++nit;
                row_y += row_size;
                curr_w = 0;
                curr_count = 0;
            }
        }
    }

    //Last one
    p_draw_text_run(y_point(comp_x(curr_w), row_y), nit, curr_count);
}

/// @brief Draw polygon
void y_painter::draw_polygon(const y_point* points, y_uint16 count) {
    //TODO
    y_assert(false);
}

/// @brief Draw rectangle
void y_painter::draw_rect(const y_rect& rect) {
    //TODO
    y_assert(false);
}

/// @brief Draw rectangle
void y_painter::draw_rect(y_int16 x, y_int16 y, y_int16 w, y_int16 h) {
    //TODO
    y_assert(false);
}

/// @brief Draw rectangle
void y_painter::draw_rect(const y_point& p, const y_size& size) {
    //TODO
    y_assert(false);
}

/// @brief Draw rectangle
void y_painter::draw_rects(const y_rect* rects, y_uint16 count) {
    //TODO
    y_assert(false);
}

} //yamgl