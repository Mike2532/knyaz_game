#include "./globals/globals.h"
#include "./globals/mapObjs/mapObjs.h"

void drawMapObjs() {
    for (const auto& obj : mapObjs) {
        window.draw(obj.body);
    }
}
