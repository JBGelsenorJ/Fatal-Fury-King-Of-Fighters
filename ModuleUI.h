#ifndef __ModuleTime_H__
#define __ModuleTime_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2Qeue.h"
#include "ModuleMusic.h"


struct SDL_Texture;

class ModuleUI : public Module
{
public:

	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool Timer(int,int);

public:

	//Textures and font sprites
	SDL_Texture* healthbar;
	int countdown = -1;

	//Sound and FX
	Mix_Chunk* finalcountdown;

	//Timer
	float starting = 0.0f;
	float seconds;
	uint time;
	char time_text[10];
};

#endif