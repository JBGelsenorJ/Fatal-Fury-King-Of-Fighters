#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include "ModuleMusic.h"
#include "Application.h"



#include "ModuleFFIntro.h"
#include "ModuleFFIntro2.h"
#include "ModulePlayerSelection.h"
#include "ModuleWelcomeScreen.h"


ModuleFFIntro2::ModuleFFIntro2()
{

	//Intro Background2

	introwin2.x = 7;
	introwin2.y = 195;
	introwin2.w = 463;
	introwin2.h = 241;

	//Taxi

	/*positiontaxi.x = 290;
	positiontaxi.y = 244; */

	taxi.x = 482;
	taxi.y = 322;
	taxi.w = 334;
	taxi.h = 117;

	//Player2 Animation

	/*positionplayer2.x = 290;
	positionplayer2.y = 244; */

	player2.PushBack({ 929, 323, 61, 66 });
	player2.PushBack({ 840, 323, 69, 114 });
	player2.speed = 0.04f;

	//Borders

	borders.x = 0;
	borders.y = 446;
	borders.w = 304;
	borders.h = 225;

}

ModuleFFIntro2::~ModuleFFIntro2()
{}

// Load assets
bool ModuleFFIntro2::Start()
{
	LOG("Loading image assets");
	bool ret = true;
	graphics = App->textures->Load("Source/UI/Intro/intro2.png");
	introsong = App->audio->LoadMusic("Source/Sound/Music/Opening.ogg");
	App->audio->PlayMusic(introsong);
	return ret;

}

bool ModuleFFIntro2::CleanUp()
{
	SDL_DestroyTexture(graphics);
	return true;
}

// Update: draw background
update_status ModuleFFIntro2::Update()
{
	
	//Parte2
	
	// Drawing background - Intro Background2
	
	App->render->Blit(graphics, 0, 16, &introwin2, 0.75f);

	//Start animation

	App->render->Blit(graphics, 72, 120, &(start.GetCurrentFrame()), 0.75f);

	// Player2 animation

	App->render->Blit(graphics, 400, 150, &(player2.GetCurrentFrame()), 0.75f);

	// Taxi animation

	App->render->Blit(graphics, 400, 150, &taxi, 0.75f);

	// Drawing borders - Intro broders

	App->render->Blit(graphics, 0, 1, &borders, 0.75f);
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

		App->fade->FadeToBlack(App->scene_intro2, App->scene_welcome, 1.5);

	}

	return UPDATE_CONTINUE;
}