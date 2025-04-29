#include "Animation.h"

void SpriteAnimation::Update(float* deltatime) {
	if (!playing) return; // If not playing, do nothing
	frameTimer += *deltatime;
	if (frameTimer >= frameSpeed) {
		currentFrame += 1; // Move to the next frame
		frameTimer = 0.0f; // Reset the timer
		if (currentFrame >= frameCount) {
			if (loop) {
				currentFrame = 0; // Loop back to the first frame
			}
			else {
				Stop(); // Stop the animation
				Reset(); // Reset to the first frame
			}
		}
	}
}

// draw the current frame of the animation
void SpriteAnimation::Draw() {
	DrawTextureRec(*texture, GetFrameRec(), position, WHITE); // Draw the current frame
}

// set the details of the animation
void SpriteAnimation::SetDetails(Texture2D* texture, int frameCount, float frameSpeed, bool loop, bool play){
	// set the details of the animation
	this->texture = texture;
	this->frameCount = frameCount;
	this->frameSpeed = frameSpeed;
	this->loop = loop;

	frameWidth = (float)texture->width / frameCount; // calculate the width of each frame
	frameHeight = (float)texture->height; // calculate the height of each frame
}

// set the position of the animation
void SpriteAnimation::SetPosition(Vector2 center) {
	position = { center.x - frameWidth / 2, center.y - frameHeight / 2 }; // set the position based on the given center position 
}