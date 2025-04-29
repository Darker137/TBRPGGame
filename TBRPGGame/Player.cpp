#include "Player.h"

// Player class constructor
Player::Player() {
	health = 100.0f; // Set the initial health to 100.0f
	maxHealth = 100.0f; // Set the maximum health to 100.0f
	mana = 50.0f; // Set the initial mana to 50.0f
	maxMana = 50.0f; // Set the maximum mana to 50.0f
	activeBattleTimeInterval = 2.5f; // Set the interval to 5 seconds
	activeBattleTimeTimer = 0.0f; // Initialize the timer
	defence = 30.0f; // Set the defence value
	damage = 20.0f; // Set the damage value
	magicDamage = 40.0f; // Set the magic damage value
	level = 1.0f; // Set the level to 1.0f

	isRunning = false; // Set the running state to false
}

// Check if the player is ready for the next turn
bool Player::TurnReady(float* deltatime) {
	// Check if the active battle time timer is less than the active battle time interval
	if (activeBattleTimeTimer < activeBattleTimeInterval) { //if not
		// Update the active battle time timer
		activeBattleTimeTimer += *deltatime;
		// Increment the timer by the delta time
		if (activeBattleTimeTimer > activeBattleTimeInterval) {
			activeBattleTimeTimer = activeBattleTimeInterval; // Clamp the timer to the interval
			return true; // Ready for the next turn
		}
		return false; // Not ready for the next turn
	}
	else {
		return true; // Ready for the next turn
	}
}

// Take damage from the enemy
void Player::TakeDamage(float* enemyDamage, float* enemyLevel, float* baseAttackDamage) {
	// Calculate damage dealt to the player
	health -= DamageCalculator(enemyDamage, enemyLevel, &defence, &level, baseAttackDamage);
	if (health < 0) {
		health = 0; // Ensure health doesn't go below 0
	}
}

// Heal the player
void Player::Heal(float amount) {
	health += amount; // Heal the player by the specified amount
	if (health > maxHealth) {
		health = maxHealth; // Ensure health doesn't exceed max health
	}
}