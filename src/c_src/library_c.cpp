// gdstk_c.cpp
#include "library_c.h"
#include "gdstk/library.hpp"
#include "gdstk/array.hpp"
#include "gdstk/tagmap.hpp"
#include "gdstk/utils.hpp"
#include "gdstk/cell.hpp"
#include "gdstk/rawcell.hpp"
#include "gdstk/property.hpp"
#include "gdstk/set.hpp"

using namespace gdstk;

// Internal wrapper structures
struct GDSTK_Array {
    gdstk::Array<void*>* array;
};

struct GDSTK_Library {
    Library lib;
};

struct GDSTK_LibraryInfo {
    LibraryInfo info;
};

struct GDSTK_Cell {
    Cell cell;
};

struct GDSTK_RawCell {
    RawCell rawcell;
};

struct GDSTK_Property {
    Property property;
};

struct GDSTK_TagSet {
    Set<Tag> set;
};

struct GDSTK_TagMap {
    TagMap map;
};

using namespace gdstk;

extern "C" {

// Library implementation
GDSTK_Library* gdstk_library_create(const char* name, double unit, double precision) {
    auto* wrapper = new GDSTK_Library;
    wrapper->lib.init(name, unit, precision);
    return wrapper;
}

void gdstk_library_free(GDSTK_Library* library) {
    if (library) {
        library->lib.free_all();
        delete library;
    }
}

void gdstk_library_clear(GDSTK_Library* library) {
    if (library) library->lib.clear();
}

void gdstk_library_free_all(GDSTK_Library* library) {
    if (library) library->lib.free_all();
}

GDSTK_Cell* gdstk_library_get_cell(const GDSTK_Library* library, const char* name) {
    if (!library) return nullptr;
    Cell* cell = library->lib.get_cell(name);
    if (!cell) return nullptr;
    auto* wrapper = new GDSTK_Cell;
    wrapper->cell = *cell;
    return wrapper;
}

GDSTK_RawCell* gdstk_library_get_rawcell(const GDSTK_Library* library, const char* name) {
    if (!library) return nullptr;
    RawCell* rawcell = library->lib.get_rawcell(name);
    if (!rawcell) return nullptr;
    auto* wrapper = new GDSTK_RawCell;
    wrapper->rawcell = *rawcell;
    return wrapper;
}

GDSTK_ErrorCode gdstk_library_write_gds(const GDSTK_Library* library, const char* filename,
                                      uint64_t max_points, const struct tm* timestamp) {
    if (!library) return GDSTK_ERROR_NO_LIBRARY;
    ErrorCode result = library->lib.write_gds(filename, max_points, const_cast<tm*>(timestamp));
    return static_cast<GDSTK_ErrorCode>(result);
}

GDSTK_ErrorCode gdstk_library_write_oas(GDSTK_Library* library, const char* filename,
                                       double circle_tolerance, uint8_t deflate_level,
                                       uint16_t config_flags) {
    if (!library) return GDSTK_ERROR_NO_LIBRARY;
    ErrorCode result = library->lib.write_oas(filename, circle_tolerance, deflate_level, config_flags);
    return static_cast<GDSTK_ErrorCode>(result);
}

// Library struct accessors
const char* gdstk_library_get_name(const GDSTK_Library* library) {
    return library ? library->lib.name : nullptr;
}

void gdstk_library_set_name(GDSTK_Library* library, const char* name) {
    if (library) {
        if (library->lib.name) free_allocation(library->lib.name);
        library->lib.name = copy_string(name, nullptr);
    }
}

double gdstk_library_get_unit(const GDSTK_Library* library) {
    return library ? library->lib.unit : 0.0;
}

void gdstk_library_set_unit(GDSTK_Library* library, double unit) {
    if (library) library->lib.unit = unit;
}

double gdstk_library_get_precision(const GDSTK_Library* library) {
    return library ? library->lib.precision : 0.0;
}

void gdstk_library_set_precision(GDSTK_Library* library, double precision) {
    if (library) library->lib.precision = precision;
}

uint64_t gdstk_library_get_cell_count(const GDSTK_Library* library) {
    return library ? library->lib.cell_array.count : 0;
}

GDSTK_Cell* gdstk_library_get_cell_by_index(const GDSTK_Library* library, uint64_t index) {
    if (!library || index >= library->lib.cell_array.count) return nullptr;
    auto* wrapper = new GDSTK_Cell;
    wrapper->cell = *library->lib.cell_array[index];
    return wrapper;
}

uint64_t gdstk_library_get_rawcell_count(const GDSTK_Library* library) {
    return library ? library->lib.rawcell_array.count : 0;
}

GDSTK_RawCell* gdstk_library_get_rawcell_by_index(const GDSTK_Library* library, uint64_t index) {
    if (!library || index >= library->lib.rawcell_array.count) return nullptr;
    auto* wrapper = new GDSTK_RawCell;
    wrapper->rawcell = *library->lib.rawcell_array[index];
    return wrapper;
}

GDSTK_Property* gdstk_library_get_properties(const GDSTK_Library* library) {
    if (!library || !library->lib.properties) return nullptr;
    auto* wrapper = new GDSTK_Property;
    wrapper->property = *library->lib.properties;
    return wrapper;
}

void gdstk_library_set_properties(GDSTK_Library* library, GDSTK_Property* properties) {
    if (library) {
        if (properties) {
            library->lib.properties = &properties->property;
        } else {
            library->lib.properties = nullptr;
        }
    }
}

// Additional Library functions
void gdstk_library_print(const GDSTK_Library* library, int all) {
    if (library) library->lib.print(all);
}

void gdstk_library_copy_from(GDSTK_Library* dst, const GDSTK_Library* src, int deep_copy) {
    if (dst && src) dst->lib.copy_from(src->lib, deep_copy);
}

void gdstk_library_get_shape_tags(const GDSTK_Library* library, GDSTK_TagSet* result) {
    if (library && result) {
        library->lib.get_shape_tags(result->set);
    }
}

void gdstk_library_get_label_tags(const GDSTK_Library* library, GDSTK_TagSet* result) {
    if (library && result) {
        library->lib.get_label_tags(result->set);
    }
}

void gdstk_library_rename_cell(GDSTK_Library* library, const char* old_name, const char* new_name) {
    if (library) library->lib.rename_cell(old_name, new_name);
}

// File I/O implementation
GDSTK_Library* gdstk_read_gds(const char* filename, double unit, double tolerance,
                             const GDSTK_TagSet* shape_tags, GDSTK_ErrorCode* error_code) {
    ErrorCode ec = ErrorCode::NoError;
    Library lib = read_gds(filename, unit, tolerance, shape_tags ? &shape_tags->set : nullptr, &ec);
    
    if (error_code) *error_code = static_cast<GDSTK_ErrorCode>(ec);
    if (ec != ErrorCode::NoError) return nullptr;
    
    auto* wrapper = new GDSTK_Library;
    wrapper->lib = lib;
    return wrapper;
}

GDSTK_Library* gdstk_read_oas(const char* filename, double unit, double tolerance,
                             GDSTK_ErrorCode* error_code) {
    ErrorCode ec = ErrorCode::NoError;
    Library lib = read_oas(filename, unit, tolerance, &ec);
    
    if (error_code) *error_code = static_cast<GDSTK_ErrorCode>(ec);
    if (ec != ErrorCode::NoError) return nullptr;
    
    auto* wrapper = new GDSTK_Library;
    wrapper->lib = lib;
    return wrapper;
}

GDSTK_ErrorCode gdstk_gds_units(const char* filename, double* unit, double* precision) {
    if (!unit || !precision) return GDSTK_ERROR_OTHER;
    ErrorCode result = gds_units(filename, *unit, *precision);
    return static_cast<GDSTK_ErrorCode>(result);
}

GDSTK_ErrorCode gdstk_oas_precision(const char* filename, double* precision) {
    if (!precision) return GDSTK_ERROR_OTHER;
    ErrorCode result = oas_precision(filename, *precision);
    return static_cast<GDSTK_ErrorCode>(result);
}

int gdstk_oas_validate(const char* filename, uint32_t* signature, GDSTK_ErrorCode* error_code) {
    ErrorCode ec = ErrorCode::NoError;
    bool result = oas_validate(filename, signature, &ec);
    if (error_code) *error_code = static_cast<GDSTK_ErrorCode>(ec);
    return result ? 1 : 0;
}

GDSTK_ErrorCode gdstk_gds_info(const char* filename, GDSTK_LibraryInfo* info) {
    if (!info) return GDSTK_ERROR_OTHER;
    ErrorCode result = gds_info(filename, info->info);
    return static_cast<GDSTK_ErrorCode>(result);
}

// LibraryInfo implementation
GDSTK_LibraryInfo* gdstk_library_info_create() {
    return new GDSTK_LibraryInfo;
}

void gdstk_library_info_free(GDSTK_LibraryInfo* info) {
    if (info) {
        info->info.clear();
        delete info;
    }
}

void gdstk_library_info_clear(GDSTK_LibraryInfo* info) {
    if (info) info->info.clear();
}

// LibraryInfo struct accessors
uint64_t gdstk_library_info_get_cell_names_count(const GDSTK_LibraryInfo* info) {
    return info ? info->info.cell_names.count : 0;
}

char* gdstk_library_info_get_cell_name(const GDSTK_LibraryInfo* info, uint64_t index) {
    if (!info || index >= info->info.cell_names.count) return nullptr;
    return copy_string(info->info.cell_names.items[index], nullptr);
}

uint64_t gdstk_library_info_get_shape_tags_count(const GDSTK_LibraryInfo* info) {
    return info ? info->info.shape_tags.count : 0;
}

char* gdstk_library_info_get_shape_tag(const GDSTK_LibraryInfo* info, uint64_t index) {
    if (!info || index >= info->info.shape_tags.count) return nullptr;
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", static_cast<int>(info->info.shape_tags.items[index].value));
    return copy_string(buffer, nullptr);
}

uint64_t gdstk_library_info_get_label_tags_count(const GDSTK_LibraryInfo* info) {
    return info ? info->info.label_tags.count : 0;
}

char* gdstk_library_info_get_label_tag(const GDSTK_LibraryInfo* info, uint64_t index) {
    if (!info || index >= info->info.label_tags.count) return nullptr;
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", static_cast<int>(info->info.label_tags.items[index].value));
    return copy_string(buffer, nullptr);
}

uint64_t gdstk_library_info_get_num_polygons(const GDSTK_LibraryInfo* info) {
    return info ? info->info.num_polygons : 0;
}

uint64_t gdstk_library_info_get_num_paths(const GDSTK_LibraryInfo* info) {
    return info ? info->info.num_paths : 0;
}

uint64_t gdstk_library_info_get_num_references(const GDSTK_LibraryInfo* info) {
    return info ? info->info.num_references : 0;
}

uint64_t gdstk_library_info_get_num_labels(const GDSTK_LibraryInfo* info) {
    return info ? info->info.num_labels : 0;
}

double gdstk_library_info_get_unit(const GDSTK_LibraryInfo* info) {
    return info ? info->info.unit : 0.0;
}

double gdstk_library_info_get_precision(const GDSTK_LibraryInfo* info) {
    return info ? info->info.precision : 0.0;
}

// Top level cell retrieval
void gdstk_library_get_top_level(const GDSTK_Library* library, struct GDSTK_Array* top_cells,
                                struct GDSTK_Array* top_rawcells) {
    if (!library || !top_cells || !top_rawcells) return;

    // Call library's top_level function directly with the arrays
    library->lib.top_level(*reinterpret_cast<gdstk::Array<Cell*>*>(top_cells->array),
                          *reinterpret_cast<gdstk::Array<RawCell*>*>(top_rawcells->array));
}

// Cell replacement functions
void gdstk_library_replace_cell_with_cell(GDSTK_Library* library, GDSTK_Cell* old_cell,
                                        GDSTK_Cell* new_cell) {
    if (!library || !old_cell || !new_cell) return;
    library->lib.replace_cell(&old_cell->cell, &new_cell->cell);
}

void gdstk_library_replace_cell_with_rawcell(GDSTK_Library* library, GDSTK_Cell* old_cell,
                                           GDSTK_RawCell* new_cell) {
    if (!library || !old_cell || !new_cell) return;
    library->lib.replace_cell(&old_cell->cell, &new_cell->rawcell);
}

void gdstk_library_replace_rawcell_with_cell(GDSTK_Library* library, GDSTK_RawCell* old_cell,
                                           GDSTK_Cell* new_cell) {
    if (!library || !old_cell || !new_cell) return;
    library->lib.replace_cell(&old_cell->rawcell, &new_cell->cell);
}

void gdstk_library_replace_rawcell_with_rawcell(GDSTK_Library* library, GDSTK_RawCell* old_cell,
                                              GDSTK_RawCell* new_cell) {
    if (!library || !old_cell || !new_cell) return;
    library->lib.replace_cell(&old_cell->rawcell, &new_cell->rawcell);
}

// Tag remapping
void gdstk_library_remap_tags(GDSTK_Library* library, const GDSTK_TagMap* map) {
    if (!library || !map) return;
    library->lib.remap_tags(map->map);
}

// GDS timestamp functions
struct tm gdstk_gds_timestamp(const char* filename, const struct tm* new_timestamp, 
                            GDSTK_ErrorCode* error_code) {
    ErrorCode ec = ErrorCode::NoError;
    struct tm result = gds_timestamp(filename, new_timestamp, &ec);
    if (error_code) *error_code = static_cast<GDSTK_ErrorCode>(ec);
    return result;
}

} // extern "C"