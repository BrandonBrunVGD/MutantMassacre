#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "Item.h"

Item::Item(std::string texture, std::string type, std::string item) {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;

	mTexture = texture;
	mItem = item;

	mSelected = false;
	mItemType = type;
	mMoveable = false;

	BackgroundTexture();
	ItemTexture();

	mMoveBounds = Vector2(1920, 1080);

	AddCollider(new BoxCollider(Vector2(332 / 2, 307 / 2)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}

Item::~Item() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mRareTexture;
	mRareTexture = nullptr;

	delete mEpicTexture;
	mEpicTexture = nullptr;

	delete mLegTexture;
	mLegTexture = nullptr;

	delete mCrystalShard;
	mCrystalShard = nullptr;
}

void Item::Visible(bool visible) {
	mVisible = visible;
}

bool Item::IsAnimating() {
	return mAnimating;
}

bool Item::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Item::Hit(PhysEntity* other) {
	if (other->GetTag() == "cursor") {
		mSelected = true;
		std::cout << mSelected << std::endl;
	}
}

void Item::Update() {
	if (mAnimating) {

	}
	else {
		if (Active()) {
			mSelected = false;

			if (mTexture == "rare") { mRareTexture->Update(); }
			else if (mTexture == "epic") { mEpicTexture->Update(); }
			else if (mTexture == "legendary") { mLegTexture->Update(); }

		
		}
	}
}

void Item::Render() {

	if (mVisible) {
		if (mAnimating) {

		}
		else {
			if (mTexture == "rare") { mRareTexture->Render(); }
			else if (mTexture == "epic") { mEpicTexture->Render(); }
			else if (mTexture == "legendary") { mLegTexture->Render(); }

			if (mItem == "crystal shard") { mCrystalShard->Render(); }
		}
	}

	PhysEntity::Render();
}

void Item::BackgroundTexture() {
	if (mTexture == "rare") {	
		mRareTexture = new GLTexture("InventoryBackgrounds.png", 0, 0, 332, 307);
		mRareTexture->Parent(this);
		mRareTexture->Position(Vec2_Zero);
		mRareTexture->Scale(Vector2(0.5f, 0.5f));
	}
	else if (mTexture == "epic") {
		mEpicTexture = new GLTexture("InventoryBackgrounds.png", 332, 0, 332, 307);
		mEpicTexture->Parent(this);
		mEpicTexture->Position(Vec2_Zero);
		mEpicTexture->Scale(Vector2(0.5f, 0.5f));
	}
	else if (mTexture == "legendary") {
		mLegTexture = new GLTexture("InventoryBackgrounds.png", 664, 0, 332, 307);
		mLegTexture->Parent(this);
		mLegTexture->Position(Vec2_Zero);
		mLegTexture->Scale(Vector2(0.5f, 0.5f));
	}
}

void Item::ItemTexture() {	
	//list of all items in game
	if (mItem == "crystal shard") {
		mCrystalShard = new GLTexture("CrystalShard.png");
		mCrystalShard->Parent(this);
		mCrystalShard->Position(Vec2_Zero);
		mCrystalShard->Scale(Vector2(0.25f, 0.25f));
	}
	
}

void Item::SetEquiped(bool equipe) {
	mEquiped = equipe;
}

void Item::SetLastPos(Vector2 pos) {
	mLastPos = pos;
}

void Item::SetMoveable(bool move) {
	mMoveable = move;
}

void Item::SetLastSocket(int socket) {
	mLastSocket = socket;
}