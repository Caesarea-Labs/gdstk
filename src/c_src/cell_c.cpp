#include "cell_c.h"

#include "array_c.h"
#include "gdstk/array.hpp"
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
    if (!name) {
        fprintf(stderr, "Warning: gdstk_cell_create received null name parameter\n");
    }
    auto* wrapper = new GDSTK_Cell;
    wrapper->cell.init(name);
    return wrapper;
}

void gdstk_cell_free(GDSTK_Cell* cell) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_free received null cell parameter\n");
        return;
    }
    cell->cell.free_all();
    delete cell;
}

void gdstk_cell_clear(GDSTK_Cell* cell) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_clear received null cell parameter\n");
        return;
    }
    cell->cell.clear();
}

// Basic properties
const char* gdstk_cell_get_name(const GDSTK_Cell* cell) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_name received null cell parameter\n");
    }
    return cell ? cell->cell.name : nullptr;
}

void gdstk_cell_set_name(GDSTK_Cell* cell, const char* name) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_set_name received null cell parameter\n");
        return;
    }
    if (!name) {
        fprintf(stderr, "Warning: gdstk_cell_set_name received null name parameter\n");
        return;
    }
    if (cell->cell.name) free_allocation(cell->cell.name);
    cell->cell.name = copy_string(name, nullptr);
}

// Array accessors
// uint64_t gdstk_cell_polygon_count(const GDSTK_Cell* cell) {
//     if (!cell) {
//         fprintf(stderr, "Warning: gdstk_cell_polygon_count received null cell parameter\n");
//     }
//     return cell ? cell->cell.polygon_array.count : 0;
// }
//
// GDSTK_Polygon* gdstk_cell_get_polygon(const GDSTK_Cell* cell, uint64_t index) {
//     if (!cell) {
//         fprintf(stderr, "Warning: gdstk_cell_get_polygon received null cell parameter\n");
//         return nullptr;
//     }
//     if (index >= cell->cell.polygon_array.count) {
//         fprintf(stderr, "Warning: gdstk_cell_get_polygon index out of bounds\n");
//         return nullptr;
//     }
//     return reinterpret_cast<GDSTK_Polygon*>(cell->cell.polygon_array[index]);
// }
//
// void gdstk_cell_add_polygon(GDSTK_Cell* cell, GDSTK_Polygon* polygon) {
//     if (!cell) {
//         fprintf(stderr, "Warning: gdstk_cell_add_polygon received null cell parameter\n");
//         return;
//     }
//     if (!polygon) {
//         fprintf(stderr, "Warning: gdstk_cell_add_polygon received null polygon parameter\n");
//         return;
//     }
//     cell->cell.polygon_array.append(reinterpret_cast<Polygon*>(polygon));
// }
// GDSTK_Array gdstk_cell_get_polygons(const GDSTK_Cell* cell, int8_t apply_repetitions, int8_t include_paths, int64_t depth, int8_t filter, ) {
//     if (!cell) {
//         fprintf(stderr, "Warning: gdstk_cell_get_references received null cell parameter\n");
//         constexpr GDSTK_Array array = {nullptr};
//         return array;
//     }
//
//     cell->cell.get_polygons()
//
//     const GDSTK_Array array = {const_cast<Array<Polygon*>*>(&cell->cell.polygon_array)};
//     return array;
// }

// bool apply_repetitions, bool include_paths, ,
// Tag tag, Array<Polygon*>&result 
GDSTK_Array gdstk_cell_get_references(const GDSTK_Cell* cell) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_references received null cell parameter\n");
        constexpr GDSTK_Array array = {nullptr};
        return array;
    }

    const GDSTK_Array array = {const_cast<Array<Reference*>*>(&cell->cell.reference_array)};
    return array;
}

// uint64_t gdstk_cell_reference_count(const GDSTK_Cell* cell) {
//     if (!cell) {
//         fprintf(stderr, "Warning: gdstk_cell_reference_count received null cell parameter\n");
//     }
//     return cell ? cell->cell.reference_array.count : 0;
// }
//
// GDSTK_Reference* gdstk_cell_get_reference(const GDSTK_Cell* cell, uint64_t index) {
//     if (!cell) {
//         fprintf(stderr, "Warning: gdstk_cell_get_reference received null cell parameter\n");
//         return nullptr;
//     }
//     if (index >= cell->cell.reference_array.count) {
//         fprintf(stderr, "Warning: gdstk_cell_get_reference index out of bounds\n");
//         return nullptr;
//     }
//     return reinterpret_cast<GDSTK_Reference*>(cell->cell.reference_array[index]);
// }
//
// void gdstk_cell_add_reference(GDSTK_Cell* cell, GDSTK_Reference* reference) {
//     if (!cell) {
//         fprintf(stderr, "Warning: gdstk_cell_add_reference received null cell parameter\n");
//         return;
//     }
//     if (!reference) {
//         fprintf(stderr, "Warning: gdstk_cell_add_reference received null reference parameter\n");
//         return;
//     }
//     cell->cell.reference_array.append(reinterpret_cast<Reference*>(reference));
// }

uint64_t gdstk_cell_flexpath_count(const GDSTK_Cell* cell) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_flexpath_count received null cell parameter\n");
    }
    return cell ? cell->cell.flexpath_array.count : 0;
}

GDSTK_FlexPath* gdstk_cell_get_flexpath(const GDSTK_Cell* cell, uint64_t index) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_flexpath received null cell parameter\n");
        return nullptr;
    }
    if (index >= cell->cell.flexpath_array.count) {
        fprintf(stderr, "Warning: gdstk_cell_get_flexpath index out of bounds\n");
        return nullptr;
    }
    return reinterpret_cast<GDSTK_FlexPath*>(cell->cell.flexpath_array[index]);
}

void gdstk_cell_add_flexpath(GDSTK_Cell* cell, GDSTK_FlexPath* flexpath) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_add_flexpath received null cell parameter\n");
        return;
    }
    if (!flexpath) {
        fprintf(stderr, "Warning: gdstk_cell_add_flexpath received null flexpath parameter\n");
        return;
    }
    cell->cell.flexpath_array.append(reinterpret_cast<FlexPath*>(flexpath));
}

uint64_t gdstk_cell_robustpath_count(const GDSTK_Cell* cell) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_robustpath_count received null cell parameter\n");
    }
    return cell ? cell->cell.robustpath_array.count : 0;
}

GDSTK_RobustPath* gdstk_cell_get_robustpath(const GDSTK_Cell* cell, uint64_t index) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_robustpath received null cell parameter\n");
        return nullptr;
    }
    if (index >= cell->cell.robustpath_array.count) {
        fprintf(stderr, "Warning: gdstk_cell_get_robustpath index out of bounds\n");
        return nullptr;
    }
    return reinterpret_cast<GDSTK_RobustPath*>(cell->cell.robustpath_array[index]);
}

void gdstk_cell_add_robustpath(GDSTK_Cell* cell, GDSTK_RobustPath* robustpath) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_add_robustpath received null cell parameter\n");
        return;
    }
    if (!robustpath) {
        fprintf(stderr, "Warning: gdstk_cell_add_robustpath received null robustpath parameter\n");
        return;
    }
    cell->cell.robustpath_array.append(reinterpret_cast<RobustPath*>(robustpath));
}

uint64_t gdstk_cell_label_count(const GDSTK_Cell* cell) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_label_count received null cell parameter\n");
    }
    return cell ? cell->cell.label_array.count : 0;
}

GDSTK_Label* gdstk_cell_get_label(const GDSTK_Cell* cell, uint64_t index) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_label received null cell parameter\n");
        return nullptr;
    }
    if (index >= cell->cell.label_array.count) {
        fprintf(stderr, "Warning: gdstk_cell_get_label index out of bounds\n");
        return nullptr;
    }
    return reinterpret_cast<GDSTK_Label*>(cell->cell.label_array[index]);
}

void gdstk_cell_add_label(GDSTK_Cell* cell, GDSTK_Label* label) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_add_label received null cell parameter\n");
        return;
    }
    if (!label) {
        fprintf(stderr, "Warning: gdstk_cell_add_label received null label parameter\n");
        return;
    }
    cell->cell.label_array.append(reinterpret_cast<Label*>(label));
}

// Property accessors
GDSTK_Property* gdstk_cell_get_properties(const GDSTK_Cell* cell) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_properties received null cell parameter\n");
    }
    return cell ? reinterpret_cast<GDSTK_Property*>(cell->cell.properties) : nullptr;
}

void gdstk_cell_set_properties(GDSTK_Cell* cell, GDSTK_Property* properties) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_set_properties received null cell parameter\n");
        return;
    }
    cell->cell.properties = reinterpret_cast<Property*>(properties);
}

// Geometry operations
void gdstk_cell_get_bounding_box(const GDSTK_Cell* cell, GDSTK_Vec2* min, GDSTK_Vec2* max) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_bounding_box received null cell parameter\n");
        return;
    }
    if (!min || !max) {
        fprintf(stderr, "Warning: gdstk_cell_get_bounding_box received null min/max parameter\n");
        return;
    }
    Vec2 vmin, vmax;
    cell->cell.bounding_box(vmin, vmax);
    *reinterpret_cast<Vec2*>(min) = vmin;
    *reinterpret_cast<Vec2*>(max) = vmax;
}

void gdstk_cell_get_convex_hull(const GDSTK_Cell* cell, GDSTK_Array result) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_convex_hull received null cell parameter\n");
        return;
    }
    if (!result.array) {
        fprintf(stderr, "Warning: gdstk_cell_get_convex_hull received null result parameter\n");
        return;
    }
    cell->cell.convex_hull(*reinterpret_cast<Array<Vec2>*>(result.array));
}

// Copy operations
void gdstk_cell_copy_from(GDSTK_Cell* dst, const GDSTK_Cell* src, const char* new_name,
                          int deep_copy) {
    if (!dst) {
        fprintf(stderr, "Warning: gdstk_cell_copy_from received null destination parameter\n");
        return;
    }
    if (!src) {
        fprintf(stderr, "Warning: gdstk_cell_copy_from received null source parameter\n");
        return;
    }
    dst->cell.copy_from(src->cell, new_name, deep_copy != 0);
}

// Element retrieval
void gdstk_cell_get_polygons(const GDSTK_Cell* cell, int apply_repetitions, int include_paths,
                             int64_t depth, int filter, Tag tag, GDSTK_Array result) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_polygons received null cell parameter\n");
        return;
    }
    if (!result.array) {
        fprintf(stderr, "Warning: gdstk_cell_get_polygons received null result parameter\n");
        return;
    }
    cell->cell.get_polygons(apply_repetitions != 0, include_paths != 0, depth, filter != 0, tag,
                            *static_cast<Array<Polygon*>*>(result.array));
}

void gdstk_cell_get_flexpaths(const GDSTK_Cell* cell, int apply_repetitions, int64_t depth,
                              int filter, Tag tag, GDSTK_Array result) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_flexpaths received null cell parameter\n");
        return;
    }
    if (!result.array) {
        fprintf(stderr, "Warning: gdstk_cell_get_flexpaths received null result parameter\n");
        return;
    }
    cell->cell.get_flexpaths(apply_repetitions != 0, depth, filter != 0, tag,
                             *reinterpret_cast<Array<FlexPath*>*>(result.array));
}

void gdstk_cell_get_robustpaths(const GDSTK_Cell* cell, int apply_repetitions, int64_t depth,
                                int filter, Tag tag, GDSTK_Array result) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_robustpaths received null cell parameter\n");
        return;
    }
    if (!result.array) {
        fprintf(stderr, "Warning: gdstk_cell_get_robustpaths received null result parameter\n");
        return;
    }
    cell->cell.get_robustpaths(apply_repetitions != 0, depth, filter != 0, tag,
                               *reinterpret_cast<Array<RobustPath*>*>(result.array));
}

void gdstk_cell_get_labels(const GDSTK_Cell* cell, int apply_repetitions, int64_t depth, int filter,
                           Tag tag, GDSTK_Array result) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_labels received null cell parameter\n");
        return;
    }
    if (!result.array) {
        fprintf(stderr, "Warning: gdstk_cell_get_labels received null result parameter\n");
        return;
    }
    cell->cell.get_labels(apply_repetitions != 0, depth, filter != 0, tag,
                          *reinterpret_cast<Array<Label*>*>(result.array));
}

// Dependency management
void gdstk_cell_get_dependencies(const GDSTK_Cell* cell, int recursive, GDSTK_Map_Cell* result) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_dependencies received null cell parameter\n");
        return;
    }
    if (!result) {
        fprintf(stderr, "Warning: gdstk_cell_get_dependencies received null result parameter\n");
        return;
    }
    Map<Cell*>& cell_map = reinterpret_cast<Map<Cell*>&>(result->map);
    cell->cell.get_dependencies(recursive != 0, cell_map);
}

void gdstk_cell_get_raw_dependencies(const GDSTK_Cell* cell, int recursive,
                                     GDSTK_Map_RawCell* result) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_raw_dependencies received null cell parameter\n");
        return;
    }
    if (!result) {
        fprintf(stderr,
                "Warning: gdstk_cell_get_raw_dependencies received null result parameter\n");
        return;
    }
    Map<RawCell*>& raw_map = reinterpret_cast<Map<RawCell*>&>(result->map);
    cell->cell.get_raw_dependencies(recursive != 0, raw_map);
}

// Tag operations
void gdstk_cell_get_shape_tags(const GDSTK_Cell* cell, GDSTK_Set_Tag* result) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_shape_tags received null cell parameter\n");
        return;
    }
    if (!result) {
        fprintf(stderr, "Warning: gdstk_cell_get_shape_tags received null result parameter\n");
        return;
    }
    Set<Tag>& tag_set = reinterpret_cast<Set<Tag>&>(result->set);
    cell->cell.get_shape_tags(tag_set);
}

void gdstk_cell_get_label_tags(const GDSTK_Cell* cell, GDSTK_Set_Tag* result) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_get_label_tags received null cell parameter\n");
        return;
    }
    if (!result) {
        fprintf(stderr, "Warning: gdstk_cell_get_label_tags received null result parameter\n");
        return;
    }
    Set<Tag>& tag_set = reinterpret_cast<Set<Tag>&>(result->set);
    cell->cell.get_label_tags(tag_set);
}

void gdstk_cell_remap_tags(GDSTK_Cell* cell, const GDSTK_TagMap* map) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_remap_tags received null cell parameter\n");
        return;
    }
    if (!map) {
        fprintf(stderr, "Warning: gdstk_cell_remap_tags received null map parameter\n");
        return;
    }
    const TagMap& tag_map = reinterpret_cast<const TagMap&>(*map);
    cell->cell.remap_tags(tag_map);
}

// Cell operations
void gdstk_cell_flatten(GDSTK_Cell* cell, int apply_repetitions, GDSTK_Array removed_references) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_flatten received null cell parameter\n");
        return;
    }
    if (!removed_references.array) {
        fprintf(stderr, "Warning: gdstk_cell_flatten received null removed_references parameter\n");
        return;
    }
    cell->cell.flatten(apply_repetitions != 0,
                       *reinterpret_cast<Array<Reference*>*>(removed_references.array));
}

// File output
int gdstk_cell_to_gds(const GDSTK_Cell* cell, FILE* out, double scaling, uint64_t max_points,
                      double precision, const struct tm* timestamp) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_to_gds received null cell parameter\n");
        return -1;
    }
    if (!out) {
        fprintf(stderr, "Warning: gdstk_cell_to_gds received null output file parameter\n");
        return -1;
    }
    return static_cast<int>(cell->cell.to_gds(out, scaling, max_points, precision, timestamp));
}

int gdstk_cell_to_svg(const GDSTK_Cell* cell, FILE* out, double scaling, uint32_t precision,
                      const char* attributes) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_to_svg received null cell parameter\n");
        return -1;
    }
    if (!out) {
        fprintf(stderr, "Warning: gdstk_cell_to_svg received null output file parameter\n");
        return -1;
    }
    return static_cast<int>(cell->cell.to_svg(out, scaling, precision, attributes, nullptr));
}

int gdstk_cell_write_svg(const GDSTK_Cell* cell, const char* filename, double scaling,
                         uint32_t precision, GDSTK_StyleMap* shape_style,
                         GDSTK_StyleMap* label_style, const char* background, double pad,
                         int pad_as_percentage) {
    if (!cell) {
        fprintf(stderr, "Warning: gdstk_cell_write_svg received null cell parameter\n");
        return -1;
    }
    if (!filename) {
        fprintf(stderr, "Warning: gdstk_cell_write_svg received null filename parameter\n");
        return -1;
    }
    StyleMap* shape = reinterpret_cast<StyleMap*>(shape_style);
    StyleMap* label = reinterpret_cast<StyleMap*>(label_style);
    return static_cast<int>(cell->cell.write_svg(filename, scaling, precision, shape, label,
                                                 background, pad, pad_as_percentage != 0, nullptr));
}

}  // extern "C"