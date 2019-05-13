#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL\include\SDL.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemy2.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleScenePaoPao.h"
#include "ModuleInput.h"
#include "ModuleUI.h"

ModuleEnemy2::ModuleEnemy2()
{
	position.x = 200;
	position.y = 220;

	//IDLE
	{

		//Terry Bogard Idle Animation
		idle.PushBack({ 870, 121, 60, 102 });
		/*idle.PushBack({ 877, 601, 64, 100 });
		idle.PushBack({ 870, 121, 60, 102 });
		idle.PushBack({ 877, 601, 64, 100 });*/

		idle.speed = 0.18f;

	}

	//NORMAL MOVEMENTS (WALK AND CROUCH)
	{
		//Andy Bogard Forward Animation
		forward.PushBack({ 744, 602, 64, 99 });
		forward.PushBack({ 819, 601, 57, 100 });
		forward.PushBack({ 877, 601, 64, 100 });
		forward.PushBack({ 943, 599, 61, 102 });
		forward.speed = 0.15f;

		//Andy Bogard Backward Animation
		backward.PushBack({ 946, 476, 55, 97 });
		backward.PushBack({ 865, 474, 55, 99 });
		backward.PushBack({ 800, 471, 50, 102 });
		backward.PushBack({ 744, 473, 51, 100 });
		backward.speed = 0.15f;

		//crouch animation

		crouch.PushBack({ 946, 158, 51, 66 });
		crouch.speed = 0.2f;

	}

	//JUMP
	{

		//Andy Bogard Jump NEUTRAL Animation
		jump.PushBack({ 375, 121, 61, 102 });
		jump.PushBack({ 441, 142, 55, 81 });
		jump.PushBack({ 514, 118, 44, 106 });
		jump.PushBack({ 577, 117, 52, 95 });
		jump.PushBack({ 647, 121, 51, 85 });
		jump.PushBack({ 707, 142, 55, 81 });

		jump.speed = 0.12f;


		/*//Andy Bogard Jump FORWARD Animation

		jumpf.PushBack({ 716, 927, 60, 96 });
		jumpf.PushBack({ 716, 927, 60, 96 });
		jumpf.PushBack({ 716, 927, 60, 96 });
		jumpf.PushBack({ 716, 927, 60, 96 });
		jumpf.PushBack({ 782, 918, 59, 106 });
		jumpf.PushBack({ 841, 941, 89, 55 });
		jumpf.PushBack({ 841, 941, 89, 55 });
		jumpf.PushBack({ 841, 941, 89, 55 });

		jumpf.speed = 0.12f;

		//Terry Bogard Jump BACKWARD Animation

		jumpb.PushBack({ 716, 927, 60, 96 });
		jumpb.PushBack({ 716, 927, 60, 96 });
		jumpb.PushBack({ 716, 927, 60, 96 });
		jumpb.PushBack({ 716, 927, 60, 96 });
		jumpb.PushBack({ 782, 918, 59, 106 });
		jumpb.PushBack({ 841, 941, 89, 55 });
		jumpb.PushBack({ 841, 941, 89, 55 });
		jumpb.PushBack({ 841, 941, 89, 55 });

		jumpb.speed = 0.12f;
		}*/

		//KICK
		{
			//Terry Bogard Kick Animation
			kick.PushBack({ 449, 806, 59, 107 });
			kick.PushBack({ 512, 803, 53, 107 });
			kick.PushBack({ 31, 1150, 50, 97 });
			kick.PushBack({ 84, 1148, 59, 115 });
			kick.PushBack({ 149, 1151, 50, 108 });
			kick.PushBack({ 211, 1155, 119, 108 });
			kick.PushBack({ 342, 1152, 68, 111 });
			kick.PushBack({ 714, 925, 64, 98 });
			kick.speed = 0.18f;

			/*//Terry Bogard Kick JUMPF Animation
			kickf.PushBack({ 577, 482, 59, 74 });
			kickf.PushBack({ 577, 482, 59, 74 });
			kickf.PushBack({ 577, 482, 59, 74 });
			kickf.PushBack({ 577, 482, 59, 74 });
			kickf.PushBack({ 640, 464, 80, 114 });
			kickf.PushBack({ 737, 485, 115, 72 });
			kickf.PushBack({ 737, 485, 115, 72 });
			kickf.PushBack({ 737, 485, 115, 72 });
			kickf.speed = 0.18f;

			//Terry Bogard Kick JUMPB Animation
			kickb.PushBack({ 577, 482, 59, 74 });
			kickb.PushBack({ 577, 482, 59, 74 });
			kickb.PushBack({ 577, 482, 59, 74 });
			kickb.PushBack({ 577, 482, 59, 74 });
			kickb.PushBack({ 640, 464, 80, 114 });
			kickb.PushBack({ 737, 485, 115, 72 });
			kickb.PushBack({ 737, 485, 115, 72 });
			kickb.PushBack({ 737, 485, 115, 72 });
			kickb.speed = 0.18f;

			//Terry Bogard Kick JUMPN Animation
			kickn.PushBack({ 376, 489, 58, 75 });
			kickn.PushBack({ 376, 489, 58, 75 });
			kickn.PushBack({ 376, 489, 58, 75 });
			kickn.PushBack({ 376, 489, 58, 75 });
			kickn.PushBack({ 447, 477, 75, 97 });
			kickn.PushBack({ 447, 477, 75, 97 });
			kickn.PushBack({ 447, 477, 75, 97 });
			kickn.speed = 0.18f;

			//Terry Bogard Kick Crouch Animation
			/*kickc.PushBack({ 449, 806, 59, 107 });
			kickc.PushBack({ 512, 803, 53, 107 });
			kickc.PushBack({ 31, 1150, 50, 97 });
			kickc.PushBack({ 84, 1148, 59, 115 });
			kickc.PushBack({ 149, 1151, 50, 108 });
			kickc.PushBack({ 211, 1155, 119, 108 });
			kickc.PushBack({ 342, 1152, 68, 111 });
			kickc.PushBack({ 714, 925, 64, 98 });
			kickc.speed = 0.18f;*/
		}

		//PUNCH

		// punch animation 

		punch.PushBack({ 15, 121, 60, 101 });
		punch.PushBack({ 88, 131, 51, 92 });
		punch.PushBack({ 154, 127, 50, 97 });
		punch.PushBack({ 219, 126, 95, 97 });
		punch.speed = 0.18f;

		/*// punch jumpf animation
		punchf.PushBack({ 23, 799, 65, 111 });
		punchf.PushBack({ 23, 799, 65, 111 });
		punchf.PushBack({ 23, 799, 65, 111 });
		punchf.PushBack({ 23, 799, 65, 111 });
		punchf.PushBack({ 91, 807, 53, 104 });
		punchf.PushBack({ 147, 809, 85, 101 });
		punchf.PushBack({ 147, 809, 85, 101 });
		punchf.PushBack({ 147, 809, 85, 101 });
		punchf.speed = 0.1f;

		// punch jumpb animation
		punchb.PushBack({ 23, 799, 65, 111 });
		punchb.PushBack({ 23, 799, 65, 111 });
		punchb.PushBack({ 23, 799, 65, 111 });
		punchb.PushBack({ 23, 799, 65, 111 });
		punchb.PushBack({ 91, 807, 53, 104 });
		punchb.PushBack({ 147, 809, 85, 101 });
		punchb.PushBack({ 147, 809, 85, 101 });
		punchb.PushBack({ 147, 809, 85, 101 });
		punchb.speed = 0.1f;

		// punch jumpn animation
		punchn.PushBack({ 719, 695, 46, 46 });
		punchn.PushBack({ 719, 695, 46, 46 });
		punchn.PushBack({ 719, 695, 46, 46 });
		punchn.PushBack({ 719, 695, 46, 46 });
		punchn.PushBack({ 769, 679, 70, 97 });
		punchn.PushBack({ 769, 679, 70, 97 });
		punchn.PushBack({ 769, 679, 70, 97 });
		punchn.speed = 0.1f;

		// punch crouch animation
		punchc.PushBack({ 261, 952, 61, 67 });
		punchc.PushBack({ 320, 954, 83, 67 });
		punchc.speed = 0.1f;
		}*/

		//SPECIAL MOVEMENTS

		/*//Special Movement 1

			sm1.PushBack({ 970, 1334, 54, 106 });
			sm1.PushBack({ 897, 1325, 61, 115 });
			sm1.PushBack({ 833, 1343, 63, 97 });
			sm1.PushBack({ 679, 1359, 71, 81 });
			sm1.PushBack({ 612, 1359, 66, 81 });
			sm1.PushBack({ 547, 1359, 61, 81 });

			sm1.speed = 0.18f;
			}

			//DAMAGE
			{
			//Low damage

			lowd.PushBack({ 24, 475, 60, 100 });
			lowd.PushBack({ 88, 469, 68, 107 });
			lowd.speed = 0.15f;

			//High damage

			highd.PushBack({ 160, 479, 65, 98 });
			highd.PushBack({ 235, 478, 70, 88 });
			highd.PushBack({ 88, 469, 68, 107 });
			highd.speed = 0.15f;

			//Hihgh High damage

			hhd.PushBack({ 75, 5, 101, 91 });
			hhd.PushBack({ 185, 48, 112, 44 });
			hhd.PushBack({ 299, 44, 116, 44 });
			hhd.PushBack({ 423, 41, 97, 47 });
			hhd.PushBack({ 523, 22, 82, 70 });
			hhd.PushBack({ 614, 19, 58, 74 });
			hhd.PushBack({ 677, 11, 58, 82 });
			hhd.PushBack({ 88, 469, 68, 107 });

			hhd.speed = 0.15f;
			}*/
	}

}

ModuleEnemy2::~ModuleEnemy2()
{}

bool ModuleEnemy2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Source/Sprites/Character_Sprites/Andy_Bogard/andy.png"); // Andy Bogard Sprites
	Kick = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack5.wav");
	Punch = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Attack4.wav");
	Specialattack = App->audio->LoadFX("Source/Sound/FX/Voice/SpecialAttacks/PoweWave.wav");

	//Loading Enemy Colliders
	enemycol = App->collision->AddCollider({ 200, -250, 55, -103 }, COLLIDER_ENEMY, this);
	enemypunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY_SHOT, 0);
	enemykick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY_SHOT, 0);

	return ret;
}

// Update: draw background
update_status ModuleEnemy2::Update()
{
	Animation* current_animation = &idle;
	if (current_animation = &idle)
	{
		enemypunch->to_delete = true;
		enemykick->to_delete = true;
	}
	int speed = 2;

	//Crouch
	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT) {

		current_animation = &crouch;

	}
	else {
		//MoveForward
		if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT && position.x < 670)
		{
			if (position.x < (App->render->camera.x + 500))
			{
				current_animation = &forward;
				position.x += speed;
			}
			
		}

		//Move Backward
		if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_REPEAT && position.x > 0)
		{
			if (position.x > App->render->camera.x)
			{
				current_animation = &backward;
				position.x -= speed;
			}
			
		}

		//Jump
		if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_REPEAT || (TimeJump == true)) {

			current_animation = &jump;

			TimeJump = true;
			position.y -= jumpspeed;
			jumpspeed -= 0.2;

			if (current_animation->AnimFinished() == true)
			{
				TimeJump = false;
				position.y = 220;
				jumpspeed = 6;
			}

		}

		//Punch
		if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN || (TimePunch == true)) {
			current_animation = &punch;
			TimePunch = true;
			App->audio->PlayFX(Punch);
			enemypunch = App->collision->AddCollider({ 10, 30, 55, 10 }, COLLIDER_ENEMY_SHOT, this);
			if (current_animation->AnimFinished() == true)
			{	
				TimePunch = false;
				cont = 0;
			}
		}

		//Kick
		if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN || (KickAnim == true)) {
			KickAnim = true;
			current_animation = &kick;
			enemykick = App->collision->AddCollider({ 10, 30, 55, 10 }, COLLIDER_ENEMY_SHOT, this);
			App->audio->PlayFX(Kick);
			if (current_animation->AnimFinished() == true)
			{
				enemykick->to_delete = true;
				KickAnim = false;
				cont = 0;
			}
		}

		//Special Move

		if ((App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN) || (TimeAnim == true))
		{
			TimeAnim = true;
			int cont = SDL_GetTicks();
			current_animation = &sm1;
			forenemy = true;
			if (current_animation->AnimFinished() == true)
			{
				App->particles->AddParticle(App->particles->terryspecial1, position.x + 48, position.y - 42, COLLIDER_ENEMY_SHOT, 0);
				App->particles->AddParticle(App->particles->terryspecial2, position.x + 35, position.y - 70, COLLIDER_ENEMY_SHOT, 50);
				App->particles->AddParticle(App->particles->terryspecial3, position.x + 18, position.y - 99, COLLIDER_ENEMY_SHOT, 200);
				App->particles->AddParticle(App->particles->terryspecial4, position.x + 5, position.y - 70, COLLIDER_ENEMY_SHOT, 400);
				App->particles->AddParticle(App->particles->terryspecial5, position.x - 13, position.y - 42, COLLIDER_ENEMY_SHOT, 600);
				TimeAnim = false;
				App->particles->cont = 0;
			}
		}



	}

	SDL_Rect r = current_animation->GetCurrentFrame();
	enemycol->SetPos(position.x, position.y);

	if (App->player2->position.x > position.x)
	{
		App->render->Blit(graphics, position.x, position.y - r.h, &r);
	}

	if (App->player2->position.x < position.x)
	{
		App->render->MirrorBlit(graphics, position.x, position.y - r.h, &r, 1.0f, 0, NULL, true);
	}

	if (App->player2->position.x > position.x) {
		enemypunch->SetPos(position.x + 40, position.y - 90);
		enemykick->SetPos(position.x + 40, position.y - 60);
	}
	if (App->player2->position.x < position.x) {
		enemypunch->SetPos(position.x - 40, position.y - 90);
		enemykick->SetPos(position.x - 40, position.y - 60);
	}

	return UPDATE_CONTINUE;
}

void ModuleEnemy2::OnCollision(Collider* c1, Collider* c2) {

	if (enemycol == c1 && c2->type == COLLIDER_PLAYER && App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_REPEAT && App->player2->position.y == position.y && position.x > App->player2->position.x)
	{
		App->player2->position.x -= 3;

	}

	if (enemycol == c1 && c2->type == COLLIDER_PLAYER && App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT && App->player2->position.y == position.y && position.x < App->player2->position.x)
	{
		App->player2->position.x += 3;

	}

	if (enemypunch == c1 && c2->type == COLLIDER_PLAYER && cont < 1)
	{
		enemypunch->to_delete = true;
		App->player2->life -= 25;
		cont++;

	}

	if (enemykick == c1 && c2->type == COLLIDER_PLAYER && cont < 1)
	{
		if (enemykick->callback != nullptr)
		{
			enemykick->to_delete = true;
		}
		App->player2->life -= 25;
		cont++;

	}

	else if (enemycol == c1 && c2->type == COLLIDER_WALL)
	{
		position.x += 15;
	}

}


bool ModuleEnemy2::CleanUp()
{
	SDL_DestroyTexture(graphics);
	App->player2->Disable();
	LOG("Unloading Terry From Scene");

	return true;
}