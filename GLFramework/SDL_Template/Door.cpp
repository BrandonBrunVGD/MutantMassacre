#include "Door.h"
#include "PhysicsManager.h"
#include "BoxCollider.h"

Door::Door() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mInput = InputManager::Instance();

	mWasHit = false;

	mDoorUnderGlow = new GLTexture("DoorUnderGlow.png");
	mDoorUnderGlow->Parent(this);
	mDoorUnderGlow->Position(Vec2_Zero);
	mDoorUnderGlow->Active(true);

	AddCollider(new BoxCollider(Vector2(367, 32)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);
}

Door::~Door() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mDoorUnderGlow;
	mDoorUnderGlow = nullptr;
}

void Door::Update() {
	if (mWasHit) {
		mDoorUnderGlow->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_E)) {
			mInteracted = true;
		}
		mWasHit = false;
	}
}

void Door::Render() {

	if (mWasHit) { mDoorUnderGlow->Render(); }
	PhysEntity::Render();
}
void Door::Hit(PhysEntity* other) {
	if (other->GetTag() == "player") {
		mWasHit = true;

	}
}

void Door::SetInteracted(bool interacted) {
	mInteracted = interacted;
}