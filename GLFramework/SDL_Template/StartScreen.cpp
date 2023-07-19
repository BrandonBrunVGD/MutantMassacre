#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mMenuSwitch = 0;


	//Background
	mBackground = new GLTexture("Background.png", 0, 0, 1920, 1080);
	mBackground->Parent(this);
	mBackground->Position(1920/2, 1080/2);

	// logo entities
	mLogo = new GLTexture("MutantMassacreLogo.png", 0, 0, 1236, 532);

	mLogo->Parent(this);

	mLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);

	mSpaceBar = new GLTexture("SpaceGlow.png");
	mSpaceBar->Parent(this);
	mSpaceBar->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.75);
	mSpaceBar->Scale(Vector2(0.5, 0.5));

	//profile 1
	mProfile1 = new GLTexture("ProfileTexture.png");
	mProfile1->Parent(mProfiles);
	mProfile1->Position(Graphics::SCREEN_WIDTH * 0.3, Graphics::SCREEN_HEIGHT * 0.75);

	mProfile1Text = new GLTexture("Profile 1", "emulogic.ttf", 32, { 255, 255, 255 });
	mProfile1Text->Parent(mProfile1);
	mProfile1Text->Position(0, 0);

	//profile 2
	mProfile2 = new GLTexture("ProfileTexture.png");
	mProfile2->Parent(mProfiles);
	mProfile2->Position(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT * 0.75);

	mProfile2Text = new GLTexture("Profile 2", "emulogic.ttf", 32, { 255, 255, 255 });
	mProfile2Text->Parent(mProfile2);
	mProfile2Text->Position(0, 0);

	//profile 3
	mProfile3 = new GLTexture("ProfileTexture.png");
	mProfile3->Parent(mProfiles);
	mProfile3->Position(Graphics::SCREEN_WIDTH * 0.7, Graphics::SCREEN_HEIGHT * 0.75);

	mProfile3Text = new GLTexture("Profile 3", "emulogic.ttf", 32, { 255, 255, 255 });
	mProfile3Text->Parent(mProfile3);
	mProfile3Text->Position(0, 0);

	// play mode entities
	mProfiles = new GameEntity(Graphics::SCREEN_WIDTH * 0.50f, Graphics::SCREEN_HEIGHT * 0.75f);

	mCursor = new GLTexture("ProfileSelector.png");

	mProfiles->Parent(this);
	
	mCursor->Parent(this);

	
	mCursor->Position(Graphics::SCREEN_WIDTH * 0.3, Graphics::SCREEN_HEIGHT * 0.75);

	mCursorStartPos = mCursor->Position(Local);
	mCursorOffset = Vector2(Graphics::SCREEN_WIDTH * 0.2, 0.0f);
	mSelectedProfile = 0;

}


StartScreen::~StartScreen() {

	delete mBackground;
	mBackground = nullptr;
	// logo entities
	delete mLogo;
	mLogo = nullptr;
	

	delete mSpaceBar;
	mSpaceBar = nullptr;

	//profile 1
	delete mProfile1;
	mProfile1 = nullptr;
	delete mProfile1Text;
	mProfile1Text = nullptr;

	//profile 2
	delete mProfile2;
	mProfile2 = nullptr;
	delete mProfile2Text;
	mProfile2Text = nullptr;

	//profile 3
	delete mProfile3;
	mProfile3 = nullptr;
	delete mProfile3Text;
	mProfile3Text = nullptr;

	// play mode entities
	delete mProfiles;
	mProfiles = nullptr;
	
	delete mCursor;
	mCursor = nullptr;

	mTimer = nullptr;
	mInput = nullptr;
}

void StartScreen::ResetAnimation() {
	mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mAnimationEndPos = Vec2_Zero;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Position(mAnimationStartPos);
}

int StartScreen::SelectedProfile() {
	return mSelectedProfile;
}

void StartScreen::ChangeSelectedProfile(int change) {
	mProfileSwitch += change;

	if (mProfileSwitch < 0) {
		mProfileSwitch = 2;
	}
	else if (mProfileSwitch > 2) {
		mProfileSwitch = 0;
	}

	mCursor->Position(mCursorStartPos + mCursorOffset * (float)mProfileSwitch);
}

void StartScreen::Update() {

		if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
			mMenuSwitch = 1;
		}

		if (mInput->KeyPressed(SDL_SCANCODE_LEFT)) {
			ChangeSelectedProfile(-1);
			std::cout << mProfileSwitch << std::endl;
		}
		else if (mInput->KeyPressed(SDL_SCANCODE_RIGHT)) {
			ChangeSelectedProfile(1);
			std::cout << mProfileSwitch << std::endl;
		}
	//}
}

void StartScreen::Render() {

	mBackground->Render();

	mLogo->Render();
	
	if (mMenuSwitch == 0) {
		mSpaceBar->Render();
	}
	else if (mMenuSwitch == 1) {
		mProfile1->Render();
		mProfile1Text->Render();
		mProfile2->Render();
		mProfile2Text->Render();
		mProfile3->Render();
		mProfile3Text->Render();
		mCursor->Render();
	}
	
}