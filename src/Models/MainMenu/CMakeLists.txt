add_library(MainMenu MainMenu.cpp)

target_include_directories(MainMenu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(MainMenu PUBLIC sfml-graphics)