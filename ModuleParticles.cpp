#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleMusic.h"
#include "ModuleCollision.h"
#include "ModuleEnemy2.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"

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
	//App->player->forplayer = true;
	graphics = App->textures->Load("Source/Sprites/Character_Sprites/Andy_Bogard/andy.png");

	// Special1
	andyspecial1.anim.PushBack({ 327, 375, 23, 26 });
	andyspecial1.anim.PushBack({ 362, 354, 39, 68 });
	andyspecial1.anim.PushBack({ 403, 355, 52, 65 });
	andyspecial1.anim.PushBack({ 458, 342, 67, 94 });
	andyspecial1.anim.PushBack({ 533, 340, 49, 96 });
	andyspecial1.anim.PushBack({ 458, 342, 67, 94 });
	andyspecial1.anim.PushBack({ 533, 340, 49, 96 });
	andyspecial1.anim.PushBack({ 721, 342, 73, 101 });
	andyspecial1.anim.loop = false;
	andyspecial1.anim.speed = 0.07f;
	andyspecial1.life = 4000;
	andyspecial1.fx_played = true;
	andyspecial1.speed.x = 0;
	andyspecial1.born = 0;

	andyspecial2.anim.PushBack({ 327, 375, 23, 26 });
	andyspecial2.anim.PushBack({ 362, 354, 39, 68 });
	andyspecial2.anim.PushBack({ 403, 355, 52, 65 });
	andyspecial2.anim.PushBack({ 458, 342, 67, 94 });
	andyspecial2.anim.PushBack({ 533, 340, 49, 96 });
	andyspecial2.anim.PushBack({ 458, 342, 67, 94 });
	andyspecial2.anim.PushBack({ 533, 340, 49, 96 });
	andyspecial2.anim.PushBack({ 721, 342, 73, 101 });
	andyspecial2.anim.loop = false;
	andyspecial2.anim.speed = 0.07f;
	andyspecial2.life = 4000;
	andyspecial2.fx_played = true;
	andyspecial2.speed.x = 0;
	andyspecial2.born = 0;


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
			if (App->enemy2->position.x > App->player2->position.x){
				App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			}
			if (App->enemy2->position.x < App->player2->position.x) {
				App->render->MirrorBlit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()),1,0,0,0);
			}
			if (p->fx_played == false)
			{
				p->fx_played = true;
				
				//SPECIAL ATTACK HISHOKEN FX
				fx = App->audio->LoadFX("Source/Sound/FX/Voice/SpecialAttacks/Hishoken.wav");
				App->audio->PlayFX(fx);
				Mix_VolumeChunk(fx, 120);

			}
		}
	}
	if (App->enemy2->position.x > App->player2->position.x) {
		andyspecial1.speed.x = 2;


	}
	if (App->enemy2->position.x < App->player2->position.x ) {
		andyspecial1.speed.x = -2;


	}
	if (App->enemy2->position.x > App->player2->position.x) {
		andyspecial2.speed.x = -2;


	}
	if (App->enemy2->position.x < App->player2->position.x ) {
		andyspecial2.speed.x = 2;

	}

	return UPDATE_CONTINUE;
}
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
		if (c2->type == COLLIDER_ENEMY && cont < 1)
		{
			App->render->StartCameraShake(250, 3);
			App->render->UpdateCameraShake();
			App->enemy2->life -=  30;
			App->player2->hit = true;
			App->player2->hhdamage2 = true;
			App->input->inputs2.Push(IN_HHDAMAGE2);
			cont++;
		}
		if (c2->type == COLLIDER_PLAYER && cont < 1)
		{
			App->render->StartCameraShake(250, 3);
			App->render->UpdateCameraShake();
			App->player2->life -= 30;
			App->enemy2->hit = true;
			App->enemy2->hhdamage1 = true;
			App->input->inputs.Push(IN_HHDAMAGE);
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


