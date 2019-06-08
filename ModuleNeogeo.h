#ifndef __ModuleNeogeo_H__
#define __ModuleNeogeo_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"

#define LIMIT_TIME 2000

struct SDL_Texture;

class ModuleNeogeo : public Module
{
public:
	ModuleNeogeo();
	~ModuleNeogeo();

	bool Start();
	update_status Update();
	bool CleanUp();


public:

	SDL_Texture * graphics = nullptr;
	SDL_Rect neo;
	Animation * current_animation = nullptr;
	Animation neogeo;
	Animation last;
	Animation rect1;
	Animation rect2;
	Animation rect3;
	Mix_Music* song;
	int posx1;
	int posx2;
	int posx3;
	int time_start;
	bool anim_done = false;

};

#endif