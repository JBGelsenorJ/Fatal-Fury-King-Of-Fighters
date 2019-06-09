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
#include "ModuleEnemy2.h"
#include "ModulePlayer2.h"

//Needed to make sprintf_s
#include <stdio.h>

//Needed to make scene change
#include "ModuleSceneBillyKane.h"
#include "ModuleSceneBillyKane2.h"
#include "ModuleSceneBillyKane3.h"
#include "ModuleP1Wins.h"
#include "ModuleFadeToBlack.h"


#define START_DELAY 2000;


ModuleUI::ModuleUI(){

	//White Square behind Timer
	timerbackground.x = (SCREEN_WIDTH / 2) - 16; //CENTER OF THE SCREEN LESS TIMER
	timerbackground.y = 18;
	timerbackground.w = 32;
	timerbackground.h = 24;

	//Time Text Upp timer
	timetext.x = 34;
	timetext.y = 89;
	timetext.w = 33;
	timetext.h = 10;

	//P1 Yellow Healthbar
	health.x = 5;
	health.y = 11;
	health.w = 98;
	health.h = 9;

	//P2 Yellow Healthbar
	healthp2.x = 5;
	healthp2.y = 11;
	healthp2.w = 98;
	healthp2.h = 9;

	//Gray HealthBar
	nohealth.x = 5;
	nohealth.y = 25;
	nohealth.w = 98;
	nohealth.h = 9;

	//RedLife Animation
	redlife.PushBack({ 5,42,98,9 });
	redlife.PushBack({ 5,25,98,9 });
	redlife.speed = 0.1f;

	//Redpoint Animation
	redpoint.PushBack({22,63,18,18});
	redpoint.PushBack({ 40,63,18,18 });
	redpoint.speed = 0.1f;

	//Black Dot
	point.x = 22;
	point.y = 63;
	point.w = 18;
	point.h = 18;

	//Red Dot Point
	pointred.x = 40;
	pointred.y = 63;
	pointred.w = 18;
	pointred.h = 18;

	//Point Scored Dot
	pointscored.x = 4;
	pointscored.y = 63;
	pointscored.w = 18;
	pointscored.h = 18;

	//Andy and Terry Square
	andybogard.x = 62;
	andybogard.y = 63;
	andybogard.w = 18;
	andybogard.h = 18;

	terrybogard.x = 84;
	terrybogard.y = 64;
	terrybogard.w = 18; //maybe 17
	terrybogard.h = 18;

	healthwidth = 98;
	
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


	health.w = 98 * (App->enemy2->life / 100);
	healthp2.w = 98 * (App->player2->life / 100);
	
	Timer();
	DrawLife();
	Score(App->player2->rounds, App->enemy2->rounds);
	
	winactive = WinLose(App->player2->life, App->enemy2->life, time);
	
	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	
	//Destroying features loaded
	App->textures->Unload(graphics);
	App->fonts->UnLoad(countdown);
	App->fonts->UnLoad(scorefont);
	LOG("Unloading Textures, Fonts and Audio");

	return true;
}

bool ModuleUI::Timer() {

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
	App->fonts->BlitText(((SCREEN_WIDTH/2)-15), 19, countdown, time_text);
	App->render->Blit(graphics, ((SCREEN_WIDTH / 2) - 17), 9, &timetext, false);


	
	return true;
}

bool ModuleUI::DrawLife() {

	//Rendering P1 Life and character square
	
	if (App->player2->IsEnabled() == true)App->render->Blit(graphics, 21, 17, &andybogard, false);
	
	//Life and Animation
	App->render->MirrorBlit(graphics, 37, 25, &nohealth, 0.0f, 0, NULL);
	if (App->player2->life < 50) {
		App->render->Blit(graphics, 37, 25, &(redlife.GetCurrentFrame()), 0, false);
	}
	App->render->MirrorBlit(graphics, 37, 25, &healthp2, 0.0f, 0, NULL);
	

	//Rendering P2 Life and character square
	if (App->enemy2->IsEnabled() == true)App->render->MirrorBlit(graphics, (SCREEN_WIDTH - andybogard.w - 21), 17, &andybogard, 0.0f, 0, NULL);

	//Life and Animation
	App->render->Blit(graphics, (SCREEN_WIDTH - 37 - healthwidth), 25, &nohealth,false);
	if (App->enemy2->life < 50) {
		App->render->Blit(graphics, (SCREEN_WIDTH - 37 - healthwidth), 25, &(redlife.GetCurrentFrame()), 0, false);
	}
	App->render->Blit(graphics, (SCREEN_WIDTH - 37 - healthwidth), 25, &health, false);

	return true;
}

void ModuleUI::Score(int playerrounds, int enemyrounds){

	
	//DEFAULT RENDER
	App->render->Blit(graphics, 21, 49, &point, false);
	App->render->Blit(graphics, 39, 49, &point, false);

	App->render->Blit(graphics, (SCREEN_WIDTH - 57), 49, &point, false);
	App->render->Blit(graphics, (SCREEN_WIDTH - 39), 49, &point, false);


	//P1
	if(playerrounds == 1) App->render->Blit(graphics, 21, 49, &(redpoint.GetCurrentFrame()), 0.0f, false); 
	if(playerrounds == 2) App->render->Blit(graphics, 39, 49, &(redpoint.GetCurrentFrame()), 0.0f, false);

	if(enemyrounds == 1) App->render->Blit(graphics, (SCREEN_WIDTH - 57), 49, &(redpoint.GetCurrentFrame()), 0.0f, false);
	if (enemyrounds == 2) App->render->Blit(graphics, (SCREEN_WIDTH - 39), 49, &(redpoint.GetCurrentFrame()), 0.0f, false);

	//if (playerrounds == 2) App->render->Blit(graphics, 21, 49, &(redpoint.GetCurrentFrame()), 0.1f);
}

bool ModuleUI::WinLose(float player, float enemy, int time) {
	
	//Checking win
	if (enemy <= 0) { 
		App->player2->rounds += 1;
		return true;
	}

	if (player <= 0) {
		App->enemy2->rounds += 1;
		return true;
	}

	if (player > enemy && time <= 0) {
		App->player2->rounds++;
		return true;
	}

	if (enemy > player && time <= 0) {
		App->enemy2->rounds++;
		return true;
	}
		
	return false;
}

void ModuleUI::ChangeScene(int p1round, int p2round) {

	//Change from Scene 1 to Scene 2
	if (change1 == true) {
		if (p1round == 1 || p2round == 1) {
			App->fade->FadeToBlack(App->scene_billykane, App->scene_billykane2);
			change1 = false;
		}
	}

	//Change from Scene 2 to Scene3

		if ((p1round && p2round) == 1) {
			App->fade->FadeToBlack(App->scene_billykane2, App->scene_billykane3);
			change2 = false;
		}
	

	//CHECK THIS ISSUE. IMPORTANT
	if (p1round == 2 && p2round == 0) App->fade->FadeToBlack(App->scene_billykane2, App->p1w);
	//if ((p1round == 2 && p2round == 1) || (p2round == 2 && p1round == 1))App->fade->FadeToBlack(this, App->p1w, 3.0f);
		
}

void ModuleUI::ResetSceneChange() {
	change1 = true;
	change2 = true;
	change3 = true;
}

void ModuleUI::DebugRounds() {
	
	if (App->input->keyboard[SDL_SCANCODE_1])
	{
		App->player2->rounds++;
	}

	if (App->input->keyboard[SDL_SCANCODE_2])
	{
		App->enemy2->rounds++;
	}
}