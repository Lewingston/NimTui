
set(Name ImTui)

cmake_minimum_required(VERSION 3.10)

project(${Name} VERSION 0.0.1)

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(WARNING_FLAGS
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
    -Werror=return-type)

set(TEST_COMPILE_FLAGS
    --coverage
    -fno-inline
    -fno-inline-functions
    -fno-inline-functions-called-once
    -fno-lto
    -O0)

set(INCLUDE_DIRS
    src/
    src/Common/
    lib/
    lib/wtswidth)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Og")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3")

# All source files; Excluding main.cpp
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp src/*.h)
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

list(APPEND SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/wtswidth/wtswidth.c")

# Test files
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS ./test/*.cpp ./test/*.h)

# Build expectuable
add_executable(${Name} ${SOURCE_FILES} src/main.cpp)

# Build test executable
add_executable(${Name}.test ${SOURCE_FILES} ${TEST_FILES})

# Set include directories
target_include_directories(${Name} SYSTEM PRIVATE ${INCLUDE_DIRS})
target_include_directories(${Name}.test SYSTEM PRIVATE ${INCLUDE_DIRS})

# Executable build configuration
target_link_options(${Name} PRIVATE -static -static-libgcc -static-libstdc++)
target_compile_options(${Name} PRIVATE ${WARNING_FLAGS})

# Test buidl configuration
add_subdirectory(lib/googletest)
target_link_libraries(${Name}.test PRIVATE GTest::gtest_main)
target_compile_options(${Name}.test PRIVATE ${WARNING_FLAGS} ${TEST_COMPILE_FLAGS})
target_link_options(${Name}.test PRIVATE --coverage -fno-lto)

# Register tests
include(GoogleTest)
gtest_discover_tests(${Name}.test)

# Generate directory for coverage reprort
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/coverage")

# Execute custom command to generate coverage report
add_custom_target(coverage
    COMMAND gcovr -r ../src/ . --html-nested --html-theme github.dark-green --output coverage/coverage.html
    COMMAND del /S /Q *.gcda
)

add_custom_target(clean_coverage
    COMMAND del /S /Q *.gcda
)
