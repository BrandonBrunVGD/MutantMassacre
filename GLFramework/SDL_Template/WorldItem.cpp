#include "WorldItem.h"

WorldItem::WorldItem(std::string texture) {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mTexture = texture;
	mSpeed = 500;

	mRenderGUI = false;
	mMined = false;
	mGiveItem = false;

	mCrystal = new GLTexture("CrystalChunk.png");
	mCrystal->Parent(this);
	mCrystal->Position(Vec2_Zero);
	mCrystal->Scale(Vector2(0.20f, 0.20f));

	mMinedCrystal = new GLTexture("MinedCrystal.png");
	mMinedCrystal->Parent(this);
	mMinedCrystal->Position(Vec2_Zero);
	mMinedCrystal->Scale(Vector2(0.20f, 0.20f));

	mDroppedCrabShell = new GLTexture("CrabShell.png");
	mDroppedCrabShell->Parent(this);
	mDroppedCrabShell->Position(Vec2_Zero);
	mDroppedCrabShell->Scale(Vector2(0.20f, 0.20f));

	AddCollider(new CircleCollider(mCrystal->ScaledDimensions().y));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	Visible(true);
}

WorldItem::~WorldItem() {
	mTimer = nullptr;

	delete mCrystal;
	mCrystal = nullptr;

	delete mMinedCrystal;
	mMinedCrystal = nullptr;

	delete mDroppedCrabShell;
	mDroppedCrabShell = nullptr;
}

bool WorldItem::IgnoreCollisions()	{
	return !mVisible || mAnimating;
}

void WorldItem::Hit(PhysEntity* other) {
	if (other->GetTag() == "player") {
		mWasHit = true;
	}
}

void WorldItem::Update() {
	mRenderGUI = false;
	
	if (mTexture == "crystal") { mCrystal->Update(); mMinedCrystal->Update(); }
	else if (mTexture == "crab shell") { mDroppedCrabShell->Update(); }
	
	if (!mMined && mWasHit) { mRenderGUI = true; }
	else { mRenderGUI = false; }

	if (mWasHit) {
		if (mInput->KeyPressed(SDL_SCANCODE_E)) {
			mMined = true;
			mGiveItem = true;
		}
		mWasHit = false;
	}

	std::cout << mTag << " " << mRenderGUI << std::endl;
}

void WorldItem::Render() {
	if (mTexture == "crystal") { 
		if (mMined == false) {
			mCrystal->Render();
		}
		else { mMinedCrystal->Render(); }
	}
	else if (mTexture == "crab shell") {
		if (mMined == false) {
			mDroppedCrabShell->Render();
		}
	}

	PhysEntity::Render();
}

void WorldItem::Visible(bool visible) {
	mVisible = visible;
}

void WorldItem::SetGiveItem(bool give) {
	mGiveItem = give;
}