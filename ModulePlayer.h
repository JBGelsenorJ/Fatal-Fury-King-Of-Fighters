#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation jump;
	Animation kick;
	Animation punch;
	Animation crouch;
	Animation lowd;
	Animation highd;
	Particle special;
	Animation sm1;
	iPoint position;
	Mix_Chunk* Specialattack;
	Mix_Chunk* Punch;
	Mix_Chunk* Kick;
	Collider* player;
	Collider * particles;
	bool jumpreset;
	bool TimeAnim = false;
	bool KickAnim = false;
	bool TimePunch = false;
	bool Lowdtime = false;
	bool Highdtime = false;
	

};

#endif