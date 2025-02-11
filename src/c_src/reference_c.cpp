#include "reference_c.h"
#include "gdstk/reference.hpp"
#include "gdstk/cell.hpp"
#include "gdstk/rawcell.hpp"
#include "gdstk/map.hpp"
#include "gdstk/property.hpp"
#include "gdstk/utils.hpp"
#include "gdstk/array.hpp"
#include <string>

using namespace gdstk;

struct GDSTK_Vec2 {
    double x;
    double y;
};

struct GDSTK_Reference {
    Reference reference;
};

struct GDSTK_Polygon {
    Polygon polygon;
};

struct GDSTK_FlexPath {
    FlexPath flexpath;
};

struct GDSTK_RobustPath {
    RobustPath robustpath;
};

struct GDSTK_Label {
    Label label;
};

struct GDSTK_Map_GeometryInfo {
    Map<GeometryInfo> map;
};

extern "C" {

// Constructor and destructor
GDSTK_Reference* gdstk_reference_create_with_cell(GDSTK_Cell* cell) {
    if (!cell) return nullptr;
    auto* wrapper = new GDSTK_Reference;
    wrapper->reference.type = ReferenceType::Cell;
    wrapper->reference.cell = reinterpret_cast<Cell*>(cell);
    return wrapper;
}

GDSTK_Reference* gdstk_reference_create_with_rawcell(GDSTK_RawCell* rawcell) {
    if (!rawcell) return nullptr;
    auto* wrapper = new GDSTK_Reference;
    wrapper->reference.type = ReferenceType::RawCell;
    wrapper->reference.rawcell = reinterpret_cast<RawCell*>(rawcell);
    return wrapper;
}

GDSTK_Reference* gdstk_reference_create_with_name(const char* name) {
    if (!name) return nullptr;
    auto* wrapper = new GDSTK_Reference;
    wrapper->reference.type = ReferenceType::Name;
    wrapper->reference.name = copy_string(name, nullptr);
    return wrapper;
}

void gdstk_reference_free(GDSTK_Reference* reference) {
    if (reference) {
        if (reference->reference.type == ReferenceType::Name) {
            free_allocation(reference->reference.name);
        }
        delete reference;
    }
}

void gdstk_reference_clear(GDSTK_Reference* reference) {
    if (reference) {
        reference->reference.clear();
    }
}

// Basic properties
GDSTK_ReferenceType gdstk_reference_get_type(const GDSTK_Reference* reference) {
    if (!reference) return GDSTK_ReferenceType_Cell;
    switch (reference->reference.type) {
        case ReferenceType::Cell:
            return GDSTK_ReferenceType_Cell;
        case ReferenceType::RawCell:
            return GDSTK_ReferenceType_RawCell;
        case ReferenceType::Name:
            return GDSTK_ReferenceType_Name;
        default:
            return GDSTK_ReferenceType_Cell;
    }
}

GDSTK_Cell* gdstk_reference_get_cell(const GDSTK_Reference* reference) {
    if (!reference || reference->reference.type != ReferenceType::Cell) return nullptr;
    return reinterpret_cast<GDSTK_Cell*>(reference->reference.cell);
}

GDSTK_RawCell* gdstk_reference_get_rawcell(const GDSTK_Reference* reference) {
    if (!reference || reference->reference.type != ReferenceType::RawCell) return nullptr;
    return reinterpret_cast<GDSTK_RawCell*>(reference->reference.rawcell);
}

const char* gdstk_reference_get_name(const GDSTK_Reference* reference) {
    if (!reference || reference->reference.type != ReferenceType::Name) return nullptr;
    return reference->reference.name;
}

// Transformation properties
void gdstk_reference_get_origin(const GDSTK_Reference* reference, GDSTK_Vec2* origin) {
    if (!reference || !origin) return;
    origin->x = reference->reference.origin.x;
    origin->y = reference->reference.origin.y;
}

void gdstk_reference_set_origin(GDSTK_Reference* reference, const GDSTK_Vec2* origin) {
    if (!reference || !origin) return;
    reference->reference.origin.x = origin->x;
    reference->reference.origin.y = origin->y;
}

double gdstk_reference_get_rotation(const GDSTK_Reference* reference) {
    return reference ? reference->reference.rotation : 0.0;
}

void gdstk_reference_set_rotation(GDSTK_Reference* reference, double rotation) {
    if (reference) {
        reference->reference.rotation = rotation;
    }
}

double gdstk_reference_get_magnification(const GDSTK_Reference* reference) {
    return reference ? reference->reference.magnification : 1.0;
}

void gdstk_reference_set_magnification(GDSTK_Reference* reference, double magnification) {
    if (reference) {
        reference->reference.magnification = magnification;
    }
}

int gdstk_reference_get_x_reflection(const GDSTK_Reference* reference) {
    return reference ? (reference->reference.x_reflection ? 1 : 0) : 0;
}

void gdstk_reference_set_x_reflection(GDSTK_Reference* reference, int x_reflection) {
    if (reference) {
        reference->reference.x_reflection = x_reflection != 0;
    }
}

// Property accessors
GDSTK_Property* gdstk_reference_get_properties(const GDSTK_Reference* reference) {
    return reference ? reinterpret_cast<GDSTK_Property*>(reference->reference.properties) : nullptr;
}

void gdstk_reference_set_properties(GDSTK_Reference* reference, GDSTK_Property* properties) {
    if (reference) {
        reference->reference.properties = reinterpret_cast<Property*>(properties);
    }
}

// Copy operations
void gdstk_reference_copy_from(GDSTK_Reference* dst, const GDSTK_Reference* src) {
    if (!dst || !src) return;
    dst->reference.copy_from(src->reference);
}

// Geometry operations
void gdstk_reference_bounding_box(const GDSTK_Reference* reference, GDSTK_Vec2* min, GDSTK_Vec2* max) {
    if (!reference || !min || !max) return;
    Vec2 vmin, vmax;
    reference->reference.bounding_box(vmin, vmax);
    min->x = vmin.x;
    min->y = vmin.y;
    max->x = vmax.x;
    max->y = vmax.y;
}

void gdstk_reference_bounding_box_cached(const GDSTK_Reference* reference, GDSTK_Vec2* min, GDSTK_Vec2* max,
                                       GDSTK_Map_GeometryInfo* cache) {
    if (!reference || !min || !max || !cache) return;
    Vec2 vmin, vmax;
    reference->reference.bounding_box(vmin, vmax, cache->map);
    min->x = vmin.x;
    min->y = vmin.y;
    max->x = vmax.x;
    max->y = vmax.y;
}

void gdstk_reference_convex_hull(const GDSTK_Reference* reference, struct GDSTK_Array* result) {
    if (!reference || !result) return;
    Array<Vec2> temp_array;
    reference->reference.convex_hull(temp_array);
    
    // Convert temp_array to GDSTK_Array
    for (uint64_t i = 0; i < temp_array.count; i++) {
        GDSTK_Vec2 vec = {temp_array[i].x, temp_array[i].y};
        gdstk_array_append(result, &vec);
    }
}

void gdstk_reference_convex_hull_cached(const GDSTK_Reference* reference, struct GDSTK_Array* result,
                                      GDSTK_Map_GeometryInfo* cache) {
    if (!reference || !result || !cache) return;
    Array<Vec2> temp_array;
    reference->reference.convex_hull(temp_array, cache->map);
    
    // Convert temp_array to GDSTK_Array
    for (uint64_t i = 0; i < temp_array.count; i++) {
        GDSTK_Vec2 vec = {temp_array[i].x, temp_array[i].y};
        gdstk_array_append(result, &vec);
    }
}

// Transformation operations
void gdstk_reference_transform(GDSTK_Reference* reference, double magnification, int x_reflection,
                             double rotation, const GDSTK_Vec2* origin) {
    if (!reference || !origin) return;
    reference->reference.transform(magnification, x_reflection != 0, rotation, {origin->x, origin->y});
}

void gdstk_reference_apply_repetition(GDSTK_Reference* reference, struct GDSTK_Array* result) {
    if (!reference || !result) return;
    Array<Reference*> temp_array;
    reference->reference.apply_repetition(temp_array);
    
    // Convert temp_array to GDSTK_Array
    for (uint64_t i = 0; i < temp_array.count; i++) {
        auto* ref_wrapper = new GDSTK_Reference;
        ref_wrapper->reference = *temp_array[i];
        gdstk_array_append(result, &ref_wrapper);
        delete temp_array[i];
    }
}

void gdstk_reference_repeat_and_transform(const GDSTK_Reference* reference, struct GDSTK_Array* point_array) {
    if (!reference || !point_array) return;
    Array<Vec2> temp_array;
    reference->reference.repeat_and_transform(temp_array);
    
    // Convert temp_array to GDSTK_Array
    for (uint64_t i = 0; i < temp_array.count; i++) {
        GDSTK_Vec2 vec = {temp_array[i].x, temp_array[i].y};
        gdstk_array_append(point_array, &vec);
    }
}

// Element retrieval
void gdstk_reference_get_polygons(const GDSTK_Reference* reference, int apply_repetitions,
                                 int include_paths, int64_t depth, int filter, int tag,
                                 struct GDSTK_Array* result) {
    if (!reference || !result) return;
    Array<Polygon*> temp_array;
    reference->reference.get_polygons(apply_repetitions != 0, include_paths != 0, depth,
                                    filter != 0, tag, temp_array);
    
    // Convert temp_array to GDSTK_Array
    for (uint64_t i = 0; i < temp_array.count; i++) {
        auto* poly_wrapper = new GDSTK_Polygon;
        poly_wrapper->polygon = *temp_array[i];
        gdstk_array_append(result, &poly_wrapper);
        delete temp_array[i];
    }
}

void gdstk_reference_get_flexpaths(const GDSTK_Reference* reference, int apply_repetitions,
                                  int64_t depth, int filter, int tag,
                                  struct GDSTK_Array* result) {
    if (!reference || !result) return;
    Array<FlexPath*> temp_array;
    reference->reference.get_flexpaths(apply_repetitions != 0, depth, filter != 0, tag, temp_array);
    
    // Convert temp_array to GDSTK_Array
    for (uint64_t i = 0; i < temp_array.count; i++) {
        auto* path_wrapper = new GDSTK_FlexPath;
        path_wrapper->flexpath = *temp_array[i];
        gdstk_array_append(result, &path_wrapper);
        delete temp_array[i];
    }
}

void gdstk_reference_get_robustpaths(const GDSTK_Reference* reference, int apply_repetitions,
                                    int64_t depth, int filter, int tag,
                                    struct GDSTK_Array* result) {
    if (!reference || !result) return;
    Array<RobustPath*> temp_array;
    reference->reference.get_robustpaths(apply_repetitions != 0, depth, filter != 0, tag, temp_array);
    
    // Convert temp_array to GDSTK_Array
    for (uint64_t i = 0; i < temp_array.count; i++) {
        auto* path_wrapper = new GDSTK_RobustPath;
        path_wrapper->robustpath = *temp_array[i];
        gdstk_array_append(result, &path_wrapper);
        delete temp_array[i];
    }
}

void gdstk_reference_get_labels(const GDSTK_Reference* reference, int apply_repetitions,
                               int64_t depth, int filter, int tag,
                               struct GDSTK_Array* result) {
    if (!reference || !result) return;
    Array<Label*> temp_array;
    reference->reference.get_labels(apply_repetitions != 0, depth, filter != 0, tag, temp_array);
    
    // Convert temp_array to GDSTK_Array
    for (uint64_t i = 0; i < temp_array.count; i++) {
        auto* label_wrapper = new GDSTK_Label;
        label_wrapper->label = *temp_array[i];
        gdstk_array_append(result, &label_wrapper);
        delete temp_array[i];
    }
}

// File output
int gdstk_reference_to_gds(const GDSTK_Reference* reference, FILE* out, double scaling) {
    if (!reference || !out) return -1;
    ErrorCode result = reference->reference.to_gds(out, scaling);
    return result == ErrorCode::NoError ? 0 : -1;
}

int gdstk_reference_to_svg(const GDSTK_Reference* reference, FILE* out, double scaling,
                          uint32_t precision) {
    if (!reference || !out) return -1;
    ErrorCode result = reference->reference.to_svg(out, scaling, precision);
    return result == ErrorCode::NoError ? 0 : -1;
}

} // extern "C" 