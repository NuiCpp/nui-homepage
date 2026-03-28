cmake_minimum_required(VERSION 3.21)

project(nui-homepage VERSION 0.1.0)

# Nui Dependency
add_subdirectory(dependencies/Nui)
include (${CMAKE_CURRENT_LIST_DIR}/_cmake/common_options.cmake)

# add_subdirectory(examples/simple-reactive)

# Add executable (sources are added later, depending on frontend/backend)

set(PREJS_FILE ${CMAKE_SOURCE_DIR}/frontend/source/frontend/js/module.js)

if (EMSCRIPTEN)
    add_executable(nui-homepage)

    add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/5cript-nui-components)
    add_subdirectory(${CMAKE_SOURCE_DIR}/frontend/source/frontend)
else()
    add_library(nui-homepage INTERFACE)

     # Creates a target that is compiled through emscripten. This target becomes the frontend part.
     nui_add_emscripten_target(nui-homepage
         TARGET
             nui-homepage
         PREJS
             ${PREJS_FILE}
         SOURCE_DIR
             ${CMAKE_SOURCE_DIR}
         CMAKE_OPTIONS
     )
endif()