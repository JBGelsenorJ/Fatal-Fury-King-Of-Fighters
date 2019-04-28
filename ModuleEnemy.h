#ifndef __ModuleEnemy_H__
#define __ModuleEnemy_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "p2Qeue.h"
#include "SDL\include\SDL_timer.h"



#define MAX_KEYS2 300
#define JUMP_TIME2 1020
#define PUNCH_TIME2 400
#define SP1_TIME2 500
#define KICK_TIME2 550

struct SDL_Texture;

class ModuleEnemy : public Module
{
public:

	ModuleEnemy();
	~ModuleEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool Activesm1 = false;

public:

	SDL_Texture* graphics2 = nullptr;
	Animation idle2;
	Animation forward2;
	Animation backward2;
	Animation jump2;
	Animation kick2;
	Animation punch2;
	Animation crouch2;
	Animation lowd2;
	Animation highd2;
	Animation sm12;

	Particle special;
	iPoint position2;

	Mix_Chunk* Specialattack;
	Mix_Chunk* Punch;
	Mix_Chunk* Kick;

	Collider* enemycol;
	Collider* enemypunch;
	Collider* enemykick;

	Uint32 jump_timer2 = 0;
	Uint32 punch_timer2 = 0;
	Uint32 sp1_timer2 = 0;
	Uint32 kick_timer2 = 0;

	bool jumpreset2;
	bool TimeJump2 = false;

	bool godmode = false;
	int countdown_font = -1;

	void OnCollision(Collider* c1, Collider* c2);

	float jumpspeed2 = 6;
	int speed2 = 2;
	float life2 = 100;

	enum enemy_states
	{
		ST_UNKNOWN2,
		ST_IDLE2,
		ST_WALK2_FORWARD,
		ST_WALK2_BACKWARD,
		ST_JUMP2_NEUTRAL,
		ST_CROUCH2,
		ST_PUNCH2_STANDING,
		ST_SP12,
		ST_KICK2_STANDING,

	};

	enum enemy_inputs
	{
		IN_LEFT2_DOWN,
		IN_LEFT2_UP,

		IN_RIGHT2_DOWN,
		IN_RIGHT2_UP,


		IN_JUMP2,

		IN_PUNCH2_DOWN,
		IN_PUNCH2_UP,

		IN_CROUCH2_UP,
		IN_CROUCH2_DOWN,

		IN_SP12_UP,
		IN_SP12_DOWN,

		IN_KICK2_DOWN,
		IN_KICK2_UP,

		IN_JUMP2_FINISH,
		IN_PUNCH2_FINISH,
		IN_SP12_FINISH,
		IN_KICK2_FINISH,

		IN_JUMP2_AND_CROUCH,
		IN_LEFT2_AND_RIGHT,
		IN_PUNCH2_AND_KICK,
		IN_PUNCH2_AND_SP1,
		IN_KICK2_AND_SP1,
		IN_PUNCH2_AND_KICK_AND_SP1,

		IN_PUNCH2,
		IN_KICK2,
		IN_SM12,


	};

	bool external_input(p2Qeue<enemy_inputs>&);

	void internal_input(p2Qeue<enemy_inputs>&);

	enemy_states process_fsm(p2Qeue<enemy_inputs>& inputs)
	{
		static enemy_states state = ST_IDLE2;
		enemy_inputs last_input;

		while (inputs.Pop(last_input))
		{
			switch (state)
			{

			case ST_IDLE2:
			{
				switch (last_input)
				{

				case IN_RIGHT2_DOWN: state = ST_WALK2_FORWARD; break;
				case IN_LEFT2_DOWN: state = ST_WALK2_BACKWARD; break;
				case IN_CROUCH2_DOWN: state = ST_CROUCH2; break;
				case IN_JUMP2: state = ST_JUMP2_NEUTRAL; jump_timer2 = SDL_GetTicks();  break;

				case IN_PUNCH2: state = ST_PUNCH2_STANDING; punch_timer2 = SDL_GetTicks();  break;
				case IN_SM12: state = ST_SP12; sp1_timer2 = SDL_GetTicks(); break;
				case IN_KICK2: state = ST_KICK2_STANDING; kick_timer2 = SDL_GetTicks(); break;

				case IN_PUNCH2_AND_KICK: state = ST_IDLE2; break;
				case IN_PUNCH2_AND_SP1: state = ST_IDLE2; break;
				case IN_KICK2_AND_SP1: state = ST_IDLE2; break;
				case IN_PUNCH2_AND_KICK_AND_SP1: state = ST_IDLE2; break;

				}
			}
			break;

			case ST_WALK2_FORWARD:
			{

				switch (last_input)
				{

				case IN_RIGHT2_UP: state = ST_IDLE2; break;
				case IN_LEFT2_AND_RIGHT: state = ST_IDLE2; break;
				case IN_CROUCH2_DOWN: state = ST_CROUCH2; break;
				case IN_PUNCH2: state = ST_PUNCH2_STANDING, punch_timer2 = SDL_GetTicks(); break;
				case IN_KICK2: state = ST_KICK2_STANDING, kick_timer2 = SDL_GetTicks(); break;
				case IN_SM12: state = ST_SP12, sp1_timer2 = SDL_GetTicks(); break;

				}

			}
			break;

			case ST_WALK2_BACKWARD:
			{
				switch (last_input)
				{

				case IN_LEFT2_UP: state = ST_IDLE2; break;
				case IN_LEFT2_AND_RIGHT: state = ST_IDLE2; break;
				case IN_CROUCH2_DOWN: state = ST_CROUCH2; break;
				case IN_PUNCH2: state = ST_PUNCH2_STANDING, punch_timer2 = SDL_GetTicks(); break;
				case IN_KICK2: state = ST_KICK2_STANDING, kick_timer2 = SDL_GetTicks(); break;
				case IN_SM12: state = ST_SP12, sp1_timer2 = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_CROUCH2:
			{
				switch (last_input)
				{

				case IN_CROUCH2_UP: state = ST_IDLE2; break;
				case IN_JUMP2_AND_CROUCH: state = ST_IDLE2; break;
				case IN_PUNCH2: state = ST_PUNCH2_STANDING, punch_timer2 = SDL_GetTicks(); break;
				case IN_KICK2: state = ST_KICK2_STANDING, kick_timer2 = SDL_GetTicks(); break;
				case IN_SM12: state = ST_SP12, sp1_timer2 = SDL_GetTicks(); break;

				}

			}
			break;

			case ST_JUMP2_NEUTRAL:
			{
				switch (last_input)
				{

				case IN_JUMP2_FINISH: state = ST_IDLE2; break;
				case IN_JUMP2: state = ST_JUMP2_NEUTRAL; jump_timer2 = SDL_GetTicks(); break;

				}
			}
			break;

			case ST_PUNCH2_STANDING:
			{
				switch (last_input)
				{
				case IN_PUNCH2_FINISH: state = ST_IDLE2; break;
				case IN_PUNCH2_AND_KICK: state = ST_IDLE2; break;
				case IN_PUNCH2_AND_KICK_AND_SP1: state = ST_IDLE2; break;
				case IN_PUNCH2_AND_SP1: state = ST_IDLE2; break;


				}
			}
			break;

			case ST_KICK2_STANDING:
			{

				switch (last_input)
				{

				case IN_KICK2_FINISH: state = ST_IDLE2; break;
				case IN_PUNCH2_AND_KICK: state = ST_IDLE2; break;
				case IN_PUNCH2_AND_KICK_AND_SP1: state = ST_IDLE2; break;
				case IN_KICK2_AND_SP1: state = ST_IDLE2; break;
				}
			}

			case ST_SP12:
			{

				switch (last_input)
				{

				case IN_SP12_FINISH: state = ST_IDLE2; break;
				case IN_PUNCH2_AND_SP1: state = ST_IDLE2; break;
				case IN_PUNCH2_AND_KICK_AND_SP1: state = ST_IDLE2; break;
				case IN_KICK2_AND_SP1: state = ST_IDLE2; break;
				}
				break;

			}
			}
		}

		return state;
	}

};

#endif
/*
#ifndef __ModuleEnemy_H__
#define __ModuleEnemy_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "p2Qeue.h"

#define JUMP2_TIME 3000
#define PUNCH2_TIME 1000
#define SP12_TIME 1000
#define KICK2_TIME 1000

struct SDL_Texture;


class ModuleEnemy : public Module
{
public:
	ModuleEnemy();
	~ModuleEnemy();

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
	bool jumpreset;
	bool TimeAnim = false;
	bool KickAnim = false;
	bool TimePunch = false;
	bool TimeJump = false;
	Collider* enemycol;
	Collider* enemykick;
	Collider* enemypunch;
	void OnCollision(Collider* c1, Collider* c2);
	int speed = 2;
	float life = 100;
	float score = 0;
	float jumpspeed = 6;

};

enum enemy_states
{
	ST_UNKNOWN2,
	ST_IDLE2,
	ST_WALK2_FORWARD,
	ST_WALK2_BACKWARD,
	ST_JUMP2_NEUTRAL,
	ST_CROUCH2,
	ST_PUNCH2_STANDING,
	ST_SP12_STANDING,
	ST_KICK2_STANDING,

};

enum enemy_inputs
{
	IN_LEFT2_DOWN,
	IN_LEFT2_UP,

	IN_RIGHT2_DOWN,
	IN_RIGHT2_UP,

	IN_JUMP2_DOWN,
	IN_JUMP2_UP,

	IN_PUNCH2_DOWN,
	IN_PUNCH2_UP,

	IN_CROUCH2_UP,
	IN_CROUCH2_DOWN,

	IN_SP12_UP,
	IN_SP12_DOWN,

	IN_KICK2_DOWN,
	IN_KICK2_UP,

	IN_JUMP2_FINISH,
	IN_PUNCH2_FINISH,
	IN_SP12_FINISH,
	IN_KICK2_FINISH,

	IN_JUMP2_AND_CROUCH,
	IN_LEFT2_AND_RIGHT,
	IN_PUNCH2_AND_KICK,
	IN_PUNCH2_AND_SP1,
	IN_KICK2_AND_SP1,
	IN_PUNCH2_AND_KICK_AND_SP1,


};

#endif*/