#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include "ModuleMusic.h"
#include "ModuleEnemy.h"
#include "ModuleCollision.h"


#include "ModulePlayerSelection.h"
#include "ModuleSceneSoundBeach.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include "ModuleMusic.h"


#include "ModuleScenePaoPao.h"
#include "ModuleSceneSoundBeach.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleP1Wins.h"
#include "ModuleFFIntro.h"


ModuleSceneSoundBeach::ModuleSceneSoundBeach()
{

	//SoundBeach Background
	background.x = 0;
	background.y = 0;
	background.w = 619;
	background.h = 224;

}

ModuleSceneSoundBeach::~ModuleSceneSoundBeach()
{}

// Load assets
bool ModuleSceneSoundBeach::Start()
{
	App->enemy->Enable();
	App->collision->Enable();
	music = App->audio->LoadMusic("Source/Sound/Music/SoundBeach.ogg");
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Source/Sprites/Stage_Sprites/Sound_Beach/Day/Background.png");
	App->player->Enable();


	App->audio->PlayMusic(music);
	
	return ret;
}

bool ModuleSceneSoundBeach::CleanUp()
{
	App->player->Disable();
	App->enemy->Disable();
	App->collision->Disable();
	SDL_DestroyTexture(graphics);
	LOG("Unloading Terry From Scene");
	

	return true;
}

// Update: draw background
update_status ModuleSceneSoundBeach::Update()
{
	// Drawing background - SoundBeach Background
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_soundbeach, App->p1w, 1.5);

	}

	return UPDATE_CONTINUE;
}