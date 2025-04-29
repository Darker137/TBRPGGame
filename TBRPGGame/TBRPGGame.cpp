// TBRPGGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "BattleInterface.h"
#include "EnemyManager.h"
#include "Mouse.h"

int main()
{
	// Initialization
	// window initialization
	// Set the screen size and initialize the window
	const Vector2 virtualScale = { 1280, 720 };
	float screenScaling = 1.0f; // Set the screen scaling factor
	Vector2 screenScale = { virtualScale.x * screenScaling, virtualScale.y * screenScaling };

	InitWindow(screenScale.x, screenScale.y, "RPGaem");
	SetExitKey(KEY_NULL); // Disable the exit key to prevent closing the window with ESC
	SetTargetFPS(60);

	srand((unsigned int)time(nullptr)); // seed rand with current time

	RenderTexture2D target = LoadRenderTexture((int)virtualScale.x, (int)virtualScale.y); // Create a render texture for the game
	SetTextureFilter(target.texture, TEXTURE_FILTER_POINT); // Set the texture filter to point for pixel art

	Player* player = new Player(); // Create a new player object
	EnemyManager* enemyManager = new EnemyManager(&screenScale); // Create a new enemy manager
	BattleUI* battleUI = new BattleUI(&screenScale); // Create the battle UI

	Mouse* mouse = new Mouse(); // Create a new mouse object

	Background* background = new Background(); // Create a new background object
	background->texture = LoadTexture("Resources/BattleBackground.png"); // Load the background texture

	float deltatime = 0.0f; // Initialize delta times

	enemyManager->AddEnemies(&screenScale); // Add enemies to the game

	while (!WindowShouldClose() && !player->GetIsRunning()) 
	{// Loop until the game is closed 
		deltatime = GetFrameTime(); // Get the time since the last frame
		HideCursor(); // Hide the cursor for the game

		MakeFullScreen(&virtualScale, &screenScale, &screenScaling); // Check for full screen toggle

		battleUI->Update(player, enemyManager->GetEnemies(), &deltatime); // Update the battle UI
		enemyManager->UpdateEnemies(player, &deltatime); // Update the enemies
		
		BeginTextureMode(target); // Begin drawing to the render texture

		ClearBackground(BLACK); // Clear the background
		//DrawBackingGridCheckers(); // Draw the backing grid for testing
		background->Draw(); // Draw the background
		enemyManager->DrawEnemies(); // Draw the enemies
		battleUI->Draw(player); // Draw the battle UI
		mouse->Draw(); // Draw the mouse

		EndTextureMode(); // End drawing to the render texture

		BeginDrawing(); // Begin drawing to the window
		ClearBackground(BLACK); // Clear the background
		
		float scale = min(
			(float)GetScreenWidth() / target.texture.width,
			(float)GetScreenHeight() / target.texture.height
		);

		screenScale = { virtualScale.x * scale, virtualScale.y * scale }; // Set the screen scale based on the render texture size
		float offsetX = (GetScreenWidth() - screenScale.x) / 2.0f; // Calculate the offset for centering the texture
		float offsetY = (GetScreenHeight() - screenScale.y) / 2.0f; // Calculate the offset for centering the texture

		Rectangle source = { 0, 0, virtualScale.x, -virtualScale.y }; // Set the source rectangle for the render texture
		Rectangle dest = { 0, 0, screenScale.x, screenScale.y }; // Set the destination rectangle for the window
		DrawTexturePro(target.texture, source, dest, { offsetX, offsetY }, 0.0f, WHITE); // Draw the render texture to the window
		EndDrawing(); // End drawing to the window
	}
	// De-Initialization

	delete player; // Delete the player object
	delete enemyManager; // Delete the enemy manager
	delete battleUI; // Delete the battle UI
	delete mouse; // Delete the mouse object
	delete background; // Delete the background object

	return 0; // Exit the program
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
