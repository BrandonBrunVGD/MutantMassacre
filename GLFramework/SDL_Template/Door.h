#ifndef __DOORSCREEN_H
#define __DOORSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "PhysEntity.h"
#include "InputManager.h"

using namespace SDLFramework;

class Door : public PhysEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;
	InputManager* mInput;

	Texture* mDoorUnderGlow;

	bool mWasHit;
	bool mInteracted;

public:

	Door();
	~Door();

	void Update() override;
	void Render() override;

	bool WasHit() { return mWasHit; }
	bool GetInteracted() { return mInteracted; }
	void SetInteracted(bool interacted);

	void Hit(PhysEntity* other) override;
};
#endif;
