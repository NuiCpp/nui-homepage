target_sources(${PROJECT_NAME}
    PRIVATE
        about.cpp
        main.cpp
        page_frame.cpp
        main_content.cpp
        navigation_bar.cpp
        cards/attribute_card.cpp
        cards/simple_reactive_card.cpp
        cards/function_component_card.cpp
        cards/conditional_rendering_card.cpp
        cards/basic_card.cpp
        cards/list_card.cpp
)

set_common_options(nui-homepage)

# Link frontend of nui inside of emscripten
target_link_libraries(nui-homepage PRIVATE nui-frontend fmt)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/frontend/include)

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
        # -g -sNO_DISABLE_EXCEPTION_CATCHING
        # or other options, see emscripten docs.
    EMSCRIPTEN_COMPILE_OPTIONS
        -O3
        # -g
    OBSERVED_BUNDLE_FILES
        "${CMAKE_SOURCE_DIR}/static/styles/page_content.scss"
        "${CMAKE_SOURCE_DIR}/static/styles/responsive.scss"
        "${CMAKE_SOURCE_DIR}/static/styles/navbar.scss"
        "${CMAKE_SOURCE_DIR}/static/styles/main.scss"
        "${CMAKE_SOURCE_DIR}/static/styles/card.scss"
        "${CMAKE_SOURCE_DIR}/static/styles/bootstrap.scss"
        "${CMAKE_SOURCE_DIR}/static/styles/about.scss"
)