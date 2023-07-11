#include "Cursor.h"
#include "BoxCollider.h"

Cursor::Cursor() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mOnMenu = false;

	mGameCursor = new GLTexture("GameCursor.png");
	mGameCursor->Parent(this);
	mGameCursor->Position();
	mGameCursor->Scale(Vector2(0.1f, 0.1f));

	mMenuCursor = new GLTexture("ProfileSelector.png");
	mMenuCursor->Parent(this);
	mMenuCursor->Position();
	mMenuCursor->Scale(Vector2(0.1f, 0.1f));

	mMoveBounds = Vector2(1920, 1080);

	AddCollider(new BoxCollider(Vector2(10.50f, 10.50f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	Visible(true);
}

Cursor::~Cursor() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mGameCursor;
	mGameCursor = nullptr;

	delete mMenuCursor;
	mMenuCursor = nullptr;

}

void Cursor::Visible(bool visible) {
	mVisible = visible;
}

bool Cursor::IsAnimating() {
	return mAnimating;
}

bool Cursor::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Cursor::Hit(PhysEntity* other) {
	if (other->GetTag() == "menu") {
		mOnMenu = true;
	}
}

bool Cursor::WasHit() {
	return mOnMenu;
}

void Cursor::Update() {
	mOnMenu = false;

	if (mOnMenu == true) {
		mMenuCursor->Update();
	}
	else if (mOnMenu == false) {
		mGameCursor->Update();
	}
}

void Cursor::Render() {
	if (mOnMenu == true) {
		mMenuCursor->Render();
	}
	else if (mOnMenu == false) {
		mGameCursor->Render();
	}

	PhysEntity::Render();
}