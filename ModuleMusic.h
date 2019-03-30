#ifndef __ModuleMusic_H__
#define __ModuleMusic_H__

#include "Module.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define MAX_AUDIO 50



class ModuleMusic : public Module
{
public:
	ModuleMusic();
	~ModuleMusic();

	bool Init();
	bool CleanUp();

	Mix_Music* const Load(const char* path);

public:
	Mix_Music * Audios[MAX_AUDIO];
};

#endif // __ModuleTextures_H__