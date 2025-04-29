#ifndef BATTLEINTERFACE_H
#define BATTLEINTERFACE_H

#include "GeneralFunctions.h"
#include "Player.h"
#include "Enemy.h"
#include "Target.h"

// forward declaration
enum AttackMode {
	PLAYER_NONE, 
	PLAYER_ATTACK,
	PLAYER_MAGIC,
	PLAYER_ITEM,
	PLAYER_RUN
};

// forward declaration
class Button {
protected:
	Rectangle hitBox; // hitbox for the button
	Texture texture; // texture for the button
	Color color; // color of the button
public:
	Button() : hitBox({ 0, 0, 0, 0 }), texture({ 0 }), color(WHITE) {}; // default constructor
	~Button() { UnloadTexture(texture); } // destructor
	void Draw(); // draw the button
	bool IsButtonPressed(Vector2* mousePos); // check if the button is pressed
	void SetColor(Color newColor) { color = newColor; } // set the color of the button
};

// attack button
class AttackButton : public Button { 
public:
	AttackButton(Vector2 location); // constructor
	void Action(Player* player, Enemy* enemy); // action for the attack button
};

// magic button
class MagicButton : public Button {
public:
	MagicButton(Vector2 location); // constructor
	void Action(Player* player, Enemy* enemy); // action for the magic button
};

// item button
class ItemButton : public Button {
public:
	ItemButton(Vector2 location); // constructor
	void Action(Player* player); // action for the item button
};

// run button
class RunButton : public Button {
public:
	RunButton(Vector2 location); // constructor
	void Action(Player* player); // action for the run button
};

// bar class
class Bar {
protected:
	Texture texture; // texture for the bar
	Texture iconTexture; // texture for the icon
	Rectangle hitBox; // hitbox for the bar
	Rectangle innerHitBox; // inner hitbox for the bar
	Color color; // color of the bar
	Color borderColor; // color of the border
	float barWidth; // width of the bar
public:
	Bar(const char* iconFile, Color barColor, Color barBorderColor, Vector2 location); // constructor
	~Bar() { UnloadTexture(texture); UnloadTexture(iconTexture); } // destructor
	void Draw(); // draw the bar
	void Update(float* amount, float* maxAmount); // update the bar

	//getters
	Rectangle* GetHitBox() { return &hitBox; } // get hitbox
};

// battle buttons class
class BattleButtons {
protected:
	Texture buttonBGTexture; // texture for the button background
	Rectangle buttonBGHitBox; // hitbox for the button background

	AttackButton* attackButton; // attack button
	MagicButton* magicButton; // magic button
	ItemButton* itemButton; // item button
	RunButton* runButton; // run button

	AttackMode attackMode; // current attack mode

	Target* target; // target for chosing indicator

	Texture2D attackTexture; // attack texture
	SpriteAnimation* attackAnimation; // attack animation
	Texture2D magicAttackTexture; // magic attack texture
	SpriteAnimation* magicAttackAnimation; // magic attack animation
	
public:
	BattleButtons(const Vector2* screenScale); // constructor
	~BattleButtons(); // destructor
	void Update(Player* player, vector<Enemy>* enemies, float* deltatime); // updates the details
	void Draw(); // draw the buttons and animations if necessary
	void ChooseEnemy(vector<Enemy>* enemies, Player* player); // choose an enemy to attack, set a target on enemy being hovered over

	//getters
	Rectangle* GetButtonBGHitBox() { return &buttonBGHitBox; } // get button background hitbox
};

// battle bars class
class BattleBars {
protected:
	Texture barBGTexture; // texture for the bar background
	Rectangle barBGHitBox; // hitbox for the bar background

	Bar* healthBar; // health bar
	Bar* manaBar; // mana bar
	Bar* activeBattleTimeBar; // active battle time bar
public:
	BattleBars(Rectangle* buttonBGHitBox); // constructor
	~BattleBars() { UnloadTexture(barBGTexture); delete healthBar; delete manaBar; delete activeBattleTimeBar; } // destructor
	void Update(Player* player); // update the bars
	void Draw(Player* player); // draw the bars
};

// battle UI class
class BattleUI { 
protected: 
	BattleButtons* battleButtons; // battle buttons
	BattleBars* battleBars; // battle bars
public:
	BattleUI(const Vector2* screenScale); // constructor
	~BattleUI() { delete battleButtons; delete battleBars; } // destructor
	void Update(Player* player, vector<Enemy>* enemies, float* deltatime); // update the battle UI
	void Draw(Player* player); // draw the battle UI
};


#endif