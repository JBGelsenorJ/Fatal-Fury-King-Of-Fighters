#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures() : Module()
{
	// TODO 5: Initialize all texture pointers to nullptr
	SDL_Surface *BackgroundS = nullptr;
	SDL_Texture *BackgroundT = nullptr;
}

// Destructor
ModuleTextures::~ModuleTextures()
{}

// Called before render is available
bool ModuleTextures::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before q	uitting
bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");

	// TODO 6: Free all textures

	IMG_Quit();
	return true;
}

// Load new texture from file path
SDL_Texture* const ModuleTextures::Load(const char* path)
{

	this->BackgroundS = IMG_Load("test.png");
	if (!BackgroundS)
	{
		LOG("error, image not correctly loaded");
	}
	BackgroundT = SDL_CreateTextureFromSurface(App->render->Blit, BackgroundS);
	SDL_FreeSurface(BackgroundS);
	// TODO 2: Load and image from a path (must be a png)
	// and check for errors

	// TODO 3: Once your have the SDL_surface*, you need to create
	// a texture from it to return it (check for errors again)

	// TODO 4: Before leaving, remember to free the surface and
	// add the texture to our own array so we can properly free them

	return nullptr;
}
