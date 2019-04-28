#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL\include\SDL.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleMusic.h"
#include <string.h>

//Needed to link life with healthbars
#include "ModulePlayer.h"
#include "ModuleEnemy.h"

//Needed to make sprintf_s
#include <stdio.h>


#define START_DELAY 2000;


ModuleUI::ModuleUI(){

	//White Square behind Timer

	timerbackground.x = 382;
	timerbackground.y = 11;
	timerbackground.w = 100;
	timerbackground.h = 75;

	//HealthP1 full of life
	health.x = 1;
	health.y = 20;
	health.w = 120;
	health.h = 13;

	//HealthP2 full of life
	healthp2.x = 1;
	healthp2.y = 20;
	healthp2.w = 120;
	healthp2.h = 13;

	//Health without life
	nohealth.x = 1;
	nohealth.y = 0;
	nohealth.w = 120;
	nohealth.h = 12;

	//Point without red dot or scored
	point.x = 0;
	point.y = 0;
	point.w = 0;
	point.h = 0;

	//Red Point
	pointred.x = 0;
	pointred.y = 0;
	pointred.w = 0;
	pointred.h = 0;

	//Point Scored
	pointscored.x = 0;
	pointscored.y = 0;
	pointscored.w = 0;
	pointscored.h = 0;


	
}

ModuleUI::~ModuleUI()
{}

//Loading Assets(Fonts, textures and audio).
bool ModuleUI::Start()
{
	LOG("Loading features");
	bool ret = true;

	//Loading SpriteSheet and fonts
	graphics = App->textures->Load("Source/UI/combatui/ui.png");
	countdown = App->fonts->Load("Source/UI/fonts/marcador.png", "0123456789", 1);
	scorefont = App->fonts->Load("Source/UI/fonts/Score_font.png", "-0123456789abcdefghijklmnopqrstuvwxyz", 1);
	//We set time on 90s
	time = 90000;
	starting = SDL_GetTicks();
	starttime = SDL_GetTicks();

	return ret;
}

update_status ModuleUI::Update(){


	health.w = 120 * (App->enemy->life / 100);
	healthp2.w = 120 * (App->player->life / 100);

	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	
	//Destroying features loaded
	SDL_DestroyTexture(graphics);
	App->fonts->UnLoad(countdown);
	App->fonts->UnLoad(scorefont);
	LOG("Unloading Textures, Fonts and Audio");

	return true;
}

bool ModuleUI::Timer(int w, int h) {

	if (starting <= SDL_GetTicks() && time > 0) {
		//starting = SDL_GetTicks();
		//time -= SDL_GetTicks();
		time = 90000 - SDL_GetTicks() + starttime;
		//time--;
	}
	if (time >= 200000)
	{
		time = 0;
	}

	sprintf_s(time_text, 10, "%7d", time / 1000);
	App->render->DrawQuad(timerbackground, 255, 255, 255, 255, false);
	App->fonts->BlitText(w, h, countdown, time_text);

	
	return true;
}

bool ModuleUI::DrawLife() {
	
	//Rendering P1 Life

	
	/*		FIX FONT SIZE
	sprintf_s(p2score, 10, "%7d", App->player->score);
	App->fonts->BlitText(20, 15, scorefont, p2score);
	*/

	//Rendering P2 Life
	App->render->Blit(graphics, 166, 10, &nohealth,false);
	App->render->Blit(graphics, 166, 10, &health, false);



	App->render->MirrorBlit(graphics, 2, 10, &nohealth , 0.0f , 0 ,NULL);
	App->render->MirrorBlit(graphics, 2, 10, &healthp2, 0.0f, 180, NULL);

	return true;
}