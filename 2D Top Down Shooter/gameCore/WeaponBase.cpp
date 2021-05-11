#include "WeaponBase.h"

void WeaponBase::Precache() {

	// unused, weapon base class has no texture
	//m_texture.LoadTexture("img/unused.png", CRenderer);

	this->name				= "";

	this->x					= 0;
	this->y					= 0;
	this->w					= 0;
	this->h					= 0;

	this->ammoMax			= 0;
	this->ammoCurrent		= 0;
	this->ammoMag			= 0;
	this->magCap			= 0;

	this->damage			= 0.f;
	this->criticalDamage	= 0.f;
	this->penetration		= 0.f;
	this->rof				= 0.f;
	this->range				= 0.f;

	this->reloadTime		= 0.f;

	this->firstFire			= false;
	this->automatic			= false;

	this->id				= no_weaponID;
	this->type				= no_weaponType;
	this->slot				= no_weaponSlot;
}

void WeaponBase::Update() {

	rect.x = x;
	rect.y = y;

	texture.RenderTexture(CBase::CRenderer, &rect, NULL, angle);
}

void WeaponBase::UpdateA() {

	texture.RenderTexture(x, y, CBase::CRenderer, NULL, angle);
}

void WeaponBase::UpdateB(int x, int y, float angle) {

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