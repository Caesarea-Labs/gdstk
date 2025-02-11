#ifndef GDSTK_HEADER_CELL_C
#define GDSTK_HEADER_CELL_C

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "array_c.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct GDSTK_Cell GDSTK_Cell;
typedef struct GDSTK_Vec2 GDSTK_Vec2;
typedef struct GDSTK_Polygon GDSTK_Polygon;
typedef struct GDSTK_Reference GDSTK_Reference;
typedef struct GDSTK_FlexPath GDSTK_FlexPath;
typedef struct GDSTK_RobustPath GDSTK_RobustPath;
typedef struct GDSTK_Label GDSTK_Label;
typedef struct GDSTK_Property GDSTK_Property;
typedef struct GDSTK_Map_Cell GDSTK_Map_Cell;
typedef struct GDSTK_Map_RawCell GDSTK_Map_RawCell;
typedef struct GDSTK_Set_Tag GDSTK_Set_Tag;
typedef struct GDSTK_TagMap GDSTK_TagMap;
typedef struct GDSTK_StyleMap GDSTK_StyleMap;

// Constructor and destructor
GDSTK_API GDSTK_Cell* gdstk_cell_create(const char* name);
GDSTK_API void gdstk_cell_free(GDSTK_Cell* cell);
GDSTK_API void gdstk_cell_clear(GDSTK_Cell* cell);

// Basic properties
GDSTK_API const char* gdstk_cell_get_name(const GDSTK_Cell* cell);
GDSTK_API void gdstk_cell_set_name(GDSTK_Cell* cell, const char* name);

// Array accessors
GDSTK_API uint64_t gdstk_cell_polygon_count(const GDSTK_Cell* cell);
GDSTK_API GDSTK_Polygon* gdstk_cell_get_polygon(const GDSTK_Cell* cell, uint64_t index);
GDSTK_API void gdstk_cell_add_polygon(GDSTK_Cell* cell, GDSTK_Polygon* polygon);

GDSTK_API uint64_t gdstk_cell_reference_count(const GDSTK_Cell* cell);
GDSTK_API GDSTK_Reference* gdstk_cell_get_reference(const GDSTK_Cell* cell, uint64_t index);
GDSTK_API void gdstk_cell_add_reference(GDSTK_Cell* cell, GDSTK_Reference* reference);

GDSTK_API uint64_t gdstk_cell_flexpath_count(const GDSTK_Cell* cell);
GDSTK_API GDSTK_FlexPath* gdstk_cell_get_flexpath(const GDSTK_Cell* cell, uint64_t index);
GDSTK_API void gdstk_cell_add_flexpath(GDSTK_Cell* cell, GDSTK_FlexPath* flexpath);

GDSTK_API uint64_t gdstk_cell_robustpath_count(const GDSTK_Cell* cell);
GDSTK_API GDSTK_RobustPath* gdstk_cell_get_robustpath(const GDSTK_Cell* cell, uint64_t index);
GDSTK_API void gdstk_cell_add_robustpath(GDSTK_Cell* cell, GDSTK_RobustPath* robustpath);

GDSTK_API uint64_t gdstk_cell_label_count(const GDSTK_Cell* cell);
GDSTK_API GDSTK_Label* gdstk_cell_get_label(const GDSTK_Cell* cell, uint64_t index);
GDSTK_API void gdstk_cell_add_label(GDSTK_Cell* cell, GDSTK_Label* label);

// Property accessors
GDSTK_API GDSTK_Property* gdstk_cell_get_properties(const GDSTK_Cell* cell);
GDSTK_API void gdstk_cell_set_properties(GDSTK_Cell* cell, GDSTK_Property* properties);

// Geometry operations
GDSTK_API void gdstk_cell_get_bounding_box(const GDSTK_Cell* cell, GDSTK_Vec2* min, GDSTK_Vec2* max);
GDSTK_API void gdstk_cell_get_convex_hull(const GDSTK_Cell* cell, struct GDSTK_Array* result);

// Copy operations
GDSTK_API void gdstk_cell_copy_from(GDSTK_Cell* dst, const GDSTK_Cell* src, const char* new_name, int deep_copy);

// Element retrieval
GDSTK_API void gdstk_cell_get_polygons(const GDSTK_Cell* cell, int apply_repetitions, int include_paths, 
                            int64_t depth, int filter, int tag, struct GDSTK_Array* result);
GDSTK_API void gdstk_cell_get_flexpaths(const GDSTK_Cell* cell, int apply_repetitions, int64_t depth, 
                             int filter, int tag, struct GDSTK_Array* result);
GDSTK_API void gdstk_cell_get_robustpaths(const GDSTK_Cell* cell, int apply_repetitions, int64_t depth, 
                               int filter, int tag, struct GDSTK_Array* result);
GDSTK_API void gdstk_cell_get_labels(const GDSTK_Cell* cell, int apply_repetitions, int64_t depth, 
                          int filter, int tag, struct GDSTK_Array* result);

// Dependency management
GDSTK_API void gdstk_cell_get_dependencies(const GDSTK_Cell* cell, int recursive, GDSTK_Map_Cell* result);
GDSTK_API void gdstk_cell_get_raw_dependencies(const GDSTK_Cell* cell, int recursive, GDSTK_Map_RawCell* result);

// Tag operations
GDSTK_API void gdstk_cell_get_shape_tags(const GDSTK_Cell* cell, GDSTK_Set_Tag* result);
GDSTK_API void gdstk_cell_get_label_tags(const GDSTK_Cell* cell, GDSTK_Set_Tag* result);
GDSTK_API void gdstk_cell_remap_tags(GDSTK_Cell* cell, const GDSTK_TagMap* map);

// Cell operations
GDSTK_API void gdstk_cell_flatten(GDSTK_Cell* cell, int apply_repetitions, struct GDSTK_Array* removed_references);

// File output
GDSTK_API int gdstk_cell_to_gds(const GDSTK_Cell* cell, FILE* out, double scaling, uint64_t max_points, 
                      double precision, const struct tm* timestamp);
GDSTK_API int gdstk_cell_to_svg(const GDSTK_Cell* cell, FILE* out, double scaling, uint32_t precision, 
                      const char* attributes);
GDSTK_API int gdstk_cell_write_svg(const GDSTK_Cell* cell, const char* filename, double scaling, 
                        uint32_t precision, GDSTK_StyleMap* shape_style, GDSTK_StyleMap* label_style,
                        const char* background, double pad, int pad_as_percentage);

#ifdef __cplusplus
}
#endif

#endif  // GDSTK_HEADER_CELL_C