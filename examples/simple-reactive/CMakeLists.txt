cmake_minimum_required(VERSION 3.21)

project(simple-reactive VERSION 0.1.0)

# Add executable (sources are added later, depending on frontend/backend)

set(PREJS_FILE ${CMAKE_SOURCE_DIR}/frontend/source/frontend/js/module.js)

add_executable(simple-reactive)

if (EMSCRIPTEN)
    set_common_options(simple-reactive)

	# Link frontend of nui inside of emscripten
	target_link_libraries(simple-reactive PRIVATE nui-frontend)
  
	nui_prepare_emscripten_target(
		TARGET
			simple-reactive
        PARCEL_ARGS
            # --no-optimize
            --dist-dir=${CMAKE_BINARY_DIR}/../bin
		PREJS
			${PREJS_FILE}
        UNPACKED_MODE
            off
		EMSCRIPTEN_LINK_OPTIONS
            -sEXPORTED_FUNCTIONS=_frontendMain
            -O2
			-sALLOW_MEMORY_GROWTH=1 
            # -g -sNO_DISABLE_EXCEPTION_CATCHING
            # or other options, see emscripten docs.
        EMSCRIPTEN_COMPILE_OPTIONS
            -O3
            # -g
	)

    target_sources(simple-reactive PRIVATE front.cpp)
else() 
     # Creates a target that is compiled through emscripten. This target becomes the frontend part.
     nui_add_emscripten_target(simple-reactive
         TARGET
             simple-reactive
         PREJS 
             ${PREJS_FILE}
         SOURCE_DIR
             ${CMAKE_SOURCE_DIR}
         CMAKE_OPTIONS
     )

     target_sources(simple-reactive PRIVATE main.cpp)
endif()