#ifndef __ModulePlayerSelectiom_H__
#define __ModulePlayerSelection_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"

struct SDL_Texture;

class ModulePlayerSelection : public Module
{
public:
	ModulePlayerSelection();
	~ModulePlayerSelection();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool terryhover = 0;
	bool andyhover = 0;
	bool joehover = 0;


public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	SDL_Rect charlocked;
	SDL_Rect title;
	SDL_Rect player;
	Animation hoverterry;
	Animation hoverandy;
	Animation hoverjoe;
	Mix_Music* song;
	Mix_Chunk* choosefx;


};

#endif