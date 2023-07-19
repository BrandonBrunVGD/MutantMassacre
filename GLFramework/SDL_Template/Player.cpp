#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_D)) {
		Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
		mWalkingLeft = false;
		mWalkingRight = true;
		if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
			Translate(Vec2_Right * (mMoveSpeed * 20) * mTimer->DeltaTime(), World);
		}
	}
	else if (mInput->KeyDown(SDL_SCANCODE_A)) {
		Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
		mWalkingRight = false;
		mWalkingLeft = true;
		if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
			Translate(-Vec2_Right * (mMoveSpeed * 20) * mTimer->DeltaTime(), World);
		}
	}
	else { mWalkingRight = false; mWalkingLeft = false; }

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

	if (mCanShoot) {		
		if (mInput->MouseButtonPressed(InputManager::MouseButton::Left)) {
			
			
		}
	}

	Vector2 pos = Position(Local);
	if (pos.x - mPlayer->GetWidth() / 2 < 0) {
		pos.x = 0 + mPlayer->GetWidth() / 2;
	}
	else if (pos.x + mPlayer->GetWidth()/2 > mMoveBounds.x) {
		pos.x = mMoveBounds.x - mPlayer->GetWidth() / 2;
	}

	if (pos.y - mPlayer->GetHeight() / 2 < 0) {
		pos.y = 0 + mPlayer->GetHeight() / 2;
	}
	else if (pos.y + mPlayer->GetHeight() / 2 > mMoveBounds.y) {
		pos.y = mMoveBounds.y - mPlayer->GetHeight() / 2;
	}

	Position(pos);
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mHp = 10;

	mPlayer = new GLTexture("CharacterWalkAnim.png", 0, 0, 338, 338);
	mPlayer->Parent(this);
	mPlayer->Position(Vec2_Zero);
	mPlayer->Scale(Vector2(0.50f, 0.50f));

	mMoveSpeed = 450.0f;
	mMoveBounds = Vector2(1920, 1080);

	mWalkAnim = new AnimatedGLTexture("CharacterWalkAnim.png", 0, 0, 330, 330, 5, 0.75f, Animation::Layouts::Horizontal);
	mWalkAnim->Parent(this);
	mWalkAnim->Position(Vec2_Zero);
	mWalkAnim->SetWrapMode(Animation::WrapModes::Loop);
	mWalkAnim->Scale(Vector2(0.50f, 0.50f));

	mWalkAnimLeft = new AnimatedGLTexture("CharacterWalkAnimLeft.png", 0, 0, 330, 330, 5, 0.75f, Animation::Layouts::Horizontal);
	mWalkAnimLeft->Parent(this);
	mWalkAnimLeft->Position(Vec2_Zero);
	mWalkAnimLeft->SetWrapMode(Animation::WrapModes::Loop);
	mWalkAnimLeft->Scale(Vector2(0.50f, 0.50f));

	AddCollider(new BoxCollider(Vector2(16.0f, 67.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mWalkAnim;
	mWalkAnim = nullptr;

	delete mWalkAnimLeft;
	mWalkAnimLeft = nullptr;
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
		mHp -= 1;
		mWasHit = true;
	}
}

bool Player::WasHit() {
	return mWasHit;
}

void Player::Update() {
	
	mWalkAnim->Update();
	mWalkAnimLeft->Update();

	if (Active()) {
		HandleMovement();
	}
		
}

void Player::Render() {
	if (mVisible) {
		
		if (mWalkingRight) {
			mWalkAnim->Render();
		}
		else if (mWalkingLeft) {
			mWalkAnimLeft->Render();
		}
		else mPlayer->Render();
		
	}

	PhysEntity::Render();
}