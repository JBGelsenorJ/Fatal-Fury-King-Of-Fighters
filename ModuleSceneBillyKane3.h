#ifndef __ModuleBillyKane3_H__
#define __ModuleBillyKane3_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleBillyKane3 : public Module
{
public:
	ModuleBillyKane3();
	~ModuleBillyKane3();

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
	SDL_Rect wall1;
	SDL_Rect wall2;
	Collider* wall1c = nullptr;
	Collider* wall2c = nullptr;
	iPoint limitleft;
	iPoint limitright;
	float starting = 0.0f;
	float distance;
	float seconds;
	uint time;
	char time_text[10];
	int countdown = -1;

	//Scene State Machine
	COMBAT_STATUS scenestatus;
	int globaltime;
	int pretime;
	bool audiofight = true;
	bool audioround = true;
};

#endif