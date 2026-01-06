#include "./horizontal/horizontal.h"
#include "./vertical/vertical.h"
#include "../knyaz.h"

void knyazMove(const float& elapsedTime) {
    horizontalMove(elapsedTime);
    verticalMove();
}