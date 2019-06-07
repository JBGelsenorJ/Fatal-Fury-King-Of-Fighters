#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneBillyKane.h"
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
#include "ModuleSlowdown.h"


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
	graphics = App->textures->Load("Source/Sprites/Stage_Sprites/Billy_Kane_map/Background.png"); //rest add the shadow texture
	
	//Enabling game features
	App->particles->Enable();
	App->input->Enable();
	App->collision->Enable();
	App->enemy2->Enable();
	App->player2->Enable();
	App->ui->Enable();
	App->slowdown->Enable();
	App->player2->rounds = 0;
	App->enemy2->rounds = 0;
	//Enabling audio
	App->audio->PlayMusic(music);
	Mix_PlayChannel(-1 , audience, -1);
	Mix_VolumeChunk(audience, 35);
	wall1c = App->collision->AddCollider(wall1,COLLIDER_WALL,this);
	wall2c = App->collision->AddCollider(wall2, COLLIDER_WALL_RIGHT, this);

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

	//Restarting Booleans that works on scene change
	App->ui->ResetSceneChange();
	App->player2->rounds = 0;
	App->enemy2->rounds = 0;
}


// Update: draw background
update_status ModuleBillyKane::Update()
{
	//Camera Move
	App->render->CameraMove(App->player2->position.x, App->enemy2->position.x);

	//Background

	App->render->Blit(graphics, -115, 0, &(sea.GetCurrentFrame()), 1.4f);

	//People animation
	App->render->Blit(graphics, 250, 115, &(people1.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, 187, 115, &(people2.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, -108, 115, &(people3.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, 0, 0, &wall1, 1.4, true);
	App->render->Blit(graphics, 0, 0, &wall2, 1.4, true);

	//Features that should update
	App->ui->Timer();
	App->ui->DrawLife();
	App->ui->WinLose(App->player2->life, App->enemy2->life, App->ui->time);
	App->ui->Score(App->player2->rounds, App->enemy2->rounds);
	App->ui->ChangeScene(App->player2->rounds, App->enemy2->rounds);

	//Check this stuff
	float centerx = (App->player2->position.x + App->enemy2->position.x) / 2;
	float centery = (App->player2->position.y + App->enemy2->position.y) / 2; 
	wall1c->SetPos(wall1.x, wall1.y); 
	wall2c->SetPos(wall2.x, wall2.y);
	
	
	return UPDATE_CONTINUE;
}