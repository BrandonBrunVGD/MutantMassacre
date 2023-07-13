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

	/*delete mInventory;
	mInventory = new Inventory();
	mInventory->Parent(this);
	mInventory->Position();
	mInventory->Active(true);
	mInventory->SetTag("null");*/

	delete mGun;
	mGun = new Gun();
	mGun->Parent(mPlayer);
	mGun->Position(Vec2_Zero);
	mGun->Active(true);
	mGun->SetTag("player gun");

	delete mGUI;
	mGUI = new GUIManager("E");
	mGUI->Parent(this);
	mGUI->Position(Graphics::SCREEN_WIDTH * 0.9f, Graphics::SCREEN_HEIGHT * 0.9f);
	mGUI->Active(true);

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

	delete mCursor;
	mCursor = nullptr;

	//delete mInventory;
	//mInventory = nullptr;

	delete mGun;
	mGun = nullptr;

	delete mGUI;
	mGUI = nullptr;

	delete mSpawnBackground;
	mSpawnBackground = nullptr;

	delete mDoor;
	mDoor = nullptr;

	delete mBlackSmith;
	mBlackSmith = nullptr;
}

void SpawnScreen::Update() {

	//if (mWasHit) { mWasHit = false; mGUI->Position(mPlayer->Position()); }

	mSpawnBackground->Update();
	mDoor->Update();
	mBlackSmith->Update();
	mGUI->Update();
	mPlayer->Update();
	mCursor->Update();
	//mInventory->Update();
	mGun->Update();

	mCursor->Position(mInput->MousePosition());
	MenuOpen();

	mGun->SetTargetPos(mPlayer->Position());

	if (mDoor->GetInteracted() == true) { mInteracted = true; mDoor->SetInteracted(false); }
}

void SpawnScreen::Render() {

	mSpawnBackground->Render();
	mDoor->Render();
	mBlackSmith->Render();
	mPlayer->Render();
	mGun->Render();
	//mInventory->Render();
	mCursor->Render();
	if (mDoor->WasHit() == true) { mGUI->Render(); }
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