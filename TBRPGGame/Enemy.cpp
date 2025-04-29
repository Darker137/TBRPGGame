#include "Enemy.h"

// Enemy class constructor
Enemy::Enemy(EnemyData* enemyData, Vector2 position) {
	name = enemyData->name; // Set the name of the enemy
	health = enemyData->health; // Set the current health of the enemy
	maxHealth = enemyData->health; // Set the maximum health of the enemy
	speed = enemyData->speed; // Set the speed of the enemy
	damage = enemyData->damage; // Set the damage of the enemy
	defence = enemyData->defence; // Set the defence of the enemy
	level = 1.0f; // Set the level to 1.0fs

	// Initialize the attacks
	for (auto& attack : enemyData->attackData) {
		attacks.push_back(new Attack(attack)); // Add the attack to the enemy's attack list
	}

	texture = nullptr; // Initialize texture to nullptrs
	hitBox = { position.x, position.y, 0, 0 }; // Initialize the hitbox
	origin = { 0, 0 }; // Initialize the origin point


	ATBInterval = 100.0f; // Set the interval to 1 second
	ATBTimer = 0.0f; // Initialize the timer

	damageAnimationDuration = 0.5f; // Set the duration to 0.5 seconds
	damageAnimationTimer = 0.0f; // Initialize the timer

	attackAnimationDuration = 0.5f; // Set the duration to 0.5 seconds
	attackAnimationTimer = 0.0f; // Initialize the timer

	deathAnimationDuration = 1.5f; // Set the duration to 0.5 seconds
	deathAnimationTimer = 0.0f; // Initialize the timer

	animationPositive = true; // Set the animation to positive
	state = NEUTRAL;

	flash = false; // Set the flashing state to false
	flashingDuration = 0.1f; // Set the duration to 0.5 seconds
	flashingTimer = 0.0f; // Initialize the timer
	color = WHITE; // Set the color to white

	attackBanner = nullptr; // Initialize the attack banner to nullptr
	damageDealtDisplay = nullptr; // Initialize the damage dealt display to nullptr
}

// Destructor for the Enemy class
Enemy::~Enemy() {
	attacks.clear(); // Clear the attack list
}

// Set the texture for the enemy
void Enemy::SetTexture(EnemyTexture* enemyTexture, Texture2D* bannerTexture) {
	texture = enemyTexture; // Set the texture for the enemy
	hitBox.width = (float)texture->neutral.width * 2.0f; // Set the width of the hitbox
	hitBox.height = (float)texture->neutral.height * 2.0f; // Set the height of the hitbox
	hitBox.x -= hitBox.width / 2; // Center the hitbox
	hitBox.y -= hitBox.height / 2; // Center the hitbox
	origin.x = hitBox.x; // Set the origin point
	origin.y = hitBox.y; // Set the origin point

	attackBanner = new AttackBanner(bannerTexture, { hitBox.x, 0 }); // Initialize the attack banner
	damageDealtDisplay = new DamageDealtDisplay(40.0f, { hitBox.x + hitBox.width / 2, hitBox.y + hitBox.height / 2 }); // Initialize the damage dealt display
}

// Draw the enemy
void Enemy::Draw() {

	// check the enemy state
	switch(state){

	case NEUTRAL: //if neutral draw with neutral texture
	{
		DrawTextureEx(texture->neutral, { hitBox.x, hitBox.y }, 0.0f, 2.0f, WHITE);
		break;
	}
	case ATTACKING: // if attacking draw with attack texture
	{
		DrawTextureEx(texture->attack, { hitBox.x, hitBox.y }, 0.0f, 2.0f, WHITE);
		break;
	}
	case DAMAGED: // if damaged draw with damage texture
	{
		DrawTextureEx(texture->damage, { hitBox.x, hitBox.y }, 0.0f, 2.0f, WHITE);
		break;
	}
	case DYING: // if dying also draw with damage texture
	{
		// if the enemy is flashing, draw with the flash color
		if (flash) {
			DrawTextureEx(texture->damage, { hitBox.x, hitBox.y }, 0.0f, 2.0f, color);
		}
		break;
	}
	}

	attackBanner->Draw(); // Draw the attack banner
	damageDealtDisplay->Draw(); // Draw the damage dealt display
}

// Update the enemy
void Enemy::Update(Player* player, float* deltatime) {

	attackBanner->Update(deltatime); // Update the attack banner
	damageDealtDisplay->Update(deltatime); // Update the damage dealt display
	switch (state)  // check the enemy state
	{
	case NEUTRAL: // if state is neutral
	{	
		ATBTimer += *deltatime * speed; // Increment the timer based on speed
		if (ATBTimer >= ATBInterval) { 
			// Perform action
			state = ATTACKING; // Set state to attacking
			ATBTimer = 0.0f; // Reset the timer
			// Perform attack logic here
			// Choose a random attack from the list
			while (true) {
				int randomAttack = rand() % attacks.size();
				if (attacks[randomAttack]->IsReady()) {
					// Perform the attack
					attackBanner->SetAttackName(attacks[randomAttack]->GetName());
					player->TakeDamage(&damage, &level, attacks[randomAttack]->GetDamage()); // Deal damage to the player
					cout << "Enemy: "<< name << " attacked player for " << *attacks[randomAttack]->GetDamage() << " damage with: " << *attacks[randomAttack]->GetName() << endl;
					break; // Exit the loop after performing the attack
				}
			}
		}

		for (auto& attack : attacks) {
			attack->Update(deltatime); // Update the attack cooldowns
		}

		ReturnToOriginX(deltatime); // Return to original position
		NeutralAnimation(deltatime); // Perform neutral animation
		// Perform neutral animation
		break;
	}
	case ATTACKING: // perform attack animation and update the attack timer
	{
		AttackAnimation(deltatime);
		// Perform attack animation
		attackAnimationTimer += *deltatime;
		if (attackAnimationTimer >= attackAnimationDuration) {
			state = NEUTRAL; // Reset to neutral state after attack
			attackAnimationTimer = 0.0f; // Reset the timer
		}
		break;
	}
	case DAMAGED: // perform damage animation and update the damage timer
	{
		DamageAnimation(deltatime);
		// Perform damage animation
		damageAnimationTimer += *deltatime;
		if (damageAnimationTimer >= damageAnimationDuration) {
			state = NEUTRAL; // Reset to neutral state after damage
			damageAnimationTimer = 0.0f; // Reset the timer
		}
		break;
	}
	case DYING: // perform death animation and update death timer
	{
		DeathAnimation(deltatime);
		// Perform death logic here
		deathAnimationTimer += *deltatime;
		if (deathAnimationTimer >= deathAnimationDuration) {
			state = DEAD; // Set state to dead
			// Reset the enemy or remove it from the game
		}
		break;
	}
	}
}

// Take damage from player
void Enemy::TakeDamage(int damage) {
	health -= damage; // Reduce health by damage
	cout << health << endl; // Print the current health
	if (health <= 0) { // Check if health is less than or equal to 0
		state = DYING; // Set state to dead
	}
	else { // If health is greater than 0
		state = DAMAGED; // Set state to damaged
	}
	damageDealtDisplay->SetDamage(damage); // Set the damage dealt display
}

// Check if the enemy is chosen by the mouse
MouseState Enemy::IsChosen(Vector2* mousePos) {
	// Check if the mouse is inside the hitbox
	if (IsMouseInRectangle(&hitBox, mousePos)) {
		// Check if the left mouse button is pressed
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			return CLICKED; // Return clicked state
		}
		else {
			return HOVERING; // Return hovering state
		}
	}
	else {
		return NONE; // Return none state
	}
}

// Set the color alpha for the enemy
void Enemy::NeutralAnimation(float* deltatime) {
	// Perform neutral animation
	// Move the hitbox up and down
	if (animationPositive) {
		hitBox.y += 10.0f * *deltatime; // Move the hitbox up
		if (hitBox.y >= origin.y + 10) { 
			animationPositive = false; // Change direction
		}
	}
	else {
		hitBox.y -= 10.0f * *deltatime; // Move the hitbox down
		if (hitBox.y <= origin.y) {
			animationPositive = true; // Change direction
		}
	}

}

// Set the color alpha for the enemy
void Enemy::AttackAnimation(float* deltatime) {
	// Perform attack animation
	if (animationPositive) {
		hitBox.x += 30.0f * *deltatime; // Move the hitbox right
		if (hitBox.x >= origin.x + 2) {
			animationPositive = false; // Change direction
		}
	}
	else {
		hitBox.x -= 30.0f * *deltatime; // Move the hitbox left
		if (hitBox.x <= origin.x - 2) {
			animationPositive = true; // Change direction
		}
	}
}

// Set the color alpha for the enemy
void Enemy::DamageAnimation(float* deltatime) {
	// Perform damage animation
	// Move the hitbox left and right
	if (animationPositive) {
		hitBox.x += 10.0f * *deltatime; // Move the hitbox right
		if (hitBox.x >= origin.x + 2) {
			animationPositive = false; // Change direction
		}
	}
	else {
		hitBox.x -= 10.0f * *deltatime; // Move the hitbox left
		if (hitBox.x <= origin.x - 2) {
			animationPositive = true; // Change direction
		}
	}
}

// Set the color alpha for the enemy
void Enemy::DeathAnimation(float* deltatime) {
	// Perform death animation
	// Move the hitbox up and down
	hitBox.y += 10.0f * *deltatime; // Move the hitbox up
	if (animationPositive) {
		hitBox.x += 30.0f * *deltatime; // Move the hitbox right
		if (hitBox.x >= origin.x + 2) {
			animationPositive = false; // Change direction
		}
	}
	else {
		hitBox.x -= 30.0f * *deltatime; // Move the hitbox left
		if (hitBox.x <= origin.x - 2) {
			animationPositive = true; // Change direction
		}
	}
	flashingTimer += *deltatime; // Increment the flashing timer
	if (flashingTimer >= flashingDuration) { 
		flash = !flash; // Toggle the flashing state
		flashingTimer = 0.0f; // Reset the timer
	}
	SetColorAlpha(&color, (1 - deathAnimationTimer / deathAnimationDuration)); // Set the color alpha based on the death animation timer
}

// Set the color alpha for the enemy
void Enemy::ReturnToOriginX(float* deltatime) {
	// Return to original position
	if (hitBox.x > origin.x) {
		hitBox.x -= 10.0f * *deltatime; // Move the hitbox left
	}
	else if (hitBox.x < origin.x) {
		hitBox.x += 10.0f * *deltatime; // Move the hitbox right
	}
}