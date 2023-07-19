#include "InventorySocket.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

InventorySocket::InventorySocket() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;

	mSelected = false;
	mEquipeSocket = false;
	mFull = false;

	mInventorySocket = new GLTexture("InventoryBackgrounds.png", 996, 0, 332, 307);
	mInventorySocket->Parent(this);
	mInventorySocket->Position(Vec2_Zero);
	mInventorySocket->Scale(Vector2(0.5f, 0.5f));

	mSelector = new GLTexture("ProfileSelector.png");
	mSelector->Parent(this);
	mSelector->Position(Vec2_Zero);
	mSelector->Scale(Vector2(0.5f, 0.5f));

	AddCollider(new BoxCollider(Vector2(mInventorySocket->GetWidth()/2, mInventorySocket->GetHeight()/2)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}

InventorySocket::~InventorySocket() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mInventorySocket;
	mInventorySocket = nullptr;

	delete mSelector;
	mSelector = nullptr;
}

void InventorySocket::Visible(bool visible) {
	mVisible = visible;
}

bool InventorySocket::IsAnimating() {
	return mAnimating;
}

bool InventorySocket::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void InventorySocket::Update() {
	mSelected = false;

	if (mAnimating) {

	}
	else {
		if (Active()) {
			mInventorySocket->Update();

			if (mSelected == true) {
				mSelector->Update();
			}
		}
	}

}

void InventorySocket::Render() {

	
	mInventorySocket->Render();

	if (mSelected == true) {
		mSelector->Render();
	}
	
	PhysEntity::Render();
}

void InventorySocket::Hit(PhysEntity* other) {
	if (mInventoryOpen == true) {
		if (other->GetTag() == "cursor") {
			mSelected = true;
		}
	}
}

bool InventorySocket::WasHit() {
	return mSelected;
}

void InventorySocket::SetSocketTag(int tag) {
	mSocketTag = tag;
}

void InventorySocket::SetInventoryOpen(bool open) {
	mInventoryOpen = open;
}

void InventorySocket::SetEquipeSocket(bool equipe) {
	mEquipeSocket = equipe;
}

void InventorySocket::SetFull(bool full) {
	mFull = full;
}