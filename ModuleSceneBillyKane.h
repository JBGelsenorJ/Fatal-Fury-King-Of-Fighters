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
	Animation people1;
	Animation people2;
	Animation people3;
	Animation sea;
	Mix_Music* music;
	Mix_Chunk* audience;
	SDL_Rect wall1;
	SDL_Rect wall2;
	Collider* wall1c;
	Collider* wall2c;
	float starting = 0.0f;
	float seconds;
	uint time;
	char time_text[10];
	int countdown = -1;

	//Shadow
	SDL_Rect shadow;
	int shadowtime;
	int timerstart;
};

#endif