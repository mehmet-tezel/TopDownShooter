#include "WeaponSystem.h"

void WeaponSystem(Player* player, InventorySystem* inv) {

	switch (player->weapon.id)
	{
	case WEAPON_AK47:
		FireAK47(player, inv);
		break;
	case WEAPON_GLOCK17:
		FireGlock17(player, inv);
		break;
	default:
		break;
	}
	
}

void ReloadSystem(Player* player, InventorySystem* inv) {

	switch (player->weapon.id)
	{
	case WEAPON_AK47:
		ReloadAK47(player, inv);
		break;
	case WEAPON_GLOCK17:
		ReloadGlock17(player, inv);
		break;
	default:
		break;
	}

}

void ReloadAK47(Player* player, InventorySystem* inv) {

	if (player->reload)
	{
		player->weapon.reloadTimer.StartTimer();

		if (player->weapon.reloadTimer.GetTicks() >= player->weapon.reloadTime) {

			player->reload = false;
			player->weapon.reloadTimer.StopTimer();

			if (player->weapon.ammoCurrent > 0 && player->weapon.ammoMag < player->weapon.magCap) {

				if (player->weapon.ammoCurrent <= player->weapon.magCap && (player->weapon.ammoCurrent + player->weapon.ammoMag) < player->weapon.magCap)
				{
					player->weapon.ammoMag += player->weapon.ammoCurrent;
					player->weapon.ammoCurrent -= player->weapon.ammoCurrent;
				}
				else
				{
					int magCurrent = player->weapon.magCap - player->weapon.ammoMag;
					player->weapon.ammoMag += magCurrent;
					player->weapon.ammoCurrent -= magCurrent;
				}

				if (!inv->mainItem.empty() && player->itemSlot == 1)
				{
					inv->mainItem[0]->ammoMag = player->weapon.ammoMag;
					inv->mainItem[0]->ammoCurrent = player->weapon.ammoCurrent;
				}
				else if (!inv->secondItem.empty() && player->itemSlot == 2)
				{
					inv->secondItem[0]->ammoMag = player->weapon.ammoMag;
					inv->secondItem[0]->ammoCurrent = player->weapon.ammoCurrent;
				}
				else if (!inv->thirdItem.empty() && player->itemSlot == 3)
				{
					inv->thirdItem[0]->ammoMag = player->weapon.ammoMag;
					inv->thirdItem[0]->ammoCurrent = player->weapon.ammoCurrent;
				}
			}
		}
	}
}

void FireAK47(Player* player, InventorySystem* inv) {
	
	if (player->fire)
	{
		if (player->weapon.ammoMag > 0)
		{
			if (player->weapon.fireTimer.GetTicks() >= player->weapon.rof)
			{
				PlaySound(&player->weapon.soundFire, 0);

				Bullet* toShoot = new bullet_762();
				toShoot->x = player->playerCenter.x;
				toShoot->y = player->playerCenter.y;
				toShoot->dx = player->aimDirNorm.x * toShoot->speed;
				toShoot->dy = player->aimDirNorm.y * toShoot->speed;
				toShoot->angle = GetAngle(toShoot->x, toShoot->y, CBase::mouse.x, CBase::mouse.y, -180);

				player->weapon.bullets.push_back(toShoot);
				player->weapon.ammoMag -= 1;

				if (!inv->mainItem.empty() && player->itemSlot == 1)
				{
					inv->mainItem[0]->ammoMag -= 1;
				}
				else if (!inv->secondItem.empty() && player->itemSlot == 2)
				{
					inv->secondItem[0]->ammoMag -= 1;
				}
				else if (!inv->thirdItem.empty() && player->itemSlot == 3)
				{
					inv->thirdItem[0]->ammoMag -= 1;
				}

				player->weapon.fireTimer.StopTimer();
				player->weapon.fireTimer.StartTimer();
			}
		}
		else
		{
			PlaySound(&player->weapon.soundEmpty, 2);
		}
	}

	for (Bullet* bullet : player->weapon.bullets) {
		bullet->BlitRotated(bullet->x, bullet->y, bullet->angle);
	}

	for (player->weapon.itBullet = player->weapon.bullets.begin(); player->weapon.itBullet != player->weapon.bullets.end();)
	{
		(*player->weapon.itBullet)->x += (*player->weapon.itBullet)->dx;
		(*player->weapon.itBullet)->y += (*player->weapon.itBullet)->dy;

		if ((*player->weapon.itBullet)->x > CBase::CScreenWidth || (*player->weapon.itBullet)->y > CBase::CScreenHeight || (*player->weapon.itBullet)->x < 0 || (*player->weapon.itBullet)->y < 0)
		{
			player->weapon.itBullet = player->weapon.bullets.erase(player->weapon.itBullet);
		}
		else
		{
			++player->weapon.itBullet;
		}
	}
}

void ReloadGlock17(Player* player, InventorySystem* inv) {

	if (player->reload)
	{
		player->weapon.reloadTimer.StartTimer();

		if (player->weapon.reloadTimer.GetTicks() >= player->weapon.reloadTime) {

			player->reload = false;
			player->weapon.reloadTimer.StopTimer();

			if (player->weapon.ammoCurrent > 0 && player->weapon.ammoMag < player->weapon.magCap) {

				if (player->weapon.ammoCurrent <= player->weapon.magCap && (player->weapon.ammoCurrent + player->weapon.ammoMag) < player->weapon.magCap)
				{
					player->weapon.ammoMag += player->weapon.ammoCurrent;
					player->weapon.ammoCurrent -= player->weapon.ammoCurrent;
				}
				else
				{
					int magCurrent = player->weapon.magCap - player->weapon.ammoMag;
					player->weapon.ammoMag += magCurrent;
					player->weapon.ammoCurrent -= magCurrent;
				}

				if (!inv->mainItem.empty() && player->itemSlot == 1)
				{
					inv->mainItem[0]->ammoMag = player->weapon.ammoMag;
					inv->mainItem[0]->ammoCurrent = player->weapon.ammoCurrent;
				}
				else if (!inv->secondItem.empty() && player->itemSlot == 2)
				{
					inv->secondItem[0]->ammoMag = player->weapon.ammoMag;
					inv->secondItem[0]->ammoCurrent = player->weapon.ammoCurrent;
				}
				else if (!inv->thirdItem.empty() && player->itemSlot == 3)
				{
					inv->thirdItem[0]->ammoMag = player->weapon.ammoMag;
					inv->thirdItem[0]->ammoCurrent = player->weapon.ammoCurrent;
				}
			}
		}
	}
}

void FireGlock17(Player* player, InventorySystem* inv) {

	if (player->fire)
	{
		if (player->weapon.ammoMag > 0)
		{
			if (player->weapon.fireTimer.GetTicks() >= player->weapon.rof)
			{
				PlaySound(&player->weapon.soundFire, 0);

				Bullet* toShoot = new bullet_9mm();
				toShoot->x = player->playerCenter.x;
				toShoot->y = player->playerCenter.y;
				toShoot->dx = player->aimDirNorm.x * toShoot->speed;
				toShoot->dy = player->aimDirNorm.y * toShoot->speed;
				toShoot->angle = GetAngle(toShoot->x, toShoot->y, CBase::mouse.x, CBase::mouse.y, -180);

				player->weapon.bullets.push_back(toShoot);
				player->weapon.ammoMag -= 1;
				
				if (!inv->mainItem.empty() && player->itemSlot == 1)
				{
					inv->mainItem[0]->ammoMag -= 1;
				}
				else if (!inv->secondItem.empty() && player->itemSlot == 2)
				{
					inv->secondItem[0]->ammoMag -= 1;
				}
				else if (!inv->thirdItem.empty() && player->itemSlot == 3)
				{
					inv->thirdItem[0]->ammoMag -= 1;
				}

				player->fire = false;

				player->weapon.fireTimer.StopTimer(); 
				player->weapon.fireTimer.StartTimer();

			}
		}
		else
		{
			PlaySound(&player->weapon.soundEmpty, 2);
		}
	}

	for (Bullet* bullet : player->weapon.bullets) {
		bullet->BlitRotated(bullet->x, bullet->y, bullet->angle);
	}

	for (player->weapon.itBullet = player->weapon.bullets.begin(); player->weapon.itBullet != player->weapon.bullets.end();)
	{
		(*player->weapon.itBullet)->x += (*player->weapon.itBullet)->dx;
		(*player->weapon.itBullet)->y += (*player->weapon.itBullet)->dy;

		if ((*player->weapon.itBullet)->x > CBase::CScreenWidth || (*player->weapon.itBullet)->y > CBase::CScreenHeight || (*player->weapon.itBullet)->x < 0 || (*player->weapon.itBullet)->y < 0)
		{
			player->weapon.itBullet = player->weapon.bullets.erase(player->weapon.itBullet);
		}
		else
		{
			++player->weapon.itBullet;
		}
	}
}