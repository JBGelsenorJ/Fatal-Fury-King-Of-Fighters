#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayerSelection.h"
#include "ModuleMusic.h"
#include "ModuleWelcomeScreen.h" 
#include "ModuleFFIntro.h"
#include "ModuleFFIntro2.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleP1Wins.h"
#include "ModuleP2Wins.h"
#include "ModuleSceneBillyKane.h"
#include "ModuleSceneBillyKane2.h"
#include "ModuleSceneBillyKane3.h"
#include "ModulePlayer2.h"
#include "ModuleEnemy2.h"
#include "ModuleNeogeo.h"
#include "ModuleSlowdown.h"
#include "ModuleControls.h"


Application::Application()
{
	//Main Features
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = slowdown = new ModuleSlowdown();
	modules[3] = input = new ModuleInput();
	modules[4] = textures = new ModuleTextures();
	modules[5] = audio = new ModuleMusic();
	modules[6] = fonts = new ModuleFonts();
	
	//Scenes
	modules[7] = scene_neogeo = new ModuleNeogeo();
	modules[8] = scene_intro = new ModuleFFIntro();
	modules[9] = scene_intro2 = new ModuleFFIntro2();
	modules[10] = scene_controls = new ModuleControls();
	modules[11] = scene_welcome = new ModuleWelcomeScreen();
	modules[12] = playerselection = new ModulePlayerSelection();
	modules[13] = scene_billykane = new ModuleBillyKane();
	modules[14] = scene_billykane2 = new ModuleBillyKane2();
	modules[15] = scene_billykane3 = new ModuleBillyKane3();
	modules[16] = p1w = new ModuleP1Wins();
	modules[17] = p2w = new ModuleP2Wins();

	//Things that must render above scenes in order
	modules[18] = collision = new ModuleCollision();
	modules[19] = particles = new ModuleParticles();
	modules[20] = ui = new ModuleUI();

	//Players must render above all features
	modules[21] = player2 = new ModulePlayer2();
	modules[22] = enemy2 = new ModuleEnemy2();
	modules[23] = fade = new ModuleFadeToBlack();
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;
	
	/*SCENES IN ORDER DISABLED. COMMENT LINE IF YOU WANT ENABLE*/
	scene_neogeo->Disable();
	scene_intro->Disable();
	scene_intro2->Disable(); 
	scene_controls->Disable();
	scene_welcome->Disable();
	playerselection->Disable();
	//scene_billykane->Disable();  
	scene_billykane2->Disable();
	scene_billykane3->Disable();
	p1w->Disable();
	p2w->Disable();
	
	
	//Disable game features
	player2->Disable();
	enemy2->Disable();
	audio->Disable();
	collision->Disable();
	particles->Disable();
	ui->Disable();
	slowdown->Disable();

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