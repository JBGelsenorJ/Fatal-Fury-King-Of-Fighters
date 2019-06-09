Alpha version of our recreation of Fatal Fury: King of Fighter.

Repository: https://github.com/JBGelsenorJ/Fatal-Fury-King-Of-Fighters
Webpage(done with github pages):https://jbgelsenorj.github.io/Fatal-Fury-King-Of-Fighters/
Team: 

 - Carlos Redolar Torres - https://github.com/carlosredolar
 - Javier Damián Belda González - https://github.com/JBGelsenorJ
 - Germán Insua Perdomo - https://github.com/Germanins6
 - Christian Piña López - https://github.com/christianpi4

Changelog:

0.1.0- Added first level and operative scroll, Audio module created but unable to make it play music.
0.1.1- Convertion a Zip and fx added in music module
0.1.2- Added animations and modules to do it
0.2- Music fixed and added different scenes
0.3- Particles Module added, fixed animation to make each combo animation on one single key_down instead of holding the key.
0.3.9- Added Collision Module, not able to make collisions functional (will be operative in 0.4), godmode added and limited for the player to don't be out 
the map.
0.5- Added UI, Font Module, Fixed Errors with Colliders now functional, State machine added and working 
0.6 -Added New map and changed first player for Andy Bogard.
0.7 - Added SceneBillyKane(morning), Added Andy in Player and Enemy, New State Machine working, added GamePad Control, Life and time UI, fullscreen
1.0 - Added all movements (crouch punch, crouch kick, jump punch, jump kick...), added SceneBillyKane(sunset, night), added shake and slowdown, added 3 new special atacks, added rounds system, added new sounds 


Controls:

Controller:
Joystick: Move and crouch
A:Kick
B:Punch
Down + Right + B: HISHO KEN (Andy's Power Wave) 
Down + left + B: ZANEI KEN (Dash)
Start: Next scene

Keyboard (not intended to be the way of playing):

ESC: Close Game
ESPACE: Next scene (exept for player selection there you choose with ENTER)

Player1 Controls:
D: Move Right
A: Move Left
W: Jump (need to be fixed)
S: Crouch
F: HISHO KEN (Andy's Power Wave) 
C: ZANEI KEN (Dash)
X: SHORYU DAN (Windmill move)
T: Punch
R: Kick

Player 2 Controls:
L: Move Right
J: Move Left
I: Jump (need to be fixed)
K: Crouch
H: HISHO KEN (Andy's Power Wave)
M: ZANEI KEN (Dash)
N: SHORYU DAN (Windmill move)
Y: Punch
U: Kick

Debug Mode:
F1: Show and hide colliders
F4: Player 1 wins round instant
F5: Turn on/off godmode



Using the following SDL libraries:
SDL: https://www.libsdl.org/
SDL_Image: https://www.libsdl.org/projects/SDL_image/
SDL_Mixer: https://www.libsdl.org/projects/SDL_mixer/
