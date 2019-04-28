#ifndef __ModuleEnemy_H__
#define __ModuleEnemy_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "p2Qeue.h"
#include "SDL\include\SDL_timer.h"

#define MAX_KEYS 500
#define JUMP_TIME 1000
#define JUMPF_TIME 1000
#define JUMPB_TIME 1000

#define PUNCH_TIME 250
#define PUNCHF_TIME 250
#define PUNCHB_TIME 250
#define PUNCHN_TIME 250
#define PUNCHC_TIME 250

#define SP1_TIME 500

#define KICK_TIME 550
#define KICKF_TIME 550
#define KICKB_TIME 550
#define KICKN_TIME 550
#define KICKC_TIME 550

#define LDAMAGE_TIME 100
#define HDAMAGE_TIME 200
#define HHDAMAGE_TIME 300

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

	SDL_Texture* graphics = nullptr;
	Animation * current_animation = nullptr;

	Animation idle;
	Animation forward;
	Animation backward;
	Animation crouch;

	Animation jump;
	Animation jumpf;
	Animation jumpb;

	Animation lowd;
	Animation highd;
	Animation hhd;

	Animation sm1;

	Animation kick;
	Animation kickf;
	Animation kickb;
	Animation kickc;
	Animation kickn;

	Animation punch;
	Animation punchc;
	Animation punchf;
	Animation punchb;
	Animation punchn;

	Particle special;
	iPoint position;

	Mix_Chunk* Specialattack;
	Mix_Chunk* Punch;
	Mix_Chunk* Kick;

	Collider* enemycol;
	Collider* enemypunch;
	Collider* enemykick;

	Uint32 jump_timer = 0;
	Uint32 jumpf_timer = 0;
	Uint32 jumpb_timer = 0;

	Uint32 punch_timer = 0;
	Uint32 punchc_timer = 0;
	Uint32 punchf_timer = 0;
	Uint32 punchb_timer = 0;
	Uint32 punchn_timer = 0;

	Uint32 sp1_timer = 0;

	Uint32 kick_timer = 0;
	Uint32 kickc_timer = 0;
	Uint32 kickf_timer = 0;
	Uint32 kickb_timer = 0;
	Uint32 kickn_timer = 0;

	Uint32 ldamage_timer = 0;
	Uint32 hdamage_timer = 0;
	Uint32 hhdamage_timer = 0;

	bool animdone = true;
	bool jumpreset;
	bool TimeJump = false;
	bool anim_done = false;
	bool colcreated = false;

	bool godmode = false;
	bool dealtdamage = false;
	int countdown_font = -1;

	void OnCollision(Collider* c1, Collider* c2);


	float jumpspeed = 6;

	int speed = 2;
	float life = 100;


	enum enemy_states
	{
		ST_UNKNOWN,
		ST_IDLE,
		ST_WALK_FORWARD,
		ST_WALK_BACKWARD,
		ST_CROUCH,

		ST_SP1,

		ST_LDAMAGE,
		ST_HDAGAME,
		ST_HHDAMAGE,

		ST_JUMP_FORWARD,
		ST_JUMP_BACKWARD,
		ST_JUMP_NEUTRAL,

		ST_KICK_STANDING,
		ST_KICK_NEUTRAL_JUMP,
		ST_KICK_FORWARD_JUMP,
		ST_KICK_BACKWARD_JUMP,
		ST_KICK_CROUCH,

		ST_PUNCH_STANDING,
		ST_PUNCH_BACKWARD_JUMP,
		ST_PUNCH_FORWARD_JUMP,
		ST_PUNCH_NEUTRAL_JUMP,
		ST_PUNCH_CROUCH

	};

	enum enemy_inputs
	{
		IN_LEFT_DOWN,
		IN_LEFT_UP,

		IN_CROUCH_UP,
		IN_CROUCH_DOWN,

		IN_RIGHT_DOWN,
		IN_RIGHT_UP,

		IN_JUMP_AND_CROUCH,
		IN_JUMP_AND_LEFT,
		IN_JUMP_AND_RIGHT,
		IN_LEFT_AND_RIGHT,

		IN_JUMP_FINISH,
		IN_JUMPF_FINISH,
		IN_JUMPB_FINISH,

		IN_PUNCH_FINISH,
		IN_PUNCHF_FINISH,
		IN_PUNCHB_FINISH,
		IN_PUNCHN_FINISH,
		IN_PUNCHC_FINISH,

		IN_KICK_FINISH,
		IN_KICKF_FINISH,
		IN_KICKB_FINISH,
		IN_KICKN_FINISH,
		IN_KICKC_FINISH,

		IN_SP1_FINISH,

		IN_LDAMAGE_FINISH,
		IN_HDAMAGE_FINISH,
		IN_HHDAMAGE_FINISH,

		IN_JUMP,
		IN_JUMPF,
		IN_JUMB,

		IN_PUNCH,
		IN_PUNCHF,
		IN_PUNCHB,
		IN_PUNCHN,
		IN_PUNCHC,

		IN_KICK,
		IN_KICKF,
		IN_KICKB,
		IN_KICKN,
		IN_KICKC,

		IN_SM1,

		IN_LDAMAGE,
		IN_HDAMAGE,
		IN_HHDAMAGE,

	};

	bool external_input(p2Qeue<enemy_inputs>&);

	void internal_input(p2Qeue<enemy_inputs>&);

	enemy_states process_fsm(p2Qeue<enemy_inputs>& inputs)
	{
		static enemy_states state = ST_IDLE;
		enemy_inputs last_input;

		while (inputs.Pop(last_input))
		{
			switch (state)
			{

			case ST_IDLE:
			{
				switch (last_input)
				{

				case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
				case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
				case IN_CROUCH_DOWN: state = ST_CROUCH; break;
				case IN_JUMP: state = ST_JUMP_NEUTRAL; jump_timer = SDL_GetTicks();  break;

				case IN_PUNCH: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
				case IN_SM1: state = ST_SP1; sp1_timer = SDL_GetTicks(); break;
				case IN_KICK: state = ST_KICK_STANDING; kick_timer = SDL_GetTicks(); break;



				}
			}
			break;

			case ST_WALK_FORWARD:
			{

				switch (last_input)
				{

				case IN_RIGHT_UP: state = ST_IDLE; break;
				case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
				case IN_CROUCH_DOWN: state = ST_CROUCH; break;
				case IN_PUNCH: state = ST_PUNCH_STANDING, punch_timer = SDL_GetTicks(); break;
				case IN_KICK: state = ST_KICK_STANDING, kick_timer = SDL_GetTicks(); break;
				case IN_SM1: state = ST_SP1, sp1_timer = SDL_GetTicks(); break;

				}

			}
			break;

			case ST_WALK_BACKWARD:
			{
				switch (last_input)
				{

				case IN_LEFT_UP: state = ST_IDLE; break;
				case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
				case IN_CROUCH_DOWN: state = ST_CROUCH; break;
				case IN_PUNCH: state = ST_PUNCH_STANDING, punch_timer = SDL_GetTicks(); break;
				case IN_KICK: state = ST_KICK_STANDING, kick_timer = SDL_GetTicks(); break;
				case IN_SM1: state = ST_SP1, sp1_timer = SDL_GetTicks(); break;
				}
			}
			break;

			case ST_CROUCH:
			{
				switch (last_input)
				{

				case IN_CROUCH_UP: state = ST_IDLE; break;
				case IN_JUMP_AND_CROUCH: state = ST_IDLE; break;
				case IN_PUNCH: state = ST_PUNCH_STANDING, punch_timer = SDL_GetTicks(); break;
				case IN_KICK: state = ST_KICK_STANDING, kick_timer = SDL_GetTicks(); break;
				case IN_SM1: state = ST_SP1, sp1_timer = SDL_GetTicks(); break;

				}

			}
			break;

			case ST_JUMP_NEUTRAL:
			{
				switch (last_input)
				{

				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_JUMP: state = ST_JUMP_NEUTRAL; jump_timer = SDL_GetTicks(); break;

				}
			}
			break;

			case ST_PUNCH_STANDING:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_IDLE; break;



				}
			}
			break;

			case ST_KICK_STANDING:
			{

				switch (last_input)
				{

				case IN_KICK_FINISH: state = ST_IDLE; break;

				}
			}

			case ST_SP1:
			{

				switch (last_input)
				{

				case IN_SP1_FINISH: state = ST_IDLE; break;

				}
				break;

			}

			case ST_LDAMAGE:
			{

				switch (last_input) {

				case IN_LDAMAGE_FINISH: state = ST_IDLE; break;
				}
			}

			case ST_HDAGAME:
			{

				switch (last_input) {

				case IN_HDAMAGE_FINISH: state = ST_IDLE; break;
				}
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