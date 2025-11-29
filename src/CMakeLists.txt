# НЕ вызываем project() снова; cmake_minimum_required не обязателен в субдиректории

# Список исходников из каталога src
set(SRC_SOURCES
        main.cpp
        globals/globals.cpp
        knyaz/knyaz.cpp
        resources/resources.cpp
        ui/ui.cpp
        types.h  # хедеры можно не включать, но это не критично
)

# Создаём понятный исполняемый таргет (не называйте его "src")
add_executable(knyaz_game ${SRC_SOURCES})

# подключаем include пути для поддиректорий, если нужно
target_include_directories(knyaz_game PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/globals
        ${CMAKE_CURRENT_SOURCE_DIR}/knyaz
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

# Линкуем локальную библиотеку config (она добавлена выше из root)
target_link_libraries(knyaz_game PRIVATE config)

# Линкуем SFML (импортированные цели)
target_link_libraries(knyaz_game PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)

# Если у вас есть локальные библиотеки как knyaz_lib, resources_lib и т.д. — добавим их как subdirs
add_subdirectory(globals)
add_subdirectory(knyaz)
add_subdirectory(resources)
add_subdirectory(ui)

# Если main зависит на эти библиотеки, можно их добавить в линковку:
# target_link_libraries(knyaz_game PRIVATE knyaz_lib resources_lib ui_lib)
