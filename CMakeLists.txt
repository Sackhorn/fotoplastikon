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


############### ASSIMP LOADER #####################
add_subdirectory(libs/assimp)


############### SAIL LOADER #####################
add_subdirectory(libs/Simple-OpenGL-Image-Library)

############### COMMON FILES #################
file(GLOB COMMON_CPP "src/common/*.cpp")
include_directories(src/common/)

############### MAIN TARGET ##################
add_library(meshes src/common/StaticMesh.cpp src/common/StaticMesh.h)
target_link_libraries(meshes gl3w glm assimp ${OPENGL_LIBRARIES})

add_library(materials src/common/Shader.cpp src/common/Shader.h src/common/Material.cpp src/common/Material.h src/common/LoadShader.cpp src/common/LoadShader.hpp)
target_link_libraries(materials gl3w glm SOIL ${OPENGL_LIBRARIES})

add_executable(main_app src/main.cpp)
target_link_libraries(main_app meshes materials glfw gl3w glm ${OPENGL_LIBRARIES})




