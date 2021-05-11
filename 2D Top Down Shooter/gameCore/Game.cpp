#include <iostream>

#include "Game.h"
#include "Hud.h"
#include "WeaponSystem.h"
#include "InventorySystem.h"

void TestEvents(SDL_Event* e, Player* player, InventorySystem* inventorySystem);

int GAMECOREDLL_EX StartGame()
{
	Hyper::Window window;
	CBase::SetWindow(&window);

	SDL_Renderer* renderer = nullptr;
	CBase::SetRenderer(renderer);

	Hyper::Timer timer;
	CBase::SetTimer(&timer);
	
	if (!HYP_Init_Window()) {

		printf("HYP_Init() could not be initialized! Error: %s\n", SDL_GetError());
	}

	SDL_Event e;
	CBase::SetEvent(&e);

	// main properties

	Player player;
	Hud hud(&player);
	InventorySystem inventorySystem;

	// test items

	FirstAid firstaid;
	Glock17 glock;
	AK47 ak;

	inventorySystem.AddItem(&glock);
	inventorySystem.AddItem(&ak);
	inventorySystem.AddItem(&firstaid);

	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0) {

			if (e.type == SDL_QUIT) {

				quit = true;
			}

			ReloadSystem(&player, &inventorySystem);

			player.MotionEvent();
			inventorySystem.Event(&player);

			TestEvents(&e, &player, &inventorySystem);
		}

		std::cout << CBase::mouse.x << " " << CBase::mouse.y << std::endl;

		CBase::StartTimer();
		CBase::SetMouse();
		
		SDL_GetWindowSize(CBase::CWindow->GetWindow(), &CBase::CScreenWidth, &CBase::CScreenHeight);
		player.Move();
		
		SDL_SetRenderDrawColor(CBase::CRenderer, 0, 0, 0, 255);
		SDL_RenderClear(CBase::CRenderer);

		WeaponSystem(&player, &inventorySystem);

		player.UpdateA();
		hud.Update(&player);
		inventorySystem.UpdateInventory(&player);

		SDL_RenderPresent(CBase::CRenderer);
	}

	ak.~AK47();
	glock.~Glock17();
	firstaid.~FirstAid();
	player.~Player();
	hud.~Hud();
	HYP_Free();

	return 0;
}

void TestEvents(SDL_Event* e, Player* player, InventorySystem* inventorySystem) {

	if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.sym)
		{
		default:
			break;
		case SDLK_q:
			player->health -= 5;
			break;
		case SDLK_e:
		{
			if (inventorySystem->items.size() < inventorySystem->inventorySize)
			{ FirstAid* fa = new FirstAid(); inventorySystem->AddItem(fa); }
		}	break;
		case SDLK_t:
			if (CBase::CDrawCollisions)
				CBase::CDrawCollisions = false;
			else
				CBase::CDrawCollisions = true;
			break;
		case SDLK_g: {
			// don't forget to delete
			if (inventorySystem->items.size() < inventorySystem->inventorySize)
			{ AK47* aq = new AK47(); inventorySystem->AddItem(aq); }
		}break;
		}
	}
}