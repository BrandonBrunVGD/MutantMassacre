#ifndef __DEATHSCREEN_H
#define __DEATHSCREEN_H
#include "AnimatedGLTexture.h"
#include "InputManager.h"
#include "Scoreboard.h"

using namespace SDLFramework;

class DeathScreen : public GameEntity {

private:
	Timer* mTimer;
	InputManager* mInput;

	Texture* mYouDied;

public:
	DeathScreen();
	~DeathScreen();

	void Update() override;
	void Render() override;

};
#endif
