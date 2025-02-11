#include "cell_c.h"
#include "gdstk/cell.hpp"
#include "gdstk/map.hpp"
#include "gdstk/set.hpp"
#include "gdstk/style.hpp"
#include "gdstk/tagmap.hpp"

using namespace gdstk;

struct GDSTK_Cell {
    Cell cell;
};

struct GDSTK_Map_Cell {
    Map<Cell*> map;
};

struct GDSTK_Map_RawCell {
    Map<RawCell*> map;
};

struct GDSTK_Set_Tag {
    Set<Tag> set;
};

extern "C" {

// Constructor and destructor
GDSTK_Cell* gdstk_cell_create(const char* name) {
    auto* wrapper = new GDSTK_Cell;
    wrapper->cell.init(name);
    return wrapper;
}

void gdstk_cell_free(GDSTK_Cell* cell) {
    if (cell) {
        cell->cell.free_all();
        delete cell;
    }
}

void gdstk_cell_clear(GDSTK_Cell* cell) {
    if (cell) {
        cell->cell.clear();
    }
}

// Basic properties
const char* gdstk_cell_get_name(const GDSTK_Cell* cell) {
    return cell ? cell->cell.name : nullptr;
}

void gdstk_cell_set_name(GDSTK_Cell* cell, const char* name) {
    if (cell) {
        if (cell->cell.name) free_allocation(cell->cell.name);
        cell->cell.name = copy_string(name, nullptr);
    }
}

// Array accessors
uint64_t gdstk_cell_polygon_count(const GDSTK_Cell* cell) {
    return cell ? cell->cell.polygon_array.count : 0;
}

GDSTK_Polygon* gdstk_cell_get_polygon(const GDSTK_Cell* cell, uint64_t index) {
    if (!cell || index >= cell->cell.polygon_array.count) return nullptr;
    return reinterpret_cast<GDSTK_Polygon*>(cell->cell.polygon_array[index]);
}

void gdstk_cell_add_polygon(GDSTK_Cell* cell, GDSTK_Polygon* polygon) {
    if (cell && polygon) {
        cell->cell.polygon_array.append(reinterpret_cast<Polygon*>(polygon));
    }
}

uint64_t gdstk_cell_reference_count(const GDSTK_Cell* cell) {
    return cell ? cell->cell.reference_array.count : 0;
}

GDSTK_Reference* gdstk_cell_get_reference(const GDSTK_Cell* cell, uint64_t index) {
    if (!cell || index >= cell->cell.reference_array.count) return nullptr;
    return reinterpret_cast<GDSTK_Reference*>(cell->cell.reference_array[index]);
}

void gdstk_cell_add_reference(GDSTK_Cell* cell, GDSTK_Reference* reference) {
    if (cell && reference) {
        cell->cell.reference_array.append(reinterpret_cast<Reference*>(reference));
    }
}

uint64_t gdstk_cell_flexpath_count(const GDSTK_Cell* cell) {
    return cell ? cell->cell.flexpath_array.count : 0;
}

GDSTK_FlexPath* gdstk_cell_get_flexpath(const GDSTK_Cell* cell, uint64_t index) {
    if (!cell || index >= cell->cell.flexpath_array.count) return nullptr;
    return reinterpret_cast<GDSTK_FlexPath*>(cell->cell.flexpath_array[index]);
}

void gdstk_cell_add_flexpath(GDSTK_Cell* cell, GDSTK_FlexPath* flexpath) {
    if (cell && flexpath) {
        cell->cell.flexpath_array.append(reinterpret_cast<FlexPath*>(flexpath));
    }
}

uint64_t gdstk_cell_robustpath_count(const GDSTK_Cell* cell) {
    return cell ? cell->cell.robustpath_array.count : 0;
}

GDSTK_RobustPath* gdstk_cell_get_robustpath(const GDSTK_Cell* cell, uint64_t index) {
    if (!cell || index >= cell->cell.robustpath_array.count) return nullptr;
    return reinterpret_cast<GDSTK_RobustPath*>(cell->cell.robustpath_array[index]);
}

void gdstk_cell_add_robustpath(GDSTK_Cell* cell, GDSTK_RobustPath* robustpath) {
    if (cell && robustpath) {
        cell->cell.robustpath_array.append(reinterpret_cast<RobustPath*>(robustpath));
    }
}

uint64_t gdstk_cell_label_count(const GDSTK_Cell* cell) {
    return cell ? cell->cell.label_array.count : 0;
}

GDSTK_Label* gdstk_cell_get_label(const GDSTK_Cell* cell, uint64_t index) {
    if (!cell || index >= cell->cell.label_array.count) return nullptr;
    return reinterpret_cast<GDSTK_Label*>(cell->cell.label_array[index]);
}

void gdstk_cell_add_label(GDSTK_Cell* cell, GDSTK_Label* label) {
    if (cell && label) {
        cell->cell.label_array.append(reinterpret_cast<Label*>(label));
    }
}

// Property accessors
GDSTK_Property* gdstk_cell_get_properties(const GDSTK_Cell* cell) {
    return cell ? reinterpret_cast<GDSTK_Property*>(cell->cell.properties) : nullptr;
}

void gdstk_cell_set_properties(GDSTK_Cell* cell, GDSTK_Property* properties) {
    if (cell) {
        cell->cell.properties = reinterpret_cast<Property*>(properties);
    }
}

// Geometry operations
void gdstk_cell_get_bounding_box(const GDSTK_Cell* cell, GDSTK_Vec2* min, GDSTK_Vec2* max) {
    if (!cell || !min || !max) return;
    Vec2 vmin, vmax;
    cell->cell.bounding_box(vmin, vmax);
    *reinterpret_cast<Vec2*>(min) = vmin;
    *reinterpret_cast<Vec2*>(max) = vmax;
}

void gdstk_cell_get_convex_hull(const GDSTK_Cell* cell, GDSTK_Array* result) {
    if (!cell || !result) return;
    Array<Vec2>& hull = reinterpret_cast<Array<Vec2>&>(*result);
    cell->cell.convex_hull(hull);
}

// Copy operations
void gdstk_cell_copy_from(GDSTK_Cell* dst, const GDSTK_Cell* src, const char* new_name, int deep_copy) {
    if (!dst || !src) return;
    dst->cell.copy_from(src->cell, new_name, deep_copy != 0);
}

// Element retrieval
void gdstk_cell_get_polygons(const GDSTK_Cell* cell, int apply_repetitions, int include_paths,
                            int64_t depth, int filter, int tag, GDSTK_Array* result) {
    if (!cell || !result) return;
    Array<Polygon*>& poly_array = reinterpret_cast<Array<Polygon*>&>(*result);
    cell->cell.get_polygons(apply_repetitions != 0, include_paths != 0, depth, filter != 0, tag, poly_array);
}

void gdstk_cell_get_flexpaths(const GDSTK_Cell* cell, int apply_repetitions, int64_t depth,
                             int filter, int tag, GDSTK_Array* result) {
    if (!cell || !result) return;
    Array<FlexPath*>& path_array = reinterpret_cast<Array<FlexPath*>&>(*result);
    cell->cell.get_flexpaths(apply_repetitions != 0, depth, filter != 0, tag, path_array);
}

void gdstk_cell_get_robustpaths(const GDSTK_Cell* cell, int apply_repetitions, int64_t depth,
                               int filter, int tag, GDSTK_Array* result) {
    if (!cell || !result) return;
    Array<RobustPath*>& path_array = reinterpret_cast<Array<RobustPath*>&>(*result);
    cell->cell.get_robustpaths(apply_repetitions != 0, depth, filter != 0, tag, path_array);
}

void gdstk_cell_get_labels(const GDSTK_Cell* cell, int apply_repetitions, int64_t depth,
                          int filter, int tag, GDSTK_Array* result) {
    if (!cell || !result) return;
    Array<Label*>& label_array = reinterpret_cast<Array<Label*>&>(*result);
    cell->cell.get_labels(apply_repetitions != 0, depth, filter != 0, tag, label_array);
}

// Dependency management
void gdstk_cell_get_dependencies(const GDSTK_Cell* cell, int recursive, GDSTK_Map_Cell* result) {
    if (!cell || !result) return;
    Map<Cell*>& cell_map = reinterpret_cast<Map<Cell*>&>(result->map);
    cell->cell.get_dependencies(recursive != 0, cell_map);
}

void gdstk_cell_get_raw_dependencies(const GDSTK_Cell* cell, int recursive, GDSTK_Map_RawCell* result) {
    if (!cell || !result) return;
    Map<RawCell*>& raw_map = reinterpret_cast<Map<RawCell*>&>(result->map);
    cell->cell.get_raw_dependencies(recursive != 0, raw_map);
}

// Tag operations
void gdstk_cell_get_shape_tags(const GDSTK_Cell* cell, GDSTK_Set_Tag* result) {
    if (!cell || !result) return;
    Set<Tag>& tag_set = reinterpret_cast<Set<Tag>&>(result->set);
    cell->cell.get_shape_tags(tag_set);
}

void gdstk_cell_get_label_tags(const GDSTK_Cell* cell, GDSTK_Set_Tag* result) {
    if (!cell || !result) return;
    Set<Tag>& tag_set = reinterpret_cast<Set<Tag>&>(result->set);
    cell->cell.get_label_tags(tag_set);
}

void gdstk_cell_remap_tags(GDSTK_Cell* cell, const GDSTK_TagMap* map) {
    if (!cell || !map) return;
    const TagMap& tag_map = reinterpret_cast<const TagMap&>(*map);
    cell->cell.remap_tags(tag_map);
}

// Cell operations
void gdstk_cell_flatten(GDSTK_Cell* cell, int apply_repetitions, GDSTK_Array* removed_references) {
    if (!cell || !removed_references) return;
    Array<Reference*>& ref_array = reinterpret_cast<Array<Reference*>&>(*removed_references);
    cell->cell.flatten(apply_repetitions != 0, ref_array);
}

// File output
int gdstk_cell_to_gds(const GDSTK_Cell* cell, FILE* out, double scaling, uint64_t max_points,
                      double precision, const struct tm* timestamp) {
    if (!cell || !out) return -1;
    return static_cast<int>(cell->cell.to_gds(out, scaling, max_points, precision, timestamp));
}

int gdstk_cell_to_svg(const GDSTK_Cell* cell, FILE* out, double scaling, uint32_t precision,
                      const char* attributes) {
    if (!cell || !out) return -1;
    return static_cast<int>(cell->cell.to_svg(out, scaling, precision, attributes, nullptr));
}

int gdstk_cell_write_svg(const GDSTK_Cell* cell, const char* filename, double scaling,
                        uint32_t precision, GDSTK_StyleMap* shape_style, GDSTK_StyleMap* label_style,
                        const char* background, double pad, int pad_as_percentage) {
    if (!cell || !filename) return -1;
    StyleMap* shape = reinterpret_cast<StyleMap*>(shape_style);
    StyleMap* label = reinterpret_cast<StyleMap*>(label_style);
    return static_cast<int>(cell->cell.write_svg(filename, scaling, precision, shape, label,
                                                background, pad, pad_as_percentage != 0, nullptr));
}

} // extern "C" 