#ifndef PLAYER_H
#define PLAYER_H

#include "GeneralFunctions.h"

// Player class to handle player logic
class Player {
protected:
	float health; // current health of the player
	float maxHealth; // maximum health of the player
	float mana; // current mana of the player
	float maxMana; // maximum mana of the player
	float activeBattleTimeInterval; // time between actions
	float activeBattleTimeTimer; // time since last action
	float defence; // defence of the player
	float damage; // damage dealt by the player
	float magicDamage; // magic damage dealt by the player
	float level; // level of the player

	bool isRunning; // flag to check if the player is running

public:
	Player(); // constructor
	bool TurnReady(float* deltatime); // check if the player is ready for the next turn
	void TakeDamage(float* enemyDamage, float* enemyLevel, float* baseAttackDamage); // take damage from the enemy
	void Heal(float amount); // heal the player
	void SetRun(bool run) { isRunning = run; } // set the run state

	// getters
	float* GetHealth() { return &health; } // get current health
	float* GetMaxHealth() { return &maxHealth; } // get maximum health
	float* GetMana() { return &mana; } // get current mana
	float* GetMaxMana() { return &maxMana; } // get maximum mana
	float* GetActiveBattleTimeInterval() { return &activeBattleTimeInterval; } // get active battle time interval
	float* GetActiveBattleTimeTimer() { return &activeBattleTimeTimer; } // get active battle time timer
	float* GetDamage() { return &damage; } // get damage dealt by the player
	float* GetMagicDamage() { return &magicDamage; } // get magic damage dealt by the player
	float* GetLevel() { return &level; } // get level of the player
	float* GetDefence() { return &defence; } // get defence of the player
	bool GetIsRunning() { return isRunning; } // check if the player is running
};

#endif