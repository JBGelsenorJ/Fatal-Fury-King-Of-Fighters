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
	modules[9] = fade = new ModuleFadeToBlack();
	modules[10] = audio = new ModuleMusic();
	modules[11] = scene_intro = new ModuleFFIntro();
	modules[12] = scene_intro2 = new ModuleFFIntro2();
	modules[13] = particles = new ModuleParticles();

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
	scene_paopao->Disable();
	scene_soundbeach->Disable();
	playerselection->Disable();
	scene_intro2->Enable();
	scene_intro->Disable();
	scene_welcome->Disable();

	App->player->Disable();

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