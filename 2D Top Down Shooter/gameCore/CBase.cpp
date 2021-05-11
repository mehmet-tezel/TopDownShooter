#include "CBase.h"

int CBase::CScreenWidth = 800;
int CBase::CScreenHeight = 600;

SDL_Renderer* CBase::CRenderer = nullptr;
Hyper::Window* CBase::CWindow = nullptr;
SDL_Event* CBase::CEvent = nullptr;
Hyper::Timer* CBase::CTimer = nullptr;

vec2i CBase::mouse = vec2<int>::vec2();
vec2f CBase::mousef = vec2<float>::vec2();

bool CBase::CDrawCollisions = false;

void CBase::StartTimer() {

	CTimer->StartTimer();
}

void CBase::StopTimer() {

	CTimer->StopTimer();
}

Uint32 CBase::GetTicks() {

	return CTimer->GetTicks();
}

void LoadSprite(std::string path, Hyper::Texture* texture) {

	texture->LoadTexture(path, CBase::CRenderer);
}

void SetSprite(Hyper::Texture* texture, Hyper::Texture* texture2) {

	texture = texture2;
}

void LoadSound(std::string path, Hyper::Sound* sound) {

	sound->LoadSound(path);
}

void PlaySound(Hyper::Sound* sound, int channel) {

	sound->PlaySound(0, channel); 
}

void FreeSound(Hyper::Sound* soundFire, Hyper::Sound* soundReload, Hyper::Sound* soundEmpty, Hyper::Sound* soundDraw) {

	soundFire->FreeSound();
	soundReload->FreeSound();
	soundEmpty->FreeSound();
	soundDraw->FreeSound();
}

void LoadFont(std::string path, Hyper::Text* text, int size) {

	text->LoadFont(path, size);
}

bool HYP_Init_Window() {

	bool status = true;

	if (!Hyper::HYP_Init(SDL_INIT_EVERYTHING, SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		status = false;
	}
	else
	{
		if (!CBase::CWindow->initWindow("Test Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CBase::CScreenWidth, CBase::CScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE))
		{
			status = false;
		}
		else
		{
			CBase::CRenderer = CBase::CWindow->CreateRenderer(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (CBase::CRenderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				status = false;
			}
			else
			{
				CBase::CWindow->SetRenderDrawColor(CBase::CRenderer, 0, 0, 0, 255);

				if (!Hyper::LoadLibraries(IMG_INIT_PNG))
				{
					status = false;
				}

				Mix_AllocateChannels(4);
			}
		}
	}

	return status;
}

void HYP_Free() {

	SDL_DestroyRenderer(CBase::CRenderer);
	CBase::CRenderer = nullptr;

	CBase::CWindow->FreeWindow();
	CBase::CWindow = nullptr;

	Hyper::QuitAllLibraries();
}