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



ModuleEnemy2::ModuleEnemy2()
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
			kick.PushBack({ 515, 24, 114, 77 });
			kick.PushBack({ 641, 11, 85, 96 });
			kick.PushBack({ 747, 26, 55, 82 });
			kick.PushBack({ 832, 11, 61, 102 });
			
			kick.speed = 0.18f;

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
		
		punch.speed = 0.18f;

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
		punchn.PushBack({ 22, 21, 60, 87 });
		punchn.PushBack({ 81, 28, 74, 80 });
		punchn.PushBack({ 167, 21, 60, 86 });
		
		punchn.speed = 0.1f;

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

		/*		//DAMAGE
				{
				//Low damage

				lowd.PushBack({ 24, 475, 60, 100 });
				lowd.PushBack({ 88, 469, 68, 107 });
				lowd.speed = 0.15f;

				//High damage

				highd.PushBack({ 160, 479, 65, 98 });
				highd.PushBack({ 235, 478, 70, 88 });
				highd.PushBack({ 88, 469, 68, 107 });
				highd.speed = 0.15f;

				//Hihgh High damage

				hhd.PushBack({ 75, 5, 101, 91 });
				hhd.PushBack({ 185, 48, 112, 44 });
				hhd.PushBack({ 299, 44, 116, 44 });
				hhd.PushBack({ 423, 41, 97, 47 });
				hhd.PushBack({ 523, 22, 82, 70 });
				hhd.PushBack({ 614, 19, 58, 74 });
				hhd.PushBack({ 677, 11, 58, 82 });
				hhd.PushBack({ 88, 469, 68, 107 });

				hhd.speed = 0.15f;
				}*/

				//Shadow
		shadow.x = 644;
		shadow.y = 695;
		shadow.w = 66;
		shadow.h = 14;

}


ModuleEnemy2::~ModuleEnemy2() {
}

// Load assets
bool ModuleEnemy2::Start()
{

	LOG("Loading player textures");
	bool ret = true;
	colcreated = true;
	Activesm1 = true;

	graphics = App->textures->Load("Source/Sprites/Character_Sprites/Andy_Bogard/andy2.png");
	Kick = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack5.wav");
	Punch = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack4.wav");
	Specialattack = App->audio->LoadFX("Source/Sound/FX/Voice/SpecialAttacks/PoweWave.wav");

	position.x = 200;
	position.y = 220;
	initialPos = position.y;

	playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_ENEMY, this);
	playerpunch = App->collision->AddCollider({0, 0, 0, 0 }, COLLIDER_ENEMY_SHOT, 0);
	playerkick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY_SHOT, 0);

	return ret;

}

bool ModuleEnemy2::CleanUp()
{
	SDL_DestroyTexture(graphics);
	App->player2->Disable();
	LOG("Unloading Andy From Scene");

	return true;
}

// Update: draw background
update_status ModuleEnemy2::Update()
{

	Animation* current_animation = &idle;

	player_states current_state = ST_UNKNOWN;
	player_states state = process_fsm(App->input->inputs2);
	App->render->Blit(graphics, position.x - 5, 210, &shadow, 0, false);

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
			playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_ENEMY, this);

			godmode = false;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN) {

		App->player2->life = 0; //Kill Enemy

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
			kick.Reset();
			punch.Reset();
			sm1.Reset();
			jump.Reset();

			break;

		case ST_WALK_FORWARD:

			current_animation = &forward;
			position.x += speed;

			backward.Reset();
			crouch.Reset();
			jump.Reset();
			kick.Reset();
			punch.Reset();
			sm1.Reset();

			break;

		case ST_WALK_BACKWARD:

			current_animation = &backward;
			position.x -= speed;

			forward.Reset();
			crouch.Reset();
			crouch.Reset();
			kick.Reset();
			punch.Reset();
			sm1.Reset();

			break;

		case ST_JUMP_NEUTRAL:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &jump;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
			}



			if (SDL_GetTicks() - App->input->jump_timer2 > JUMP_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH2);
				App->input->jump_timer2 = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			/*if (position.y <= 220)
			{
				animdone = false;
				current_animation = &jump;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
			}

			if ((position.y == 220 && jump_timer > 0) || current_animation->AnimFinished() == true)
			{
				position.y = 220;
				jumpspeed = 6;
				animdone == true;
			}
			if (Active == 0)
			{
				position.y -= jumpSpeed;
				current_animation = &jump;

				if (attack == true)
				{
					//App->audio->PlayFX("AudioJUMP");
					attack = false;
				}

				if (position.y < 220) {
					jumpSpeed -= 0.5;
					if (jumpSpeed < 0) jumpSpeed = -6;
				}
				if (position.y >= initialPos && jumpSpeed < 0) {
					Active = 1;
					position.y = initialPos;
					jumpSpeed = 6;
				}*/
				LOG("JUMPING ^^\n")
			

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



			if (SDL_GetTicks() - App->input->jump_timer2 > JUMP_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH2);
				App->input->jump_timer2 = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			/*if (position.y <= 220)
			{
				animdone = false;
				current_animation = &jumpf;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				position.x += 2;
			}



			if (SDL_GetTicks() - App->input->jump_timer2 > JUMP_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH2);
				App->input->jump_timer2 = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}*/

			/*if (Active == 0)
			{
				current_animation = &jump;
				position.y -= jumpSpeed;
				position.x += 3;

				if (attack == true)
				{
					//App->audio->PlayFX("AudioJUMP");
					attack = false;
				}

				if (position.y < 220) {
					jumpSpeed -= 0.5;
					if (jumpSpeed < 0) jumpSpeed = -6;
				}
				if (position.y >= initialPos && jumpSpeed < 0) {
					Active = 1;
					position.y = initialPos;
					jumpSpeed = 6;
				}
			}*/
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



			if (SDL_GetTicks() - App->input->jump_timer2 > JUMP_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH2);
				App->input->jump_timer2 = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			/*if (Active == 0)
			{
				current_animation = &jump;
				position.y -= jumpSpeed;

				if (attack == true)
				{
					//App->audio->PlayFX("AudioJUMP");
					attack = false;
				}

				//if (wall) {}
				//else {
				//	if (position.x) position.x -= 3;
				//}

				if (position.y < 120) {

					jumpSpeed -= 0.5;
					if (jumpSpeed < 0) jumpSpeed = -6;

				}
				if (position.y >= initialPos && jumpSpeed < 0) {

					Active = 1;
					position.y = initialPos;
					jumpSpeed = 6;

				}
			}*/
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
				//App->audio->PlayFX("Audio");
				attack = false;
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
			{
				if (App->enemy2->colcreated == true)
				{
					App->enemy2->playerpunch = App->collision->AddCollider({ 10, 30, 55, 10 }, COLLIDER_ENEMY_SHOT, this);
					App->enemy2->playerkick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY_SHOT, 0);
					App->enemy2->colcreated = false;
				}

			}
			

			break;

		case ST_PUNCH_NEUTRAL_JUMP:


			/*if (attack == true)
			{
				//App->audio->PlayFX(Audio);
				attack = false;
			}
			if (Active == 0)
			{
				current_animation = &punchn;
			}*/

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &punchn;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
			}

			//CAMINA HACIA DELANTE AL PEGAR
			if (position.x < App->player2->position.x)
			{
				position.x += 1;
			}
			if (position.x > App->player2->position.x)
			{
				position.x -= 1;
			}



			if (SDL_GetTicks() - App->input->punchn_timer2 > PUNCHN_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH2);
				App->input->punchn_timer2 = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			LOG("PUNCH NEUTRAL JUMP ++++\n");

			/*if (position.y <= 220)
			{
				animdone = false;
				current_animation = &punchn;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
			}
			if ((position.y == 220 && punchn_timer > 0) || current_animation->AnimFinished() == true)
			{
				position.y = 220;
				jumpspeed = 6;
				animdone == true;
			}*/

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



			if (SDL_GetTicks() - App->input->punchf_timer2 > PUNCHF_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH2);
				App->input->punchf_timer2 = 0;

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



			if (SDL_GetTicks() - App->input->punchb_timer2 > PUNCHB_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH2);
				App->input->punchb_timer2 = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			LOG("PUNCH JUMP BACKWARD ^<<+\n");

			break;

		case ST_KICK_CROUCH:

			position.x += 0.5*speed;
			if (attack == true)
			{
				//App->audio->PlayFX(Audio);

				attack = false;
			}
			if (Active == 0)
			{
				current_animation = &kickc;
			}

			LOG("KICK CROUCHING **--\n");

			break;

		case ST_KICK_STANDING:

			if (attack == true)
			{
				//App->audio->PlayFX(Audio);
				attack = false;
			}
			if (Active == 0)
			{
				current_animation = &kick;
			}

			LOG("KICK --\n")
				if (App->enemy2->colcreated == true)
				{
					App->enemy2->playerkick = App->collision->AddCollider({ 10, 30, 75, 10 }, COLLIDER_ENEMY_SHOT, 0);
					App->enemy2->playerpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY_SHOT, 0);
					App->enemy2->colcreated = false;
				}
				if (App->enemy2->colcreated == true)
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
			}

			//AL PEGAR CAMINA HACIA DELANTE
			if (position.x < App->player2->position.x)
			{
				position.x += 1;
			}
			if (position.x > App->player2->position.x)
			{
				position.x -= 1;
			}



			if (SDL_GetTicks() - App->input->kickn_timer2 > KICKN_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH2);
				App->input->kickn_timer2 = 0;

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



			if (SDL_GetTicks() - App->input->kickf_timer2 > KICKF_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH2);
				App->input->kickf_timer2 = 0;

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



			if (SDL_GetTicks() - App->input->kickb_timer2 > KICKB_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH2);
				App->input->kickb_timer2 = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			LOG("KICK JUMP BACKWARD ^<<-\n");

			break;

		case ST_SM1:

			current_animation = &sm1;
			if (Activesm1 == true)
			{	
			//App->audio->PlayFX(Audio);
			App->particles->AddParticle(App->particles->andyspecial2, position.x + 30, position.y -90, COLLIDER_ENEMY_SHOT, 0);
			Activesm1 = false;
			break;

			}




			/*case ST_LDAMAGE:

				if (dealtdamage == true) {

					current_animation = &lowd;

				}

				break;

			case ST_HDAGAME:

				/*if ()
				{
				current_animation=&highd
				}

				break;*/

		}

	}

	current_state = state;

	SDL_Rect* r = &current_animation->GetCurrentFrame();

	playercol->SetPos(position.x, position.y);
	playerpunch->SetPos(position.x + 40, position.y - 90);
	playerkick->SetPos(position.x + 40, position.y - 60);

	if (App->player2->position.x > position.x)
	{
		App->render->Blit(graphics, position.x + (current_animation->pivotx2[current_animation->returnCurrentFrame()]), position.y - r->h + current_animation->pivoty2[current_animation->returnCurrentFrame()], r);
	}

	if (App->player2->position.x < position.x)
	{
		App->render->BlitWithScale(graphics, position.x + 50 + (-current_animation->pivotx2[current_animation->returnCurrentFrame()]), position.y - r->h + current_animation->pivoty2[current_animation->returnCurrentFrame()], r, -1, 1.0f, 1, TOP_RIGHT);
	}

	if (App->player2->position.x > position.x) {

		playerpunch->SetPos(position.x + 40, position.y - 90);
		playerkick->SetPos(position.x + 40, position.y - 60);

	}

	if (App->player2->position.x < position.x) {

		playerpunch->SetPos(position.x - 40, position.y - 90);
		playerkick->SetPos(position.x - 40, position.y - 60);

	}

	playercol->SetPos(position.x, position.y);

	return UPDATE_CONTINUE;

}

player_states ModuleEnemy2::process_fsm(p2Qeue<player_inputs>& inputs)
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

			case IN_RIGHT_DOWN2: state = ST_WALK_FORWARD; break;
			case IN_LEFT_DOWN2: state = ST_WALK_BACKWARD; break;
			case IN_JUMP2: state = ST_JUMP_NEUTRAL; App->input->jump_timer2 = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH; break;
			case IN_Y: state = ST_PUNCH_STANDING, App->input->punch_timer2 = SDL_GetTicks(); break;
			case IN_U: state = ST_KICK_STANDING, App->input->kick_timer2 = SDL_GetTicks(); break;
			case IN_H: state = ST_SM1, App->input->sp1_timer2 = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_WALK_FORWARD:
		{

			switch (last_input)
			{

			case IN_RIGHT_UP2: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE; break;
			case IN_JUMP2: state = ST_JUMP_FORWARD;  App->input->jump_timer2 = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH; break;
			case IN_Y: state = ST_PUNCH_STANDING, App->input->punch_timer2 = SDL_GetTicks(); break;
			case IN_U: state = ST_KICK_STANDING, App->input->kick_timer2 = SDL_GetTicks(); break;
			case IN_H: state = ST_SM1, App->input->sp1_timer2 = SDL_GetTicks(); break;

			}

		}
		break;

		case ST_WALK_BACKWARD:
		{

			switch (last_input)
			{

			case IN_LEFT_UP2: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE; break;
			case IN_JUMP2: state = ST_JUMP_BACKWARD;  App->input->jump_timer2 = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH; break;
			case IN_Y: state = ST_PUNCH_STANDING, App->input->punch_timer2 = SDL_GetTicks(); break;
			case IN_U: state = ST_KICK_STANDING, App->input->kick_timer2 = SDL_GetTicks(); break;
			case IN_H: state = ST_SM1, App->input->sp1_timer2 = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{

			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE; Active = 0; attack = true; break;
			case IN_Y: state = ST_PUNCH_NEUTRAL_JUMP;  App->input->punch_timer2 = SDL_GetTicks(); Active = 0; attack = true; break;
			case IN_U: state = ST_KICK_NEUTRAL_JUMP;  App->input->kick_timer2 = SDL_GetTicks(); Active = 0; attack = true; break;

			}
		}
		break;

		case ST_JUMP_FORWARD:
		{

			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE; Active = 0; attack = true; break;
			case IN_Y: state = ST_PUNCH_FORWARD_JUMP;   App->input->punch_timer2 = SDL_GetTicks(); break;
			case IN_U: state = ST_KICK_FORWARD_JUMP;  App->input->kickf_timer2 = SDL_GetTicks(); Active = 0; attack = true; break;


			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{

			switch (last_input)
			{

			case IN_JUMP_FINISH2: state = ST_IDLE; Active = 0; attack = true; break;
			case IN_Y: state = ST_PUNCH_BACKWARD_JUMP;  App->input->punchb_timer2 = SDL_GetTicks(); break;
			case IN_U: state = ST_KICK_BACKWARD_JUMP;  App->input->kickb_timer2 = SDL_GetTicks(); Active = 0; attack = true; break;

			}

		}
		break;

		case ST_PUNCH_NEUTRAL_JUMP:
		{
			switch (last_input)
			{

			case IN_PUNCH_FINISH2: state = ST_JUMP_NEUTRAL; attack = true; break;
			case IN_JUMP_FINISH2: state = ST_IDLE; break;

			}

		}
		break;

		case ST_PUNCH_FORWARD_JUMP:
		{
			switch (last_input)
			{

			case IN_PUNCH_FINISH2: state = ST_JUMP_FORWARD; break;
			case IN_JUMP_FINISH2: state = ST_IDLE; break;

			}

		}
		break;

		case ST_PUNCH_BACKWARD_JUMP:
		{
			switch (last_input)
			{

			case IN_PUNCH_FINISH2: state = ST_JUMP_BACKWARD; break;
			case IN_JUMP_FINISH2: state = ST_IDLE; break;


			}
		}
		break;

		case ST_PUNCH_STANDING:
		{
			switch (last_input)
			{

			case IN_PUNCH_FINISH2: state = ST_IDLE; Active = 0; attack = true; break;

			}
		}
		break;

		case ST_CROUCH:
		{

		playercol->to_delete = true;
		playercol = App->collision->AddCollider({ 50, -250, 45, -65 }, COLLIDER_ENEMY, this);

		switch (last_input)
		{

		case IN_CROUCH_UP2: state = ST_IDLE; playercol->to_delete = true; playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_ENEMY, this); break;
			case IN_JUMP_AND_CROUCH2: state = ST_IDLE; break;
			case IN_Y: state = ST_PUNCH_CROUCH; App->input->punchc_timer2 = SDL_GetTicks(); break;
			case IN_U: state = ST_KICK_CROUCH; App->input->kickc_timer2 = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{

			case IN_PUNCH_CROUCH_FINISH2:

				if (IN_CROUCH_DOWN2 == true)
				{
					state = ST_CROUCH; Active = 0; attack = true;

				}
				else
				{
					state = ST_IDLE; Active = 0; attack = true;
				}

			}
		}

		break;

		case ST_KICK_STANDING:
		{
			switch (last_input)
			{

			case IN_KICK_FINISH2: state = ST_IDLE; Active = 0; attack = true; break;

			}

		}
		break;

		case ST_KICK_NEUTRAL_JUMP:
		{
			switch (last_input)
			{

			case IN_KICK_FINISH2: state = ST_JUMP_NEUTRAL; Active = 0; attack = true; break;
			case IN_JUMP_FINISH2: state = ST_IDLE; break;

			}
		}

		case ST_KICK_FORWARD_JUMP:
		{
			switch (last_input)
			{

			case IN_KICK_FINISH2: state = ST_JUMP_FORWARD; break;
			case IN_JUMP_FINISH2: state = ST_IDLE; break;

			}

		}
		break;

		case ST_KICK_BACKWARD_JUMP:
		{
			switch (last_input)
			{

			case IN_KICK_FINISH2: state = ST_JUMP_BACKWARD; break;
			case IN_JUMP_FINISH2: state = ST_IDLE; break;

			}

		}
		break;

		case ST_KICK_CROUCH:
		{
			switch (last_input)
			{
			case IN_KICK_CROUCH_FINISH2:

				if (IN_CROUCH_DOWN2 == true)
				{
					state = ST_CROUCH; Active = 0; attack = true;

				}

				else
				{
					state = ST_IDLE; Active = 0; attack = true;
				}

			}
		}

		case ST_SM1:
		{

			switch (last_input)
			{

			case IN_SM1_FINISH2: state = ST_IDLE; Active = 0; Activesm1 = true; break;

			}
			break;

		}

		/*case ST_LDAMAGE:
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

		}*/
		}
	}
	return state;

}

void ModuleEnemy2::OnCollision(Collider* c1, Collider* c2) {


	if (playercol == c1 && c2->type == COLLIDER_PLAYER && App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT && App->player2->position.y == position.y && position.x < App->player2->position.x)
	{
		App->player2->position.x += 3;

	}


	if (playercol == c1 && c2->type == COLLIDER_PLAYER && App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT && App->player2->position.y == position.y && position.x > App->player2->position.x)
	{
		App->player2->position.x -= 3;

	}

	if (playerpunch == c1 && c2->type == COLLIDER_PLAYER)
	{
		App->render->StartCameraShake(250, 3);
		App->render->UpdateCameraShake();
		playerpunch->to_delete = true;
		App->player2->position.x += 3;
		App->player2->life -= 25;


	}

	if (playerkick == c1 && c2->type == COLLIDER_PLAYER)
	{
		App->render->StartCameraShake(250, 3);
		App->render->UpdateCameraShake();
		playerkick->to_delete = true;
		App->player2->life -= 25;
		App->player2->position.x += 3;


	}


	if (playercol == c1 && c2->type == COLLIDER_WALL)
	{
		if (App->render->camera.x >= -200)
		{
			position.x ++;
			App->render->camera.x+=10;
			App->scene_billykane->wall1.x-=5;
			App->scene_billykane->wall2.x-=5;
		}
	}
	if (playercol == c1 && c2->type == COLLIDER_WALL_RIGHT)
	{
		position.x --;
		App->render->camera.x-=10;
		App->scene_billykane->wall1.x += 5;
		App->scene_billykane->wall2.x += 5;

	}
}
