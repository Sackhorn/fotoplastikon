cmake_minimum_required(VERSION 3.2)
project(fractal_renderer)

set(CMAKE_CXX_STANDARD 11)

############### OpenGL######################
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

############### GLFW ##########################
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/glfw)
include_directories(libs/glfw/include)

############### GLM ###########################
add_subdirectory(libs/glm)

############### GL3W #####################
add_subdirectory(libs/gl3w)

############### COMMON FILES #################
file(GLOB COMMON_CPP "src/common/*.cpp")
include_directories(src/common/)

############### MAIN TARGET ##################
add_executable(main_app  src/main.cpp ${COMMON_CPP})
target_link_libraries(main_app glfw gl3w glm ${OPENGL_LIBRARIES})




