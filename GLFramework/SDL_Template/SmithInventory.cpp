#include "SmithInventory.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

SmithInventory::SmithInventory() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mOpen = false;
	mCanBuy = true;

	mCurrentCrystals = 0;
	mCurrentShells = 0;
	mCrabGunBuyReq1 = 2;
	mCrabGunBuyReq2 = 2;

	mAddCrabGun = false;
	mDeleteItems = false;

	mBackground = new GLTexture("Inventory.png", 0, 0, 1920, 1080);
	mBackground->Parent(this);
	mBackground->Position(Vector2(1920 / 2, 1080 / 2));

	mCrabGun = new Item("legendary", "Gun", "crab gun");
	mCrabGun->Parent(mBackground);
	mCrabGun->Position(Vector2(-850, -450));

	mCrystalShard = new Item("epic", "Mat", "crystal shard");
	mCrystalShard->Parent(mBackground);
	mCrystalShard->Scale(Vector2(0.5, 0.5));
	mCrystalShard->Position(Vector2(-900, -850));

	mCrabShell = new Item("epic", "Mat", "crab shell");
	mCrabShell->Parent(mBackground);
	mCrabShell->Scale(Vector2(0.5, 0.5));
	mCrabShell->Position(Vector2(-450, -850));

	mX2_1 = new GLTexture("x2", "emulogic.ttf", 32, { 255, 255, 255 });
	mX2_1->Parent(mCrystalShard);
	mX2_1->Position(Vector2(200, 200));

	mX2_2 = new GLTexture("x2", "emulogic.ttf", 32, { 255, 255, 255 });
	mX2_2->Parent(mCrabShell);
	mX2_2->Position(Vector2(200, 200));

	mBUYButton = new GLTexture("BuyUI.png");
	mBUYButton->Parent(mBackground);
	mBUYButton->Scale(Vector2(0.4, 0.4));
	mBUYButton->Position(Vector2(-400, -450));

	mBought = new GLTexture("BoughtUI.png");
	mBought->Parent(mBackground);
	mBought->Scale(Vector2(0.4, 0.4));
	mBought->Position(Vector2(-400, -450));

	mBUY = new GLTexture("BUY", "emulogic.ttf", 32, { 255, 255, 255 });
	mBUY->Parent(mBUYButton);
	mBUY->Position(Vector2(3700, -900));

	AddCollider(new BoxCollider(Vector2(595*0.4, 307*0.4)), mBUYButton->Position());

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}

SmithInventory::~SmithInventory() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mCrabGun;
	mCrabGun = nullptr;

	delete mCrystalShard;
	mCrystalShard = nullptr;

	delete mCrabShell;
	mCrabShell = nullptr;

	delete mX2_1;
	mX2_1 = nullptr;

	delete mX2_2;
	mX2_2 = nullptr;
	
	delete mBUYButton;
	mBUYButton = nullptr;

	delete mBUY;
	mBUY = nullptr;
}

void SmithInventory::Visible(bool visible) {
	mVisible = visible;
}

bool SmithInventory::IsAnimating() {
	return mAnimating;
}

bool SmithInventory::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void SmithInventory::Update() {

	if (mVisible) {
		Open();
		Close();
		if (mOpen) {
			mBackground->Update();
			mCrabGun->Update();
			mCrystalShard->Update();
			mCrabShell->Update();
			mX2_1->Update();
			mX2_2->Update();
			mBUYButton->Update();
			mBUY->Update();
			
			
			if (mCurrentCrystals == mCrabGunBuyReq1 && mCurrentShells == mCrabGunBuyReq2) {
				
				if (mWasHit && mInput->MouseButtonPressed(::InputManager::MouseButton::Left)) {
					mAddCrabGun = true;
					mDeleteItems = true;
					mWasHit = false;
					mCanBuy = false;
				}
				else { mAddCrabGun = false; mDeleteItems = false; }
				
			}
			
		}
	}
}

void SmithInventory::Render() {

	if (mVisible) {
		if (mOpen) {
			mBackground->Render();
			mCrabGun->Render();
			mCrystalShard->Render();
			mCrabShell->Render();
			mX2_1->Render();
			mX2_2->Render();
			if (mCanBuy) { mBUYButton->Render(); }
			else { mBought->Render(); }
			mBUY->Render();
		}
	}

	PhysEntity::Render();
}

void SmithInventory::Open() {
	if (mOpenMenu) {
		if (mInput->KeyPressed(SDL_SCANCODE_E)) {
			mOpen = true;
			SetTag("smith menu");
		}
	}
}

void SmithInventory::Close() {
	if (mOpen) {
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
			mOpen = false;
			IgnoreCollisions();
			SetTag("null");
		
		}
	}
}

void SmithInventory::Hit(PhysEntity* other) {
	if (other->GetTag() == "cursor" ) {		
			mWasHit = true;
	}	
}