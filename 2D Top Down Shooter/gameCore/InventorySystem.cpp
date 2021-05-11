#include "InventorySystem.h"

void InventorySystem::Precache()
{
	PRECACHE_SPRITE("resource/textures/inventory.png");
}

void InventorySystem::SetInventory()
{
	this->w = 700;
	this->h = 400;
	this->rect.w = 700;
	this->rect.h = 400;
	this->x = CBase::CScreenWidth / 2 - this->w / 2;
	this->y = CBase::CScreenHeight / 2 - this->h / 2;
	inventorySize = 10;

	// for testing
	//AK47* p = new AK47();
	//AddItem(p);
}

void InventorySystem::Event(Player* player)
{
	if (CBase::CEvent->type == SDL_KEYDOWN && CBase::CEvent->key.keysym.sym == SDLK_i) {

		if (itemOp)
			itemOp = false;
		else
			itemOp = true;
	}

	if (CBase::CEvent->type == SDL_MOUSEBUTTONDOWN && CBase::CEvent->button.button == SDL_BUTTON_LEFT && CBase::CEvent->button.clicks == 2)
		itemClick = true;
	else
		itemClick = false;


	if (CBase::CEvent->type == SDL_WINDOWEVENT && CBase::CEvent->window.event == SDL_WINDOWEVENT_RESIZED)
		invResized = true;

	if (CBase::CEvent->type == SDL_KEYDOWN)
	{
		switch (CBase::CEvent->key.keysym.sym)
		{
		default:
			break;
		case SDLK_1: {
			if (!player->reload && !player->fire && player->status)
			{
				if (!mainItem.empty()) {
					player->weapon = *mainItem[0];
					player->itemSlot = 1;
				}
			}
		} break;
		case SDLK_2: {
			if (!player->reload && !player->fire && player->status) {
				if (!secondItem.empty()) {
					player->weapon = *secondItem[0];
					player->itemSlot = 2;
				}
			}
		} break;
		case SDLK_3: {
			if (!player->reload && !player->fire && player->status)
				if (!thirdItem.empty()) {
					player->weapon = *thirdItem[0];
					player->itemSlot = 3;
				}
		} break;
		}
	}
}

void InventorySystem::isWindowResized() {

	size_t invItemsCurrentSize = items.size();

	if (!items.empty()) {
		items[0]->x = x + 50;
		items[0]->y = y + 70;
	}

	if (!mainItem.empty())
	{
		mainItem[0]->x = x + 462;
		mainItem[0]->y = y + 137;
	}

	if (!secondItem.empty())
	{
		secondItem[0]->x = x + 533;
		secondItem[0]->y = y + 137;
	}

	if (!thirdItem.empty())
	{
		thirdItem[0]->x = x + 496;
		thirdItem[0]->y = y + 205;
	}

	for (int i = 1; i < invItemsCurrentSize; ++i) {
		//printf("%d\n", itemCurrentSize - 1); // delete this line
		items[i]->x = items[i - 1]->x + 67.5f;
		items[i]->y = items[i - 1]->y;

		if (items[i]->x + 50 > x + 310)
		{
			items[i]->x = x + 50;
			items[i]->y = items[i - 1]->y + 67.5f;
		}

		if (items[i]->y + 70 > y + 350)
		{
			items[i]->x = x + 50;
			items[i]->y = y + 70;
		}

		if (items[i]->x == items[0]->x && items[i]->y == items[0]->y)
		{
			items[i]->x = x + 50;
			items[i]->y = y + 70;
		}
	}
}

void InventorySystem::UpdateInventory(Player* player)
{
	if (itemOp && player->status) {

		player->act = false;
		player->fire = false;
		player->dx = 0;
		player->dy = 0;
		this->x = CBase::CScreenWidth / 2 - this->w / 2;
		this->y = CBase::CScreenHeight / 2 - this->h / 2;
		Update();

		if (invResized) {
		
			isWindowResized();
			invResized = false;
		}
		
		for (Items* item : items)
		{

			item->icon.RenderTexture(item->x, item->y, CBase::CRenderer);
		}

		for (Items* item : mainItem)
		{
			item->icon.RenderTexture(item->x, item->y, CBase::CRenderer);
		}

		for (Items* item : secondItem)
		{
			item->icon.RenderTexture(item->x, item->y, CBase::CRenderer);
		}	
		
		for (Items* item : thirdItem)
		{
			item->icon.RenderTexture(item->x, item->y, CBase::CRenderer);
		}

		for (itItems = items.begin(); itItems != items.end();)
		{

		}

		for (int i = 0; i < items.size(); ++i)
		{
			if (CBase::CDrawCollisions) {
				SDL_SetRenderDrawColor(CBase::CRenderer, 255, 0, 0, 255);
				SDL_RenderDrawLine(CBase::CRenderer, items[i]->x, items[i]->y, items[i]->x + items[i]->icon.GetWidth(), items[i]->y);
				SDL_RenderDrawLine(CBase::CRenderer, items[i]->x, items[i]->y, items[i]->x, items[i]->y + items[i]->icon.GetHeight());
				SDL_RenderDrawLine(CBase::CRenderer, items[i]->x, items[i]->y + items[i]->icon.GetHeight(), items[i]->x + items[i]->icon.GetWidth(), items[i]->y + items[i]->icon.GetHeight());
				SDL_RenderDrawLine(CBase::CRenderer, items[i]->x + items[i]->icon.GetWidth(), items[i]->y, items[i]->x + items[i]->icon.GetWidth(), items[i]->y + items[i]->icon.GetHeight());
			}

			if (itemClick && CBase::mouse.x < items[i]->x + items[i]->icon.GetWidth() && CBase::mouse.x > items[i]->x &&
				CBase::mouse.y < items[i]->y + items[i]->icon.GetHeight() && CBase::mouse.y > items[i]->y) {

				if (mainItem.empty())
				{
					items[i]->x = x + 462;
					items[i]->y = y + 137;
					mainItem.push_back(items[i]);
					items.erase(items.begin() + i);
				}
				else if (secondItem.empty())
				{
					items[i]->x = x + 533;
					items[i]->y = y + 137;
					secondItem.push_back(items[i]);
					items.erase(items.begin() + i);
				}
				else if (thirdItem.empty())
				{
					items[i]->x = x + 496;
					items[i]->y = y + 205;
					thirdItem.push_back(items[i]);
					items.erase(items.begin() + i);
				}
			}
		}

		for (int i = 0; i < mainItem.size(); ++i)
		{
			if (CBase::CDrawCollisions) {
				SDL_SetRenderDrawColor(CBase::CRenderer, 255, 0, 0, 255);
				SDL_RenderDrawLine(CBase::CRenderer, mainItem[i]->x, mainItem[i]->y, mainItem[i]->x + mainItem[i]->icon.GetWidth(), mainItem[i]->y);
				SDL_RenderDrawLine(CBase::CRenderer, mainItem[i]->x, mainItem[i]->y, mainItem[i]->x, mainItem[i]->y + mainItem[i]->icon.GetHeight());
				SDL_RenderDrawLine(CBase::CRenderer, mainItem[i]->x, mainItem[i]->y + mainItem[i]->icon.GetHeight(), mainItem[i]->x + mainItem[i]->icon.GetWidth(), mainItem[i]->y + mainItem[i]->icon.GetHeight());
				SDL_RenderDrawLine(CBase::CRenderer, mainItem[i]->x + mainItem[i]->icon.GetWidth(), mainItem[i]->y, mainItem[i]->x + mainItem[i]->icon.GetWidth(), mainItem[i]->y + mainItem[i]->icon.GetHeight());
			}

			if (itemClick && CBase::mouse.x < mainItem[i]->x + mainItem[i]->icon.GetWidth() && CBase::mouse.x > mainItem[i]->x &&
				CBase::mouse.y < mainItem[i]->y + mainItem[i]->icon.GetHeight() && CBase::mouse.y > mainItem[i]->y) {

				AddItem(mainItem[i]);
				mainItem.erase(mainItem.begin() + i);
			}
		}

		for (int i = 0; i < secondItem.size(); ++i)
		{
			if (CBase::CDrawCollisions) {
				SDL_SetRenderDrawColor(CBase::CRenderer, 255, 0, 0, 255);
				SDL_RenderDrawLine(CBase::CRenderer, secondItem[i]->x, secondItem[i]->y, secondItem[i]->x + secondItem[i]->icon.GetWidth(), secondItem[i]->y);
				SDL_RenderDrawLine(CBase::CRenderer, secondItem[i]->x, secondItem[i]->y, secondItem[i]->x, secondItem[i]->y + secondItem[i]->icon.GetHeight());
				SDL_RenderDrawLine(CBase::CRenderer, secondItem[i]->x, secondItem[i]->y + secondItem[i]->icon.GetHeight(), secondItem[i]->x + secondItem[i]->icon.GetWidth(), secondItem[i]->y + secondItem[i]->icon.GetHeight());
				SDL_RenderDrawLine(CBase::CRenderer, secondItem[i]->x + secondItem[i]->icon.GetWidth(), secondItem[i]->y, secondItem[i]->x + secondItem[i]->icon.GetWidth(), secondItem[i]->y + secondItem[i]->icon.GetHeight());
			}

			if (itemClick && CBase::mouse.x < secondItem[i]->x + secondItem[i]->icon.GetWidth() && CBase::mouse.x > secondItem[i]->x &&
				CBase::mouse.y < secondItem[i]->y + secondItem[i]->icon.GetHeight() && CBase::mouse.y > secondItem[i]->y) {
				
				AddItem(secondItem[i]);
				secondItem.erase(secondItem.begin() + i);
			}
		}

		for (int i = 0; i < thirdItem.size(); ++i)
		{
			if (CBase::CDrawCollisions) {
				SDL_SetRenderDrawColor(CBase::CRenderer, 255, 0, 0, 255);
				SDL_RenderDrawLine(CBase::CRenderer, thirdItem[i]->x, thirdItem[i]->y, thirdItem[i]->x + thirdItem[i]->icon.GetWidth(), thirdItem[i]->y);
				SDL_RenderDrawLine(CBase::CRenderer, thirdItem[i]->x, thirdItem[i]->y, thirdItem[i]->x, thirdItem[i]->y + thirdItem[i]->icon.GetHeight());
				SDL_RenderDrawLine(CBase::CRenderer, thirdItem[i]->x, thirdItem[i]->y + thirdItem[i]->icon.GetHeight(), thirdItem[i]->x + thirdItem[i]->icon.GetWidth(), thirdItem[i]->y + thirdItem[i]->icon.GetHeight());
				SDL_RenderDrawLine(CBase::CRenderer, thirdItem[i]->x + thirdItem[i]->icon.GetWidth(), thirdItem[i]->y, thirdItem[i]->x + thirdItem[i]->icon.GetWidth(), thirdItem[i]->y + thirdItem[i]->icon.GetHeight());
			}

			if (itemClick && CBase::mouse.x < thirdItem[i]->x + thirdItem[i]->icon.GetWidth() && CBase::mouse.x > thirdItem[i]->x &&
				CBase::mouse.y < thirdItem[i]->y + thirdItem[i]->icon.GetHeight() && CBase::mouse.y > thirdItem[i]->y) {

				AddItem(thirdItem[i]);
				thirdItem.erase(thirdItem.begin() + i);
			}
		}
	}
	else
	{
		player->act = true;
	}

	if (mainItem.empty() && player->itemSlot == 1)
	{
		player->weapon = Weapon::WeaponBase();
	}
	else if (secondItem.empty() && player->itemSlot == 2)
	{
		player->weapon = Weapon::WeaponBase();
	}
	else if (thirdItem.empty() && player->itemSlot == 3)
	{
		player->weapon = Weapon::WeaponBase();
	}
}

void InventorySystem::AddItem(Items* item) {

	size_t itemCurrentSize = items.size();

	if (itemCurrentSize > 0) {

		// printf("SIZE: %d\n", itemCurrentSize); // delete this line

		item->x = items[itemCurrentSize - 1]->x + 67.5f;
		item->y = items[itemCurrentSize - 1]->y;

		if (item->x + 50 > x + 310)
		{
			item->x = x + 50;
			item->y = items[itemCurrentSize - 1]->y + 67.5f;
		}

		if (item->y + 70 > y + 350)
		{
			item->x = x + 50;
			item->y = y + 70;
		}

		if (item->x == items[0]->x && item->y == items[0]->y)
		{
			item->x = x + 50;
			item->y = y + 70;
		}

	}
	else
	{
		item->x = x + 50;
		item->y = y + 70;
	}
	
	items.push_back(item);
}
