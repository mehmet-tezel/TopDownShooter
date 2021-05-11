#pragma once

#include "Core.h"

// Inits Hyperbase with class members
bool HYP_Init_Window();

// Deallocates members and quits all libraries
void HYP_Free();

// Main loading function to texture -> LoadTexture(...)
void LoadSprite(std::string path, Hyper::Texture* texture);

// Sets the 2nd parameter as the main texture.
void SetSprite(Hyper::Texture* texture, Hyper::Texture* texture2);

void LoadSound(std::string path, Hyper::Sound* sound);

void PlaySound(Hyper::Sound* sound, int channel);

// broken
//void FreeSound(Hyper::Sound* soundFire, Hyper::Sound* soundReload, Hyper::Sound* soundEmpty, Hyper::Sound* soundDraw);

void LoadFont(std::string path, Hyper::Text* text, int size);

// Loads textures and sounds quickly, no debug!
// PRECACHE, represents the main property for that object

#define PRECACHE_SPRITE(path) (LoadSprite(path, &texture))
#define PRECACHE_SOUND(path) (LoadSound(path, &soundFire))
#define LOAD_FONT(path, text, size) (LoadFont(path, text, size))
#define LOAD_SOUND(path, sound) (LoadSound(path, sound))
#define SET_TEXTURE(texture, texture2) (SetSprite(texture, texture2))
#define LOAD_TEXTURE(path, _texture) (LoadSprite(path, _texture))
#define SET_MAIN_TEXTURE(_texture) (SetSprite(&texture, _texture))
//#define FREE_SOUNDS() (FreeSound(&soundFire, &soundReload, &soundEmpty, &soundDraw))

/* The main control class that runs the entire game. 
   Functions and objects in this class are static and must be set to use once.
*/
class CBase {

public:

	CBase() {}
	~CBase() {}

	/* Makes the renderer suitable for all classes. Most functions are handled with this code. */
	static void SetRenderer(SDL_Renderer* renderer) { CRenderer = renderer; }
	
	/* Makes the main window belong to the CBase class. */
	static void SetWindow(Hyper::Window* window) { CWindow = window; }

	static void SetEvent(SDL_Event* event) { CEvent = event; }
	static void SetTimer(Hyper::Timer* timer) { CTimer = timer; }
	static void SetMouse(int x, int y) { mouse.x = x; mouse.y = y; mousef.x = mouse.x; mousef.y = mouse.y; }
	static void SetMouse() { SDL_GetMouseState(&mouse.x, &mouse.y); mousef.x = mouse.x; mousef.y = mouse.y;	}
	static void ShowCollisions() { CDrawCollisions = true; };
	static void HideCollisions() { CDrawCollisions = false; };

	static Uint32 GetTicks();

	/* Starts global game timer. */
	static void StartTimer();

	/* Stops global game timer.*/
	static void StopTimer();

	static int CScreenWidth;
	static int CScreenHeight;

	/* Window created for use in all classes. (HYP_Init_Window())*/
	static Hyper::Window* CWindow;

	/* Renderer created for use in all classes. (HYP_Init_Window()) */
	static SDL_Renderer* CRenderer;

	/* It is used where event is needed to keep the game flowing. */
	static SDL_Event* CEvent;

	/* The timer is created once for the entire game and cannot be changed. */
	static Hyper::Timer* CTimer;

	static vec2i mouse;
	static vec2f mousef;

	/* Shows entity's collisions */
	static bool CDrawCollisions;
};

/* This entity class covers the basic requirements of objects.
   Most objects have this class.
*/
class Entity {

public:

	Entity() {}
	~Entity() {}

	float x;
	float y;
	float dx;
	float dy;

	int w;
	int h;

	SDL_Rect rect;

	float speed;

	int health;
	int armor;

	double angle;

	bool status;
	bool fire;
	bool reload;
	bool isReloading;
	bool act; // entity action status

	Hyper::Texture texture;
	Hyper::Texture icon;
};