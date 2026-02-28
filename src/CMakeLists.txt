
set(Name imtui)

cmake_minimum_required(VERSION 3.10)

set(PUBLIC_INCLUDE_DIRS
    ./
    ./Common/
)

set(PRIVATE_INCLUDE_DIRS
    ../lib/wtswidth
)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ./*.cpp ./*.h)
list(APPEND SOURCE_FILES ../lib/wtswidth/wtswidth.c)

if (IMTUI_BUILD_STATIC_LIB)

    add_library(${Name}_static STATIC ${SOURCE_FILES})

    target_include_directories(${Name}_static PUBLIC ${PUBLIC_INCLUDE_DIRS})
    target_include_directories(${Name}_static SYSTEM PRIVATE ${PRIVATE_INCLUDE_DIRS})

    set_target_properties(${Name}_static PROPERTIES OUTPUT_NAME ${Name})

    target_compile_features(${Name}_static PRIVATE cxx_std_23)

endif()

if (IMTUI_BUILD_SHARED_LIB)

    add_library(${Name}_shared SHARED ${SOURCE_FILES})

    target_include_directories(${Name}_shared PUBLIC ${PUBLIC_INCLUDE_DIRS})
    target_include_directories(${Name}_shared SYSTEM PRIVATE ${PRIVATE_INCLUDE_DIRS})

    set_target_properties(${Name}_shared PROPERTIES OUTPUT_NAME ${Name})

    target_compile_features(${Name}_shared PRIVATE cxx_std_23)

endif()
