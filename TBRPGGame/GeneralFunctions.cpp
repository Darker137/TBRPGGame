#include "GeneralFunctions.h"

// Background class to handle background logic
void Background::Draw() {
	DrawTextureEx(texture, { 0, 0 }, 0.0f, 2.0f, WHITE); // Draw the background texture
}

// Update function for the background
void DrawBackingGridCheckers() { //draws the backing grid for testing
	for (int i = 0; i < 1280; i += 20)
	{
		for (int j = 0; j < 720; j += 20)
		{
			if ((i / 20 + j / 20) % 2 == 0)
			{
				DrawRectangle(i, j, 20, 20, RAYWHITE);
			}
			else
			{
				DrawRectangle(i, j, 20, 20, GRAY);
			}
		}
	}
}

void MakeFullScreen(const Vector2* windowedSize, Vector2* screenScale, float* virtualScaling) { //sets the game to full screen
	// Check if the F11 key is pressed to toggle fullscreen
	if (IsKeyPressed(KEY_F11)) {
		if (IsWindowFullscreen()) {
			ToggleFullscreen();
			SetWindowSize(windowedSize->x, windowedSize->y);
			*virtualScaling = 1.0f; // Reset the virtual scaling factor
			screenScale->x = windowedSize->x;
			screenScale->y = windowedSize->y;
		}
		else {
			ToggleFullscreen();
			screenScale->x = (float)GetMonitorWidth(0);
			screenScale->y = (float)GetMonitorHeight(0);
			*virtualScaling = screenScale->x / windowedSize->x; // Calculate the virtual scaling factor
		}
	}
}

// Check if the mouse is in a rectangle
bool IsMouseInRectangle(Rectangle* rect, Vector2* mousePs) {
	if (mousePs->x > rect->x && mousePs->x < rect->x + rect->width &&
		mousePs->y > rect->y && mousePs->y < rect->y + rect->height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Check if the mouse is in a rectangle
int DamageCalculator(float* attackerDamage, float* attackerLevel, float* targetDefence, float* targetLevel, float* baseAttackDamage) { //calculates the damage dealt to the target
	
	float averageDamage = (*attackerDamage + *baseAttackDamage) / 2.0f; // calculate average damage
	
	float attackerScale = (1.0f + pow(averageDamage, 1.2f) * 0.03f) * averageDamage; // calculate attacker damage scaled to level
	float targetScale = (1.0f + pow(*attackerLevel, 1.2f) * 0.03f) * *targetDefence; // calculate target defence scaled to level

	// Calculate and return damage based on the difference between attacker and target scales with a random factor
	float damage = (attackerScale * (attackerScale / (attackerScale + targetScale))) * ((float)(rand() % 21) / 100.0f + 0.9f);
	if (damage < 1.0f) {
		damage = 1.0f; // Ensure minimum damage is 1
	}
	//make a full number
	damage = floor(damage);
	return (int)damage;
}

void SetColorAlpha(Color* color, float percentage) { // sets the alpha of a color by a percentage

	color->a = (unsigned char)(255 * percentage); // Set the alpha value based on the percentage
}