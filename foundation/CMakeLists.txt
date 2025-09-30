add_library(foundation STATIC error.cpp shader.cpp pipeline.cpp vbo.cpp vao.cpp)

target_include_directories(foundation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/external/SDL/include)

# Define SHADERS_DIR for the foundation library
set(SHADERS_DIR "${CMAKE_SOURCE_DIR}/src/shaders")
target_compile_definitions(foundation PRIVATE
    SHADERS_DIR="${SHADERS_DIR}"
)
