#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{

	//Pao Pao Background
	background.x = 0;
	background.y = 0;
	background.w = 619;
	background.h = 224;


	//Background Animation
	people.PushBack({ 0, 224, 619, 224 });
	people.PushBack({ 0,448,619,224 });
	people.speed = 0.09f;
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Source/Sprites/Stage_Sprites/PaoPao_Cafe/Background.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Drawing background - Pao Pao Background
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	
	//People animation
	App->render->Blit(graphics, 0, 0, &(people.GetCurrentFrame()), 0.75f ); 

	return UPDATE_CONTINUE;
}