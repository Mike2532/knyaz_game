#include "./horizontal/horizontal.h"
#include "./vertical/vertical.h"

void knyazMove(const float& elapsedTime) {
    horizontalMove(elapsedTime);
    verticalMove();
}