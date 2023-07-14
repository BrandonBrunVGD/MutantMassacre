#include "DeathScreen.h"

DeathScreen::DeathScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();


}


DeathScreen::~DeathScreen() {

	
	mTimer = nullptr;
	mInput = nullptr;
}

void DeathScreen::Update() {

	
}

void DeathScreen::Render() {


}