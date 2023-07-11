#ifndef __INVENTORYSOCKET_H
#define __INVENTORYSOCKET_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"

using namespace SDLFramework;

class InventorySocket : public PhysEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	bool mSelected;
	bool mInventoryOpen;
	bool mEquipeSocket;
	bool mFull;

	int mSocketTag;

	Texture* mInventorySocket;
	Texture* mSelector;

private:

public:
	InventorySocket();
	~InventorySocket();

	void Visible(bool visible);
	bool IsAnimating();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

	void Hit(PhysEntity* other) override;
	bool WasHit();

	void Update() override;
	void Render() override;

	void SetSocketTag(int tag);
	void SetInventoryOpen(bool open);
	void SetEquipeSocket(bool equipe);
	void SetFull(bool full);

	bool GetSocketTag() { return mSocketTag; }
	bool GetEquipeSocket() { return mEquipeSocket; }
	bool GetSelected() { return mSelected; }
	bool GetFull() { return mFull; }
};
#endif

