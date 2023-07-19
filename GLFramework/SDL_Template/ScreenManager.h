#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H
#include "StartScreen.h"
#include "PlayScreen.h"
#include "SpawnScreen.h"
#include "DeathScreen.h"
#include "Inventory.h"
#include "SmithInventory.h"
#include "Cursor.h"

class ScreenManager : GameEntity{
private:
	static ScreenManager * sInstance;

	enum Screens { Start, Spawn, DungeonScreen, Death};
	Screens mCurrentScreen;

	InputManager * mInput;

	StartScreen * mStartScreen;
	SpawnScreen* mSpawnScreen;
	PlayScreen * mDungeonScreen;
	DeathScreen* mDeathScreen;

	Inventory* mInventory;
	SmithInventory* mSmithInventory;
	Cursor* mCursor;

	bool mPlayScreenLock;
	bool mSpawnScreenLock;
	bool mDeathScreenLock;

public:
	static ScreenManager * Instance();
	static void Release();

	void Update();
	void Render();

	void CreatePlayScreen();
	void CreateSpawnScreen();
	void CreateDeathScreen();

private:
	ScreenManager();
	~ScreenManager();
};
#endif