#ifndef MOUSE_H
#define MOUSE_H

#include "GeneralFunctions.h"

struct Mouse {
	Texture2D texture = LoadTexture("Resources/MousePointer.png");
	void Draw();
	// Destructor
	~Mouse() { UnloadTexture(texture); } // Unload the texture

};




#endif