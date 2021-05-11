#include "Weapons.h"

// 
// m4a1
//
/*void M4A1::Precache() {

	// load weapon texture
	//m_texture.LoadTexture("img/m4a1.png", CRenderer);
	//LOAD_TEXTURE("img/m4a1.png", &m_texture);
	PRECACHE_SPRITE("img/m4a1.png");
}

void M4A1::Spawn() {

	// weapon properties

	this->name = "M4A1";

	this->ammoCurrent = 90;
	this->ammoMag = 30;

	this->damage = 1.13f;
	this->criticalDamage = 0.3f;
	this->penetration = 0.17f;
	this->rof = 1.f;
	this->range = 100.5f;

	this->firstFire = false;

	this->id = id_m4a1;
	this->type = AR;
	this->slot = AR;
}

/*void M4A1::Update() {

	rect.x = x;
	rect.y = y;

	m_texture.RenderTexture(CBase::CRenderer, &rect, NULL, angle);
}

void M4A1::UpdateA() {

	m_texture.RenderTexture(x, y, CBase::CRenderer);
}
*/

//
// ak47
//
void AK47::Precache() {

	// load weapon texture
	PRECACHE_SPRITE("resource/weapons/ak47/ak47.png");
	LOAD_TEXTURE("resource/weapons/ak47/icon-ak47.png", &icon);
	PRECACHE_SOUND("resource/weapons/ak47/ak47.wav");
	LOAD_SOUND("resource/weapons/ak47/Reload.wav", &soundReload);
	LOAD_SOUND("resource/sounds/Empty.wav", &soundEmpty);
}

void AK47::Spawn() {

	// weapon properties

	this->name = "AK47";
	
	this->bullet = ak_bullet;

	this->x = 0;
	this->y = 0;
	this->w = 256;
	this->h = 32;
	this->rect.w = 256;
	this->rect.h = 32;

	this->ammoMax = 90;
	this->ammoCurrent = 30;
	this->ammoMag = 30;
	this->magCap = 30;

	this->damage = 1.13f;
	this->criticalDamage = 0.3f;
	this->penetration = 1.17f;
	this->rof = 100.94f;
	this->range = 105.7f;
	this->reloadTime = 2000.0f;

	this->reload = false;
	this->firstFire = false;
	this->automatic = true;

	this->id = id_ak47;
	this->type = AR;
	this->slot = AR;

	this->fireTimer.SetTimerAndStart(this->rof);
}

/*void AK47::Update() {

	rect.x = x;
	rect.y = y;

	m_texture.RenderTexture(CBase::CRenderer, &rect, NULL, angle);
}
*/
void AK47::UpdateA() {

	texture.RenderTexture(x, y, CBase::CRenderer, NULL, angle);
}

void AK47::UpdateB(int x, int y, float angle) {

	SDL_Rect dstRect;

	dstRect.x = x;
	dstRect.y = y;
	SDL_QueryTexture(texture.GetTexture(), NULL, NULL, &dstRect.w, &dstRect.h);

	dstRect.w = w;
	dstRect.h = h;

	dstRect.x -= (dstRect.w / 2);
	dstRect.y -= (dstRect.h / 2);

	texture.RenderTexture(CBase::CRenderer, &dstRect, NULL, angle);
}

void Glock17::Precache() {

	PRECACHE_SPRITE("resource/weapons/glock17/pistol.png");
	LOAD_TEXTURE("resource/weapons/glock17/icon-glock17.png", &icon);
	PRECACHE_SOUND("resource/weapons/glock17/glock17.wav");
	LOAD_SOUND("resource/weapons/glock17/Reload.wav", &soundReload);
	LOAD_SOUND("resource/sounds/Empty.wav", &soundEmpty);
}

void Glock17::Spawn() {

	this->name = "Glock17";

	this->bullet = glock_bullet;

	this->x = 0;
	this->y = 0;
	this->w = 96;
	this->h = 32;
	this->rect.w = 96;
	this->rect.h = 32;

	this->ammoMax = 120;
	this->ammoCurrent = 20;
	this->ammoMag = 20;
	this->magCap = 20;

	this->damage = 0.74f;
	this->criticalDamage = 0.1f;
	this->penetration = 0.07f;
	this->rof = 120.09f;
	this->range = 83.7f;
	this->reloadTime = 2000.0f;

	this->reload = false;
	this->firstFire = false;
	this->automatic = false;

	this->id = id_glock17;
	this->type = PISTOL;
	this->slot = PISTOL;

	this->fireTimer.SetTimerAndStart(this->rof);
}