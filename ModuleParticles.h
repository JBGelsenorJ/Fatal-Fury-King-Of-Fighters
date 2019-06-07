#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleMusic.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;

struct Particle
{
	Collider* collider;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	int born = 0;
	int life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
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
	void OnCollision(Collider* c1, Collider* c2);
	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, int delay);
	int cont;

private:

	SDL_Texture * graphics = nullptr; 
	SDL_Texture * graphics2 = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:
	Mix_Chunk * fx;
	Particle andyspecial1;
	Particle andyspecial2;

};

#endif // __MODULEPARTICLES_H__