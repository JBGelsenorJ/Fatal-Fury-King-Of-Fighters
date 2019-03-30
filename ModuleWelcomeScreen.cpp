#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"

#include "ModuleWelcomeScreen.h"
#include "ModulePlayerSelection.h"
#include "ModuleScenePaoPao.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleWelcomeScreen::ModuleWelcomeScreen()
{

	//Pao Pao Background
	welcome.x = 0;
	welcome.y = 0;
	welcome.w = 619;
	welcome.h = 224;


	//Background Animation
	logo.PushBack({ 11, 273, 235, 120 });
	logo.PushBack({ 256, 273, 235, 120 });
	logo.PushBack({ 501, 273, 235, 120 });
	logo.speed = 0.04f;
}

ModuleWelcomeScreen::~ModuleWelcomeScreen()
{}

// Load assets
bool ModuleWelcomeScreen::Start()
{
	LOG("Loading image assets");
	bool ret = true;
	graphics = App->textures->Load("Source/UI/Intro/intro.png");
	return ret;
}

bool ModuleWelcomeScreen::CleanUp()
{

	return true;
}

// Update: draw background
update_status ModuleWelcomeScreen::Update()
{
	// Drawing background - Pao Pao Background
	App->render->Blit(graphics, 0, 0, &welcome, 0.75f);

	//Logo animation
	App->render->Blit(graphics, 25, 30, &(logo.GetCurrentFrame()), 0.75f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_welcome, App->playerselection, 2.5);

	}

	return UPDATE_CONTINUE;
}