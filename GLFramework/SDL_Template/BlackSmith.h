#ifndef __BLACKSMITH_H
#define __BLACKSMITH_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"

using namespace SDLFramework;

class BlackSmith : public PhysEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	Texture* mBlackSmith;
	Texture* mAnvil;

	bool mWasHit;
	bool mVisible;
	bool mAnimating;
	bool mInteracted;

private:

public:
	BlackSmith();
	~BlackSmith();

	void Visible(bool visible);
	bool IsAnimating();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

	void Update() override;
	void Render() override;

	void Hit(PhysEntity* other) override;
	bool WasHit() { return mWasHit; }
	void SetWasHit(bool hit) { mWasHit = hit; }

	bool GetInteracted() { return mInteracted; }
	void SetInteracted(bool interacted) { mInteracted = interacted; }

};
#endif

