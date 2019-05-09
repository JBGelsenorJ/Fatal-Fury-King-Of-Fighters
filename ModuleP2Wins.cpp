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
#include "ModuleSceneBillyKane.h"


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
	bool ret = true;

	//Loading Music
	music = App->audio->LoadMusic("Source/Sound/Music/winner.ogg");
	
	//Loading Textures
	graphics = App->textures->Load("Source/UI/WinLose/Background2.png");

	//Enabling audio
	App->audio->PlayMusic(music);

	LOG("Loading assets");
	return ret;
}

bool ModuleP2Wins::CleanUp()
{
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleP2Wins::Update()
{

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// Drawing background - WinP1 Background
	uint cont = SDL_GetTicks();
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	if (cont = SDL_GetTicks() + 500)
	{
		App->fade->FadeToBlack(App->p2w, App->scene_billykane, 3);
	}
	return UPDATE_CONTINUE;
}