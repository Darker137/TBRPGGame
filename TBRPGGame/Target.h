#ifndef TARGET_H
#define TARGET_H

#include "GeneralFunctions.h"

// Target class to handle target logic
class Target {
protected:
	Rectangle hitBox; // hitbox for the target
	Color color; // color of the target
	Texture2D texture; // texture for the target
	int multiplier; // multiplier for the fade effect

	bool isVisible; // Flag to check if the target is visible

	float fadeDuration; // Duration for the fade effect
	float fadeTimer; // Timer for the fade effect
public:
	Target(); // constructor
	~Target() { UnloadTexture(texture); } // destructor
	void Draw(); // Draw the target
	void Update(Rectangle* enemyHitbox); // Update the target position and fade effect

	//setters 
	void Hide() { isVisible = false; } // Hide the target
};

#endif