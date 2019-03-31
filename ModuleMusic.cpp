#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleMusic::ModuleMusic() : Module()
{

}

// Destructor
ModuleMusic::~ModuleMusic()
{}

bool ModuleMusic::Init()
{
	LOG("Init audio library");
	bool ret = true;


	int flags = MIX_INIT_OGG;
	Mix_Init(SDL_INIT_AUDIO);
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize audi lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		LOG("Mix_OpenAudio: %s\n", Mix_GetError());
		//fix error: can't fnd a mastering voice
		return false;
	}
	return ret;
}

// Called before quitting
bool ModuleMusic::CleanUp()
{
	LOG("Freeing music");

	for (int i = 0; i < MAX_AUDIO; i++)
	{
		if (Audios[i] != nullptr)
		{
			Audios[i] = nullptr;
		}
	}
	for (int i = 0; i <MAX_FX; i++)
	{
		if (fxs[i] != nullptr)
		{
			fxs[i] = nullptr;
		}
	}


	Mix_CloseAudio();
	Mix_Quit();
	return true;
}

Mix_Music* const ModuleMusic::LoadMusic(const char* path)
{

	Mix_Music* song;
	song = Mix_LoadMUS(path);


	if (!song)
	{
		LOG("Error loading music", path, Mix_GetError());
	}
	for (int i = 0; i < MAX_AUDIO; i++)
	{
		if (Audios[i] == nullptr)
		{
			Audios[i] = song;
			break;
		}
	}
	return song;
}

Mix_Chunk* ModuleMusic::LoadFX(const char* path) {
	Mix_Chunk* fx;
	fx = Mix_LoadWAV(path);
	if (!fx)
	{
		LOG("Error loading fx", Mix_GetError());
	}
	for (int i = 0; i < MAX_FX; i++)
	{
		if (fxs[i] == nullptr)
		{
			fxs[i] = fx;
			break;
		}
	}
	return fx;
}

bool ModuleMusic::PlayMusic(Mix_Music* song) {

	if (Mix_PlayMusic(song, -1) == -1)
	{
		LOG("Error play music: %s \n", Mix_GetError());
		return false;
	}

	return true;
}

bool ModuleMusic::PlayFX(Mix_Chunk* fx) {
	if (Mix_PlayChannel(-1, fx, 0) == -1)
	{
		LOG("Error playing fx\n", Mix_GetError());
		return false;
	}
	return true;
}

