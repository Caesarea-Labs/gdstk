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

typedef struct GDSTK_Library GDSTK_Library;
typedef struct GDSTK_Cell GDSTK_Cell;
typedef struct GDSTK_RawCell GDSTK_RawCell;
typedef struct GDSTK_Property GDSTK_Property;
typedef struct GDSTK_TagSet GDSTK_TagSet;
typedef struct GDSTK_LibraryInfo GDSTK_LibraryInfo;

typedef enum {
    GDSTK_SUCCESS = 0,
    GDSTK_ERROR_FILE_OPEN,
    GDSTK_ERROR_FILE_FORMAT,
    GDSTK_ERROR_INVALID_UNIT,
    GDSTK_ERROR_NO_LIBRARY,
    GDSTK_ERROR_OTHER
} GDSTK_ErrorCode;

// Library functions
GDSTK_API GDSTK_Library* gdstk_library_create(const char* name, double unit, double precision);
GDSTK_API void gdstk_library_free(GDSTK_Library* library);

GDSTK_API void gdstk_library_clear(GDSTK_Library* library);
GDSTK_API void gdstk_library_free_all(GDSTK_Library* library);

GDSTK_API GDSTK_Cell* gdstk_library_get_cell(const GDSTK_Library* library, const char* name);
GDSTK_API GDSTK_RawCell* gdstk_library_get_rawcell(const GDSTK_Library* library, const char* name);

GDSTK_API GDSTK_ErrorCode gdstk_library_write_gds(const GDSTK_Library* library, const char* filename,
                                      uint64_t max_points, const struct tm* timestamp);
GDSTK_API GDSTK_ErrorCode gdstk_library_write_oas( GDSTK_Library* library, const char* filename,
                                       double circle_tolerance, uint8_t deflate_level,
                                       uint16_t config_flags);

// File I/O functions
GDSTK_API GDSTK_Library* gdstk_read_gds(const char* filename, double unit, double tolerance,
                             const GDSTK_TagSet* shape_tags, GDSTK_ErrorCode* error_code);
GDSTK_API GDSTK_ErrorCode gdstk_gds_units(const char* filename, double* unit, double* precision);
GDSTK_API GDSTK_ErrorCode gdstk_gds_info(const char* filename, GDSTK_LibraryInfo* info);

// LibraryInfo functions
GDSTK_API GDSTK_LibraryInfo* gdstk_library_info_create();
GDSTK_API void gdstk_library_info_free(GDSTK_LibraryInfo* info);
GDSTK_API void gdstk_library_info_clear(GDSTK_LibraryInfo* info);

#ifdef __cplusplus
}
#endif

#endif // GDSTK_C_H