#pragma once

#include "WeaponBase.h"
#include <vector>

using Weapon = WeaponBase;

/*class M4A1 : public Weapon {

public:

	M4A1() { Precache(); Spawn(); }
	~M4A1() { texture.FreeTexture(); }

	void Precache();
	void Spawn();
	//void Update();
	//void UpdateA();
};*/

class AK47 : public Weapon {

public:

	AK47() { Precache(); Spawn(); }
	~AK47() { texture.FreeTexture(); fireTimer.FreeTimer(); reloadTimer.FreeTimer(); }

	void Precache();
	void Spawn();
	//void Update();
	void UpdateA();
	void UpdateB(int x, int y, float angle);

private:

	bullet_762 ak_bullet;
};

class Glock17 : public Weapon {

public:

	Glock17() { Precache(); Spawn(); }
	~Glock17() { texture.FreeTexture(); fireTimer.FreeTimer(); reloadTimer.FreeTimer(); }

	void Precache();
	void Spawn();
	//void UpdateA();
	//void UpdateB(int x, int y, float angle);

private:

	bullet_9mm glock_bullet;
};