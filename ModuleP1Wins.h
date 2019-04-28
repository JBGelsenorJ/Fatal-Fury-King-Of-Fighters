#ifndef __ModuleP1Wins_H__
#define __ModuleP1Wins_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"

struct SDL_Texture;

class ModuleP1Wins : public Module
{
public:
	ModuleP1Wins();
	~ModuleP1Wins();

	bool Start();
	update_status Update();
	bool CleanUp();


public:

	SDL_Texture * graphics = nullptr;
	SDL_Rect background;
	SDL_Rect p1;
	SDL_Rect p2;
	Animation people;
	Mix_Music* music;
	Mix_Chunk* fx;
};

#endif