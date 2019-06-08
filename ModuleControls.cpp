#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include "ModuleMusic.h"
#include "Application.h"
#include "p2Point.h"
#include "ModuleControls.h"
#include "ModuleFFIntro.h"
#include "ModuleFFIntro2.h"
#include "ModuleUI.h"
#include "ModuleWelcomeScreen.h"
#include "ModulePlayerSelection.h"

ModuleControls::ModuleControls()
{

	//Background
	background.PushBack({ 0,0,305,225 });


	//terry idle animation

	terry.PushBack({ 373, 499, 70, 108 });
	terry.PushBack({ 442, 499, 70, 108 });
	terry.PushBack({ 508, 499, 70, 108 });
	terry.speed = 0.08f;


	//andy idle animation

	andy.PushBack({ 36, 497, 64, 106 });
	andy.PushBack({ 99, 497, 64, 106 });
	andy.PushBack({ 162, 497, 64, 106 });
	andy.speed = 0.08f;


	//joe idle animation

	joe.PushBack({ 685, 500, 68, 111 });
	joe.PushBack({ 763, 500, 68, 111 });
	joe.PushBack({ 841, 500, 68, 111 });
	joe.speed = 0.08f;

	//controls animation

	controls.PushBack({ 324, 119, 305, 106 }); //inicial
	controls.PushBack({ 646, 119, 305, 106 }); //punch
	controls.PushBack({ 324, 119, 305, 106 }); //inicial
	controls.PushBack({ 324, 241, 305, 106 }); //kick
	controls.PushBack({ 324, 119, 305, 106 }); //inicial
	controls.PushBack({ 646, 241, 305, 106 }); //jump
	controls.PushBack({ 324, 119, 305, 106 }); //inicial
	controls.PushBack({ 1, 361, 305, 106 }); //squat
	controls.PushBack({ 324, 119, 305, 106 }); //inicial
	controls.PushBack({ 324, 361, 305, 106 }); //throw
	controls.PushBack({ 324, 119, 305, 106 }); //inicial
	controls.speed = 0.01f;


}

ModuleControls::~ModuleControls()
{}

// Load assets
bool ModuleControls::Start()
{
	LOG("Loading image assets");
	bool ret = true;

	/*fplayer = { 27,73 };
	frock = { -25,177 };
	animationState = Enter;
	step = 0;*/

	graphics = App->textures->Load("Source/UI/Intro/controls.png");
	introsong = App->audio->LoadMusic("Source/Sound/Music/Opening.ogg");

	App->audio->PlayMusic(introsong);
	App->render->camera.x = -33;
	App->render->camera.y = 0;

	pos_terry_x = 70;
	pos_andy_x = 150;
	pos_joe_x = 220;
	pos_controls_x = 0;

	pos_terry_y = 25;
	pos_andy_y = 25;
	pos_joe_y = 25;
	pos_controls_y = 119;


	return ret;

}

bool ModuleControls::CleanUp()
{
	LOG("Unloading FFINTRO");

	App->textures->Unload(graphics);

	//SDL_DestroyTexture(graphics);
	return true;
}

/*void ModuleControls::RenderWords() {

	App->render->Blit(graphics, pos_terry_x, terry1.position.y, &(terry1.rect));
	App->render->Blit(graphics, pos_andy_x, andy1.position.y, &(andy1.rect));
	App->render->Blit(graphics, pos_joe_x, joe1.position.y, &(joe1.rect));
	App->render->Blit(graphics, pos_controls_x, controls1.position.y, &(controls1.rect));
	App->render->DrawQuad({ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }, 255, 255, 255, 255, true);

}*/

// Update: draw background
update_status ModuleControls::Update()
{

	App->render->Blit(graphics, pos_background_x, pos_background_y, &(background.GetCurrentFrame()), 0.75f);
	
	App->render->Blit(graphics, pos_controls_x, pos_controls_y, &(controls.GetCurrentFrame()), 0.75f);

	App->render->Blit(graphics, pos_terry_x, pos_terry_y, &(terry.GetCurrentFrame()), 0.75f);
	App->render->Blit(graphics, pos_andy_x, pos_andy_y, &(andy.GetCurrentFrame()), 0.75f);
	App->render->Blit(graphics, pos_joe_x, pos_joe_y, &(joe.GetCurrentFrame()), 0.75f);




	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->scene_intro, App->playerselection, 1.5);
	}

	if (SDL_GameControllerGetButton(App->input->gamepad2, SDL_CONTROLLER_BUTTON_START) == 1)
	{
		App->fade->FadeToBlack(App->scene_intro, App->playerselection, 1.5);
	}
	if (SDL_GameControllerGetButton(App->input->gamepad1, SDL_CONTROLLER_BUTTON_START) == 1)
	{
		App->fade->FadeToBlack(App->scene_intro, App->playerselection, 1.5);
	}



	return UPDATE_CONTINUE;
}