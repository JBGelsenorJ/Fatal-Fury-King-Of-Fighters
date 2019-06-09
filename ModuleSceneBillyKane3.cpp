#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneBillyKane3.h"
#include "ModuleSceneBillyKane.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include "ModuleMusic.h"
#include "ModuleCollision.h"
#include "ModuleEnemy2.h"


#include "ModulePlayerSelection.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleFFIntro.h"
#include "ModuleP1Wins.h"
#include "ModuleP2Wins.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"


ModuleBillyKane3::ModuleBillyKane3()
{

	//Background

	//sea.PushBack({ 1360,560,617,238 });
	sea.PushBack({ 1360,816,618,239 });
	sea.PushBack({ 1360,1060,619,238 });
	sea.speed = 0.09f;

	//purple people animation
	people1.PushBack({ 1368, 43, 65, 99 });
	people1.PushBack({ 1446,43,68,102 });
	people1.speed = 0.09f;
	// fat and thin people
	people2.PushBack({ 1367, 409, 68, 99 });
	people2.PushBack({ 1454,409,62,105 });
	people2.speed = 0.09f;

	//blonde people
	people3.PushBack({ 1366, 279, 68, 99 });
	people3.PushBack({ 1459,279,62,105 });
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

ModuleBillyKane3::~ModuleBillyKane3()
{}

// Load assets
bool ModuleBillyKane3::Start()
{
	bool ret = true;

	//Restarting gameplay values
	Restart();

	//Loading Assets
	LOG("Loading BillyKane3 [3] Assets");
	music = App->audio->LoadMusic("Source/Sound/Music/billy.ogg");
	graphics = App->textures->Load("Source/Sprites/Stage_Sprites/Billy_Kane_map/Background.png");

	//Playing Music
	App->audio->PlayMusic(music);

	//Enabling game features
	App->particles->Enable();
	App->input->Enable();
	App->collision->Enable();
	App->enemy2->Enable();
	App->player2->Enable();
	App->ui->Enable();

	
	wall1c = App->collision->AddCollider(wall1,COLLIDER_WALL,this);
	wall2c = App->collision->AddCollider(wall2, COLLIDER_WALL_RIGHT, this);

	return ret;
}

bool ModuleBillyKane3::CleanUp()
{
	//Disable gameplay features
	App->player2->Disable();
	App->enemy2->Disable();
	App->particles->Disable();
	App->collision->Disable();
	App->ui->Disable();

	//Destroying Stuff
	SDL_DestroyTexture(graphics);
	LOG("Unloading features and textures from BillyKane [3]");
	
	return true;
}

void ModuleBillyKane3::Restart() {
	
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
	App->ui->winactive = false;
}


// Update: draw background
update_status ModuleBillyKane3::Update()
{
	//Camera Move
	App->render->CameraMove(App->player2->position.x, App->enemy2->position.x);

	//Background
	App->render->Blit(graphics, -115, 0, &(sea.GetCurrentFrame()), 1.4f);

	//People animation
	App->render->Blit(graphics, 250, 115, &(people1.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, 187, 115, &(people2.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, -108, 115, &(people3.GetCurrentFrame()), 1.4f);
	App->render->Blit(graphics, 0, 0, &wall1, 1.0, true);
	App->render->Blit(graphics, 0, 0, &wall2, 1.0, true);

	if (App->ui->winactive == true) {

		//PLAYER 1 WINS
		if (App->ui->p1canwin) {
			App->ui->p1win = true;
			App->fade->FadeToBlack(this, App->p1w);
		}

		//PLAYER 2 WINS
		if (App->ui->p2canwin) {
			App->ui->p2win = true;
			App->fade->FadeToBlack(this, App->p2w);
		}
	}

	return UPDATE_CONTINUE;
}