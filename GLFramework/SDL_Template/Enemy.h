#ifndef __ENEMY_H
#define __ENEMY_H
#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "PhysEntity.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"
#include "Gun.h"

class Enemy : public PhysEntity {
private:
	Timer* mTimer;

	Texture* mTexture;
	Texture* mEyeLids;
	Texture* mShadow;
	Gun* mEGun;

	bool mVisible;
	bool mAnimating;
	int mHp;
	int mMaxHp;
	bool mWasHit;

	float mSpeed;
	int mMoveSwitch;
	bool mEnragedMods;
	bool mEnragedState;
	bool mSleepState;

protected:

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

public:

	Enemy();
	virtual ~Enemy();

	// Inherited from PhysEntity
	virtual void Hit(PhysEntity * other) override;

	bool WasHit() { return mWasHit; }
	void SetWasHit(bool hit) { mWasHit = hit; }

	void Update() override;
	void Render() override;

	void Visible(bool visible);

	bool GetHp() { return mHp; }
	void HandleMovement();
};
#endif