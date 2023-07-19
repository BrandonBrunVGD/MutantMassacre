#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "BlackSmith.h"

BlackSmith::BlackSmith() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;

	mBlackSmith = new GLTexture("BlackSmith.png");
	mBlackSmith->Parent(this);
	mBlackSmith->Position(Vec2_Zero);
	mBlackSmith->Scale(Vector2(0.5f, 0.5f));

	mAnvil = new GLTexture("Anvil.png");
	mAnvil->Parent(this);
	mAnvil->Position(Vector2(80, 80));
	mAnvil->Scale(Vector2(0.5f, 0.5f));

	AddCollider(new BoxCollider(Vector2(332 / 2, 307 / 2)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	Visible(true);
}

BlackSmith::~BlackSmith() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mBlackSmith;
	mBlackSmith = nullptr;

	delete mAnvil;
	mAnvil = nullptr;
}

void BlackSmith::Visible(bool visible) {
	mVisible = visible;
}

bool BlackSmith::IsAnimating() {
	return mAnimating;
}

bool BlackSmith::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void BlackSmith::Hit(PhysEntity* other) {
	if (other->GetTag() == "player") {
		mWasHit = true;
	}
}

void BlackSmith::Update() {
	mBlackSmith->Update();
	mAnvil->Update();
	
}

void BlackSmith::Render() {
	mBlackSmith->Render();
	mAnvil->Render();

	PhysEntity::Render();
}