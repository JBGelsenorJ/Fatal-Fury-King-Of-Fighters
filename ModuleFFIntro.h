#ifndef __ModuleWelcomeScreen_H__
#define __ModuleWelcomeScreen_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"
#include "Application.h"

struct SDL_Texture;

class ModuleFFIntro : public Module
{
public:
	ModuleFFIntro();
	~ModuleFFIntro();

	bool Start();
	update_status Update();
	bool CleanUp();


public:

	SDL_Texture * graphics = nullptr;
	SDL_Rect introwin;
	SDL_Rect introwin2;
	SDL_Rect taxi;
	SDL_Rect rock;
	Animation start;
	Animation intro;
	Animation player;
	Animation player2;
	Mix_Music* introsong;
	iPoint positiontaxi;
	iPoint positionplayer;
	iPoint positionrock;
	iPoint positionplayer2;

};

#endif