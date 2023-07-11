#include "GUIManager.h"

GUIManager::GUIManager(std::string key) {

	mVisible = false;
	mAnimating = false;

	InitKey(key);

	mKey = new GLTexture(mTexture);
	mKey->Parent(this);
	mKey->Position(Vec2_Zero);
	mKey->Scale(Vector2(0.20f, 0.20f));

	Visible(true);
}

GUIManager::~GUIManager() {

	delete mKey;
	mKey = nullptr;
}

void GUIManager::Update() {
	mKey->Update();
}

void GUIManager::Render() {
	mKey->Render();

	PhysEntity::Render();
}

void GUIManager::Visible(bool visible) {
	mVisible = visible;
}

void GUIManager::InitKey(std::string key) {
	if (key == "E") { mTexture = "EKey.png"; }
}