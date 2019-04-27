#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "p2Qeue.h"
#include "SDL\include\SDL_timer.h"



#define MAX_KEYS 300
#define JUMP_TIME 1050
#define PUNCH_TIME 400
#define SP1_TIME 500
#define KICK_TIME 550

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool Activesm1 = false;

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
	Animation sm1;
	
	Particle special;
	iPoint position;
	
	Mix_Chunk* Specialattack;
	Mix_Chunk* Punch;
	Mix_Chunk* Kick;
	
	Collider* playercol;
	Collider* playerpunch;
	Collider* playerkick;

	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;
	Uint32 sp1_timer = 0;
	Uint32 kick_timer = 0;
	
	bool jumpreset;
	bool TimeJump = false;
	
	bool godmode = false;
	int countdown_font = -1;
	
	void OnCollision(Collider* c1, Collider* c2);
	
	float jumpspeed = 6;
	int speed = 2;
	int life = 100;

	enum player_states
	{
		ST_UNKNOWN,
		ST_IDLE,
		ST_WALK_FORWARD,
		ST_WALK_BACKWARD,
		ST_JUMP_NEUTRAL,
		ST_CROUCH,
		ST_PUNCH_STANDING,
		ST_SP1,
		ST_KICK_STANDING,

	};

	enum player_inputs
	{
		IN_LEFT_DOWN,
		IN_LEFT_UP,

		IN_RIGHT_DOWN,
		IN_RIGHT_UP,

		
		IN_JUMP,

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

		IN_PUNCH,
		IN_KICK,
		IN_SM1,


	};

	bool external_input(p2Qeue<player_inputs>&);

	void internal_input(p2Qeue<player_inputs>&);

	player_states process_fsm(p2Qeue<player_inputs>& inputs)
	{
		static player_states state = ST_IDLE;
		player_inputs last_input;

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

				case IN_PUNCH_AND_KICK: state = ST_IDLE; break;
				case IN_PUNCH_AND_SP1: state = ST_IDLE; break;
				case IN_KICK_AND_SP1: state = ST_IDLE; break;
				case IN_PUNCH_AND_KICK_AND_SP1: state = ST_IDLE; break;

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
				case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
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

				case IN_CROUCH_DOWN: state = ST_CROUCH; break;
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
				case IN_PUNCH_AND_KICK: state = ST_IDLE; break;
				case IN_PUNCH_AND_KICK_AND_SP1: state = ST_IDLE; break;
				case IN_PUNCH_AND_SP1: state = ST_IDLE; break;
				

				}
			}
			break;

			case ST_KICK_STANDING:
			{

				switch (last_input)
				{

				case IN_KICK_FINISH: state = ST_IDLE; break;
				case IN_PUNCH_AND_KICK: state = ST_IDLE; break;
				case IN_PUNCH_AND_KICK_AND_SP1: state = ST_IDLE; break;
				case IN_KICK_AND_SP1: state = ST_IDLE; break;
				}
			}

			case ST_SP1:
			{

				switch (last_input)
				{

				case IN_SP1_FINISH: state = ST_IDLE; break;
				case IN_PUNCH_AND_SP1: state = ST_IDLE; break;
				case IN_PUNCH_AND_KICK_AND_SP1: state = ST_IDLE; break;
				case IN_KICK_AND_SP1: state = ST_IDLE; break;
				}
				break;
			
			}
			}
		}

		return state;
	}
	
};

#endif