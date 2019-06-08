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

	neo.x = 0;
	neo.y = 0;
	neo.w = 304;
	neo.h = 224;

	//neogeo
	neogeo.PushBack({ 0, 0, 305, 225 });
	neogeo.PushBack({ 317, 0, 305, 225 });
	neogeo.PushBack({ 633, 0, 305, 225 });
	neogeo.PushBack({ 950, 0, 305, 225 });
	neogeo.PushBack({ 0, 242, 305, 225 });
	neogeo.PushBack({ 317, 242, 305, 225 });
	neogeo.PushBack({ 633, 242, 305, 225 });
	neogeo.PushBack({ 950, 242, 305, 225 });
	neogeo.PushBack({ 0, 491, 305, 225 });
	neogeo.PushBack({ 317, 491, 305, 225 });
	neogeo.PushBack({ 633, 491, 305, 225 });
	neogeo.PushBack({ 950, 491, 305, 225 });
	neogeo.PushBack({ 0, 732, 305, 225 });
	neogeo.PushBack({ 317, 732, 305, 225 });
	neogeo.PushBack({ 633, 732, 305, 225 });
	neogeo.PushBack({ 950, 732, 305, 225 });
	neogeo.PushBack({ 0, 976, 305, 225 });
	neogeo.PushBack({ 317, 976, 305, 225 });
	neogeo.PushBack({ 633, 976, 305, 225 });
	neogeo.PushBack({ 950, 976, 305, 225 });
	neogeo.PushBack({ 0, 1225, 305, 225 });
	neogeo.PushBack({ 317, 1225, 305, 225 });
	neogeo.PushBack({ 633, 1225, 305, 225 });
	neogeo.PushBack({ 950, 1225, 305, 225 });
	neogeo.speed = 0.15f;

	//neogeo last frame
	last.PushBack({ 950, 1225, 305, 225 });

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

	/*posx1 = 93;
	posx2 = 87;
	posx3 = 110;*/

	time_start = SDL_GetTicks();

}

bool ModuleNeogeo::CleanUp()
{
	SDL_DestroyTexture(graphics);
	return true;
}

// Update: draw background
update_status ModuleNeogeo::Update()
{
	// Drawing neogeo Background
	App->render->Blit(graphics, 0, 0, &neo, NULL);

	// text under the rects
	if (anim_done == false)
	{
		current_animation = &neogeo;

		App->render->Blit(graphics, 0, 0, &(neogeo.GetCurrentFrame()), NULL);
	}
	
	// text animation
	/*App->render->Blit(graphics, 93, 110, &(rect1.GetCurrentFrame()), NULL);
	App->render->Blit(graphics, 87, 128, &(rect2.GetCurrentFrame()), NULL);
	App->render->Blit(graphics, 110, 160, &(rect3.GetCurrentFrame()), NULL);*/

	/*if ((time_start - SDL_GetTicks()) >= LIMIT_TIME)
	{
		App->render->Blit(graphics, 0, 0, &(last.GetCurrentFrame()), NULL);
	}*/

	if (current_animation->AnimFinished() == true)
	{
		anim_done = true;
		App->render->Blit(graphics, 0, 0, &(last.GetCurrentFrame()), NULL);
	}



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