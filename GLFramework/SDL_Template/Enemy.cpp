#include "Enemy.h"

Enemy::Enemy() {
	mTimer = Timer::Instance();

	mVisible = false;
	mAnimating = false;

	mHp = 10;
	mSpeed = 500;

	mTexture = new GLTexture("Tarantu-Crab.png");
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);
	mTexture->Scale(Vector2(0.750f, 0.750f));

	delete mEGun;
	mEGun = new Gun();
	mEGun->Parent(this);
	mEGun->Position(Vec2_Zero);
	mEGun->Active(true);
	mEGun->SetTag("enemy gun");

	AddCollider(new CircleCollider(mTexture->ScaledDimensions().y * 0.38));
	AddCollider(new CircleCollider(mTexture->ScaledDimensions().y * 0.38), Vector2(-150.0f, -50.0f));
	AddCollider(new CircleCollider(mTexture->ScaledDimensions().y * 0.38), Vector2(150.0f, -50.0f));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	Visible(true);
}

Enemy::~Enemy() {
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;

	delete mEGun;
	mEGun = nullptr;
}

bool Enemy::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Enemy::Hit(PhysEntity* other) {
	if (other->GetTag() == "pBullet") {
		mHp -= 1;
	}
}

void Enemy::Update() {
	mEGun->Render();
	mTexture->Update();
	std::cout << mHp << std::endl;
	mEGun->Update();
	
}

void Enemy::Render() {

	mTexture->Render();
	mEGun->Render();

	PhysEntity::Render();
}

void Enemy::Visible(bool visible) {
	mVisible = visible;
}

