#include "Bullet.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"

bool Bullet::IgnoreCollisions() {
	return !Active();
}

Bullet::Bullet(std::string tag, Vector2 spawnpoint, Vector2 target, bool friendly) {
	mTimer = Timer::Instance();

	mVisible = true;
	mWasHit = false;
	mFriendly = friendly;

	mBulletTag = tag;
	if (mBulletTag == "normal") {
		mFriendlyTexture = new GLTexture("PlayerBullet.png");
		mFriendlyTexture->Parent(this);
		mFriendlyTexture->Position(Vec2_Zero);
		mFriendlyTexture->Scale(Vector2(0.2f, 0.2f));
		mSpeed = 500;
	}
	else if (mBulletTag == "crab?") {
		mFriendlyTexture = new GLTexture("CrystalCrab.png");
		mFriendlyTexture->Parent(this);
		mFriendlyTexture->Position(Vec2_Zero);
		mFriendlyTexture->Scale(Vector2(0.1f, 0.1f));
		mSpeed = 500;
	}
	
	mTexture = new GLTexture("Bullet.png");
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);
	mTexture->Scale(Vector2(0.2f, 0.2f));
	mSpeed = 500;
	

	//AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
	AddCollider(new CircleCollider(mTexture->ScaledDimensions().y));

	if (friendly) {

		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::FriendlyProjectiles);
		
		mSpawn = spawnpoint;
		mTarget = target;
	}
	else {

		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);
		
		mSpawn = spawnpoint;
		mTarget = target;
	}

	Position(mSpawn);

	mVelocity = mTarget - mSpawn;

	Rotate(mVelocity.ToAngle());
}

Bullet::~Bullet() {
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;

	delete mFriendlyTexture;
	mFriendlyTexture = nullptr;
}

void Bullet::Hit(PhysEntity * other) {
	if (mTag == "pBullet" && other->GetTag() == "enemy") {
		mWasHit = true;
		//std::cout << "hit" << std::endl;
	}
	else if (mTag == "eBullet" && other->GetTag() == "player") {
		mWasHit = true;
		//std::cout << "hit" << std::endl;
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
		if (mFriendly) {
			mFriendlyTexture->Render();
		}
		else { mTexture->Render(); }
		
		PhysEntity::Render();
	}
}
