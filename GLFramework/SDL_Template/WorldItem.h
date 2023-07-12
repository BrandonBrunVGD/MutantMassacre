#ifndef __WORLDITEM_H
#define __WORLDITEM_H
#include "PhysEntity.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"
#include "Timer.h"
#include "InputManager.h"

class WorldItem : public PhysEntity {
private:
	Timer* mTimer;
	InputManager* mInput;

	Texture* mCrystal;
	Texture* mMinedCrystal;

	Texture* mDroppedCrabShell;

	std::string mTexture;
	bool mVisible;
	bool mAnimating;
	bool mWasHit;

	bool mRenderGUI;
	bool mMined;

	bool mGiveItem;

	float mSpeed;

protected:

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

public:

	WorldItem(std::string texture);
	virtual ~WorldItem();

	// Inherited from PhysEntity
	virtual void Hit(PhysEntity* other) override;

	void Update() override;
	void Render() override;

	void Visible(bool visible);
	bool GetRenderGUI() { return mRenderGUI; }
	bool GetGiveItem() { return mGiveItem; }

	void SetGiveItem(bool give);

};
#endif