#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H
#include "StartScreen.h"
#include "PlayScreen.h"
#include "SpawnScreen.h"

class ScreenManager {
private:
	static ScreenManager * sInstance;

	enum Screens { Start, Spawn, DungeonScreen };
	Screens mCurrentScreen;

	InputManager * mInput;

	StartScreen * mStartScreen;
	SpawnScreen* mSpawnScreen;
	PlayScreen * mDungeonScreen;

	bool mPlayScreenLock;
	bool mSpawnScreenLock;

public:
	static ScreenManager * Instance();
	static void Release();

	void Update();
	void Render();

	void CreatePlayScreen();
	void CreateSpawnScreen();
	
private:
	ScreenManager();
	~ScreenManager();
};
#endif