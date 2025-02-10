#include <library_c.h>
#include <stdio.h>

int main() {
    GDSTK_ErrorCode err;
    GDSTK_Library* lib = gdstk_read_gds("example.gds", 1e-6, 1e-9, NULL, &err);

    if (lib) {
        gdstk_library_write_gds(lib, "output.gds", 1000, NULL);
        gdstk_library_free(lib);
    }
    return 0;
}