add_library(ui_lib ui.cpp ui.h)

target_link_libraries(ui_lib
        PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
)
