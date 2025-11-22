add_library(GameState GameState.cpp)

target_include_directories(GameState PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GameState PUBLIC sfml-window)