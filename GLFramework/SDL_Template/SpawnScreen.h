#ifndef __SPAWNSCREEN_H
#define __SPAWNSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "Player.h"
#include "Cursor.h"
#include "Gun.h"
#include "Enemy.h"
#include "WorldItem.h"
#include "GUIManager.h"
#include "PhysEntity.h"
#include "GameEntity.h"
#include "Door.h"
#include "BlackSmith.h"

class SpawnScreen : public GameEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;
	InputManager* mInput;

	//Inventory* mInventory;
	Gun* mGun;
	Player* mPlayer;
	//Cursor* mCursor;
	GUIManager* mGUI;
	GUIManager* mGUISPACE;
	Door* mDoor;
	BlackSmith* mBlackSmith;

	//Background Textures
	Texture* mSpawnBackground;

	bool mInteracted;

	static const int MAX_ENEMIES = 10;
	Enemy* mEnemies[MAX_ENEMIES];

	bool mAddItem;
	std::string mItemToBeAdded;
	bool mMenuOpened;

	std::string mCreateGun;
	bool mCreateGunLock;
	bool mDelGunLock;

public:
	SpawnScreen();
	~SpawnScreen();

	void Update() override;
	void Render() override;

	void MenuOpen();
	void OnItem();

	bool GetInteracted() { return mInteracted; }
	void SetInteracted(bool interacted);

	std::string AddItemToInventory() { return mItemToBeAdded; mAddItem = true; }
	bool GetAddItem() { return mAddItem; mAddItem = false; }
	void SetMenuOpen(bool opened) { mMenuOpened = opened; }

	void SetCreateGun(std::string create) { mCreateGun = create; }

	void CreateGun();
	void DelGun();
};


#endif
