add_library(globals_lib STATIC
        globals.cpp
)

target_include_directories(globals_lib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(globals_lib PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
)
