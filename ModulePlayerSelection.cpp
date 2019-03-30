#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"


//Scenes that we are going to need
#include "ModuleScenePaoPao.h"
#include "ModulePlayerSelection.h"


ModulePlayerSelection::ModulePlayerSelection()
{

	//Pao Pao Background
	background.x = 0;
	background.y = 0;
	background.w = 619;
	background.h = 224;


	//Background Animation
	people.PushBack({ 0, 224, 619, 224 });
	people.PushBack({ 0,448,619,224 });
	people.speed = 0.09f;
}

ModulePlayerSelection::~ModulePlayerSelection()
{}

// Loading assets
bool ModulePlayerSelection::Start()
{
	LOG("Loading assets");
	bool ret = true;
	//Loading Map Assets Texture
	graphics = App->textures->Load("Source/UI/Player_Map_Selection/SpriteSheet_PlayerSelection.png"); 
	return ret;
}

bool ModulePlayerSelection::CleanUp()
{
	LOG("Nothing to cleanup");	//Just destroy textures and see memory leaks
	return true;
}

update_status ModulePlayerSelection::Update()
{
	// Drawing background
	App->render->Blit(graphics, 0, 0, &background, 0.75f);

	//People animation
	App->render->Blit(graphics, 0, 0, &(people.GetCurrentFrame()), 0.75f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->playerselection, App->scene_paopao, 2.5);
	}

	return UPDATE_CONTINUE;
}