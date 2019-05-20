#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"


#define NUM_MODULES 23


class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleWelcomeScreen;
class ModuleFadeToBlack;
class ModulePlayerSelection;
class ModuleMusic;
class ModuleFFIntro;
class ModuleFFIntro2;
class ModuleParticles;
class ModuleCollision;
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
class ModuleSlowdown;

class Module;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleWelcomeScreen* scene_welcome;
	ModuleFadeToBlack* fade;
	ModulePlayerSelection* playerselection;
	ModuleMusic* audio;
	ModuleFFIntro* scene_intro;
	ModuleFFIntro2* scene_intro2;
	ModuleParticles* particles;
	ModuleCollision* collision;
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
	ModuleSlowdown* slowdown;


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