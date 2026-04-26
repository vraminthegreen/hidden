#include "Input.h"

bool Input::IsLightningStrikePressed() {
    return IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
}

Vector2 Input::GetMousePos() {
    return GetMousePosition();
}
