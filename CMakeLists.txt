cmake_minimum_required(VERSION 3.8)
project(opengl VERSION 1.0)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed.")
endif()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)
add_executable(${PROJECT_NAME} ${SOURCES} "libsrc/stbi_impl.cpp")

set(UNIVERSAL_OUT_DIR "${CMAKE_SOURCE_DIR}/out")

set_target_properties(${PROJECT_NAME} PROPERTIES 
    OUTPUT_NAME "build" 
    RUNTIME_OUTPUT_DIRECTORY ${UNIVERSAL_OUT_DIR}
)

set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Disable Assimp tests" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Disable Assimp tools" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "Disable Assimp installation" FORCE)
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build Assimp as DLL" FORCE) 
add_subdirectory("${CMAKE_SOURCE_DIR}/libsrc/assimp")


set_target_properties(assimp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${UNIVERSAL_OUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${UNIVERSAL_OUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${UNIVERSAL_OUT_DIR}"
)


# Force GLFW to build as a static library instead of a DLL
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/libsrc/glfw)


set_target_properties(glfw PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${UNIVERSAL_OUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${UNIVERSAL_OUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${UNIVERSAL_OUT_DIR}"
)


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE 
    GLEW_STATIC 
    "SOURCE_DIR=\"${CMAKE_SOURCE_DIR}\""
)
target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/lib")
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw 
    glew32s 
    opengl32 
    gdi32 
    assimp
)

# target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
