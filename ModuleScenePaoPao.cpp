#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include "ModuleMusic.h"
#include "ModuleCollision.h"
#include "ModuleEnemy.h"
#include <stdio.h>


#include "ModulePlayerSelection.h"
#include "ModuleScenePaoPao.h"
#include "ModuleSceneSoundBeach.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleFFIntro.h"
#include "ModuleP1Wins.h"
#include "ModuleFonts.h"


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
	fx = App->audio->LoadFX("Source/Sound/FX/FX/FX_audience.wav");
	Mix_VolumeChunk(fx, 35);

	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Source/Sprites/Stage_Sprites/PaoPao_Cafe/Background.png");
	
	//Enabling game features
	App->player->Enable();
	App->enemy->Enable();
	App->particles->Enable();
	App->collision->Enable();

	//Enabling audio
	App->audio->PlayMusic(music);
	App->audio->PlayFX(fx); //Fix: Loop infinite(maybe convert to ogg and play as audio)

	countdown = App->fonts->Load("Source/UI/fonts/marcador.png", "0123456789", 1);
	time = 90;
	
	return ret;
}

bool ModuleScenePaoPao::CleanUp()
{
	App->player->Disable();
	App->enemy->Disable();
	App->collision->Disable();
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


	//Time
	if (starting <= SDL_GetTicks() - 1000 && time > 0) {
		++time;
		time = SDL_GetTicks();
	}

	sprintf_s(time_text, 10, "%2d", time);
	App->fonts->BlitText(177, 40, countdown, time_text);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_paopao, App->p1w, 1.5);

	}

	return UPDATE_CONTINUE;
}