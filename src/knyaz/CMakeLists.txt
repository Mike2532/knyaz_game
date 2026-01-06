add_library(knyaz_lib
        knyaz.cpp
        eventsHandler/eventsHandler.cpp
        eventsHandler/eventsHandler.h
        eventsHandler/keyboard/keyboardHandler.cpp
        eventsHandler/keyboard/keyboardHandler.h
        eventsHandler/mouse/mouseHandler.cpp
        eventsHandler/mouse/mouseHandler.h
        eventsHandler/mouse/left/left.cpp
        eventsHandler/mouse/left/left.h
        eventsHandler/mouse/right/right.cpp
        eventsHandler/mouse/right/right.h
)

target_include_directories(knyaz_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(knyaz_lib PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
)
