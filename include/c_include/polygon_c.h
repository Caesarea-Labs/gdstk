#ifndef GDSTK_HEADER_POLYGON_C
#define GDSTK_HEADER_POLYGON_C

#include <stdint.h>
#include <stdio.h>
#include "array_c.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct GDSTK_Polygon GDSTK_Polygon;
typedef struct GDSTK_Vec2 GDSTK_Vec2;

// Constructor and destructor
/**
 *
 * @param unused Intentionally put here, jextract bugs out when there are no parameters.
 */
GDSTK_API GDSTK_Polygon* gdstk_polygon_create(int unused);
GDSTK_API void gdstk_polygon_free(GDSTK_Polygon* polygon);
GDSTK_API void gdstk_polygon_clear(GDSTK_Polygon* polygon);
GDSTK_API void gdstk_polygon_copy_from(GDSTK_Polygon* dst, const GDSTK_Polygon* src);

// Basic properties and methods
GDSTK_API double gdstk_polygon_area(const GDSTK_Polygon* polygon);
GDSTK_API double gdstk_polygon_signed_area(const GDSTK_Polygon* polygon);
GDSTK_API double gdstk_polygon_perimeter(const GDSTK_Polygon* polygon);

// Point containment
GDSTK_API int gdstk_polygon_contain(const GDSTK_Polygon* polygon, const GDSTK_Vec2* point);
GDSTK_API int gdstk_polygon_contain_all(const GDSTK_Polygon* polygon, const GDSTK_Vec2* points, uint64_t count);
GDSTK_API int gdstk_polygon_contain_any(const GDSTK_Polygon* polygon, const GDSTK_Vec2* points, uint64_t count);

// Bounding box
GDSTK_API void gdstk_polygon_bounding_box(const GDSTK_Polygon* polygon, GDSTK_Vec2* min, GDSTK_Vec2* max);

// Transformations
GDSTK_API void gdstk_polygon_translate(GDSTK_Polygon* polygon, const GDSTK_Vec2* v);
GDSTK_API void gdstk_polygon_scale(GDSTK_Polygon* polygon, const GDSTK_Vec2* scale, const GDSTK_Vec2* center);
GDSTK_API void gdstk_polygon_mirror(GDSTK_Polygon* polygon, const GDSTK_Vec2* p0, const GDSTK_Vec2* p1);
GDSTK_API void gdstk_polygon_rotate(GDSTK_Polygon* polygon, double angle, const GDSTK_Vec2* center);
GDSTK_API void gdstk_polygon_transform(GDSTK_Polygon* polygon, double magnification, int x_reflection, double rotation, const GDSTK_Vec2* origin);

// Advanced operations
GDSTK_API void gdstk_polygon_fillet(GDSTK_Polygon* polygon, const double* radii, uint64_t radii_count, double tolerance);
GDSTK_API void gdstk_polygon_fracture(const GDSTK_Polygon* polygon, uint64_t max_points, double precision, struct GDSTK_Array* result);
GDSTK_API void gdstk_polygon_apply_repetition(GDSTK_Polygon* polygon, struct GDSTK_Array* result);

// Factory functions for creating specific polygon shapes
GDSTK_API GDSTK_Polygon* gdstk_polygon_rectangle(const GDSTK_Vec2* corner1, const GDSTK_Vec2* corner2, int tag);
GDSTK_API GDSTK_Polygon* gdstk_polygon_cross(const GDSTK_Vec2* center, double full_size, double arm_width, int tag);
GDSTK_API GDSTK_Polygon* gdstk_polygon_regular(const GDSTK_Vec2* center, double side_length, uint64_t sides, double rotation, int tag);
GDSTK_API GDSTK_Polygon* gdstk_polygon_ellipse(const GDSTK_Vec2* center, double radius_x, double radius_y, 
                                    double inner_radius_x, double inner_radius_y, 
                                    double initial_angle, double final_angle, 
                                    double tolerance, int tag);
GDSTK_API GDSTK_Polygon* gdstk_polygon_racetrack(const GDSTK_Vec2* center, double straight_length, 
                                      double radius, double inner_radius,
                                      int vertical, double tolerance, int tag);

// Text to polygon conversion
GDSTK_API void gdstk_polygon_text(const char* s, double size, const GDSTK_Vec2* position, 
                       int vertical, int tag, struct GDSTK_Array* result);

// Contour generation
GDSTK_API int gdstk_polygon_contour(const double* data, uint64_t rows, uint64_t cols, 
                         double level, double scaling, struct GDSTK_Array* result);

// Point containment for multiple polygons
GDSTK_API void gdstk_polygon_inside(const GDSTK_Vec2* points, uint64_t point_count,
                         const GDSTK_Polygon** polygons, uint64_t polygon_count,
                         int* result);
GDSTK_API int gdstk_polygon_all_inside(const GDSTK_Vec2* points, uint64_t point_count,
                            const GDSTK_Polygon** polygons, uint64_t polygon_count);
GDSTK_API int gdstk_polygon_any_inside(const GDSTK_Vec2* points, uint64_t point_count,
                            const GDSTK_Polygon** polygons, uint64_t polygon_count);

#ifdef __cplusplus
}
#endif

#endif  // GDSTK_HEADER_POLYGON_C 