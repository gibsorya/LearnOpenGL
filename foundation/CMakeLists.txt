set(FOUNDATION_SOURCES
    error.c
)
add_library(foundation STATIC error.c)

target_include_directories(foundation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/external/SDL/include)
