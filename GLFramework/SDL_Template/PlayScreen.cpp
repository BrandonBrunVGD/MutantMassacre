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

	delete mInventory;
	mInventory = new Inventory();
	mInventory->Parent(this);
	mInventory->Position();
	mInventory->Active(true);
	mInventory->SetTag("null");

	delete mGun;
	mGun = new Gun();
	mGun->Parent(mPlayer);
	mGun->Position(Vec2_Zero);
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

	delete mDoor;
	mDoor = new Door();
	mDoor->Parent(this);
	mDoor->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.9f);
	mDoor->Active(true);

	mRuinsBackground = new GLTexture("RuinsBackground.png");
	mRuinsBackground->Parent(this);
	mRuinsBackground->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mRuinsBackground->Active(true);

	mSpawnCrabShell = false;
	mSpawnItemLock = false;
	mInteracted = false;

	SDL_ShowCursor(SDL_DISABLE);
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mCursor;
	mCursor = nullptr;

	delete mInventory;
	mInventory = nullptr;

	delete mGun;
	mGun = nullptr;

	delete mTarantuCrab;
	mTarantuCrab = nullptr;

	delete mCrystal;
	mCrystal = nullptr;

	delete mGUI;
	mGUI = nullptr;

	delete mRuinsBackground;
	mRuinsBackground = nullptr;

	delete mDoor;
	mDoor = nullptr;
}

void PlayScreen::Update() {
	
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
	mPlayer->Update();	
	mCursor->Update();
	mInventory->Update();
	mGun->Update();
	mCrystal->Update();
	
	mDoor->Update();
	if (mDoor->GetInteracted() == true) { mInteracted = true; mDoor->SetInteracted(false); }

	for (auto it = mDroppedItems.begin(); it != mDroppedItems.end(); ) {
		(*it)->Update();

		if ((*it)->GetGiveItem() == true) {
			mInventory->AddItem((*it)->GetTag());
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
		mInventory->AddItem(mCrystal->GetTag()); 
		mCrystal->SetGiveItem(false);
	}

	

	mGun->SetTargetPos(mPlayer->Position());

	if (!mSpawnItemLock) {
		if (mTarantuCrab == nullptr) {
			//mSpawnCrabShell = true; 
			SpawnDroppedItem();
			mSpawnItemLock = true;
		}
	}
	
	for (auto b : mDelDroppedItems) {
		delete b;
	}
	mDelDroppedItems.clear();
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
	mInventory->Render();
	mCursor->Render();

	if (mCrystal->GetRenderGUI() == true) { 
		mGUI->Render();
	}

}

void PlayScreen::MenuOpen() {
	if (mInventory->GetOpen() == true) {
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