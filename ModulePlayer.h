#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "p2Qeue.h"


#define JUMP_TIME 3000
#define PUNCH_TIME 1000

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
	Collider* particles;
	bool jumpreset;
	bool TimeAnim = false;
	bool KickAnim = false;
	bool TimePunch = false;
	bool Lowdtime = false;
	bool Highdtime = false;
	bool godmode = false;
	int countdown_font = -1;
	
	

};


enum ryu_states
{
	ST_UNKNOWN,

	ST_IDLE,
	ST_WALK_FORWARD,
	ST_WALK_BACKWARD,
	ST_JUMP_NEUTRAL,
	ST_JUMP_FORWARD,
	ST_JUMP_BACKWARD,
	ST_CROUCH,
	ST_PUNCH_STANDING,
	ST_PUNCH_NEUTRAL_JUMP,
	ST_PUNCH_FORWARD_JUMP,
	ST_PUNCH_BACKWARD_JUMP,
	ST_PUNCH_CROUCH
};

enum ryu_inputs
{
	IN_LEFT_DOWN,
	IN_LEFT_UP,
	IN_RIGHT_DOWN,
	IN_RIGHT_UP,
	IN_LEFT_AND_RIGHT,
	IN_JUMP,
	IN_CROUCH_UP,
	IN_CROUCH_DOWN,
	IN_JUMP_AND_CROUCH,
	IN_X,
	IN_JUMP_FINISH,
	IN_PUNCH_FINISH
};


#endif