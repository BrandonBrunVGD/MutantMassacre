#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "Player.h"
#include "Cursor.h"
#include "Gun.h"
#include "Enemy.h"
#include "WorldItem.h"
#include "GUIManager.h"
#include "Door.h"

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	AudioManager * mAudio;
	InputManager* mInput;

	//Inventory* mInventory;
	Gun* mGun;
	Player * mPlayer;
	Cursor* mCursor;
	Enemy* mTarantuCrab;
	WorldItem* mCrystal;
	WorldItem* mDroppedCrabShell;
	GUIManager* mGUI;
	Door* mDoor;

	//Background Textures
	Texture* mRuinsBackground;

	bool mSpawnCrabShell;
	bool mSpawnItemLock;
	bool mInteracted;
	//inventory
		bool mAddItem;
		std::string mItemToBeAdded;
		bool mMenuOpened;

	static const int MAX_ENEMIES = 10;
	Enemy* mEnemies[MAX_ENEMIES];

	static const int MAX_DROPPED_ITEMS = 10;
	std::vector<WorldItem*> mDroppedItems;
	std::vector<WorldItem*> mDelDroppedItems;

public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;

	void MenuOpen();
	void OnItem();

	bool GetInteracted() { return mInteracted; }
	void SetInteracted(bool interacted);

	//Inventory
		std::string AddItemToInventory() { return mItemToBeAdded; mAddItem = true; }
		bool GetAddItem() { return mAddItem; mAddItem = false; }
		void SetMenuOpen(bool opened) { mMenuOpened = opened; }

	void SpawnDroppedItem();
};
#endif