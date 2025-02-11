#include "array_c.h"
#include <cstring>
#include <cstdlib>
#include "gdstk/array.hpp"
#include "gdstk/vec.hpp"

// Internal wrapper structure
struct GDSTK_Array {
    gdstk::Array<void*>* array;
};

extern "C" {

GDSTK_Array* gdstk_array_create(int unused) {
    auto* wrapper = new GDSTK_Array;
    wrapper->array = new gdstk::Array<void*>();
    return wrapper;
}

void gdstk_array_free(GDSTK_Array* array) {
    if (!array) return;
    delete array->array;
    delete array;
}

void gdstk_array_clear(GDSTK_Array* array) {
    if (!array) return;
    array->array->clear();
}

void gdstk_array_print(const GDSTK_Array* array, int all) {
    if (!array) return;
    array->array->print(all != 0);
}

uint64_t gdstk_array_count(const GDSTK_Array* array) {
    return array ? array->array->count : 0;
}

uint64_t gdstk_array_capacity(const GDSTK_Array* array) {
    return array ? array->array->capacity : 0;
}

void* gdstk_array_get(GDSTK_Array* array, uint64_t index) {
    if (!array || index >= array->array->count) return nullptr;
    return array->array->items[index];
}

void gdstk_array_set(GDSTK_Array* array, uint64_t index, const void* value) {
    if (!array || !value || index >= array->array->count) return;
    array->array->items[index] = const_cast<void*>(value);
}

void gdstk_array_append(GDSTK_Array* array, const void* item) {
    if (!array || !item) return;
    array->array->append(const_cast<void*>(item));
}

void gdstk_array_ensure_slots(GDSTK_Array* array, uint64_t free_slots) {
    if (!array) return;
    uint64_t required_capacity = array->array->count + free_slots;
    if (required_capacity > array->array->capacity) {
        array->array->items = (void**)gdstk::reallocate(array->array->items, sizeof(void*) * required_capacity);
        array->array->capacity = required_capacity;
    }
}

void gdstk_array_copy_from(GDSTK_Array* dst, const GDSTK_Array* src) {
    if (!dst || !src) return;
    dst->array->clear();
    for (uint64_t i = 0; i < src->array->count; i++) {
        dst->array->append(src->array->items[i]);
    }
}

void gdstk_array_extend(GDSTK_Array* array, const GDSTK_Array* src) {
    if (!array || !src) return;
    for (uint64_t i = 0; i < src->array->count; i++) {
        array->array->append(src->array->items[i]);
    }
}

int gdstk_array_contains(const GDSTK_Array* array, const void* item) {
    if (!array || !item) return 0;
    return array->array->contains(const_cast<void*>(item));
}

uint64_t gdstk_array_index(const GDSTK_Array* array, const void* item) {
    if (!array || !item) return gdstk_array_count(array);
    return array->array->index(const_cast<void*>(item));
}

void gdstk_array_remove(GDSTK_Array* array, uint64_t index) {
    if (!array || index >= array->array->count) return;
    array->array->remove(index);
}

void gdstk_array_remove_unordered(GDSTK_Array* array, uint64_t index) {
    if (!array || index >= array->array->count) return;
    array->array->remove_unordered(index);
}

int gdstk_array_remove_item(GDSTK_Array* array, const void* item) {
    if (!array || !item) return 0;
    uint64_t index = gdstk_array_index(array, item);
    if (index < gdstk_array_count(array)) {
        gdstk_array_remove(array, index);
        return 1;
    }
    return 0;
}

} // extern "C"