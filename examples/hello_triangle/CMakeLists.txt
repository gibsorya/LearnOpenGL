get_filename_component(EXAMPLE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_executable(${EXAMPLE_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Define a variable for the shader directory relative to the source
set(SHADERS_DIR "${CMAKE_SOURCE_DIR}/shaders")

# Add a definition for the C++ code to use
target_compile_definitions(${EXAMPLE_NAME} PRIVATE
    SHADERS_DIR="${SHADERS_DIR}"
)

target_link_libraries(${EXAMPLE_NAME} PRIVATE foundation)

target_include_directories(${EXAMPLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
