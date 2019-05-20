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
#include "ModuleSceneBillyKane2.h"
#include "ModuleSceneBillyKane3.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleFFIntro.h"
#include "ModuleP1Wins.h"
#include "ModuleP2Wins.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"


ModuleBillyKane2::ModuleBillyKane2()
{

	//Background

	//sea.PushBack({ 721,567,621,234  });
	//sea.PushBack({ 721,821,621,239 });
	sea.PushBack({ 721,1062,621,237 });
	sea.PushBack({ 721,1311,621,237 });
	sea.speed = 0.09f;

	//purple people animation<
	people1.PushBack({ 757, 51, 64, 95 });
	people1.PushBack({ 843,51,64,95 });
	people1.speed = 0.09f;
	// fat and thin people
	people2.PushBack({ 753, 268, 62, 150 });
	people2.PushBack({ 846, 277,61,150 });
	people2.speed = 0.09f;

	//blonde people
	people3.PushBack({ 749, 410, 64, 98 });
	people3.PushBack({ 844,410,63,98 });
	people3.speed = 0.09f;

	//walls
	wall1.x = 30;
	wall1.y = 0;
	wall1.h = 300;
	wall1.w = 30;

	wall2.x = 280;
	wall2.y = 0;
	wall2.h = 300;
	wall2.w = 30;


}

ModuleBillyKane2::~ModuleBillyKane2()
{}

// Load assets
bool ModuleBillyKane2::Start()
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
	wall1c = App->collision->AddCollider(wall1,COLLIDER_WALL,this);
	wall2c = App->collision->AddCollider(wall2, COLLIDER_WALL_RIGHT, this);

	return ret;
}

bool ModuleBillyKane2::CleanUp()
{
	App->player2->Disable();
	App->enemy2->Disable();
	App->particles->Disable();
	App->collision->Disable();
	SDL_DestroyTexture(graphics);
	LOG("Unloading all Features from Scene");
	

	return true;
}

void ModuleBillyKane2::Restart() {
	
	//Restart Player values
	App->player2->life = 100;
	App->player2->position.x = 100;
	App->player2->position.y = 220;
	//Restart enemy values
	App->enemy2->life= 100;
	App->enemy2->position.x = 200;
	App->enemy2->position.y = 220;
	//Restart time
	App->ui->time = 90000;
	App->ui->starttime = SDL_GetTicks();
}


// Update: draw background
update_status ModuleBillyKane2::Update()
{
	//background
	App->render->Blit(graphics, -115, 0, &(sea.GetCurrentFrame()), 1.4f);
	//People animation
	App->render->Blit(graphics, 250, 115, &(people1.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, 187, 115, &(people3.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, -108, 115, &(people2.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, 0, 0, &wall1, 1.0, true);
	App->render->Blit(graphics, 0, 0, &wall2, 1.0, true);

	App->ui->Timer();
	App->ui->DrawLife();
	App->ui->Score(App->player2->rounds, App->enemy2->rounds, App->player2->life, App->enemy2->life, App->player2->score, App->enemy2->score);

	
	wall1c->SetPos(wall1.x, wall1.y); 
	wall2c->SetPos(wall2.x, wall2.y);
	// Scene out
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {

		App->fade->FadeToBlack(App->scene_billykane2, App->scene_billykane3, 1.5);

	}
	if (App->player2->life <= 0)
	{
		App->enemy2->rounds++;

		 if (App->enemy2->rounds == 2)
		{
			App->fade->FadeToBlack(App->scene_billykane2, App->p2w, 1.5);
		}
		else
		{
			App->fade->FadeToBlack(App->scene_billykane2, App->scene_billykane3, 1.5);
		}
	}
	// Player wins by defeating enemy
	else if (App->enemy2->life <= 0)
	{
		App->player2->rounds++;
		if (App->player2->rounds == 2)
		{
			App->fade->FadeToBlack(App->scene_billykane2, App->p1w, 1.5);
		}
		else
		{
			App->fade->FadeToBlack(App->scene_billykane2, App->scene_billykane3, 1.5);
		}

	}
	// Time's out player wins because he has more life
	else if (App->ui->time <= 0 && App->player2->life > App->enemy2->life || App->ui->time >= 200000 && App->player2->life > App->enemy2->life)
	{

		App->player2->rounds++;
		if (App->player2->rounds == 2)
		{
			App->fade->FadeToBlack(App->scene_billykane2, App->p1w, 1.5);
		}
		else
		{
			App->fade->FadeToBlack(App->scene_billykane2, App->scene_billykane3, 1.5);
		}
	}
	// Time's out enemy wins because he has more life
	else if (App->ui->time <= 0 && App->player2->life < App->enemy2->life || App->ui->time >= 200000 && App->player2->life < App->enemy2->life)
	{
		App->enemy2->rounds++;
		 if (App->enemy2->rounds == 2)
		{
			App->fade->FadeToBlack(App->scene_billykane3, App->p2w, 1.5);
		}
		else
		{
			App->fade->FadeToBlack(App->scene_billykane2, App->scene_billykane3, 1.5);
		}
	}
	// Tie
	else if (App->ui->time <= 0 && App->player2->life == App->enemy2->life || App->ui->time >= 200000 && App->player2->life == App->enemy2->life)
	{
		App->fade->FadeToBlack(App->scene_billykane2, App->scene_billykane3, 1.5);

	}
	return UPDATE_CONTINUE;
}