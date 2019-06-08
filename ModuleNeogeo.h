#ifndef __ModuleNeogeo_H__
#define __ModuleNeogeo_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"

#define LIMIT_TIME 2000

struct SDL_Texture;

class ModuleNeogeo : public Module
{
public:
	ModuleNeogeo();
	~ModuleNeogeo();

	bool Start();
	update_status Update();
	bool CleanUp();


public:

	SDL_Texture * graphics = nullptr;
	
	
	Animation neogeo;
	Mix_Music* song;
	
};

#endif