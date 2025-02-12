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
typedef struct GDSTK_PropertyValue GDSTK_PropertyValue;

// Property value type enum
typedef enum {
    GDSTK_PropertyType_UnsignedInteger = 0,
    GDSTK_PropertyType_Integer = 1,
    GDSTK_PropertyType_Real = 2,
    GDSTK_PropertyType_String = 3
} GDSTK_PropertyType;

// Field getters
GDSTK_API uint64_t gdstk_polygon_get_tag(const GDSTK_Polygon* polygon);
GDSTK_API uint64_t gdstk_polygon_point_array_count(const GDSTK_Polygon* polygon);
GDSTK_API void gdstk_polygon_get_point_array(const GDSTK_Polygon* polygon, GDSTK_Vec2* points, uint64_t count);
GDSTK_API void* gdstk_polygon_get_owner(const GDSTK_Polygon* polygon);

// Repetition getters
GDSTK_API int gdstk_polygon_get_repetition_type(const GDSTK_Polygon* polygon);
GDSTK_API uint64_t gdstk_polygon_get_repetition_columns(const GDSTK_Polygon* polygon);
GDSTK_API uint64_t gdstk_polygon_get_repetition_rows(const GDSTK_Polygon* polygon);
GDSTK_API void gdstk_polygon_get_repetition_spacing(const GDSTK_Polygon* polygon, GDSTK_Vec2* spacing);
GDSTK_API void gdstk_polygon_get_repetition_v1(const GDSTK_Polygon* polygon, GDSTK_Vec2* v1);
GDSTK_API void gdstk_polygon_get_repetition_v2(const GDSTK_Polygon* polygon, GDSTK_Vec2* v2);
GDSTK_API uint64_t gdstk_polygon_get_repetition_offsets_count(const GDSTK_Polygon* polygon);
GDSTK_API void gdstk_polygon_get_repetition_offsets(const GDSTK_Polygon* polygon, GDSTK_Vec2* offsets, uint64_t count);
GDSTK_API uint64_t gdstk_polygon_get_repetition_coords_count(const GDSTK_Polygon* polygon);
GDSTK_API void gdstk_polygon_get_repetition_coords(const GDSTK_Polygon* polygon, double* coords, uint64_t count);
GDSTK_API uint64_t gdstk_polygon_repetition_get_count(const GDSTK_Polygon* polygon);

// Property getters
GDSTK_API GDSTK_PropertyValue* gdstk_polygon_get_property(const GDSTK_Polygon* polygon, const char* name);
GDSTK_API GDSTK_PropertyValue* gdstk_polygon_get_gds_property(const GDSTK_Polygon* polygon, uint16_t attribute);

// Property value getters
GDSTK_API GDSTK_PropertyType gdstk_property_value_get_type(const GDSTK_PropertyValue* property);
GDSTK_API uint64_t gdstk_property_value_get_unsigned_integer(const GDSTK_PropertyValue* property);
GDSTK_API int64_t gdstk_property_value_get_integer(const GDSTK_PropertyValue* property);
GDSTK_API double gdstk_property_value_get_real(const GDSTK_PropertyValue* property);
GDSTK_API uint64_t gdstk_property_value_get_string_length(const GDSTK_PropertyValue* property);
GDSTK_API void gdstk_property_value_get_string(const GDSTK_PropertyValue* property, char* buffer, uint64_t buffer_size);
GDSTK_API GDSTK_PropertyValue* gdstk_property_value_get_next(const GDSTK_PropertyValue* property);
GDSTK_API void gdstk_property_value_free(GDSTK_PropertyValue* property);

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