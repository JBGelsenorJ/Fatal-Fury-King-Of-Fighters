#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include "ModuleMusic.h"
#include"ModuleSceneBillyKane.h"


#include "ModuleNeogeo.h"
#include "ModulePlayerSelection.h"
#include "ModuleWelcomeScreen.h"



ModuleNeogeo::ModuleNeogeo()
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			neogeo.PushBack({ (320 * j), (224 * i), 320, 224 });
		}
	}

	neogeo.speed = 0.25f;
	neogeo.loop = false;
	


}

ModuleNeogeo::~ModuleNeogeo()
{}

// Load assets
bool ModuleNeogeo::Start()
{
	LOG("Loading image assets");
	bool ret = true;
	graphics = App->textures->Load("Source/UI/Intro/neogeo.png");
	song = App->audio->LoadMusic("Source/Sound/Music/Opening.ogg");
	App->audio->PlayMusic(song);
	return ret;


}

bool ModuleNeogeo::CleanUp()
{
	SDL_DestroyTexture(graphics);
	return true;
}

// Update: draw background
update_status ModuleNeogeo::Update()
{
	App->render->Blit(graphics, 0, 0, &(neogeo.GetCurrentFrame()), 0.0f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_neogeo, App->scene_welcome, 1.5);

	}

	if (SDL_GameControllerGetButton(App->input->gamepad2, SDL_CONTROLLER_BUTTON_START) == 1)
	{
		App->fade->FadeToBlack(App->scene_neogeo, App->scene_welcome, 1.5);
	}
	if (SDL_GameControllerGetButton(App->input->gamepad1, SDL_CONTROLLER_BUTTON_START) == 1)
	{
		App->fade->FadeToBlack(App->scene_neogeo, App->scene_welcome, 1.5);
	}

	return UPDATE_CONTINUE;
}