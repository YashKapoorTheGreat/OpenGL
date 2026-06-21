cmake_minimum_required(VERSION 3.15)
project(opengl VERSION 1.0)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)
add_executable(${PROJECT_NAME} ${SOURCES} "libsrc/stbi_impl.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "build" RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed.")
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/libsrc/assimp)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)

set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")

# Force GLFW to build as a static library instead of a DLL
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/libsrc/glfw)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glew32s opengl32 gdi32 assimp)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC)
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
