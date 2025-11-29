add_library(knyaz_lib
        knyaz.cpp
)

target_include_directories(knyaz_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Линкуем SFML цели (они найдены в корне, будут видны)
target_link_libraries(knyaz_lib PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
)
