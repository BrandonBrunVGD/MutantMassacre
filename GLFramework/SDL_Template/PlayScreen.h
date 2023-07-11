#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "Player.h"
#include "Cursor.h"
#include "Inventory.h"
#include "Gun.h"
#include "Enemy.h"
#include "WorldItem.h"
#include "GUIManager.h"

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	AudioManager * mAudio;
	InputManager* mInput;

	Inventory* mInventory;
	Gun* mGun;
	Player * mPlayer;
	Cursor* mCursor;
	Enemy* mTarantuCrab;
	WorldItem* mCrystal;
	GUIManager* mGUI;

	static const int MAX_ENEMIES = 10;
	Enemy* mEnemies[MAX_ENEMIES];
public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;

	void MenuOpen();
	void OnItem();
};
#endif