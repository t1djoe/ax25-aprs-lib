cmake_minimum_required(VERSION 3.9)

project(ax25beacon VERSION 0.9)

add_library(${PROJECT_NAME}
src/ax25.c
src/ax25beacon.c)

target_include_directories(${PROJECT_NAME} PRIVATE include)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

set(CMAKE_BUILD_TYPE Release)
set(COMPILE_OPTIONS "-Wall")
set(COMPILE_RELEASE_OPTIONS "${COMPILE_OPTIONS};-O3")
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Release>:${COMPILE_RELEASE_OPTIONS}>")

