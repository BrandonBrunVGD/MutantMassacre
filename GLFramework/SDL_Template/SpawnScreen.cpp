#include "SpawnScreen.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

SpawnScreen::SpawnScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mInput = InputManager::Instance();

	mInteracted = false;
	mAddItem = false;
	mItemToBeAdded = "null";
	mMenuOpened = false;

	mCreateGun = "null";
	mCreateGunLock = false;
	mDelGunLock = true;

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.8f);
	mPlayer->Active(true);
	mPlayer->SetTag("player");

	delete mGUI;
	mGUI = new GUIManager("E");
	mGUI->Parent(this);
	mGUI->Position(Graphics::SCREEN_WIDTH * 0.9f, Graphics::SCREEN_HEIGHT * 0.9f);
	mGUI->Active(true);

	delete mGUISPACE;
	mGUISPACE = new GUIManager("SPACE");
	mGUISPACE->Parent(this);
	mGUISPACE->Position(Graphics::SCREEN_WIDTH * 0.7f, Graphics::SCREEN_HEIGHT * 0.9f);
	mGUISPACE->Active(true);

	mDoor = new Door();
	mDoor->Parent(this);
	mDoor->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.19f);
	mDoor->Active(true);
	mDoor->SetTag("door");

	mBlackSmith = new BlackSmith();
	mBlackSmith->Parent(this);
	mBlackSmith->Position(Graphics::SCREEN_WIDTH * 0.8, Graphics::SCREEN_HEIGHT * 0.5);
	mBlackSmith->Active(true);
	mBlackSmith->SetTag("blacksmith");

	mSpawnBackground = new GLTexture("SpawnScreenBackground.png");
	mSpawnBackground->Parent(this);
	mSpawnBackground->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mSpawnBackground->Active(true);

	SDL_ShowCursor(SDL_DISABLE);
}

SpawnScreen::~SpawnScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mGun;
	mGun = nullptr;

	delete mGUI;
	mGUI = nullptr;

	delete mGUISPACE;
	mGUISPACE = nullptr;

	delete mSpawnBackground;
	mSpawnBackground = nullptr;

	delete mDoor;
	mDoor = nullptr;

	delete mBlackSmith;
	mBlackSmith = nullptr;
}

void SpawnScreen::Update() {

	//if (mWasHit) { mWasHit = false; mGUI->Position(mPlayer->Position()); }
	std::cout << mCreateGun << std::endl;
	mSpawnBackground->Update();
	mDoor->Update();
	mBlackSmith->Update();
	mGUI->Update();
	mPlayer->Update();

	CreateGun();
	DelGun();
	if (mGun != nullptr) { 
		mGun->Update(); 
		mGun->SetTargetPos(mPlayer->Position());
		MenuOpen();
	}

	if (mDoor->GetInteracted() == true) { mInteracted = true; mDoor->SetInteracted(false); }

	if (mMenuOpened) { mPlayer->SetCanShoot(false); }
	else { mPlayer->SetCanShoot(true); }
}

void SpawnScreen::Render() {

	mSpawnBackground->Render();
	mDoor->Render();
	mBlackSmith->Render();
	mPlayer->Render();
	if (mGun != nullptr) { mGun->Render(); }
	
	if (mDoor->WasHit() == true) { mGUI->Render(); }
	mGUISPACE->Render();
}

void SpawnScreen::MenuOpen() {
	if (mMenuOpened == true) {
		mGun->CanShoot(false);
	}
	else {
		mGun->CanShoot(true);
	}
}

void SpawnScreen::SetInteracted(bool interacted) {
	mInteracted = interacted;
}

void SpawnScreen::CreateGun() {
	if (mCreateGun == "null") { mCreateGunLock = false; }
	if (!mCreateGunLock) {
		if (mCreateGun == "starter gun") {
			mGun = new Gun();
			mGun->Parent(mPlayer);
			mGun->Position(Vector2(80, 0));
			mGun->Active(true);
			mGun->SetTag("player gun");
			std::cout << "CREATED GUN" << std::endl;
			mCreateGunLock = true;
			mPlayer->SetCanShoot(true);
		}
		
	}
}
void SpawnScreen::DelGun() {
	if (mCreateGun != "null") { mDelGunLock = false; }
	if (!mDelGunLock) {
		if (mCreateGun == "null") {
			delete mGun;
			mGun = nullptr;
			std::cout << "DELETED GUN" << std::endl;
			mDelGunLock = true;
			mCreateGunLock = true;
			mPlayer->SetCanShoot(false);
		}
		
	}
}