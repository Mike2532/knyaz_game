add_library(knyaz_lib
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
        move/move.cpp
        move/move.h
        move/vertical/vertical.cpp
        move/vertical/vertical.h
        move/horizontal/horizontal.cpp
        move/horizontal/horizontal.h
        move/collisionChecker/checker.cpp
        move/collisionChecker/checker.h
        move/falling/falling.cpp
        move/falling/falling.h
        state/state.cpp
        state/state.h
        knyaz.h
        knyaz.cpp
)

target_include_directories(knyaz_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(knyaz_lib PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
)
