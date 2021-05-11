#pragma once

#include "Player.h"

using Items = Weapon;

class Player;

// This class is useless for now but will be updated in the future
class FirstAid : public Items {

public:

	FirstAid() { Precache(); Spawn(); }
	~FirstAid() {}

	void Precache()
	{
		PRECACHE_SPRITE("resource/textures/first_aid.png");
		LOAD_TEXTURE("resource/textures/icon-first_aid.png", &icon);
	}

	void Spawn()
	{
		this->x = 0;
		this->y = 0;
		this->dx = 0;
		this->dy = 0;

		this->w = 50;
		this->h = 50;

		this->rect = { 0, 0, 50, 50 };

		this->angle = 0.f;

		this->status = 1;
	}
};

class InventorySystem : public Items {

public:
	InventorySystem() { Precache(); SetInventory(); }
	~InventorySystem() { texture.FreeTexture(); }

	void Precache();
	void SetInventory();
	void Event(Player* player);
	void UpdateInventory(Player* player);
	void AddItem(Items* item);

	/* special event */
	void isWindowResized();

	std::vector<Items*> items, mainItem, secondItem, thirdItem;
	std::vector<Items*>::iterator itItems;

	int invSlot = 0;
	uint32_t inventorySize;

private:
	bool itemOp = false;
	bool itemClick = false;
	bool invResized = false;
};

