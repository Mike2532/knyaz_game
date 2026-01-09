set(SRC_SOURCES
        main.cpp
        globals/globals.cpp
        boss/bossType.cpp
        boss/bossType.h
        boss/initBoss.cpp
        boss/initBoss.h
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