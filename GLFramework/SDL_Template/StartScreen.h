#ifndef __STARTSCREEN_H
#define __STARTSCREEN_H
#include "AnimatedGLTexture.h"
#include "InputManager.h"
//#include "BackgroundStars.h"
#include "Scoreboard.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {

private:
	Timer* mTimer;
	InputManager* mInput;

	// Top Bar Entities
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mPlayerTwo;
	Texture* mHiScore;
	Scoreboard* mPlayerOneScore;
	Scoreboard* mPlayerTwoScore;
	Scoreboard* mTopScore;

	Texture* mBackground;
	// Logo Entities
	Texture* mLogo;
	//AnimatedGLTexture* mAnimatedLogo;
	Texture* mSpaceBar;
	
	// Profiles
	GameEntity* mProfiles;
	Texture* mProfile1;
	Texture* mProfile1Text;
	Texture* mProfile2;
	Texture* mProfile2Text;
	Texture* mProfile3;
	Texture* mProfile3Text;
	Texture* mCursor;

	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;
	int mSelectedProfile;

	int mProfileSwitch;

	// Bottom Bar Entities
	GameEntity* mBottomBar;
	Texture* mNamco;
	Texture* mDates;
	Texture* mRights;

	// Screen Animation Variables
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

	// stars
	//BackgroundStars* mStars;

	int mMenuSwitch;

public:
	StartScreen();
	~StartScreen();

	void ResetAnimation();

	int SelectedProfile();

	void ChangeSelectedProfile(int change);

	void Update() override;
	void Render() override;

	int getMenuSwitch() { return mMenuSwitch; }
};
#endif