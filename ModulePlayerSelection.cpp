#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include "ModuleMusic.h"


//Scenes that we are going to need
#include "ModuleScenePaoPao.h"
#include "ModulePlayerSelection.h"
#include "ModuleFFIntro.h"


ModulePlayerSelection::ModulePlayerSelection()
{

	//Pao Pao Background
	background.x = 4;
	background.y = 4;
	background.w = 288;
	background.h = 224;
	
	//Player Selection Title
	title.x = 576;
	title.y = 130;
	title.w = 120;
	title.h = 17;

	//PlayerNumber pointer
	player.x = 580;
	player.y = 170;
	player.w = 50;
	player.h = 17;


	//Characters Locked
	charlocked.x = 243;
	charlocked.y = 232;
	charlocked.w = 225;
	charlocked.h = 133;

	


	//Hover Terry Bogard
	hoverterry.PushBack({ 573, 237, 71, 128 });
	hoverterry.PushBack({ 95, 374, 71, 128 });
	hoverterry.speed = 0.07f;

	//Hover Joe Higashi
	hoverjoe.PushBack({482 , 231, 76 , 134});
	hoverjoe.PushBack({ 4 , 368 , 76 , 134 });
	hoverjoe.speed = 0.07f;
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
	song = App->audio->LoadMusic("Source/Sound/Music/CharacterSelection.ogg");
	App->audio->PlayMusic(song);

	return ret;
}

bool ModulePlayerSelection::CleanUp()
{
	SDL_DestroyTexture(graphics);
	LOG("Nothing to cleanup");	//Just destroy textures and see memory leaks
	return true;
}

update_status ModulePlayerSelection::Update()
{
	//Background Rendered
	App->render->Blit(graphics, 0, 0, &background, NULL);
	App->render->Blit(graphics, 80, 40, &title, NULL);
	App->render->Blit(graphics, 20, 71, &charlocked, NULL);
	


	//Terry Hover animation: default
		if (terryhover == 0) {
			App->render->Blit(graphics, 111, 76, &(hoverterry.GetCurrentFrame()), NULL);
			App->render->Blit(graphics, 119, 58, &player, NULL);
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == 1 || joehover == 1 ) {
			terryhover = true;	//Desactivating Terry's Default Animation
			joehover = true;	//Activating Joe's Animation
			App->render->Blit(graphics, 20, 70, &(hoverjoe.GetCurrentFrame()), NULL);
			App->render->Blit(graphics, 45, 55, &player, NULL);
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == 1) {
			terryhover = true;
		}


	//If enter
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->playerselection, App->scene_paopao, 2.5);
	}

	return UPDATE_CONTINUE;
}