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
	mGUI->Parent(mCrystal);
	mGUI->Position(Vector2(80.0f, -80.0f));
	mGUI->Active(true);

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
	
	mGUI->Update();
	mPlayer->Update();	
	mCursor->Update();
	mInventory->Update();
	mGun->Update();
	mCrystal->Update();
	mCursor->Position(mInput->MousePosition());
	MenuOpen();

	if (mCrystal->GetGiveItem() == true) { 
		mInventory->AddItem(mCrystal->GetTag()); 
		mCrystal->SetGiveItem(false);
	}

	mGun->SetTargetPos(mPlayer->Position());

}

void PlayScreen::Render() {

	if (mTarantuCrab != nullptr) {
		mTarantuCrab->Render();
	}
	
	mCrystal->Render();
	mPlayer->Render();
	mGun->Render();
	mInventory->Render();
	mCursor->Render();

	if (mCrystal->GetRenderGUI() == true) { mGUI->Render(); }
}

void PlayScreen::MenuOpen() {
	if (mInventory->GetOpen() == true) {
		mGun->CanShoot(false);
	}
	else {
		mGun->CanShoot(true);
	}
}