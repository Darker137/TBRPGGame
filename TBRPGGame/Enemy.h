#ifndef ENEMY_H
#define ENEMY_H

#include "GeneralFunctions.h"
#include "Player.h"
#include "Animation.h"
#include "Attacks.h"

// EnemyData struct to hold enemy data
struct EnemyData {
	string name; // Name of the enemy
	float health; // Health of the enemy
	float speed; // Speed of the enemy
	float damage; // Damage dealt by the enemy
	float defence; // Defence of the enemy
	vector<AttackData*> attackData; // List of attacks

	void Print() { // Print enemy data
		cout << "Name: " << name << ", Health: " << health << ", Speed: " << speed
			<< ", Damage: " << damage << ", Defence: " << defence << endl;
		cout << "Attacks: ";
		for (const auto& attack : attackData) {
			attack->Print();
		}
		cout << endl;
	}
};

// EnemyTexture struct to hold enemy textures
struct EnemyTexture {
	Texture2D neutral; // Neutral texture
	Texture2D attack; // Attack texture
	Texture2D damage; // Damage texture

};

// EnemyState enum to hold enemy states
enum EnemyState {	
	NEUTRAL,
	ATTACKING,
	DAMAGED,
	DYING,
	DEAD
};

// EnemyState enum to hold mouse states for an enemy
enum MouseState {
	NONE,
	HOVERING,
	CLICKED
};

// Enemy class to handle enemy logic
class Enemy {
protected:
	string name; // Name of the enemy
	float health; // Current health of the enemy
	float maxHealth; // Maximum health of the enemy
	float speed; // Speed of the enemy
	float damage; // Damage dealt by the enemy
	float defence; // Defence of the enemy
	float level; // Level of the enemy
	vector<Attack*> attacks; // List of attacks

	EnemyTexture* texture; // Pointer to enemy texture
	Rectangle hitBox; // Hitbox for the enemy
	Vector2 origin; // Origin point for the enemy

	// ATB short for active time battle
	float ATBInterval; // time between actions
	float ATBTimer; // time since last action

	// Damage animation interval
	float damageAnimationDuration; // time for damage animation
	float damageAnimationTimer; // time since last damage animation

	// Attack animation interval
	float attackAnimationDuration; // time for attack animation
	float attackAnimationTimer; // time since last attack animation

	// death animation interval
	float deathAnimationDuration; // time for death animation
	float deathAnimationTimer; // time since last death animation

	bool animationPositive; // used to check if the animation is positive or negative
	EnemyState state;

	bool flash; // used to check if the enemy is flashing
	float flashingDuration; // time since last flashing
	float flashingTimer; // time since last flashing
	Color color; // color of the enemy

	AttackBanner* attackBanner; // attack banner for the enemy
	DamageDealtDisplay* damageDealtDisplay; // damage dealt display for the enemy

public:
	//constructor
	Enemy(EnemyData* enemyData, Vector2 position);
	//destructor
	~Enemy();

	//setters
	void SetTexture(EnemyTexture* enemyTexture, Texture2D* bannerTexture);

	//logic and draw 
	void Draw();
	void Update(Player* player, float* deltatime);
	void TakeDamage(int damage);
	MouseState IsChosen(Vector2* mousePos);

	//animation functions
	void NeutralAnimation(float* deltatime);
	void AttackAnimation(float* deltatime);
	void DamageAnimation(float* deltatime);
	void DeathAnimation(float* deltatime);

	void ReturnToOriginX(float* deltatime);
	// Getters
	string GetName() { return name; }
	float* GetHealth() { return &health; }
	float* GetMaxHealth() { return &maxHealth; }
	float* GetSpeed() { return &speed; }
	float* GetDamage() { return &damage; }
	float* GetDefence() { return &defence; }
	float* GetLevel() { return &level; }
	const EnemyState* GetState() const { return &state; }
	Rectangle* GetHitBox() { return &hitBox; }
};





#endif