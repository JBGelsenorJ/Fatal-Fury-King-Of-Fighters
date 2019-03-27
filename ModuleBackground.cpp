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
	people.PushBack({0, 0, 619, 224});
	people.PushBack({ 0,0,0,0 });
	people.speed = 0.08f;
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Source/Sprites/Stage_Sprites/PaoPao_Cafe/PaoPaoStage_frame.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); //Pao Pao Background
	
	
	App->render->Blit(graphics2, 0, 0, &(people.GetCurrentFrame()), 0.75f); 

	// TODO 2: Draw the ship from the sprite sheet with some parallax effect
	
	// TODO 3: Animate the girl on the ship (see the sprite sheet)
	
	

	return UPDATE_CONTINUE;
}