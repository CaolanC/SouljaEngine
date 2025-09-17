cmake_minimum_required(VERSION 3.28.3)
project(Soulja C)

set(SDL_VIDEO            ON  CACHE BOOL "" FORCE)
set(SDL_VIDEO_X11        ON  CACHE BOOL "" FORCE)
set(SDL_VIDEO_WAYLAND    ON  CACHE BOOL "" FORCE)
set(SDL_VIDEO_OPENGL     ON  CACHE BOOL "" FORCE)
set(SDL_VIDEO_OPENGL_GLX ON  CACHE BOOL "" FORCE)
set(SDL_VIDEO_OPENGL_EGL ON  CACHE BOOL "" FORCE)

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

find_package(OpenGL REQUIRED)

add_subdirectory(thirdpartypoopers/libhv)
add_subdirectory(thirdpartypoopers/libsdl-org)
add_subdirectory(thirdpartypoopers/cglm)
add_subdirectory(thirdpartypoopers/glad)
add_subdirectory(thirdpartypoopers/FastNoiseLite)
add_subdirectory(thirdpartypoopers/glm)

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/server/*.c")
file(GLOB_RECURSE CLIENT_SRC_FILES "${CMAKE_SOURCE_DIR}/src/client/*.c")
file(GLOB_RECURSE SHARED_SRC_FILES "${CMAKE_SOURCE_DIR}/src/shared/*.c")
add_library(SouljaLib ${SRC_FILES})
add_library(SouljaClientLib ${CLIENT_SRC_FILES})
add_library(SouljaSharedLib ${SHARED_SRC_FILES})

add_executable(Soulja apps/soulja_server/main.c)
add_executable(SouljaClient apps/soulja_client/main.c)
add_executable(SouljaTestSandbox apps/soulja_test/main.c)

target_include_directories(SouljaLib PRIVATE internal)
target_include_directories(SouljaClientLib PRIVATE internal)
target_include_directories(SouljaSharedLib PRIVATE internal)

target_include_directories(SouljaTestSandbox PRIVATE internal)
target_include_directories(SouljaClient PRIVATE internal)
target_include_directories(SouljaClient PRIVATE internal)
target_include_directories(Soulja PRIVATE internal)

set_target_properties(Soulja PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
set_target_properties(SouljaClient PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

set_target_properties(SouljaTestSandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

set(CLIENT_SHARED_LIBS cglm glad SDL3::SDL3 OpenGL::GL m glad fastnoiselitelib SouljaSharedLib)

target_link_libraries(SouljaSharedLib PRIVATE fastnoiselitelib)
target_link_libraries(Soulja PRIVATE SouljaSharedLib SouljaLib hv)
target_link_libraries(SouljaClient PRIVATE ${CLIENT_SHARED_LIBS} SouljaClientLib)
target_link_libraries(SouljaTestSandbox PRIVATE SouljaSharedLib SouljaClientLib SDL3::SDL3 OpenGL::GL cglm m glad fastnoiselitelib)
target_link_libraries(SouljaClientLib PRIVATE ${CLIENT_SHARED_LIBS})

target_compile_definitions(SouljaTestSandbox PRIVATE SLJA_ASSETS_DIR="${ASSETS_DIR}")
target_compile_definitions(SouljaClient PRIVATE SLJA_ASSETS_DIR="${ASSETS_DIR}")
target_compile_definitions(SouljaClientLib PRIVATE SLJA_ASSETS_DIR="${ASSETS_DIR}")

project(ProjectSoulja CXX)

add_executable(Client apps/client/main.cpp)
set_target_properties(Client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
target_include_directories(Client PRIVATE internal/client)
target_link_libraries(Client PRIVATE glad SDL3::SDL3 OpenGL::GL ${CMAKE_SOURCE_DIR}/internal/client)
target_compile_definitions(Client PRIVATE SLJA_ASSETS_DIR="${ASSETS_DIR}" SLJA_WINDOW_TITLE="Soulja")
