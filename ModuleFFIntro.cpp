#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include "ModuleMusic.h"
#include "Application.h"
#include "p2Point.h"
#include "ModuleEnemy.h"
#include "ModuleFFIntro.h"
#include "ModuleFFIntro2.h"
#include "ModuleTime.h"
#include "ModuleWelcomeScreen.h"

ModuleFFIntro::ModuleFFIntro()
{

	//Intro Background

	introwin.PushBack({ 0,0,314,192 });
	borders.PushBack({ 0,446,304,225 });

	//Start Animation

	start.PushBack({ 590, 260, 146, 21 });
	start.PushBack({ 0, 700, 236, 44 });
	start.speed = 0.06f;

	//player

	player.PushBack({ 340, 37, 62, 127 });
	player.PushBack({ 411, 38, 62, 127 });
	player.PushBack({ 484, 38, 62, 127 });
	player.PushBack({ 553, 38, 62, 127 });
	player.PushBack({ 484, 38, 62, 127 });
	player.PushBack({ 411, 38, 62, 127 });
	player.PushBack({ 484, 38, 62, 127 });
	player.speed = 0.15f;

	//rock

	rock1.rect = { 0,0,117,31 };

	rock.PushBack({ 647,129,117,31 });
	//title.rect = { 0,80,200,75 };

	//Player Animation

	//positionplayer.x = -40;
	//positionplayer.y = 73;

	/*player.PushBack({ 340, 37, 62, 127 });
	player.PushBack({ 411, 38, 62, 127 });
	player.PushBack({ 484, 38, 62, 127 });
	player.PushBack({ 553, 38, 62, 127 });
	player.PushBack({ 484, 38, 62, 127 });
	player.PushBack({ 411, 38, 62, 127 });
	player.PushBack({ 484, 38, 62, 127 });
	player.speed = 0.4f;*/

	//Rock
/*
	positionrock.x = -40;
	positionrock.y = 244;

	rock.x = 647;
	rock.y = 129;
	rock.w = 117;
	rock.h = 31;
*/
//Borders
/*
borders.x = 0;
borders.y = 446;
borders.w = 304;
borders.h = 225;*/

}

ModuleFFIntro::~ModuleFFIntro()
{}

// Load assets
bool ModuleFFIntro::Start()
{
	LOG("Loading image assets");
	bool ret = true;
	player1.position = { -40,73 };
	rock1.position = { -40,177 };
	//title.position={50,300}
	fplayer = { 27,73 };
	frock = { -25,177 };
	animationState = Enter;
	step = 0;

	graphics = App->textures->Load("Source/UI/Intro/intro2.png");
	introsong = App->audio->LoadMusic("Source/Sound/Music/Opening.ogg");

	App->audio->PlayMusic(introsong);
	App->collision->Disable();

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;

}

bool ModuleFFIntro::CleanUp()
{
	LOG("Unloading FFINTRO");
	App->player->Disable();
	App->enemy->Disable();
	App->timer->Disable();
	App->textures->Unload(graphics);

	//SDL_DestroyTexture(graphics);
	return true;
}

void ModuleFFIntro::RenderWords() {

	App->render->Blit(graphics, rock1.position.x, rock1.position.y, &(rock1.rect));
	App->render->Blit(graphics, player1.position.x, player1.position.y, &(player1.rect));
	App->render->DrawQuad({ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }, 255, 255, 255, 255, true);

}

// Update: draw background
update_status ModuleFFIntro::Update()
{

	switch (animationState) {

	case Enter:

		rock1.position += frock;
		step++;

		if (step >= 40) {

			animationState = Done;

			step = 0;
		}

		RenderWords();

		break;

		/*case GoBack:

			rock1.position -= frock;
			player1.position += {0, -4};

			step++;

			if (step >= 20) {

				step = 0;
				animationState = Done;
			}

			RenderWords();

			break;*/

			/*case Fighting:

				title.position += {0, -7};
				step++;

				if (step >= 20) {

					animationState = Done;
				}

				RenderWords;
				break;*/

	case Done:

		App->render->Blit(graphics, 0, 16, &(introwin.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphics, 72, 140, &(start.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphics, -25, 177, &(rock.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphics, 27, 73, &(player.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphics, 0, 1, &(borders.GetCurrentFrame()), 0.75f);


		break;

	default:
		break;

	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->scene_intro, App->scene_welcome, 1.5);
	}

	/*// Drawing background - Intro Background

	App->render->Blit(graphics, 0, 16, &introwin, 0.75f);

	//Drawing Rock

	App->render->Blit(graphics, positionrock.x, 177, &rock, 0.75f);

	for (positionrock.x = -40; positionrock.x < -25; positionrock.x++) {

		positionrock.x += 1.5;

	}

	/*do {

		positionrock.x += 1.5;

	} while (positionrock.x < -25);



	// Player animation

	App->render->Blit(graphics, positionplayer.x, 73, &(player.GetCurrentFrame()), 0.75f);

	for (positionplayer.x = -40; positionplayer.x < 27; positionplayer.x++) {

		positionplayer.x += 1;

	}




	//Start animation

	App->render->Blit(graphics, 72, 140, &(start.GetCurrentFrame()), 0.99f);


	// Drawing borders - Intro broders

	App->render->Blit(graphics, 0, 0, &borders, 0.75f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_intro, App->scene_intro2, 1.5);

	}*/

	return UPDATE_CONTINUE;
}