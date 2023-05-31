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

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/frontend/include)