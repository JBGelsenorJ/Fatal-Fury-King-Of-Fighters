#ifndef __ModuleControls_H__
#define __ModuleControls_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"
#include "Application.h"
#include "p2Point.h"

struct SDL_Texture;

/*enum IntroAnimationState {

	Enter,
	GoBack,
	Fighting,
	Done

};*/

/*struct AnimationObject {

	iPoint position;
	SDL_Rect rect;
	float scale;

};*/

class ModuleControls : public Module
{
public:
	ModuleControls();
	~ModuleControls();

	bool Start();
	update_status Update();
	bool CleanUp();

	void RenderWords();

public:

	SDL_Texture * graphics = nullptr;
	//SDL_Rect borders;
	Animation terry;
	Animation andy;
	Animation joe;
	Animation background;
	Animation controls;
	Mix_Music* introsong;
	/*iPoint positionplayer;
	iPoint positionrock;
	iPoint positiontitle;*/
	float pos_terry_x;
	float pos_andy_x;
	float pos_joe_x;
	float pos_background_x;
	float pos_controls_x;
	float pos_terry_y;
	float pos_andy_y;
	float pos_joe_y;
	float pos_background_y;
	float pos_controls_y;

private:

	/*AnimationObject terry1;
	AnimationObject andy1;
	AnimationObject joe1;
	AnimationObject controls1;
	IntroAnimationState animationState;
	int step = 0;
	iPoint fterry;
	iPoint fandy;
	iPoint fjoe;
	iPoint fcontrols;*/
};


#endif // __ModuleControls_H__