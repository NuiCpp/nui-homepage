cmake_minimum_required(VERSION 3.21)

project(nui-template VERSION 0.1.0)

# Nui Dependency
include (${CMAKE_CURRENT_LIST_DIR}/_cmake/dependencies/nui.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/_cmake/common_options.cmake)

# Add executable (sources are added later, depending on frontend/backend)
add_executable(${PROJECT_NAME})
set_common_options(${PROJECT_NAME})

set(PREJS_FILE ${CMAKE_SOURCE_DIR}/frontend/source/frontend/js/module.js)

if (EMSCRIPTEN)
	# Link frontend of nui inside of emscripten
	target_link_libraries(${PROJECT_NAME} PRIVATE nui-frontend)
  
	nui_prepare_emscripten_target(
		TARGET
			${PROJECT_NAME}
        PARCEL_ARGS
            # --no-optimize
		PREJS
			${PREJS_FILE}
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
    # Link backend of nui outside of emscripten
    target_link_libraries(${PROJECT_NAME} PRIVATE nui-backend)

    nui_set_target_output_directories(${PROJECT_NAME})

    # Creates a target that is compiled through emscripten. This target becomes the frontend part.
	nui_add_emscripten_target(${PROJECT_NAME}
		TARGET
			${PROJECT_NAME}
		PREJS 
            ${PREJS_FILE}
		SOURCE_DIR
			${CMAKE_SOURCE_DIR}
		CMAKE_OPTIONS
            # I recommend to work with a release build by default because debug builds get big fast.
            -DCMAKE_BUILD_TYPE=Release
		MAKE_OPTIONS
			# VERBOSE=1
	)

	add_subdirectory(${CMAKE_SOURCE_DIR}/backend/source/backend)
endif()