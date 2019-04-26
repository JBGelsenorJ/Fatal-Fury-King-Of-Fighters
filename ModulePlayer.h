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
#define SP1_TIME 1000
#define KICK_TIME 1000

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
	void OnCollision(Collider* c1, Collider* c2);
	int jumpspeed = 6;
	int speed = 2;
	
};

enum player_states
{
	ST_UNKNOWN,
	ST_IDLE,
	ST_WALK_FORWARD,
	ST_WALK_BACKWARD,
	ST_JUMP_NEUTRAL,
	ST_CROUCH,
	ST_PUNCH_STANDING,
	ST_SP1_STANDING,
	ST_KICK_STANDING,
	
};

enum player_inputs
{
	IN_LEFT_DOWN,
	IN_LEFT_UP,
	
	IN_RIGHT_DOWN,
	IN_RIGHT_UP,
	
	IN_JUMP_DOWN,
	IN_JUMP_UP,

	IN_PUNCH_DOWN,
	IN_PUNCH_UP,
	
	IN_CROUCH_UP,
	IN_CROUCH_DOWN,
	
	IN_SP1_UP,
	IN_SP1_DOWN,
	
	IN_KICK_DOWN,
	IN_KICK_UP,
	
	IN_JUMP_FINISH,
	IN_PUNCH_FINISH,
	IN_SP1_FINISH,
	IN_KICK_FINISH,

	IN_JUMP_AND_CROUCH,
	IN_LEFT_AND_RIGHT,
	IN_PUNCH_AND_KICK,
	IN_PUNCH_AND_SP1,
	IN_KICK_AND_SP1,
	IN_PUNCH_AND_KICK_AND_SP1,


};

#endif