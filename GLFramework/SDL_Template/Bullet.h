#ifndef __BULLET_H
#define __BULLET_H
#include "PhysEntity.h"
#include "Timer.h"
#include "InputManager.h"

using namespace SDLFramework;

class Bullet : public PhysEntity {
private:

	Timer * mTimer;

	bool mFriendly;
	bool mVisible;
	bool mWasHit;

	Texture * mTexture;
	Texture* mFriendlyTexture;

	float mSpeed;
	std::string mBulletTag;

	Vector2 mSpawn;		
	Vector2 mVelocity;
	Vector2 mTarget;

private:
	//Inherited from PhysEntity
	bool IgnoreCollisions() override;

public:
	Bullet(std::string tag, Vector2 spawnpoint = Vec2_Zero, Vector2 target = Vec2_Zero, bool friendly = true);
	~Bullet();

	// Inherited from PhysEntity
	void Hit(PhysEntity * other) override;

	bool WasHit();

	void Update() override;
	void Render() override;

	Vector2 Target() {
		return mTarget;
	}
};
#endif