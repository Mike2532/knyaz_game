#include "./globals/globals.h"
#include "./resources/ui/ui.h"

void drawUI() {
    window.setView(UIView);
    window.draw(HpIndicatorSprite);

    window.draw(ui.focusOutline);
    window.draw(ui.focusFill);
    window.draw(ui.rageOutline);
    window.draw(ui.rageFill);
}