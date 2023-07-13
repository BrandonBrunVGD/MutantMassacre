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

	bool mVisible;
	bool mAnimating;

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


};
#endif

