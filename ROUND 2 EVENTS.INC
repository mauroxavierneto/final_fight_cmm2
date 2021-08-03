' --- ROUND 2 EVENTS ---

SUB Round_2_Events(xx)
 LOCAL TT
 
 SELECT CASE Section

  CASE 1: ' ROUND 2-1: SUBWAY ----------------------------------------------------------    

   SELECT CASE Levelpart

    CASE 0: 

     BLIT xs,0,0,0,(320-xs)*RX,240,2,0
     BLIT 0,0,320-xs,0,xs+RXX,240,3,0
     IF RXX=64 THEN BLIT 0,0,640-xs,0,xs+RXX,240,4,0

     IF xs>140 AND Event(6)=0 THEN
      'SPAWN OBJECT - TELEPHONE BOOTH - RANDOM WEAPONS
      SpawnObject(450,235,5,,-3)
      Event(6)=1: Event(3)=1400
      'START SUBWAY SOUND
      FOR TT=3 TO 4: PLAY_SAMPLE 30,TT,,-1,24: NEXT TT
     ENDIF

     IF xs>200 AND Event(2)=0 THEN
      SpawnEnemy(-60,200,AXL,1)
      SpawnEnemy(-60,230,POISON,1)
      SpawnEnemy(450,200,SLASH,1)
      SpawnEnemy(500,230,ROXY,1)
      Event(2)=1
     ENDIF

     'SUBWAY ON THE BACKGROUND
     IF Event(2)>0 THEN Event_Background_Subway(xx)

    CASE 1:

     IF MVSCR=0 THEN
      'DUSTBIN - ALL RANDOM
      SpawnObject(350,235,DUSTBIN,,-4)
     ENDIF

     BLIT xs,0,0,0,(320-xs)*RX,240,3,0
     BLIT 0,0,320-xs,0,xs+RXX,240,4,0
     IF RXX=64 THEN BLIT 0,0,640-xs,0,xs+RXX,240,5,0

     'SUBWAY ON THE BACKGROUND
     IF Event(2)>0 THEN Event_Background_Subway(xx)

     INC Event(0)

     IF Event(5)=0 and xs>200 THEN
      Event(5)=1
      SpawnEnemy(-60,200,HOLLY_WOOD,1)
      SpawnEnemy(450,210,BRED,1)
      SpawnEnemy(-60,200,TWO_P,1)
     ENDIF

    CASE 2:

     BLIT xs,0,0,0,(320-xs)*RX,240,4,0
     BLIT 0,0,320-xs,0,xs+RXX,240,5,0

     IF Event(7)=0 and xs>80 THEN
      Event(7)=1
      SpawnEnemy(500,230,ANDORE_JR,1)
     ENDIF

     'SUBWAY ON THE BACKGROUND
     IF Event(2)>0 THEN Event_Background_Subway(xx)

   END SELECT 'END OF LevelPart -----------------------------------------------------------

  CASE 2: ' ROUND 2-2: INSIDE SUBWAY ------------------------------------------------------

   'SUBWAY BACKGROUND
   PAGE WRITE 1
   CLS RGB(0,0,0)
   IF MVSCR THEN INC Event(0),-xx: INC Event(1),-xx

   'LIGHTS
   FOR T=0 TO 1
    INC Event(T),-Event(2)
    IF Event(T)<-32 THEN INC Event(T),MM.HRES
    BLIT 2,139,Event(T),65,62,42,13,0
   NEXT T

   SHAKE=10
   'SUBWAY SOUND
   IF TIMER MOD 2500 < 250 AND Event(2)=30 THEN FOR TT=3 TO 4: PLAY_SAMPLE 30,TT,,-1,24: NEXT TT

   SELECT CASE Levelpart

    CASE 0: 

     IF EVENT(30)=0 THEN
      EVENT(30)=1
      'STARTING SUBWAY SOUND
      FOR TT=3 TO 4: PLAY_SAMPLE 30,TT,,-1,24: NEXT TT
      SpawnEnemy(310,175,J,67)
      SpawnEnemy(355,175,TWO_P,66)
      SpawnEnemy(415,190,JAKE,66)
      SpawnEnemy(615,190,DUG,66)
     ENDIF
   
     'SUBWAY HANDLES
     IF EVENT(10)=0 THEN
      FOR T=5 TO 19: EVENT(T)=-30: NEXT T
      FOR T=0 TO 2
       EVENT( 5+T)= 17+48*T
      NEXT T
      FOR T=0 TO 4
       EVENT( 8+T)=240+48*T
      NEXT T
      FOR T=0 TO 1
       EVENT(13+T)=580+48*T
      NEXT T
     ENDIF

     BLIT xs,0,0,0,(320-xs)*RX,240,6,4
     BLIT 0,0,320-xs,0,xs+RXX,240,7,4
     IF RXX=64 THEN BLIT 0,0,640-xs,0,xs+RXX,240,8,0

    CASE 1:

     'SUBWAY HANDLES
     IF MVSCR=0 THEN
      FOR T=0 TO 2
       EVENT(15+T)= 460+48*T
      NEXT T
      FOR T=0 TO 4
       EVENT( 5+T)= 700+48*T
      NEXT T
      FOR T=0 TO 1
       EVENT(18+T)=1040+48*T
      NEXT T
     ENDIF

     BLIT xs,0,0,0,(320-xs)*RX,240,7,4
     BLIT 0,0,320-xs,0,xs+RXX,240,8,4
     IF RXX=64 THEN BLIT 0,0,640-xs,0,xs+RXX,240,9,0

     IF EVENT(31)=0 and scrx>560 THEN
      EVENT(31)=1
      SpawnEnemy(415,200,ANDORE_JR,75)
      SpawnEnemy(380,215,HOLLY_WOOD,1)
      SpawnEnemy(-45,195,ROXY,1)
      SpawnEnemy(590,175,AXL,64)
     ENDIF

    CASE 2:

     'SUBWAY HANDLES
     IF MVSCR=0 THEN
      FOR T=0 TO 2
       EVENT(10+T)= 910+48*T
      NEXT T
     ENDIF

     BLIT xs,0,0,0,(320-xs)*RX,240,8,4
     BLIT 0,0,320-xs,0,xs+RXX,240,9,4
     IF RXX=64 THEN BLIT 0,0,640-xs,0,xs+RXX,240,10,0

     IF EVENT(32)=0 and scrx>700 THEN
      EVENT(32)=1
      SpawnEnemy(430,190,BRED,66)
      SpawnEnemy(520,190,DUG,66)
     ENDIF

     IF EVENT(33)=0 and scrx>1000 THEN
      EVENT(33)=1
      SpawnEnemy(500,200,BRED,1)
      SpawnEnemy(500,215,DUG,1)
     ENDIF

     IF EVENT(33)=1 and scrx>1050 AND CNTE<5 THEN
      EVENT(33)=2
      SpawnEnemy(-40,200,DUG,66)
      SpawnEnemy(-40,215,BRED,66)
      SpawnEnemy(400,215,AXL,1)
     ENDIF

    CASE 3:

     BLIT xs,0,0,0,(320-xs)*RX,240,9,4
     BLIT 0,0,320-xs,0,xs+RXX,240,10,4
     IF RXX=64 THEN BLIT 0,0,640-xs,0,xs+RXX,240,11,0

     'BARRELS
     IF EVENT(34)=0 and scrx>1200 THEN
      EVENT(34)=1
      SpawnObject(470,235,8,,-4)
      SpawnObject(530,235,8,,-4)
      SpawnObject(550,195,8,,-3)
     ENDIF

    CASE 4:

     'SUBWAY HANDLES
     IF MVSCR=0 THEN
      FOR T=0 TO 5
       EVENT(13+T)= 510+48*T
      NEXT T
     ENDIF

     BLIT xs,0,0,0,(320-xs)*RX,240,10,4
     BLIT 0,0,320-xs,0,xs+RXX,240,11,4
     IF RXX=64 THEN BLIT 0,0,640-xs,0,xs+RXX,240,12,0

     IF EVENT(34)=1 and scrx>1350 THEN
      EVENT(34)=2
      SpawnEnemy(415,200,ANDORE_JR,75)
      SpawnEnemy(380,215,HOLLY_WOOD,1)
      SpawnEnemy(-45,195,ROXY,1)
      'SpawnEnemy(590,175,AXL,64)
     ENDIF

     IF EVENT(35)=0 and scrx>1700 THEN
      EVENT(35)=1
      SpawnEnemy(410,175,J,67)
      SpawnEnemy(455,175,TWO_P,66)
      SpawnEnemy(515,190,AXL,1)
     ENDIF

    CASE 5:

     BLIT xs,0,0,0,(320-xs)*RX,240,11,4
     BLIT 0,0,320-xs,0,xs+RXX,240,12,4

     'BARRELS
     IF EVENT(36)=0 THEN
      EVENT(36)=1
      SpawnObject(450,235,8,,-4)
      SpawnObject(510,235,8,,-3)
      SpawnObject(570,235,8,,-4)
      SpawnObject(550,215,8,,-4)
      SpawnObject(530,195,8,,-2)
     ENDIF

     IF scrx>1950 THEN
      IF EVENT(37) =  0 THEN SpawnEnemy(-45,220,ANDORE_JR,1)
      IF EVENT(37) = 40 THEN SpawnEnemy(-45,220,HOLLY_WOOD,1)
      IF EVENT(37) = 90 THEN SpawnEnemy(-45,220,EL_GADO,1)
      IF EVENT(37) =120 THEN SpawnEnemy(-45,220,BILL_BULL,1)
      IF EVENT(37)<=120 THEN INC EVENT(37)
     ENDIF

    END SELECT 'END OF Section

    'SUBWAY HANDLES
    INC EVENT(20),0.5: IF EVENT(20)>7.99 THEN EVENT(20)=0
    FOR T=5 TO 19
     INC EVENT(T),-xx
     Subway_Handle(EVENT(T),31,INT(EVENT(20)))
    NEXT T

  CASE 3: ' ROUND 2-3: SUBWAY GALLERY -----------------------------------------------------

   SELECT CASE Levelpart

    CASE 0: 

     IF EVENT(1)=0 THEN
      EVENT(1)=1
      SpawnEnemy(310,185,AXL,66)
      SpawnEnemy(360,185,J,66)
      SpawnEnemy(375,205,JAKE,68)
      'DUSTBIN
      SpawnObject(550,190,11,,-4)
      SpawnObject(600,190,11,,-4)
      'BARREL
      SpawnObject(660,190,8,,-4)
     'DRUMCAN
      SpawnObject(550,195,1,,-1)
      SpawnObject(570,215,1,,-2)
      SpawnObject(590,235,1,,-3)
      'ENEMIES READY TO KICK THE DRUMCANS
      SpawnEnemy(580,198,BRED,68)
      SpawnEnemy(600,218,DUG,68)
      SpawnEnemy(620,238,JAKE,68)
     ENDIF
 
     ' "WAKE UP" ENEMIES
     IF EVENT(2)<110 THEN INC EVENT(2)
     IF EVENT(2)=40 THEN STE(5)=1: EMV(5)=1
     IF EVENT(2)=70 THEN STE(4)=1: EMV(4)=1
     IF EVENT(2)=100 THEN STE(6)=1: EMV(6)=1

     BLIT xs,0,0,0,(320-xs)*RX,240,2,0
     BLIT 0,0,320-xs,0,xs+RXX,240,3,0
     IF RXX=64 THEN BLIT 0,0,640-xs,0,xs+RXX,240,4,0

    CASE 1:

     IF EVENT(3)=0 AND scrx>600 AND CNTE<3 THEN
      EVENT(3)=1
      SpawnEnemy(-40,210,BRED,1)
      SpawnEnemy(-50,220,DUG,1)
      SpawnEnemy(-40,190,HOLLY_WOOD,1)
      SpawnEnemy(410,220,HOLLY_WOOD_RED,1)
     ENDIF

     BLIT xs,0,0,0,(320-xs)*RX,240,3,0
     BLIT 0,0,320-xs,0,xs+RXX,240,4,0

    END SELECT 'END OF Section

  CASE 4: ' ROUND 2-4: SODOM RING ---------------------------------------------------------

   'ONLY ONE PART
   PAGE WRITE 1: CLS 0

   BLIT xs,0,0,0,(320-xs)*RX,240,4,4
   BLIT 0,0,320-xs,0,xs+RXX,240,5,4
  
 END SELECT 'END OF Round
 
END SUB

'SUBWAY IN THE BACKGROUND
SUB Event_Background_Subway(xx)
 LOCAL TT

 IF Event(2)<300 THEN
  'MOVE SUBWAY
  INC Event(3),-20  
  IF Event(3)<-640 THEN
   INC Event(3),640: INC Event(2)
   FOR TT=3 TO 4
    PLAY_SAMPLE 30,TT,,-1,24 'SUBWAY SOUND
   NEXT TT
  ENDIF
  'STOPPING SOUND
  IF Event(2)=8 THEN Event(2)=310: FOR TT=3 TO 4: PLAY_SAMPLE 31,TT,,99999,24: NEXT TT 
  SHAKE=10 'SHAKING SCREEN
 ELSE IF Event(2)<400 THEN 
  'STOP SUBWAY
  IF Event(3)>-ScrX+100 THEN SHAKE=10 'SHAKING SCREEN
  IF Event(3)>-ScrX+ 80 THEN INC Event(3),-abs( (-ScrX+80+4)-Event(3) )/45-xx-1
  IF Event(3)<-ScrX+ 81 THEN Event(3)=-ScrX+80: Event(2)=401
 ELSE
  'ONLY SCROLL SUBWAY AFTER STOPPED
  INC Event(3),-xx
 ENDIF

 'OPEN DOORS
 IF Event(2)>=400 AND Event(2)<=450 THEN
  INC Event(2)
  PAGE WRITE 14
  BLIT 140,30,139,30,45,112,14,0 ' LEFT DOOR - 14
  BLIT 185,30,186,30,45,112,14,0 'RIGHT DOOR - 14
  BOX 184,30,2,112,1,0
  PAGE WRITE 15
  BLIT 204,30,203,30,45,112,15,0 ' LEFT DOOR - 15
  BLIT 249,30,250,30,45,112,15,0 'RIGHT DOOR - 15
  BOX 248,30,2,112,1,0
  PAGE WRITE 1
 ENDIF

 BLIT 218, 0,218+Event(3)- 640,34,    102,148,16,4 'FRONT OF THE SUBWAY
 BLIT 114,30,203+Event(3)- 320,64,     92,112,16,4 'DOOR - 15
 BLIT   0, 0,    Event(3)- 320,34,MM.HRES,148,15,4
 BLIT 114,30,139+Event(3)     ,64,     92,112,16,4 'DOOR - 14
 BLIT   0, 0,    Event(3)     ,34,MM.HRES,148,14,4
 BLIT 114,30,203+Event(3)+ 320,64,     92,112,16,4 'DOOR - 15
 BLIT   0, 0,    Event(3)+ 320,34,MM.HRES,148,15,4
 BLIT 114,30,139+Event(3)+ 640,64,     92,112,16,4 'DOOR - 14
 BLIT   0, 0,    Event(3)+ 640,34,MM.HRES,148,14,4
 BLIT 114,30,203+Event(3)+ 960,64,     92,112,16,4 'DOOR - 15
 BLIT   0, 0,    Event(3)+ 960,34,MM.HRES,148,15,4
 BLIT   0, 0,    Event(3)+1280,34,    105,148,16,4 'REAR OF THE SUBWAY

END SUB


'SUBWAY HANDLE
SUB Subway_Handle(X,Y,AN)
 SELECT CASE AN
  CASE 0: BLIT  69,138,X  ,Y,19,47,13,4
  CASE 1: BLIT  89,138,X  ,Y,15,48,13,4
  CASE 2: BLIT 106,138,X  ,Y,13,48,13,4
  CASE 3: BLIT 120,138,X-4,Y,15,48,13,4
  CASE 4: BLIT 137,138,X-8,Y,19,46,13,4
  CASE 5: BLIT 120,138,X-4,Y,15,48,13,4
  CASE 6: BLIT 106,138,X  ,Y,13,48,13,4
  CASE 7: BLIT  89,138,X  ,Y,15,48,13,4
 END SELECT
END SUB


