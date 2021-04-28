cmake_minimum_required(VERSION 3.15.0)
project(RenderEngine VERSION 0.1.0)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include(CTest)
enable_testing()

add_executable(RenderEngine main.cc core/window.cc core/input.cc)

target_include_directories(RenderEngine PUBLIC "./")

target_include_directories(RenderEngine PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(RenderEngine PUBLIC ${OPENGL_INCLUDE_DIRS})
target_include_directories(RenderEngine PUBLIC ${GLEW_INCLUDE_DIRS})

message(STATUS "<<${OPENGL_INCLUDE_DIRS}>>")
message(STATUS "<<${SDL2_INCLUDE_DIRS}>>")

target_link_libraries(RenderEngine ${SDL2_LIBRARIES})
target_link_libraries(RenderEngine ${OPENGL_LIBRARIES})
target_link_libraries(RenderEngine ${GLEW_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
