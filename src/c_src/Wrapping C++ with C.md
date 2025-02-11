
When wrapping C++ code with a C wrapper:
- First read the C++ header file (for example cell.hpp) to understand the C++ api.
- do NOT use `bool` - it doesn't exist in C
- C wrappers should always be contained in `extern "C"`. 

- Wrap C++ structs with a C struct:
    ```
        struct GDSTK_SomeStruct {
            structName: SomeStruct;
        }
    ```
- Wrap C++ struct fields with functions:
    ```
        int gdstk_someStruct_get_x(struct GDSTK_SomeStruct *someStruct) {
            return someStruct->structName.x;
        }
    ```
- Use portable C types (for example long long instead of long). 
- Make sure to only use C types (bool is not a C type for example).
- Whenever C++ does some automatic memory deallocation that cannot be done from C, an appropriate free() function must be declared to deallocate, and the documentation must explain it should be used
- Every C++ source file+header should be wrapped by a single Cpp wrapper file+ C header. For example, library.cpp+library.hpp is wrapped by library_c.cpp+library_c.h. 
- The C wrapper should be a 1-1 wrapper of the C++ api. For every single field, there is a single accessor of the same name, and same goes for methods and structs. 
