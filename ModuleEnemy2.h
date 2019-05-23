#ifndef __ModuleEnemy2_H__
#define __ModuleEnemy2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "p2Qeue.h"
#include "ModuleInput.h"
#include "SDL\include\SDL_timer.h"

struct SDL_Texture;

class ModuleEnemy2 : public Module
{
public:

	ModuleEnemy2();
	~ModuleEnemy2();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool Active = false;
	bool Activesm1 = true;
	bool shoot = false;
	int jumpSpeed = 6;
	bool attack = true;

public:

	SDL_Texture* graphics = nullptr;
	Animation * current_animation = nullptr;
	SDL_Rect shadow;



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

	int initialPos;


	bool animdone = true;
	bool jumpreset;
	bool TimeJump = false;
	bool anim_done = false;
	bool colcreated = false;
	bool forplayer = false;

	bool playaudio = false;
	bool godmode = false;
	bool dealtdamage = false;
	void OnCollision(Collider* c1, Collider* c2);
	player_states process_fsm(p2Qeue<player_inputs>& inputs);

	float jumpspeed = 6;
	float kick_jumpspeed = 6;

	int speed = 2;
	float life = 100;
	int score = 0;
	int rounds = 0;
};

#endif