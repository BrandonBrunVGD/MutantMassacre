#include "Bullet.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"

bool Bullet::IgnoreCollisions() {
	return !Active();
}

Bullet::Bullet(Vector2 spawnpoint, Vector2 target, bool friendly) {
	mTimer = Timer::Instance();

	mVisible = true;
	mWasHit = false;
	mFriendly = friendly;

	mTexture = new GLTexture("Bullet.png");
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);
	mTexture->Scale(Vector2(0.1f, 0.1f));
	mSpeed = 500;

	//AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
	AddCollider(new CircleCollider(mTexture->ScaledDimensions().y));

	if (friendly) {
		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::FriendlyProjectiles);
		
		mSpawn = spawnpoint;
		mTarget = target;
	}
	else {
		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::HostileProjectiles);
		
	}

	Position(mSpawn);

	mVelocity = mTarget - mSpawn;

	Rotate(mVelocity.ToAngle());
}

Bullet::~Bullet() {
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void Bullet::Hit(PhysEntity * other) {
	if (mTag == "pBullet" && other->GetTag() == "enemy") {
		mWasHit = true;
		std::cout << "hit" << std::endl;
	}
	else if (mTag == "eBullet" && other->GetTag() == "player") {
		mWasHit = false;
		std::cout << "hit" << std::endl;
	}
	
}

bool Bullet::WasHit() {
	return mWasHit;
}

void Bullet::Update() {
	if (Active()) {
		Translate(mVelocity.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		
	}

}

void Bullet::Render() {
	if (Active()) {
		mTexture->Render();
		PhysEntity::Render();
	}
}
