#ifndef GDSTK_HEADER_REFERENCE_C
#define GDSTK_HEADER_REFERENCE_C

#include <stdint.h>
#include <stdio.h>
#include "array_c.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct GDSTK_Reference GDSTK_Reference;
typedef struct GDSTK_Cell GDSTK_Cell;
typedef struct GDSTK_RawCell GDSTK_RawCell;
typedef struct GDSTK_Vec2 GDSTK_Vec2;
typedef struct GDSTK_Property GDSTK_Property;
typedef struct GDSTK_Map_GeometryInfo GDSTK_Map_GeometryInfo;

// Reference type enum
typedef enum GDSTK_ReferenceType {
    GDSTK_ReferenceType_Cell = 0,
    GDSTK_ReferenceType_RawCell,
    GDSTK_ReferenceType_Name
} GDSTK_ReferenceType;

// Constructor and destructor
GDSTK_API GDSTK_Reference* gdstk_reference_create_with_cell(GDSTK_Cell* cell);
GDSTK_API GDSTK_Reference* gdstk_reference_create_with_rawcell(GDSTK_RawCell* rawcell);
GDSTK_API GDSTK_Reference* gdstk_reference_create_with_name(const char* name);
GDSTK_API void gdstk_reference_free(GDSTK_Reference* reference);
GDSTK_API void gdstk_reference_clear(GDSTK_Reference* reference);

// Basic properties
GDSTK_API GDSTK_ReferenceType gdstk_reference_get_type(const GDSTK_Reference* reference);
GDSTK_API GDSTK_Cell* gdstk_reference_get_cell(const GDSTK_Reference* reference);
GDSTK_API GDSTK_RawCell* gdstk_reference_get_rawcell(const GDSTK_Reference* reference);
GDSTK_API const char* gdstk_reference_get_name(const GDSTK_Reference* reference);

// Transformation properties
GDSTK_API void gdstk_reference_get_origin(const GDSTK_Reference* reference, GDSTK_Vec2* origin);
GDSTK_API void gdstk_reference_set_origin(GDSTK_Reference* reference, const GDSTK_Vec2* origin);
GDSTK_API double gdstk_reference_get_rotation(const GDSTK_Reference* reference);
GDSTK_API void gdstk_reference_set_rotation(GDSTK_Reference* reference, double rotation);
GDSTK_API double gdstk_reference_get_magnification(const GDSTK_Reference* reference);
GDSTK_API void gdstk_reference_set_magnification(GDSTK_Reference* reference, double magnification);
GDSTK_API int gdstk_reference_get_x_reflection(const GDSTK_Reference* reference);
GDSTK_API void gdstk_reference_set_x_reflection(GDSTK_Reference* reference, int x_reflection);

// Property accessors
GDSTK_API GDSTK_Property* gdstk_reference_get_properties(const GDSTK_Reference* reference);
GDSTK_API void gdstk_reference_set_properties(GDSTK_Reference* reference, GDSTK_Property* properties);

// Copy operations
GDSTK_API void gdstk_reference_copy_from(GDSTK_Reference* dst, const GDSTK_Reference* src);

// Geometry operations
GDSTK_API void gdstk_reference_bounding_box(const GDSTK_Reference* reference, GDSTK_Vec2* min, GDSTK_Vec2* max);
GDSTK_API void gdstk_reference_bounding_box_cached(const GDSTK_Reference* reference, GDSTK_Vec2* min, GDSTK_Vec2* max, 
                                       GDSTK_Map_GeometryInfo* cache);
GDSTK_API void gdstk_reference_convex_hull(const GDSTK_Reference* reference, struct GDSTK_Array* result);
GDSTK_API void gdstk_reference_convex_hull_cached(const GDSTK_Reference* reference, struct GDSTK_Array* result, 
                                      GDSTK_Map_GeometryInfo* cache);

// Transformation operations
GDSTK_API void gdstk_reference_transform(GDSTK_Reference* reference, double magnification, int x_reflection, 
                             double rotation, const GDSTK_Vec2* origin);
GDSTK_API void gdstk_reference_apply_repetition(GDSTK_Reference* reference, struct GDSTK_Array* result);
GDSTK_API void gdstk_reference_repeat_and_transform(const GDSTK_Reference* reference, struct GDSTK_Array* point_array);

// Element retrieval
GDSTK_API void gdstk_reference_get_polygons(const GDSTK_Reference* reference, int apply_repetitions, 
                                 int include_paths, int64_t depth, int filter, int tag, 
                                 struct GDSTK_Array* result);
GDSTK_API void gdstk_reference_get_flexpaths(const GDSTK_Reference* reference, int apply_repetitions, 
                                  int64_t depth, int filter, int tag, 
                                  struct GDSTK_Array* result);
GDSTK_API void gdstk_reference_get_robustpaths(const GDSTK_Reference* reference, int apply_repetitions, 
                                    int64_t depth, int filter, int tag, 
                                    struct GDSTK_Array* result);
GDSTK_API void gdstk_reference_get_labels(const GDSTK_Reference* reference, int apply_repetitions, 
                               int64_t depth, int filter, int tag, 
                               struct GDSTK_Array* result);

// File output
GDSTK_API int gdstk_reference_to_gds(const GDSTK_Reference* reference, FILE* out, double scaling);
GDSTK_API int gdstk_reference_to_svg(const GDSTK_Reference* reference, FILE* out, double scaling, 
                          uint32_t precision);

#ifdef __cplusplus
}
#endif

#endif  // GDSTK_HEADER_REFERENCE_C