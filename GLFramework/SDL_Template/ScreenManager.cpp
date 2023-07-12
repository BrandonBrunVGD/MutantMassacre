 #include "ScreenManager.h"

ScreenManager * ScreenManager::sInstance = nullptr;

ScreenManager * ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void ScreenManager::Update() {

	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Update();

		if (mStartScreen->getMenuSwitch() != 0) {
			if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
				mCurrentScreen = Spawn;
			}
		}
		break;
	case Spawn:
		CreateSpawnScreen();
		if (mSpawnScreen != nullptr) {
			mSpawnScreen->Update();
			if (mSpawnScreen->GetInteracted() == true) {
				mSpawnScreen->SetInteracted(false);
				delete mSpawnScreen;
				mSpawnScreen = nullptr;
				mPlayScreenLock = false;
				mCurrentScreen = DungeonScreen;
			}
		}

		break;
	case DungeonScreen:
		CreatePlayScreen();
		if (mDungeonScreen != nullptr) {
			mDungeonScreen->Update();
			if (mDungeonScreen->GetInteracted() == true) {
				mDungeonScreen->SetInteracted(false);
				delete mDungeonScreen;
				mDungeonScreen = nullptr;
				mSpawnScreenLock = false;
				mCurrentScreen = Spawn;
			}
		}
		break;
	}
}

void ScreenManager::Render() { 


	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Render();
		break;
	case Spawn:
		
		if (mSpawnScreen != nullptr) {
			mSpawnScreen->Render();
		}
		break;
	case DungeonScreen:
		
		if (mDungeonScreen != nullptr) {
			mDungeonScreen->Render();
		}
		break;
	}
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();


	mStartScreen = new StartScreen();
	//mSpawnScreen = new SpawnScreen();
	
	mCurrentScreen = Start;

	mPlayScreenLock = false;
	mSpawnScreenLock = false;
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mSpawnScreen;
	mSpawnScreen = nullptr;

	delete mDungeonScreen;
	mDungeonScreen = nullptr;
}

void ScreenManager::CreatePlayScreen() {
	if (!mPlayScreenLock) {
		mDungeonScreen = new PlayScreen();
		mPlayScreenLock = true;
	}
}

void ScreenManager::CreateSpawnScreen() {
	if (!mSpawnScreenLock) {
		mSpawnScreen = new SpawnScreen();
		mSpawnScreenLock = true;
	}
}

//To Do:
//Switch Inventory Into Screen Manager or Fix Items Not Carrying Over Screens