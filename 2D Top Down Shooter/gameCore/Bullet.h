#pragma once

#include "CBase.h"

class Bullet : public Entity {

public:

	Bullet() { Precache(); }
	~Bullet() { texture.FreeTexture(); }

	virtual void Precache();
	virtual void Update();

	virtual void BlitRotated(int x, int y, float angle);
};

class bullet_762 : public Bullet {

public:

	bullet_762() { Precache(); Spawn(); }
	~bullet_762() { texture.FreeTexture(); }

	void Precache();
	void Spawn();
	void Update();

	void BlitRotated(int x, int y, float angle);
};

class bullet_45acp : public Bullet {

};

class bullet_9mm : public Bullet {

public:

	bullet_9mm() { Precache(); Spawn(); }
	~bullet_9mm() { texture.FreeTexture(); }

	void Precache();
	void Spawn();
	//void Update();

	//void BlitRotated(int x, int y, float angle);
};