#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({27, 914, 58, 103});
	idle.PushBack({95, 916, 59, 102});
	idle.PushBack({165, 917, 58, 101});
	idle.PushBack({ 95, 916, 59, 102 });

	idle.speed = 0.18f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({32, 1300, 60, 105});
	forward.PushBack({108, 1300, 68, 105});
	forward.PushBack({189, 1300, 68, 105});
	forward.PushBack({263, 1300, 68, 105});
	forward.speed = 0.15f;
	//backward
	backward.PushBack({ 263, 1300, 57, 104 });
	backward.PushBack({ 453, 1300, 57, 110 });
	backward.PushBack({ 453, 1300, 57, 110 });
	backward.PushBack({ 107, 1297, 71, 107 });
	backward.PushBack({ 95, 916, 59, 102 });
	backward.speed = 0.15f;

	// TODO 4: Make ryu walk backwards with the correct animations
	jump.PushBack({ 78, 131, 60, 88 });
	jump.PushBack({ 162, 128, 64, 92 });
	jump.PushBack({ 259, 128, 63, 90 });
	jump.PushBack({ 352, 128, 54, 91 });
	jump.PushBack({ 432, 131, 50, 89 });
	jump.speed = 0.5f;

	// kick animation 
	kick.PushBack({ 449, 806, 59, 107 });
	kick.PushBack({ 514, 803, 59, 107 });
	kick.PushBack({ 31, 1150, 59, 107 });
	kick.PushBack({ 85, 1151, 59, 113 });
	kick.PushBack({ 147, 1150, 59, 113 });
	kick.PushBack({ 210, 1155, 128, 113 });
	kick.PushBack({ 343, 1152, 63, 113 });
	kick.PushBack({ 713, 920, 63, 97 });
	kick.speed = 0.2f;

	// punch animation 
	punch.PushBack({ 506, 918, 60, 101 });
	punch.PushBack({ 573, 918, 98, 101 });
	punch.PushBack({ 506, 918, 60, 101 });
	punch.speed = 0.1f;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Source/Sprites/Character_Sprites/Terry_Bogard/terry.png"); // Terry Bogard Sprites
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 2;

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &forward;
		position.x += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &backward;
		position.x -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == 1) {
		current_animation = &jump;
		position.y -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_X] == 1) {
		current_animation = &kick;
		
	}
	bool ban = 0;
	if (App->input->keyboard[SDL_SCANCODE_E] == 1) {

				current_animation = &punch;
		}
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}