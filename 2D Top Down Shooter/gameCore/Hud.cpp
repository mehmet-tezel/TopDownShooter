#include "Hud.h"

void Hud::Precache() {

	LOAD_FONT("resource/fonts/SourceSansPro-Bold.otf", &healthBarPerc, 12);
	LOAD_FONT("resource/fonts/SourceSansPro-Bold.otf", &ammoText, 12);
}

void Hud::Spawn(Player* player) {

	healthBar = { 0 + 25, 0 + 25, player->health, 10 };
	ammoRect = { 0 + 150, 0 + 25 };
}

void Hud::Update(Player* player) {

	if (player->health > 0) {

		healthBar = { 0 + 25, 0 + 25, player->health, 10 };
	
		SDL_SetRenderDrawColor(CBase::CRenderer, 0, 255, 255, 255);
		SDL_RenderFillRect(CBase::CRenderer, &healthBar);
	}

	healthBarPerc.UpdateText("%" + std::to_string(player->health), healthColor, CBase::CRenderer);
	healthBarPerc.RenderText(healthBar.x + healthBar.w / 2 - healthBarPerc.GetWidth() / 2, healthBar.y + healthBar.h / 2 - healthBarPerc.GetHeight() / 2, CBase::CRenderer);

	ammoText.UpdateText(player->weapon.name + "  " + std::to_string(player->weapon.ammoMag) + " / " + std::to_string(player->weapon.ammoCurrent), ammoColor, CBase::CRenderer);
	ammoText.RenderText(150, 23, CBase::CRenderer);
}