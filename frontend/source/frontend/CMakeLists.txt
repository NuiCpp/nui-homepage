target_sources(${PROJECT_NAME} 
    PRIVATE 
        main.cpp 
        page_frame.cpp
        main_content.cpp
        navigation_bar.cpp
        example_card.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/frontend/include)