#pragma once

#include <HyperTexture.h>
#include "CBase.h"
#include "Bullet.h"

/* Includes all weapon IDs in game */
typedef enum WeaponIDs {

	no_weaponID,

	id_combat,
	id_glock17,
	id_usp,
	id_uzi,
	id_m4a1,
	id_ak47,
	id_awp,
	id_minigun
};

/* Includes all weapon types in game */
typedef enum WeaponTypes {

	// none
	no_weaponType,
	no_weaponSlot = 0,

	KNIFE,
	PISTOL,
	SHOTGUN,
	SMG,
	ASSAULTRIFLE,
	AR = 5, // same with ASSAULTRIFLE
	SNIPER,
	HEAVY,

} WeaponSlots;

/* Base entity class for all weapon classes. */
class WeaponEntity {

public:

	WeaponEntity() {}
	~WeaponEntity() {}

	// weapon name
	std::string name;

	// bullet
	Bullet bullet;
	std::vector<Bullet*> bullets;
	std::vector<Bullet*>::iterator itBullet;

	// number of ammos in the mag
	int ammoMag;
	
	// max ammo capacity
	int ammoMax;

	// current ammo
	int ammoCurrent;

	// max magazine capacity
	int magCap;

	float damage;
	float criticalDamage;

	// armor penetration rate
	float penetration;
	
	// attack speed, rate of fire
	float rof;
 
	//float cycleTime;

	float range;
	float reloadTime;

	Hyper::Timer reloadTimer;
	Hyper::Timer fireTimer;

	// first shoot
	bool firstFire;

	// holds whether the gun is semi-automatic or fully automatic
	bool automatic;

	/* game properties */

	int id;
	int type;
	int slot;
};

class WeaponBase : public WeaponEntity, public Entity {

public:

	WeaponBase() { Precache(); }
	~WeaponBase() { texture.FreeTexture(); soundFire.~Sound(); soundReload.~Sound(); soundEmpty.~Sound(); fireTimer.FreeTimer(); reloadTimer.FreeTimer(); }

	/*void LoadWeaponTexture(std::string path) {
	
		m_texture.LoadTexture(path, CBase::CRenderer);
	}*/

	virtual void Precache();
	virtual void Update();
	virtual void UpdateA();
	virtual void UpdateB(int x, int y, float angle);

	Hyper::Sound soundFire;
	Hyper::Sound soundReload;
	Hyper::Sound soundEmpty;
	Hyper::Sound soundDraw;
};

/* weapon defines start */

#define WEAPON_NONE			no_weaponID
#define WEAPON_COMBAT		id_combat
#define WEAPON_GLOCK17		id_glock17
#define WEAPON_USP			id_usp
#define WEAPON_UZI			id_uzi
#define WEAPON_M4A1			id_m4a1
#define WEAPON_AK47			id_ak47
#define WEAPON_AWP			id_awp
#define WEAPON_MINIGUN		id_minigun

/* weapon defines end */