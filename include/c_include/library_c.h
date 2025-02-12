#ifndef GDSTK_C_H
#define GDSTK_C_H

#ifdef _WIN32
  #define GDSTK_API __declspec(dllexport)
#else
  #define GDSTK_API __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <time.h>
#include "array_c.h"

struct GDSTK_Library;
struct GDSTK_Cell;
struct GDSTK_RawCell;
struct GDSTK_Property;
struct GDSTK_TagSet;
struct GDSTK_LibraryInfo;
struct GDSTK_TagMap;

typedef enum  {
    GDSTK_NoError = 0,
    // Warnings
    GDSTK_BooleanError,
    GDSTK_EmptyPath,
    GDSTK_IntersectionNotFound,
    GDSTK_MissingReference,
    GDSTK_UnsupportedRecord,
    GDSTK_UnofficialSpecification,
    GDSTK_InvalidRepetition,
    GDSTK_Overflow,
    // Errors
    GDSTK_ChecksumError,
    GDSTK_OutputFileOpenError,
    GDSTK_InputFileOpenError,
    GDSTK_InputFileError,
    GDSTK_FileError,
    GDSTK_InvalidFile,
    GDSTK_InsufficientMemory,
    GDSTK_ZlibError,
} GDSTK_ErrorCode;




// Library functions
GDSTK_API struct GDSTK_Library* gdstk_library_create(const char* name, double unit, double precision);
GDSTK_API void gdstk_library_free(struct GDSTK_Library* library);

GDSTK_API void gdstk_library_clear(struct GDSTK_Library* library);
GDSTK_API void gdstk_library_free_all(struct GDSTK_Library* library);

GDSTK_API struct GDSTK_Cell* gdstk_library_get_cell(const struct GDSTK_Library* library, const char* name);
GDSTK_API struct GDSTK_RawCell* gdstk_library_get_rawcell(const struct GDSTK_Library* library, const char* name);

GDSTK_API GDSTK_ErrorCode gdstk_library_write_gds(const struct GDSTK_Library* library, const char* filename,
                                      uint64_t max_points, const struct tm* timestamp);
GDSTK_API GDSTK_ErrorCode gdstk_library_write_oas(struct GDSTK_Library* library, const char* filename,
                                       double circle_tolerance, uint8_t deflate_level,
                                       uint16_t config_flags);

GDSTK_API void gdstk_library_print(const struct GDSTK_Library* library, int print_all);
GDSTK_API void gdstk_library_copy_from(struct GDSTK_Library* dst, const struct GDSTK_Library* src, int deep_copy);
GDSTK_API void gdstk_library_get_shape_tags(const struct GDSTK_Library* library, struct GDSTK_TagSet* result);
GDSTK_API void gdstk_library_get_label_tags(const struct GDSTK_Library* library, struct GDSTK_TagSet* result);
GDSTK_API void gdstk_library_rename_cell(struct GDSTK_Library* library, const char* old_name, const char* new_name);

// Library struct accessors
GDSTK_API const char* gdstk_library_get_name(const struct GDSTK_Library* library);
GDSTK_API void gdstk_library_set_name(struct GDSTK_Library* library, const char* name);
GDSTK_API double gdstk_library_get_unit(const struct GDSTK_Library* library);
GDSTK_API void gdstk_library_set_unit(struct GDSTK_Library* library, double unit);
GDSTK_API double gdstk_library_get_precision(const struct GDSTK_Library* library);
GDSTK_API void gdstk_library_set_precision(struct GDSTK_Library* library, double precision);
GDSTK_API uint64_t gdstk_library_get_cell_count(const struct GDSTK_Library* library);
GDSTK_API struct GDSTK_Cell* gdstk_library_get_cell_by_index(const struct GDSTK_Library* library, uint64_t index);
GDSTK_API uint64_t gdstk_library_get_rawcell_count(const struct GDSTK_Library* library);
GDSTK_API struct GDSTK_RawCell* gdstk_library_get_rawcell_by_index(const struct GDSTK_Library* library, uint64_t index);
GDSTK_API struct GDSTK_Property* gdstk_library_get_properties(const struct GDSTK_Library* library);
GDSTK_API void gdstk_library_set_properties(struct GDSTK_Library* library, struct GDSTK_Property* properties);

// Top level cell retrieval
GDSTK_API void gdstk_library_get_top_level(const struct GDSTK_Library* library,struct GDSTK_Array top_cells,
                                          struct GDSTK_Array top_rawcells);

// Cell replacement functions
GDSTK_API void gdstk_library_replace_cell_with_cell(struct GDSTK_Library* library, struct GDSTK_Cell* old_cell,
                                                   struct GDSTK_Cell* new_cell);
GDSTK_API void gdstk_library_replace_cell_with_rawcell(struct GDSTK_Library* library, struct GDSTK_Cell* old_cell,
                                                      struct GDSTK_RawCell* new_cell);
GDSTK_API void gdstk_library_replace_rawcell_with_cell(struct GDSTK_Library* library, struct GDSTK_RawCell* old_cell,
                                                      struct GDSTK_Cell* new_cell);
GDSTK_API void gdstk_library_replace_rawcell_with_rawcell(struct GDSTK_Library* library, struct GDSTK_RawCell* old_cell,
                                                         struct GDSTK_RawCell* new_cell);

// Tag remapping
GDSTK_API void gdstk_library_remap_tags(struct GDSTK_Library* library, const struct GDSTK_TagMap* map);

// LibraryInfo struct accessors
GDSTK_API uint64_t gdstk_library_info_get_cell_names_count(const struct GDSTK_LibraryInfo* info);
GDSTK_API char* gdstk_library_info_get_cell_name(const struct GDSTK_LibraryInfo* info, uint64_t index);

GDSTK_API uint64_t gdstk_library_info_get_shape_tags_count(const struct GDSTK_LibraryInfo* info);
GDSTK_API char* gdstk_library_info_get_shape_tag(const struct GDSTK_LibraryInfo* info, uint64_t index);

GDSTK_API uint64_t gdstk_library_info_get_label_tags_count(const struct GDSTK_LibraryInfo* info);
GDSTK_API char* gdstk_library_info_get_label_tag(const struct GDSTK_LibraryInfo* info, uint64_t index);

GDSTK_API uint64_t gdstk_library_info_get_num_polygons(const struct GDSTK_LibraryInfo* info);
GDSTK_API uint64_t gdstk_library_info_get_num_paths(const struct GDSTK_LibraryInfo* info);
GDSTK_API uint64_t gdstk_library_info_get_num_references(const struct GDSTK_LibraryInfo* info);
GDSTK_API uint64_t gdstk_library_info_get_num_labels(const struct GDSTK_LibraryInfo* info);

GDSTK_API double gdstk_library_info_get_unit(const struct GDSTK_LibraryInfo* info);
GDSTK_API double gdstk_library_info_get_precision(const struct GDSTK_LibraryInfo* info);

// File I/O functions
GDSTK_API struct GDSTK_Library* gdstk_read_gds(const char* filename, double unit, double tolerance,
                             const struct GDSTK_TagSet* shape_tags, GDSTK_ErrorCode* error_code);
GDSTK_API struct GDSTK_Library* gdstk_read_oas(const char* filename, double unit, double tolerance,
                             GDSTK_ErrorCode* error_code);
GDSTK_API GDSTK_ErrorCode gdstk_gds_units(const char* filename, double* unit, double* precision);
GDSTK_API GDSTK_ErrorCode gdstk_gds_info(const char* filename, struct GDSTK_LibraryInfo* info);
GDSTK_API GDSTK_ErrorCode gdstk_oas_precision(const char* filename, double* precision);
GDSTK_API int gdstk_oas_validate(const char* filename, uint32_t* signature, GDSTK_ErrorCode* error_code);

// GDS timestamp functions
GDSTK_API struct tm gdstk_gds_timestamp(const char* filename, const struct tm* new_timestamp, 
                                       GDSTK_ErrorCode* error_code);

// LibraryInfo functions
GDSTK_API struct GDSTK_LibraryInfo* gdstk_library_info_create();
GDSTK_API void gdstk_library_info_free(struct GDSTK_LibraryInfo* info);
GDSTK_API void gdstk_library_info_clear(struct GDSTK_LibraryInfo* info);

#ifdef __cplusplus
}
#endif

#endif // GDSTK_C_H