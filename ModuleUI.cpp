#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL\include\SDL.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleMusic.h"

//Needed to link life with healthbars
#include "ModulePlayer.h"
#include "ModuleEnemy.h"

//Needed to make sprintf_s
#include <stdio.h>





ModuleUI::ModuleUI(){

	//White Square behind Timer

	timerbackground.x = 382;
	timerbackground.y = 56;
	timerbackground.w = 100;
	timerbackground.h = 75;

	//Health full of life
	health.x = 1;
	health.y = 20;
	health.w = 120;
	health.h = 13;

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

	return ret;
}

update_status ModuleUI::Update(){
	health.w = 120 / ((App->enemy->life) / 100);

	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	
	//Destroying features loaded
	SDL_DestroyTexture(graphics);
	App->fonts->UnLoad(countdown);
	
	LOG("Unloading Textures, Fonts and Audio");

	return true;
}

bool ModuleUI::Timer(int w, int h) {

	//Time   !FIX DOES START IN 88 SEC NOT IN 90¡
	if (starting <= SDL_GetTicks() && time > 0) {
		//starting = SDL_GetTicks();
		//time -= SDL_GetTicks();
		time = 90000 - SDL_GetTicks();
		//time--;
	}

	

	sprintf_s(time_text, 10, "%7d", time / 1000);
	App->render->DrawQuad(timerbackground, 255, 255, 255, 255, false);
	App->fonts->BlitText(w, h, countdown, time_text);

	
	return true;
}

bool ModuleUI::DrawLife() {
	
	//Rendering P2 Life
	App->render->Blit(graphics, 166, 25, &nohealth,false);
	App->render->Blit(graphics, 166, 25, &health, false);

	App->render->MirrorBlit(graphics, 2, 25, &nohealth , 0.0f , 0 ,NULL);
	App->render->MirrorBlit(graphics, 2, 25, &health, 0.0f, 0, NULL);



	return true;
}
