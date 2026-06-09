cmake_minimum_required(VERSION 3.10)
project(opengl VERSION 1.0)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp res/*)
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "build" RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed.")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw3 glew32s.lib opengl32 gdi32)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
