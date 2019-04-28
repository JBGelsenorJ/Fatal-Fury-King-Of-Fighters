#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL\include\SDL.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemy.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleScenePaoPao.h"


ModuleEnemy::ModuleEnemy()
{
	position2.x = 200;
	position2.y = 220;

	//Terry Bogard Idle Animation
	idle2.PushBack({ 27, 914, 58, 103 });
	idle2.PushBack({ 95, 916, 59, 102 });
	idle2.PushBack({ 165, 917, 58, 101 });
	idle2.PushBack({ 95, 916, 59, 102 });

	idle2.speed = 0.18f;

	//Terry Bogard Forward Animation
	forward2.PushBack({ 32, 1300, 60, 105 });
	forward2.PushBack({ 108, 1300, 68, 105 });
	forward2.PushBack({ 189, 1300, 68, 105 });
	forward2.PushBack({ 263, 1300, 68, 105 });
	forward2.speed = 0.15f;

	//Terry Bogard Backward Animation
	backward2.PushBack({ 263, 1300, 57, 104 });
	backward2.PushBack({ 453, 1300, 57, 110 });
	backward2.PushBack({ 453, 1300, 57, 110 });
	backward2.PushBack({ 107, 1297, 71, 107 });
	backward2.PushBack({ 95, 916, 59, 102 });
	backward2.speed = 0.15f;

	//Terry Bogard Jump UP Animation
	jump2.PushBack({ 548, 1035, 51, 125 });
	jump2.PushBack({ 548, 1035, 51, 125 });
	jump2.PushBack({ 548, 1035, 51, 125 });
	jump2.PushBack({ 548, 1035, 51, 125 });
	jump2.PushBack({ 611, 1046, 57, 103 });
	jump2.PushBack({ 680, 1056, 57, 94 });
	jump2.PushBack({ 680, 1056, 57, 94 });
	jump2.PushBack({ 680, 1056, 57, 94 });

	jump2.speed = 0.12f;


	//Terry Bogard Kick Animation
	kick2.PushBack({ 449, 806, 59, 107 });
	kick2.PushBack({ 512, 803, 53, 107 });
	kick2.PushBack({ 31, 1150, 50, 97 });
	kick2.PushBack({ 84, 1148, 59, 115 });
	kick2.PushBack({ 149, 1151, 50, 108 });
	kick2.PushBack({ 211, 1155, 119, 108 });
	kick2.PushBack({ 342, 1152, 68, 111 });
	kick2.PushBack({ 714, 925, 64, 98 });
	kick2.speed = 0.18f;

	// punch animation 
	punch2.PushBack({ 506, 918, 60, 101 });
	punch2.PushBack({ 573, 918, 98, 101 });
	punch2.PushBack({ 506, 918, 60, 101 });
	punch2.speed = 0.1f;

	//crouch animation

	crouch2.PushBack({ 265, 949, 56, 70 });
	crouch2.speed = 0.2f;

	//Special Movement 1

	sm12.PushBack({ 970, 1334, 54, 106 });
	sm12.PushBack({ 897, 1325, 61, 115 });
	sm12.PushBack({ 833, 1343, 63, 97 });
	sm12.PushBack({ 679, 1359, 71, 81 });
	sm12.PushBack({ 612, 1359, 66, 81 });
	sm12.PushBack({ 547, 1359, 61, 81 });

	sm12.speed = 0.18f;

	//Low damage

	lowd2.PushBack({ 24, 475, 60, 100 });
	lowd2.PushBack({ 88, 469, 68, 107 });
	lowd2.speed = 0.15f;

	//High damage

	highd2.PushBack({ 160, 479, 65, 98 });
	highd2.PushBack({ 235, 478, 70, 88 });
	highd2.PushBack({ 88, 469, 68, 107 });
	highd2.speed = 0.15f;

}

ModuleEnemy::~ModuleEnemy()
{}

// Load assets
bool ModuleEnemy::Start()
{
	LOG("Loading player textures");
	bool ret = true;

	//Loading SpriteSheet
	graphics2 = App->textures->Load("Source/Sprites/Character_Sprites/Terry_Bogard/terry.png"); // Terry Bogard Sprites

	//Loading attack audios
	Kick = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack5.wav");
	Punch = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack4.wav");
	Specialattack = App->audio->LoadFX("Source/Sound/FX/Voice/SpecialAttacks/PoweWave.wav");

	//Loading Player Colliders
	enemycol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_ENEMY, this);
	enemypunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY_SHOT, 0);
	enemykick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY_SHOT, 0);


	countdown_font = App->fonts->Load("Source/UI/fonts/countdouwn_font.png", "012345678", 1);


	return ret;
}

// Update: draw background
update_status ModuleEnemy::Update()
{
	Animation* current_animation2 = &idle2;
	p2Qeue<enemy_inputs> inputs;
	enemy_states current_state = ST_UNKNOWN2;

	int speed = 2;

	while (external_input(inputs))
	{
		internal_input(inputs);

		enemy_states state = process_fsm(inputs);

		if (state != current_state)
		{
			switch (state)
			{
			case ST_IDLE2:
				current_animation2 = &idle2;
				forward2.Reset();
				backward2.Reset();
				crouch2.Reset();

				kick2.Reset();
				punch2.Reset();
				sm12.Reset();
				break;

			case ST_WALK2_FORWARD:
				current_animation2 = &forward2;
				position2.x += speed;
				backward2.Reset();
				crouch2.Reset();
				kick2.Reset();
				punch2.Reset();
				sm12.Reset();
				break;

			case ST_WALK2_BACKWARD:
				current_animation2 = &backward2;
				position2.x -= speed;
				forward2.Reset();
				crouch2.Reset();
				kick2.Reset();
				punch2.Reset();
				sm12.Reset();
				break;

				//case ST_JUMP_FORWARD:
					//LOG("JUMPING FORWARD ^^>>\n")
				//case ST_JUMP_BACKWARD:
					//LOG("JUMPING BACKWARD ^^<<\n");

			case ST_CROUCH2:
				current_animation2 = &crouch2;
				LOG("CROUCHING ****\n");
				break;
				//case ST_PUNCH_CROUCH:
					//LOG("PUNCH CROUCHING **++\n");
					//break;
			case ST_PUNCH2_STANDING:
				current_animation2 = &punch2;
				LOG("PUNCH STANDING ++++\n");
				enemycol = App->collision->AddCollider({ 10, 30, 55, 10 }, COLLIDER_ENEMY_SHOT, this);
				break;



				//case ST_PUNCH2_NEUTRAL_JUMP:
						//LOG("PUNCH NEUTRAL JUMP ++++\n");
						//break;
				//case ST_PUNCH2_FORWARD_JUMP:
						//LOG("PUNCH JUMP FORWARD ^>>+\n");
						//break;
				//case ST_PUNCH2_BACKWARD_JUMP:
						//LOG("PUNCH JUMP BACKWARD ^<<+\n");
						//break;
				//case ST_KICK2_CROUCH:
						//LOG("KICK CROUCHING **--\n");
						//break;


			case ST_KICK2_STANDING:
				current_animation2 = &kick2;
				break;

				//case ST_KICK2_NEUTRAL_JUMP:
				//	LOG("KICK JUMP NEUTRAL ^^--\n");
					//break;
			//case ST_KICK2_FORWARD_JUMP:
					//LOG("KICK JUMP FORWARD ^>>-\n");
					//break;
			//case ST_KICK2_BACKWARD_JUMP:
					//LOG("KICK JUMP BACKWARD ^<<-\n");
					//break;
			//case ST_DAMAGE2_RECEIVED:
					//current_animation = &beat;
					//break;

			case ST_SP12:

				current_animation2 = &sm12;
				Activesm1 = true;
				break;

			case ST_JUMP2_NEUTRAL:

				current_animation2 = &jump2;
				LOG("JUMPING  ^^^^\n");

				position2.y -= jumpspeed2;
				jumpspeed2 -= 0.2;

				if (current_animation2->AnimFinished() == true)
				{
					position2.y = 220;
					jumpspeed2 = 6.0;
				}

				break;

			}
		}

		current_state = state;

		SDL_Rect r = current_animation2->GetCurrentFrame();

		App->render->MirrorBlit(graphics2, position2.x, position2.y - r.h, &r, 1.0f, 0, NULL);

		enemycol->SetPos(position2.x, position2.y);
		enemypunch->SetPos(position2.x + 40, position2.y - 90);
		enemykick->SetPos(position2.x + 40, position2.y - 60);

		return UPDATE_CONTINUE;

	}
}


void ModuleEnemy::OnCollision(Collider* c1, Collider* c2) {



	if (enemycol == c1 && c2->type == COLLIDER_ENEMY && App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT && App->player->position.y == position2.y && position2.x < App->player->position.x)
	{
		App->player->position.x += 3;

	}

	if (enemycol == c1 && c2->type == COLLIDER_ENEMY && App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_REPEAT && App->player->position.y == position2.y && position2.x > App->player->position.x)
	{
		App->player->position.x -= 3;

	}

	if (enemycol == c1 && c2->type == COLLIDER_ENEMY)
	{
		App->player->position.x += 3;


	}

	else if (enemycol == c1 && c2->type == COLLIDER_WALL)
	{
		position2.x = 15;
	}

}

bool ModuleEnemy::external_input(p2Qeue<enemy_inputs>& inputs)
{
	static bool backward2 = false;
	static bool forward2 = false;
	static bool crouch2 = false;
	static bool jump2 = false;

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return false;
				break;

			case SDLK_j:
				inputs.Push(IN_CROUCH2_UP);
				crouch2 = false;
				break;

			case SDLK_u:

				jump2 = false;
				break;

			case SDLK_h:
				inputs.Push(IN_LEFT2_UP);
				backward2 = false;
				break;

			case SDLK_k:
				inputs.Push(IN_RIGHT2_UP);
				forward2 = false;
				break;

			case SDLK_o:
				break;

			case SDLK_p:
				break;

			case SDLK_l:
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{

			case SDLK_u:
				jump2 = true;
				//App->audio->PlayFX(AUDIOSALTO);
				break;
			case SDLK_j:
				crouch2 = true;
				break;
			case SDLK_h:
				backward2 = true;
				break;
			case SDLK_k:
				forward2 = true;
				break;

			case SDLK_o:
				enemypunch = App->collision->AddCollider({ 10, 30, 55, 10 }, COLLIDER_ENEMY_SHOT, this);
				inputs.Push(IN_PUNCH2);
				App->audio->PlayFX(Punch);
				break;

			case SDLK_p:
				enemykick = App->collision->AddCollider({ 10, 30, 75, 10 }, COLLIDER_ENEMY_SHOT, this);
				inputs.Push(IN_KICK2);
				App->audio->PlayFX(Kick);
				break;

			case SDLK_l:

				if (Activesm1 = true) {

					App->particles->AddParticle(App->particles->terryspecial1, position2.x + 48, position2.y - 42, COLLIDER_ENEMY_SHOT, 0);
					App->particles->AddParticle(App->particles->terryspecial2, position2.x + 35, position2.y - 70, COLLIDER_ENEMY_SHOT, 50);
					App->particles->AddParticle(App->particles->terryspecial3, position2.x + 18, position2.y - 99, COLLIDER_ENEMY_SHOT, 200);
					App->particles->AddParticle(App->particles->terryspecial4, position2.x + 5, position2.y - 70, COLLIDER_ENEMY_SHOT, 400);
					App->particles->AddParticle(App->particles->terryspecial5, position2.x - 13, position2.y - 42, COLLIDER_ENEMY_SHOT, 600);
					Activesm1 = false;
				}

				App->audio->PlayFX(Specialattack);

				inputs.Push(IN_SM12);

				break;
			}

		}

	}

	if (backward2 && forward2)
		inputs.Push(IN_LEFT2_AND_RIGHT);

	{
		if (backward2)
			inputs.Push(IN_LEFT2_DOWN);
		if (forward2)
			inputs.Push(IN_RIGHT2_DOWN);
	}

	if (jump2 && crouch2)
		inputs.Push(IN_JUMP2_AND_CROUCH);

	else
	{
		if (crouch2)
			inputs.Push(IN_CROUCH2_DOWN);
		if (jump2)
			inputs.Push(IN_JUMP2);
	}



	return true;
}

void ModuleEnemy::internal_input(p2Qeue<enemy_inputs>& inputs)
{
	if (jump_timer2 > 0)
	{
		if (SDL_GetTicks() - jump_timer2 > JUMP_TIME2)
		{
			inputs.Push(IN_JUMP2_FINISH);
			jump_timer2 = 0;

		}
	}

	if (punch_timer2 > 0)
	{
		if (SDL_GetTicks() - punch_timer2 > PUNCH_TIME2)
		{

			inputs.Push(IN_PUNCH2_FINISH);
			enemypunch->to_delete = true;
			punch_timer2 = 0;

		}
	}

	if (kick_timer2 > 0)
	{
		if (SDL_GetTicks() - kick_timer2 > KICK_TIME2)
		{
			enemykick->to_delete = true;
			inputs.Push(IN_KICK2_FINISH);
			kick_timer2 = 0;
		}
	}

	if (sp1_timer2 > 0)
	{
		if (SDL_GetTicks() - sp1_timer2 > SP1_TIME2)
		{
			inputs.Push(IN_SP12_FINISH);
			sp1_timer2 = 0;
		}
	}
}

bool ModuleEnemy::CleanUp()
{
	SDL_DestroyTexture(graphics2);
	App->player->Disable();
	LOG("Unloading Terry From Scene");

	return true;
}
/*
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL\include\SDL.h"
#include "ModuleParticles.h"
#include "ModuleEnemy.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleScenePaoPao.h"
#include "ModulePlayer.h"


ModuleEnemy::ModuleEnemy()
{
	position.x = 200;
	position.y = 220;

	//Terry Bogard Idle Animation
	idle.PushBack({ 27, 914, 58, 103 });
	idle.PushBack({ 95, 916, 59, 102 });
	idle.PushBack({ 165, 917, 58, 101 });
	idle.PushBack({ 95, 916, 59, 102 });

	idle.speed = 0.18f;

	//Terry Bogard Forward Animation
	forward.PushBack({ 32, 1300, 60, 105 });
	forward.PushBack({ 108, 1300, 68, 105 });
	forward.PushBack({ 189, 1300, 68, 105 });
	forward.PushBack({ 263, 1300, 68, 105 });
	forward.speed = 0.15f;

	//Terry Bogard Backward Animation
	backward.PushBack({ 263, 1300, 57, 104 });
	backward.PushBack({ 453, 1300, 57, 110 });
	backward.PushBack({ 453, 1300, 57, 110 });
	backward.PushBack({ 107, 1297, 71, 107 });
	backward.PushBack({ 95, 916, 59, 102 });
	backward.speed = 0.15f;

	//Terry Bogard Jump UP Animation
	jump.PushBack({ 548, 1035, 51, 125 });
	jump.PushBack({ 548, 1035, 51, 125 });
	jump.PushBack({ 548, 1035, 51, 125 });
	jump.PushBack({ 548, 1035, 51, 125 });
	jump.PushBack({ 611, 1046, 57, 103 });
	jump.PushBack({ 680, 1056, 57, 94 });
	jump.PushBack({ 680, 1056, 57, 94 });
	jump.PushBack({ 680, 1056, 57, 94 });

	jump.speed = 0.12f;

	//Terry Bogard Kick Animation
	kick.PushBack({ 449, 806, 59, 107 });
	kick.PushBack({ 512, 803, 53, 107 });
	kick.PushBack({ 31, 1150, 50, 97 });
	kick.PushBack({ 84, 1148, 59, 115 });
	kick.PushBack({ 149, 1151, 50, 108 });
	kick.PushBack({ 211, 1155, 119, 108 });
	kick.PushBack({ 342, 1152, 68, 111 });
	kick.PushBack({ 714, 925, 64, 98 });
	kick.speed = 0.18f;

	// punch animation 
	punch.PushBack({ 506, 918, 60, 101 });
	punch.PushBack({ 573, 918, 98, 101 });
	punch.PushBack({ 506, 918, 60, 101 });
	punch.speed = 0.1f;

	//crouch animation

	crouch.PushBack({ 265, 949, 56, 70 });
	crouch.speed = 0.2f;

	//Special Movement 1

	sm1.PushBack({ 970, 1334, 54, 106 });
	sm1.PushBack({ 897, 1325, 61, 115 });
	sm1.PushBack({ 833, 1343, 63, 97 });
	sm1.PushBack({ 679, 1359, 71, 81 });
	sm1.PushBack({ 612, 1359, 66, 81 });
	sm1.PushBack({ 547, 1359, 61, 81 });

	sm1.speed = 0.18f;

	//Low damage

	lowd.PushBack({ 24, 475, 60, 100 });
	lowd.PushBack({ 88, 469, 68, 107 });
	lowd.speed = 0.10f;

	//High damage

	highd.PushBack({ 24, 475, 60, 100 });
	highd.PushBack({ 88, 469, 68, 107 });
	highd.PushBack({ 160, 479, 65, 98 });
	highd.PushBack({ 235, 478, 70, 88 });
	highd.PushBack({ 88, 469, 68, 107 });
	highd.speed = 0.20f;


}

ModuleEnemy::~ModuleEnemy()
{}

// Load assets
bool ModuleEnemy::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Source/Sprites/Character_Sprites/Terry_Bogard/terry.png"); // Terry Bogard Sprites
	Kick = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack5.wav");
	Punch = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack4.wav");
	Specialattack = App->audio->LoadFX("Source/Sound/FX/Voice/SpecialAttacks/PoweWave.wav");

	//Loading Enemy Colliders
	enemycol = App->collision->AddCollider({ 210, -250, 55, -103 }, COLLIDER_ENEMY, this);
	enemypunch= App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY_SHOT, 0);
	enemykick= App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY_SHOT, 0);
	return ret;
}

// Update: draw background
update_status ModuleEnemy::Update()
{
	Animation* current_animation = &idle;

	int speed = 2;

	//Crouch
	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT) {

		current_animation = &crouch;

	}
	else {
		//MoveForward
		if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT && position.x < 670)
		{
			current_animation = &forward;
			position.x += speed;
		}

		//Move Backward
		if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_REPEAT && position.x > 0)
		{
			current_animation = &backward;
			position.x -= speed;
		}

		//Jump
		

		if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_REPEAT || (TimeJump == true)) {
				
				current_animation = &jump;
				
				TimeJump = true;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				
				if (current_animation->AnimFinished() == true)
				{
					TimeJump = false;
					position.y = 220;
					jumpspeed = 6;
				}
				
		}
		

		//Punch
		if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN || (TimePunch == true)) {
			current_animation = &punch;
			TimePunch = true;
			App->audio->PlayFX(Punch);
			if (current_animation->AnimFinished() == true)
			{
				TimePunch = false;
				enemypunch->to_delete = true;
			}
		}

		//Kick
		if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN || (KickAnim == true)) {
			KickAnim = true;
			current_animation = &kick;
			App->audio->PlayFX(Kick);
			if (current_animation->AnimFinished() == true)
			{
				enemykick->to_delete = true;
				KickAnim = false;
			}
		}

		//Special Move

		if ((App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN) || (TimeAnim == true))
		{
			TimeAnim = true;
			int cont = SDL_GetTicks();
			current_animation = &sm1;

			if (current_animation->AnimFinished() == true)
			{
				App->particles->AddParticle(App->particles->terryspecial1, position.x + 48, position.y - 42, COLLIDER_PLAYER_SHOT, 0);
				App->particles->AddParticle(App->particles->terryspecial2, position.x + 35, position.y - 70, COLLIDER_PLAYER_SHOT, 50);
				App->particles->AddParticle(App->particles->terryspecial3, position.x + 18, position.y - 99, COLLIDER_PLAYER_SHOT, 200);
				App->particles->AddParticle(App->particles->terryspecial4, position.x + 5, position.y - 70, COLLIDER_PLAYER_SHOT, 400);
				App->particles->AddParticle(App->particles->terryspecial5, position.x - 13, position.y - 42, COLLIDER_PLAYER_SHOT, 600);
				TimeAnim = false;
			}
		}



	}

	SDL_Rect r = current_animation->GetCurrentFrame();
	enemycol->SetPos(position.x, position.y);
	enemykick->SetPos(position.x, position.y);
	enemypunch->SetPos(position.x, position.y);
	App->render->MirrorBlit(graphics, position.x, position.y - r.h, &r, 1.0f, 0, NULL);

	return UPDATE_CONTINUE;
}

Uint32 jump2_timer = 0;
Uint32 punch2_timer = 0;
Uint32 sp12_timer = 0;
Uint32 kick2_timer = 0;


bool external_input(p2Qeue<enemy_inputs>& inputs)
{
	static bool backward = false;
	static bool forward = false;
	static bool crouch = false;
	static bool jump = false;
	static bool punch = false;
	static bool kick = false;
	static bool sp1 = false;

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return false;
				break;

			case SDLK_DOWN:
				inputs.Push(IN_CROUCH2_UP);
				crouch = false;
				break;

			case SDLK_UP:
				inputs.Push(IN_JUMP2_UP);
				jump = false;
				break;

			case SDLK_LEFT:
				inputs.Push(IN_LEFT2_UP);
				backward = false;
				break;

			case SDLK_RIGHT:
				inputs.Push(IN_RIGHT2_UP);
				forward = false;
				break;

			case SDLK_t:
				inputs.Push(IN_PUNCH2_UP);
				punch = false;
				break;

			case SDLK_y:
				inputs.Push(IN_KICK2_UP);
				kick = false;
				break;

			case SDLK_f:
				inputs.Push(IN_SP12_UP);
				sp1 = false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{

			case SDLK_UP:
				inputs.Push(IN_JUMP2_DOWN);
				jump = true;
				break;
			case SDLK_DOWN:
				inputs.Push(IN_CROUCH2_DOWN);
				crouch = true;
				break;
			case SDLK_LEFT:
				inputs.Push(IN_LEFT2_DOWN);
				backward = true;
				break;
			case SDLK_RIGHT:
				inputs.Push(IN_RIGHT2_DOWN);
				forward = true;
				break;

			case SDLK_t:
				inputs.Push(IN_PUNCH2_DOWN);
				punch = true;
				break;

			case SDLK_y:
				inputs.Push(IN_KICK2_DOWN);
				kick = true;
				break;

			case SDLK_f:
				inputs.Push(IN_SP12_DOWN);
				sp1 = true;
				break;
			}

		}

	}

	if (backward && forward) {

		inputs.Push(IN_LEFT2_AND_RIGHT);
	}
	else
	{
		if (backward)
			inputs.Push(IN_LEFT2_DOWN);
		if (forward)
			inputs.Push(IN_RIGHT2_DOWN);
	}

	if (jump && crouch) {
		inputs.Push(IN_JUMP2_AND_CROUCH);
	}
	else
	{
		if (crouch)
			inputs.Push(IN_CROUCH2_DOWN);
		if (jump)
			inputs.Push(IN_JUMP2_DOWN);
	}

	if (punch && kick) {
		inputs.Push(IN_PUNCH2_AND_KICK);
	}
	else
	{
		if (punch)
			inputs.Push(IN_PUNCH2_DOWN);
		if (kick)
			inputs.Push(IN_KICK2_DOWN);
	}

	if (punch && sp1) {
		inputs.Push(IN_PUNCH2_AND_SP1);
	}
	else
	{
		if (punch)
			inputs.Push(IN_PUNCH2_DOWN);
		if (sp1)
			inputs.Push(IN_SP12_DOWN);
	}

	if (kick && sp1) {
		inputs.Push(IN_KICK2_AND_SP1);
	}
	else
	{
		if (kick)
			inputs.Push(IN_KICK2_DOWN);
		if (sp1)
			inputs.Push(IN_SP12_DOWN);
	}

	if (punch && kick && sp1) {
		inputs.Push(IN_PUNCH2_AND_KICK_AND_SP1);
	}
	else
	{
		if (punch)
			inputs.Push(IN_PUNCH2_DOWN);
		if (kick)
			inputs.Push(IN_KICK2_DOWN);
		if (sp1)
			inputs.Push(IN_SP12_DOWN);

	}

	return true;
}

void internal_input(p2Qeue<enemy_inputs>& inputs)
{
	if (jump2_timer > 0)
	{
		if (SDL_GetTicks() - jump2_timer > JUMP2_TIME)
		{
			inputs.Push(IN_JUMP2_FINISH);
			jump2_timer = 0;
		}
	}

	if (punch2_timer > 0)
	{
		if (SDL_GetTicks() - punch2_timer > PUNCH2_TIME)
		{
			inputs.Push(IN_PUNCH2_FINISH);
			punch2_timer = 0;
		}
	}

	if (kick2_timer > 0)
	{
		if (SDL_GetTicks() - kick2_timer > KICK2_TIME)
		{
			inputs.Push(IN_KICK2_FINISH);
			kick2_timer = 0;
		}
	}

	if (sp12_timer > 0)
	{
		if (SDL_GetTicks() - sp12_timer > SP12_TIME)
		{
			inputs.Push(IN_SP12_FINISH);
			sp12_timer = 0;
		}
	}
}

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
			case IN_JUMP2_DOWN: state = ST_JUMP2_NEUTRAL; jump2_timer = SDL_GetTicks();  break;

			case IN_PUNCH2_DOWN: state = ST_PUNCH2_STANDING; punch2_timer = SDL_GetTicks();  break;
			case IN_SP12_DOWN: state = ST_SP12_STANDING; sp12_timer = SDL_GetTicks(); break;
			case IN_KICK2_DOWN: state = ST_KICK2_STANDING; kick2_timer = SDL_GetTicks(); break;

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

			case IN_RIGHT2_DOWN: state = ST_WALK2_FORWARD; break;
			case IN_RIGHT2_UP: state = ST_IDLE2; break;
			case IN_LEFT2_AND_RIGHT: state = ST_IDLE2; break;
			case IN_CROUCH2_DOWN: state = ST_CROUCH2; break;

			}

		}
		break;

		case ST_WALK2_BACKWARD:
		{
			switch (last_input)
			{
			case IN_LEFT2_DOWN: state = ST_WALK2_BACKWARD; break;
			case IN_LEFT2_UP: state = ST_IDLE2; break;
			case IN_LEFT2_AND_RIGHT: state = ST_IDLE2; break;
			case IN_CROUCH2_DOWN: state = ST_CROUCH2; break;
			}
		}
		break;

		case ST_CROUCH2:
		{
			switch (last_input)
			{

			case IN_CROUCH2_DOWN: state = ST_CROUCH2; break;
			case IN_CROUCH2_UP: state = ST_IDLE2; break;
			case IN_JUMP2_AND_CROUCH: state = ST_IDLE2; break;

			}

		}
		break;

		case ST_JUMP2_NEUTRAL:
		{
			switch (last_input)
			{
			case IN_JUMP2_UP: state = ST_IDLE2; break;
			case IN_JUMP2_DOWN: state = ST_JUMP2_NEUTRAL; jump2_timer = SDL_GetTicks(); break;
			case IN_JUMP2_AND_CROUCH: state = ST_IDLE2; break;
			case IN_JUMP2_FINISH: state = ST_IDLE2; break;

			}
		}
		break;

		case ST_PUNCH2_STANDING:
		{
			switch (last_input)
			{
			case IN_PUNCH2_UP: state = ST_IDLE2; break;
			case IN_PUNCH2_DOWN: state = ST_PUNCH2_STANDING; punch2_timer = SDL_GetTicks(); break;
			case IN_PUNCH2_AND_KICK: state = ST_IDLE2; break;
			case IN_PUNCH2_AND_KICK_AND_SP1: state = ST_IDLE2; break;
			case IN_PUNCH2_AND_SP1: state = ST_IDLE2; break;
			case IN_PUNCH2_FINISH: state = ST_IDLE2; break;

			}
		}
		break;

		case ST_KICK2_STANDING:
		{

			switch (last_input)
			{

			case IN_KICK2_UP: state = ST_IDLE2; break;
			case IN_KICK2_DOWN: state = ST_KICK2_STANDING; kick2_timer = SDL_GetTicks(); break;
			case IN_PUNCH2_AND_KICK: state = ST_IDLE2; break;
			case IN_PUNCH2_AND_KICK_AND_SP1: state = ST_IDLE2; break;
			case IN_KICK2_AND_SP1: state = ST_IDLE2; break;
			}
		}

		case ST_SP12_STANDING:
		{

			switch (last_input)
			{

			case IN_SP12_UP: state = ST_IDLE2; break;
			case IN_SP12_DOWN: state = ST_SP12_STANDING; sp12_timer = SDL_GetTicks(); break;
			case IN_PUNCH2_AND_SP1: state = ST_IDLE2; break;
			case IN_PUNCH2_AND_KICK_AND_SP1: state = ST_IDLE2; break;
			case IN_KICK2_AND_SP1: state = ST_IDLE2; break;
			}
		}
		}
	}

	return state;
}

bool ModuleEnemy::CleanUp()
{
	SDL_DestroyTexture(graphics);
	App->player->Disable();
	LOG("Unloading Terry From Scene");

	return true;
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2) {

	if (enemycol == c1 && c2->type == COLLIDER_PLAYER && App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_REPEAT && App->player->position.y == position.y && position.x > App->player->position.x)
	{
		App->player->position.x -= 3;

	}

	if (enemycol == c1 && c2->type == COLLIDER_PLAYER && App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT && App->player->position.y == position.y && position.x < App->player->position.x)
	{
		App->player->position.x += 3;

	}

	else if (enemycol == c1 && c2->type == COLLIDER_WALL)
	{
		position.x = 15;
	}

}*/
