#ifndef GENERALFUNCTONS_H  
#define GENERALFUNCTONS_H  

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> 
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <map>
#include "raylib.h"  
#include "string"

using namespace std;


// forward declaration
struct Background {
	Texture2D texture;
	void Draw();
	//destructor
	~Background() { UnloadTexture(texture); } // destructor
};

void DrawBackingGridCheckers(); //draws the backing grid for testing

void MakeFullScreen(const Vector2* windowedSize, Vector2* screenScale, float* virtualScalng); //sets the game to full screen

bool IsMouseInRectangle(Rectangle* rect, Vector2* mousePs); //checks if the mouse is in a rectangle

int DamageCalculator(float* attackerDamage, float* attackerLevel, float* targetDefence, float* targetLevel, float* baseAttackDamage); //calculates the damage dealt to the target

void SetColorAlpha(Color* color, float percentage); //reduces the alpha of a color by a percentage
#endif