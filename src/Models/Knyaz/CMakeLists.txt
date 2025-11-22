add_library(Knyaz Knyaz.cpp)

target_include_directories(Knyaz PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Knyaz PUBLIC sfml-graphics)