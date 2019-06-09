#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

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

class ModulePlayer2 : public Module
{
public:
	
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool Active = false;
	bool Activesm1 = true;
	bool Activesm2 = true;
	bool Activesm3 = true;
	bool shoot = false;
	int jumpSpeed = 6;
	bool attack = true;

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect shadow;
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
	
	Mix_Chunk* Punch;
	Mix_Chunk* Kick;
	
	Collider* playercol;
	Collider* playerpunch;
	Collider* playercrouchpunch;
	Collider* playerjumpnpunch;
	Collider* playerkick;
	Collider* playercrouchkick;
	Collider* playerjumpnkick;
	Collider* playerdash;
	Collider* playerjumpfpunch;
	Collider* playerjumpbpunch;
	Collider* playerjumpfkick;
	Collider* playerjumpbkick;
	Collider* playerwindmill;
	int initialPos;

	
	bool animdone = true;
	bool jumpreset;
	bool TimeJump = false;
	bool anim_done = false;
	bool colcreated = false;
	bool forplayer = false;
	
	bool playaudio = false;
	bool controllermover = false;
	bool controllermovel = false;
	bool godmode;
	bool lowdamage2 = false;
	bool highdamage2 = false;
	bool hhdamage2 = false;
	bool hit = false;
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
	int cont = 0;
	int rounds = 0;

	int timer_combo;

	// COMBOS
	Uint32 combo1 = 0;
	Uint32 combo2 = 0;
	Uint32 combo3 = 0;
	Uint32 combo4 = 0;

	Uint32 combotime;
	Uint32 combosm1;
	Uint32 combosm2;
	Uint32 combosm3;
	Uint32 combosm4;
};

#endif