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
	Gun* mEGun;

	bool mVisible;
	bool mAnimating;
	int mHp;

	float mSpeed;


protected:

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

public:

	Enemy();
	virtual ~Enemy();

	// Inherited from PhysEntity
	virtual void Hit(PhysEntity * other) override;

	void Update() override;
	void Render() override;

	void Visible(bool visible);

	bool GetHp() { return mHp; }

};
#endif