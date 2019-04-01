#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleMusic.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Source/Sprites/Character_Sprites/Terry_Bogard/terry.png");

	// Special1
	terryspecial1.anim.PushBack({ 612, 275, 19, 69 });
	terryspecial1.anim.PushBack({ 578, 248, 23, 73 });
	terryspecial1.anim.PushBack({ 645, 219, 19, 96 }); 
	terryspecial1.anim.loop = true;
	terryspecial1.anim.speed = 0.05f;
	terryspecial1.life = 1000;
	terryspecial1.fx_played = true;
	terryspecial1.speed.x = 1;	
	terryspecial1.born = 0;


	terryspecial2.anim.PushBack({ 645, 219, 19, 96 });
	terryspecial2.anim.PushBack({ 578, 248, 23, 73 });
	terryspecial2.anim.PushBack({ 612, 275, 19, 69 });
	terryspecial2.anim.loop = true;
	terryspecial2.anim.speed = 0.05f;
	terryspecial2.life = 1000;
	terryspecial2.fx_played = true;
	terryspecial2.speed.x = 1;
	terryspecial2.born = 0;
	return true;

	terryspecial3.anim.PushBack({ 612, 275, 19, 69 });
	terryspecial3.anim.PushBack({ 578, 248, 23, 73 });
	terryspecial3.anim.PushBack({ 645, 219, 19, 96 });
	terryspecial3.anim.loop = true;
	terryspecial3.anim.speed = 0.05f;
	terryspecial3.life = 1000;
	terryspecial3.fx_played = true;
	terryspecial3.speed.x = 1;
	terryspecial3.born = 0;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
				fx = App->audio->LoadFX("Source/Sound/FX/Voice/SpecialAtacks/PowerWave.wav");
				App->audio->PlayFX(fx);

			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	active[last_particle++] = p;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	return ret;
}