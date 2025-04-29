#ifndef ANIMATION_H
#define ANIMATION_H

#include "GeneralFunctions.h"

struct SpriteAnimation {
	Texture2D* texture; // sprite sheet
	Vector2 position = { 0,0 };
	int frameCount; // number of frames in the animation
	int currentFrame = 0; // current frame of the animation
	float frameWidth; // width of each frame
	float frameHeight; // height of each frame
	float frameSpeed; // time per frame
	float frameTimer = 0; // time since last frame

	bool loop; // if the animation should loop
	bool playing; // if the animation is playing

	
	Rectangle GetFrameRec() const { return { currentFrame * frameWidth, 0, frameWidth, frameHeight }; }; // get the rectangle of the current frame
	
	void Update(float* deltatime); // update the animation

	void Draw(); // draw the animation


	//setters
	void SetDetails(Texture2D* texture, int frameCount, float frameSpeed, bool loop, bool play);
	void Play() { playing = true; } // Start the animation
	void Stop() { playing = false; } // Stop the animation
	void Reset() { currentFrame = 0; } // Reset the animation to the first frame
	void SetPosition(Vector2 center); // Set the position of the animation
};

#endif