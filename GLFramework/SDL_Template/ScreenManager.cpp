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
		mInventory->SetCanOpen(false);
		mStartScreen->Update();

		if (mStartScreen->getMenuSwitch() != 0) {
			if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
				mCurrentScreen = Spawn;
			}
		}
		break;
	case Spawn:
		mInventory->SetCanOpen(true);
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
		mInventory->SetCanOpen(true);
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

			if (mDungeonScreen->GetPlayerHp() <= 0) {
				delete mDungeonScreen;
				mDungeonScreen = nullptr;

				mDeathScreenLock = false;
				mCurrentScreen = Death;
			}
		}
		break;
	case Death:
		mInventory->SetCanOpen(false);
		CreateDeathScreen();

		if (mDeathScreen != nullptr) {
			mDeathScreen->Update();

			
				//delete mDeathScreen;
				//mDeathScreen = nullptr;

				//mSpawnScreenLock = false;
				//mCurrentScreen = Spawn;
			
		}
		break;
	}
	
	if (mInventory->GetCanOpen() == true) {
		mInventory->Update();
	}
	
	if (mDungeonScreen != nullptr) {
		if (mDungeonScreen->GetAddItem() == true) {
			mInventory->AddItem(mDungeonScreen->AddItemToInventory());
		}
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
	case Death:

		if (mDeathScreen != nullptr) {
			mDeathScreen->Render();
		}
		break;
	}

	if (mInventory->GetCanOpen() == true) {
		if (mInventory->GetOpen() == true) {
			mInventory->Render();
			if (mDungeonScreen != nullptr) {
				mDungeonScreen->SetMenuOpen(true);
			}
		}
		else {
			if (mDungeonScreen != nullptr) {
				mDungeonScreen->SetMenuOpen(false);
			}
		}
	}
	
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();

	mStartScreen = new StartScreen();
	//mSpawnScreen = new SpawnScreen();
	
	mInventory = new Inventory();
	mInventory->Position();
	mInventory->Active(true);
	mInventory->SetTag("null");

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

	delete mDeathScreen;
	mDeathScreen = nullptr;

	delete mInventory;
	mInventory = nullptr;
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

void ScreenManager::CreateDeathScreen() {
	if (!mDeathScreenLock) {
		mDeathScreen = new DeathScreen();
		mDeathScreenLock = true;
	}
}