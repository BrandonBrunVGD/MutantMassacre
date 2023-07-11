#ifndef __GUIMANAGER_H
#define __GUIMANAGER_H
#include "PhysicsManager.h"

class GUIManager : public PhysEntity {
private:

	Texture* mKey;

	std::string mTexture;
	bool mVisible;
	bool mAnimating;

public:

	GUIManager(std::string texture);
	virtual ~GUIManager();

	void Update() override;
	void Render() override;

	void Visible(bool visible);

	void InitKey(std::string key);
};
#endif