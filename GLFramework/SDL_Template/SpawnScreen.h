#ifndef __SPAWNSCREEN_H
#define __SPAWNSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "Player.h"
#include "Cursor.h"
#include "Inventory.h"
#include "Gun.h"
#include "Enemy.h"
#include "WorldItem.h"
#include "GUIManager.h"
#include "PhysEntity.h"
#include "GameEntity.h"
#include "Door.h"

class SpawnScreen : public GameEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;
	InputManager* mInput;

	Inventory* mInventory;
	Gun* mGun;
	Player* mPlayer;
	Cursor* mCursor;
	GUIManager* mGUI;
	Door* mDoor;

	//Background Textures
	Texture* mSpawnBackground;

	bool mInteracted;

	static const int MAX_ENEMIES = 10;
	Enemy* mEnemies[MAX_ENEMIES];

public:
	SpawnScreen();
	~SpawnScreen();

	void Update() override;
	void Render() override;

	void MenuOpen();
	void OnItem();

	bool GetInteracted() { return mInteracted; }
	void SetInteracted(bool interacted);
};


#endif
