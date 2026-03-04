
set(Name ImTuiDemo)

cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ./*.cpp ./*.h)

add_executable(${Name} ${SOURCE_FILES})

target_compile_features(${Name} PRIVATE cxx_std_23)

target_include_directories(${Name} SYSTEM PRIVATE ../lib)

target_compile_options(${Name} PRIVATE ${IMTUI_WARNING_FLAGS})

target_link_options(${Name} PRIVATE -static -static-libgcc -static-libstdc++)

if (IMTUI_BUILD_STATIC_LIB)

    target_link_libraries(${Name} PRIVATE imtui_static)

elseif (IMTUI_BUILD_SHARED_LIB)

    target_link_libraries(${Name} PRIVATE imtui_shared)

else()

    message(FATAL_ERROR "Unable to build demo without ImTui library!")

endif()

# When library is build with coverage flags, linking must be done with
# coverage enabled
if (IMTUI_TEST_COVERAGE)

    target_link_options(${Name} PRIVATE --coverage -fno-lto)

endif()
