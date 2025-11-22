add_executable(mainGame main.cpp
        ../config/config.cpp
        ../config/config.h
        Models/GameState/GameState.cpp
        Models/Knyaz/Knyaz.cpp
        Models/MainMenu/MainMenu.cpp
        Models/GameState/GameState.h
        Models/Knyaz/Knyaz.h
        Models/MainMenu/MainMenu.h
        CommonElements/CommonElements.cpp
)
target_link_libraries(mainGame PRIVATE config)

get_filename_component(_sfml_prefix "${SFML_DIR}/../.." ABSOLUTE)
set(_sfml_include "${_sfml_prefix}/include")

target_include_directories(mainGame PRIVATE "${_sfml_include}")
target_link_libraries(mainGame PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

target_compile_features(mainGame PUBLIC cxx_std_17)