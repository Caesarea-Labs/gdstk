#ifndef GDSTK_HEADER_ARRAY_C
#define GDSTK_HEADER_ARRAY_C

#include <library_c.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// Opaque pointer to the array structure
typedef struct GDSTK_Array GDSTK_Array;

// Constructor and destructor
GDSTK_API GDSTK_Array* gdstk_array_create(int unused);
GDSTK_API void gdstk_array_free(GDSTK_Array* array);

// Basic operations
GDSTK_API void gdstk_array_clear(GDSTK_Array* array);
GDSTK_API void gdstk_array_print(const GDSTK_Array* array, int all);

// Array accessors
GDSTK_API uint64_t gdstk_array_count(const GDSTK_Array* array);
GDSTK_API uint64_t gdstk_array_capacity(const GDSTK_Array* array);

// Element access
GDSTK_API void* gdstk_array_get(GDSTK_Array* array, uint64_t index);
GDSTK_API void gdstk_array_set(GDSTK_Array* array, uint64_t index, const void* value);

// Array modification
GDSTK_API void gdstk_array_append(GDSTK_Array* array, const void* item);
GDSTK_API void gdstk_array_ensure_slots(GDSTK_Array* array, uint64_t free_slots);
GDSTK_API void gdstk_array_copy_from(GDSTK_Array* dst, const GDSTK_Array* src);
GDSTK_API void gdstk_array_extend(GDSTK_Array* array, const GDSTK_Array* src);

// Array search and removal
GDSTK_API int gdstk_array_contains(const GDSTK_Array* array, const void* item);
GDSTK_API uint64_t gdstk_array_index(const GDSTK_Array* array, const void* item);
GDSTK_API void gdstk_array_remove(GDSTK_Array* array, uint64_t index);
GDSTK_API void gdstk_array_remove_unordered(GDSTK_Array* array, uint64_t index);
GDSTK_API int gdstk_array_remove_item(GDSTK_Array* array, const void* item);

#ifdef __cplusplus
}
#endif

#endif  // GDSTK_HEADER_ARRAY_C