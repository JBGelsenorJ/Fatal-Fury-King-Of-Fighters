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


ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	//Terry Bogard Idle Animation
	idle.PushBack({27, 914, 58, 103});
	idle.PushBack({95, 916, 59, 102});
	idle.PushBack({165, 917, 58, 101});
	idle.PushBack({ 95, 916, 59, 102 });

	idle.speed = 0.18f;

	//Terry Bogard Forward Animation
	forward.PushBack({32, 1300, 60, 105});
	forward.PushBack({108, 1300, 68, 105});
	forward.PushBack({189, 1300, 68, 105});
	forward.PushBack({263, 1300, 68, 105});
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
	lowd.speed = 0.15f;

	//High damage

	highd.PushBack({ 160, 479, 65, 98 });
	highd.PushBack({ 235, 478, 70, 88 });
	highd.PushBack({ 88, 469, 68, 107 });
	highd.speed = 0.15f;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	colcreated = true;
	Activesm1 = true;
	//Loading SpriteSheet
	graphics = App->textures->Load("Source/Sprites/Character_Sprites/Terry_Bogard/terry.png"); // Terry Bogard Sprites
	
	//Loading attack audios
	Kick = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack5.wav");
	Punch = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack4.wav");
	Specialattack = App->audio->LoadFX("Source/Sound/FX/Voice/SpecialAttacks/PoweWave.wav");
	
	//Loading Player Colliders
	playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_PLAYER, this);
	playerpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playerkick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);


	countdown_font = App->fonts->Load("Source/UI/fonts/countdouwn_font.png", "012345678", 1);


	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		if (godmode == false)
		{
			playercol->to_delete = true;
			App->enemy->enemycol->to_delete = true;

			godmode = true;
		}
		else if (godmode == true)
		{
			playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_PLAYER, this);
			App->enemy->enemycol = App->collision->AddCollider({ 210, -250, 55, -103 }, COLLIDER_ENEMY, (Module*) App->enemy->enemycol);
			godmode = false;
		}
	}
	Animation* current_animation = &idle;
	p2Qeue<player_inputs> inputs;
	player_states current_state = ST_UNKNOWN;

	int speed = 2;
	
	
	while (external_input(inputs))
	{
		internal_input(inputs);

		player_states state = process_fsm(inputs);

		if (state != current_state)
		{
			switch (state)
			{


				internal_input(inputs);

			case ST_IDLE:
			{

				current_animation = &idle;
				forward.Reset();
				backward.Reset();
				crouch.Reset();
				crouch.Reset();
				kick.Reset();
				punch.Reset();
				sm1.Reset();

				break;
			}
			case ST_WALK_FORWARD:
			{
				current_animation = &forward;
				position.x += speed;
				backward.Reset();
				crouch.Reset();
				crouch.Reset();
				kick.Reset();
				punch.Reset();
				sm1.Reset();

				break;
			}
			case ST_WALK_BACKWARD:
			{
				current_animation = &backward;
				position.x -= speed;
				forward.Reset();
				crouch.Reset();
				crouch.Reset();
				kick.Reset();
				punch.Reset();
				sm1.Reset();

				break;
			}
				//case ST_JUMP_FORWARD:
					//LOG("JUMPING FORWARD ^^>>\n")

				//case ST_JUMP_BACKWARD:
					//LOG("JUMPING BACKWARD ^^<<\n");

			case ST_CROUCH:
			{
				current_animation = &crouch;
				LOG("CROUCHING ****\n");

				break;
			}
				//case ST_PUNCH_CROUCH:
							//LOG("PUNCH CROUCHING **++\n");

				//break;

			case ST_PUNCH_STANDING:
			{
				current_animation = &punch;
				LOG("PUNCH STANDING ++++\n");

				break;
			}
				//case ST_PUNCH_NEUTRAL_JUMP:

						//LOG("PUNCH NEUTRAL JUMP ++++\n");

				//break;

				//case ST_PUNCH_FORWARD_JUMP:

						//LOG("PUNCH JUMP FORWARD ^>>+\n");

				//break;

				//case ST_PUNCH_BACKWARD_JUMP:

						//LOG("PUNCH JUMP BACKWARD ^<<+\n");

				//break;

				//case ST_KICK_CROUCH:

						//LOG("KICK CROUCHING **--\n");

				//break;

			case ST_KICK_STANDING:
			{
				current_animation = &kick;
				break;
			}
				//case ST_KICK_NEUTRAL_JUMP:

						//	LOG("KICK JUMP NEUTRAL ^^--\n");

							//break;
						//case ST_KICK_FORWARD_JUMP:
							//LOG("KICK JUMP FORWARD ^>>-\n");
							//break;
						//case ST_KICK_BACKWARD_JUMP:
							//LOG("KICK JUMP BACKWARD ^<<-\n");
							//break;
						//case ST_DAMAGE_RECEIVED:
							//current_animation = &beat;
							//break;
			case ST_SP1:
			{
				current_animation = &sm1;

			break;
			}
			case ST_JUMP_NEUTRAL:
			{
				if (position.y <= 220)
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
				
			break;
			}

			case ST_LDAMAGE:
			{	/*if ()
				{
				current_animation=&lowd
				}*/
				break;
			}
			case ST_HDAGAME:
			{
				/*if ()
				{
				current_animation=&highd
				}*/
			break;
			}
			}
		}

		playercol->SetPos(position.x, position.y);
		playerpunch->SetPos(position.x + 40, position.y - 90);
		playerkick->SetPos(position.x + 40, position.y - 60);

		current_state = state;

		SDL_Rect r = current_animation->GetCurrentFrame();

		App->render->Blit(graphics, position.x, position.y - r.h, &r);

		playercol->SetPos(position.x, position.y);
		playerpunch->SetPos(position.x + 40, position.y - 90);
		playerkick->SetPos(position.x + 40, position.y - 60);



		return UPDATE_CONTINUE;

	}

}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {



	if ( playercol == c1 && c2->type == COLLIDER_ENEMY && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->enemy->position.y == position.y && position.x < App->enemy->position.x)
	{
		App->enemy->position.x += 3;

	}

	if ( playercol == c1 && c2->type == COLLIDER_ENEMY && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->enemy->position.y == position.y && position.x > App->enemy->position.x)
	{
		App->enemy->position.x -= 3;

	}

	if (playerpunch == c1 && c2->type == COLLIDER_ENEMY)
	{
		if (playerpunch->callback!=nullptr)
		{
			playerpunch->to_delete = true;
		}
		App->enemy->position.x += 3; 
			App->enemy->life -= 25;


	}

	if (playerkick == c1 && c2->type == COLLIDER_ENEMY )
	{
		if (playerkick->callback != nullptr)
		{
			playerkick->to_delete = true;
		}
		App->enemy->life -= 25;
		App->enemy->position.x += 3;


	}

	else if (playercol == c1 && c2->type == COLLIDER_WALL)
	{
		position.x = 15;
	}

}

bool ModulePlayer::external_input(p2Qeue<player_inputs>& inputs)
{
	static bool backward = false;
	static bool forward = false;
	static bool crouch = false;
	static bool jump = false;

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

			case SDLK_s:
				inputs.Push(IN_CROUCH_UP);
				playercol->to_delete = true;
				playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_PLAYER, this);
				crouch = false;
				break;

			case SDLK_w:
				jump = false;
				break;

			case SDLK_a:
				inputs.Push(IN_LEFT_UP);
				backward = false;
				break;

			case SDLK_d:
				inputs.Push(IN_RIGHT_UP);
				forward = false;
				break;

			case SDLK_t:
				break;

			case SDLK_y:
				break;

			case SDLK_f:
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{

			case SDLK_w:
				
				if (animdone == true)
				{
					jump = true;
				}
				//App->audio->PlayFX(AUDIOSALTO);

			break;

			case SDLK_s:
				playercol->to_delete = true;
				playercol = App->collision->AddCollider({ 50, -70, 45, -70 }, COLLIDER_PLAYER, this);
				crouch = true;

			break;

			case SDLK_a:

				backward = true;

			break;

			case SDLK_d:

				forward = true;

			break;

			case SDLK_t:

				inputs.Push(IN_PUNCH);
				if (colcreated == true)
				{
					playerpunch = App->collision->AddCollider({ 10, 30, 55, 10 }, COLLIDER_PLAYER_SHOT, this);
					colcreated = false;
				}
				App->audio->PlayFX(Punch);

			break;

			case SDLK_y:

				if (colcreated == true)
				{
					playerkick = App->collision->AddCollider({ 10, 30, 75, 10 }, COLLIDER_PLAYER_SHOT, this);
					colcreated = false;
				}
				inputs.Push(IN_KICK);
				App->audio->PlayFX(Kick);

			break;

			case SDLK_f:

				if (Activesm1 == true) {

					App->particles->AddParticle(App->particles->terryspecial1, position.x + 48, position.y - 42, COLLIDER_PLAYER_SHOT, 0);
					App->particles->AddParticle(App->particles->terryspecial2, position.x + 35, position.y - 70, COLLIDER_PLAYER_SHOT, 50);
					App->particles->AddParticle(App->particles->terryspecial3, position.x + 18, position.y - 99, COLLIDER_PLAYER_SHOT, 200);
					App->particles->AddParticle(App->particles->terryspecial4, position.x + 5, position.y - 70, COLLIDER_PLAYER_SHOT, 400);
					App->particles->AddParticle(App->particles->terryspecial5, position.x - 13, position.y - 42, COLLIDER_PLAYER_SHOT, 600);
					Activesm1 = false;
				}

				App->audio->PlayFX(Specialattack);

				inputs.Push(IN_SM1);

			break;
			}

		}

	}

	if (backward && forward)
		inputs.Push(IN_LEFT_AND_RIGHT);

	{
		if (backward)
			inputs.Push(IN_LEFT_DOWN);
		if (forward)
			inputs.Push(IN_RIGHT_DOWN);
	}

	if (jump && crouch)
		inputs.Push(IN_JUMP_AND_CROUCH);

	else
	{
		if (crouch)
			inputs.Push(IN_CROUCH_DOWN);
		if (jump)
			inputs.Push(IN_JUMP);
	}



	return true;
}

void ModulePlayer::internal_input(p2Qeue<player_inputs>& inputs)
{
	
		if (jump_timer > 0)
		{

			if (SDL_GetTicks() - jump_timer > JUMP_TIME && position.y == 220)
			{
				inputs.Push(IN_JUMP_FINISH);
				jump_timer = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}
			

		}
	
	

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME)
		{
			playerpunch->to_delete = true;
			colcreated = true;
			inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;

		}
	}

	if (kick_timer > 0)
	{
		if (SDL_GetTicks() - kick_timer > KICK_TIME)
		{
			colcreated = true;
			playerkick->to_delete = true;
			inputs.Push(IN_KICK_FINISH);
			kick_timer = 0;
		}
	}

	if (sp1_timer > 0)
	{
		if (SDL_GetTicks() - sp1_timer > SP1_TIME)
		{
			inputs.Push(IN_SP1_FINISH);
			sp1_timer = 0;
			
		}
		if (SDL_GetTicks() - sp1_timer > SP1_TIME + 500)
		{
			Activesm1 = true;

		}
		if (SDL_GetTicks() - sp1_timer > SP1_TIME+2000)
		{
			App->particles->cont = 0;
			
		}
	}

	if (ldamage_timer > 0)
	{
		if (SDL_GetTicks() - ldamage_timer > LDAMAGE_TIME)
		{
			inputs.Push(IN_LDAMAGE_FINISH);
			ldamage_timer = 0;

		}
		
	}

	if (hdamage_timer > 0)
	{
		if (SDL_GetTicks() - hdamage_timer > HDAMAGE_TIME)
		{
			inputs.Push(IN_HDAMAGE_FINISH);
			hdamage_timer = 0;

		}

	}
}

bool ModulePlayer::CleanUp()
{
	SDL_DestroyTexture(graphics);
	App->enemy->Disable();
	LOG("Unloading Terry From Scene");

	return true;
}