#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "p2Qeue.h"
#include <iostream>
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePlayer2.h"
#include "ModuleEnemy2.h"


ModuleInput::ModuleInput() : Module()
{
	//Starting Keyboard inputs
	for (uint i = 0; i < MAX_KEYS; ++i) {
		keyboard[i] = KEY_IDLE;
	}
	
}

ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	
	bool ret = true;
	SDL_Init(0);


	//Checking all InitSubSystem
	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}   //Events

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) 
	{
		LOG("SDL_GAMECONTROLLER could not initialize! SDL_Error: %s\n", SDL_GetError());
			ret = false;
	}   //Gamepads

	if (SDL_InitSubSystem(SDL_INIT_HAPTIC) < 0) {
		LOG("SDL_Haptic could not initialize! SDL_Error: %s\n", SDL_GetError());
			ret = false;
	}	   //Haptics

	

	/*
	if (SDL_NumJoysticks() < 1) {
		LOG("No Joysticks or Gamepads connected!\n");
	}
	else {
		//Loading devices.(Must be connected and will be open). -- GAMEPADS
		gamepad1 = SDL_GameControllerOpen(0);
		gamepad2 = SDL_GameControllerOpen(1);

		if (gamepad1 == NULL || gamepad2 == NULL) {
			LOG("Couldn't Open Gamepad Controller! SDL Error: %s\n", SDL_GetError());
		}
		
	}
	*/

	return ret;
}

bool ModuleInput::external_input()
{

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		//Switch events
		switch (event.type) {

			//If device are connected
		case SDL_CONTROLLERDEVICEADDED:
			LOG("GAMEPAD CONNECTED");
			if(gamepad1 == NULL){
					gamepad1 = SDL_GameControllerOpen(0);
					if(SDL_JoystickIsHaptic(SDL_GameControllerGetJoystick(gamepad1)) > 0) {
							haptic = SDL_HapticOpenFromJoystick(SDL_GameControllerGetJoystick(gamepad1));
							if (haptic != NULL) LOG("HAPTIC SUCCESS");
							if (SDL_HapticRumbleInit(haptic) < 0) LOG("Error init rumble in haptic");
							SDL_HapticRumblePlay(haptic, 0.3f, 600);
					}
				} else {
					if (gamepad2 == NULL) {
						gamepad2 = SDL_GameControllerOpen(1);
						if (SDL_JoystickIsHaptic(SDL_GameControllerGetJoystick(gamepad2)) > 0) {
							haptic2 = SDL_HapticOpenFromJoystick(SDL_GameControllerGetJoystick(gamepad2));
							if (haptic2 != NULL) LOG("HAPTIC SUCCESS");
							if (SDL_HapticRumbleInit(haptic2) < 0) LOG("Error init rumble in haptic");
							SDL_HapticRumblePlay(haptic2, 0.3f, 600);
						}
					}
				
				}
			break;

			//If device are removed
		case SDL_CONTROLLERDEVICEREMOVED:
			LOG("GAMEPAD REMOVED");
			if (gamepad2 != NULL) {
				LOG("WE ARE REMOVING PLAYER 2 CONTROLLER");
					SDL_HapticClose(haptic2);
					SDL_GameControllerClose(gamepad2);
					gamepad2 = NULL;
					haptic2 = NULL;
				}
			else {
				if (gamepad1 != NULL) {
					LOG("WE ARE REMOVING PLAYER 1 CONTROLLER");
					SDL_HapticClose(haptic);
					SDL_GameControllerClose(gamepad1);
					gamepad1 = NULL;
					haptic = NULL;
				}
			}
			break;
		}





		//CONTROLS FOR KEYBOARD --- KEYUP
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return false;
				break;
			//PLAYER 1 KEYBOARD CONTROLS
			case SDLK_s:
				inputs.Push(IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_w:
				up = false;
				break;
			case SDLK_a:
				inputs.Push(IN_LEFT_UP);

				left = false;
				break;
			case SDLK_d:
				inputs.Push(IN_RIGHT_UP);

				right = false;
				break;
			
			//PLAYER 2 KEYBOARD CONTROLS
			case SDLK_k:
				inputs2.Push(IN_CROUCH_UP2);
				down2 = false;
				break;
			case SDLK_i:
				up2 = false;
				break;
			case SDLK_j:
				inputs2.Push(IN_LEFT_UP2);
				left2 = false;
				break;
			case SDLK_l:
				inputs2.Push(IN_RIGHT_UP2);
				right2 = false;
				break;
			}
		}
		//CONTROLS FOR KEYBOARD --- KEYDOWN
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
				//PLAYER 1
			case SDLK_r:
				inputs.Push(IN_R);
				
				break;
			case SDLK_t:
				inputs.Push(IN_T);
				break;
			case SDLK_f:
				inputs.Push(IN_F);
				break;
			case SDLK_w:
				up = true;
				break;
			case SDLK_s:
				down = true;
				break;
			case SDLK_a:
				left = true;
				break;
			case SDLK_d:
				right = true;
				break;
			case SDLK_c:
				inputs.Push(IN_C);
				break;

				//PLAYER 2

			case SDLK_u:
				inputs2.Push(IN_U);
				break;
			case SDLK_y:
				inputs2.Push(IN_Y);
				break;
			case SDLK_h:
				inputs2.Push(IN_H);
				break;
			case SDLK_i:
				up2 = true;
				break;
			case SDLK_k:
				down2 = true;
				break;
			case SDLK_j:
				left2 = true;
				break;
			case SDLK_l:
				right2 = true;
				break;
			case SDLK_m:
				sm22 = true;
				break;
			}
		}

		
		//GAMEPADS AXIS CONTROL
		if (event.type == SDL_CONTROLLERAXISMOTION) {
			//GAMEPAD 1
			if (event.caxis.which == 0) { 
				if (event.caxis.axis == 0)
				{
					//Left of dead zone
					if (event.caxis.value < -GAMEPAD_DEAD_ZONE)
					{
						left = true;
						right = false;
					} 
					//Right of dead zone
					else if (event.caxis.value > GAMEPAD_DEAD_ZONE)
					{
						right = true;
						left = false;
					}
					else
					{
						left = false;
						right = false;
					}
				}
				else if (event.caxis.axis == 1)
				{
					//Below of dead zone
					if (event.caxis.value < -GAMEPAD_DEAD_ZONE)
					{
						down = false;
						up = true;
					}
					//Above of dead zone
					else if (event.caxis.value > GAMEPAD_DEAD_ZONE)
					{
						up = false;
						down = true;
					}
					else
					{
						down = false;
						up = false;
					}
				}
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//GAMEPAD 2
			if (event.caxis.which == 1) { //En el gamepad 2
				if (event.caxis.axis == 0)
				{
					//Left of dead zone
					if (event.caxis.value < -GAMEPAD_DEAD_ZONE)
					{
						left2 = true;
						right2 = false;
					}
					//Right of dead zone
					else if (event.caxis.value > GAMEPAD_DEAD_ZONE)
					{
						right2 = true;
						left2 = false;
					}
					else
					{
						left2 = false;
						right2 = false;
					}
				}
				else if (event.caxis.axis == 1)
				{
					//Below of dead zone
					if (event.caxis.value < -GAMEPAD_DEAD_ZONE)
					{
						down2 = false;
						up2 = true;
					}
					//Above of dead zone
					else if (event.caxis.value > GAMEPAD_DEAD_ZONE)
					{
						up2 = false;
						down2 = true;
					}
					else
					{
						down2 = false;
						up2 = false;
					}
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		//GAMEPADS BUTTON CONTROLS
		if (event.type == SDL_CONTROLLERBUTTONDOWN) {
			if (event.cbutton.which == 0) {
				//STUFF FOR GAMEPAD1
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {		//SQUARE(DUALSHOCK) X(XBOX) PUNCH
					inputs.Push(IN_T);
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {		//SQUARE(DUALSHOCK) Y(XBOX) PUNCH
					inputs.Push(IN_F);
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {		//SQUARE(DUALSHOCK) B(XBOX) PUNCH
					inputs.Push(IN_R);
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {		//SQUARE(DUALSHOCK) A(XBOX) PUNCH
					inputs.Push(IN_CROUCH_DOWN);
				}
			}
			if (event.cbutton.which == 1) {
				//STUFF FOR GAMEPAD2
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {		//SQUARE(DUALSHOCK) X(XBOX) PUNCH
					inputs2.Push(IN_U);
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {		//SQUARE(DUALSHOCK) Y(XBOX) PUNCH
					inputs2.Push(IN_H);
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {		//SQUARE(DUALSHOCK) B(XBOX) PUNCH
					inputs2.Push(IN_Y);
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {		//SQUARE(DUALSHOCK) A(XBOX) PUNCH
					inputs2.Push(IN_CROUCH_DOWN);
				}
			}
		}


		//PLAYER 1
		if (left && right)
			inputs.Push(IN_LEFT_AND_RIGHT);
		{
			if (left)
				inputs.Push(IN_LEFT_DOWN);
			if (right)
				inputs.Push(IN_RIGHT_DOWN);
		}

		if (!left)
			inputs.Push(IN_LEFT_UP);
		if (!right)
			inputs.Push(IN_RIGHT_UP);
		if (!down)
			inputs.Push(IN_CROUCH_UP);

		if (up && down)
			inputs.Push(IN_JUMP_AND_CROUCH);
		else
		{
			if (down)
				inputs.Push(IN_CROUCH_DOWN);
			if (up)
				inputs.Push(IN_JUMP);
		}

		//PLAYER 2
		if (left2 && right2)
			inputs2.Push(IN_LEFT_AND_RIGHT2);
		{
			if (left2)
				inputs2.Push(IN_LEFT_DOWN2);
			if (right2)
				inputs2.Push(IN_RIGHT_DOWN2);
		}
		///////////////////////////////////////
		if (!left2)
			inputs2.Push(IN_LEFT_UP2);
		if (!right2)
			inputs2.Push(IN_RIGHT_UP2);
		if (!down2)
			inputs2.Push(IN_CROUCH_UP2);
		////////////////////////////////////////
		if (up2 && down2)
			inputs2.Push(IN_JUMP_AND_CROUCH2);
		else
		{
			if (down2)
				inputs2.Push(IN_CROUCH_DOWN2);
			if (up2)
				inputs2.Push(IN_JUMP2);
		}
	}
	return true;
}

void ModuleInput::internal_input(p2Qeue<player_inputs>& inputs, p2Qeue<player_inputs>& inputs2)
{
	//PLAYER 1
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME)
		{
			inputs.Push(IN_JUMP_FINISH);
			App->player2->position.y = 220;
			App->player2->jumpspeed = 6;
			App->player2->animdone = true;
			App->player2->playerjumpnkick->to_delete = true;
			App->player2->colcreated = true;
			App->player2->playerjumpnpunch->to_delete = true;
			jump_timer = 0;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME)
		{
			App->player2->colcreated = true;
			App->player2->playerpunch->to_delete = true;
			inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}

	if (punchc_timer > 0)
	{
		if (SDL_GetTicks() - punchc_timer > PUNCHC_TIME)
		{
			App->player2->colcreated = true;
			App->player2->playercrouchpunch->to_delete = true;
			inputs.Push(IN_PUNCH_CROUCH_FINISH);
			punchc_timer = 0;
		}
	}

	if (kick_timer > 0)
	{
		if (SDL_GetTicks() - kick_timer > KICK_TIME)
		{
			inputs.Push(IN_KICK_FINISH);
			App->player2->position.y = 220;
			App->player2->kick_jumpspeed = 6;
			App->player2->animdone = true;
			App->player2->colcreated = true;
			App->player2->playerkick->to_delete = true;
			kick_timer = 0;
		}
	}

	if (kickc_timer > 0)
	{
		if (SDL_GetTicks() - kickc_timer > KICKC_TIME)
		{
			inputs.Push(IN_KICK_CROUCH_FINISH);
			App->player2->colcreated = true;
			App->player2->playercrouchkick->to_delete = true;
			kickc_timer = 0;
		}
	}

	if (sp1_timer > 0)
	{
		if (SDL_GetTicks() - sp1_timer > SP1_TIME)
		{
			inputs.Push(IN_SM1_FINISH);
			sp1_timer = 0;


		}
		if (SDL_GetTicks() - sp1_timer > SP1_TIME + 500)
		{
			App->player2->Activesm1 = true;
			App->enemy2->Activesm1 = true;

		}

	}

	//PLAYER 2
	if (jump_timer2 > 0)
	{
		if (SDL_GetTicks() - jump_timer2 > JUMP_TIME)
		{
			inputs2.Push(IN_JUMP_FINISH2);
			App->enemy2->position.y = 220;
			App->enemy2->jumpspeed = 6;
			App->enemy2->animdone = true;
			App->enemy2->enemyjumpnpunch->to_delete = true;
			App->enemy2->enemyjumpnkick->to_delete = true;
			App->enemy2->colcreated = true;
			jump_timer2 = 0;
		}
	}

	if (punch_timer2 > 0)
	{
		if (SDL_GetTicks() - punch_timer2 > PUNCH_TIME)
		{
			inputs2.Push(IN_PUNCH_FINISH2);
			punch_timer2 = 0;
			App->enemy2->colcreated = true;
			App->enemy2->enemypunch->to_delete = true;
		}
	}

	if (punchc_timer2 > 0)
	{
		if (SDL_GetTicks() - punchc_timer2 > PUNCHC_TIME)
		{
			App->enemy2->enemycrouchpunch->to_delete = true;
			App->enemy2->colcreated = true;
			inputs2.Push(IN_PUNCH_CROUCH_FINISH2);
			punchc_timer2 = 0;
		}
	}

	if (kick_timer2 > 0)
	{
		if (SDL_GetTicks() - kick_timer2 > KICK_TIME)
		{
			inputs2.Push(IN_KICK_FINISH2);
			kick_timer2 = 0;
			App->enemy2->colcreated = true;
			App->enemy2->enemykick->to_delete = true;
		}
	}

	if (kickc_timer2 > 0)
	{
		if (SDL_GetTicks() - kickc_timer2 > KICKC_TIME)
		{
			App->enemy2->enemycrouchkick->to_delete = true;
			App->enemy2->colcreated = true;
			inputs2.Push(IN_KICK_CROUCH_FINISH2);
			kickc_timer2 = 0;
		}
	}
	if (sp1_timer2 > 0)
	{
		if (SDL_GetTicks() - sp1_timer2 > SP1_TIME)
		{
			inputs2.Push(IN_SM1_FINISH2);
			sp1_timer2 = 0;
		}
		if (SDL_GetTicks() - sp1_timer2 > SP1_TIME + 500)
		{
			App->player2->Activesm1 = true;
			App->enemy2->Activesm1 = true;

		}
	}

	if (ldamage_timer > 0)
	{
		if (SDL_GetTicks() - ldamage_timer > LDAMAGE_TIME)
		{
			inputs.Push(IN_LDAMAGE_FINISH);
			ldamage_timer = 0;
			App->player2->lowdamage2 = false;
		}
	}

	if (hdamage_timer > 0)
	{
		if (SDL_GetTicks() - hdamage_timer > HDAMAGE_TIME)
		{
			inputs.Push(IN_HDAMAGE_FINISH);
			hdamage_timer = 0;
			App->player2->highdamage2 = false;
		}
	}

	if (hhdamage_timer > 0)
	{
		if (SDL_GetTicks() - hhdamage_timer > HHDAMAGE_TIME)
		{
			inputs.Push(IN_HHDAMAGE_FINISH);
			hhdamage_timer = 0;
			App->player2->hhdamage2 = false;
		}
	}

	if (ldamage_timer2 > 0)
	{
		if (SDL_GetTicks() - ldamage_timer2 > LDAMAGE_TIME)
		{
			inputs2.Push(IN_LDAMAGE_FINISH2);
			ldamage_timer2 = 0;
			App->enemy2->lowdamage1 = false;
		}
	}

	if (hdamage_timer2 > 0)
	{
		if (SDL_GetTicks() - hdamage_timer2 > HDAMAGE_TIME)
		{
			inputs2.Push(IN_HDAMAGE_FINISH2);
			hdamage_timer2 = 0;
			App->enemy2->highdamage1 = false;
		}
	}

	if (hhdamage_timer2 > 0)
	{
		if (SDL_GetTicks() - hhdamage_timer2 > HHDAMAGE_TIME)
		{
			inputs2.Push(IN_HHDAMAGE_FINISH2);
			hhdamage_timer2 = 0;
			App->enemy2->hhdamage1 = false;
		}
	}

}
// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	//Put inputs to states
	if (external_input() == false) { return update_status::UPDATE_STOP; }
	else {
		internal_input(inputs, inputs2);
	}

	return update_status::UPDATE_CONTINUE;

	SDL_PumpEvents();

}

update_status ModuleInput::PostUpdate() {
	
	key = -1;
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{

	//Cleaning Gamepads
	SDL_GameControllerClose(gamepad1);
	SDL_GameControllerClose(gamepad2);

	gamepad1 = NULL;
	gamepad2 = NULL;

	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	
	return true;

}