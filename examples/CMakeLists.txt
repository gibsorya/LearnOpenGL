cmake_minimum_required(VERSION 4.0.1)

message("SUB_DIRS: ${SUB_DIRS}")

set(TOTAL_SAMPLE_ID_LIST)

function(add_sub_dirs DIRECTORY)

    scan_dirs(DIR ${CMAKE_CURRENT_SOURCE_DIR} LIST SUB_DIRS)
    foreach (CURR_DIR ${SUB_DIRS})
message("CURR_DIR: ${CURR_DIR}")
        if (EXISTS "${DIRECTORY}/${CURR_DIR}/CMakeLists.txt")
            add_subdirectory(${DIRECTORY}/${CURR_DIR})
            list(APPEND TOTAL_SAMPLE_ID_LIST ${CURR_DIR})
        else ()
            add_sub_dirs(${DIRECTORY}/${CURR_DIR})
        endif ()
        set(TOTAL_SAMPLE_ID_LIST ${TOTAL_SAMPLE_ID_LIST} PARENT_SCOPE)
    endforeach ()
endfunction(add_sub_dirs)

add_sub_dirs(${CMAKE_CURRENT_SOURCE_DIR}/${SUB_DIR})
