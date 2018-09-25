#ifndef _Y_AFFINE_HPP_
#define _Y_AFFINE_HPP_

#include "y_types.hpp"
#include "y_matrix.hpp"
#include "y_func.hpp"
#include "y_platform.hpp"
#include "y_rect.hpp"
#include "y_point.hpp"

namespace yamgl {

/// @brief Affine transformation matrix
class y_affine {
public:
    Y_DECL_CONSTEXPR y_affine();

    Y_DECL_CONSTEXPR inline void translate(y_int16 dx, y_int16 dy);
    Y_DECL_CONSTEXPR inline void rotate(y_int32 rad);
    Y_DECL_CONSTEXPR inline void scale(y_int32 sx, y_int32 sy);
    Y_DECL_CONSTEXPR inline void shear(y_int32 sx, y_int32 sy);

    Y_DECL_CONSTEXPR inline y_point map(const y_point& p);
    Y_DECL_CONSTEXPR inline y_point map_inv(const y_point& p);
    Y_DECL_CONSTEXPR inline y_rect map_rect(const y_rect& r);

    Y_DECL_CONSTEXPR inline bool is_inv_identity() const;
    Y_DECL_CONSTEXPR inline bool is_identity() const;

private:
    y_matrix _direct;
    y_matrix _inverse;
    y_point _offset;
};

/// @brief Default constructor
Y_DECL_CONSTEXPR inline y_affine::y_affine()
    : _direct((1 << 12), 0, 0, (1 << 12)),
    _inverse((1 << 12), 0, 0, (1 << 12)),
    _offset(0, 0) {}

/// @brief Translate
Y_DECL_CONSTEXPR inline void y_affine::translate(y_int16 dx, y_int16 dy) {
    _offset += y_point(dx, dy);
}

/// @brief Rotate, q12 angle (radians)
Y_DECL_CONSTEXPR inline void y_affine::rotate(y_int32 rad) {
    y_int32 lsin = y_sin(rad);
    y_int32 lcos = y_cos(rad);

    //Re-compute matrices
    _direct = y_matrix(lcos, lsin, -lsin, lcos) * _direct;
    _inverse = _inverse * y_matrix(lcos, -lsin, lsin, lcos);
}

/// @brief Scale
Y_DECL_CONSTEXPR inline void y_affine::scale(y_int32 sx, y_int32 sy) {
    y_int32 lsx = (sx == 0) ? 0 : ((1 << 24) / sx);
    y_int32 lsy = (sy == 0) ? 0 : ((1 << 24) / sy);
    
    _direct = y_matrix(sx, 0, 0, sy) * _direct;
    _inverse = _inverse * y_matrix(lsx, 0, 0, lsy);
}

/// @brief Shear
Y_DECL_CONSTEXPR inline void y_affine::shear(y_int32 sx, y_int32 sy) {
    _direct = y_matrix((1 << 12), sx, sy, (1 << 12)) * _direct;
    _inverse = _inverse * y_matrix((1 << 12), -sx, -sy, (1 << 12));
}

/// @brief Map point to transform
Y_DECL_CONSTEXPR inline y_point y_affine::map(const y_point& p) {
    y_point lp;
    
    if (_direct.is_identity()) {
        lp = p;
    } else {
        lp = _direct * p;
    }

    return lp + _offset;
}

/// @brief Map point inverse
Y_DECL_CONSTEXPR inline y_point y_affine::map_inv(const y_point& p) {
    y_point lp = p - _offset;

    if (!_inverse.is_identity()) {
        lp = _inverse * lp;
    }

    return lp;
}

/// @brief Return minimum enclosing rectangle
Y_DECL_CONSTEXPR inline y_rect y_affine::map_rect(const y_rect& r) {
    y_rect lr;

    if (_direct.is_identity()) {
        lr = r;
    } else {
        //Corners
        y_point p1 = _direct * y_point(r.x1(), r.y1());
        y_point p2 = _direct * y_point(r.x1(), r.y2());
        y_point p3 = _direct * y_point(r.x2(), r.y2());
        y_point p4 = _direct * y_point(r.x2(), r.y1());

        //Bounds
        y_int16 x1 = y_min(y_min(p1.x(), p3.x()), y_min(p2.x(), p4.x()));
        y_int16 x2 = y_max(y_max(p1.x(), p3.x()), y_max(p2.x(), p4.x()));
        y_int16 y1 = y_min(y_min(p1.y(), p3.y()), y_min(p2.y(), p4.y()));
        y_int16 y2 = y_max(y_max(p1.y(), p3.y()), y_max(p2.y(), p4.y()));

        lr = y_rect(y_point(x1, y1), y_point(x2, y2));
    }

    lr.translate(_offset);
    return lr;
}

/// @brief Inverse identity
Y_DECL_CONSTEXPR inline bool y_affine::is_inv_identity() const {
    return _inverse.is_identity();
}

/// @brief Direct identity
Y_DECL_CONSTEXPR inline bool y_affine::is_identity() const {
    return _direct.is_identity();
}

} //yamgl

#endif