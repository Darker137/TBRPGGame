#include "Target.h"

// Target class to handle target logic
Target::Target() {
	hitBox = { 0, 0, 0, 0 }; // Initialize the hitbox
	color = WHITE; // Set the color to white
	texture = LoadTexture("Resources/Target.png"); // Load the target texture
	multiplier = 1; // Set the multiplier for the fade effect
	hitBox.width = (float)texture.width * 2.0f; // Set the width of the hitbox
	hitBox.height = (float)texture.height * 2.0f; // Set the height of the hitbox

	isVisible = false; // Set the target to be invisible initially
	fadeDuration = 0.5f; // Set the fade duration to 0.5 seconds
	fadeTimer = 0.0f; // Initialize the fade timer
}

// draw the target
void Target::Draw() {
	// Check if the target is visible before drawing
	if (isVisible) {
		cout << "DRAWING TARGET" << endl; // Debug message
		DrawTextureEx(texture, { hitBox.x, hitBox.y }, 0.0f, 2.0f, color); // Draw the target texture
	}
}

// Update the target position and fade effect
void Target::Update(Rectangle* enemyHitbox) {
	isVisible = true; // Set the target to be visible
	hitBox.x = enemyHitbox->x + enemyHitbox->width / 2 - hitBox.width / 2; // Center the target on the enemy
	hitBox.y = enemyHitbox->y + enemyHitbox->height / 2 - hitBox.height / 2; // Center the target on the enemy

	fadeTimer += GetFrameTime() * multiplier; // Increment the fade timer
	if (fadeTimer >= fadeDuration || fadeTimer <= 0.0f) { 
		if (fadeTimer > fadeDuration) fadeTimer = fadeDuration; // cap the fade timer
		else if (fadeTimer < 0.0f) fadeTimer = 0.0f; // Reset the fade timer
		multiplier = -multiplier; // Reverse the multiplier to fade in and out
	}
	SetColorAlpha(&color, fadeTimer / fadeDuration); // Set the color alpha based on the fade timer
}