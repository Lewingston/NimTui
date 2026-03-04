
set(Name ImTui)

cmake_minimum_required(VERSION 3.10)

project(${Name} VERSION 0.0.1)

set(IMTUI_BUILD_STATIC_LIB ON  CACHE BOOL "Build static library")
set(IMTUI_BUILD_SHARED_LIB ON  CACHE BOOL "Build shared library")
set(IMTUI_BUILD_TEST       ON  CACHE BOOL "Build tests")
set(IMTUI_BUILD_DEMO       ON  CACHE BOOL "Build Demo")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(IMTUI_WARNING_FLAGS
    -Wall
    -Wextra
    -pedantic
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wmisleading-indentation
    -Wduplicated-cond
    -Wduplicated-branches
    -Wnull-dereference
    -Wfloat-equal
    -Wformat=2
    -Wlogical-op
    -Wmissing-declarations
    -Wmissing-include-dirs
    -Wpointer-arith
    -Wredundant-decls
    -Wsequence-point
    -Wswitch
    -Wundef
    -Wuseless-cast
    -Wimplicit-fallthrough
    -Wunreachable-code
    -Wunused-but-set-parameter
    -Wwrite-strings
    -Werror=return-type
)

if (IMTUI_BUILD_STATIC_LIB OR IMTUI_BUILD_SHARED_LIB)

    add_subdirectory(src)

endif()

if (IMTUI_BUILD_TEST)

    add_subdirectory(lib/googletest)
    add_subdirectory(test)

endif()

if (IMTUI_BUILD_DEMO)

    add_subdirectory(demo)

endif()

add_custom_target(coverage
    COMMAND del /S /Q *.gcda
    COMMAND ctest --test-dir ./test/
    COMMAND gcovr -r ../src/ . --html-nested --html-theme github.dark-green --output coverage/coverage.html
)
