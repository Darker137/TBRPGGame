#include "Mouse.h"

// Mouse class draw function
void Mouse::Draw() {
	Vector2 mousePos = GetMousePosition();
	DrawTextureEx(texture, { mousePos.x, mousePos.y}, 0.0f, 2.0f, WHITE);
}