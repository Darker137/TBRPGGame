#ifndef ATTACKS_H
#define ATTACKS_H

#include "GeneralFunctions.h"

// AttackData struct to hold attack data
struct AttackData {
	string name; // name of the attack
	float damage; // damage dealt by the attack
	float cooldown; // cooldown time of the attack

	void Print() { // Print attack data
		cout << "Attack: " << name << ", Damage: " << damage << ", Cooldown: " << cooldown << endl;
	}
};

// Attack class to handle attack logic
class Attack {
protected: 
	AttackData* attackData; //pointer to attack Data
	float cooldownTimer = 0; // time since last attack
public:
	Attack(AttackData* attackData); // constructor
	void Update(float* deltatime); // update the cooldown timer
	bool IsReady(); // check if the attack is ready
	void SetCooldown(); // reset the cooldown timer

	//getters
	AttackData* GetAttackData() { return attackData; }
	float* GetCooldown() { return &cooldownTimer; }
	float* GetDamage() { return &attackData->damage; }
	string* GetName() { return &attackData->name; }

};

// AttackBanner class to display the attack name
class AttackBanner {
protected:
	bool isVisible = false; // Flag to check if the banner is visible
	Texture2D* texture; // Texture for the banner
	Rectangle hitBox; // Hitbox for the banner
	string* attackName = 0; // Attack name to display

	float fontSize; // Font size for the text
	Vector2 textPosition; // Position for the text

	float showDuration = 1.0f; // Duration to show the attack name
	float showTimer = 0.0f; // Timer to track the duration

public:
	//constructor
	AttackBanner(Texture2D* bannerTexture, Vector2 position);
	//destructor
	~AttackBanner();
	//default constructor
	AttackBanner() : texture(nullptr), hitBox({ 0, 0, 0, 0 }), attackName(nullptr), fontSize(0), textPosition({ 0, 0 }) {} // default constructor
	void Draw(); // Draw the attack banner
	void Update(float* deltatime); // Update the attack banner
	void SetAttackName(string* name); // Set the attack name
};

class DamageDealtDisplay {
protected:
	float fontSize; // Font size for the text
	Vector2 textPosition = { 0,0 }; // Position for the text
	Vector2 textOrigin; // Origin for the text
	float showDuration = 2.0f; // Duration to show the attack name
	float showTimer = 0.0f; // Timer to track the duration
	float damage = 0.0f; // Damage dealt
	bool isVisible = false; // Flag to check if the banner is visible
	Color color = WHITE; // Color of the text
public:
	DamageDealtDisplay(float fontSize, Vector2 textOrigin) : fontSize(fontSize), textOrigin(textOrigin) {} // constructor
	void Draw(); // Draw the damage dealt display
	void Update(float* deltatime); // Update the damage dealt display
	void SetDamage(float damage); // Set the damage dealt
};

#endif