// gdstk_c.cpp
#include <library_c.h>

#include "gdstk/library.hpp"

using namespace gdstk;

extern "C" {

struct GDSTK_Library {
    Library lib;
};

struct GDSTK_LibraryInfo {
    LibraryInfo info;
};

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
    return reinterpret_cast<GDSTK_Cell*>(library->lib.get_cell(name));
}

GDSTK_RawCell* gdstk_library_get_rawcell(const GDSTK_Library* library, const char* name) {
    if (!library) return nullptr;
    return reinterpret_cast<GDSTK_RawCell*>(library->lib.get_rawcell(name));
}

GDSTK_ErrorCode gdstk_library_write_gds(const GDSTK_Library* library, const char* filename,
                                      uint64_t max_points, const struct tm* timestamp) {
    if (!library) return GDSTK_ERROR_NO_LIBRARY;
    return static_cast<GDSTK_ErrorCode>(library->lib.write_gds(filename, max_points,
                                                             const_cast<tm*>(timestamp)));
}

GDSTK_ErrorCode gdstk_library_write_oas(GDSTK_Library* library, const char* filename,
                                       double circle_tolerance, uint8_t deflate_level,
                                       uint16_t config_flags) {
    if (!library) return GDSTK_ERROR_NO_LIBRARY;
    return static_cast<GDSTK_ErrorCode>(library->lib.write_oas(filename, circle_tolerance,
                                                              deflate_level, config_flags));
}

// File I/O implementation
GDSTK_Library* gdstk_read_gds(const char* filename, double unit, double tolerance,
                             const GDSTK_TagSet* shape_tags, GDSTK_ErrorCode* error_code) {
    auto ec = ErrorCode::NoError;
    const auto* tags = reinterpret_cast<const Set<Tag>*>(shape_tags);
    const Library lib = read_gds(filename, unit, tolerance, tags, &ec);

    if (error_code) *error_code = static_cast<GDSTK_ErrorCode>(ec);

    if (ec != ErrorCode::NoError) return nullptr;

    auto* wrapper = new GDSTK_Library;
    wrapper->lib = lib;
    return wrapper;
}

GDSTK_ErrorCode gdstk_gds_units(const char* filename, double* unit, double* precision) {
    return static_cast<GDSTK_ErrorCode>(gds_units(filename, *unit, *precision));
}

GDSTK_ErrorCode gdstk_gds_info(const char* filename, GDSTK_LibraryInfo* info) {
    if (!info) return GDSTK_ERROR_OTHER;
    return static_cast<GDSTK_ErrorCode>(gds_info(filename, info->info));
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

} // extern "C"