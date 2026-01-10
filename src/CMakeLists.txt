set(SRC_SOURCES
        main.cpp
        globals/globals.cpp
        globals/bottle/bottle.cpp
        globals/bottle/bottle.h
        kernel/drawer/BG/DrawerBG.cpp
        kernel/drawer/BG/DrawerBG.h
        kernel/drawer/Porals/DrawerPortals.cpp
        kernel/drawer/Porals/DrawerPortals.h
        kernel/polling/eventsPolling.cpp
        kernel/polling/eventsPolling.h
        kernel/drawer/UI/DrawerUI.cpp
        kernel/drawer/UI/DrawerUI.h
        kernel/drawer/MapObjs/DrawerMapObjs.cpp
        kernel/drawer/MapObjs/DrawerMapObjs.h
        kernel/drawer/MapEnemys/DrawerMapEnemys.cpp
        kernel/drawer/MapEnemys/DrawerMapEnemys.h
        kernel/drawer/Menu/DrawerMenu.cpp
        kernel/drawer/Menu/DrawerMenu.h
        kernel/drawer/Game/DrawerGame.cpp
        kernel/drawer/Game/DrawerGame.h
        kernel/drawer/redraw.cpp
        kernel/drawer/redraw.h
        kernel/updater/Game/UpdateGame.cpp
        kernel/updater/Game/UpdateGame.h
        kernel/updater/loadScreen/UpdaterLoadScreen.cpp
        kernel/updater/loadScreen/UpdaterLoadScreen.h
        kernel/updater/mainMenu/UpdaterMainMenu.cpp
        kernel/updater/mainMenu/UpdaterMainMenu.h
        kernel/updater/update.cpp
        kernel/updater/update.h
)

add_executable(knyaz_game ${SRC_SOURCES})

target_include_directories(knyaz_game PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/globals
        ${CMAKE_CURRENT_SOURCE_DIR}/knyaz
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

target_link_libraries(
        knyaz_game PRIVATE
        config
        ui_lib
        knyaz_lib
        resources_lib
        globals_lib
)

target_link_libraries(knyaz_game PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)

add_subdirectory(globals)
add_subdirectory(knyaz)
add_subdirectory(resources)
add_subdirectory(ui)