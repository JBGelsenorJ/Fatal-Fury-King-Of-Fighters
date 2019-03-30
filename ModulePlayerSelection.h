#ifndef __ModulePlayerSelectiom_H__
#define __ModulePlayerSelection_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModulePlayerSelection : public Module
{
public:
	ModulePlayerSelection();
	~ModulePlayerSelection();

	bool Start();
	update_status Update();
	bool CleanUp();


public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	Animation people;


};

#endif