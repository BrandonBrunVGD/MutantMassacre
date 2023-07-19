#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mInput = InputManager::Instance();

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.8f);
	mPlayer->Active(true);
	mPlayer->SetTag("player");

	delete mTarantuCrab;
	mTarantuCrab = new Enemy();
	mTarantuCrab->Parent(this);
	mTarantuCrab->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mTarantuCrab->Active(true);
	mTarantuCrab->SetTag("enemy");	

	delete mCrystal;
	mCrystal = new WorldItem("crystal");
	mCrystal->Parent(this);
	mCrystal->Position(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.2f);
	mCrystal->Active(true);
	mCrystal->SetTag("crystal");

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

	delete mDoor;
	mDoor = new Door();
	mDoor->Parent(this);
	mDoor->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.85f);
	mDoor->Active(true);
	//mDoor->Scale(-Vec2_One);

	mRuinsBackground = new GLTexture("RuinsBackground.png");
	mRuinsBackground->Parent(this);
	mRuinsBackground->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mRuinsBackground->Active(true);

	for (int i = 0; i < MAX_HP_GONE; ++i) {
		GUIManager* heartGone = new GUIManager("HEART_GONE");
		heartGone->Position(Vector2(750 - 75 * i, 75));
		heartGone->SetTag("heartGone");
		mHeartsGone.push_back(heartGone);
	}

	for (int i = 0; i < MAX_HP; ++i) {
		GUIManager* heart = new GUIManager("HEART");
		heart->Position(Vector2(750 -75*i, 75));
		heart->SetTag("heart");
		mHearts.push_back(heart);
	}

	for (int i = 0; i < MAX_EHP_GONE; ++i) {
		GUIManager* EheartGone = new GUIManager("HEART_GONE");
		EheartGone->Position(Vector2(1175 + 75 * i, 75));
		EheartGone->SetTag("EheartGone");
		mEHeartsGone.push_back(EheartGone);
	}

	for (int i = 0; i < MAX_EHP; ++i) {
		GUIManager* Eheart = new GUIManager("EHEART");
		Eheart->Position(Vector2(1175 + 75 * i, 75));
		Eheart->SetTag("Eheart");
		mEHearts.push_back(Eheart);
	}

	mSpawnCrabShell = false;
	mSpawnItemLock = false;
	mDoorInteracted = false;
	mAddItem = false;
	mItemToBeAdded = "null";

	mCreateGun = "null";
	mCreateGunLock = false;
	mDelGunLock = true;

	SDL_ShowCursor(SDL_DISABLE);
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mTarantuCrab;
	mTarantuCrab = nullptr;

	delete mGun;
	mGun = nullptr;

	delete mCrystal;
	mCrystal = nullptr;

	delete mGUI;
	mGUI = nullptr;

	delete mGUISPACE;
	mGUISPACE = nullptr;

	delete mRuinsBackground;
	mRuinsBackground = nullptr;

	delete mDoor;
	mDoor = nullptr;

	for (auto b : mHearts) {
		delete b;
	}

	for (auto b : mHeartsGone) {
		delete b;
	}

}

void PlayScreen::Update() {
	
	if (mPlayer != nullptr) { mPlayerHp = mPlayer->GetHp(); }

	mItemToBeAdded = "null";

	if (mTarantuCrab != nullptr) {
		for (auto b : mEHearts) {
			b->Update();
		}

		for (auto b : mEHeartsGone) {
			b->Update();
		}

		if (mTarantuCrab->GetHp() > 0) {
			mTarantuCrab->Update();

		}
		else {
			delete mTarantuCrab;
			mTarantuCrab = nullptr;

			for (auto b : mEHearts) {
				delete b;
			}

			for (auto b : mEHeartsGone) {
				delete b;
			}
		}
	}

	if (!mSpawnItemLock) {
		if (mTarantuCrab == nullptr) {
			SpawnDroppedItem();
			mSpawnItemLock = true;
		}
	}

	for (auto it = mDroppedItems.begin(); it != mDroppedItems.end(); ) {
		(*it)->Update();

		if ((*it)->GetGiveItem() == true) {
			mItemToBeAdded = (*it)->GetTag();
			mAddItem = true;
			(*it)->SetGiveItem(false);

			mDelDroppedItems.push_back(*it);
			it = mDroppedItems.erase(it);
		}
		else {
			++it;
		}

	}
	
	mRuinsBackground->Update();
	mGUI->Update();
	mGUISPACE->Update();
	mPlayer->Update();

	if (mPlayer->WasHit() == true) {
		mHearts.erase(mHearts.begin());

		std::cout << "HEART DELETED" << std::endl;
		mPlayer->SetWasHit(false);
	}

	if (mTarantuCrab != nullptr && mTarantuCrab->WasHit() == true) {
		
		mEHearts.erase(mEHearts.begin());

		std::cout << "HEART DELETED" << std::endl;
		mTarantuCrab->SetWasHit(false);


	}

	mCrystal->Update();
	mDoor->Update();

	if (mDoor->GetInteracted() == true) { mDoorInteracted = true; mDoor->SetInteracted(false); }

	std::cout << mCreateGun << std::endl;
	CreateGun();
	DelGun();
	if (mGun != nullptr) {
		mGun->Update();
		mGun->SetTargetPos(mPlayer->Position());
		MenuOpen();
	}

	if (mCrystal->GetGiveItem() == true) { 
		mItemToBeAdded = mCrystal->GetTag();
		mAddItem = true;
		mCrystal->SetGiveItem(false);
	}
	
	for (auto b : mDelDroppedItems) {
		delete b;
	}
	mDelDroppedItems.clear();

	for (auto b : mHearts) {
		b->Update();
	}
	
	for (auto b : mHeartsGone) {
		b->Update();
	}

	if (mMenuOpened) { mPlayer->SetCanShoot(false); }
	else { mPlayer->SetCanShoot(true); }
}

void PlayScreen::Render() {

	mRuinsBackground->Render();
	if (mDoor->WasHit() == true) { mDoor->Render(); mGUI->Render(); }
	if (mTarantuCrab != nullptr) {
		
		mTarantuCrab->Render(); 

		for (auto b : mEHeartsGone) {
			b->Render();
		}

		for (auto b : mEHearts) {
			b->Render();
		}
	}
	
	mCrystal->Render();

	for (auto it = mDroppedItems.begin(); it != mDroppedItems.end(); ++it) {
		(*it)->Render();
		if ((*it) != nullptr && (*it)->GetRenderGUI() == true) {
			mGUI->Render();
		}
		
	}
	
	mPlayer->Render();
	if (mGun != nullptr) { mGun->Render(); }
	mGUISPACE->Render();

	if (mCrystal->GetRenderGUI() == true) { 
		mGUI->Render();
	}

	for (auto b : mHeartsGone) {
		b->Render();
	}

	for (auto b : mHearts) {
		b->Render();
	}

}

void PlayScreen::MenuOpen() {
	if (mMenuOpened == true) {
		mGun->CanShoot(false);
	}
	else {
		mGun->CanShoot(true);
	}
}

void PlayScreen::SpawnDroppedItem() {
	mDroppedCrabShell = new WorldItem("crab shell");
	//mDroppedCrabShell->Parent(this);
	mDroppedCrabShell->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mDroppedCrabShell->Active(true);
	mDroppedCrabShell->SetTag("crab shell");
	mDroppedItems.push_back(mDroppedCrabShell);
}

void PlayScreen::SetDoorInteracted(bool interacted) {
	mDoorInteracted = interacted;
}

void PlayScreen::CreateGun() {
	if (mCreateGun == "null") { mCreateGunLock = false; }
	if (!mCreateGunLock) {

		if (mCreateGun == "starter gun") { 
			mGun = new Gun("starter gun");
			mGun->Parent(mPlayer);
			mGun->Position(Vector2(80, 0));
			mGun->Active(true);
			mGun->SetTag("player gun");
			std::cout << "CREATED GUN" << std::endl;
			mCreateGunLock = true;
			mPlayer->SetCanShoot(true);
		}
		else if (mCreateGun == "crab gun") { 
			mGun = new Gun("crab gun");
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
void PlayScreen::DelGun() {
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