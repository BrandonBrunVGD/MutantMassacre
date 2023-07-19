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
	Enemy* mTarantuCrab;
	WorldItem* mCrystal;
	WorldItem* mDroppedCrabShell;
	GUIManager* mGUI;
	GUIManager* mGUISPACE;
	Door* mDoor;

	//Background Textures
	Texture* mRuinsBackground;

	bool mSpawnCrabShell;
	bool mSpawnItemLock;
	bool mDoorInteracted;
	//inventory
		bool mAddItem;
		std::string mItemToBeAdded;
		bool mMenuOpened;

	int mPlayerHp;

	std::string mCreateGun;
	bool mCreateGunLock;
	bool mDelGunLock;

	static const int MAX_ENEMIES = 10;
	Enemy* mEnemies[MAX_ENEMIES];

	static const int MAX_DROPPED_ITEMS = 10;
	std::vector<WorldItem*> mDroppedItems;
	std::vector<WorldItem*> mDelDroppedItems;


	static const int MAX_HP = 10;
	std::vector<GUIManager*> mHearts;

	static const int MAX_HP_GONE = 10;
	std::vector<GUIManager*> mHeartsGone;

	static const int MAX_EHP = 10;
	std::vector<GUIManager*> mEHearts;

	static const int MAX_EHP_GONE = 10;
	std::vector<GUIManager*> mEHeartsGone;

public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;

	void MenuOpen();
	void OnItem();

	bool GetDoorInteracted() { return mDoorInteracted; }
	void SetDoorInteracted(bool interacted);

	//Inventory
		std::string AddItemToInventory() { return mItemToBeAdded; mAddItem = true; }
		bool GetAddItem() { return mAddItem; mAddItem = false; }
		void SetMenuOpen(bool opened) { mMenuOpened = opened; }
	
	bool GetPlayerHp() { return mPlayerHp; }

	void SpawnDroppedItem();

	void SetCreateGun(std::string create) { mCreateGun = create; }

	void CreateGun();
	void DelGun();
};
#endif