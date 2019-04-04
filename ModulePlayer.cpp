#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL\include\SDL.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"


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
	
	sm1.PushBack({ 193, 687, 54, 107 });
	sm1.PushBack({ 264, 681, 56, 113 });
	sm1.PushBack({ 323, 698, 62, 96 });
	sm1.PushBack({ 387, 718, 80, 77 });
	sm1.PushBack({ 471, 717, 69, 77 });
	sm1.PushBack({ 540, 726, 67, 69 });
	sm1.speed = 0.18f;
	

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Source/Sprites/Character_Sprites/Terry_Bogard/terry.png"); // Terry Bogard Sprites
	Kick = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack5.wav");
	Punch = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack4.wav");
	Specialattack = App->audio->LoadFX("Source/Sound/FX/Voice/SpecialAttacks/PoweWave.wav");

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
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
			{
				current_animation = &forward;
				position.x += speed;
			}

			//Move Backward
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
			{
				current_animation = &backward;
				position.x -= speed;
			}

			//Jump
			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
				current_animation = &jump;
				position.y -= speed;

			}

			//Punch
			if (App->input->keyboard[SDL_SCANCODE_T]) {

				current_animation = &punch;
				App->audio->PlayFX(Punch);
			}

			//Kick
			if (App->input->keyboard[SDL_SCANCODE_Y]) {
				current_animation = &kick;
				App->audio->PlayFX(Kick);
			}

			//Special Move
			if (App->input->keyboard[SDL_SCANCODE_F]== KEY_STATE::KEY_UP)
			{
				App->particles->AddParticle(App->particles->terryspecial1, position.x + 48, position.y - 42, 0);
				App->particles->AddParticle(App->particles->terryspecial2, position.x + 35, position.y - 70, 50);
				App->particles->AddParticle(App->particles->terryspecial3, position.x + 18, position.y - 99, 200);
				App->particles->AddParticle(App->particles->terryspecial4, position.x + 5, position.y - 70, 400);
				App->particles->AddParticle(App->particles->terryspecial5, position.x - 13, position.y - 42, 600);
				current_animation = &sm1;

			}
		}

	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	SDL_DestroyTexture(graphics);
	LOG("Unloading Terry From Scene");

	return true;
}
