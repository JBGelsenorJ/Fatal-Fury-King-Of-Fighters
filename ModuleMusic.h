#ifndef __ModuleMusic_H__
#define __ModuleMusic_H__

#include "Module.h"
#include "Application.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"


#define MAX_AUDIO 50
#define MAX_FX 30



class ModuleMusic : public Module
{
public:
	ModuleMusic();
	~ModuleMusic();

	bool Init();
	bool CleanUp();

	Mix_Music* const LoadMusic(const char* path);
	bool PlayMusic(Mix_Music*);
	Mix_Chunk * LoadFX(const char* path);
	bool PlayFX(Mix_Chunk*);

public:
	Mix_Music * Audios[MAX_AUDIO];
	Mix_Chunk *fxs[MAX_FX];
};

#endif // !__ModuleMusic_H__