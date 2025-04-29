#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "GeneralFunctions.h"
#include "Enemy.h"

// EnemyManager class to manage enemies
class EnemyManager {
protected:
	vector<EnemyData> enemyData; // Vector to store enemy data
	vector<AttackData> allAttacks; // Map to store all attacks
	vector<Enemy> enemies; // Vector to store enemies
	map<string, EnemyTexture> enemyTextures; // Map to store enemy textures
	Texture2D bannerTexture; // Texture for the enemy banner
public:
	EnemyManager(const Vector2* screenScale); // Constructor
	~EnemyManager(); // Destructor
	void LoadEnemiesFromFile(); // Load enemies from file
	void LoadAttacksFromFile(); // Load attacks from file
	void LoadTextures(); // Load enemy textures
	void AddEnemies(const Vector2* screenScale); // Add enemies to the game
	void RemoveEnemies(); // Remove dead enemies from the game
	void UpdateEnemies(Player* player, float* deltatime); // Update enemies
	void DrawEnemies(); // Draw enemies

	//getters
	vector<Enemy>* GetEnemies() { return &enemies; } // Get enemies vector
};

#endif