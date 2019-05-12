#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneBillyKane.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include "ModuleMusic.h"
#include "ModuleCollision.h"
#include "ModuleEnemy2.h"
#include <stdio.h>


#include "ModulePlayerSelection.h"
#include "ModuleSceneSoundBeach.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleFFIntro.h"
#include "ModuleP1Wins.h"
#include "ModuleP2Wins.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"


ModuleBillyKane::ModuleBillyKane()
{

	//Background

	//sea.PushBack({ 51,567,620,237 });
	sea.PushBack({ 51,822,620,237 });
	sea.PushBack({ 51,1071,620,237 });
	sea.PushBack({ 51,1319,620,237 });
	sea.speed = 0.09f;

	//purple people animation
	people1.PushBack({ 72, 50, 65, 99 });
	people1.PushBack({ 161,50,65,97 });
	people1.speed = 0.09f;
	// fat and thin people
	people2.PushBack({ 70, 408, 68, 99 });
	people2.PushBack({ 164,408,62,105 });
	people2.speed = 0.09f;

	//blonde people
	people3.PushBack({ 60, 272, 61, 95 });
	people3.PushBack({ 151,274,62,100 });
	people3.speed = 0.09f;

}

ModuleBillyKane::~ModuleBillyKane()
{}

// Load assets
bool ModuleBillyKane::Start()
{
	music = App->audio->LoadMusic("Source/Sound/Music/billy.ogg");
	audience = App->audio->LoadFX("Source/Sound/FX/FX/FX_audience.wav");

	Restart();
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Source/Sprites/Stage_Sprites/Billy_Kane_map/Background.png");
	
	//Enabling game features
	App->particles->Enable();
	App->input->Enable();
	App->collision->Enable();
	App->enemy2->Enable();
	App->player2->Enable();
	App->ui->Enable();

	//Enabling audio
	App->audio->PlayMusic(music);
	Mix_PlayChannel(-1 , audience, -1);
	Mix_VolumeChunk(audience, 35);

	wall1 = App->collision->AddCollider({ -200, 300, 15, -500 }, COLLIDER_WALL, this);
	wall2 = App->collision->AddCollider({ 500, 300 , 15, -500 }, COLLIDER_WALL, this);

	return ret;
}

bool ModuleBillyKane::CleanUp()
{
	App->player2->Disable();
	App->enemy2->Disable();
	App->particles->Disable();
	App->collision->Disable();
	SDL_DestroyTexture(graphics);
	LOG("Unloading all Features from Scene");
	

	return true;
}

void ModuleBillyKane::Restart() {
	
	//Restart Player values
	App->player->life = 100;
	App->player->position.x = 100;
	App->player->position.y = 220;
	//Restart enemy values
	App->enemy2->life= 100;
	App->enemy2->position.x = 200;
	App->enemy2->position.y = 220;
	//Restart time
	App->ui->time = 90000;
	App->ui->starttime = SDL_GetTicks();
}


// Update: draw background
update_status ModuleBillyKane::Update()
{
	//background
	App->render->Blit(graphics, -115, 0, &(sea.GetCurrentFrame()), 1.4f);
	//People animation
	App->render->Blit(graphics, 250, 115, &(people1.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, 187, 115, &(people2.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, -108, 115, &(people3.GetCurrentFrame()), 1.4f);


	App->ui->Timer(129,5);
	App->ui->DrawLife();

	if (App->input->keyboard[SDL_SCANCODE_T] == 1) {
		//App->audio->PlayFX(App->player->Kick);
	}

	float centerx = (App->player->position.x + App->enemy2->position.x) / 2;
	float centery = (App->player->position.y + App->enemy2->position.y) / 2; 

	//camera locked
	/*App->render->cam_pos.x = -centerx;
	App->render->cam_pos.y = (SCREEN_HEIGHT)-centery;
	App->render->camera.x = App->render->cam_pos.x;
	App->render->camera.y = App->render->cam_pos.y;*/
	

	//Scene Out
	if (App->player->life <= 0)
	{
		App->fade->FadeToBlack(App->scene_billykane, App->p2w, 1.5);

	}
	else if (App->enemy2->life <= 0)
	{
		App->fade->FadeToBlack(App->scene_billykane, App->p1w, 1.5);

	}
	else if (App->ui->time <= 0 && App->player->life > App->enemy2->life || App->ui->time >= 200000 && App->player->life > App->enemy2->life)
	{
		App->fade->FadeToBlack(App->scene_billykane, App->p1w, 1.5);

	}
	else if (App->ui->time <= 0 && App->player->life < App->enemy2->life || App->ui->time >= 200000 && App->player->life < App->enemy2->life)
	{
		App->fade->FadeToBlack(App->scene_billykane, App->p2w, 1.5);
	}
	return UPDATE_CONTINUE;
}