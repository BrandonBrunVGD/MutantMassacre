#include "DeathScreen.h"

DeathScreen::DeathScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mYouDied = new GLTexture("YOUDIED.png");
	mYouDied->Parent(this);
	mYouDied->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
}


DeathScreen::~DeathScreen() {
	mTimer = nullptr;
	mInput = nullptr;

	delete mYouDied;
	mYouDied = nullptr;
}

void DeathScreen::Update() {
	mYouDied->Update();
	
}

void DeathScreen::Render() {
	mYouDied->Render();

}