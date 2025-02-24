#include <cell_c.h>
#include <library_c.h>
#include <polygon_c.h>
#include <reference_c.h>
#include <stdio.h>

int main() {
    GDSTK_ErrorCode err;
    struct GDSTK_Library* lib = gdstk_read_gds("../../../../gds/oleg_full.gds", 1e-6, 1e-9, NULL, &err);
    struct GDSTK_Array cells = gdstk_array_create(0);
    struct GDSTK_Array raw_cells = gdstk_array_create(0);
    gdstk_library_get_top_level(lib, cells, raw_cells);
    GDSTK_Cell* cell = gdstk_array_get(cells, 0);
    // GDSTK_Reference* reference = gdstk_array_get(gdstk_cell_get_references(cell), 0);
    struct GDSTK_Array polygons = gdstk_array_create(0);
    gdstk_cell_get_polygons(cell, 1, 0, -1, 0, 0, polygons);
    // int cap = gdstk_array_capacity(polygons);
    // gdstk_reference_get_polygons(reference, 0, 0, 0, 0, 0, polygons);
    GDSTK_Polygon* polygon = gdstk_array_get(polygons, 0);
    struct GDSTK_Vec2Array points = gdstk_polygon_get_point_array(polygon);
    struct GDSTK_Vec2 vec2 = points.items[0];
    printf("x value: %f\n", vec2.x);
    printf("x bytes: %lx\n", *((uint64_t*)&vec2.x));

    printf("%f", gdstk_polygon_area(polygon));

    double value = gdstk_library_get_unit(lib);

    if (lib) {
        gdstk_library_write_gds(lib, "output.gds", 1000, NULL);
        gdstk_library_free(lib);
    }
    return 0;
}