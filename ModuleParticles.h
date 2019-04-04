#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleMusic.h"

#define MAX_ACTIVE_PARTICLES 10000000

struct SDL_Texture;

struct Particle
{
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	int born = 0;
	int life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y, int delay);

private:

	SDL_Texture * graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:
	Mix_Chunk * fx;
	Particle terryspecial1;
	Particle terryspecial2;
	Particle terryspecial3;
	Particle terryspecial4;
	Particle terryspecial5;
};

#endif // __MODULEPARTICLES_H__