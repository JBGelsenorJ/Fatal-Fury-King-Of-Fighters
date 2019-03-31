#ifndef __ModuleWelcomeScreen_H__
#define __ModuleWelcomeScreen_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"

struct SDL_Texture;

class ModuleWelcomeScreen : public Module
{
public:
	ModuleWelcomeScreen();
	~ModuleWelcomeScreen();

	bool Start();
	update_status Update();
	bool CleanUp();


public:

	SDL_Texture * graphics = nullptr;
	SDL_Rect welcome;
	Animation logo;
	Animation start;
	Mix_Music* song;
};

#endif