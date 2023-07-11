#ifndef __GUN_H
#define __GUN_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "Bullet.h"
#include <vector>

using namespace SDLFramework;

class Gun : public PhysEntity {
private:
	static const int OFFSCREEN_BUFFER = 10;

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	std::string mSomeOtherGun;
	std::string mSomeGun;
	std::string mStarterBlaster;
	std::string mCurrentTexture;

	Texture* mGun;

	bool mCanShoot;
	float mMoveSpeed;
	Vector2 mMoveBounds;
	Vector2 mTargetPos;

	int mEnemyFireTimer;
	int mShootPatterns; //switch

	static const int MAX_BULLETS = 200;
	std::vector<Bullet*> mPBullets;
	std::vector<Bullet*> mDelPBullets;

	std::vector<Bullet*> mEBullets;
	std::vector<Bullet*> mDelEBullets;

private:
	void HandleMovement();
	void HandleFiring();
	void EnemyFiring();

public:
	Gun();
	~Gun();

	void Visible(bool visible);
	bool IsAnimating();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

	void Update() override;
	void Render() override;

	void CanShoot(bool shoot);

	void ShootPattern1();
	void ShootPattern2();

	void SetTargetPos(Vector2 pos);
};
#endif
