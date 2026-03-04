
set(Name ImTuiTest)

cmake_minimum_required(VERSION 3.10)

enable_testing()

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ../src/*.cpp ../src/*.h)

file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS ./*.cpp ./*.h)

add_executable(${Name} ${SOURCE_FILES} ${TEST_FILES})

set(COVERAGE_FLAGS
    --coverage
    -fno-inline
    -fno-inline-functions
    -fno-inline-functions-called-once
    -fno-lto
    -O0
)

set(PUBLIC_INCLUDE_DIRS
    ../src/
    ../src/Common/
)

set(PRIVATE_INCLUDE_DIRS
    ../lib/wtswidth
)

target_compile_features(${Name} PRIVATE cxx_std_23)

target_include_directories(${Name} PRIVATE ${PUBLIC_INCLUDE_DIRS})
target_include_directories(${Name} SYSTEM PRIVATE ${PRIVATE_INCLUDE_DIRS})

target_compile_options(${Name} PRIVATE ${COVERAGE_FLAGS})
target_compile_options(${Name} PRIVATE ${IMTUI_WARNING_FLAGS})

target_link_options(${Name} PRIVATE -static -static-libgcc -static-libstdc++ --coverage -fno-lto)

target_link_libraries(${Name} PRIVATE GTest::gtest_main wtswidth)

# Register tests
include(GoogleTest)
gtest_discover_tests(${Name})

# Generate directory for coverage reprort
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/coverage")
