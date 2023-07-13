#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H
#include "StartScreen.h"
#include "PlayScreen.h"
#include "SpawnScreen.h"
#include "Inventory.h"

class ScreenManager : GameEntity{
private:
	static ScreenManager * sInstance;

	enum Screens { Start, Spawn, DungeonScreen };
	Screens mCurrentScreen;

	InputManager * mInput;

	StartScreen * mStartScreen;
	SpawnScreen* mSpawnScreen;
	PlayScreen * mDungeonScreen;

	Inventory* mInventory;

	bool mPlayScreenLock;
	bool mSpawnScreenLock;

public:
	static ScreenManager * Instance();
	static void Release();

	void Update();
	void Render();

	void CreatePlayScreen();
	void CreateSpawnScreen();
	
	//void AddItemToInventory(std::string tag);
private:
	ScreenManager();
	~ScreenManager();
};
#endif