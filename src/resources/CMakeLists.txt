add_library(resources_lib resources.cpp resources.h)

target_link_libraries(resources_lib
        PUBLIC
        sfml-audio
        sfml-system
)
