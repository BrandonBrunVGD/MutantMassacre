#include "GUIManager.h"

GUIManager::GUIManager(std::string key) {

	mVisible = false;
	mAnimating = false;

	InitKey(key);

	mKey = new GLTexture(mTexture);
	mKey->Parent(this);
	mKey->Position(Vec2_Zero);
	mKey->Scale(Vector2(0.20f, 0.20f));

	mDashUI = new GLTexture("DashUI.png");
	mDashUI->Parent(this);
	mDashUI->Position(Vector2(220, 0));
	mDashUI->Scale(Vector2(0.25, 0.25));

	Visible(true);
}

GUIManager::~GUIManager() {

	delete mKey;
	mKey = nullptr;

	delete mDashUI;
	mDashUI = nullptr;

	delete mHeart;
	mHeart = nullptr;
}

void GUIManager::Update() {
	mKey->Update();
	if (mTexture == "SpaceGlow.png") { mDashUI->Update(); }
}

void GUIManager::Render() {
	mKey->Render();
	if (mTexture == "SpaceGlow.png") { mDashUI->Render(); }

	PhysEntity::Render();
}

void GUIManager::Visible(bool visible) {
	mVisible = visible;
}

void GUIManager::InitKey(std::string key) {
	if (key == "E") { mTexture = "EKey.png"; }
	else if (key == "SPACE") { mTexture = "SpaceGlow.png"; }
	else if (key == "HEART") { mTexture = "HealthHeart.png"; }
	else if (key == "HEART_GONE") { mTexture = "HeartGone.png"; }
}