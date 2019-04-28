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
#include "ModuleP2Wins.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"


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
	audience = App->audio->LoadMusic("Source/Sound/Music/audience.ogg");

	Restart();
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Source/Sprites/Stage_Sprites/PaoPao_Cafe/Background.png");
	
	//Enabling game features
	App->particles->Enable();
	App->collision->Enable();
	App->player->Enable();
	App->enemy->Enable();
	App->ui->Enable();

	//Enabling audio
	App->audio->PlayMusic(music);
	App->audio->PlayMusic(audience);

	wall1 = App->collision->AddCollider({ 0, 300, 15, -500 }, COLLIDER_WALL, this);
	wall2 = App->collision->AddCollider({ 750, 300 , 15, -500 }, COLLIDER_WALL, this);

	return ret;
}

bool ModuleScenePaoPao::CleanUp()
{
	App->player->Disable();
	App->enemy->Disable();
	App->particles->Disable();
	App->collision->Disable();
	SDL_DestroyTexture(graphics);
	LOG("Unloading all Features from Scene");
	

	return true;
}

void ModuleScenePaoPao::Restart() {
	//Restart Player values
	App->player->life = 100;
	App->player->position.x = 100;
	App->player->position.y = 220;
	//Restart enemy values


	App->enemy->life= 100;
	App->enemy->position.x = 200;
	App->enemy->position.y = 220;
	//Restart time
	App->ui->time = 90000;
	

}


// Update: draw background
update_status ModuleScenePaoPao::Update()
{
	// Drawing background - Pao Pao Background
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	
	//People animation
	App->render->Blit(graphics, 0, 0, &(people.GetCurrentFrame()), 0.75f ); 

	App->ui->Timer(129,5);
	App->ui->DrawLife();

	float centerx = (App->player->position.x + App->enemy->position.x) / 2;
	float centery = (App->player->position.y + App->enemy->position.y) / 2;

	//camera locked
	App->render->cam_pos.x = -centerx;
	App->render->cam_pos.y = (SCREEN_HEIGHT)-centery;
	App->render->camera.x = App->render->cam_pos.x;
	App->render->camera.y = App->render->cam_pos.y;
	

	//Scene Out
	if (App->player->life <= 0)
	{
		App->fade->FadeToBlack(App->scene_paopao, App->p2w, 1.5);

	}
	else if (App->enemy->life <= 0)
	{
		App->fade->FadeToBlack(App->scene_paopao, App->p1w, 1.5);

	}
	return UPDATE_CONTINUE;
}