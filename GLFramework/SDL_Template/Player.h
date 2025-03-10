#ifndef __PLAYER_H
#define __PLAYER_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"

using namespace SDLFramework;

class Player : public PhysEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;
	bool mWasHit;

	int mScore;
	int mHp;

	bool mWalkingLeft;
	bool mWalkingRight;
	bool mCanShoot;

	Texture* mPlayer;
	AnimatedGLTexture* mWalkAnim;
	AnimatedGLTexture* mWalkAnimLeft;

	float mMoveSpeed;
	Vector2 mMoveBounds;

private:
	void HandleMovement();

public:
	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;
	bool GetHp() { return mHp; }

	bool WasHit();
	void SetWasHit(bool hit) { mWasHit = hit; }

	void SetCanShoot(bool shoot) { mCanShoot = shoot; }

	void Update() override;
	void Render() override;
};
#endif