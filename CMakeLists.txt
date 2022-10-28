cmake_minimum_required(VERSION 3.21)

project(nui-homepage VERSION 0.1.0)

# Nui Dependency
add_subdirectory(dependencies/Nui)
include (${CMAKE_CURRENT_LIST_DIR}/_cmake/common_options.cmake)

# Add executable (sources are added later, depending on frontend/backend)

set(PREJS_FILE ${CMAKE_SOURCE_DIR}/frontend/source/frontend/js/module.js)

if (EMSCRIPTEN)
    add_executable(nui-homepage)
    set_common_options(nui-homepage)

	# Link frontend of nui inside of emscripten
	target_link_libraries(nui-homepage PRIVATE nui-frontend)

    add_custom_target(
        nui-homepage-copy-wasm
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/bin/index.wasm ${CMAKE_BINARY_DIR}/../bin/index.wasm
        COMMAND stat -c %s ${CMAKE_BINARY_DIR}/bin/index.wasm | numfmt --to=iec
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        BYPRODUCTS ${CMAKE_BINARY_DIR}/../bin/index.wasm
    )
    add_dependencies(nui-homepage-copy-wasm nui-homepage-parcel)
  
	nui_prepare_emscripten_target(
		TARGET
			nui-homepage
        PARCEL_ARGS
            # --no-optimize
            --dist-dir=${CMAKE_BINARY_DIR}/../bin
		PREJS
			${PREJS_FILE}
        UNPACKED_MODE
            on
		EMSCRIPTEN_LINK_OPTIONS
            -sEXPORTED_FUNCTIONS=_frontendMain
            -O2
			-sALLOW_MEMORY_GROWTH=1 
            # -g
            # or other options, see emscripten docs.
        EMSCRIPTEN_COMPILE_OPTIONS
            -O3
            # -g
	)

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
         MAKE_OPTIONS
            nui-homepage nui-homepage-copy-wasm
     )
endif()