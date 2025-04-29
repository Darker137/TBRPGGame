#include "BattleInterface.h"

// Button class draw
void Button::Draw() {
	DrawTextureEx(texture, { hitBox.x, hitBox.y }, 0.0f, 2.0f, color); // Draw the button texture
}

// Check if the button is pressed
bool Button::IsButtonPressed(Vector2* mousePos) {
	// Check if the mouse is inside the button hitbox
	if (IsMouseInRectangle(&hitBox, mousePos)) {
		// Check if the left mouse button is pressed
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			color = WHITE; // Set the color to white when pressed
			return true; // Button is pressed
		}
		else {
			color = LIGHTGRAY; // Set the color to light gray when hovering
			return false; // Button is not pressed
			
		}
	}
	else { 
		color = WHITE; // Set the color to white when not hovering
		return false; // Button is not pressed
	}
}

// Set the color of the button
AttackButton::AttackButton(Vector2 location) {
	texture = LoadTexture("Resources/UIButtonAttack.png"); // Load the attack button texture
	color = WHITE; // Set the color to white
	hitBox = { location.x, location.y, (float)texture.width * 2.0f, (float)texture.height * 2.0f }; // Set the hitbox for the button
}

void AttackButton::Action(Player* player, Enemy* enemy) {
	// Implement the action for the attack button
	// For example, deal damage to the enemy
	enemy->TakeDamage(DamageCalculator(player->GetDamage(), player->GetLevel(), enemy->GetDefence(), enemy->GetLevel(), player->GetDamage())); // Calculate damage dealt to the enemy
	*player->GetActiveBattleTimeTimer() = 0.0f; // Reset the active battle time timer

}

// Magic button class
MagicButton::MagicButton(Vector2 location) {
	texture = LoadTexture("Resources/UIButtonMagic.png"); // Load the magic button texture
	color = WHITE; // Set the color to white
	hitBox = { location.x, location.y, (float)texture.width * 2.0f, (float)texture.height * 2.0f }; // Set the hitbox for the button

}

void MagicButton::Action(Player* player, Enemy* enemy) {
	// Implement the action for the magic button
	// For example, deal magic damage to the enemy
	enemy->TakeDamage(DamageCalculator(player->GetMagicDamage(), player->GetLevel(), enemy->GetDefence(), enemy->GetLevel(), player->GetMagicDamage())); // Calculate magic damage dealt to the enemy
	*player->GetMana() -= 10.0f; // Deduct mana cost
	*player->GetActiveBattleTimeTimer() = 0.0f; // Reset the active battle time timer
}

// Item button class
ItemButton::ItemButton(Vector2 location) {
	texture = LoadTexture("Resources/UIButtonHeal.png"); // Load the item button texture
	color = WHITE; // Set the color to white
	hitBox = { location.x, location.y, (float)texture.width * 2.0f, (float)texture.height * 2.0f }; // Set the hitbox for the button
}

// Action for the item button
void ItemButton::Action(Player* player) {
	// Implement the action for the item button
	// For example, heal the player
	player->Heal(30.0f); // Heal the player by 30 health points
	*player->GetActiveBattleTimeTimer() = 0.0f; // Reset the active battle time timer
}

// Run button class
RunButton::RunButton(Vector2 location) {
	texture = LoadTexture("Resources/UIButtonRun.png"); // Load the run button texture
	color = WHITE; // Set the color to white
	hitBox = { location.x, location.y, (float)texture.width * 2.0f, (float)texture.height * 2.0f }; // Set the hitbox for the button
}

// Action for the run button
void RunButton::Action(Player* player) {
	// Implement the action for the run button
	// For example, attempt to flee from battle
	// Flee logic goes here
	// demo logic
	player->SetRun(true); // Set the player to running state
}

// bar class constructor
Bar::Bar(const char* iconFile, Color barColor, Color barBorderColor, Vector2 location) {
	texture = LoadTexture("Resources/UIBar.png"); // Load the bar texture
	iconTexture = LoadTexture(iconFile); // Load the icon texture
	hitBox = { location.x, location.y, (float)texture.width * 2.0f, (float)texture.height * 2.0f }; // Set the hitbox for the bar
	innerHitBox = { location.x + 4, location.y + 4, (float)texture.width * 2.0f - 4, (float)texture.height * 2.0f - 8 }; // Set the inner hitbox for the bar
	color = barColor; // Set the color of the bar
	borderColor = barBorderColor; // Set the border color of the bar
	barWidth = innerHitBox.width; // Set the width of the bar
}

// draw the bar class	
void Bar::Draw() {
	DrawTextureEx(iconTexture, { hitBox.x - 20, hitBox.y }, 0.0f, 2.0f, WHITE); // Draw the icon texture
	DrawRectangle(innerHitBox.x, innerHitBox.y, innerHitBox.width, innerHitBox.height, color); // Draw the inner hitbox
	DrawRectangleLinesEx(innerHitBox, 2, borderColor); // Draw the border of the inner hitbox
	DrawTextureEx(texture, { hitBox.x, hitBox.y }, 0.0f, 2.0f, WHITE); // Draw the bar texture
}

// Update the bar class
void Bar::Update(float* amount, float* maxAmount) {
	innerHitBox.width = (*amount / *maxAmount) * barWidth; // Update the width of the inner hitbox based on the amount and max amount
}

// battle buttons class constructor
BattleButtons::BattleButtons(const Vector2* screenScale) {
	buttonBGTexture = LoadTexture("Resources/UIButtonBase.png"); // Load the button background texture
	buttonBGHitBox = { 0,0,0,0 }; // Initialize the button background hitbox
	buttonBGHitBox.width = (float)buttonBGTexture.width * 2.0f; // Set the width of the button background hitbox
	buttonBGHitBox.height = (float)buttonBGTexture.height * 2.0f; // Set the height of the button background hitbox
	buttonBGHitBox.y = screenScale->y - buttonBGHitBox.height; // Set the y position of the button background hitbox

	attackButton = new AttackButton({ buttonBGHitBox.x + 20, buttonBGHitBox.y + 20 }); // Initialize the attack button
	magicButton = new MagicButton({ buttonBGHitBox.x + 20 + 120 + 20, buttonBGHitBox.y + 20 }); // Initialize the magic button 
	itemButton = new ItemButton({ buttonBGHitBox.x + 20, buttonBGHitBox.y + 20 + 60 + 20 }); // Initialize the item button
	runButton = new RunButton({ buttonBGHitBox.x + 20 + 120 + 20, buttonBGHitBox.y + 20 + 60 + 20 }); // Initialize the run button

	attackMode = PLAYER_NONE; // Set the attack mode to none

	target = new Target(); // Initialize the target for choosing indicator

	attackTexture = LoadTexture("Resources/PlayerAttack.png"); // Load the attack texture
	attackAnimation = new SpriteAnimation(); // Initialize the attack animation
	attackAnimation->SetDetails(&attackTexture, 8, 0.1f, false, false); // Set the details of the attack animation

	magicAttackTexture = LoadTexture("Resources/PlayerMagicAttack.png"); // Load the magic attack texture
	magicAttackAnimation = new SpriteAnimation(); // Initialize the magic attack animation
	magicAttackAnimation->SetDetails(&magicAttackTexture, 8, 0.1f, false, false); // Set the details of the magic attack animation
}

BattleButtons::~BattleButtons() {
	UnloadTexture(buttonBGTexture); // Unload the button background texture

	delete attackButton; // Delete the attack button
	delete magicButton; // Delete the magic button
	delete itemButton; // Delete the item button
	delete runButton; // Delete the run button
	delete target; // Delete the target

	delete attackAnimation; // Delete the attack animation
	delete magicAttackAnimation; // Delete the magic attack animation

	UnloadTexture(attackTexture); // Unload the attack texture
	UnloadTexture(magicAttackTexture); // Unload the magic attack texture
}

// Update function for the battle buttons
void BattleButtons::Update(Player* player, vector<Enemy>* enemies, float* deltatime) {
	// Update logic for the buttons
	Vector2 mousePos = GetMousePosition(); // Get the mouse position

	if (player->TurnReady(deltatime) && attackMode == NONE) { //if no attack mode is selected
		// execute button actions if clicked, change colours if hovered over
		if (attackButton->IsButtonPressed(&mousePos)) {
			// Handle attack button pressed
			// set attack mode to attack for ChooseEnemy function
			attackMode = PLAYER_ATTACK;
		}
		if (*player->GetMana() > 0) { // Check if player has enough mana and magic damage
			if (magicButton->IsButtonPressed(&mousePos)) {
				// Handle magic button pressed
				// set attack mode to magic for ChooseEnemy function
				attackMode = PLAYER_MAGIC;
			}
		}
		else {
			// if player has no mana, set magic button to grey
			magicButton->SetColor(GRAY);
		}
		if (itemButton->IsButtonPressed(&mousePos)) { // Check if item button is pressed
			// Handle item button pressed
			itemButton->Action(player);
		}
		if (runButton->IsButtonPressed(&mousePos)) { // Check if run button is pressed
			// Handle run button pressed
			runButton->Action(player); // Execute the run action
		}
	}
	else {
		// if player is not ready, set all buttons to grey
		attackButton->SetColor(GRAY);
		magicButton->SetColor(GRAY);
		itemButton->SetColor(GRAY);
		runButton->SetColor(GRAY);
	}
	//if attackMode is not none, check if the mouse is above any enemy through ChooseEnemy function
	if (attackMode != PLAYER_NONE) {
		ChooseEnemy(enemies, player);
	}
	attackAnimation->Update(deltatime); // update the attack animation
	magicAttackAnimation->Update(deltatime); // update the magic attack animation
}

// Draw function for the battle buttons
void BattleButtons::Draw() {
	DrawTextureEx(buttonBGTexture, { buttonBGHitBox.x, buttonBGHitBox.y }, 0.0f, 2.0f, WHITE); // Draw the button background texture
	attackButton->Draw(); // Draw the attack button
	magicButton->Draw(); // Draw the magic button
	itemButton->Draw(); // Draw the item button
	runButton->Draw(); // Draw the run button
	target->Draw(); // Draw the target for choosing indicator

	// if the attack animation is playing, draw it
	if (attackAnimation->playing) { 
		attackAnimation->Draw(); // Draw the attack animation
	}
	// if the magic attack animation is playing, draw it
	if (magicAttackAnimation->playing) {
		magicAttackAnimation->Draw(); // Draw the magic attack animation
	}
}

// Choose an enemy to attack
void BattleButtons::ChooseEnemy(vector<Enemy>* enemies, Player* player){

	// if the player is not ready, return by pressing esc key 
	if (IsKeyPressed(KEY_ESCAPE)) {
		attackMode = PLAYER_NONE;
		target->Hide();
		return;
	}
	// get the mouse position
	Vector2 mousePos = GetMousePosition();
	//check if the mouse is above any enemy
	for (auto& enemy : *enemies) {
		// check if the enemy is dead
		switch (enemy.IsChosen(&mousePos))
		{

		case NONE: // if the mouse is not above any enemy
		{
			target->Hide();  //hide the target
			break;
		}
		case HOVERING: // if mouse is hovering above an enemy
		{
			target->Update(enemy.GetHitBox()); // update the target position and make it visible
			return; // return to avoid checking other enemies
		}
		case CLICKED: //if mouse is clicking an enemy
		{
			switch (attackMode) //switch with attackMode 
			{
			case PLAYER_ATTACK: // if attaack mode is set to attack
			{
				attackButton->Action(player, &enemy); // execute the attack action
				attackAnimation->SetPosition({ enemy.GetHitBox()->x + enemy.GetHitBox()->width / 2, enemy.GetHitBox()->y + enemy.GetHitBox()->height / 2 }); // set the position of the attack animation
				attackAnimation->Play(); // play the attack animation
				break;
			}
			case PLAYER_MAGIC: // if attack mode is set to magic
			{
				magicButton->Action(player, &enemy); // execute the magic action
				magicAttackAnimation->SetPosition({ enemy.GetHitBox()->x + enemy.GetHitBox()->width / 2, enemy.GetHitBox()->y + enemy.GetHitBox()->height / 2 }); // set the position of the magic attack animation
				magicAttackAnimation->Play(); // play the magic attack animation
				break;
			}
			}
			target->Hide(); // hide the target
			attackMode = PLAYER_NONE; // set the attack mode to none
			return; // return to avoid checking other enemies
		}
		}
	}
}

// battle bars class constructor
BattleBars::BattleBars(Rectangle* buttonBGHitBox) {
	barBGTexture = LoadTexture("Resources/UIBarBase.png"); // Load the bar background texture
	barBGHitBox = { 0,0,0,0 }; // Initialize the bar background hitbox
	barBGHitBox.width = (float)barBGTexture.width * 2.0f; // Set the width of the bar background hitbox
	barBGHitBox.height = (float)barBGTexture.height * 2.0f; // Set the height of the bar background hitbox
	barBGHitBox.x = buttonBGHitBox->x + buttonBGHitBox->width; // Set the x position of the bar background hitbox
	barBGHitBox.y = buttonBGHitBox->y; // Set the y position of the bar background hitbox

	healthBar = new Bar("Resources/UIHealthIcon.png", Color{ 14, 255, 0, 255 }, Color{ 11, 200, 0, 255 }, { barBGHitBox.x + 60, barBGHitBox.y + 40 }); // Initialize the health bar
	manaBar = new Bar("Resources/UIMagicIcon.png", Color{ 0, 255, 255, 255 }, Color{ 0, 178, 195, 255 }, { barBGHitBox.x + 60, barBGHitBox.y + 100 }); // Initialize the mana bar
	activeBattleTimeBar = new Bar("Resources/UIATBIcon.png", Color{ 246, 0, 255, 255 }, Color{ 163, 0, 196, 255 }, { barBGHitBox.x + 60, barBGHitBox.y + 140 }); // Initialize the active battle time bar
}

// destructor for battle bars
void BattleBars::Draw(Player* player) {
	DrawTextureEx(barBGTexture, { barBGHitBox.x, barBGHitBox.y }, 0.0f, 2.0f, WHITE); // Draw the bar background texture 
	string healthText = "HP: " + std::to_string((int)*player->GetHealth()) + "/" + std::to_string((int)*player->GetMaxHealth()); // Create health text
	DrawText(healthText.c_str(), barBGHitBox.x + 40, barBGHitBox.y + 20, 20, WHITE); // Draw the health text
	healthBar->Draw(); // Draw the health bar
	string manaText = "MP: " + to_string((int)*player->GetMana()) + "/" + to_string((int)*player->GetMaxMana()); // Create mana text
	DrawText(manaText.c_str(), barBGHitBox.x + 40, barBGHitBox.y + 80, 20, WHITE); // Draw the mana text
	manaBar->Draw(); // Draw the mana bar
	activeBattleTimeBar->Draw(); // Draw the active battle time bar
}

// Update function for the battle bars
void BattleBars::Update(Player* player) {
	healthBar->Update(player->GetHealth(), player->GetMaxHealth()); // Update the health bar
	manaBar->Update(player->GetMana(), player->GetMaxMana()); // Update the mana bar
	activeBattleTimeBar->Update(player->GetActiveBattleTimeTimer(), player->GetActiveBattleTimeInterval()); // Update the active battle time bar
}

// battle ui class constructor
BattleUI::BattleUI(const Vector2* screenScale) {
	battleButtons = new BattleButtons(screenScale); // Initialize the battle buttons
	battleBars = new BattleBars(battleButtons->GetButtonBGHitBox()); // Initialize the battle bars
}

// destructor for battle ui
void BattleUI::Update(Player* player, vector<Enemy>* enemies, float* deltatime) {
	battleButtons->Update(player, enemies, deltatime); // Update the battle buttons
	battleBars->Update(player); // Update the battle bars
}

// draw function for battle ui
void BattleUI::Draw(Player* player) {
	battleButtons->Draw(); // Draw the battle buttons
	battleBars->Draw(player); // Draw the battle bars
}