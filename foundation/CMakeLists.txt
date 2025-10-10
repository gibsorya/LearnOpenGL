add_library(foundation STATIC error.cpp shader.cpp pipeline.cpp vbo.cpp vao.cpp ebo.cpp)

target_include_directories(foundation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/external/SDL/include)

