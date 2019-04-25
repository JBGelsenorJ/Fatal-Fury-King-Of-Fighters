#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScenePaoPao.h"
#include "ModuleSceneSoundBeach.h"
#include "ModulePlayerSelection.h"
#include "ModuleMusic.h"
#include "ModuleWelcomeScreen.h" 
#include "ModuleFFIntro.h"
#include "ModuleFFIntro2.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemy.h"
#include "ModuleFonts.h"
#include "ModuleTime.h"
#include "ModuleP1Wins.h"
#include "ModuleP2Wins.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = playerselection = new ModulePlayerSelection();
	modules[5] = scene_paopao = new ModuleScenePaoPao();
	modules[6] = scene_soundbeach = new ModuleSceneSoundBeach();
	modules[7] = scene_welcome = new ModuleWelcomeScreen();
	modules[8] = player = new ModulePlayer();
	modules[9] = enemy = new ModuleEnemy();
	modules[10] = fade = new ModuleFadeToBlack();
	modules[11] = audio = new ModuleMusic();
	modules[12] = scene_intro = new ModuleFFIntro();
	modules[13] = scene_intro2 = new ModuleFFIntro2();
	modules[14] = particles = new ModuleParticles();
	modules[15] = collision = new ModuleCollision();
	modules[16] = fonts = new ModuleFonts();
	modules[17] = timer = new ModuleTime();
	modules[18] = p1w = new ModuleP1Wins();
	modules[19] = p2w = new ModuleP2Wins();

}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;
	
	// Disable the map that you do not start with
	playerselection->Disable();
	scene_soundbeach->Disable();
	scene_intro2->Disable();
	scene_intro->Disable();
	scene_welcome->Disable();
	p1w->Disable();
	p2w->Disable();
	
	//Disable game features
	App->player->Disable();
	collision->Disable();
	particles->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}