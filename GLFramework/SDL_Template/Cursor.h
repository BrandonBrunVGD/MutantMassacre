#ifndef __CURSOR_H
#define __CURSOR_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysicsManager.h"

using namespace SDLFramework;

class Cursor : public PhysEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;
	bool mOnMenu;
	
	//AnimatedGLTexture* mDeathAnimation;
	
	std::string mCurrentCursor;

	Texture* mGameCursor;
	Texture* mMenuCursor;

	//float mMoveSpeed;
	Vector2 mMoveBounds;

private:

public:
	Cursor();
	~Cursor();

	void Visible(bool visible);
	bool IsAnimating();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;

	void HandleMovement();

	bool WasHit();

	void Update() override;
	void Render() override;

};
#endif
