cmake_minimum_required(VERSION 3.15.0)
project(renderEngine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include(CTest)
enable_testing()

add_executable(renderEngine 
    main.cc 
    core/window.cc 
    core/input.cc
    graphics/shader.cc
    util/resource.cc
)
target_include_directories(renderEngine PUBLIC "${PROJECT_SOURCE_DIR}")

target_include_directories(renderEngine PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(renderEngine PUBLIC ${OPENGL_INCLUDE_DIRS})
target_include_directories(renderEngine PUBLIC ${GLEW_INCLUDE_DIRS})

message(STATUS "<<${OPENGL_INCLUDE_DIRS}>>")
message(STATUS "<<${SDL2_INCLUDE_DIRS}>>")

target_link_libraries(renderEngine ${SDL2_LIBRARIES})
target_link_libraries(renderEngine ${OPENGL_LIBRARIES})
target_link_libraries(renderEngine ${GLEW_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
