#ifndef __ModulFFIntro_H__
#define __ModulFFIntro_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"
#include "Application.h"
#include "p2Point.h"

struct SDL_Texture;

enum IntroAnimationState{
	
	Enter,
	GoBack,
	Fighting,
	Done

};

struct AnimationObject {

	iPoint position;
	SDL_Rect rect;
	float scale;
	
};

class ModuleFFIntro : public Module
{
public:
	ModuleFFIntro();
	~ModuleFFIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

	void RenderWords();

public:

	SDL_Texture * graphics = nullptr;
	Animation introwin;
	//SDL_Rect rock;
	SDL_Rect borders;
	Animation start;
	//Animation player;
	
	Mix_Music* introsong;
	iPoint positionplayer;
	iPoint positionrock;

private:

	AnimationObject rock;
	AnimationObject player;
	IntroAnimationState animationState;
	int step = 0;
	iPoint frock;
	iPoint fplayer;
};


#endif // __ModulFFIntros_H__