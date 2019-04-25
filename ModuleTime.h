#ifndef __ModuleTime_H__
#define __ModuleTime_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2Qeue.h"


struct SDL_Texture;

class ModuleTime : public Module
{
public:

	ModuleTime();
	~ModuleTime();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* countdown = nullptr;
	Animation mark;
	Animation timer[10];
	iPoint position_mark;
	iPoint position_decs;
	iPoint position_units;
};

#endif