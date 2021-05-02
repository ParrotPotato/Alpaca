# cmake file tutorial for SDL, OPENGL, GLEW and imgui
# (sdl and opengl) https://marcelfischer.eu/blog/2019/sdl-opengl-cmake/
# (imgui) https://marcelfischer.eu/blog/2019/imgui-in-sdl-opengl/

cmake_minimum_required(VERSION 3.15.0)
project(renderEngine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include(CTest)
enable_testing()

add_library(imgui STATIC
    # Main Imgui files
    vendor/imgui/imgui.cpp vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp vendor/imgui/imgui_widgets.cpp
    # SDL2+OpenGL-specific files
    vendor/imgui/backends/imgui_impl_sdl.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)

# Make SDL2 available to Imgui
target_include_directories(imgui PUBLIC ${SDL2_INCLUDE_DIRS})
# imgui/backends/ contains the SDL implementation
target_include_directories(imgui PUBLIC vendor/imgui/ vendor/imgui/backends/)
# Configure Imgui to use OpengGL through SDL2
target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_CUSTOM=<SDL_opengl.h>  GL_GLEXT_PROTOTYPES=1)

add_executable(renderEngine 
    src/main.cc 
    src/core/window.cc 
    src/core/input.cc

    src/graphics/shader.cc
    src/graphics/vertexattrib.cc
    src/graphics/renderer.cc
    src/graphics/mesh.cc
    src/graphics/camera.cc

    src/util/resource.cc
)
target_include_directories(renderEngine PUBLIC "${PROJECT_SOURCE_DIR}/src/")
target_include_directories(renderEngine PUBLIC "${PROJECT_SOURCE_DIR}/vendor/stb")
target_include_directories(renderEngine PUBLIC "${PROJECT_SOURCE_DIR}/vendor/imgui")

target_include_directories(renderEngine PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(renderEngine PUBLIC ${OPENGL_INCLUDE_DIRS})
target_include_directories(renderEngine PUBLIC ${GLEW_INCLUDE_DIRS})

message(STATUS "<<${OPENGL_INCLUDE_DIRS}>>")
message(STATUS "<<${SDL2_INCLUDE_DIRS}>>")

target_link_libraries(renderEngine ${SDL2_LIBRARIES})
target_link_libraries(renderEngine ${OPENGL_LIBRARIES})
target_link_libraries(renderEngine ${GLEW_LIBRARIES})

target_link_libraries(renderEngine imgui)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
