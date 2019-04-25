#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL\include\SDL.h"
#include "ModuleTime.h"
#include "ModuleFonts.h"

ModuleTime::ModuleTime()
{
	position_mark.x = 100;
	position_mark.y = 50;

	position_decs.x = 100;
	position_decs.y = 50;

	position_units.x = 200;
	position_units.y = 50;

	//marcador decenas
	timer[0].PushBack({ 8, 6, 15, 22 });
	timer[1].PushBack({ 29, 6, 15, 22 });
	timer[2].PushBack({ 50, 6, 15, 22 });
	timer[3].PushBack({ 71, 6, 15, 22 });
	timer[4].PushBack({ 8, 33, 15, 22 });
	timer[5].PushBack({ 29, 33, 15, 22 });
	timer[6].PushBack({ 50, 33, 15, 22 });
	timer[7].PushBack({ 71, 33, 15, 22 });
	timer[8].PushBack({ 8, 60, 15, 22 });
	timer[9].PushBack({ 29, 60, 15, 22 });
	

	//fondo marcador
	mark.PushBack({ 54, 59, 32, 24 });


}

ModuleTime::~ModuleTime()
{}

// Load assets
bool ModuleTime::Start()
{
	LOG("Loading player textures");
	bool ret = true;

	//Loading SpriteSheet
	countdown = App->textures->Load("Source/UI/fonts/marcador.png");

	return ret;
}

// Update: draw background
update_status ModuleTime::Update()
{
	Animation* current_animation = &mark;

	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(countdown, position_mark.x, position_mark.y - r.h, &r);

	for (int i = 9; i < 0; i--)
	{
		for (int j = 9; j < 0; j--)
		{
			Animation* current_animation = &timer[j];

			SDL_Rect r = current_animation->GetCurrentFrame();

			App->render->Blit(countdown, position_units.x, position_units.y - r.h, &r);
		}

		Animation* current_animation = &timer[i];

		SDL_Rect r = current_animation->GetCurrentFrame();

		App->render->Blit(countdown, position_decs.x, position_decs.y - r.h, &r);

	}


	return UPDATE_CONTINUE;
}

bool ModuleTime::CleanUp()
{
	SDL_DestroyTexture(countdown);

	LOG("Unloading Terry From Scene");

	return true;
}