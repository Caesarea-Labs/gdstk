#include "array_c.h"

#include <cstdlib>
#include <cstring>

#include "gdstk/array.hpp"
#include "gdstk/vec.hpp"

// Helper function to convert from C to C++ type
namespace {

gdstk::Array<void*>* to_cpp(GDSTK_Array array) {
    return static_cast<gdstk::Array<void*>*>(array.array);
}
}  // namespace

// Internal wrapper structure
// struct GDSTK_Array {
//     gdstk::Array<void*>* array;
// };

extern "C" {

GDSTK_Array gdstk_array_create(int unused) {
    auto wrapper = GDSTK_Array{};
    wrapper.array = new gdstk::Array<void*>();
    return wrapper;
}

void gdstk_array_free(GDSTK_Array array) {
    if (!array.array) {
        fprintf(stderr, "Warning: gdstk_array_free received null array parameter\n");
        return;
    }
    const auto arr = to_cpp(array);
    arr->clear();
    delete arr;
}

// void gdstk_array_clear(GDSTK_Array* array) {
//     if (!array) {
//         fprintf(stderr, "Warning: gdstk_array_clear received null array parameter\n");
//         return;
//     }
//     to_cpp(array)->clear();
// }

void gdstk_array_print(const GDSTK_Array array, int all) {
    if (!array.array) {
        fprintf(stderr, "Warning: gdstk_array_print received null array parameter\n");
        return;
    }
    to_cpp(array)->print(all != 0);
}

uint64_t gdstk_array_count(const GDSTK_Array array) {
    if (!array.array) {
        fprintf(stderr, "Warning: gdstk_array_count received null array parameter\n");
        return 0;
    }
    return to_cpp(array)->count;
}

uint64_t gdstk_array_capacity(const GDSTK_Array array) {
    if (!array.array) {
        fprintf(stderr, "Warning: gdstk_array_capacity received null array parameter\n");
        return 0;
    }
    return to_cpp(array)->capacity;
}

// NEW:
void* gdstk_array_get(GDSTK_Array array, uint64_t index) {
    if (!array.array) {
        fprintf(stderr, "Warning: gdstk_array_get received null array parameter\n");
        return nullptr;
    }
    auto* cpp_array = to_cpp(array);
    return (*cpp_array)[index];
}

void gdstk_array_set(GDSTK_Array array, uint64_t index, const void* value) {
    if (!array.array || !value) {
        fprintf(stderr, "Warning: gdstk_array_set received null parameter\n");
        return;
    }
    auto* cpp_array = to_cpp(array);
    (*cpp_array)[index] = const_cast<void*>(value);
}

void gdstk_array_append(GDSTK_Array array, const void* item) {
    if (!array.array || !item) {
        fprintf(stderr, "Warning: gdstk_array_append received null parameter\n");
        return;
    }
    to_cpp(array)->append(const_cast<void*>(item));
}

void gdstk_array_ensure_slots(GDSTK_Array array, uint64_t free_slots) {
    if (!array.array) {
        fprintf(stderr, "Warning: gdstk_array_ensure_slots received null array parameter\n");
        return;
    }
    to_cpp(array)->ensure_slots(free_slots);
}

void gdstk_array_copy_from(GDSTK_Array dst, const GDSTK_Array src) {
    if (!dst.array || !src.array) {
        fprintf(stderr, "Warning: gdstk_array_copy_from received null parameter\n");
        return;
    }
    to_cpp(dst)->copy_from(*to_cpp(src));
}

void gdstk_array_extend(GDSTK_Array array, const GDSTK_Array src) {
    if (!array.array) {
        fprintf(stderr, "Warning: gdstk_array_extend received null destination array parameter\n");
        return;
    }
    if (!src.array) {
        fprintf(stderr, "Warning: gdstk_array_extend received null source array parameter\n");
        return;
    }
    to_cpp(array)->extend(*to_cpp(src));
}

int gdstk_array_contains(const GDSTK_Array array, const void* item) {
    if (!array.array) {
        fprintf(stderr, "Warning: gdstk_array_contains received null array parameter\n");
        return 0;
    }
    if (!item) {
        fprintf(stderr, "Warning: gdstk_array_contains received null item parameter\n");
        return 0;
    }
    return to_cpp(array)->contains(const_cast<void*>(item));
}

uint64_t gdstk_array_index(const GDSTK_Array array, const void* item) {
    if (!array.array) {
        fprintf(stderr, "Warning: gdstk_array_index received null array parameter\n");
        return gdstk_array_count(array);
    }
    if (!item) {
        fprintf(stderr, "Warning: gdstk_array_index received null item parameter\n");
        return gdstk_array_count(array);
    }
    return to_cpp(array)->index(const_cast<void*>(item));
}

void gdstk_array_remove(GDSTK_Array array, uint64_t index) {
    if (!array.array) {
        fprintf(stderr, "Warning: gdstk_array_remove received null array parameter\n");
        return;
    }
    to_cpp(array)->remove(index);
}

void gdstk_array_remove_unordered(GDSTK_Array array, uint64_t index) {
    if (!array.array) {
        fprintf(stderr, "Warning: gdstk_array_remove_unordered received null array parameter\n");
        return;
    }
    to_cpp(array)->remove_unordered(index);
}

int gdstk_array_remove_item(GDSTK_Array array, const void* item) {
    if (!array.array) {
        fprintf(stderr, "Warning: gdstk_array_remove_item received null array parameter\n");
        return 0;
    }
    if (!item) {
        fprintf(stderr, "Warning: gdstk_array_remove_item received null item parameter\n");
        return 0;
    }
    return to_cpp(array)->remove_item(const_cast<void*>(item));
}

}  // extern "C"