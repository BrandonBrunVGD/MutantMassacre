#ifndef __ITEM_H
#define __ITEM_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"

using namespace SDLFramework;

class Item : public PhysEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	std::string mTexture;
	std::string mItem;

	std::string mItemType;
	bool mSelected;
	bool mEquiped;
	bool mMoveable;

	Texture* mRareTexture;
	Texture* mEpicTexture;
	Texture* mLegTexture;

	Texture* mCrystalShard;
	Texture* mCrabShell;
	Texture* mStarterGun;
	Texture* mRareRing;
	Texture* mIronHelm;
	Texture* mCrabGun;

	float mMoveSpeed;
	Vector2 mMoveBounds;
	Vector2 mLastPos;
	int mLastSocket;

private:
	

public:
	Item(std::string texture, std::string type, std::string item);
	~Item();

	void Visible(bool visible);
	bool IsAnimating();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

	void Update() override;
	void Render() override;

	void Hit(PhysEntity* other) override;

	void BackgroundTexture();
	void ItemTexture();

	bool GetSelected() { return mSelected; }
	std::string GetItemType() { return mItemType; }

	std::string GetItemName() { return mItem; }

	bool GetEquiped() { return mEquiped; }
	void SetEquiped(bool equipe);

	Vector2 GetLastPos() { return mLastPos; }
	void SetLastPos(Vector2 pos);

	int GetLastSocket() { return mLastSocket; }
	void SetLastSocket(int socket);

	void SetMoveable(bool move);
	bool GetMoveable() { return mMoveable; }
};
#endif
