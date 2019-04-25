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


#include "ModulePlayerSelection.h"
#include "ModuleScenePaoPao.h"
#include "ModuleSceneSoundBeach.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleP2Wins.h"
#include "ModuleFFIntro.h"
#include "ModuleWelcomeScreen.h"


ModuleP2Wins::ModuleP2Wins()
{

	//WinP1 Background
	background.x = 0;
	background.y = 0;
	background.w = 290;
	background.h = 225;
}

ModuleP2Wins::~ModuleP2Wins()
{}

// Load assets
bool ModuleP2Wins::Start()
{
	music = App->audio->LoadMusic("Source/Sound/Music/winner.ogg");
	//fx = App->audio->LoadFX("Source/Sound/FX/FX/FX_audience.wav");
	//Mix_VolumeChunk(fx, 35);

	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Source/UI/WinLose/Background2.png");



	//Enabling audio
	App->audio->PlayMusic(music);
	//App->audio->PlayFX(fx); //Fix: Loop infinite(maybe convert to ogg and play as audio)

	return ret;
}

bool ModuleP2Wins::CleanUp()
{

	SDL_DestroyTexture(graphics);



	return true;
}

// Update: draw background
update_status ModuleP2Wins::Update()
{
	// Drawing background - WinP1 Background
	uint cont = SDL_GetTicks();
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	if (cont = SDL_GetTicks() + 500)
	{
		App->fade->FadeToBlack(App->p2w, App->scene_intro, 3);
	}
	return UPDATE_CONTINUE;
}