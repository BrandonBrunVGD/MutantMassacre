#include "Gun.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

void Gun::HandleMovement() {

}

void Gun::HandleFiring() {
	if (mCanShoot) {
		if (mTag == "player gun") {
			if (mInput->MouseButtonPressed(InputManager::MouseButton::Left)) {
				Bullet* bullet = new Bullet(mBulletTexture, Position(), mInput->MousePosition(), true);
				bullet->SetTag("pBullet");
				mPBullets.push_back(bullet);

			}
		}	
	}
}

void Gun::EnemyFiring() {
	if (mTag == "enemy gun" && mCanShoot) {

		switch (mShootPatterns)	{
		case 1:
			mEnemyFireTimer -= 1 * mTimer->DeltaTime(); 
			if (mEnemyFireTimer <= 0) { mEnemyFireTimer = 60; ShootPattern1(); mShootPatterns = 2; }
			
			break;
		case 2:
			mEnemyFireTimer -= 1 * mTimer->DeltaTime();
			if (mEnemyFireTimer <= 0) { mEnemyFireTimer = 60; ShootPattern2(); mShootPatterns = 1; }
			
			break;
		default:
			break;
		}		
	}
}

void Gun::ShootPattern1() {
	Bullet* bullet1_1 = new Bullet(mBulletTexture, Position(), Vector2(0, 0), false);
	bullet1_1->SetTag("eBullet");
	mEBullets.push_back(bullet1_1);

	Bullet* bullet1_2 = new Bullet(mBulletTexture, Position(), Vector2(1920/2, 0), false);
	bullet1_2->SetTag("eBullet");
	mEBullets.push_back(bullet1_2);

	Bullet* bullet1_3 = new Bullet(mBulletTexture, Position(), Vector2(1920, 0), false);
	bullet1_3->SetTag("eBullet");
	mEBullets.push_back(bullet1_3);

	Bullet* bullet1_4 = new Bullet(mBulletTexture, Position(), Vector2(0, 1080/2), false);
	bullet1_4->SetTag("eBullet");
	mEBullets.push_back(bullet1_4);

	Bullet* bullet1_5 = new Bullet(mBulletTexture, Position(), Vector2(1920, 1080/2), false);
	bullet1_5->SetTag("eBullet");
	mEBullets.push_back(bullet1_5);

	Bullet* bullet1_6 = new Bullet(mBulletTexture, Position(), Vector2(0, 1080), false);
	bullet1_6->SetTag("eBullet");
	mEBullets.push_back(bullet1_6);

	Bullet* bullet1_7 = new Bullet(mBulletTexture, Position(), Vector2(1920/2, 1080), false);
	bullet1_7->SetTag("eBullet");
	mEBullets.push_back(bullet1_7);

	Bullet* bullet1_8 = new Bullet(mBulletTexture, Position(), Vector2(1920, 1080), false);
	bullet1_8->SetTag("eBullet");
	mEBullets.push_back(bullet1_8);
}
void Gun::ShootPattern2() {
	Bullet* bullet2_1 = new Bullet(mBulletTexture, Position(), Vector2(480, 0), false);
	bullet2_1->SetTag("eBullet");
	mEBullets.push_back(bullet2_1);

	Bullet* bullet2_2 = new Bullet(mBulletTexture, Position(), Vector2(1440, 0), false);
	bullet2_2->SetTag("eBullet");
	mEBullets.push_back(bullet2_2);

	Bullet* bullet2_3 = new Bullet(mBulletTexture, Position(), Vector2(0, 270), false);
	bullet2_3->SetTag("eBullet");
	mEBullets.push_back(bullet2_3);

	Bullet* bullet2_4 = new Bullet(mBulletTexture, Position(), Vector2(1920, 270), false);
	bullet2_4->SetTag("eBullet");
	mEBullets.push_back(bullet2_4);

	Bullet* bullet2_5 = new Bullet(mBulletTexture, Position(), Vector2(0, 810), false);
	bullet2_5->SetTag("eBullet");
	mEBullets.push_back(bullet2_5);

	Bullet* bullet2_6 = new Bullet(mBulletTexture, Position(), Vector2(1920, 810), false);
	bullet2_6->SetTag("eBullet");
	mEBullets.push_back(bullet2_6);

	Bullet* bullet2_7 = new Bullet(mBulletTexture, Position(), Vector2(480, 1080), false);
	bullet2_7->SetTag("eBullet");
	mEBullets.push_back(bullet2_7);

	Bullet* bullet2_8 = new Bullet(mBulletTexture, Position(), Vector2(1440, 1080), false);
	bullet2_8->SetTag("eBullet");
	mEBullets.push_back(bullet2_8);

	Bullet* bullet2_9 = new Bullet(mBulletTexture, Position(), Vector2(1920 / 2, 0), false);
	bullet2_9->SetTag("eBullet");
	mEBullets.push_back(bullet2_9);

	Bullet* bullet2_10 = new Bullet(mBulletTexture, Position(), Vector2(1920/2, 1080), false);
	bullet2_10->SetTag("eBullet");
	mEBullets.push_back(bullet2_10);
}

Gun::Gun(std::string tag) {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mCanShoot = true;

	mGunTag = tag;

	if (mGunTag == "starter gun") {
		mGun = new GLTexture("StarterBlaster.png");
		mGun->Parent(this);
		mGun->Position(Vec2_Zero);
		mGun->Scale(Vector2(0.1f, 0.1f));
		mBulletTexture = "normal";
	}
	else if (mGunTag == "crab gun") {
		mGun = new GLTexture("CrabGun.png");
		mGun->Parent(this);
		mGun->Position(Vec2_Zero);
		mGun->Scale(Vector2(0.25f, 0.25f));
		mBulletTexture = "crab?";
	}

	mMoveBounds = Vector2(1920, 1080);
	mTargetPos = Vec2_Zero;

	mEnemyFireTimer = 60;
	mShootPatterns = 1;

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

	if (mAnimating) {

	}
	else {
		if (Active()) {
			HandleFiring();
			EnemyFiring();
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
			//std::cout << "bullet deleted" << std::endl;
		}
		else {
			++it;
		}
	}
	for (auto it = mEBullets.begin(); it != mEBullets.end();) {

		if ((*it)->WasHit()) {
			mDelEBullets.push_back(*it);
			it = mEBullets.erase(it);
			//std::cout << "bullet deleted" << std::endl;
		}
		else if ((*it)->Position().y < -OFFSCREEN_BUFFER) {
			mDelEBullets.push_back(*it);
			it = mEBullets.erase(it);
			//std::cout << "bullet deleted" << std::endl;
		}
		else if ((*it)->Position().y > 1080 + OFFSCREEN_BUFFER) {
			mDelEBullets.push_back(*it);
			it = mEBullets.erase(it);
			//std::cout << "bullet deleted" << std::endl;
		}
		else if ((*it)->Position().x < -OFFSCREEN_BUFFER) {
			mDelEBullets.push_back(*it);
			it = mEBullets.erase(it);
			//std::cout << "bullet deleted" << std::endl;
		}
		else if ((*it)->Position().x > 1920 + OFFSCREEN_BUFFER) {
			mDelEBullets.push_back(*it);
			it = mEBullets.erase(it);
			//std::cout << "bullet deleted" << std::endl;
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

	
}

void Gun::Render() {
	for (auto b : mPBullets) {
		b->Render();
	}

	for (auto b : mEBullets) {
		b->Render();
	}

	if (mGun != nullptr) {
		mGun->Render();
	}

	PhysEntity::Render();
}

void Gun::CanShoot(bool shoot) {
	mCanShoot = shoot;
}

void Gun::SetTargetPos(Vector2 pos) {
	mTargetPos = pos;
}