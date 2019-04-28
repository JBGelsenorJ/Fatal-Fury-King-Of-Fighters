#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleMusic.h"
#include "ModuleCollision.h"
#include "ModuleEnemy.h"
#include "ModulePlayer.h"

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
	terryspecial1.anim.PushBack({ 609, 275, 19, 40 });
	terryspecial1.anim.loop = false;
	terryspecial1.anim.speed = 0.02f;
	terryspecial1.life = 4000;
	terryspecial1.fx_played = true;
	terryspecial1.speed.x = 2;
	terryspecial1.born = 0;

	terryspecial2.anim.PushBack({ 577, 248, 18, 68 });
	terryspecial2.anim.loop = false;
	terryspecial2.anim.speed = 0.04f;
	terryspecial2.life = 4000;
	terryspecial2.fx_played = false;
	terryspecial2.speed.x = 2;
	terryspecial2.born = 0;

	terryspecial3.anim.PushBack({ 643, 219, 21, 96 });
	terryspecial3.anim.loop = false;
	terryspecial3.anim.speed = 0.06f;
	terryspecial3.life = 4000;
	terryspecial3.fx_played = false;
	terryspecial3.speed.x = 2;
	terryspecial3.born = 0;

	terryspecial4.anim.PushBack({ 577, 248, 18, 68 });
	terryspecial4.anim.loop = false;
	terryspecial4.anim.speed = 0.08f;
	terryspecial4.life = 4000;
	terryspecial4.fx_played = false;
	terryspecial4.speed.x = 2;
	terryspecial4.born = 0;

	terryspecial5.anim.PushBack({ 609, 275, 19, 40 });
	terryspecial5.anim.loop = false;
	terryspecial5.anim.speed = 0.1f;
	terryspecial5.life = 4000;
	terryspecial5.fx_played = false;
	terryspecial5.speed.x = 2;
	terryspecial5.born = 0;


	return true;
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
				fx = App->audio->LoadFX("Source/Sound/FX/Voice/SpecialAttacks/PowerWave.wav");

				App->audio->PlayFX(fx);

			}
		}
	}

	return UPDATE_CONTINUE;
}
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
		if (c2->type == COLLIDER_ENEMY && cont < 1)
		{
			App->enemy->life -= 30;
			cont++;
		}
		if (c2->type == COLLIDER_PLAYER && cont < 1)
		{
			App->player->life -= 33;
			cont++;
		}
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}
void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, int delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}
bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((int)(SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;
	collider->SetPos(position.x, position.y);

	return ret;
}


