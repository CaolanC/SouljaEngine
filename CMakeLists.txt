cmake_minimum_required(VERSION 3.28.3)
project(Soulja C)


add_subdirectory(thirdpartypoopers/libhv)

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.c")

add_library(SouljaLib ${SRC_FILES})

target_include_directories(SouljaLib PRIVATE internal)

add_executable(Soulja apps/soulja_game/main.c)

target_include_directories(Soulja PRIVATE internal)

set_target_properties(Soulja PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

target_link_libraries(Soulja PRIVATE SouljaLib hv)
