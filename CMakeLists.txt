cmake_minimum_required(VERSION 4.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(LearnOpenGL VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(external/SDL EXCLUDE_FROM_ALL)

configure_file(version.h.in version.h)

find_package(OpenGL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/external/glad/include ${CMAKE_SOURCE_DIR}/external/stb})

file(GLOB BUTTERFLIES_SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR} *.c external/glad/src/gl.c)

add_subdirectory(foundation)

add_executable(${PROJECT_NAME} "src/main.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC foundation)

# Define a variable for the shader directory relative to the source
set(SHADERS_DIR "${CMAKE_SOURCE_DIR}/src/shaders")

# Add a definition for the C++ code to use
target_compile_definitions(${PROJECT_NAME} PRIVATE
    SHADERS_DIR="${SHADERS_DIR}"
)

target_sources(${PROJECT_NAME} PRIVATE external/glad/src/gl.c)
set_source_files_properties(external/glad/src/gl.c PROPERTIES LANGUAGE C)

include(FetchContent)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${OPENGL_INCLUDE_DIRS}")
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES} glm::glm)
