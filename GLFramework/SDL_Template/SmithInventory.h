#ifndef __SMITHINVENTORY_H
#define __SMITHINVENTORY_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"
#include "Cursor.h"
#include "InventorySocket.h"
#include "Item.h"

using namespace SDLFramework;

class SmithInventory : public PhysEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	Item* mCrabGun;
	Item* mCrystalShard;
	Item* mCrabShell;

	bool mVisible;
	bool mAnimating;
	bool mWasHit;

	bool mCanOpen;
	bool mOpenMenu;
	bool mOpen;

	bool mCanBuy;

	int mCrabGunBuyReq1;
	int mCrabGunBuyReq2;

	int mCurrentCrystals;
	int mCurrentShells;

	bool mAddCrabGun;
	bool mDeleteItems;

	GameEntity* mSmithInventory;
	Texture* mBackground;
	Texture* mX2_1;
	Texture* mX2_2;
	Texture* mBUYButton;
	Texture* mBUY;

	Vector2 mMoveBounds;

private:

public:
	SmithInventory();
	~SmithInventory();

	void Visible(bool visible);
	bool IsAnimating();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

	void Update() override;
	void Render() override;

	void Open();
	void Close();

	bool GetCanOpen() { return mCanOpen; }
	void SetCanOpen(bool canOpen) { mCanOpen = canOpen; }

	void SetCurrentCrystals(int crystals) { mCurrentCrystals = crystals; }
	void SetCurrentShells(int shells) { mCurrentShells = shells; }

	void SetOpen(bool open) { mOpen = open; }
	bool GetOpen() { return mOpen; }
	void SetOpenMenu(bool open) { mOpenMenu = open; }

	bool GetAddCrabGun() { return mAddCrabGun; mAddCrabGun = false; }
	bool GetDeleteItems() { return mDeleteItems; mDeleteItems = false; }

	void Hit(PhysEntity* other) override;
	bool WasHit() { return mWasHit; }

};

#endif
