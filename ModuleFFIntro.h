#ifndef __ModulFFIntro_H__
#define __ModulFFIntro_H__

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
	SDL_Rect rock;
	SDL_Rect borders;
	Animation start;
	Animation player;
	
	Mix_Music* introsong;
	/*iPoint positionplayer;
	iPoint positionrock;*/

};


#endif // __ModulFFIntros_H__