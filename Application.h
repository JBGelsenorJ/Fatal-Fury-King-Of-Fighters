#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"


#define NUM_MODULES 26


class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleScenePaoPao;
class ModuleSceneSoundBeach;
class ModuleWelcomeScreen;
class ModulePlayer;
class ModuleFadeToBlack;
class ModulePlayerSelection;
class ModuleMusic;
class ModuleFFIntro;
class ModuleFFIntro2;
class ModuleParticles;
class ModuleCollision;
class ModuleEnemy;
class ModuleFonts;
class ModuleUI;
class ModuleP1Wins;
class ModuleP2Wins;
class ModuleBillyKane;
class ModulePlayer2;
class ModuleEnemy2;
class ModuleNeogeo;
class ModuleBillyKane2;
class ModuleBillyKane3;

class Module;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleScenePaoPao* scene_paopao;
	ModuleSceneSoundBeach* scene_soundbeach;
	ModuleWelcomeScreen* scene_welcome;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModulePlayerSelection* playerselection;
	ModuleMusic* audio;
	ModuleFFIntro* scene_intro;
	ModuleFFIntro2* scene_intro2;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleEnemy* enemy;
	ModuleFonts* fonts;
	ModuleUI* ui;
	ModuleP1Wins* p1w;
	ModuleP2Wins* p2w;
	ModuleBillyKane* scene_billykane;
	ModulePlayer2* player2;
	ModuleEnemy2* enemy2;
	ModuleNeogeo* scene_neogeo;
	ModuleBillyKane2* scene_billykane2;
	ModuleBillyKane3* scene_billykane3;


public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__