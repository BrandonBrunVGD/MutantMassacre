#ifndef __INVENTORY_H
#define __INVENTORY_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"
#include "Cursor.h"
#include "InventorySocket.h"
#include "Item.h"

using namespace SDLFramework;

class Inventory : public PhysEntity{
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;
	
	Item* mLegendaryGun;
	Item* mRareArti;
	Item* mEpicArti;

	Item* mCrystalShard;
	Item* mCrabShell;

	bool mVisible;
	bool mAnimating;
	bool mWasHit;

	bool mCanOpen;
	bool mOpen;
	bool mOnItem;
	int mSelectedSocket;
	int mSelectedEquipeSocket;
	bool mMove;

	int mInventorySpace;

	int mSocketOffset;
	int mEmptySocket;
	std::string mCreateGun;

	static const int MAX_SOCKETS = 25;
	InventorySocket* mSockets[MAX_SOCKETS];
	static const int MAX_EQUIPED = 5;
	InventorySocket* mEquipedSockets[MAX_EQUIPED];

	GameEntity* mInventory;
	Texture* mBackground;

	Vector2 mMoveBounds;
	
private:

public:
	Inventory();
	~Inventory();

	void Visible(bool visible);
	bool IsAnimating();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

	void Update() override;
	void Render() override;

	void Open();
	void Close();

	bool GetCanOpen() {return mCanOpen; }
	void SetCanOpen(bool canOpen) { mCanOpen = canOpen; }

	bool GetOpen() { return mOpen; }
	void SetOnItem(bool item) { mOnItem = item; }

	void SetGiveItem(bool give);

	void Equipe();
	void ApplyEquipe();
	void UnEquipe();
	void Move();

	void CreateItem(Item* name, std::string rarity, std::string type, std::string item);
	void AddItem(std::string tag);

	void InventorySocketInit();
	void EquipedSocketInit();

	std::string GetCreateGun() { return mCreateGun; }

	std::vector<Item*> mInventoryVec;
	std::vector<Item*>::iterator mInventoryIter;

	std::vector<Item*> mEquipedGunVec;
	std::vector<Item*> mEquipedHelmVec;
	std::vector<Item*> mEquipedChestVec;
	std::vector<Item*> mEquipedBootsVec;
	std::vector<Item*> mEquipedArtiVec;

	std::vector<Item*>::iterator mEquipedIter;
};
#endif

