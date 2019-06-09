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
#include "ModuleSlowdown.h"

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
	wall1.y = -100;
	wall1.h = 300;
	wall1.w = 30;

	wall2.x = 280;
	wall2.y = -100;
	wall2.h = 300;
	wall2.w = 30;


}

ModuleBillyKane2::~ModuleBillyKane2()
{}

// Load assets
bool ModuleBillyKane2::Start()
{
	bool ret = true;

	//Restarting gameplay values
	Restart();

	//Loading Assets
	LOG("Loading BillyKane2 [2] Assets");
	music = App->audio->LoadMusic("Source/Sound/Music/billy.ogg");
	graphics = App->textures->Load("Source/Sprites/Stage_Sprites/Billy_Kane_map/Background.png");

	//Playing Music
	App->audio->PlayMusic(music);
	
	//Enabling Gampleay Features
	App->player2->Enable();
	App->enemy2->Enable();
	App->collision->Enable();
	App->particles->Enable();
	App->ui->Enable();
	//App->slowdown->Enable();


	//Scene limits from left and right
	limitleft.x = 20;
	limitleft.y = -300;
	limitright.x = 333;
	limitright.y = -300;
	wall1c = App->collision->AddCollider({ limitleft.x, limitleft.y, 15, -1000 }, COLLIDER_WALL, this);//NEW
	wall2c = App->collision->AddCollider({ limitright.x, limitright.y , 15, -1000 }, COLLIDER_WALL, this);//NEW

	//STATE MACHINE
	scenestatus = PREUPDATE;
	globaltime = SDL_GetTicks();

	return ret;
}

bool ModuleBillyKane2::CleanUp()
{
	//Disable gameplay features
	App->player2->Disable();
	App->enemy2->Disable();
	App->particles->Disable();
	App->collision->Disable();
	App->ui->Disable();

	//Destroying Scene Resources
	SDL_DestroyTexture(graphics);
	LOG("Unloading all Features and textures from BillyKane [2]");

	return true;
}

void ModuleBillyKane2::Restart() {
	//Restart Player values
	App->player2->life = 100;
	App->player2->position.x = 100;
	App->player2->position.y = 220;
	//Restart enemy values
	App->enemy2->life = 100;
	App->enemy2->position.x = 200;
	App->enemy2->position.y = 220;
	//Restart time
	App->ui->time = 90000;
	App->ui->starttime = SDL_GetTicks();
	App->ui->enabletime = false;
	App->ui->winactive = false;
	audiofight = true;
	audioround = true;

}


// Update: draw background
update_status ModuleBillyKane2::Update()
{
	//Camera Move
	App->render->CameraMove(App->player2->position.x, App->enemy2->position.x);

	//Background
	App->render->Blit(graphics, -115, 0, &(sea.GetCurrentFrame()), 1.4f);

	//People animation
	App->render->Blit(graphics, 250, 115, &(people1.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, 187, 115, &(people3.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, -108, 115, &(people2.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, 0, 0, &wall1, 1.0, true);
	App->render->Blit(graphics, 0, 0, &wall2, 1.0, true);

	wall1c->SetPos((((-App->render->camera.x))), -limitleft.y);//NEW
	wall2c->SetPos((((-App->render->camera.x) + 300)), -limitright.y);//NEW

	
	
	//SCENE STATE MACHINE
	switch (scenestatus) {

	case PREUPDATE:
		pretime = SDL_GetTicks();

		//2 SECONDS
		if (pretime >= globaltime + 2000) {
			App->render->Blit(App->ui->titles, (SCREEN_WIDTH / 2) - 55, 45, &(App->ui->roundtwo), false);
			if (audioround) {
				App->audio->PlayFX(App->ui->readyfx);
				audioround = false;
			}
		}


		//4 SECONDS
		if (pretime >= globaltime + 4000) {
			App->render->Blit(App->ui->titles, (SCREEN_WIDTH / 2) - 88, 70, &(App->ui->fight), false);
			if (audiofight) {
				App->audio->PlayFX(App->ui->fightfx);
				audiofight = false;
			}
		}

		//FINISH CONDITION
		if (pretime >= globaltime + 5000)scenestatus = UPDATE;
		break;

	case UPDATE:
		App->ui->enabletime = true;

		//FINISH CONDITION
		if (App->ui->WinLose(App->player2->life, App->enemy2->life, App->ui->time) || time == 0) scenestatus = POSTCOMBAT;
		break;

	case POSTCOMBAT:
		pretime = SDL_GetTicks();






		//FINISH SCENE CONDITION
		/*Change Scene conditions*/
		if (App->ui->winactive == true) {
			//IF PLAYER BOOL 1 AND ENEMY BOOL 1 GOES 3rd round
			if (App->ui->p1canwin && App->ui->p2canwin) {
				App->fade->FadeToBlack(this, App->scene_billykane3);
			}
			else {
				//
				if (App->ui->p1canwin) {
					App->ui->p1win = true;
					App->fade->FadeToBlack(this, App->p1w);
					App->slowdown->StartSlowdown(40, 200);
					App->slowdown->UpdateSlowdown();
				}
				if (App->ui->p2canwin) {
					App->ui->p1win = true;
					App->fade->FadeToBlack(this, App->p2w);
					App->slowdown->StartSlowdown(40, 200);
					App->slowdown->UpdateSlowdown();
				}
			}

		}
		else if (App->ui->time <= 0) 	App->fade->FadeToBlack(this, this);
		break;
	}

	return UPDATE_CONTINUE;
}