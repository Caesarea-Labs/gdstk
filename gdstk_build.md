# Here's how to build gdstk.
1. Install vcpkg
2. Set environment variable
   ```
   VCPKG_ROOT = C:\Program Files\Microsoft Visual Studio\2022\Community\VC\vcpkg
   ```
3. Build with CLI using:
```
cmake -S . -B build
```
4. Build and run tests using:
```cmd
cd build
cmake --build . --target examples --config Debug
ctest -C Debug
```
5. Or run a specific test with std output:
```cmd
ctest -V  -C debug -R apply_repetition 
```


MIGHT NOT NEED THIS ANYMORE:
2. `cd gdstk`
3. `vcpkg install`
4. `cmake -S . -B build -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_INSTALL_PREFIX="../gdstk_built" -DZLIB_LIBRARY="vcpkg_installed/x64-windows/lib/zlib.lib" -DZLIB_INCLUDE_DIR="vcpkg_installed/x64-windows/include" -DQHULL_LIBRARY="vcpkg_installed/x64-windows/lib/qhull_r.lib" -DQHULL_INCLUDE_DIR="%CD%/vcpkg_installed/x64-windows/include/libqhull_r" -DQHULL_LIBRARY_TYPE=STATIC`
