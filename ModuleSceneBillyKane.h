#ifndef __ModuleBillyKane_H__
#define __ModuleBillyKane_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"

struct SDL_Texture;

class ModuleBillyKane : public Module
{
public:
	ModuleBillyKane();
	~ModuleBillyKane();

	bool Start();
	update_status Update();
	bool CleanUp();
	void Restart();


public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	Animation people;
	Mix_Music* music;
	Mix_Chunk* audience;
	Collider* wall1;
	Collider* wall2;
	Collider* wall3;
	float starting = 0.0f;
	float seconds;
	uint time;
	char time_text[10];
	int countdown = -1;
};

#endif