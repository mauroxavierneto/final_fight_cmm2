' --- GENERAL STAGE/ROUND EVENTS CONTROL ---

SUB ClearEvents
 LOCAL T
 'RESET ALL STAGE EVENTS, ENEMIES, OBJECTS AND MORE
 MATH SET 0,Event()
 MATH SET 0,EEnergy()
 MATH SET 0,STE()
 MATH SET 0,EX()
 MATH SET 0,EY()
 MATH SET 0,ESJMP()
 MATH SET 0,ETR()
 MATH SET 0,EWAIT()
 MATH SET 0,ESPD()
 MATH SET 0,ESIDE()
 MATH SET 0,EType()
 MATH SET 0,ECOMBO()
 MATH SET 0,EHIT()
 MATH SET 0,ESPDX()
 MATH SET 0,ESPDY()
 MATH SET 0,EBACK()
 MATH SET 0,EBACKX()
 MATH SET 0,EAN()
 MATH SET 0,EAniSpd()
 MATH SET 0,EAniDelay()
 MATH SET 0,EDIST()
 MATH SET 0,EEnergy()
 MATH SET 0,EEnMax()
 MATH SET 0,EMV()
 MATH SET 0,STE()
 MATH SET 0,ES_SPD()
 MATH SET 0,ES_POW()
 MATH SET 0,ES_DEF()
 MATH SET 0,ESCORE()
 MATH SET 0,EITEM()
 MATH SET 0,XHit()
 MATH SET 0,YHit()
 MATH SET 0,AHit()
 MATH SET 0,EnHit()
 MATH SET 0,SPHit()
 MATH SET 0,Event()
 MATH SET 0,Index()
 MATH SET 0,ZBUF()
 MATH SET 0,Y()
 FOR T=4 TO EMAX
  RealY(T)=0
 NEXT T
 Scroll=0
 LevelPart=0
 ScrX=240
END SUB

' SCROLL STAGE AND CONTROL EVENTS (ANIMATIONS, SPAWN ENEMIES)

SUB StageScrollEvent(xx,PL)
 Local t,i,xs,mv

 'DON'T ALLOW SCROLL FOR A WHILE
 IF ScrollLock>0 THEN INC ScrollLock,-1: xx=0

 xx=int(xx)

 'SCROLL OTHER PLAYERS OR CANCEL SCROLL IF OTHER PLAYER IS IN THE LIMIT OF THE SCREEN
 IF OSDX=0 THEN
  for t=1 to MAXPL
   IF t<>PL THEN INC X(t),-xx
   IF X(t)<20 THEN xx=0: X(t)=0
  next t
 ENDIF

 INC Scroll,xx
 xs=Scroll: mv=1

 'SCROLL ENEMIES
 for t=0 to EMAX
  INC EX(t),-xx
 next t

 'LIMIT OF THE ROUND 
 INC ScrX,xx

 IF ScrX>=LIMRD THEN
  ScrX=LIMRD
  'LOAD END OF SECTION EVENT ONLY WHEN PLAYERS ARE STOPPED
  IF CNTE=0 AND OSDX<5000 THEN
   GO=1
   FOR T=1 TO MAXPL
    IF Punch(T)>0 OR Kick(T)>0 OR Special(T)>0 OR PHurted(T)>0 OR AN(T)>14 THEN GO=0
   NEXT T
   IF GO THEN OSDX=9990': RoundIntro(1)
  ENDIF
 ENDIF

 'CREATE HORIZONTAL LIMIT FOR THE ROUND
 R_SCR=LIMRD-ScrX+RSCRX
 L_SCR=LSCRX-(ScrX-240)

 'CALL EACH LEVEL PART UNTIL THE SECTION LIMIT
 if xs>320 then inc xs,-320: inc LevelPart, 1:mv=0
 if xs<  0 then inc xs, 320: inc LevelPart,-1:mv=0
 if LevelPart<0 then xs=0: LevelPart=0

 IF LevelPart>PartMax THEN LevelPart=PartMax: xs=320

 PAGE WRITE 1
 
 if Round=1 then  

  SELECT CASE Section

   CASE 1: ' ROUND 1-1: SLUMS -----------------------------------------------------------    

    'PARALLAX CITY BACKGROUND
    IF MV=1 THEN PAGE SCROLL 11,-xx\2,0
    PAGE COPY 11 TO 1  

    SELECT CASE Levelpart

     CASE 0: 

      BLIT xs,0,0,0,320-xs,240,2,4: BLIT 0,0,320-xs,0,xs,240,3,4

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
      IF Event(0)= 20 THEN InsertEnemy(487-xs,164,4,57)
      IF Event(0)= 60 THEN InsertEnemy(487-xs,164,6,57)
      IF Event(0)=100 THEN InsertEnemy(487-xs,164,5,57)
      IF Event(0)=170 THEN InsertEnemy(-30,170,7,1)

      IF OSDX=10 THEN
       'INSERT OBJECT - TELEPHONE BOOTH
       InsertObject(650,195,5,,-1)
       'ENEMY LEANING AGAINST THE WALL
       InsertEnemy(427-xs,174,4,65)

       'TESTS
       'InsertEnemy(340,200,17,1)
       'InsertEnemy(340,230,18,1)
       'InsertObject(250,195,19,,-1)
 
      ENDIF

     CASE 1:

      BLIT xs,0,0,0,320-xs,240,3,4: BLIT 0,0,320-xs,0,xs,240,4,4

      'INSERT OBJECTS - 2 DUSTBINS
      IF MV=0 THEN 
       InsertObject(450,190,11,,-1)
       InsertObject(500,190,11,,-1)
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
      IF Event(0)= 20 THEN InsertEnemy(167-xs,164,4,57)
      IF Event(0)= 60 THEN InsertEnemy(167-xs,164,6,57)
      IF Event(0)=100 THEN InsertEnemy(167-xs,164,5,57)
      IF Event(0)=170 THEN InsertEnemy(-30,170,7,1)

     CASE 2:

      BLIT xs,0,0,0,320-xs,240,4,4: BLIT 0,0,320-xs,0,xs,240,5,4

      'INSERT OBJECTS - 3 DUSTBINS
      IF MV=0 THEN 
       InsertObject(450,185,11,,-2)
       InsertObject(500,185,11,,-2)
       InsertObject(480,238,11,,-1)
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
      IF Event(1)= 20 THEN InsertEnemy(246-xs,164,4,57)
      IF Event(1)= 60 THEN InsertEnemy(246-xs,164,6,57)
      IF Event(1)=100 THEN InsertEnemy(246-xs,164,5,57)
      IF Event(1)=120 THEN InsertEnemy(-30,170,8,1)

      'RELEASE ENEMIES ON THE STAGE
      IF XS>200 THEN INC Event(2)
      IF Event(2)= 50 THEN InsertEnemy(-30,170,4,1)
      IF Event(2)=100 THEN InsertEnemy(-30,160,6,1): InsertEnemy(-60,200,9,1)
      IF Event(2)=150 THEN InsertEnemy(-30,170,11,1)
    END SELECT 'END OF LevelPart -----------------------------------------------------------

   CASE 2: ' ROUND 1-2: SLUMS GALLERY ------------------------------------------------------

    'ONLY ONE PART
    PAGE WRITE 1: CLS 0
    BLIT xs,0,0,0,320-xs,240,6,4: BLIT 0,0,320-xs,0,xs,240,7,4
   
    IF EVENT(0)=0 THEN
     InsertObject(140,200,17,,-3)
     InsertObject(280,195,8,,-1)
     InsertObject(350,195,8,,-1)
     'SEATED ENEMIES
     InsertEnemy(295,210,9,66,4)
     InsertEnemy(255,230,5,68,4)
     InsertEnemy(325,230,4,68,5)
    ENDIF
    INC EVENT(0)
    ' "WAKE UP" ENEMIES
    IF EVENT(0)=60 THEN STE(5)=1: EMV(5)=1
    IF EVENT(0)=70 THEN STE(4)=1: EMV(4)=1
    IF EVENT(0)=80 THEN STE(6)=1: EMV(6)=1
  
    IF xs>180 AND EVENT(1)=0 THEN INC EVENT(1): ScrollLock=140
    IF EVENT(1)>0 THEN INC EVENT(1)
    ' G. ORIBER RUNNING + J - LEFT
    IF EVENT(1)=20 THEN InsertEnemy(-20,190,15,80,5): InsertEnemy(-40,210,7,1,5)
    ' BILL BULL + TWO P - RIGHT
    IF EVENT(1)=35 THEN InsertEnemy(335,210,14,1,5): InsertEnemy(355,230,8,1,4)

   CASE 3: ' ROUND 1-3: SLUMS MAD GEAR'S LAIR ----------------------------------------------

    'PARALLAX CITY BACKGROUND
    IF MV=1 THEN PAGE SCROLL 11,-xx\2,0
    PAGE COPY 11 TO 1  

    SELECT CASE Levelpart

     CASE 0: 

      BLIT xs,0,0,0,320-xs,240,8,4: BLIT 0,0,320-xs,0,xs,240,9,4

      IF OSDX=2200 THEN
       'INSERT OBJECT - TIRES
       InsertObject(220,185,13,,140) 'BARBECUE
       InsertObject(274,185,13,,-3)  'RANDOM WEAPON
       'ENEMIES
       InsertEnemy(470,180, 7,66,4) 'J
       InsertEnemy(540,180, 9,64,5) 'AXEL
      ENDIF

     CASE 1:

      BLIT xs,0,0,0,320-xs,240,9,4: BLIT 0,0,320-xs,0,xs,240,10,4

      'INSERT ENEMY
      IF MV=0 THEN InsertEnemy(440,185, 8,66,4) 'TWO P

      'DAMND BREAK THE DOOR
      IF EVENT(0)=0 AND xs>120 THEN
       INC EVENT(0)
       PAGE WRITE  9: BLIT  0,118,295,52,25,122,12,0
       PAGE WRITE 10: BLIT 25,118,  0,52,73,122,12,0
       PAGE WRITE 1
       FOR T=0 TO 2
        FOR I=0 TO 3
         InsertObject(220+((I<=1)-(I>=2))*RND*15,180,201+INT(RND*3.99),NUM): EY(NUM)=-40-T*15
         ESJMP(NUM)=-15+RND*5: ESIDE(NUM)=5: EMV(NUM)=1
         ESPDX(NUM)=((I<=1)-(I>=2))*RND*6
        NEXT I
       NEXT T
       PLAY_SAMPLE 2,4,22050
      ENDIF

     CASE 2:

      BLIT xs,0,0,0,320-xs,240,10,4

    END SELECT 'END OF LevelPart -----------------------------------------------------------


  END SELECT 'END OF Section

 ENDIF 'END OF ROUND 1
 Scroll=xs
END SUB

