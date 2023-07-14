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

	delete mCursor;
	mCursor = new Cursor();
	mCursor->Parent(this);
	mCursor->Position();
	mCursor->Active(true);
	mCursor->SetTag("cursor");

	delete mGun;
	mGun = new Gun();
	mGun->Parent(mPlayer);
	mGun->Position(Vector2(80, 0));
	mGun->Active(true);
	mGun->SetTag("player gun");

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
	mDoor->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.9f);
	mDoor->Active(true);

	mRuinsBackground = new GLTexture("RuinsBackground.png");
	mRuinsBackground->Parent(this);
	mRuinsBackground->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mRuinsBackground->Active(true);

	for (int i = 0; i < MAX_HP_GONE; ++i) {
		GUIManager* heartGone = new GUIManager("HEART_GONE");
		heartGone->Position(Vector2(1175 + 75 * i, 75));
		heartGone->SetTag("heartGone");
		mHeartsGone.push_back(heartGone);
	}

	for (int i = 0; i < MAX_HP; ++i) {
		GUIManager* heart = new GUIManager("HEART");
		heart->Position(Vector2(1175 +75*i, 75));
		heart->SetTag("heart");
		mHearts.push_back(heart);
	}

	mSpawnCrabShell = false;
	mSpawnItemLock = false;
	mInteracted = false;
	mAddItem = false;
	mItemToBeAdded = "null";

	SDL_ShowCursor(SDL_DISABLE);
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mCursor;
	mCursor = nullptr;

	delete mGun;
	mGun = nullptr;

	delete mTarantuCrab;
	mTarantuCrab = nullptr;

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
	
	mPlayerHp = mPlayer->GetHp();

	mItemToBeAdded = "null";

	if (mTarantuCrab != nullptr) {
		if (mTarantuCrab->GetHp() > 0) {
			mTarantuCrab->Update();
		}
		else {
			delete mTarantuCrab;
			mTarantuCrab = nullptr;
		}
	}
	
	mRuinsBackground->Update();
	mGUI->Update();
	mGUISPACE->Update();
	mPlayer->Update();

	if (mPlayer->WasHit() == true) {
		//mDelHearts.push_back(mHearts[mPlayer->GetHp() -1]);
		mHearts.erase(mHearts.begin());

		std::cout << "HEART DELETED" << std::endl;
		mPlayer->SetWasHit(false);
	}

	mCursor->Update();
	mGun->Update();
	mCrystal->Update();
	mDoor->Update();

	if (mDoor->GetInteracted() == true) { mInteracted = true; mDoor->SetInteracted(false); }

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

	mCursor->Position(mInput->MousePosition());
	MenuOpen();

	if (mCrystal->GetGiveItem() == true) { 
		mItemToBeAdded = mCrystal->GetTag();
		mAddItem = true;
		mCrystal->SetGiveItem(false);
	}

	mGun->SetTargetPos(mPlayer->Position());

	if (!mSpawnItemLock) {
		if (mTarantuCrab == nullptr) {
			SpawnDroppedItem();
			mSpawnItemLock = true;
		}
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

	for (auto b : mDelHearts) {
		delete b;
	}

	mDelHearts.clear();
}

void PlayScreen::Render() {

	mRuinsBackground->Render();
	if (mDoor->WasHit() == true) { mDoor->Render(); }
	if (mTarantuCrab != nullptr) { mTarantuCrab->Render(); }
	
	mCrystal->Render();

	for (auto it = mDroppedItems.begin(); it != mDroppedItems.end(); ++it) {
		(*it)->Render();
		if ((*it) != nullptr && (*it)->GetRenderGUI() == true) {
			mGUI->Render();
		}
		
	}
	
	mPlayer->Render();
	mGun->Render();
	mCursor->Render();
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
	mDroppedCrabShell->Parent(this);
	mDroppedCrabShell->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mDroppedCrabShell->Active(true);
	mDroppedCrabShell->SetTag("crab shell");
	mDroppedItems.push_back(mDroppedCrabShell);
}

void PlayScreen::SetInteracted(bool interacted) {
	mInteracted = interacted;
}