' --- ROUND 1 EVENTS ---

SUB Round_1_Events(xx)
 
 SELECT CASE Section

  CASE 1: ' ROUND 1-1: SLUMS -----------------------------------------------------------    

   'PARALLAX CITY BACKGROUND
   IF MVSCR THEN PAGE SCROLL 11,-xx\2,0
   PAGE COPY 11 TO 1  

   SELECT CASE Levelpart

    CASE 0: 

     BLIT xs,0,0,0,(320-xs)*RX,240,2,4
     BLIT 0,0,320-xs,0,xs+RXX,240,3,4
     IF RXX=64 THEN BLIT 0,0,640-xs,0,xs+RXX,240,4,4

     'OPEN DOOR 1
     IF XS>230 AND XS<240 AND Event(0)=0 THEN Event(0)=1
     IF Event(0)>0 THEN INC Event(0) 
     IF Event(0)<=20 THEN
      PAGE WRITE 3        
      IF Event(0)\4<5 THEN
       BLIT (Event(0)\4)*44,0,143,60,44,105,12,0
      ELSE
       BLIT           132,105,143,60,44,105,12,0
      ENDIF
      PAGE WRITE 1
     ENDIF
     'RELEASE ENEMIES THROUGH THE DOOR AND FROM LEFT
     IF Event(0)= 20 THEN SpawnEnemy(487-xs,164,4,57)
     IF Event(0)= 60 THEN SpawnEnemy(487-xs,164,6,57)
     IF Event(0)=100 THEN SpawnEnemy(487-xs,164,5,57)
     IF Event(0)=170 THEN SpawnEnemy(-30,170,7,1)

     IF OSDX=10 THEN
      'SPAWN OBJECT - TELEPHONE BOOTH
      SpawnObject(650,195,5,,-1)
      'ENEMY LEANING AGAINST THE WALL
      SpawnEnemy(427-xs,174,4,65)

      'TESTS
      IF NOINTRO THEN
       SpawnEnemy(340,200,HOLLY_WOOD_RED,1)
       SpawnEnemy(180,210,4,1)
      ENDIF
      'SpawnObject(250,195,19,,-1)
     ENDIF

    CASE 1:

     BLIT xs,0,0,0,(320-xs)*RX,240,3,4
     BLIT 0,0,320-xs,0,xs+RXX,240,4,4
     IF RXX=64 THEN BLIT 0,0,640-xs,0,xs+RXX,240,5,4

     'SPAWN OBJECTS - 2 DUSTBINS
     IF MVSCR=0 THEN 
      SpawnObject(450,190,11,,-1)
      SpawnObject(500,190,11,,-1)
     ENDIF
     INC Event(0)
     'FINISH OPENING THE DOOR IF THE PLAYER IS FAST
     IF Event(0)<=20 THEN
      PAGE WRITE 3        
      IF Event(0)\4<5 THEN
       BLIT (Event(0)\4)*44,0,143,60,44,105,12,0
      ELSE
       BLIT           132,105,143,60,44,105,12,0
      ENDIF
      PAGE WRITE 1
     ENDIF
     'RELEASE ENEMIES THROUGH THE DOOR AND FROM LEFT - IF NOT RELEASED IN PREVIOUS BLOCK
     IF Event(0)= 20 THEN SpawnEnemy(167-xs,164,4,57)
     IF Event(0)= 60 THEN SpawnEnemy(167-xs,164,6,57)
     IF Event(0)=100 THEN SpawnEnemy(167-xs,164,5,57)
     IF Event(0)=170 THEN SpawnEnemy(-30,170,7,1)

    CASE 2:

     BLIT xs,0,0,0,(320-xs)*RX,240,4,4
     BLIT 0,0,320-xs,0,xs+RXX,240,5,4

     'SPAWN OBJECTS - 3 DUSTBINS
     IF MVSCR=0 THEN 
      SpawnObject(450,185,11,,-2)
      SpawnObject(500,185,11,,-2)
      SpawnObject(480,238,11,,-1)
     ENDIF
     'OPEN DOOR 2
     INC Event(1)
     IF Event(1)<=20 THEN
      PAGE WRITE 4        
      IF Event(1)\4<5 THEN 
       BLIT (Event(1)\4)*44,0,222,60,44,105,12,0
      ELSE
       BLIT           132,105,222,60,44,105,12,0
      ENDIF
      PAGE WRITE 1
     ENDIF
     'RELEASE ENEMIES THROUGH THE DOOR
     IF Event(1)= 20 THEN SpawnEnemy(246-xs,164,4,57)
     IF Event(1)= 60 THEN SpawnEnemy(246-xs,164,6,57)
     IF Event(1)=100 THEN SpawnEnemy(246-xs,164,5,57)
     IF Event(1)=120 THEN SpawnEnemy(-30,170,8,1)

     'RELEASE ENEMIES ON THE STAGE
     IF XS>200 THEN INC Event(2)
     IF Event(2)= 50 THEN SpawnEnemy(-30,170,4,1)
     IF Event(2)=100 THEN SpawnEnemy(-30,160,6,1): SpawnEnemy(-60,200,9,1)
     IF Event(2)=150 THEN SpawnEnemy(-30,170,11,1)
   END SELECT 'END OF LevelPart -----------------------------------------------------------

  CASE 2: ' ROUND 1-2: SLUMS GALLERY ------------------------------------------------------

   'ONLY ONE PART
   PAGE WRITE 1: CLS 0
   BLIT xs,0,0,0,(320-xs)*RX,240,6,4
   BLIT 0,0,320-xs,0,xs+RXX,240,7,4
   
   IF EVENT(0)=0 THEN
    SpawnObject(140,200,17,,-3)
    SpawnObject(280,195,8,,-1)
    SpawnObject(350,195,8,,-1)
    'SEATED ENEMIES
    SpawnEnemy(295,210,9,66,4)
    SpawnEnemy(255,230,5,68,4)
    SpawnEnemy(325,230,4,68,5)
   ENDIF
   INC EVENT(0)
   ' "WAKE UP" ENEMIES
   IF EVENT(0)<60 THEN STE(5)=68
   IF EVENT(0)<70 THEN STE(4)=66
   IF EVENT(0)<80 THEN STE(6)=68

   ' "WAKE UP" ENEMIES
   IF EVENT(0)=60 THEN STE(5)=1: EMV(5)=1
   IF EVENT(0)=70 THEN STE(4)=1: EMV(4)=1
   IF EVENT(0)=80 THEN STE(6)=1: EMV(6)=1
  
   IF xs>180 AND EVENT(1)=0 THEN INC EVENT(1): ScrollLock=140
   IF EVENT(1)>0 THEN INC EVENT(1)
   ' G. ORIBER RUNNING + J - LEFT
   IF EVENT(1)=20 THEN SpawnEnemy(-20,190,15,80,5): SpawnEnemy(-40,210,7,1,5)
   ' BILL BULL + TWO P - RIGHT
   IF EVENT(1)=35 THEN SpawnEnemy(335+RXX,210,14,1,5): SpawnEnemy(355+RXX,230,8,1,4)

  CASE 3: ' ROUND 1-3: SLUMS MAD GEAR'S LAIR ----------------------------------------------

   'PARALLAX CITY BACKGROUND
   IF MVSCR THEN PAGE SCROLL 11,-xx\2,0
   PAGE COPY 11 TO 1  

   SELECT CASE Levelpart

    CASE 0: 

     BLIT xs,0,0,0,(320-xs)*RX,240,8,4
     BLIT 0,0,320-xs,0,xs+RXX,240,9,4
     IF RXX=64 THEN BLIT 0,0,640-xs,0,xs+RXX,240,10,4

     IF OSDX=2200 THEN
      'SPAWN OBJECT - TIRES
      SpawnObject(220,185,13,,140) 'BARBECUE
      SpawnObject(274,185,13,,-3)  'RANDOM WEAPON
      'ENEMIES
      SpawnEnemy(470,180, 7,66,4) 'J
      SpawnEnemy(540,180, 9,64,5) 'AXEL
     ENDIF

    CASE 1:

     BLIT xs,0,0,0,(320-xs)*RX,240,9,4
     BLIT 0,0,320-xs,0,xs+RXX,240,10,4

     'SPAWN ENEMY
     IF MVSCR=0 THEN SpawnEnemy(440,185, 8,66,4) 'TWO P

     'DAMND BREAK THE DOOR
     IF EVENT(0)=0 AND xs>120 THEN
      LEFTLIM=1 'TURN ON THE SCROLL TO LEFT
      LIMLD=700 'DEFINE LIMIT TO LEFT SCROLL
      INC EVENT(0)
      PAGE WRITE  9: BLIT  0,118,295,52,25,122,12,0
      PAGE WRITE 10: BLIT 25,118,  0,52,73,122,12,0
      PAGE WRITE 1
      FOR T=0 TO 2
       FOR I=0 TO 3
        SpawnObject(220+((I<=1)-(I>=2))*RND*15,180,201+INT(RND*3.99),NUM): EY(NUM)=-40-T*15
        ESJMP(NUM)=-15+RND*5: ESIDE(NUM)=5: EMV(NUM)=1
        ESPDX(NUM)=((I<=1)-(I>=2))*RND*6
       NEXT I
      NEXT T
      SpawnEnemy(220,180,DAMND,70,5,BOSS) 
      PLAY_SAMPLE 2,4,22050
     ENDIF

    CASE 2:

     BLIT xs,0,0,0,(320-xs)*RX,240,9,4
     BLIT 0,0,320-xs,0,xs+RXX,240,10,4

   END SELECT 'END OF LevelPart -----------------------------------------------------------

   'CONTROL DAMND WHISTLE THAT CALL AN ENEMY WAVES
   IF EVENT(1)=0 AND EEnergy(BOSS)<250 AND STE(BOSS)>0 AND STE(BOSS)<=40 THEN
    EVENT(1)=1: STE(BOSS)=76 'GO TO THE SUBWAY ENTRY WALL
   ENDIF
   IF EVENT(1)>0 AND EVENT(1)<100 AND EMV(BOSS)=3 THEN 'CALL FIRST ENEMIES WAVE
    INC EVENT(1)
    IF EVENT(1)= 2 THEN SpawnEnemy(910-SCRX,180,HOLLY_WOOD,1,5) 
    IF EVENT(1)=15 THEN SpawnEnemy(910-SCRX,180,BRED,1,5) 
    IF EVENT(1)=30 THEN SpawnEnemy(-40,230,DUG,1,4) 
    IF EVENT(1)=50 THEN SpawnEnemy(-40,210,J,1,4): EMV(BOSS)=2: EVENT(1)=100
   ENDIF

   IF EVENT(1)=100 AND EEnergy(BOSS)<140 AND STE(BOSS)>0 AND STE(BOSS)<=40 THEN
    EVENT(1)=101: STE(BOSS)=76 'GO TO THE SUBWAY ENTRY WALL AGAIN
   ENDIF
   IF EVENT(1)>100 AND EVENT(1)<200 AND EMV(BOSS)=3 THEN 'CALL SECOND ENEMIES WAVE
    INC EVENT(1)
    IF EVENT(1)=102 THEN SpawnEnemy(     -40,210,ROXY    , 1,4) 
    IF EVENT(1)=115 THEN SpawnEnemy(     -30,230,G_ORIBER,80,4) 
    IF EVENT(1)=130 THEN SpawnEnemy(910-SCRX,180,BRED    , 1,5) 
    IF EVENT(1)=150 THEN SpawnEnemy(910-SCRX,180,DUG     , 1,5)
   ENDIF
   IF EVENT(1)=200 AND CNTE<5 THEN
    EMV(BOSS)=2: EVENT(1)=201
    SpawnEnemy(-35,200,HOLLY_WOOD_RED,1,4)
    SpawnEnemy(-45,230,HOLLY_WOOD_RED,1,4)
   ENDIF

 END SELECT 'END OF Section

END SUB

