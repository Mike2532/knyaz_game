add_library(globals_lib STATIC
        globals.cpp
        mapObjs/mapObjs.cpp
        mapObjs/mapObjs.h
        mapObjs/gameEntity/gameEntity.cpp
        mapObjs/gameEntity/gameEntity.h
        mapPortals/mapPortals.cpp
        mapPortals/mapPortals.h
        mapPortals/Portal.h
        mapEnemys/mapEnemys.cpp
        mapEnemys/mapEnemys.h
        AnimatedObj/AnimatedObj.cpp
        AnimatedObj/AnimatedObj.h
        AnimatedObj/AnimationData.h
        mapEnemys/Enemy/Enemy.cpp
        mapEnemys/Enemy/Enemy.h
        bottle/bottle.cpp
        bottle/bottle.h
        tpEntity/tpEntity.cpp
        tpEntity/tpEntity.h
)

target_include_directories(globals_lib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(globals_lib PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
)
