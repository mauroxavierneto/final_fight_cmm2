# final_fight_cmm2

This is a non-profit port of the arcade game Final Fight from CAPCOM, made 100% in MMBasic for the Colour Maximite 2.

I don't have any rights to the images, sound effects and music in this repository, but I'm counting on the tolerance of CAPCOM about your huge fan games base already present.

THIS GAME IS A WORK IN PROGRESS AND SEE IN THE CHANGELOG WHAT IS THE LAST STAGE IMPLEMENTED. THE OTHER ROUNDS ARE ON THE WAY...

PS.: The current enemies on the CMM2 G1 probably will not be implemented because of some memory restrictions: Simons, Wong Who and the appearance of the Andore Father, Uncle and Granpa outside the ring stage. I'm still not sure if I can do something about this yet.

Changelog:

2021-08-03
- Implemented Round 2-3 (still missing the rolling drum cans)

2021-08-02
- Tweaked collision hitboxes
- Fixed collisions in the player jump attacks
- Fixed intro and ending cutscenes in Round 2-1
- Fixed ending cutscene in the Round 2-2

2021-07-22
- Implemented Round 2-2
- Fixed background subway on the Round 2-1 

2021-07-19
- Implemented Round 2-1 with background subway

2021-07-17
- Implemented the Andore "family"
- Implemented Damnd dying
- Round 1 clear routine now is called immediately as Damnd dies, killing all enemies on the screen

2021-07-14
- Optimized decision tree and collision blocks of all enemies
- Optimized player's control performance
- Optimized player's control schema and was separated from the main source (PLAYER CONTROL.INC)
- Optimized object renderer
- Optimized performance of all particles
- 16-bit mode little optimizations (but still have slowdown)

2021-07-13
- Fixed controller auto-detection start routine
- Fixed I2C error when none controller was connected
- Fixed control type selection in the game menu
- Fixed the control detection in-game
- Removed white start screen used to synchronize capture card for YouTube video

2021-07-12
- Fixed the final cutscenes to the players jump backwards to avoid foreground artefacts
- Fixed Damnd laughing outside the screen
- Fixed Damnd jump to slowly follow the player

2021-07-11
- Fixed enemies changing when burned
- Implemented player dying and falling from the sky

2021-07-10
- Implemented weapons control for Haggar and Cody
- Fixed weapons when dropped
- Fixed some animations on players and weapons

2021-07-09
- Implemented player weapons: katana, knife and pipe
- Implemented weapon control for Guy
- Changed the collision type of a grappled enemy is hurt by any player
- Changed how many particles are used to the broken objects

2021-07-07
- Fixed J / Two P invisible shapes
- Fixed wrong position of the shape when an enemy dies while being thrown by a player
- Huge optimization on the particles (pieces of glass, fire, wood, etc)
- Optimized Objects and Player shapes

2021-07-05
- Remade all sound effects directly from an emulator of the Arcade
- Readjusted music volume
- Fixed bug that caused the freezing of the enemy on the floor
- Fixed many bugs in the pile drive (Haggar)
- Fixed no BGM option
- Removed left scroll in Round 1-3 until fixing the bug

2021-07-03
- Fixed bad position of front end objects in the ending cutscenes
- Source code repositioned inside the INC files (again)
- Little optimizations in the enemies
- Changes in Poison / Roxy movements to keep more similar to the arcade
- Fixed J / Two P disappearing when getting up
- Finished Holly Wood Molotov and fire (but I need to optimize it)
- Now enemies and players can be burned with fire
- Implemented difficult level

2021-07-02
- Implemented an option menu
- Implemented optional 400x300 resolution mode (only in 8-bit and need a CMM2 G2)
- Implemented optional 384x240 resolution mode (only for CMM2 G2)
- Implemented optional 16-bit colour mode, but it's slower than the 8-bit mode
- Adjusted OSD and the engine to support 320 or 384 width pixel mode
- Fixed the freeze effects on the enemies when hurt
- Restored scream sound of the "fat runners"
- Fixed Damnd jumping kick freeze
- Fixed many fixes in the enemies animations that caused unexpected behaviours
- Fixed vertical flip when using two parts to make one shape

2021-06-29
- Fixed many bugs when players throw enemies
- Reorganized source code and INC files
- Added all round 1 cutscenes
- Added Damnd
 
2021-06-28
- Intro scenes from the arcade are finished
- Select player screen is finished
- All points items from the arcade are finished
- All foods items from the arcade are finished
- All destructible items from the arcade are finished
- All sections of round 1 are finished
- Finished two-player support
- Added Bred, Jake and Dug
- Added J and Two P
- Added Axl and Slash
- Added Holly Wood (not red) and El Gado 
- Added Bill Bull and Graham Oriber
- Added Poison and Roxy
