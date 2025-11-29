cmake_minimum_required(VERSION 3.10)
project(knyaz_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указать путь к cmake-модулям SFML (если у вас Homebrew)
set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")

# Найти SFML (в корне — чтобы поддиректории могли использовать цели)
find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

# Копируем медиа в бинарную папку
file(COPY ${CMAKE_SOURCE_DIR}/media DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Сначала добавляем библиотеки, которые экспортируют таргеты (config)
add_subdirectory(config)

# Теперь добавляем основной src — он будет линковаться с config и SFML
add_subdirectory(src)
