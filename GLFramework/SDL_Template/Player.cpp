#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_D)) {
		Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);

		if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
			Translate(Vec2_Right * (mMoveSpeed * 20) * mTimer->DeltaTime(), World);
		}
	}
	else if (mInput->KeyDown(SDL_SCANCODE_A)) {
		Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);

		if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
			Translate(-Vec2_Right * (mMoveSpeed * 20) * mTimer->DeltaTime(), World);
		}
	}

	if (mInput->KeyDown(SDL_SCANCODE_W)) {
		Translate(-Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);

		if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
			Translate(-Vec2_Up * (mMoveSpeed * 20) * mTimer->DeltaTime(), World);
		}
	}
	else if (mInput->KeyDown(SDL_SCANCODE_S)) {
		Translate(Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);

		if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
			Translate(Vec2_Up * (mMoveSpeed * 20) * mTimer->DeltaTime(), World);
		}
	}

	//Vector2 pos = Position(Local);
	//if (pos.x < mMoveBounds.x) {
		//pos.x = mMoveBounds.x;
	//}
	//else if (pos.x > mMoveBounds.y) {
		//pos.x = mMoveBounds.y;
	//}

	//Position(pos);
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mHp = 1000;

	mShip = new GLTexture("PlayerShips.png", 0, 0, 60, 64);
	mShip->Parent(this);
	mShip->Position(Vec2_Zero);

	mMoveSpeed = 450.0f;
	mMoveBounds = Vector2(1920, 1080);

	mDeathAnimation = new AnimatedGLTexture("PlayerExplosion.png", 0, 0, 128, 128, 4, 1.0f, Animation::Layouts::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(Animation::WrapModes::Once);

	AddCollider(new BoxCollider(Vector2(16.0f, 67.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mShip;
	mShip = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;
}

void Player::Visible(bool visible) {
	mVisible = visible;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mHp;
}

void Player::AddScore(int change) {
	mScore += change;
}

bool Player::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Player::Hit(PhysEntity* other) {
	if (other->GetTag() == "enemy") {
		mHp -= 1;		
		mWasHit = true;
	}
	else if (other->GetTag() == "eBullet") {
		mHp -= 100;
		mWasHit = true;
	}
}

bool Player::WasHit() {
	return mWasHit;
}

void Player::Update() {
	if (mAnimating) {

		if (mWasHit) {
			mWasHit = false;
		}

		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	}
	else {
		if (Active()) {
			std::cout << mHp << std::endl;
			HandleMovement();
		}
	}
}

void Player::Render() {
	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else {
			mShip->Render();
		}
	}

	PhysEntity::Render();
}