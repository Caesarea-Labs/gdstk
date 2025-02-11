#include "polygon_c.h"
#include "gdstk/polygon.hpp"
#include "gdstk/vec.hpp"

using namespace gdstk;

// Internal wrapper structures
struct GDSTK_Array {
    gdstk::Array<void*>* array;
};

struct GDSTK_Vec2 {
    double x;
    double y;
};

struct GDSTK_Polygon {
    Polygon polygon;
};

extern "C" {

// Constructor and destructor
GDSTK_Polygon* gdstk_polygon_create(int unused) {
    auto* wrapper = new GDSTK_Polygon;
    return wrapper;
}

void gdstk_polygon_free(GDSTK_Polygon* polygon) {
    if (polygon) {
        polygon->polygon.clear();
        delete polygon;
    }
}

void gdstk_polygon_clear(GDSTK_Polygon* polygon) {
    if (polygon) {
        polygon->polygon.clear();
    }
}

void gdstk_polygon_copy_from(GDSTK_Polygon* dst, const GDSTK_Polygon* src) {
    if (dst && src) {
        dst->polygon.copy_from(src->polygon);
    }
}

// Basic properties and methods
double gdstk_polygon_area(const GDSTK_Polygon* polygon) {
    return polygon ? polygon->polygon.area() : 0.0;
}

double gdstk_polygon_signed_area(const GDSTK_Polygon* polygon) {
    return polygon ? polygon->polygon.signed_area() : 0.0;
}

double gdstk_polygon_perimeter(const GDSTK_Polygon* polygon) {
    return polygon ? polygon->polygon.perimeter() : 0.0;
}

// Point containment
int gdstk_polygon_contain(const GDSTK_Polygon* polygon, const GDSTK_Vec2* point) {
    if (!polygon || !point) return 0;
    Vec2 p = {point->x, point->y};
    return polygon->polygon.contain(p) ? 1 : 0;
}

int gdstk_polygon_contain_all(const GDSTK_Polygon* polygon, const GDSTK_Vec2* points, uint64_t count) {
    if (!polygon || !points) return 0;
    Array<Vec2> pts;
    pts.ensure_slots(count);
    for (uint64_t i = 0; i < count; i++) {
        pts.append({points[i].x, points[i].y});
    }
    return polygon->polygon.contain_all(pts) ? 1 : 0;
}

int gdstk_polygon_contain_any(const GDSTK_Polygon* polygon, const GDSTK_Vec2* points, uint64_t count) {
    if (!polygon || !points) return 0;
    Array<Vec2> pts;
    pts.ensure_slots(count);
    for (uint64_t i = 0; i < count; i++) {
        pts.append({points[i].x, points[i].y});
    }
    return polygon->polygon.contain_any(pts) ? 1 : 0;
}

// Bounding box
void gdstk_polygon_bounding_box(const GDSTK_Polygon* polygon, GDSTK_Vec2* min, GDSTK_Vec2* max) {
    if (!polygon || !min || !max) return;
    Vec2 vmin, vmax;
    polygon->polygon.bounding_box(vmin, vmax);
    min->x = vmin.x;
    min->y = vmin.y;
    max->x = vmax.x;
    max->y = vmax.y;
}

// Transformations
void gdstk_polygon_translate(GDSTK_Polygon* polygon, const GDSTK_Vec2* v) {
    if (!polygon || !v) return;
    polygon->polygon.translate({v->x, v->y});
}

void gdstk_polygon_scale(GDSTK_Polygon* polygon, const GDSTK_Vec2* scale, const GDSTK_Vec2* center) {
    if (!polygon || !scale || !center) return;
    polygon->polygon.scale({scale->x, scale->y}, {center->x, center->y});
}

void gdstk_polygon_mirror(GDSTK_Polygon* polygon, const GDSTK_Vec2* p0, const GDSTK_Vec2* p1) {
    if (!polygon || !p0 || !p1) return;
    polygon->polygon.mirror({p0->x, p0->y}, {p1->x, p1->y});
}

void gdstk_polygon_rotate(GDSTK_Polygon* polygon, double angle, const GDSTK_Vec2* center) {
    if (!polygon || !center) return;
    polygon->polygon.rotate(angle, {center->x, center->y});
}

void gdstk_polygon_transform(GDSTK_Polygon* polygon, double magnification, int x_reflection, 
                           double rotation, const GDSTK_Vec2* origin) {
    if (!polygon || !origin) return;
    polygon->polygon.transform(magnification, x_reflection != 0, rotation, {origin->x, origin->y});
}

// Advanced operations
void gdstk_polygon_fillet(GDSTK_Polygon* polygon, const double* radii, uint64_t radii_count, double tolerance) {
    if (!polygon || !radii) return;
    Array<double> rad;
    rad.ensure_slots(radii_count);
    for (uint64_t i = 0; i < radii_count; i++) {
        rad.append(radii[i]);
    }
    polygon->polygon.fillet(rad, tolerance);
}

void gdstk_polygon_fracture(const GDSTK_Polygon* polygon, uint64_t max_points, double precision, 
                          struct GDSTK_Array* result) {
    if (!polygon || !result) return;
    polygon->polygon.fracture(max_points, precision, *reinterpret_cast<Array<Polygon*>*>(result->array));
}

void gdstk_polygon_apply_repetition(GDSTK_Polygon* polygon, struct GDSTK_Array* result) {
    if (!polygon || !result) return;
    polygon->polygon.apply_repetition(*reinterpret_cast<Array<Polygon*>*>(result->array));
}

// Factory functions for creating specific polygon shapes
GDSTK_Polygon* gdstk_polygon_rectangle(const GDSTK_Vec2* corner1, const GDSTK_Vec2* corner2, int tag) {
    if (!corner1 || !corner2) return nullptr;
    auto* wrapper = new GDSTK_Polygon;
    wrapper->polygon = rectangle({corner1->x, corner1->y}, {corner2->x, corner2->y}, tag);
    return wrapper;
}

GDSTK_Polygon* gdstk_polygon_cross(const GDSTK_Vec2* center, double full_size, double arm_width, int tag) {
    if (!center) return nullptr;
    auto* wrapper = new GDSTK_Polygon;
    wrapper->polygon = cross({center->x, center->y}, full_size, arm_width, tag);
    return wrapper;
}

GDSTK_Polygon* gdstk_polygon_regular(const GDSTK_Vec2* center, double side_length, uint64_t sides, 
                                   double rotation, int tag) {
    if (!center) return nullptr;
    auto* wrapper = new GDSTK_Polygon;
    wrapper->polygon = regular_polygon({center->x, center->y}, side_length, sides, rotation, tag);
    return wrapper;
}

GDSTK_Polygon* gdstk_polygon_ellipse(const GDSTK_Vec2* center, double radius_x, double radius_y,
                                    double inner_radius_x, double inner_radius_y,
                                    double initial_angle, double final_angle,
                                    double tolerance, int tag) {
    if (!center) return nullptr;
    auto* wrapper = new GDSTK_Polygon;
    wrapper->polygon = ellipse({center->x, center->y}, radius_x, radius_y,
                             inner_radius_x, inner_radius_y,
                             initial_angle, final_angle, tolerance, tag);
    return wrapper;
}

GDSTK_Polygon* gdstk_polygon_racetrack(const GDSTK_Vec2* center, double straight_length,
                                      double radius, double inner_radius,
                                      int vertical, double tolerance, int tag) {
    if (!center) return nullptr;
    auto* wrapper = new GDSTK_Polygon;
    wrapper->polygon = racetrack({center->x, center->y}, straight_length,
                               radius, inner_radius, vertical != 0,
                               tolerance, tag);
    return wrapper;
}

// Text to polygon conversion
void gdstk_polygon_text(const char* s, double size, const GDSTK_Vec2* position,
                       int vertical, int tag, struct GDSTK_Array* result) {
    if (!s || !position || !result) return;
    text(s, size, {position->x, position->y}, vertical != 0, tag, *reinterpret_cast<Array<Polygon*>*>(result->array));
}

// Contour generation
int gdstk_polygon_contour(const double* data, uint64_t rows, uint64_t cols,
                         double level, double scaling, struct GDSTK_Array* result) {
    if (!data || !result) return -1;
    return contour(data, rows, cols, level, scaling, *reinterpret_cast<Array<Polygon*>*>(result->array)) == ErrorCode::NoError ? 0 : -1;
}

// Point containment for multiple polygons
void gdstk_polygon_inside(const GDSTK_Vec2* points, uint64_t point_count,
                         const GDSTK_Polygon** polygons, uint64_t polygon_count,
                         int* result) {
    if (!points || !polygons || !result) return;
    
    Array<Vec2> pts;
    pts.ensure_slots(point_count);
    for (uint64_t i = 0; i < point_count; i++) {
        pts.append({points[i].x, points[i].y});
    }
    
    Array<Polygon*> poly_ptrs;
    poly_ptrs.ensure_slots(polygon_count);
    for (uint64_t i = 0; i < polygon_count; i++) {
        if (polygons[i]) {
            poly_ptrs.append(const_cast<Polygon*>(&polygons[i]->polygon));
        }
    }
    
    bool* temp = new bool[point_count];
    inside(pts, poly_ptrs, temp);
    for (uint64_t i = 0; i < point_count; i++) {
        result[i] = temp[i] ? 1 : 0;
    }
    delete[] temp;
}

int gdstk_polygon_all_inside(const GDSTK_Vec2* points, uint64_t point_count,
                            const GDSTK_Polygon** polygons, uint64_t polygon_count) {
    if (!points || !polygons) return 0;
    
    Array<Vec2> pts;
    pts.ensure_slots(point_count);
    for (uint64_t i = 0; i < point_count; i++) {
        pts.append({points[i].x, points[i].y});
    }
    
    Array<Polygon*> poly_ptrs;
    poly_ptrs.ensure_slots(polygon_count);
    for (uint64_t i = 0; i < polygon_count; i++) {
        if (polygons[i]) {
            poly_ptrs.append(const_cast<Polygon*>(&polygons[i]->polygon));
        }
    }
    
    return all_inside(pts, poly_ptrs) ? 1 : 0;
}

int gdstk_polygon_any_inside(const GDSTK_Vec2* points, uint64_t point_count,
                            const GDSTK_Polygon** polygons, uint64_t polygon_count) {
    if (!points || !polygons) return 0;
    
    Array<Vec2> pts;
    pts.ensure_slots(point_count);
    for (uint64_t i = 0; i < point_count; i++) {
        pts.append({points[i].x, points[i].y});
    }
    
    Array<Polygon*> poly_ptrs;
    poly_ptrs.ensure_slots(polygon_count);
    for (uint64_t i = 0; i < polygon_count; i++) {
        if (polygons[i]) {
            poly_ptrs.append(const_cast<Polygon*>(&polygons[i]->polygon));
        }
    }
    
    return any_inside(pts, poly_ptrs) ? 1 : 0;
}

} // extern "C" 