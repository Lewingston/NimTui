
set(Name ImTui)

cmake_minimum_required(VERSION 3.10)

project(${Name} VERSION 0.0.1)

set(IMTUI_BUILD_STATIC_LIB ON  CACHE BOOL "Build static library")
set(IMTUI_BUILD_SHARED_LIB ON  CACHE BOOL "Build shared library")
set(IMTUI_BUILD_TEST       ON  CACHE BOOL "Build tests")
set(IMTUI_BUILD_DEMO       ON  CACHE BOOL "Build Demo")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
