#include "Gun.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

void Gun::HandleMovement() {

}

void Gun::HandleFiring() {
	if (mCanShoot) {
		if (mTag == "player gun") {
			if (mInput->MouseButtonPressed(InputManager::MouseButton::Left)) {
				Bullet* bullet = new Bullet(Position(), mInput->MousePosition(), true);
				bullet->SetTag("pBullet");
				mPBullets.push_back(bullet);

			}
		}	
	}
}

void Gun::EnemyFiring() {
	if (mTag == "enemy gun") {
		ShootPattern1();
	}
}

void Gun::ShootPattern1() {
	Bullet* bullet1 = new Bullet(Position(), Vector2(0, 0), true);
	bullet1->SetTag("eBullet");
	mEBullets.push_back(bullet1);

	Bullet* bullet2 = new Bullet(Position(), Vector2(1920/2, 0), true);
	bullet2->SetTag("eBullet");
	mEBullets.push_back(bullet2);

	Bullet* bullet3 = new Bullet(Position(), Vector2(1920, 0), true);
	bullet3->SetTag("eBullet");
	mEBullets.push_back(bullet3);

	Bullet* bullet4 = new Bullet(Position(), Vector2(0, 1080/2), true);
	bullet4->SetTag("eBullet");
	mEBullets.push_back(bullet4);

	Bullet* bullet5 = new Bullet(Position(), Vector2(1920, 1080/2), true);
	bullet5->SetTag("eBullet");
	mEBullets.push_back(bullet5);

	Bullet* bullet6 = new Bullet(Position(), Vector2(0, 1080), true);
	bullet6->SetTag("eBullet");
	mEBullets.push_back(bullet6);

	Bullet* bullet7 = new Bullet(Position(), Vector2(1920/2, 1080), true);
	bullet7->SetTag("eBullet");
	mEBullets.push_back(bullet7);

	Bullet* bullet8 = new Bullet(Position(), Vector2(1920, 1080), true);
	bullet8->SetTag("eBullet");
	mEBullets.push_back(bullet8);
}
void Gun::ShootPattern2() {

}

Gun::Gun() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mCanShoot = true;

	mSomeOtherGun = "SomeOtherTexture.png";
	mSomeGun = "SomeTexture.png";
	mStarterBlaster = "StarterBlaster.png";
	mCurrentTexture = mStarterBlaster;

	mGun = new GLTexture(mCurrentTexture);
	mGun->Parent(this);
	mGun->Position(Vec2_Zero);
	mGun->Scale(Vector2(0.1f, 0.1f));

	mMoveBounds = Vector2(1920, 1080);
	mTargetPos = Vec2_Zero;

	mEnemyFireTimer = 60;

	AddCollider(new BoxCollider(Vector2(16.0f, 67.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}

Gun::~Gun() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mGun;
	mGun = nullptr;

	for (auto b : mPBullets) {
		delete b;
	}

	for (auto b : mEBullets) {
		delete b;
	}
}

void Gun::Visible(bool visible) {
	mVisible = visible;
}

bool Gun::IsAnimating() {
	return mAnimating;
}

bool Gun::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Gun::Update() {

	mEnemyFireTimer -= 1 * mTimer->DeltaTime();
	if (mEnemyFireTimer <= 0) { mEnemyFireTimer = 60; EnemyFiring(); }

	if (mAnimating) {

	}
	else {
		if (Active()) {
			HandleFiring();
		}
	}

	for (auto b : mPBullets) {
		b->Update();
	}

	for (auto b : mEBullets) {
		b->Update();
	}

	for (auto it = mPBullets.begin(); it != mPBullets.end();) {
		
		if ((*it)->WasHit()) {
			mDelPBullets.push_back(*it);
			it = mPBullets.erase(it);
			std::cout << "bullet deleted" << std::endl;
		}
		else {
			++it;
		}
	}
	for (auto it = mEBullets.begin(); it != mEBullets.end();) {

		if ((*it)->WasHit()) {
			mDelEBullets.push_back(*it);
			it = mEBullets.erase(it);
			std::cout << "bullet deleted" << std::endl;
		}
		else {
			++it;
		}
	}

	for (auto b : mDelPBullets) {
		delete b;
	}
	for (auto b : mDelEBullets) {
		delete b;
	}

	mDelPBullets.clear();
	mDelEBullets.clear();

	Vector2 pos = Position(Local);

	Position(pos);

	//Vector2 pos = Position();
	if (pos.y < -OFFSCREEN_BUFFER) {

	}
	else if (pos.y > 1080 + OFFSCREEN_BUFFER) {

	}

	if (pos.x < -OFFSCREEN_BUFFER) {

	}
	else if (pos.x > 1920 + OFFSCREEN_BUFFER) {

	}
}

void Gun::Render() {
	for (auto b : mPBullets) {
		b->Render();
	}

	for (auto b : mEBullets) {
		b->Render();
	}

	mGun->Render();		

	PhysEntity::Render();
}

void Gun::CanShoot(bool shoot) {
	mCanShoot = shoot;
}

void Gun::SetTargetPos(Vector2 pos) {
	mTargetPos = pos;
}