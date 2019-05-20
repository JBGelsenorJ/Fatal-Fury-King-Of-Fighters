#ifndef __ModuleTime_H__
#define __ModuleTime_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2Qeue.h"
#include "ModuleMusic.h"


struct SDL_Texture;

class ModuleUI : public Module
{
public:

	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool Timer();
	bool DrawLife();
	bool Score(int,int, float, float, int, int);

public:
	//Shape for Timer
	SDL_Rect timerbackground;

	//Textures and font sprites
	SDL_Texture* graphics;
	SDL_Rect timetext;
	SDL_Rect health;
	SDL_Rect healthp2;
	SDL_Rect nohealth;
	SDL_Rect redhealth;
	SDL_Rect point;
	SDL_Rect pointred;
	SDL_Rect pointscored;
	SDL_Rect andybogard;
	SDL_Rect terrybogard;

	Animation redlife;
	Animation redpoint;

	int countdown = -1;
	int scorefont = -1;
	int healthwidth = 0;

	//Sound and FX
	Mix_Chunk* finalcountdown;

	//Timer
	int start_delay = 2000;
	float starting = 0.0f;
	uint time;
	uint starttime;

	char time_text[10];
	
	char p1score[10];
	char p2score[10];
};

#endif