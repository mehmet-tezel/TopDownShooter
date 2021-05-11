#include "Bullet.h"

void Bullet::Precache() {

	this->x = 0;
	this->y = 0;

	this->dx = 0;
	this->dy = 0;
	
	this->angle = 0.0;
	
	this->rect = { 0 , 0 , 0 , 0 };

	this->speed = 0.f;
	
	this->status = 0;
}

void Bullet::Update() {

	rect.x = x;
	rect.y = y;

	texture.RenderTexture(CBase::CRenderer, &rect, NULL, angle);
}

void Bullet::BlitRotated(int x, int y, float angle) {

	SDL_Rect dstRect;

	dstRect.x = x;
	dstRect.y = y;
	SDL_QueryTexture(texture.GetTexture(), NULL, NULL, &dstRect.w, &dstRect.h);

	dstRect.w = rect.w;
	dstRect.h = rect.h;

	dstRect.x -= (dstRect.w / 2);
	dstRect.y -= (dstRect.h / 2);

	texture.RenderTexture(CBase::CRenderer, &dstRect, NULL, angle);
}

void bullet_762::Precache() {

	PRECACHE_SPRITE("resource/textures/bullet-762.png");
}

void bullet_762::Spawn() {

	this->x = 0;
	this->y = 0;
	this->dx = 0;
	this->dy = 0;

	this->w = 25;
	this->h = 10;

	this->angle = 0.0;

	this->rect = { 0 , 0 , 25 , 10 };

	this->speed = 100.f;

	this->status = 1;
}

void bullet_762::Update() {

	rect.x = x;
	rect.y = y;

	texture.RenderTexture(CBase::CRenderer, &rect, NULL, angle);
}

void bullet_762::BlitRotated(int x, int y, float angle) {

	SDL_Rect dstRect;

	dstRect.x = x;
	dstRect.y = y;
	SDL_QueryTexture(texture.GetTexture(), NULL, NULL, &dstRect.w, &dstRect.h);

	dstRect.w = rect.w;
	dstRect.h = rect.h;

	dstRect.x -= (dstRect.w / 2);
	dstRect.y -= (dstRect.h / 2);

	texture.RenderTexture(CBase::CRenderer, &dstRect, NULL, angle);
}

void bullet_9mm::Precache() {

	PRECACHE_SPRITE("resource/textures/bullet-9mm.png");
}

void bullet_9mm::Spawn() {

	this->x = 0;
	this->y = 0;
	this->dx = 0;
	this->dy = 0;

	this->w = 14;
	this->h = 7;

	this->angle = 0.0;

	this->rect = { 0 , 0 , 14 , 7 };

	this->speed = 80.f;

	this->status = 1;
}