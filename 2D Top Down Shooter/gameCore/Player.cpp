#include "Player.h"

vec2f Player::playerCenter = vec2f::vec2();
vec2f Player::aimDirNorm = vec2f::vec2();
vec2f Player::aimDir = vec2f::vec2();

void Player::Precache() {

	PRECACHE_SPRITE("resource/player/player.png");
}

void Player::Spawn() {

	/*SET_TEXTURE(&m_texture);*/

	this->x = 200;
	this->y = 300;
	this->dx = 0.f;
	this->dy = 0.f;

	this->w = 56; // 258
	this->h = 56; // 152

	this->speed = 5.f;

	this->health = 100;
	this->armor = 0;

	this->angle = 0.0;

	this->status = 1;

	this->fire = false;
	this->reload = false;
	this->isReloading = false;
	this->act = true;

	this->weapon = Weapon::WeaponBase();
	this->itemSlot = 0;
}

void Player::MotionEvent() {

	if (CBase::CEvent->type == SDL_KEYDOWN && CBase::CEvent->key.repeat == 0 && act) {
		switch (CBase::CEvent->key.keysym.sym)
		{
		case SDLK_UP: case SDLK_w:
		{
			dy -= speed;
		}break;

		case SDLK_DOWN: case SDLK_s:
		{
			dy += speed;
		}break;

		case SDLK_LEFT: case SDLK_a:
		{
			dx -= speed;
		}break;

		case SDLK_RIGHT: case SDLK_d:
		{
			dx += speed;
		}break;
		}
	}
	else if (CBase::CEvent->type == SDL_KEYUP && CBase::CEvent->key.repeat == 0 && act)
	{
		switch (CBase::CEvent->key.keysym.sym)
		{
		case SDLK_UP: case SDLK_w:
		{
			dy += speed;
		}break;

		case SDLK_DOWN: case SDLK_s:
		{
			dy -= speed;
		}break;

		case SDLK_LEFT: case SDLK_a:
		{
			dx += speed;
		}break;

		case SDLK_RIGHT: case SDLK_d:
		{
			dx -= speed;
		}break;
		}
	}

	if (CBase::CEvent->type == SDL_MOUSEBUTTONDOWN && CBase::CEvent->button.button == SDL_BUTTON_LEFT && status && act)
	{
		if (!reload)
			fire = true;
	}
	else if (CBase::CEvent->type == SDL_MOUSEBUTTONUP && CBase::CEvent->button.button == SDL_BUTTON_LEFT && status && act)
	{
		fire = false;
	}

	if (CBase::CEvent->type == SDL_KEYDOWN && CBase::CEvent->key.keysym.sym == SDLK_r && !reload && status && act)
	{
		if (weapon.ammoMag < weapon.magCap && weapon.ammoCurrent > 0) {
			PlaySound(&weapon.soundReload, 1);
			fire = false;
			reload = true;
		}
	}
}

void Player::Move() {

	if (act) {
		x += dx;

		y += dy;
	}

	if (health <= 0)
	{
		status = 0;

		health = 0;
		armor = 0;

		speed = 0.f;

		dx = 0.f;
		dy = 0.f;

		fire = false;
		reload = false;
		isReloading = false;
	}
	else if (act && status)
	{
		angle = GetAngle(x, y, CBase::mouse.x, CBase::mouse.y, -90);

		playerCenter.x = x + w / 2;
		playerCenter.y = y + h / 2;

		aimDir = CBase::mousef - playerCenter;
		aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	}
}

void Player::Update() {

	if (status) {
	
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
	}

	texture.RenderTexture(CBase::CRenderer, &rect, NULL, angle);
}

void Player::UpdateA() {

	if (act && status) { weapon.angle = GetAngle(x + w / 2, y + h / 2, CBase::mouse.x, CBase::mouse.y, -180); }

	weapon.UpdateB(x + w / 2, y + h / 2, weapon.angle);
	texture.RenderTexture(x, y, CBase::CRenderer, NULL, angle);
}
