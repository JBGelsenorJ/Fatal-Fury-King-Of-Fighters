#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include "ModuleMusic.h"


#include "ModulePlayerSelection.h"
#include "ModuleScenePaoPao.h"
#include "ModuleSceneSoundBeach.h"
#include "ModuleWelcomeScreen.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScenePaoPao::ModuleScenePaoPao()
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

ModuleScenePaoPao::~ModuleScenePaoPao()
{}

// Load assets
bool ModuleScenePaoPao::Start()
{
	music = App->audio->LoadMusic("Source/Sound/Music/paopao.ogg");
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Source/Sprites/Stage_Sprites/PaoPao_Cafe/Background.png");
	App->player->Enable();


	App->audio->PlayMusic(music);
	
	return ret;
}

bool ModuleScenePaoPao::CleanUp()
{
	App->player->Disable();
	SDL_DestroyTexture(graphics);
	LOG("Unloading Terry From Scene");
	

	return true;
}

// Update: draw background
update_status ModuleScenePaoPao::Update()
{
	// Drawing background - Pao Pao Background
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	
	//People animation
	App->render->Blit(graphics, 0, 0, &(people.GetCurrentFrame()), 0.75f ); 

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_paopao, App->scene_soundbeach, 2.5);

	}

	return UPDATE_CONTINUE;
}