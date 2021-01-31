cmake_minimum_required(VERSION 3.2)
project(fractal_renderer)

set(CMAKE_CXX_STANDARD 17)

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
message("##GLU##")
add_subdirectory(libs/glm)

############### GL3W #####################
message("##GL3W##")
add_subdirectory(libs/gl3w libs/gl3w)
include_directories(libs/gl3w/include/GL)


############### ASSIMP LOADER #####################
message("##ASSIMP##")
SET (ASSIMP_BUILD_TESTS CACHE BOOL OFF)
add_subdirectory(libs/assimp)


############### SAIL LOADER #####################
message("##SOIL##")
add_subdirectory(libs/Simple-OpenGL-Image-Library)

############### entt ############################
message("##ENTT##")
add_subdirectory(libs/entt)
include_directories(libs/entt/src)

################ DirectX 12 #####################
#message("##DIRECTX##")##
#find_path(directx D3d12.dll)
#find_path(directx_header D3d12.h)
#message("DirectX D3d12.h path: " ${directx_header})
#message("DirectX D3d12.dll path: " ${directx})
#
#include_directories(${directx_header})

############### COMMON FILES #################
message("##General Compilation##")
#file(GLOB COMMON_CPP "src/common/*.cpp")
#include_directories(src/common/ src/renderer src/general_components)
include_directories(src/renderer src/general_components)

############### MAIN TARGET ##################
add_library(components STATIC
        src/general_components/TransformComponent.cpp src/general_components/TransformComponent.h
        src/general_components/CameraComponent.cpp src/general_components/CameraComponent.h
        src/general_components/RegistryHierarchy.h src/general_components/RegistryHierarchy.cpp)
target_link_libraries(components glm)

add_library(renderer STATIC
        src/renderer/Renderer.cpp
        src/renderer/GLShader.cpp
        src/renderer/MeshComponent.cpp
        src/renderer/MaterialComponent.cpp
        src/renderer/LoadShader.cpp
        src/renderer/LightComponent.cpp
        src/renderer/Texture.cpp
        src/renderer/DirectionalLightComponent.cpp
        src/renderer/PointLightComponent.cpp)
target_link_libraries(renderer glfw gl3w glm assimp components SOIL ${OPENGL_LIBRARIES})

add_compile_definitions(NOMINMAX)
add_executable(main_app src/main.cpp)
target_link_libraries(main_app renderer components)




