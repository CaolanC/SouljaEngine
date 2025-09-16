cmake_minimum_required(VERSION 3.28.3)
project(Soulja C)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)

if(WIN32)
    set(SDL_VIDEO            ON  CACHE BOOL "" FORCE)
    set(SDL_VIDEO_X11        OFF CACHE BOOL "" FORCE)
    set(SDL_VIDEO_WAYLAND    OFF CACHE BOOL "" FORCE)
    set(SDL_VIDEO_OPENGL     ON  CACHE BOOL "" FORCE)
    set(SDL_VIDEO_OPENGL_GLX OFF CACHE BOOL "" FORCE)
    set(SDL_VIDEO_OPENGL_EGL OFF CACHE BOOL "" FORCE)
else()
    set(SDL_VIDEO            ON  CACHE BOOL "" FORCE)
    set(SDL_VIDEO_X11        ON  CACHE BOOL "" FORCE)
    set(SDL_VIDEO_WAYLAND    ON  CACHE BOOL "" FORCE)
    set(SDL_VIDEO_OPENGL     ON  CACHE BOOL "" FORCE)
    set(SDL_VIDEO_OPENGL_GLX ON  CACHE BOOL "" FORCE)
    set(SDL_VIDEO_OPENGL_EGL ON  CACHE BOOL "" FORCE)
endif()

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

find_package(OpenGL REQUIRED)

add_subdirectory(thirdpartypoopers/libhv)
add_subdirectory(thirdpartypoopers/libsdl-org)
add_subdirectory(thirdpartypoopers/cglm)
add_subdirectory(thirdpartypoopers/glad)
add_subdirectory(thirdpartypoopers/FastNoiseLite)

file(GLOB_RECURSE SRC_FILES           "${CMAKE_SOURCE_DIR}/src/server/*.c")
file(GLOB_RECURSE CLIENT_SRC_FILES    "${CMAKE_SOURCE_DIR}/src/client/*.c")
file(GLOB_RECURSE SHARED_SRC_FILES    "${CMAKE_SOURCE_DIR}/src/shared/*.c")

add_library(SouljaLib        ${SRC_FILES})
add_library(SouljaClientLib  ${CLIENT_SRC_FILES})
add_library(SouljaSharedLib  ${SHARED_SRC_FILES})

add_executable(Soulja             apps/soulja_server/main.c)
add_executable(SouljaClient       apps/soulja_client/main.c)
add_executable(SouljaTestSandbox  apps/soulja_test/main.c)

target_include_directories(SouljaLib        PRIVATE internal)
target_include_directories(SouljaClientLib  PRIVATE internal)
target_include_directories(SouljaSharedLib  PRIVATE internal)

target_include_directories(SouljaTestSandbox PRIVATE internal)
target_include_directories(SouljaClient      PRIVATE internal)
target_include_directories(Soulja            PRIVATE internal)

foreach(tgt IN ITEMS Soulja SouljaClient SouljaTestSandbox)
  set_target_properties(${tgt} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY                  "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG            "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE          "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO   "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL       "${CMAKE_SOURCE_DIR}/bin"
  )
endforeach()

set(CLIENT_SHARED_LIBS cglm glad OpenGL::GL fastnoiselitelib SouljaSharedLib)
if(NOT MSVC)
  list(APPEND CLIENT_SHARED_LIBS m)
endif()

target_link_libraries(SouljaSharedLib PRIVATE fastnoiselitelib)

target_link_libraries(Soulja PRIVATE
  SouljaSharedLib
  SouljaLib
  hv
)

target_link_libraries(SouljaClientLib  PRIVATE ${CLIENT_SHARED_LIBS} SDL3::SDL3)
target_link_libraries(SouljaClient     PRIVATE ${CLIENT_SHARED_LIBS} SDL3::SDL3 SouljaClientLib)

target_link_libraries(SouljaTestSandbox PRIVATE
  SouljaSharedLib
  SouljaClientLib
  SDL3::SDL3
  OpenGL::GL
  cglm
  glad
  fastnoiselitelib
)

target_compile_definitions(SouljaTestSandbox PRIVATE SLJA_ASSETS_DIR="${ASSETS_DIR}")
target_compile_definitions(SouljaClient      PRIVATE SLJA_ASSETS_DIR="${ASSETS_DIR}")
target_compile_definitions(SouljaClientLib   PRIVATE SLJA_ASSETS_DIR="${ASSETS_DIR}")

if(MSVC)                                                                          # CHANGED
  target_compile_definitions(SouljaClient     PRIVATE _USE_MATH_DEFINES)
  target_compile_definitions(SouljaClientLib  PRIVATE _USE_MATH_DEFINES)
  target_compile_definitions(SouljaTestSandbox PRIVATE _USE_MATH_DEFINES)
endif()

