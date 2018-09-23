#ifndef _Y_PAINTER_HPP_
#define _Y_PAINTER_HPP_

#include "y_device.hpp"
#include "y_surface.hpp"
#include "y_rect.hpp"
#include "y_point.hpp"
#include "y_line.hpp"
#include "y_pixmap.hpp"
#include "y_font.hpp"
#include "y_ro_string.hpp"
#include "y_affine.hpp"

namespace yamgl {

enum painter_text_flags {
    align_left = 0x0001,
    align_right = 0x0002,
    align_h_center = 0x0004,
    align_top = 0x0008,
    align_bottom = 0x0010,
    align_v_center = 0x0020,
    align_center = 0x0040,
    char_wrap = 0x0080
};

/// @brief A painter paints onto a surface
class y_painter {
public:
    y_painter(y_surface* base);

    //Text related
    void set_font(y_font& font);
    void set_text_mode(y_uint16 flags);
    void set_row_modifier(y_int16 multiplier);

    //Brushes
    void set_brush(y_color color);
    void set_fill(y_color color);
    
    void set_transform(const y_affine& aff);
    void reset_transform();

    //Points
    void draw_point(y_int16 x, y_int16 y);
    void draw_point(const y_point& point);
    void draw_points(const y_point* points, y_uint16 count);
    
    //Lines
    void draw_line(const y_line& line);
    void draw_line(const y_point& p1, const y_point& p2);
    void draw_line(y_int16 x1, y_int16 y1, y_int16 x2, y_int16 y2);
    void draw_lines(const y_line* lines, y_uint16 count);
    void draw_lines(const y_point* pairs, y_uint16 count);
    void draw_polyline(const y_point* points, y_uint16 count);
    
    //Pixmaps
    void draw_pixmap(y_int16 x, y_int16 y, const y_pixmap& pixmap);
    void draw_pixmap(const y_point& origin, const y_pixmap& pixmap);

    //Text
    void draw_text(const y_point& pos, const y_ro_string& text);
    void draw_text(y_int16 x, y_int16 y, const y_ro_string& text);
    void draw_text(const y_rect& rect, const y_ro_string& text, y_uint16 flags = 0);
    
    //Polygons (fill by set_fill) TODO 
    void draw_polygon(const y_point* points, y_uint16 count);

    //Rectangles (fill by set_fill) TODO
    void draw_rect(const y_rect& rect);
    void draw_rect(y_int16 x, y_int16 y, y_int16 w, y_int16 h);
    void draw_rect(const y_point& p, const y_size& size);
    void draw_rects(const y_rect* rects, y_uint16 count);

private:
    void p_draw_bitmap(const y_point& p, const y_bitmap& bmap);
    void p_draw_text_run(const y_point& p, y_ro_string::iterator& it, y_uint16 count);
 
private:
    const y_surface* _base;
    
    //Text related
    y_font* _font;
    y_uint16 _tflags;
    y_int16 _row_mult;

    //Colors
    y_color _brush;
    y_color _fill;

    //Transform
    y_affine _affine;
};

} //yamgl

#endif