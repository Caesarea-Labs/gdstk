# Enable C language
if(WIN32)
    # Use the vcpkg target triplet if defined; otherwise default to x64-windows.
    if(DEFINED VCPKG_TARGET_TRIPLET)
        set(_triplet ${VCPKG_TARGET_TRIPLET})
    else()
        set(_triplet "x64-windows")
    endif()
    # Set the bin directory; adjust the path if your vcpkg_installed directory is elsewhere.
    set(VCPKG_BIN_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/${_triplet}/bin")

else ()
    message(FATAL_ERROR "Only windows works at the moment")
endif ()


set(ALL_EXAMPLES some_c_file)

foreach(EXAMPLE ${ALL_EXAMPLES})
    add_executable(${EXAMPLE} EXCLUDE_FROM_ALL "${EXAMPLE}.c")
    ################## CAESAREALABS EDIT ###################
    #### REASON: Make sure c++20 is used otherwise examples don't work.
    target_compile_features(${EXAMPLE} PRIVATE c_std_17)
    ##########################################################
    target_link_libraries(${EXAMPLE} gdstk)
    add_test(NAME ${EXAMPLE} COMMAND ${EXAMPLE})

    ################## CAESAREALABS EDIT ###################
    #### REASON: Copy libraries to example output dirs so you won't need to install the libraries manually
    if(WIN32)
        # Echo and copy zlib1.dll as zlibd1.dll
        add_custom_command(TARGET ${EXAMPLE} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E echo "Copying zlib1.dll to $<TARGET_FILE_DIR:${EXAMPLE}>/zlibd1.dll"
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${VCPKG_BIN_DIR}/zlib1.dll"
                "$<TARGET_FILE_DIR:${EXAMPLE}>/zlibd1.dll"
                COMMAND ${CMAKE_COMMAND} -E echo "Finished copying zlib1.dll as zlibd1.dll"
        )


        # Echo and copy qhull_r.dll
        add_custom_command(TARGET ${EXAMPLE} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E echo "Copying qhull_r.dll to $<TARGET_FILE_DIR:${EXAMPLE}>"
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${VCPKG_BIN_DIR}/qhull_r.dll"
                $<TARGET_FILE_DIR:${EXAMPLE}>
                COMMAND ${CMAKE_COMMAND} -E echo "Finished copying qhull_r.dll"
        )

        # Echo and copy gdstk.dll
        add_custom_command(TARGET ${EXAMPLE} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E echo "Copying gdstk.dll from $<TARGET_FILE_DIR:gdstk>/gdstk.dll to $<TARGET_FILE_DIR:${EXAMPLE}>"
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE_DIR:gdstk>/gdstk.dll"
                $<TARGET_FILE_DIR:${EXAMPLE}>
                COMMAND ${CMAKE_COMMAND} -E echo "Finished copying gdstk.dll"
        )
    endif()
    ############################################################################
endforeach()

add_custom_target(c_examples DEPENDS ${ALL_EXAMPLES})
