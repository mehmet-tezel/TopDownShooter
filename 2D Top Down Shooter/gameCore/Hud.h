#pragma once

#include "Player.h"

class Hud {

public:

	Hud() { }
	Hud(Player* player) { Precache(); Spawn(player); }
	~Hud() { healthBarPerc.FreeText(); ammoText.FreeText(); }

	void Precache();
	void Spawn(Player* player);
	void Update(Player* player);

private:

	SDL_Rect healthBar;
	SDL_Color healthColor = { 0, 0, 0, 255 };
	Hyper::Text healthBarPerc;

	SDL_Rect ammoRect;
	SDL_Color ammoColor = { 255, 255, 255, 255 };
	Hyper::Text ammoText;
};

