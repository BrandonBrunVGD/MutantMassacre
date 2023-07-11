#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mMenuSwitch = 0;

	// top bar entities
	//mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 80.0f);
	//mPlayerOne = new GLTexture("1UP", "emulogic.ttf", 32, { 200, 0, 0 });
	//mPlayerTwo = new GLTexture("2UP", "emulogic.ttf", 32, { 200, 0, 0 });
	//mHiScore = new GLTexture("HI SCORE", "emulogic.ttf", 32, { 200, 0, 0 });
	//mPlayerOneScore = new Scoreboard();
	//mPlayerTwoScore = new Scoreboard();
	//mTopScore = new Scoreboard();

	//mTopBar->Parent(this);
	//mPlayerOne->Parent(mTopBar);
	//mPlayerTwo->Parent(mTopBar);
	//mHiScore->Parent(mTopBar);
	//mPlayerOneScore->Parent(mTopBar);
	//mPlayerTwoScore->Parent(mTopBar);
	//mTopScore->Parent(mTopBar);

	//mPlayerOne->Position(-Graphics::SCREEN_WIDTH * 0.35f, 0.0f);
	//mPlayerTwo->Position(Graphics::SCREEN_WIDTH * 0.2f, 0.0f);
	//mHiScore->Position(-30.0f, 0.0f);

	//mPlayerOneScore->Position(-Graphics::SCREEN_WIDTH * 0.23f, 40.0f);
	//mPlayerTwoScore->Position(Graphics::SCREEN_WIDTH * 0.32f, 40.0f);
	//mTopScore->Position(Graphics::SCREEN_WIDTH * 0.05f, 40.0f);

	//mTopScore->Score(645987);

	//Background
	mBackground = new GLTexture("Background.png", 0, 0, 1920, 1080);
	mBackground->Parent(this);
	mBackground->Position(1920/2, 1080/2);

	// logo entities
	mLogo = new GLTexture("MutantMassacreLogo.png", 0, 0, 1236, 532);
	//mAnimatedLogo = new AnimatedGLTexture("GalagaLogo.png", 0, 0, 360, 180, 3, 0.2f, Animation::Layouts::Vertical);

	mLogo->Parent(this);
	//mAnimatedLogo->Parent(this);

	mLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);
	//mAnimatedLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);

	mSpaceBar = new GLTexture("Space.png");
	mSpaceBar->Parent(this);
	mSpaceBar->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.75);

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
	//mOnePlayerMode = new GLTexture("1 Player ", "emulogic.ttf", 32, { 230, 230, 230 });
	//mTwoPlayerMode = new GLTexture("2 Players", "emulogic.ttf", 32, { 230, 230, 230 });
	mCursor = new GLTexture("ProfileSelector.png");

	mProfiles->Parent(this);
	//mOnePlayerMode->Parent(mPlayModes);
	//mTwoPlayerMode->Parent(mPlayModes);
	mCursor->Parent(this);

	//mOnePlayerMode->Position(0.0f, -35.0f);
	//mTwoPlayerMode->Position(0.0f, 35.0f);
	mCursor->Position(Graphics::SCREEN_WIDTH * 0.3, Graphics::SCREEN_HEIGHT * 0.75);

	mCursorStartPos = mCursor->Position(Local);
	mCursorOffset = Vector2(Graphics::SCREEN_WIDTH * 0.2, 0.0f);
	mSelectedProfile = 0;

	// bottom bar entities
	//mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
	//mNamco = new GLTexture("namcot", "namco__.ttf", 36, { 200, 0, 0 });
	//mDates = new GLTexture("1981 1985 NAMCO LTD.", "emulogic.ttf", 32, { 230, 230, 230 });
	//mRights = new GLTexture("ALL RIGHTS RESERVED", "emulogic.ttf", 32, { 230, 230, 230 });

	//mBottomBar->Parent(this);
	//mNamco->Parent(mBottomBar);
	//mDates->Parent(mBottomBar);
	//mRights->Parent(mBottomBar);

	//mNamco->Position(Vec2_Zero);
	//mDates->Position(0.0f, 90.0f);
	//mRights->Position(0.0f, 170.0f);

	// screen animation variables
	//ResetAnimation();

	/*mStars = BackgroundStars::Instance();
	mStars->Scroll(true);*/
}


StartScreen::~StartScreen() {
	// top bar entities
	//delete mTopBar;
	//mTopBar = nullptr;
	//delete mPlayerOne;
	//mPlayerOne = nullptr;
	//delete mPlayerTwo;
	//mPlayerTwo = nullptr;
	//delete mHiScore;
	//mHiScore = nullptr;
	//delete mPlayerOneScore;
	//mPlayerOneScore = nullptr;
	//delete mPlayerTwoScore;
	//mPlayerTwoScore = nullptr;
	//delete mTopScore;
	//mTopScore = nullptr;

	delete mBackground;
	mBackground = nullptr;
	// logo entities
	delete mLogo;
	mLogo = nullptr;
	//delete mAnimatedLogo;
	//mAnimatedLogo = nullptr;

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
	//delete mOnePlayerMode;
	//mOnePlayerMode = nullptr;
	//delete mTwoPlayerMode;
	//mTwoPlayerMode = nullptr;
	delete mCursor;
	mCursor = nullptr;

	// bottom bar entities
	//delete mBottomBar;
	//mBottomBar = nullptr;
	//delete mNamco;
	//mNamco = nullptr;
	//delete mDates;
	//mDates = nullptr;
	//delete mRights;
	//mRights = nullptr;

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

	/*switch (mProfileSwitch) {
	case 1:
		mSelectedProfile = 0;
		break;
	case 2:
		mSelectedProfile = 1;
		break;
	case 3:
		mSelectedProfile = 2;
		break;
	}*/

	if (mProfileSwitch < 0) {
		mProfileSwitch = 2;
	}
	else if (mProfileSwitch > 2) {
		mProfileSwitch = 0;
	}

	mCursor->Position(mCursorStartPos + mCursorOffset * (float)mProfileSwitch);
}

void StartScreen::Update() {
	//if (!mAnimationDone) {
		//mAnimationTimer += mTimer->DeltaTime();
		//Position(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		//if (mAnimationTimer >= mAnimationTotalTime) {
			//mAnimationDone = true;
			//mStars->Scroll(false);
		//}

		//if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP)) {
			//mAnimationTimer = mAnimationTotalTime;
		//}
	//}
	//else {
		//mAnimatedLogo->Update();

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
	//mPlayerOne->Render();
	//mPlayerTwo->Render();
	//mHiScore->Render();
	//mPlayerOneScore->Render();
	//mPlayerTwoScore->Render();
	//mTopScore->Render();

	//if (!mAnimationDone) {

	//}
	//else {
		//mAnimatedLogo->Render();

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
	
	//}

	//mOnePlayerMode->Render();
	//mTwoPlayerMode->Render();
	//mCursor->Render();

	//mNamco->Render();
	//mDates->Render();
	//mRights->Render();
}