#pragma once

#include "Weapons.h"

class Entity;

class Player : public Entity {

public:

	Player() { Precache(); Spawn(); }
	~Player() { texture.FreeTexture(); if (!weapon.bullets.empty()) { weapon.bullets.clear(); } }

	void Precache();
	void Spawn();
	void MotionEvent();
	void Move();
	void Update();
	void UpdateA();
	
	Weapon weapon;
	int itemSlot;

	static vec2f playerCenter;
	static vec2f aimDirNorm;
	static vec2f aimDir;
};
