#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleMusic::ModuleMusic() : Module()
{
	// TODO 5: Initialize all texture pointers to nullptr
	for (int i = 0; i < MAX_AUDIO; i++)
	{
		Audios[i] = nullptr;
	}
}

// Destructor
ModuleMusic::~ModuleMusic()
{}

// Called before render is available
bool ModuleMusic::Init()
{
	LOG("Init audio library");
	bool ret = true;

	// load support for the PNG image format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize audi lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	return ret;
}

// Called before quitting
bool ModuleMusic::CleanUp()
{
	for (int i = 0; i < MAX_AUDIO; i++)
	{
		Mix_FreeMusic(Audios[i]);
	}

	Mix_CloseAudio();
	Mix_Quit();
	return true;
}

Mix_Music* const ModuleMusic::Load(const char* path)
{

	Audios[0] = Mix_LoadMUS("../Source/Music/a.ogg");

	if (!Audios[0]) {
		LOG("Error music not Loaded");
	}


	Mix_PlayMusic(Audios[0], -1);



	return nullptr;
}
