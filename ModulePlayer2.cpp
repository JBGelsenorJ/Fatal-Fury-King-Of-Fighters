#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleMusic.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemy2.h"
#include "SDL\include\SDL.h"
#include "ModuleFonts.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleSceneBillyKane.h"
#include "Animation.h"
#include "ModuleSlowdown.h"

ModulePlayer2::ModulePlayer2()
{
	current_animation = NULL;
	graphics = NULL;

	//IDLE
	{

		//Andy Bogard Idle Animation
		idle.PushBack({ 811, 341, 60, 101 });
		idle.PushBack({ 873, 343, 61, 100 });
		idle.PushBack({ 937, 346, 61, 98 });
		idle.PushBack({ 873, 343, 61, 100 });

		idle.speed = 0.18f;

	}

	//NORMAL MOVEMENTS (WALK AND CROUCH)
	{
		//Andy Bogard Forward Animation
		forward.PushBack({ 744, 602, 64, 99 });
		forward.PushBack({ 819, 601, 57, 100 });
		forward.PushBack({ 877, 601, 64, 100 });
		forward.PushBack({ 943, 599, 61, 102 });
		forward.speed = 0.15f;

		//Andy Bogard Backward Animation
		backward.PushBack({ 946, 476, 55, 97 });
		backward.PushBack({ 865, 474, 55, 99 });
		backward.PushBack({ 800, 471, 50, 102 });
		backward.PushBack({ 744, 473, 51, 100 });
		backward.speed = 0.15f;

		//crouch animation

		crouch.PushBack({ 946, 158, 51, 66 });
		crouch.speed = 0.2f;

	}

	//JUMP
	{

		//Andy Bogard Jump NEUTRAL Animation
		jump.PushBack({ 375, 121, 61, 102 });
		jump.PushBack({ 441, 142, 55, 81 });
		jump.PushBack({ 514, 118, 44, 106 });
		jump.PushBack({ 577, 117, 52, 95 });
		jump.PushBack({ 647, 121, 51, 85 });
		jump.PushBack({ 707, 142, 55, 81 });

		jump.speed = 0.12f;


		//Andy Bogard Jump FORWARD Animation

		jumpf.PushBack({ 728, 822, 58, 95 });
		jumpf.PushBack({ 802, 831, 69, 57 });
		jumpf.PushBack({ 884, 810, 50, 107 });

		jumpf.speed = 0.12f;

		//Terry Bogard Jump BACKWARD Animation

		jumpb.PushBack({ 728, 822, 58, 95 });
		jumpb.PushBack({ 802, 831, 69, 57 });
		jumpb.PushBack({ 884, 810, 50, 107 });

		jumpb.speed = 0.12f;

	}

	//KICK
	{
		//Terry Bogard Kick Animation
		kick.PushBack({ 310, 13, 47, 100 });
		kick.PushBack({ 378, 24, 57, 89 });
		kick.PushBack({ 448, 20, 54, 92 });
		kick.PushBack({ 506, 23, 126, 93 });
		kick.PushBack({ 641, 11, 85, 96 });
		kick.PushBack({ 747, 26, 55, 82 });
		kick.PushBack({ 832, 11, 61, 102 });

		kick.speed = 0.13f;

		//Terry Bogard Kick JUMPF Animation
		kickf.PushBack({ 305, 718, 52, 83 });
		kickf.PushBack({ 369, 721, 58, 77 });
		kickf.PushBack({ 435, 727, 96, 71 });

		kickf.speed = 0.1f;

		//Terry Bogard Kick JUMPB Animation
		kickb.PushBack({ 305, 718, 52, 83 });
		kickb.PushBack({ 369, 721, 58, 77 });
		kickb.PushBack({ 435, 727, 96, 71 });

		kickb.speed = 0.1f;

		//Terry Bogard Kick JUMPN Animation
		kickn.PushBack({ 713, 709, 57, 87 });
		kickn.PushBack({ 778, 710, 94, 89 });

		kickn.speed = 0.1f;

		//Terry Bogard Kick Crouch Animation
		kickc.PushBack({ 23, 739, 54, 62 });
		kickc.PushBack({ 93, 744, 68, 57 });
		kickc.PushBack({ 165, 765, 121, 36 });

		kickc.speed = 0.18f;
	}

	//PUNCH
	{
		// punch animation 

		punch.PushBack({ 15, 121, 60, 101 });
		punch.PushBack({ 88, 131, 51, 92 });
		punch.PushBack({ 154, 127, 50, 97 });
		punch.PushBack({ 219, 126, 95, 97 });

		punch.speed = 0.14f;

		// punch jumpf animation
		punchf.PushBack({ 19, 824, 52, 100 });
		punchf.PushBack({ 79, 824, 68, 94 });
		punchf.PushBack({ 152, 803, 57, 121 });
		punchf.PushBack({ 237, 815, 64, 97 });
		punchf.PushBack({ 314, 811, 81, 99 });

		punchf.speed = 0.1f;

		// punch jumpb animation
		punchb.PushBack({ 19, 824, 52, 100 });
		punchb.PushBack({ 79, 824, 68, 94 });
		punchb.PushBack({ 152, 803, 57, 121 });
		punchb.PushBack({ 237, 815, 64, 97 });
		punchb.PushBack({ 314, 811, 81, 99 });

		punchb.speed = 0.1f;

		// punch jumpn animation
		punchn.PushBack({ 234, 809, 70, 106 });
		punchn.PushBack({ 311, 807, 86, 106 });
		punchn.speed = 0.05f;

		// punch crouch animation
		punchc.PushBack({ 880, 734, 51, 65 });
		punchc.PushBack({ 942, 735, 79, 64 });

		punchc.speed = 0.1f;

	}

	//SPECIAL MOVEMENTS

	//Special Movement 1

	sm1.PushBack({ 23, 357, 66, 99 });
	sm1.PushBack({ 92, 361, 52, 94 });
	sm1.PushBack({ 153, 364, 51, 94 });
	sm1.PushBack({ 216, 363, 99, 92 });

	sm1.speed = 0.17f;

	//DAMAGE
	{
		//Low damage

		lowd.PushBack({ 719, 918, 65, 97 });
		lowd.PushBack({ 784, 931, 67, 82 });
		lowd.speed = 0.15f;

		//High damage

		highd.PushBack({ 719, 918, 65, 97 });
		highd.PushBack({ 780, 931, 67, 84 });
		highd.PushBack({ 852, 920, 55, 95 });
		highd.PushBack({ 907, 931, 68, 81 });
		highd.speed = 0.15f;

		//Hihgh High damage


		hhd.PushBack({ 719, 918, 65, 97 });
		hhd.PushBack({ 780, 931, 67, 84 });
		hhd.PushBack({ 852, 920, 55, 95 });
		hhd.PushBack({ 907, 931, 68, 81 });
		hhd.PushBack({ 26, 934, 92, 81 });
		hhd.PushBack({ 125, 941, 100, 61 });
		hhd.PushBack({ 231, 942, 89, 56 });
		hhd.PushBack({ 315, 948, 101, 44 });
		hhd.PushBack({ 420, 953, 114, 38 });
		hhd.PushBack({ 521, 916, 109, 33 });


		hhd.speed = 0.15f;
	}

		//Shadow
		shadow.x = 644;
		shadow.y = 696;
		shadow.w = 65;
		shadow.h = 14;


}

ModulePlayer2::~ModulePlayer2(){
}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	App->particles->cont = 0;
	bool ret = true;
	colcreated = true;
	Activesm1 = true;

	graphics = App->textures->Load("Source/Sprites/Character_Sprites/Andy_Bogard/andy.png");
	Kick = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Kick.wav");
	Punch = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Punch.wav");

	position.x = 100;
	position.y = 220;
	initialPos = position.y;

	playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_PLAYER, this);
	playerpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playerkick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playercrouchkick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playercrouchpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playerjumpnkick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playerjumpnpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);

	//winanimation.Reset();

	return ret;

}

bool ModulePlayer2::CleanUp()
{
	//App->input->inputs.Push(IN_WIN_FINISH);

	SDL_DestroyTexture(graphics);
	App->player2->Disable();
	App->audio->Disable();
	// DANGER NEXT LINE IF USED CREATES EXCEPTION AND BREAKS GAME
//App->audio->CleanUp();
	LOG("Unloading Andy From Scene");

	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{

	Animation* current_animation = &idle;

	player_states current_state = ST_UNKNOWN;
	player_states state = process_fsm(App->input->inputs);

	App->render->Blit(graphics, position.x - 5, 210, &shadow, 1.0f, true);

	int speed = 2;

	//god mode
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		
		if (godmode == false)
		{
			
			playercol->to_delete = true;

			godmode = true;
		}
		else if (godmode == true)
		{
			playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_PLAYER, this);

			godmode = false;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN) {

		App->enemy2->life = 0; //Kill Enemy

	}
	
	if (state != current_state)
	{

		switch (state)
		{

		case ST_IDLE:

			current_animation = &idle;

			forward.Reset();
			backward.Reset();
			crouch.Reset();
			jump.Reset();
			jumpf.Reset();
			jumpb.Reset();


			kick.Reset();
			kickb.Reset();
			kickf.Reset();
			kickc.Reset();

			punch.Reset();
			punchb.Reset();
			punchf.Reset();
			punchc.Reset();
			sm1.Reset();

			hhd.Reset();
			highd.Reset();
			lowd.Reset();

			break;

		case ST_WALK_FORWARD:

			if (position.x > App->enemy2->position.x)
			{
				current_animation = &backward;
				forward.Reset();
			}
			else
			{
				current_animation = &forward;
				backward.Reset();
			}

			controllermover = true;
			position.x += speed;
			crouch.Reset();
			jump.Reset();
			jumpf.Reset();
			jumpb.Reset();


			kick.Reset();
			kickb.Reset();
			kickf.Reset();
			kickc.Reset();

			punch.Reset();
			punchb.Reset();
			punchf.Reset();
			punchc.Reset();
			sm1.Reset();

			hhd.Reset();
			highd.Reset();
			lowd.Reset();

			break;

		case ST_WALK_BACKWARD:

			if (position.x > App->enemy2->position.x)
			{
				current_animation = &forward;
				backward.Reset();
			}
			else
			{
				current_animation = &backward;
				forward.Reset();
			}

			controllermovel = true;
			position.x -= speed;
			crouch.Reset();
			jump.Reset();
			jumpf.Reset();
			jumpb.Reset();


			kick.Reset();
			kickb.Reset();
			kickf.Reset();
			kickc.Reset();

			punch.Reset();
			punchb.Reset();
			punchf.Reset();
			punchc.Reset();
			sm1.Reset();

			hhd.Reset();
			highd.Reset();
			lowd.Reset();

			break;

		case ST_JUMP_NEUTRAL:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &jump;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
			}

			if (SDL_GetTicks() - App->input->jump_timer > JUMP_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->jump_timer = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			break;

		case ST_JUMP_FORWARD:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &jumpf;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				position.x += 2;
			}

			if (SDL_GetTicks() - App->input->jump_timer > JUMP_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->jump_timer = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}
			LOG("JUMPING FORWARD ^^>>\n");

			break;

		case ST_JUMP_BACKWARD:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &jumpb;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				position.x -= 2;
			}

			if (SDL_GetTicks() - App->input->jump_timer > JUMP_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->jump_timer = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}
			LOG("JUMPING BACKWARD ^^<<\n");

			break;

		case ST_CROUCH:

			current_animation = &crouch;
			punchc.Reset();
			kickc.Reset();
			LOG("CROUCHING ****\n");

			break;

		case ST_PUNCH_CROUCH:
			if (attack == true)
			{
				attack = false;
				if (colcreated == true)
				{
					App->audio->PlayFX(Punch);
					playercrouchpunch = App->collision->AddCollider({ 10, 20, 35, 10 }, COLLIDER_PLAYER_SHOT, this);
					colcreated = false;
				}
			}
			if (Active == 0)
			{
				current_animation = &punchc;
			}

			LOG("PUNCH CROUCHING **++\n");

			break;

		case ST_PUNCH_STANDING:
			if (attack == true)
			{
				App->audio->PlayFX(Punch);
				attack = false;
			}
			if (Active == 0)
			{
				current_animation = &punch;
			}
			LOG("PUNCH STANDING ++++\n");
			if (colcreated == true)
			{
				playerpunch = App->collision->AddCollider({ 10, 20, 55, 10 }, COLLIDER_PLAYER_SHOT, this);
				colcreated = false;
			}
			break;

		case ST_PUNCH_NEUTRAL_JUMP:


			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &punchn;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				if (colcreated == true)
				{
					playerjumpnpunch = App->collision->AddCollider({ 10, 20, 55, 10 }, COLLIDER_PLAYER_SHOT, this);
					colcreated = false;
				}
			}


			if (SDL_GetTicks() - App->input->punchn_timer > PUNCHN_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->punchn_timer = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			LOG("PUNCH NEUTRAL JUMP ++++\n");


			break;

		case ST_PUNCH_FORWARD_JUMP:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &punchf;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				position.x += 2;
			}

			if (SDL_GetTicks() - App->input->punchf_timer > PUNCHF_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->punchf_timer = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			LOG("PUNCH JUMP FORWARD ^>>+\n");

			break;

		case ST_PUNCH_BACKWARD_JUMP:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &punchb;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				position.x -= 2;
			}

			if (SDL_GetTicks() - App->input->punchb_timer > PUNCHB_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->punchb_timer = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}
			LOG("PUNCH JUMP BACKWARD ^<<+\n");

			break;

		case ST_KICK_CROUCH:

			if (attack == true)
			{
				if (colcreated == true)
				{
					playercrouchkick = App->collision->AddCollider({ 10, 20, 100, 10 }, COLLIDER_PLAYER_SHOT, this);
				}
				attack = false;
			}
			if (Active == 0)
			{
				current_animation = &kickc;
			}

			LOG("KICK CROUCHING **--\n");

			break;

		case ST_KICK_STANDING:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &kick;


				//Check where should go fx
				//App->audio->PlayFX(Kick);		
				if (SDL_GetTicks() - App->input->kick_timer > 400 && position.y == 180)
				{
					position.y = 220;

				}

			}

			if (SDL_GetTicks() - App->input->kick_timer > KICK_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_KICK_FINISH);
				App->input->kick_timer = 0;

				position.y = 220;
				kick_jumpspeed = 6;
				animdone = true;
			}

			/*if (attack == true)
			{
				//App->audio->PlayFX(Audio);
				attack = false;
			}
			if (Active == 0)
			{
				current_animation = &kick;
			}*/

			LOG("KICK --\n")
			if (App->player2->colcreated == true)
			{
				App->player2->playerkick = App->collision->AddCollider({ 30, 100, 50, 10 }, COLLIDER_PLAYER_SHOT, this);
				App->player2->playerpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
				App->player2->colcreated = false;
			}
				break;

		case ST_KICK_NEUTRAL_JUMP:

			/*if (attack == true)
			{
				//App->audio->PlayFX(ryokick);
				attack = false;
			}
			if (Active == 0)
			{
				current_animation = &kickn;
			}*/

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &kickn;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				if (colcreated == true)
				{
					playerjumpnkick = App->collision->AddCollider({ 10, 20, 55, 10 }, COLLIDER_PLAYER_SHOT, this);
					colcreated = false;
				}
				
			}

			if (SDL_GetTicks() - App->input->kickn_timer > KICKN_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->kickn_timer = 0;
				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			LOG("KICK JUMP NEUTRAL ^^--\n");

			break;

		case ST_KICK_FORWARD_JUMP:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &kickf;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				position.x += 2;
			}

			if (SDL_GetTicks() - App->input->kickf_timer > KICKF_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->kickf_timer = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			LOG("KICK JUMP FORWARD ^>>-\n");
			
			break;

		case ST_KICK_BACKWARD_JUMP:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &kickb;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				position.x -= 2;
			}

			if (SDL_GetTicks() - App->input->kickb_timer > KICKB_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->kickb_timer = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			LOG("KICK JUMP BACKWARD ^<<-\n");

			break;

		case ST_SM1:
			App->particles->p1 = true;
			current_animation = &sm1;
			if (Activesm1 == true)
			{
				if (App->particles->cont<1)
				{
					App->particles->AddParticle(App->particles->andyspecial1, position.x + 30, position.y - 90, COLLIDER_PLAYER_SHOT, 0);
				}

			Activesm1 = false;


			}
			break;


		case ST_LDAMAGE:

			if (App->enemy2->lowdamage1 == true)
			{
				current_animation = &lowd;
			}

			break;

		case ST_HDAMAGE:

			if (App->enemy2->highdamage1 == true)
			{
				current_animation = &highd;
			}

			break;
		
		case ST_HHDAMAGE:

			if (App->enemy2->hhdamage1 == true)
			{
				current_animation = &hhd;
			}

			break;

		/*case ST_WIN:
			current_animation = &winAnimation;
			break;*/

		}

	}

	current_state = state;

	SDL_Rect* r = &current_animation->GetCurrentFrame();

	playercol->SetPos(position.x, position.y);
	if (App->enemy2->position.x > position.x)
	{
		App->render->Blit(graphics, position.x + (current_animation->pivotx2[current_animation->returnCurrentFrame()]), position.y - r->h + current_animation->pivoty2[current_animation->returnCurrentFrame()], r);
	}

	if (App->enemy2->position.x < position.x)
	{
		App->render->BlitWithScale(graphics, position.x + 50 + (-current_animation->pivotx2[current_animation->returnCurrentFrame()]), position.y - r->h + current_animation->pivoty2[current_animation->returnCurrentFrame()], r, -1, 1.0f, 1, TOP_RIGHT);
	}

	if (App->enemy2->position.x > position.x) {
			
		playerpunch->SetPos(position.x + 40, position.y - 90);
		playerkick->SetPos(position.x + 60, position.y - 80);
		playercrouchpunch->SetPos(position.x + 40, position.y - 55);
		playercrouchkick->SetPos(position.x+20, position.y-20);
		playerjumpnkick->SetPos(position.x + 30, position.y - 15);
		playerjumpnpunch->SetPos(position.x + 35, position.y - 55);

	}
	
	if (App->enemy2->position.x < position.x) {
			
		playerpunch->SetPos(position.x - 40, position.y - 90);
		playerkick->SetPos(position.x - 60, position.y - 80);
		playercrouchpunch->SetPos(position.x - 40, position.y - 55);
		playercrouchkick->SetPos(position.x - 70, position.y - 20);
		playerjumpnkick->SetPos(position.x - 30, position.y - 15);
		playerjumpnpunch->SetPos(position.x - 30, position.y - 55);

	}

	playercol->SetPos(position.x, position.y);

	return UPDATE_CONTINUE;

}

player_states ModulePlayer2::process_fsm(p2Qeue<player_inputs>& inputs)
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
			case IN_JUMP: state = ST_JUMP_NEUTRAL; App->input->jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_T: state = ST_PUNCH_STANDING, App->input->punch_timer = SDL_GetTicks(); break;
			case IN_R: state = ST_KICK_STANDING, App->input->kick_timer = SDL_GetTicks(); break;
			case IN_F: state = ST_SM1, App->input->sp1_timer = SDL_GetTicks(); break;
			case IN_LDAMAGE: state = ST_LDAMAGE, App->input->ldamage_timer = SDL_GetTicks(); break;
			case IN_HDAMAGE: state = ST_HDAMAGE, App->input->hdamage_timer = SDL_GetTicks(); break;
			case IN_HHDAMAGE: state = ST_HHDAMAGE, App->input->hhdamage_timer = SDL_GetTicks(); break;
			//case IN_WIN: state = ST_WIN; Active = 0;  break;
			}
		}
		break;

		case ST_WALK_FORWARD:
		{

			switch (last_input)
			{

			case IN_RIGHT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_FORWARD;  App->input->jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_T: state = ST_PUNCH_STANDING, App->input->punch_timer = SDL_GetTicks(); break;
			case IN_R: state = ST_KICK_STANDING, App->input->kick_timer = SDL_GetTicks(); break;
			case IN_F: state = ST_SM1, App->input->sp1_timer = SDL_GetTicks(); break;
			case IN_LDAMAGE: state = ST_LDAMAGE, App->input->ldamage_timer = SDL_GetTicks(); break;
			case IN_HDAMAGE: state = ST_HDAMAGE, App->input->hdamage_timer = SDL_GetTicks(); break;
			case IN_HHDAMAGE: state = ST_HHDAMAGE, App->input->hhdamage_timer = SDL_GetTicks(); break;
			//case IN_WIN: state = ST_WIN; Active = 0;  break;
			}

		}
		break;

		case ST_WALK_BACKWARD:
		{

			switch (last_input)
			{

			case IN_LEFT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_BACKWARD;  App->input->jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_T: state = ST_PUNCH_STANDING, App->input->punch_timer = SDL_GetTicks(); break;
			case IN_R: state = ST_KICK_STANDING, App->input->kick_timer = SDL_GetTicks(); break;
			case IN_F: state = ST_SM1, App->input->sp1_timer = SDL_GetTicks(); break;
			//case IN_WIN: state = ST_WIN; Active = 0;  break;
			
			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{

			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; Active = 0; attack = true; break;
			case IN_T: state = ST_PUNCH_NEUTRAL_JUMP; App->input->punchn_timer = SDL_GetTicks(); Active = 0; attack = true; break;
			case IN_R: state = ST_KICK_NEUTRAL_JUMP; App->input->kickn_timer = SDL_GetTicks(); Active = 0; attack = true; break;
			//case IN_WIN: state = ST_WIN; animstart = 0;  break;

			}
		}
		break;

		case ST_JUMP_FORWARD:
		{

			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; Active = 0; attack = true; break;
			case IN_T: state = ST_PUNCH_FORWARD_JUMP;  App->input->punchf_timer = SDL_GetTicks(); Active = 0; attack = true; break;
			case IN_R: state = ST_KICK_FORWARD_JUMP;  App->input->kickf_timer = SDL_GetTicks(); Active = 0; attack = true; break;
			//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{

			switch (last_input)
			{

			case IN_JUMP_FINISH: state = ST_IDLE; Active = 0; attack = true; break;
			case IN_T: state = ST_PUNCH_BACKWARD_JUMP;  App->input->punchb_timer = SDL_GetTicks(); break;
			case IN_R: state = ST_KICK_BACKWARD_JUMP;  App->input->kickb_timer = SDL_GetTicks(); Active = 0; attack = true; break;
			//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}

		}
		break;

		case ST_PUNCH_NEUTRAL_JUMP:
		{
			switch (last_input)
			{

			case IN_PUNCH_FINISH: state = ST_JUMP_NEUTRAL; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}

		}
		break;

		case ST_PUNCH_FORWARD_JUMP:
		{
			switch (last_input)
			{

			case IN_PUNCH_FINISH: state = ST_JUMP_FORWARD; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			//case IN_WIN: state = ST_WIN; Active = 0;  break;
			}

		}
		break;

		case ST_PUNCH_BACKWARD_JUMP:
		{
			switch (last_input)
			{

			case IN_PUNCH_FINISH: state = ST_JUMP_BACKWARD; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}
		}
		break;

		case ST_PUNCH_STANDING:
		{
			switch (last_input)
			{

			case IN_PUNCH_FINISH: state = ST_IDLE; Active = 0; attack = true; break;
			case IN_LDAMAGE: state = ST_LDAMAGE, App->input->ldamage_timer = SDL_GetTicks(); break;
			

			}
		}
		break;

		case ST_CROUCH:
		{
			playercol->to_delete = true;
			playercol = App->collision->AddCollider({ 50, -250, 45, -65 }, COLLIDER_PLAYER, this);
			switch (last_input)
			{
			
			case IN_CROUCH_UP: state = ST_IDLE; playercol->to_delete = true; playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_PLAYER, this); break;
			case IN_JUMP_AND_CROUCH: state = ST_IDLE; break;
			case IN_T: state = ST_PUNCH_CROUCH; App->input->punchc_timer = SDL_GetTicks(); break;
			case IN_R: state = ST_KICK_CROUCH; App->input->kickc_timer = SDL_GetTicks(); break;
			case IN_LDAMAGE: state = ST_LDAMAGE, App->input->ldamage_timer = SDL_GetTicks(); break;
			case IN_HDAMAGE: state = ST_HDAMAGE, App->input->hdamage_timer = SDL_GetTicks(); break;
			//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}
		}
		break;

		case ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{
			case IN_LDAMAGE: state = ST_LDAMAGE, App->input->ldamage_timer = SDL_GetTicks(); break;
			
			case IN_PUNCH_CROUCH_FINISH:

				if (IN_CROUCH_DOWN == true)
				{
					state = ST_CROUCH; Active = 0; attack = true;

				}
				else
				{
					state = ST_IDLE; Active = 0; attack = true;
				}

			//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}
		}

		break;

		case ST_KICK_STANDING:
		{
			switch (last_input)
			{

			case IN_KICK_FINISH: state = ST_IDLE; playercol->to_delete = true; playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_PLAYER, this); attack = true; break;
			
			case IN_HDAMAGE: state = ST_HDAMAGE, App->input->hdamage_timer = SDL_GetTicks(); break;

			//case IN_WIN: state = ST_WIN; Active = 0;  break;
			
			}

		}
		break;

		case ST_KICK_NEUTRAL_JUMP:
		{
			switch (last_input)
			{

			case IN_KICK_FINISH: state = ST_JUMP_NEUTRAL; Active = 0; attack = true; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}
		}

		case ST_KICK_CROUCH:
		{
			switch (last_input)
			{
			
			case IN_HDAMAGE: state = ST_HDAMAGE, App->input->hdamage_timer = SDL_GetTicks(); break;
			
			case IN_KICK_CROUCH_FINISH:

				if (IN_CROUCH_DOWN == true)
				{
					state = ST_CROUCH; Active = 0; attack = true;

				}

				else
				{
					state = ST_IDLE; Active = 0; attack = true;
				}

			//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}
		}

		case ST_SM1:
		{

			switch (last_input)
			{

			case IN_SM1_FINISH: state = ST_IDLE; Active = 0; Activesm1 = true; break;

			}
			break;

		}

		case ST_KICK_FORWARD_JUMP:
		{
			switch (last_input)
			{

			case IN_KICK_FINISH: state = ST_JUMP_FORWARD; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}

		}
		break;

		case ST_KICK_BACKWARD_JUMP:
		{
			switch (last_input)
			{

			case IN_KICK_FINISH: state = ST_JUMP_BACKWARD; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}

		}
		break;

		case ST_LDAMAGE:
		{

			switch (last_input) {

			case IN_LDAMAGE_FINISH: state = ST_IDLE; Active = 0;  break;
			}
		}

		case ST_HDAMAGE:
		{

			switch (last_input) {

			case IN_HDAMAGE_FINISH: state = ST_IDLE; Active = 0; break;
			}
		}

		case ST_HHDAMAGE:
		{

			switch (last_input) {

			case IN_HHDAMAGE_FINISH: state = ST_IDLE; Active = 0; break;
			}
		}

		/*case ST_WIN:

			switch (last_input)
			{
			case IN_WIN_FINISH: state = ST_IDLE; Active = 0; break;

			}
			break;*/

		
		}
	}
	return state;

}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {

	if ( playercol == c1 && c2->type == COLLIDER_ENEMY  && App->enemy2->position.y == position.y && position.x < App->enemy2->position.x/* || playercol == c1 && c2->type == COLLIDER_ENEMY && controllermover == true*/)
	{
		App->enemy2->position.x += 3;

	}

	if ( playercol == c1 && c2->type == COLLIDER_ENEMY && App->enemy2->position.y == position.y && position.x > App->enemy2->position.x/* || playercol == c1 && c2->type == COLLIDER_ENEMY && controllermovel == true*/ )
	{
		App->enemy2->position.x -= 3;

	}

	if (playerpunch == c1 && c2->type == COLLIDER_ENEMY)
	{
		
		App->render->StartCameraShake(250, 3);
		App->render->UpdateCameraShake();
		playerpunch->to_delete = true;
		lowdamage2 = true;
		App->input->inputs2.Push(IN_LDAMAGE2);
		App->enemy2->position.x += 3; 
		App->enemy2->life -= 25;
		//TRYING RUMBLE
		SDL_HapticRumblePlay(App->input->haptic, 0.2f, 500);
	}
	if (playercrouchpunch == c1 && c2->type == COLLIDER_ENEMY)
	{

		App->render->StartCameraShake(250, 3);
		App->render->UpdateCameraShake();
		playercrouchpunch->to_delete = true;
		lowdamage2 = true;
		App->input->inputs2.Push(IN_LDAMAGE2);
		App->enemy2->position.x += 3;
		App->enemy2->life -= 10;

		//TRYING RUMBLE
		SDL_HapticRumblePlay(App->input->haptic, 0.2f, 500);
	}
	if (playerjumpnpunch == c1 && c2->type == COLLIDER_ENEMY)
	{

		App->render->StartCameraShake(250, 3);
		App->render->UpdateCameraShake();
		playerjumpnpunch->to_delete = true;
		lowdamage2 = true;
		App->input->inputs2.Push(IN_LDAMAGE2);
		App->enemy2->position.x += 3;
		App->enemy2->life -=10;

		//TRYING RUMBLE
		SDL_HapticRumblePlay(App->input->haptic, 0.2f, 500);
	}
	if (playerkick == c1 && c2->type == COLLIDER_ENEMY )
	{
		
		App->render->StartCameraShake(250, 3);
		App->render->UpdateCameraShake();
		playerkick->to_delete = true;
		highdamage2 = true;
		App->input->inputs2.Push(IN_HDAMAGE2);
		App->enemy2->life -= 25;
		App->enemy2->position.x += 3;
		
		//TRYING RUMBLE
		SDL_HapticRumblePlay(App->input->haptic, 0.2f, 500);
		LOG("MUST RUMBLE");
	}
	if (playerjumpnkick == c1 && c2->type == COLLIDER_ENEMY)
	{

		App->render->StartCameraShake(250, 3);
		App->render->UpdateCameraShake();
		playerjumpnkick->to_delete = true;
		highdamage2 = true;
		App->input->inputs2.Push(IN_HDAMAGE2);
		App->enemy2->life -= 10;
		App->enemy2->position.x += 3;

		//TRYING RUMBLE
		SDL_HapticRumblePlay(App->input->haptic, 0.2f, 500);
		LOG("MUST RUMBLE");
	}
	if (playercrouchkick == c1 && c2->type == COLLIDER_ENEMY)
	{

		App->render->StartCameraShake(250, 3);
		App->render->UpdateCameraShake();
		playercrouchkick->to_delete = true;
		highdamage2 = true;
		App->input->inputs2.Push(IN_HDAMAGE2);
		App->enemy2->life -= 10;
		App->enemy2->position.x += 3;

		//TRYING RUMBLE
		SDL_HapticRumblePlay(App->input->haptic, 0.2f, 500);
		LOG("MUST RUMBLE");



	}

	if (playercol == c1 && App->scene_billykane->wall2c == c2)   //Colisions with second wall
	{
			position.x -= 2;

	}
	if (playercol == c1 && App->scene_billykane->wall1c == c2)   //Colisions with first wall
	{
			position.x += 2;

	}
	if (App->enemy2->life <= 0)
	{
		/*App->slowdown->StartSlowdown(500, 40);
		App->slowdown->UpdateSlowdown();*/
	}
}