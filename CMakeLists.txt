cmake_minimum_required(VERSION 3.10)
project(knyaz_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

file(COPY media DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(config)