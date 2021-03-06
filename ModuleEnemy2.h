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

#define TIME_COMBO 1000


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
	bool Activesm2 = true;
	bool Activesm3 = true;
	bool Activesm4 = true;
	bool shoot = false;
	bool lowdamage1 = false;
	bool highdamage1 = false;
	bool hhdamage1 = false;
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
	Animation sm2;
	Animation sm3;
	Animation sm4;

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
	Collider* enemycrouchpunch;
	Collider* enemyjumpnpunch;
	Collider* enemycrouchkick;
	Collider* enemyjumpnkick;;
	Collider* enemydash;
	Collider* enemyjumpfpunch;
	Collider* enemyjumpbpunch;
	Collider* enemyjumpfkick;
	Collider* enemyjumpbkick;
	Collider* enemywindmill;

	

	int initialPos;
	bool hit = false;

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
	float dash_speed = 6;
	float flykick_speed = 4;
	float hhd_speed = 3;

	int speed = 2;
	float life = 100;
	int score = 0;
	int rounds = 0;

	int timer_combo;
	
	// COMBOS
	Uint32 combo12 = 0;
	Uint32 combo22 = 0;
	Uint32 combo32 = 0;
	Uint32 combo42 = 0;

	Uint32 combotime2;
	Uint32 combosm12;
	Uint32 combosm22;
	Uint32 combosm32;

};

#endif