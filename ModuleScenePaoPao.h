#ifndef __ModuleScenePaoPao_H__
#define __ModuleScenePaoPao_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"

struct SDL_Texture;

class ModuleScenePaoPao : public Module
{
public:
	ModuleScenePaoPao();
	~ModuleScenePaoPao();

	bool Start();
	update_status Update();
	bool CleanUp();


public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	Animation people;
	Mix_Music* music;
	Mix_Chunk* fx;
	Collider* wall1;
	Collider* wall2;
	Collider* wall3;
	float starting = 0.0f;
	float seconds;
	uint time;
	char time_text[10];
	int countdown = -1;
};

#endif