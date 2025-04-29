#include "Attacks.h"

// AttackData struct to hold attack data
Attack::Attack(AttackData* attackData) : attackData(attackData) {
	cooldownTimer = attackData->cooldown; // Initialize cooldown timer
}

// Attack class to handle attack logic
void Attack::Update(float* deltatime) {
	// update the cooldown timer
	if (cooldownTimer > 0) {
		cooldownTimer -= *deltatime; // Decrease the cooldown timer
	}
	else {
		cooldownTimer = 0; // Clamp the cooldown timer to 0
	}
}

// check if the attack is ready
bool Attack::IsReady() {
	return cooldownTimer <= 0; // Check if the cooldown timer is less than or equal to 0
}

// reset the cooldown timer
void Attack::SetCooldown() {
	cooldownTimer = attackData->cooldown; // Reset the cooldown timer
}

// AttackBanner class to display the attack name
AttackBanner::AttackBanner(Texture2D* bannerTexture, Vector2 position) {

	texture = bannerTexture; // Set the texture for the banner
	hitBox = { position.x, position.y, (float)texture->width * 2.0f, (float)texture->height * 2.0f }; // Set the hitbox for the banner
	fontSize = hitBox.height - 16; // Set the font size for the text
	textPosition = { 0,0 }; // Initialize the text position

}

// Destructor for AttackBanner
AttackBanner::~AttackBanner() {
	// Clean up the texture and other resources
	if (texture) {
		UnloadTexture(*texture); // Unload the texture if it was loaded
	}
}

// drawing the attack banner
void AttackBanner::Draw() {
	if (!isVisible) return; // Don't draw if not visible
	if (!attackName) return; // Don't draw if attack name is not set
	DrawTextureEx(*texture, { hitBox.x, hitBox.y }, 0.0f, 2.0f, WHITE); // Draw the banner texture
	DrawText(attackName->c_str(), textPosition.x, textPosition.y, fontSize, WHITE); // Draw the attack name text
}

// Update the attack banner
void AttackBanner::Update(float* deltatime) { 
	if (showTimer < showDuration) {
		showTimer += *deltatime; // Increment the timer
	}
	else {
		showTimer = showDuration; // Clamp the timer to the duration
	}
	if (showTimer == showDuration) {
		isVisible = false; // Hide the banner after the duration
	}
	else {
		isVisible = true; // Show the banner while the timer is active
	}
}

// Set the attack name for the banner
void AttackBanner::SetAttackName(string* name) {
	attackName = name; // Set the attack name
	textPosition.x = hitBox.x + (hitBox.width - MeasureText(attackName->c_str(), fontSize)) / 2; // Center the text
	textPosition.y = hitBox.y + (hitBox.height - fontSize) / 2; // Center the text vertically
	showTimer = 0.0f; // Reset the timer
}

// DamageDealtDisplay class to display the damage dealt draw function
void DamageDealtDisplay::Draw() {
	if (isVisible) { // Only draw if visible
		// draw the damage dealt text
		DrawText(std::to_string((int)damage).c_str(), textPosition.x, textPosition.y, fontSize, color);
	}
}

// Update the damage dealt display
void DamageDealtDisplay::Update(float* deltatime) {
	// Update the damage dealt display
	if (showTimer < showDuration) {
		showTimer += *deltatime; // Increment the timer
		if (showTimer > showDuration) showTimer = showDuration; // Clamp the timer to the duration
		if (showTimer > 1.0f) {
			SetColorAlpha(&color, 1 - ((showTimer - 1) / (showDuration - 1))); // Fade out the color
		}
		textPosition.y -= (*deltatime * 50); // Move the text up
	}
	else {
		showTimer = showDuration; // Clamp the timer to the duration
	}
	if (showTimer == showDuration) {
		isVisible = false; // Hide the banner after the duration
	}
	else {
		isVisible = true; // Show the banner while the timer is active
	}
}

// runtime constructor for DamageDealtDisplay
void DamageDealtDisplay::SetDamage(float damage) {
	this->damage = damage; // Set the damage dealt
	textPosition.x = textOrigin.x - MeasureText(std::to_string((int)damage).c_str(), fontSize) / 2; // Center the text
	textPosition.y = textOrigin.y - fontSize * 4; // Center the text vertically
	showTimer = 0.0f; // Reset the timer
	color = WHITE; // Reset the color
}