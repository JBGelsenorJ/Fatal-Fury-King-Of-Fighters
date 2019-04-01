#ifndef __ModulFFIntro2_H__
#define __ModulFFIntro2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"
#include "Application.h"

struct SDL_Texture;

class ModuleFFIntro2 : public Module
{
public:
	ModuleFFIntro2();
	~ModuleFFIntro2();

	bool Start();
	update_status Update();
	bool CleanUp();


public:

	SDL_Texture * graphics = nullptr;
	SDL_Rect introwin2;
	SDL_Rect taxi;
	SDL_Rect borders;
	Animation start;
	Animation player2;
	Mix_Music* introsong;
	/*iPoint positiontaxi;
	iPoint positionplayer2;*/

};

#endif // __ModulFFIntros2_H__