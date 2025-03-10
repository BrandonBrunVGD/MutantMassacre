#include "Enemy.h"

Enemy::Enemy() {
	mTimer = Timer::Instance();

	mVisible = false;
	mAnimating = false;

	mMaxHp = 10;
	mHp = 10;
	mSpeed = 250;
	mMoveSwitch = 0;
	mEnragedState = false;
	mEnragedMods = false;
	mSleepState = true;
	mWasHit = false;

	mTexture = new GLTexture("Tarantu-Crab.png");
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);
	mTexture->Scale(Vector2(0.750f, 0.750f));

	mEyeLids = new GLTexture("Tarantu-Crab EyeLids.png");
	mEyeLids->Parent(this);
	mEyeLids->Position(Vector2(0.0f, -15.0f));
	mEyeLids->Scale(Vector2(0.750f, 0.750f));

	mShadow = new GLTexture("Tarantu-Crab Shadow.png");
	mShadow->Parent(this);
	mShadow->Position(Vector2(0.0f, 75.0f));
	mShadow->Scale(Vector2(0.750f, 0.750f));

	delete mEGun;
	mEGun = new Gun("enemy gun");
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

	delete mEyeLids;
	mEyeLids = nullptr;

	delete mShadow;
	mShadow = nullptr;

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
		mSleepState = false;
		mWasHit = true;
	}
}

void Enemy::Update() {
	if (mSleepState == true) { mEGun->CanShoot(false); mSpeed = 0; }
	else { mEGun->CanShoot(true); mSpeed = 250; }

	mTexture->Update();
	mEyeLids->Update();
	mEGun->Update();
	
	HandleMovement();
	
}

void Enemy::Render() {

	mShadow->Render();
	if (!mSleepState) { mEGun->Render(); }
	mTexture->Render();
	if (mSleepState) { mEyeLids->Render(); }
	
	PhysEntity::Render();
}

void Enemy::Visible(bool visible) {
	mVisible = visible;
}

void Enemy::HandleMovement() {
	if (mHp <= mMaxHp / 2) { mEnragedState = true; }
	if (mEnragedState == true) { mSpeed = 500; }

	switch (mMoveSwitch) {
	case 0:
		Translate(-Vec2_Right * mSpeed * mTimer->DeltaTime(), World);
		break;
	case 1:
		Translate(Vec2_Right * mSpeed * mTimer->DeltaTime(), World);
		break;
	default:
		Translate(Vec2_Right * mSpeed * mTimer->DeltaTime(), World);
		break;
	}

	if (Position().x >= Graphics::SCREEN_WIDTH * 0.5f + 200) {
		mMoveSwitch = 0;
	}
	else if (Position().x <= Graphics::SCREEN_WIDTH * 0.5f - 200) {
		mMoveSwitch = 1;
	}
}

