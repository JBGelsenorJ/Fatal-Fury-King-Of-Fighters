#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL\include\SDL.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"

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

	//Terry Bogard Jump Animation
	jump.PushBack({ 548, 1035, 51, 125 });
	jump.PushBack({ 611, 1046, 57, 103 });
	jump.PushBack({ 680, 1056, 57, 94 });
	

	jump.speed = 0.08f;

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
	//Loading SpriteSheet
	graphics = App->textures->Load("Source/Sprites/Character_Sprites/Terry_Bogard/terry.png"); // Terry Bogard Sprites
	
	//Loading attack audios
	Kick = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack5.wav");
	Punch = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack4.wav");
	Specialattack = App->audio->LoadFX("Source/Sound/FX/Voice/SpecialAttacks/PoweWave.wav");
	
	//Loading Player Colliders
	player = App->collision->AddCollider({ 10, 0, 58, -103 }, COLLIDER_PLAYER);

	countdown_font = App->fonts->Load("Source/UI/fonts/countdouwn_font.png", "012345678", 1);


	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 2;
	
	//Crouch
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {

		current_animation = &crouch;

		}
		else {
			
			//MoveForward
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && position.x < 670)
			{
				current_animation = &forward;
				position.x += speed;
				

			}

			//Move Backward
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && position.x > 0)
			{
				current_animation = &backward;
				position.x -= speed;
				
			}

			//Jump
			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
				current_animation = &jump;
				//FIX FREEFALL
				if (position.y == 5 && position.y != 0) {
					position.y = 10 - 5 * pow(SDL_GetTicks(), 2);
				}
				else {
					position.y -= speed;
				}
			}

			//Punch
			if (App->input->keyboard[SDL_SCANCODE_T] == KEY_STATE::KEY_REPEAT || (TimePunch == true)) {
				current_animation = &punch;
				TimePunch = true;
				App->audio->PlayFX(Punch);
				if (current_animation->AnimFinished() == true)
				{
					TimePunch = false;
				}
			}

			//Kick
			if (App->input->keyboard[SDL_SCANCODE_Y] == KEY_STATE::KEY_DOWN || (KickAnim == true)) {
				KickAnim = true;
				current_animation = &kick;
				App->audio->PlayFX(Kick);
				if (current_animation->AnimFinished() == true)
				{
					KickAnim = false;
				}
			}

			//Special Move

			if ((App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN) || (TimeAnim == true))
			{
				TimeAnim = true;
				current_animation = &sm1;

				if (current_animation->AnimFinished() == true)
				{
					App->particles->AddParticle(App->particles->terryspecial1, position.x + 48, position.y - 42, COLLIDER_PLAYER_SHOT,0);
					App->particles->AddParticle(App->particles->terryspecial2, position.x + 35, position.y - 70, COLLIDER_PLAYER_SHOT, 50);
					App->particles->AddParticle(App->particles->terryspecial3, position.x + 18, position.y - 99, COLLIDER_PLAYER_SHOT, 200);
					App->particles->AddParticle(App->particles->terryspecial4, position.x + 5, position.y - 70, COLLIDER_PLAYER_SHOT, 400);
					App->particles->AddParticle(App->particles->terryspecial5, position.x - 13, position.y - 42, COLLIDER_PLAYER_SHOT,600);
					TimeAnim = false;
				}
			}

			if ((App->input->keyboard[SDL_SCANCODE_Z] == KEY_STATE::KEY_DOWN) || (Lowdtime == true))
			{
				current_animation = &lowd;
				Lowdtime = true;
				//App->audio->PlayFX(Punch);
				if (current_animation->AnimFinished() == true)
				{
					Lowdtime = false;
				}
			}

			if ((App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN) || (Highdtime == true))
			{
				current_animation = &highd;
				Highdtime = true;
				//App->audio->PlayFX(Punch);
				if (current_animation->AnimFinished() == true)
				{
					Highdtime = false;
				}
			}
			if ((App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN))
			{
				if (godmode == false)
				{
					App->collision->Disable();
					App->collision->Enable();
					player = App->collision->AddCollider({ 10, 0, 58, -103 }, COLLIDER_NONE);
					godmode = true;
				}
				else
				{
					App->collision->Disable();
					App->collision->Enable();
					player = App->collision->AddCollider({ 10, 0, 58, -103 }, COLLIDER_PLAYER);
					godmode = false;
				}
			}
			
		}

	SDL_Rect r = current_animation->GetCurrentFrame();
	player->SetPos(position.x, position.y);
	
	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	App->fonts->BlitText(200, 30, countdown_font, "06");
	return UPDATE_CONTINUE;
}

Uint32 jump_timer = 0;
Uint32 punch_timer = 0;
Uint32 sp1_timer = 0;
Uint32 kick_timer = 0;


bool external_input(p2Qeue<player_inputs>& inputs)
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
				inputs.Push(IN_CROUCH_UP);
				crouch = false;
				break;

			case SDLK_UP:
				inputs.Push(IN_JUMP_UP);
				jump = false;
				break;

			case SDLK_LEFT:
				inputs.Push(IN_LEFT_UP);
				backward = false;
				break;

			case SDLK_RIGHT:
				inputs.Push(IN_RIGHT_UP);
				forward = false;
				break;

			case SDLK_t:
				inputs.Push(IN_PUNCH_UP);
				punch = false;
				break;

			case SDLK_y:
				inputs.Push(IN_KICK_UP);
				kick = false;
				break;

			case SDLK_f:
				inputs.Push(IN_SP1_UP);
				sp1 = false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{

			case SDLK_UP:
				inputs.Push(IN_JUMP_DOWN);
				jump = true;
				break;
			case SDLK_DOWN:
				inputs.Push(IN_CROUCH_DOWN);
				crouch = true;
				break;
			case SDLK_LEFT:
				inputs.Push(IN_LEFT_DOWN);
				backward = true;
				break;
			case SDLK_RIGHT:
				inputs.Push(IN_RIGHT_DOWN);
				forward = true;
				break;

			case SDLK_t:
				inputs.Push(IN_PUNCH_DOWN);
				punch = true;
				break;

			case SDLK_y:
				inputs.Push(IN_KICK_DOWN);
				kick = true;
				break;

			case SDLK_f:
				inputs.Push(IN_SP1_DOWN);
				sp1 = true;
				break;
			}
			
		}
		
	}

	if (backward && forward){
		
		inputs.Push(IN_LEFT_AND_RIGHT);
	}
	else
	{
		if (backward)
			inputs.Push(IN_LEFT_DOWN);
		if (forward)
			inputs.Push(IN_RIGHT_DOWN);
	}

	if (jump && crouch){
		inputs.Push(IN_JUMP_AND_CROUCH);
	}
	else
	{
		if (crouch)
			inputs.Push(IN_CROUCH_DOWN);
		if (jump)
			inputs.Push(IN_JUMP_DOWN);
	}

	if (punch && kick) {
		inputs.Push(IN_PUNCH_AND_KICK);
	}
	else
	{
		if (punch)
			inputs.Push(IN_PUNCH_DOWN);
		if (kick)
			inputs.Push(IN_KICK_DOWN);
	}
	
	if (punch && sp1) {
		inputs.Push(IN_PUNCH_AND_SP1);
	}
	else
	{
		if (punch)
			inputs.Push(IN_PUNCH_DOWN);
		if (sp1)
			inputs.Push(IN_SP1_DOWN);
	}
	
	if (kick && sp1) {
		inputs.Push(IN_KICK_AND_SP1);
	}
	else
	{
		if (kick)
			inputs.Push(IN_KICK_DOWN);
		if (sp1)
			inputs.Push(IN_SP1_DOWN);
	}
	
	if (punch && kick && sp1) {
		inputs.Push(IN_PUNCH_AND_KICK_AND_SP1);
	}
	else
	{
		if (punch)
			inputs.Push(IN_PUNCH_DOWN);
		if (kick)
			inputs.Push(IN_KICK_DOWN);
		if (sp1)
			inputs.Push(IN_SP1_DOWN);

	}
	
	return true;
}

void internal_input(p2Qeue<player_inputs>& inputs)
{
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME)
		{
			inputs.Push(IN_JUMP_FINISH);
			jump_timer = 0;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME)
		{
			inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}

	if (kick_timer > 0)
	{
		if (SDL_GetTicks() - kick_timer > KICK_TIME)
		{
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
	}
}

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
			case IN_JUMP_DOWN: state = ST_JUMP_NEUTRAL; jump_timer = SDL_GetTicks();  break;
			
			case IN_PUNCH_DOWN: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
			case IN_SP1_DOWN: state = ST_SP1_STANDING; sp1_timer = SDL_GetTicks(); break;
			case IN_KICK_DOWN: state = ST_KICK_STANDING; kick_timer = SDL_GetTicks(); break;
			
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

			case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
			case IN_RIGHT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;

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

			}

		}
		break;

		case ST_JUMP_NEUTRAL:
		{
			switch (last_input)
			{
			case IN_JUMP_UP: state = ST_IDLE; break;
			case IN_JUMP_DOWN: state = ST_JUMP_NEUTRAL; jump_timer = SDL_GetTicks(); break;
			case IN_JUMP_AND_CROUCH: state = ST_IDLE; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			
			}
		}
		break;

		case ST_PUNCH_STANDING:
		{
			switch (last_input)
			{
			case IN_PUNCH_UP: state = ST_IDLE; break;
			case IN_PUNCH_DOWN: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks(); break;
			case IN_PUNCH_AND_KICK: state = ST_IDLE; break;
			case IN_PUNCH_AND_KICK_AND_SP1: state = ST_IDLE; break;
			case IN_PUNCH_AND_SP1: state = ST_IDLE; break;
			case IN_PUNCH_FINISH: state = ST_IDLE; break;

			}
		}
		break;

		case ST_KICK_STANDING:
		{

			switch (last_input)
			{

			case IN_KICK_UP: state = ST_IDLE; break;
			case IN_KICK_DOWN: state = ST_KICK_STANDING; kick_timer = SDL_GetTicks(); break;
			case IN_PUNCH_AND_KICK: state = ST_IDLE; break;
			case IN_PUNCH_AND_KICK_AND_SP1: state = ST_IDLE; break;
			case IN_KICK_AND_SP1: state = ST_IDLE; break;
			}
		}
		
		case ST_SP1_STANDING:
		{

			switch (last_input)
			{

			case IN_SP1_UP: state = ST_IDLE; break;
			case IN_SP1_DOWN: state = ST_SP1_STANDING; sp1_timer = SDL_GetTicks(); break;
			case IN_PUNCH_AND_SP1: state = ST_IDLE; break;
			case IN_PUNCH_AND_KICK_AND_SP1: state = ST_IDLE; break;
			case IN_KICK_AND_SP1: state = ST_IDLE; break;
			}
		}
		}
	}

	return state;
}

bool ModulePlayer::CleanUp()
{
	SDL_DestroyTexture(graphics);
	
	LOG("Unloading Terry From Scene");

	return true;
}