#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL\include\SDL.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleMusic.h"
#include <stdio.h>




ModuleUI::ModuleUI(){
}

ModuleUI::~ModuleUI()
{}

//Loading Assets(Fonts, textures and audio).
bool ModuleUI::Start()
{
	LOG("Loading features");
	bool ret = true;


	//Loading SpriteSheet and fonts
	healthbar = App->textures->Load("");
	countdown = App->fonts->Load("Source/UI/fonts/marcador.png", "0123456789", 1);

	//We set time on 90s
	time = 90000;
	starting = SDL_GetTicks();

	return ret;
}

update_status ModuleUI::Update(){


	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	
	//Destroying features loaded
	SDL_DestroyTexture(healthbar);
	App->fonts->UnLoad(countdown);
	
	LOG("Unloading Textures, Fonts and Audio");

	return true;
}

bool ModuleUI::Timer(int w, int h) {

	//Time
	if (starting <= SDL_GetTicks() && time > 0) {
		//starting = SDL_GetTicks();
		//time -= SDL_GetTicks();
		time = 90000 - SDL_GetTicks();
		//time--;
	}

	sprintf_s(time_text, 10, "%7d", time / 1000);
	App->fonts->BlitText(w, h, countdown, time_text);


	return true;
}