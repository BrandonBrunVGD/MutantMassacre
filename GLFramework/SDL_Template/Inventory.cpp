#include "Inventory.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Inventory::Inventory() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mSocketOffset = 200;

	mCanOpen = false;
	mOpen = false;
	mOnItem = false;
	mSelectedSocket = -1;
	mSelectedEquipeSocket = -1;
	mMove = true;

	mInventorySpace = -1;

	mEmptySocket = 0;
	
	mCreateGun = "null";
	mDeleteItems = false;
	mDelCrystals = 2;
	mDelShells = 2;

	mBackground = new GLTexture("Inventory.png", 0, 0, 1920, 1080);
	mBackground->Parent(this);
	mBackground->Position(Vector2(1920/2, 1080/2));
	
	InventorySocketInit();
	EquipedSocketInit();

	
	CreateItem(mRareGun, "rare", "Gun", "starter gun");
	CreateItem(mRareArti, "rare", "Arti", "rare ring");
	CreateItem(mEpicArti, "epic", "Helm", "iron helm");
	//CreateItem(mCrabGun, "legendary", "Gun", "crab gun");

	//mMoveBounds = Vector2(1920, 1080);

	Visible(true);
}

Inventory::~Inventory() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mBackground;
	mBackground = nullptr;

	for (auto b : mSockets) {
		delete b;
	}

	for (auto b : mEquipedSockets) {
		delete b;
	}

	for (auto b : mInventoryVec) {
		delete b;
	}


	for (auto b : mEquipedGunVec) { delete b; }
	for (auto b : mEquipedHelmVec) { delete b; }
	for (auto b : mEquipedChestVec) { delete b; }
	for (auto b : mEquipedBootsVec) { delete b; }
	for (auto b : mEquipedArtiVec) { delete b; }
}

void Inventory::Visible(bool visible) {
	mVisible = visible;
}

bool Inventory::IsAnimating() {
	return mAnimating;
}

bool Inventory::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Inventory::Update() {

	if (mCanOpen) {
		Open();
		Close();
	}

	for (int i = 0; i < MAX_SOCKETS; ++i) {
		if (mSockets[i]->GetFull() == false) {
			mEmptySocket = i;

		}
	}

	if (mOpen) { 
		for (int i = 0; i < MAX_SOCKETS; ++i) {
			if (mSockets[i]->GetSelected() == true) {
				mSelectedSocket = i;
			}
		}
		for (int i = 0; i < MAX_EQUIPED; ++i) {
			if (mEquipedSockets[i]->GetSelected() == true) {
				mSelectedSocket = i;
			}
		}
		
		Equipe(); 
		UnEquipe();
		Move();
	}
	
	int crystalAmount = 0;
	int shellAmount = 0;

	for (int i = 0; i < mInventoryVec.size(); ++i) {
		mInventoryVec[i]->Update();
		if (mInventoryVec[i]->GetTag() == "crystal shard") {
			crystalAmount += 1;
		}
		if (mInventoryVec[i]->GetTag() == "crab shell") {
			shellAmount += 1;
		}
	}
	mCrystalShardAmount = crystalAmount;
	mCrabShellAmount = shellAmount;
	crystalAmount = 0;
	shellAmount = 0;
	
	if (mOpen) {
		mBackground->Update();
			
		for (int i = 0; i < MAX_SOCKETS; ++i) {
			mSockets[i]->Update();
		}
		for (int i = 0; i < MAX_EQUIPED; ++i) {
			mEquipedSockets[i]->Update();
		}
		for (int i = 0; i < mInventoryVec.size(); ++i) {
			mInventoryVec[i]->Update();
				
		}

		for (auto b : mEquipedGunVec) { b->Update(); }
		for (auto b : mEquipedHelmVec) { b->Update(); }
		for (auto b : mEquipedChestVec) { b->Update(); }
		for (auto b : mEquipedBootsVec) { b->Update(); }
		for (auto b : mEquipedArtiVec) { b->Update(); }
	}

		for (int i = 0; i < mInventoryVec.size(); ++i) {
			if (mInventoryVec[i]->GetTag() == "crystal shard" && mDeleteItems) {
				mDelCrystals -= 1;
				mSockets[mInventoryVec[i]->GetLastSocket()]->SetFull(false);
				mInventoryVec.erase(mInventoryVec.begin() + i);
				mInventorySpace -= 1;						
				if (mDelCrystals == 0) { break; mDelCrystals = 2; }
				
			}
		}

		for (int i = 0; i < mInventoryVec.size(); ++i) {
			if (mInventoryVec[i]->GetTag() == "crab shell" && mDeleteItems) {
				mDelShells -= 1;
				mSockets[mInventoryVec[i]->GetLastSocket()]->SetFull(false);
				mInventoryVec.erase(mInventoryVec.begin() + i);
				mInventorySpace -= 1;				
				if (mDelShells == 0) { break; mDelShells = 2; }
				
			}
		}
}

void Inventory::Render() {

	if (mVisible) {
		if (mOpen) {
			mBackground->Render();
			
			for (int i = 0; i < MAX_SOCKETS; ++i) {
				mSockets[i]->Render();
			}
			for (int i = 0; i < MAX_EQUIPED; ++i) {
				mEquipedSockets[i]->Render();
			}
			for (int i = 0; i < mInventoryVec.size(); ++i) {
				mInventoryVec[i]->Render();
			}

			for (auto b : mEquipedGunVec) { b->Render(); }
			for (auto b : mEquipedHelmVec) { b->Render(); }
			for (auto b : mEquipedChestVec) { b->Render(); }
			for (auto b : mEquipedBootsVec) { b->Render(); }
			for (auto b : mEquipedArtiVec) { b->Render(); }
		}	
	}

	PhysEntity::Render();
}

void Inventory::Open() {
	if (mInput->KeyPressed(SDL_SCANCODE_I)) {
		mOpen = true;
		SetTag("menu");
		
		for (int i = 0; i < MAX_SOCKETS; ++i) {
			mSockets[i]->SetInventoryOpen(true);
		}
		for (int i = 0; i < MAX_EQUIPED; ++i) {
			mEquipedSockets[i]->SetInventoryOpen(true);
		}
	}
}

void Inventory::Close() {
	if (mOpen) {
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
			mOpen = false;
			IgnoreCollisions();
			SetTag("null");

			for (int i = 0; i < MAX_SOCKETS; ++i) {
				mSockets[i]->SetInventoryOpen(false);
			}
			for (int i = 0; i < MAX_EQUIPED; ++i) {
				mEquipedSockets[i]->SetInventoryOpen(false);
			}
		}
	}
}

void Inventory::Equipe() {

	for (int i = 0; i < mInventoryVec.size(); ++i) {
		
		if (mInventoryVec[i]->GetSelected() == true && mInventoryVec[i]->GetItemType() != "Mat") {
			
			if (mInput->MouseButtonPressed(InputManager::MouseButton::Right)) {
				
				if (mInventoryVec[i]->GetItemType() == "Gun") {
					if (mEquipedSockets[0]->GetFull() == true) {
						mInventoryVec.push_back(mEquipedGunVec[0]);
						mInventorySpace += 1;
						mInventoryVec[mInventorySpace]->Position(mSockets[mEmptySocket]->Position());
						mInventoryVec[mInventorySpace]->Scale(Vector2(0.70f, 0.70f));
						mInventoryVec[mInventorySpace]->SetLastPos(mInventoryVec[mInventorySpace]->Position());
						mInventoryVec[mInventorySpace]->SetEquiped(false);
						mEquipedGunVec.clear();
						mEquipedSockets[0]->SetFull(false);
						mSockets[mEmptySocket]->SetFull(true);
						mInventoryVec[mInventorySpace]->SetLastSocket(mEmptySocket);
						mCreateGun = "null";
					}
					else {
						mEquipedGunVec.push_back(mInventoryVec[i]);
						mEquipedGunVec[0]->Position(mEquipedSockets[0]->Position());
						mEquipedGunVec[0]->SetLastPos(mEquipedGunVec[0]->Position());
						mEquipedGunVec[0]->Scale(Vector2(1.0f, 1.0f));
						mEquipedGunVec[0]->SetEquiped(true);
						mEquipedSockets[0]->SetFull(true);
						mSockets[mInventoryVec[i]->GetLastSocket()]->SetFull(false);
						mInventoryVec.erase(mInventoryVec.begin() + i);
						mInventorySpace -= 1;
						ApplyEquipe();
					}
				}
				else if (mInventoryVec[i]->GetItemType() == "Helm") {
					if (mEquipedSockets[1]->GetFull() == true) {
						mInventoryVec.push_back(mEquipedHelmVec[0]);
						mInventorySpace += 1;
						mInventoryVec[mInventorySpace]->Position(mSockets[mEmptySocket]->Position());
						mInventoryVec[mInventorySpace]->Scale(Vector2(0.70f, 0.70f));
						mInventoryVec[mInventorySpace]->SetLastPos(mInventoryVec[mInventorySpace]->Position());
						mInventoryVec[mInventorySpace]->SetEquiped(false);
						mEquipedHelmVec.clear();
						mEquipedSockets[1]->SetFull(false);
						mSockets[mEmptySocket]->SetFull(true);
						mInventoryVec[mInventorySpace]->SetLastSocket(mEmptySocket);
					}
					else {
						mEquipedHelmVec.push_back(mInventoryVec[i]);
						mEquipedHelmVec[0]->Position(mEquipedSockets[1]->Position());
						mEquipedHelmVec[0]->SetLastPos(mEquipedHelmVec[0]->Position());
						mEquipedHelmVec[0]->Scale(Vector2(1.0f, 1.0f));
						mEquipedHelmVec[0]->SetEquiped(true);
						mEquipedSockets[1]->SetFull(true);
						mSockets[mInventoryVec[i]->GetLastSocket()]->SetFull(false);
						mInventoryVec.erase(mInventoryVec.begin() + i);
						mInventorySpace -= 1;
					}
				}
				else if (mInventoryVec[i]->GetItemType() == "Chest") {
					if (mEquipedSockets[2]->GetFull() == true) {
						mInventoryVec.push_back(mEquipedChestVec[0]);
						mInventorySpace += 1;
						mInventoryVec[mInventorySpace]->Position(mSockets[mEmptySocket]->Position());
						mInventoryVec[mInventorySpace]->Scale(Vector2(0.70f, 0.70f));
						mInventoryVec[mInventorySpace]->SetLastPos(mInventoryVec[mInventorySpace]->Position());
						mInventoryVec[mInventorySpace]->SetEquiped(false);
						mEquipedChestVec.clear();
						mEquipedSockets[2]->SetFull(false);
						mSockets[mEmptySocket]->SetFull(true);
						mInventoryVec[mInventorySpace]->SetLastSocket(mEmptySocket);
					}
					else {
						mEquipedChestVec.push_back(mInventoryVec[i]);
						mEquipedChestVec[0]->Position(mEquipedSockets[2]->Position());
						mEquipedChestVec[0]->SetLastPos(mEquipedChestVec[0]->Position());
						mEquipedChestVec[0]->Scale(Vector2(1.0f, 1.0f));
						mEquipedChestVec[0]->SetEquiped(true);
						mEquipedSockets[2]->SetFull(true);
						mSockets[mInventoryVec[i]->GetLastSocket()]->SetFull(false);
						mInventoryVec.erase(mInventoryVec.begin() + i);
						mInventorySpace -= 1;
					}
				}
				else if (mInventoryVec[i]->GetItemType() == "Boots") {
					if (mEquipedSockets[3]->GetFull() == true) {
						mInventoryVec.push_back(mEquipedBootsVec[0]);
						mInventorySpace += 1;
						mInventoryVec[mInventorySpace]->Position(mSockets[mEmptySocket]->Position());
						mInventoryVec[mInventorySpace]->Scale(Vector2(0.70f, 0.70f));
						mInventoryVec[mInventorySpace]->SetLastPos(mInventoryVec[mInventorySpace]->Position());
						mInventoryVec[mInventorySpace]->SetEquiped(false);
						mEquipedBootsVec.clear();
						mEquipedSockets[3]->SetFull(false);
						mSockets[mEmptySocket]->SetFull(true);
						mInventoryVec[mInventorySpace]->SetLastSocket(mEmptySocket);
					}
					else {
						mEquipedBootsVec.push_back(mInventoryVec[i]);
						mEquipedBootsVec[0]->Position(mEquipedSockets[3]->Position());
						mEquipedBootsVec[0]->SetLastPos(mEquipedBootsVec[0]->Position());
						mEquipedBootsVec[0]->Scale(Vector2(1.0f, 1.0f));
						mEquipedBootsVec[0]->SetEquiped(true);
						mEquipedSockets[3]->SetFull(true);
						mSockets[mInventoryVec[i]->GetLastSocket()]->SetFull(false);
						mInventoryVec.erase(mInventoryVec.begin() + i);
						mInventorySpace -= 1;
					}
				}
				else if (mInventoryVec[i]->GetItemType() == "Arti") {
					if (mEquipedSockets[4]->GetFull() == true) {
						mInventoryVec.push_back(mEquipedArtiVec[0]);
						mInventorySpace += 1;
						mInventoryVec[mInventorySpace]->Position(mSockets[mEmptySocket]->Position());
						mInventoryVec[mInventorySpace]->Scale(Vector2(0.70f, 0.70f));
						mInventoryVec[mInventorySpace]->SetLastPos(mInventoryVec[mInventorySpace]->Position());
						mInventoryVec[mInventorySpace]->SetEquiped(false);
						mEquipedArtiVec.clear();
						mEquipedSockets[4]->SetFull(false);
						mSockets[mEmptySocket]->SetFull(true);
						mInventoryVec[mInventorySpace]->SetLastSocket(mEmptySocket);
					}
					else {
						mEquipedArtiVec.push_back(mInventoryVec[i]);
						mEquipedArtiVec[0]->Position(mEquipedSockets[4]->Position());
						mEquipedArtiVec[0]->SetLastPos(mEquipedArtiVec[0]->Position());
						mEquipedArtiVec[0]->Scale(Vector2(1.0f, 1.0f));
						mEquipedArtiVec[0]->SetEquiped(true);
						mEquipedSockets[4]->SetFull(true);
						mSockets[mInventoryVec[i]->GetLastSocket()]->SetFull(false);
						mInventoryVec.erase(mInventoryVec.begin() + i);
						mInventorySpace -= 1;
					}
				}
				
				
			}
		}
	}
}

void Inventory::UnEquipe() {

	if (mEquipedSockets[0]->GetSelected() == true && mEquipedSockets[0]->GetFull() == true) {

		if (mInput->MouseButtonPressed(InputManager::MouseButton::Right)) {
			mInventoryVec.push_back(mEquipedGunVec[0]);
			mInventorySpace += 1;
			mInventoryVec[mInventorySpace]->Position(mSockets[mEmptySocket]->Position());
			mInventoryVec[mInventorySpace]->Scale(Vector2(0.70f, 0.70f));
			mInventoryVec[mInventorySpace]->SetLastPos(mSockets[mEmptySocket]->Position());
			mInventoryVec[mInventorySpace]->SetEquiped(false);
			mEquipedGunVec.clear();
			mEquipedSockets[0]->SetFull(false);
			mInventoryVec[mInventorySpace]->SetLastSocket(mEmptySocket);
			mSockets[mEmptySocket]->SetFull(true);		
			mCreateGun = "null";
		}
	}
	else if (mEquipedSockets[1]->GetSelected() == true && mEquipedSockets[1]->GetFull() == true) {
		if (mInput->MouseButtonPressed(InputManager::MouseButton::Right)) {
			mInventoryVec.push_back(mEquipedHelmVec[0]);
			mInventorySpace += 1;
			mInventoryVec[mInventorySpace]->Position(mSockets[mEmptySocket]->Position());
			mInventoryVec[mInventorySpace]->Scale(Vector2(0.70f, 0.70f));
			mInventoryVec[mInventorySpace]->SetLastPos(mInventoryVec[mInventorySpace]->Position());
			mInventoryVec[mInventorySpace]->SetEquiped(false);
			mEquipedHelmVec.clear();
			mEquipedSockets[1]->SetFull(false);
			mSockets[mEmptySocket]->SetFull(true);
			mInventoryVec[mInventorySpace]->SetLastSocket(mEmptySocket);
		}
	}
	else if (mEquipedSockets[2]->GetSelected() == true && mEquipedSockets[2]->GetFull() == true) {
		if (mInput->MouseButtonPressed(InputManager::MouseButton::Right)) {
			mInventoryVec.push_back(mEquipedChestVec[0]);
			mInventorySpace += 1;
			mInventoryVec[mInventorySpace]->Position(mSockets[mEmptySocket]->Position());
			mInventoryVec[mInventorySpace]->Scale(Vector2(0.70f, 0.70f));
			mInventoryVec[mInventorySpace]->SetLastPos(mInventoryVec[mInventorySpace]->Position());
			mInventoryVec[mInventorySpace]->SetEquiped(false);
			mEquipedChestVec.clear();
			mEquipedSockets[2]->SetFull(false);
			mSockets[mEmptySocket]->SetFull(true);
			mInventoryVec[mInventorySpace]->SetLastSocket(mEmptySocket);
		}
	}
	else if (mEquipedSockets[3]->GetSelected() == true && mEquipedSockets[3]->GetFull() == true) {
		if (mInput->MouseButtonPressed(InputManager::MouseButton::Right)) {
			mInventoryVec.push_back(mEquipedBootsVec[0]);
			mInventorySpace += 1;
			mInventoryVec[mInventorySpace]->Position(mSockets[mEmptySocket]->Position());
			mInventoryVec[mInventorySpace]->Scale(Vector2(0.70f, 0.70f));
			mInventoryVec[mInventorySpace]->SetLastPos(mInventoryVec[mInventorySpace]->Position());
			mInventoryVec[mInventorySpace]->SetEquiped(false);
			mEquipedBootsVec.clear();
			mEquipedSockets[3]->SetFull(false);
			mSockets[mEmptySocket]->SetFull(true);
			mInventoryVec[mInventorySpace]->SetLastSocket(mEmptySocket);
		}
	}
	else if (mEquipedSockets[4]->GetSelected() == true && mEquipedSockets[4]->GetFull() == true) {
		if (mInput->MouseButtonPressed(InputManager::MouseButton::Right)) {
			mInventoryVec.push_back(mEquipedArtiVec[0]);
			mInventorySpace += 1;
			mInventoryVec[mInventorySpace]->Position(mSockets[mEmptySocket]->Position());
			mInventoryVec[mInventorySpace]->Scale(Vector2(0.70f, 0.70f));
			mInventoryVec[mInventorySpace]->SetLastPos(mInventoryVec[mInventorySpace]->Position());
			mInventoryVec[mInventorySpace]->SetEquiped(false);
			mEquipedArtiVec.clear();
			mEquipedSockets[4]->SetFull(false);
			mSockets[mEmptySocket]->SetFull(true);
			mInventoryVec[mInventorySpace]->SetLastSocket(mEmptySocket);
		}
	}
		
}

void Inventory::Move() {

	for (int i = 0; i < mInventoryVec.size(); ++i) {

		if (mInventoryVec[i]->GetSelected() == true) {
			mInventoryVec[i]->SetLastSocket(mSelectedSocket);
			if (mInput->MouseButtonDown(InputManager::MouseButton::Left)) {
				mInventoryVec[i]->Position(mInput->MousePosition());
			}

			if (mInput->MouseButtonReleased(InputManager::MouseButton::Left)) {
				if (mSelectedSocket == -1) {
					mInventoryVec[i]->Position(mInventoryVec[i]->GetLastPos());
				}
				else {
					mSockets[mInventoryVec[i]->GetLastSocket()]->SetFull(false);
					mSockets[mSelectedSocket]->SetFull(true);
					if (mSockets[mSelectedSocket]->GetEquipeSocket() == false) {
						mInventoryVec[i]->Position(mSockets[mSelectedSocket]->Position());
						mInventoryVec[i]->SetLastPos(mInventoryVec[i]->Position());
						mSelectedSocket = -1;
					}
				}
			}
		}
	}
}

void Inventory::CreateItem(Item* name, std::string rarity, std::string type, std::string item) {
	for (int i = 0; i < MAX_SOCKETS; ++i) {
		if (mSockets[i]->GetFull() == false) {
			mEmptySocket = i;

		}
	}
	name = new Item(rarity, type, item);
	name->SetTag(item);
	mInventoryVec.push_back(name);
	mInventorySpace += 1;
	mInventoryVec[mInventorySpace]->Position(mSockets[mEmptySocket]->Position());
	mInventoryVec[mInventorySpace]->Scale(Vector2(0.70f, 0.70f));
	mInventoryVec[mInventorySpace]->SetLastPos(mInventoryVec[mInventorySpace]->Position());
	mSockets[mEmptySocket]->SetFull(true);
	mInventoryVec[mInventorySpace]->SetLastSocket(mInventorySpace);
}

void Inventory::EquipedSocketInit() {
	for (int i = 0; i < MAX_EQUIPED; ++i) {
		mEquipedSockets[i] = new InventorySocket();
		mEquipedSockets[i]->Parent(mBackground);
		mEquipedSockets[i]->SetSocketTag(i);
		mEquipedSockets[i]->Active();
		mEquipedSockets[i]->SetEquipeSocket(true);
		mEquipedSockets[i]->SetFull(false);
	}
	mEquipedSockets[0]->Position(Vector2(840, -425));
	mEquipedSockets[1]->Position(Vector2(840, -425 + mSocketOffset));
	mEquipedSockets[2]->Position(Vector2(840, -425 + mSocketOffset * 2));
	mEquipedSockets[3]->Position(Vector2(840, -425 + mSocketOffset * 3));
	mEquipedSockets[4]->Position(Vector2(840, -425 + mSocketOffset * 4));
}

void Inventory::InventorySocketInit() {
	//Create Sockets
	for (int i = 0; i < MAX_SOCKETS; ++i) {
		mSockets[i] = new InventorySocket();
		mSockets[i]->Scale(Vector2(0.70f, 0.70f));
		mSockets[i]->SetEquipeSocket(false);
		mSockets[i]->SetFull(false);
	}
	//Position Sockets
	for (int i = 0; i < 5; ++i) {
		mSockets[i]->SetSocketTag(i);
		mSockets[i]->Position(100.0f + (130 * (i % 5)), 100.0f);

	}
	for (int i = 5; i < 10; ++i) {
		mSockets[i]->SetSocketTag(i);
		mSockets[i]->Position(100.0f + (130 * (i % 5)), 100.0f + (125 * 1));

	}
	for (int i = 10; i < 15; ++i) {
		mSockets[i]->SetSocketTag(i);
		mSockets[i]->Position(100.0f + (130 * (i % 5)), 100.0f + (125 * 2));

	}
	for (int i = 15; i < 20; ++i) {
		mSockets[i]->SetSocketTag(i);
		mSockets[i]->Position(100.0f + (130 * (i % 5)), 100.0f + (125 * 3));

	}
	for (int i = 20; i < 25; ++i) {
		mSockets[i]->SetSocketTag(i);
		mSockets[i]->Position(100.0f + (130 * (i % 5)), 100.0f + (125 * 4));

	}
}

void Inventory::AddItem(std::string tag) {
	if (tag == "crystal") { CreateItem(mCrystalShard, "epic", "Mat", "crystal shard"); }
	else if (tag == "crab shell") { CreateItem(mCrabShell, "epic", "Mat", "crab shell"); }
	else if (tag == "crab gun") { CreateItem(mCrabGun, "legendary", "Gun", "crab gun"); }
}

void Inventory::ApplyEquipe() {
	if (mEquipedGunVec[0]->GetItemName() == "starter gun") {
		mCreateGun = "starter gun";
	}
	else if (mEquipedGunVec[0]->GetItemName() == "crab gun") {
		mCreateGun = "crab gun";
	}
}