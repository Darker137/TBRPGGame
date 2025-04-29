#include "EnemyManager.h"

// EnemyManager constructor
EnemyManager::EnemyManager(const Vector2* screenScale) {
	bannerTexture = LoadTexture("Resources/AttackBanner.png"); // Load the enemy banner texture
	LoadAttacksFromFile(); // Load attacks from file
	LoadEnemiesFromFile(); // Load enemies from file
}


// EnemyManager destructor

EnemyManager::~EnemyManager() {
	UnloadTexture(bannerTexture); // Unload the enemy banner texture
	enemies.clear(); // Clear the enemies vector
	enemyData.clear(); // Clear the enemy data vector
	allAttacks.clear(); // Clear the all attacks vector
	enemyTextures.clear(); // Clear the enemy textures map
	for (auto& it : enemyTextures) {
		UnloadTexture(it.second.neutral);
		UnloadTexture(it.second.attack);
		UnloadTexture(it.second.damage);
	}
}
// EnemyManager load enemy data
void EnemyManager::LoadEnemiesFromFile() {
	ifstream file("Enemies.txt"); // Open the enemies file

	string line; // Read each line from the file

	while (getline(file, line)) { // Read each line from the file
		//ignore comments and empty lines 
		if (line.empty() || line[0] == '#') continue;

		istringstream iss(line); // Create a string stream to parse the line
		string name; // Enemy name
		string healthStr, speedStr, damageStr, defenceStr, attackStr; // Enemy stats

		getline(iss, name, ','); // Read the enemy name
		getline(iss, healthStr, ','); // Read the enemy health
		getline(iss, speedStr, ','); // Read the enemy speed
		getline(iss, damageStr, ','); // Read the enemy damage
		getline(iss, defenceStr, ','); // Read the enemy defence
		getline(iss, attackStr, ','); // Read the enemy attack names

		EnemyData enemy; // Create an enemy data object

		enemy.name = name; // Set the enemy name
		enemy.health = stof(healthStr); // Set the enemy health
		enemy.speed = stof(speedStr); // Set the enemy speed
		enemy.damage = stof(damageStr); // Set the enemy damage
		enemy.defence = stof(defenceStr); // Set the enemy defence

	    //split attack names by ;
		stringstream attackStream(attackStr);
		string attackName; 
		// Read each attack name from the stream
		while (getline(attackStream, attackName, ';')) {
			// Trim whitespace from the attack name
			if (!attackName.empty()) {
				// Remove leading and trailing whitespace
				auto it = find_if(allAttacks.begin(), allAttacks.end(), [&attackName](const AttackData& attack) {
					return attack.name == attackName; // Check if the attack name matches
					}); 
				// Find the attack in the allAttacks vector
				if (it != allAttacks.end()) {
					enemy.attackData.push_back(&(*it)); // Add the attack to the enemy's attack list
				}
				// If the attack is not found, print an error message
				else {
					cerr << "Attack " << attackName << " not found in attacks list." << endl;
				}
			}
		}
		// Add the enemy to the enemy data vector
		enemyData.push_back(enemy);
	}
	// Close the file
	file.close();

	// Print enemy data
	for (auto& enemyD : enemyData) {
		enemyD.Print(); // Print enemy data
	}
}

// Load attacks from file
void EnemyManager::LoadAttacksFromFile() {
	ifstream file("Attacks.txt"); // Open the attacks file
	string line; // Read each line from the file
	while (getline(file, line)) {
		//ignore comments and empty lines
		if (line.empty() || line[0] == '#') continue;

		istringstream iss(line); // Create a string stream to parse the line
		string name; // Attack name
		string damageStr, cooldownStr; // Attack stats

		getline(iss, name, ','); // Read the attack name
		getline(iss, damageStr, ','); // Read the attack damage
		getline(iss, cooldownStr, ','); // Read the attack cooldown

		AttackData attack; // Create an attack data object

		attack.name = name; // Set the attack name
		attack.damage = stof(damageStr); // Set the attack damage
		attack.cooldown = stof(cooldownStr); // Set the attack cooldown

		allAttacks.push_back(attack); // Add the attack to the allAttacks vector
	}
	file.close(); // Close the file

}

// Load enemy textures
void EnemyManager::LoadTextures() {
	// Load enemy textures from files
	for (auto& enemyD : enemyData) {
		// Check if the enemy texture is already loaded
		if (enemyTextures.find(enemyD.name) == enemyTextures.end()) {
			// Load textures for the enemy if not already loaded
			Texture2D neutralTexture = LoadTexture(("Resources/" + enemyD.name + "/Neutral.png").c_str());
			Texture2D attackTexture = LoadTexture(("Resources/" + enemyD.name + "/Attack.png").c_str());
			Texture2D damageTexture = LoadTexture(("Resources/" + enemyD.name + "/Damage.png").c_str());
			enemyTextures[enemyD.name] = { neutralTexture, attackTexture, damageTexture }; // Add the textures to the map
		}
	}
}

// Add enemies to the game
void EnemyManager::AddEnemies(const Vector2* screenScale) {
	// Add enemies to the vector
	int enemyCount = 5; // Number of enemies to add
	Vector2 location; // Location for the enemies
	location.x = (screenScale->x / (enemyCount + 1));
	location.y = (screenScale->y - 180) / 2;

	// Create enemies and set their positions
	for (int i = 0; i < enemyCount; i++) { 
		Vector2 pos = { location.x * (i + 1), location.y }; // Set the position for each enemy
		enemies.emplace_back(&enemyData[rand() % enemyData.size()], pos); // Create a new enemy and add it to the vector
	}
	LoadTextures(); // Load enemy textures
	for (auto& enemy : enemies) {
		enemy.SetTexture(&enemyTextures[enemy.GetName()], &bannerTexture); // Set the texture for each enemy
	}
}

// Remove dead enemies from the game
void EnemyManager::RemoveEnemies() {
	// Remove dead enemies from the vector
	enemies.erase(
		remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {
			return *enemy.GetState() == DEAD;
		}), 
		enemies.end());
}

// Update enemies
void EnemyManager::UpdateEnemies(Player* player, float* deltatime) {
	for (auto& enemy : enemies) { // Iterate through each enemy
		enemy.Update(player, deltatime); // Update the enemy
	}
	RemoveEnemies(); // Remove dead enemies
}

// Draw enemies
void EnemyManager::DrawEnemies() {
	for (auto& enemy : enemies) {
		enemy.Draw(); // Draw the enemy
	}
}