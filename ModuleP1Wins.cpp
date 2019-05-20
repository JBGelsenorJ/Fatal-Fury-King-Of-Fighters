#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include "ModuleMusic.h"
#include "ModuleCollision.h"
#include "ModuleEnemy2.h"


#include "ModulePlayerSelection.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleP1Wins.h"
#include "ModuleP2Wins.h"
#include "ModuleFFIntro.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleFonts.h"
#include "ModuleSceneBillyKane.h"


ModuleP1Wins::ModuleP1Wins()
{

	//WinP1 Background
	background.x = 0;
	background.y = 0;
	background.w = 290;
	background.h = 225;
}

ModuleP1Wins::~ModuleP1Wins()
{}

bool ModuleP1Wins::Start()
{
	bool ret = true;

	//Texture Loaded
	graphics = App->textures->Load("Source/UI/WinLose/Background.png");

	//Loading Music
	music = App->audio->LoadMusic("Source/Sound/Music/winner.ogg");

	//Enabling audio
	App->audio->PlayMusic(music);


	LOG("Loading assets");

	App->player2->rounds = 0;
	App->enemy2->rounds = 0;

	return ret;
}

bool ModuleP1Wins::CleanUp()
{
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleP1Wins::Update()
{
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// Drawing background - WinP1 Background
	uint cont = SDL_GetTicks();
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	

	if (cont = SDL_GetTicks()+1100)
	{
		App->fade->FadeToBlack(App->p1w, App->scene_welcome, 1);
	}
	return UPDATE_CONTINUE;
}