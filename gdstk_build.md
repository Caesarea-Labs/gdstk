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

6. To export the library, run in an elevated terminal:
```cmd
  cmake -S . -B build -DCMAKE_INSTALL_PREFIX="../gdstk_built"
  cmake --build build --target install
```
