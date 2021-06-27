' -- GENERAL STAGE/ROUND CONTROL AND LOADING ---


' SCROLL STAGE AND CONTROL EVENTS (ANIMATIONS, SPAWN ENEMIES)

SUB StageScrollEvent(xx,PL)
 Local t,xs,mv

 xx=int(xx)

 'SCROLL OTHER PLAYERS OR CANCEL SCROLL IF OTHER PLAYER IS IN THE LIMIT OF THE SCREEN
 for t=1 to MAXPL
  IF t<>PL THEN INC X(t),-xx
  IF X(t)<20 THEN xx=0: X(t)=0
 next t

 INC Scroll,xx
 xs=Scroll: mv=1

 'SCROLL ENEMIES
 for t=0 to EMAX
  INC EX(t),-xx
 next t

 'LIMIT OF THE ROUND 
 INC ScrX,xx
 IF ScrX>LIMRD THEN ScrX=LIMRD

 'CREATE HORIZONTAL LIMIT FOR THE ROUND
 R_SCR=LIMRD-ScrX+RSCRX
 L_SCR=LSCRX-(ScrX-240)

 'CALL EACH LEVEL PART 
 if xs>320 then inc xs,-320: inc LevelPart, 1:mv=0
 if xs<  0 then inc xs, 320: inc LevelPart,-1:mv=0
 if LevelPart<0 then xs=0: LevelPart=0
 
 if Round=1 then  
  SELECT CASE Section
   CASE 1: ' ROUND 1-1: SLUMS -----------------------------------------------------------    
    if LevelPart>2 then xs=320: LevelPart=2
    IF MV=1 THEN PAGE SCROLL 6,-xx\2,0
    PAGE COPY 6 TO 1  
    SELECT CASE Levelpart
     CASE 0: 
      BLIT xs,0,0,0,320-xs,240,2,4: BLIT 0,0,320-xs,0,xs,240,3,4
      'OPEN DOOR 1
      IF XS>230 AND XS<240 AND Event(0)=0 THEN Event(0)=1
      IF Event(0)>0 THEN INC Event(0) 
      IF Event(0)<=20 THEN
       PAGE WRITE 3        
        BLIT (Event(0)\4)*44,0,143,60,44,105,7,0
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

       'InsertEnemy(400-xs,174,10,65) 'TEST

      ENDIF
     CASE 1:
      'INSERT OBJECTS - 2 DUSTBINS
      IF MV=0 THEN 
       InsertObject(450,190,11,,-1)
       InsertObject(500,190,11,,-1)
      ENDIF
      INC Event(0)
      BLIT xs,0,0,0,320-xs,240,3,4: BLIT 0,0,320-xs,0,xs,240,4,4
      'RELEASE ENEMIES THROUGH THE DOOR AND FROM LEFT - IF NOT RELEASED IN PREVIOUS BLOCK
      IF Event(0)= 20 THEN InsertEnemy(487-xs,164,4,57)
      IF Event(0)= 60 THEN InsertEnemy(487-xs,164,6,57)
      IF Event(0)=100 THEN InsertEnemy(487-xs,164,5,57)
      IF Event(0)=170 THEN InsertEnemy(-30,170,7,1)
     CASE 2:
      'INSERT OBJECTS - 3 DUSTBINS
      IF MV=0 THEN 
       InsertObject(450,185,11,,-2)
       InsertObject(500,185,11,,-2)
       InsertObject(480,238,11,,-1)
      ENDIF
      BLIT xs,0,0,0,320-xs,240,4,4: BLIT 0,0,320-xs,0,xs,240,5,4
      'OPEN DOOR 2
      INC Event(1)
      IF Event(1)<=20 THEN
       PAGE WRITE 4        
        BLIT (Event(1)\4)*44,0,222,60,44,105,7,0
       PAGE WRITE 1
      ENDIF
      'RELEASE ENEMIES THROUGH THE DOOR
      'IF Event(1)=22 THEN InsertEnemy(246-xs,164,4,57)
      'IF Event(1)=70 THEN InsertEnemy(246-xs,164,5,57)
      IF Event(1)= 20 THEN InsertEnemy(246-xs,164,4,57)
      IF Event(1)= 60 THEN InsertEnemy(246-xs,164,6,57)
      IF Event(1)=100 THEN InsertEnemy(246-xs,164,5,57)

      'RELEASE ENEMIES ON THE STAGE
      IF XS>200 THEN INC Event(2)
      IF Event(2)= 50 THEN InsertEnemy(-30,170,4,1)
      IF Event(2)=100 THEN InsertEnemy(-30,160,6,1): InsertEnemy(-60,200,10,1)
      'IF Event(2)=150 THEN InsertEnemy(-30,170,11,1) 'HOLLY WOOD HERE
    END SELECT    
  END SELECT
 endif
 Scroll=xs
END SUB


' LOAD ROUND AND SECTION AND SET ATTRIBUTES

SUB LoadRound(R,S)
 LOCAL T

 'RESET ALL STAGE EVENTS AND ENEMIES
 MATH SET 0,Event()
 MATH SET 0,EEnergy()
 MATH SET 0,STE()
 
 'SMYA  - VERTICAL SUPERIOR Y LIMIT
 'SMYB  - VERTICAL INFERIOR Y LIMIT
 'LSCRX - HORIZONTAL LEFT  LIMIT OF THE SCROLL X
 'RSCRX - HORIZONTAL RIGHT LIMIT OF THE SCROLL X

 'LIMRD - MAXIMUM SCROLL ROUND

 'L_SCR -  LEFT LIMIT OF THE SCREEN CONSIDERING THE SCROLL
 'R_SCR - RIGHT LIMIT OF THE SCREEN CONSIDERING THE SCROLL

 'SLUMS
 IF R=1 THEN
  SELECT CASE S
  CASE 1: ' ROUND 1-1: SLUMS ------------------------------------------------------------
   SMYA=180: SMYB=238
   LIMRD=1200: LSCRX=10: RSCRX=190
   PAGE WRITE 2: CLS: LOAD PNG ".\IMAGES\1 - ROUND 1 - SLUMS\PART01.PNG",,,1
   PAGE WRITE 3: CLS: LOAD PNG ".\IMAGES\1 - ROUND 1 - SLUMS\PART02.PNG",,,1
   PAGE WRITE 4: CLS: LOAD PNG ".\IMAGES\1 - ROUND 1 - SLUMS\PART03.PNG",,,1
   PAGE WRITE 5: CLS: LOAD PNG ".\IMAGES\1 - ROUND 1 - SLUMS\PART04.PNG",,,1
   PAGE WRITE 6: CLS: LOAD PNG ".\IMAGES\1 - ROUND 1 - SLUMS\BACKGROUND.PNG",0,-20
   PAGE WRITE 7: CLS: LOAD PNG ".\IMAGES\1 - ROUND 1 - SLUMS\ANIMATION.PNG",,,1
  END SELECT
 ENDIF

END SUB


' LOAD ROUND MAP WHEN STARTING OR ENDING A ROUND
SUB LoadRoundMap(Round,CLR)
 LOCAL MA$,MB$
 PAGE WRITE 21: CLS 0
 MA$=RIGHT$("0"+STR$(Round*2+CLR),2)
 MB$=RIGHT$("0"+STR$(Round*2+CLR-1),2)
 LOAD PNG ".\IMAGES\MAPS\MAP"+MA$+".PNG",0,  0,1
 LOAD PNG ".\IMAGES\MAPS\MAP"+MB$+".PNG",0,101,1
 PAGE WRITE 1
END SUB


' SHOW ROUND MAP WHEN STARTING OR ENDING A ROUND
SUB ShowRoundMap(M,Y)
 PAGE WRITE 1
 BLIT 0,M*101,32,Y,253,100,21,4
END SUB


