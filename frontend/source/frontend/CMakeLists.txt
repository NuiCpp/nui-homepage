target_sources(${PROJECT_NAME} 
    PRIVATE 
        main.cpp 
        main_page.cpp
        navigation_bar.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/frontend/include)