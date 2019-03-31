#ifndef __ModuleSceneSoundBeach_H__
#define __ModuleSceneSoundBeach_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"

struct SDL_Texture;

class ModuleSceneSoundBeach : public Module
{
public:
	ModuleSceneSoundBeach();
	~ModuleSceneSoundBeach();

	bool Start();
	update_status Update();
	bool CleanUp();


public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	Mix_Music* music;
};

#endif