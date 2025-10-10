get_filename_component(EXAMPLE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Define a variable for the shader directory relative to the source
set(SHADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${EXAMPLE_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Add a definition for the C++ code to use
target_compile_definitions(${EXAMPLE_NAME} PRIVATE
    SHADERS_DIR="${SHADERS_DIR}"
)

target_link_libraries(${EXAMPLE_NAME} PRIVATE foundation)

# Ensure foundation library uses the correct SHADERS_DIR for this target
target_compile_definitions(foundation PRIVATE SHADERS_DIR="${SHADERS_DIR}")
target_link_libraries(${EXAMPLE_NAME} PRIVATE SDL3::SDL3)

target_include_directories(${EXAMPLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${EXAMPLE_NAME} PUBLIC "${CMAKE_BINARY_DIR}")
target_include_directories(${EXAMPLE_NAME} PRIVATE "${OPENGL_INCLUDE_DIRS}")
target_link_libraries(${EXAMPLE_NAME} PRIVATE ${OPENGL_LIBRARIES} glm::glm)

# Add GLAD source file
target_sources(${EXAMPLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/glad/src/gl.c)
set_source_files_properties(${CMAKE_SOURCE_DIR}/external/glad/src/gl.c PROPERTIES LANGUAGE C)
