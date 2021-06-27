' --- GENERAL ENEMIES ROUTINES ---

 
' INSERT NEW ENEMY
' 4,5,6 - BRED / JAKE / DUG

SUB InsertEnemy(x,y,tp,st)
 LOCAL T
 T=3

 DO WHILE T<=12
  INC T

  IF STE(T)=0 THEN
   'RIGHT OR LEFT INITIAL SIDE
   IF x<160 THEN ESide(T)=4 ELSE ESide(T)=5

   'GENERIC START PARAMETERS
   EX(T)=x: RealY(T)=y: EY(T)=0: EType(T)=tp
   IF ST=0 THEN ST=1
   EAN(T)=0: EAniDelay(T)=0:EAniSpd(T)=5: EWait(T)=0
   EMV(T)=1: EBACK(T)=1: EHIT(T)=0
   ESJMP(T)=0: STE(T)=st
   ESPDX(T)=0: ESPDY(T)=0: ETR(T)=0: ECOMBO(T)=0

   'SET SPECIFIC START PARAMETERS FOR EACH ENEMY ----------------------------------------
   SELECT CASE EType(T)

    'BRED / JAKE / DUG = 1000 POINTS 
    CASE 4 TO 6:
     EEnMAX(T)=20+Round*5+(EType(T)-4)*5: ESCORE(T)=1000+(EEnMAX(T)*20)\10
     ES_SPD(T)=2: ESPD(T)=ES_SPD(T): ES_DEF(T)=2: ES_POW(T)=10

    'J / TWO P. = 2000 POINTS
    CASE 7 TO 8:
     EEnMAX(T)=10+Round*5+(EType(T)-7)*5: ESCORE(T)=2000+(EEnMAX(T)*20)\10
     ES_SPD(T)=7: ESPD(T)=ES_SPD(T): ES_DEF(T)=2: ES_POW(T)=5

    'AXL / SLASH = 2000 POINTS
    CASE 9 TO 10:
     EEnMAX(T)=20+Round*5+(EType(T)-9)*5: ESCORE(T)=2000+(EEnMAX(T)*20)\10
     ES_SPD(T)=3: ESPD(T)=ES_SPD(T): ES_DEF(T)=4: ES_POW(T)=10

    'HOLLY WOOD / EL GADO = 3000 POINTS
    CASE 11 TO 12:
     EEnMAX(T)=55+Round*5+(EType(T)-11)*5: ESCORE(T)=3000+(EEnMAX(T)*20)\10
     ES_SPD(T)=4: ESPD(T)=ES_SPD(T): ES_DEF(T)=3: ES_POW(T)=20

    'BOTTLE RED HOLLY WOOD = 3000 POINTS
    CASE 13:
     EEnMAX(T)=55+Round*5: ESCORE(T)=3000+EEnMAX(T)
     ES_SPD(T)=4: ESPD(T)=ES_SPD(T): ES_DEF(T)=1: ES_POW(T)=15

    'BILL BULL / GRAHAM ORIBER / WONG WHO = 2500 POINTS
    CASE 14 TO 16:
     EEnMAX(T)=40+Round*5+(EType(T)-14)*5: ESCORE(T)=2500+(EEnMAX(T)*20)\10
     ES_SPD(T)=3: ESPD(T)=ES_SPD(T): ES_DEF(T)=3: ES_POW(T)=15

    'POISON / ROXY = 2000 POINTS
    CASE 17 TO 18:
     EEnMAX(T)=40+Round*5+(EType(T)-17)*5: ESCORE(T)=2000+(EEnMAX(T)*20)\10
     ES_SPD(T)=4: ESPD(T)=ES_SPD(T): ES_DEF(T)=2: ES_POW(T)=15

    'ANDORE / JR / FATHER / UNCLE / GRANPA = 3000 POINTS
    CASE 19 TO 23:
     EEnMAX(T)=75+Round*5+(EType(T)-19)*10: ESCORE(T)=3000+(EEnMAX(T)*20)\10
     ES_SPD(T)=1: ESPD(T)=ES_SPD(T): ES_DEF(T)=5: ES_POW(T)=25

    'DAMND = 10000 POINTS
    CASE 80:
     EEnMAX(T)=500: ESCORE(T)=10000+(EEnMAX(T)*20)\10
     ES_SPD(T)=2: ESPD(T)=ES_SPD(T): ES_DEF(T)=5: ES_POW(T)=25

   END SELECT

   EEnergy(T)=EEnMAX(T)
   EXIT DO
 
  ENDIF

 LOOP

END SUB


' CONTROL ENEMY ON SCREEN

SUB ControlEnemy(T)
 LOCAL I,II,TT,PL

 IF EWAIT(T)>0 THEN INC EWAIT(T),-1

 'IS THE ENEMY FREEZED IN A WAIT STATE?
 IF EWAIT(T)=0 THEN

  'READ COLLISION WITH ANY PLAYER BUT NOT DRAW THE ENEMY - SET REAL Y
  PutEnemy(EX(T),RealY(T)+EY(T),EAN(T),ESide(T),EType(T),T,-1)

  ' SEARCH FOR A NEAR PLAYER
  DIST=2000
  FOR I=1 TO MAXPL
   TT=SQR( (EX(T)-X(I))^2 + (RealY(T)-RealY(I))^2 )
   IF TT < DIST THEN DIST=TT: PL=I
  NEXT I

  ' DECREASE HIT STATUS
  INC ECOMBO(T),-1
  IF ECOMBO(T)<0 THEN ECOMBO(T)=0


  ' SELECT THE ENEMY TYPE ---------------------------------------------------------------

  SELECT CASE EType(T)

   CASE 4 TO 6: 'BRED / JAKE / DUG --------------------------------------------------------------

    IF EMV(T)=1 OR (STE(T)>=70 AND STE(T)<=99) THEN INC EAniDelay(T)
    IF EAniDelay(T)>EAniSpd(T) THEN
     EAniDelay(T)=0
     INC EAN(T)
     IF STE(T)>40 AND STE(T)<52 THEN STE(T)=1
    ENDIF

    'WALKING
    IF STE(T)<50 THEN 'CAN WALK OR MAKE ANY ATTACK? -----------------

     'DECREASE TO WALK
     INC STE(T),-1

     IF STE(T)<1 THEN
      EBACK(T)=1: EBACKX(T)=1
      STE(T)=1 'KEEP STOPPED UNTIL BACK TO WALK RANDOMLY
      IF RND<0.3 THEN
       'WALKING WITH ATTENTION OR NORMAL ACCORDLY THE DISTANCE
       IF DIST<120 THEN STE(T)=20 ELSE STE(T)=40
       IF RND>0.6 AND DIST<80 THEN 'MAYBE GO BACK IF NEAR PLAYER IS PUNCHING
        IF Punch(PL)>0 AND EBACK(T)<>-1 THEN EBACK(T)=-1: STE(T)=40
       ENDIF
      ENDIF
     ELSE
      'GO BACKWARD IF TOO NEAR
      IF DIST<35 AND STE(T)<50 THEN EBACKX(T)=-1
      'GO TO DIRECTION OF THE NEAR PLAYER
      II=ESPD(T): TT=RealY(T)
      IF RealY(T)<=SMYA THEN INC RealY(T), ABS(ESPD(T))
      IF RealY(T)>=SMYB THEN INC RealY(T),-ABS(ESPD(T))
      IF RealY(T)>RealY(PL)+2 THEN INC RealY(T),-ESPD(T)
      IF RealY(T)<RealY(PL)-2 THEN INC RealY(T), ESPD(T)
      TT=(EBACKX(T)=-1)*30
      INC EX(T),((EX(T)<X(PL)-30+TT)*II*EBACKX(T))-((EX(T)>X(PL)+30-TT)*II*EBACKX(T))
      IF EX(T)<X(PL) THEN ESide(T)=4 ELSE ESide(T)=5
     ENDIF

    ELSE 'STE(T)>=50 - DON'T WALK! ---------------------------------
     ESPD(T)=0
    ENDIF

    'ENEMY STATUS / ACTION SCRIPTS -----------------------------------------------------

    SELECT CASE STE(T)

     'WALKING WITH ATTENTION -----------------------------------------------------------
     CASE 1 TO 20: 
      EAniSpd(T)=5
      ESPD(T)=((ES_SPD(T)+EAN(T)-10)/2)*EBACK(T)
      IF EAN(T)<9 OR EAN(T)>12 THEN EAN(T)=9

     'WALKING ---------------------------------------------------------------------------
     CASE 21 TO 40:
      EAniSpd(T)=5
      ESPD(T)=ES_SPD(T)*EBACK(T)
      IF EAN(T)>5 THEN EAN(T)=0
      IF STE(T)=21 AND DIST>120 THEN STE(T)=40

     'GETTING UP ------------------------------------------------------------------------
     CASE 52:
      EAN(T)=24: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=30
      'FIX ENEMY SIDE AFTER THROWED
      IF ESide(T)=6 THEN ESide(T)=4
      IF ESide(T)=7 THEN ESide(T)=5
     CASE 53:      
      ESPDX(T)=ESPDX(T)\2: IF EAniDelay(T)>20 OR EEnergy(T)<=0 THEN INC STE(T)
     CASE 54:
      EAN(T)=25: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=3: ESPDX(T)=0
      'ENEMY DEAD?
      IF EEnergy(T)<=0 THEN STE(T)=100: EAN(T)=50: EAniDelay(T)=0: EAniSpd(T)=1       
     CASE 55: IF EAN(T)>33 THEN EAN(T)=0: STE(T)=1    
     CASE 56: STE(T)=55

     'LEAVING THROUGH THE DOOR ----------------------------------------------------------
     CASE 57: ESide(T)=4: EAniDelay(T)=0: EAniSPD(T)=5: EAN(T)=35: INC STE(T)
     CASE 58: ESide(T)=4: INC RealY(T),0.35: IF EAN(T)>39 THEN EAN(T)=0: STE(T)=1

     'THROWED UPDOWN --------------------------------------------------------------------
     CASE 60:
      EAN(T)=21: STE(T)=61: EAniDelay(T)=0: EAniSpd(T)=15
      IF ESide(T)=4 THEN ESide(T)=7 ELSE ESide(T)=6
      INC EX(T),-ESPDX(T)
     CASE 61:
      IF EAniDelay(T)>10 THEN INC STE(T)
     CASE 62:
      EAN(T)=22: STE(T)=52: EAniDelay(T)=0: EAniSpd(T)=10

     'LEANING AGAINST THE WALL ----------------------------------------------------------
     CASE 64:
      EAN(T)=35: EAniDelay(T)=0: EAniSPD(T)=10
      STE(T)=65
      IF EX(T)<235 THEN STE(T)=35
     CASE 65:
      EAN(T)=35: EAniDelay(T)=0: EAniSPD(T)=10
      STE(T)=64
      IF EX(T)<235 THEN STE(T)=35

     'SEATED ----------------------------------------------------------------------------
     CASE 66:
      EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
      STE(T)=67
      IF EX(T)<235 THEN STE(T)=35
     CASE 67:
      EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
      STE(T)=66
      IF EX(T)<235 THEN STE(T)=35

     'PUNCH -----------------------------------------------------------------------------
     CASE 70: EAN(T)=13: EAniDelay(T)=0: EAniSpd(T)=4: INC STE(T)
     CASE 71:       
      'PUNCH THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
      IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=14 AND Special(PL)=0 THEN
       'PLAY_SAMPLE 27,PL 'PUNCHED THE PLAYER!
       PLSFX(PL)=27
       INC Energy(PL),-ES_POW(T)
       PHurted(PL)=2
       SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
       INC HCombo(PL),50
       WhoE(PL)=T 'SET WHO HURTED THE PLAYER
       STE(T)=72: EAniDelay(T)=0: EAniSpd(T)=4
      ENDIF
     IF EAN(T)>15 THEN STE(T)=72
     CASE 72: IF EAN(T)>15 THEN STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=4

     'KICK ------------------------------------------------------------------------------
     CASE 75: EAN(T)=16: EAniDelay(T)=0: EAniSpd(T)=1: INC STE(T)
     CASE 76:       
      'KICK THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
      IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=18 AND Special(PL)=0 THEN
       'PLAY_SAMPLE 27,PL 'KICKED THE PLAYER!
       PLSFX(PL)=27
       INC Energy(PL),-ES_POW(T)
       PHurted(PL)=2
       SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
       INC HCombo(PL),75
       WhoE(PL)=T 'SET WHO HURTED THE PLAYER
       STE(T)=77: EAniDelay(T)=0: EAniSpd(T)=3
      ENDIF
     IF EAN(T)>20 THEN STE(T)=77
     CASE 77: IF EAN(T)>20 THEN STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=4

     'JUMP KICKING ----------------------------------------------------------------------
     CASE 80: EAN(T)=6: EAniDelay(T)=0: EAniSpd(T)=5: INC STE(T)
     CASE 81:
      IF EAN(T)=7 THEN
       EAniDelay(T)=0: EAniSpd(T)=80: INC STE(T)
       ESJMP(T)=-12: ESPDX(T)=(ESide(T)=4)*2-(ESide(T)=5)*2
      ENDIF
     CASE 82:       
      EAN(T)=7
      INC EX(T),ESPDX(T)
      'KICK THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
      IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND Special(PL)=0 THEN
       PLSFX(PL)=27
       INC Energy(PL),-ES_POW(T)
       SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
       PHurted(PL)=2
       INC HCombo(PL),200
       WhoE(PL)=T 'SET WHO HURTED THE PLAYER
       STE(T)=83
      ENDIF
      IF EY(T)>=0 THEN STE(T)=83
     CASE 83:
      IF EY(T)>=0 THEN
       EAN(T)=8: EAniDelay(T)=0: EAniSpd(T)=12: INC STE(T)
       EY(T)=0: ESJMP(T)=0: ESPDX(T)=0: EBACKX(T)=0: EBACK(T)=0: ESPDX(T)=0
      ENDIF
     CASE 84: IF EAniSpd(T)>=8 THEN STE(T)=20

     'ENEMY IS DEAD ---------------------------------------------------------------------
     CASE 100: EAniSpd(T)=0: IF EAN(T)>60 THEN EAN(T)=50: INC STE(T) ' FLASH BODY AGAIN
     CASE 101: IF EAN(T)>60 THEN EEnergy(T)=-98: STE(T)=0: RealY(T)=999: Exit Sub 'REMOVE DEAD ENEMY

     'GRAPPLED BY A PLAYER --------------------------------------------------------------
     CASE 120 TO 170:
      'RESIST IF GRAPPLED FOR A WHILE WITHOUT BEING ATTACK
      EAN(T)=22
     INC STE(T)
      FOR I=1 TO MAXPL 
       IF PlType(I)=3 AND SB THEN INC STE(T),-1 'HAGGAR KEEP GRAPPLE FOR MORE TIME
       'RELEASE IF PLAYER USE SPECIAL OR JUMP (CODY OR GUY)
       IF Special(I)=1 OR (PlType(I)<3 AND Jump(I)>0) THEN STE(T)=170: Grap(I)=0: GrapE(I)=0: Kick(I)=0: Punch(I)=1
       IF GrapE(I)=T THEN
        EX(T)=X(I)+(SIDE(I)=4)*8-(SIDE(I)=5)*8: RealY(T)=RealY(I)+4-(PlType(I)=3)*18
        IF PlType(I)=3 THEN
         EY(T)=Y(I): ESJMP(T)=0: ESPDY(T)=0
         INC EX(T),(SIDE(I)=4)*(32-(AN(I)=32)*24)-(SIDE(I)=5)*(32-(AN(I)=32)*24)
         IF AN(I)=32 THEN EAN(T)=21: EY(T)=Y(I)-10
         'PILE DRIVER ADJUST ENEMY POSITION AND SIDE
         SELECT CASE Jump(I)
          CASE 1,2,9 TO 10,21,22,29 TO 30: EY(T)=Y(I)+8
          CASE 38: ESIDE(T)=(SIDE(I)=4)*7+(SIDE(I)=5)*6        
          CASE 33:
           STE(T)=60
           ESPDX(T)=(SIDE(I)=4)*6-(SIDE(I)=5)*6: RealY(T)=RealY(I)
           EAniDelay(T)=0:EAniSpd(T)=1: ESJMP(T)=-6: ESPDY(T)=-6
           Grap(I)=0: GrapE(I)=0: Kick(I)=0: Punch(I)=1
           Exit Sub
         END SELECT
        ENDIF
        IF STE(T)>=170 THEN
         STE(T)=52: EAniDelay(T)=0:EAniSpd(T)=3: ESJMP(T)=-3: ESPDY(T)=-3: RealY(T)=RealY(I)
         Grap(I)=0: GrapE(I)=0: Combo(I)=0: Punch(I)=2: AniDelay(I)=0: AniSpd(I)=0
        ENDIF
       ENDIF
      NEXT I

     'RETURN TO THE ORIGINAL STATE IF SOMETHING GOES WRONG ON GAPPLE
     CASE >=171:
      STE(T)=20: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0: ESPDY(T)=0

    END SELECT 'END ACTION SCRIPTS BRED / JAKE -----------------------------------------


   CASE 7 TO 8: 'J / TWO P ----------------------------------------------------------------------

    IF EMV(T)=1 OR (STE(T)>=70 AND STE(T)<=99) THEN INC EAniDelay(T)
    IF EAniDelay(T)>EAniSpd(T) THEN
     EAniDelay(T)=0
     INC EAN(T)
     IF STE(T)>20 AND STE(T)<52 THEN STE(T)=1
    ENDIF

    'WALKING
    IF STE(T)<50 THEN 'CAN WALK OR MAKE ANY ATTACK? -----------------

     'DECREASE TO WALK
     INC STE(T),-1

     IF STE(T)<1 THEN
      EBACK(T)=1: EBACKX(T)=1
      STE(T)=1 'KEEP STOPPED UNTIL BACK TO WALK RANDOMLY
      IF RND<0.3 THEN
       'ALWAYS WALKING WITH ATTENTION
       STE(T)=20
       IF RND>0.6 AND DIST<80 THEN 'MAYBE GO BACK IF NEAR PLAYER IS PUNCHING
        IF Punch(PL)>0 AND EBACK(T)<>-1 THEN EBACK(T)=-1: STE(T)=40
       ENDIF
      ENDIF
     ELSE
      'GO BACKWARD IF TOO NEAR
      IF DIST<35 AND STE(T)<50 THEN EBACKX(T)=-1
      'GO TO DIRECTION OF THE NEAR PLAYER
      II=ESPD(T): TT=RealY(T)
      IF RealY(T)<=SMYA THEN INC RealY(T), ABS(ESPD(T))
      IF RealY(T)>=SMYB THEN INC RealY(T),-ABS(ESPD(T))
      IF RealY(T)>RealY(PL)+2 THEN INC RealY(T),-ESPD(T)
      IF RealY(T)<RealY(PL)-2 THEN INC RealY(T), ESPD(T)
      TT=(EBACKX(T)=-1)*30+(SIDE(PL)=5)*40-(SIDE(PL)=4)*40
      INC EX(T),((EX(T)<X(PL)-20+TT)*II*EBACKX(T))-((EX(T)>X(PL)+20-TT)*II*EBACKX(T))
      IF EX(T)<X(PL) THEN ESide(T)=4 ELSE ESide(T)=5
     ENDIF

    ELSE 'STE(T)>=50 - DON'T WALK! ---------------------------------
     ESPD(T)=0
    ENDIF

    'ENEMY STATUS / ACTION SCRIPTS -----------------------------------------------------

    SELECT CASE STE(T)

     'WALKING WITH ATTENTION -----------------------------------------------------------
     CASE 1 TO 20: 
      EAniSpd(T)=5-(EBACK(T)=-1)*3
      ESPD(T)=((ES_SPD(T)+EAN(T)-10)/2)*EBACK(T)*((EBACK(T)=-1)*2+(EBACK(T)>=0))
      IF EAN(T)<9 OR EAN(T)>12 THEN EAN(T)=9

     'GETTING UP ------------------------------------------------------------------------
     CASE 52:
      EAN(T)=24: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=30
      'FIX ENEMY SIDE AFTER THROWED
      IF ESide(T)=6 THEN ESide(T)=4
      IF ESide(T)=7 THEN ESide(T)=5
     CASE 53:      
      ESPDX(T)=ESPDX(T)\2: IF EAniDelay(T)>20 OR EEnergy(T)<=0 THEN INC STE(T)
     CASE 54:
      EAN(T)=24: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=3: ESPDX(T)=0
      'ENEMY DEAD?
      IF EEnergy(T)<=0 THEN STE(T)=100: EAN(T)=50: EAniDelay(T)=0: EAniSpd(T)=1       
     CASE 55:
      EAN(T)=24: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=10
     CASE 56: EAN(T)=9: STE(T)=1

     'THROWED UPDOWN --------------------------------------------------------------------
     CASE 60:
      EAN(T)=21: STE(T)=61: EAniDelay(T)=0: EAniSpd(T)=15
      IF ESide(T)=4 THEN ESide(T)=7 ELSE ESide(T)=6
      INC EX(T),-ESPDX(T)
     CASE 61:
      IF EAniDelay(T)>10 THEN INC STE(T)
     CASE 62:
      EAN(T)=22: STE(T)=52: EAniDelay(T)=0: EAniSpd(T)=10

     'LEANING AGAINST THE WALL ----------------------------------------------------------
     CASE 64:
      EAN(T)=35: EAniDelay(T)=0: EAniSPD(T)=10
      STE(T)=65
      IF EX(T)<235 THEN STE(T)=35
     CASE 65:
      EAN(T)=35: EAniDelay(T)=0: EAniSPD(T)=10
      STE(T)=64
      IF EX(T)<235 THEN STE(T)=35

     'SEATED ----------------------------------------------------------------------------
     CASE 66:
      EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
      STE(T)=67
      IF EX(T)<235 THEN STE(T)=35
     CASE 67:
      EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
      STE(T)=66
      IF EX(T)<235 THEN STE(T)=35

     'PUNCH AND FAST BACKWARD -----------------------------------------------------------
     CASE 70: EAN(T)=13: EAniDelay(T)=0: EAniSpd(T)=4: INC STE(T)
     CASE 71:       
      'PUNCH THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
      IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=14 AND Special(PL)=0 THEN
       'PLAY_SAMPLE 27,PL 'PUNCHED THE PLAYER!
       PLSFX(PL)=27
       INC Energy(PL),-ES_POW(T)
       PHurted(PL)=2
       SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
       INC HCombo(PL),50
       WhoE(PL)=T 'SET WHO HURTED THE PLAYER
       STE(T)=72: EAniDelay(T)=0: EAniSpd(T)=4
      ENDIF
     IF EAN(T)>=15 THEN STE(T)=72
     CASE 72: IF EAN(T)>=15 THEN EBACK(T)=-1: STE(T)=10: EAniDelay(T)=0: EAniSpd(T)=2

     'J / TWO P DON'T KICK OR JUMP ----------------------------------
     CASE 75,80: STE(T)=1

     'ENEMY IS DEAD ---------------------------------------------------------------------
     CASE 100: EAniSpd(T)=0: IF EAN(T)>60 THEN EAN(T)=50: INC STE(T) ' FLASH BODY AGAIN
     CASE 101: IF EAN(T)>60 THEN EEnergy(T)=-98: STE(T)=0: RealY(T)=999: Exit Sub 'REMOVE DEAD ENEMY

     'GRAPPLED BY A PLAYER --------------------------------------------------------------
     CASE 120 TO 170:
      'RESIST IF GRAPPLED FOR A WHILE WITHOUT BEING ATTACK
      EAN(T)=22
     INC STE(T)
      FOR I=1 TO MAXPL 
       IF PlType(I)=3 AND SB THEN INC STE(T),-1 'HAGGAR KEEP GRAPPLE FOR MORE TIME
       'RELEASE IF PLAYER USE SPECIAL OR JUMP (CODY OR GUY)
       IF Special(I)=1 OR (PlType(I)<3 AND Jump(I)>0) THEN STE(T)=170: Grap(I)=0: GrapE(I)=0: Kick(I)=0: Punch(I)=1
       IF GrapE(I)=T THEN
        EX(T)=X(I)+(SIDE(I)=4)*8-(SIDE(I)=5)*8: RealY(T)=RealY(I)+4-(PlType(I)=3)*18
        IF PlType(I)=3 THEN
         EY(T)=Y(I): ESJMP(T)=0: ESPDY(T)=0
         INC EX(T),(SIDE(I)=4)*(32-(AN(I)=32)*24)-(SIDE(I)=5)*(32-(AN(I)=32)*24)
         IF AN(I)=32 THEN EAN(T)=21: EY(T)=Y(I)-10
         'PILE DRIVER ADJUST ENEMY POSITION AND SIDE
         SELECT CASE Jump(I)
          CASE 1,2,9 TO 10,21,22,29 TO 30: EY(T)=Y(I)+8
          CASE 38: ESIDE(T)=(SIDE(I)=4)*7+(SIDE(I)=5)*6        
          CASE 33:
           STE(T)=60
           ESPDX(T)=(SIDE(I)=4)*6-(SIDE(I)=5)*6: RealY(T)=RealY(I)
           EAniDelay(T)=0:EAniSpd(T)=1: ESJMP(T)=-6: ESPDY(T)=-6
           Grap(I)=0: GrapE(I)=0: Kick(I)=0: Punch(I)=1
           Exit Sub
         END SELECT
        ENDIF
        IF STE(T)>=170 THEN
         STE(T)=52: EAniDelay(T)=0:EAniSpd(T)=3: ESJMP(T)=-3: ESPDY(T)=-3: RealY(T)=RealY(I)
         Grap(I)=0: GrapE(I)=0: Combo(I)=0: Punch(I)=2: AniDelay(I)=0: AniSpd(I)=0
        ENDIF
       ENDIF
      NEXT I

     'RETURN TO THE ORIGINAL STATE IF SOMETHING GOES WRONG ON GAPPLE
     CASE >=171:
      STE(T)=20: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0: ESPDY(T)=0

    END SELECT 'END ACTION SCRIPTS J / TWO P --------------------------------------------



   CASE 9 TO 10: 'AXL / SLASH --------------------------------------------------------------------

    IF EMV(T)=1 OR (STE(T)>=70 AND STE(T)<=99) THEN INC EAniDelay(T)
    IF EAniDelay(T)>EAniSpd(T) THEN
     EAniDelay(T)=0
     INC EAN(T)
     IF STE(T)>40 AND STE(T)<52 THEN STE(T)=1
    ENDIF

    'WALKING
    IF STE(T)<50 THEN 'CAN WALK OR MAKE ANY ATTACK? -----------------

     'DECREASE TO WALK
     INC STE(T),-1

     IF STE(T)<1 THEN
      EBACK(T)=1: EBACKX(T)=1
      STE(T)=1: EAN(T)=0 'KEEP STOPPED UNTIL BACK TO WALK RANDOMLY
      IF RND<0.3 THEN
       STE(T)=40: EAN(T)=0
       'WALKING
       IF RND>0.6 AND DIST<80 THEN 'MAYBE GO BACK IF NEAR PLAYER IS PUNCHING
        IF Punch(PL)>0 AND EBACK(T)<>-1 THEN EBACK(T)=-1
       ENDIF
      ENDIF
     ELSE
      'GO BACKWARD IF TOO NEAR
      IF DIST<35 AND STE(T)<50 THEN EBACKX(T)=-1
      'GO TO DIRECTION OF THE NEAR PLAYER
      II=ESPD(T): TT=RealY(T)
      IF RealY(T)<=SMYA THEN INC RealY(T), ABS(ESPD(T))
      IF RealY(T)>=SMYB THEN INC RealY(T),-ABS(ESPD(T))
      IF RealY(T)>RealY(PL)+2 THEN INC RealY(T),-ESPD(T)
      IF RealY(T)<RealY(PL)-2 THEN INC RealY(T), ESPD(T)
      TT=(EBACKX(T)=-1)*30
      INC EX(T),((EX(T)<X(PL)-40+TT)*II*EBACKX(T))-((EX(T)>X(PL)+40-TT)*II*EBACKX(T))
      IF EX(T)<X(PL) THEN ESide(T)=4 ELSE ESide(T)=5
     ENDIF

    ELSE 'STE(T)>=50 - DON'T WALK! ---------------------------------
     ESPD(T)=0
    ENDIF

    'ENEMY STATUS / ACTION SCRIPTS -----------------------------------------------------

    SELECT CASE STE(T)

     'WALKING WITH ATTENTION -----------------------------------------------------------
     CASE 1 TO 40: 
      IF ESPD(T)=0 THEN STE(T)=1
      EAniSpd(T)=2
      ESPD(T)=ES_SPD(T)*EBACK(T)
      IF EAN(T)>6 THEN EAN(T)=1

     'GETTING UP ------------------------------------------------------------------------
     CASE 52:
      EAN(T)=24: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=30
      'FIX ENEMY SIDE AFTER THROWED
      IF ESide(T)=6 THEN ESide(T)=4
      IF ESide(T)=7 THEN ESide(T)=5
     CASE 53:      
      ESPDX(T)=ESPDX(T)\2: IF EAniDelay(T)>20 OR EEnergy(T)<=0 THEN INC STE(T)
     CASE 54:
      EAN(T)=24: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=3: ESPDX(T)=0
      'ENEMY DEAD?
      IF EEnergy(T)<=0 THEN STE(T)=100: EAN(T)=50: EAniDelay(T)=0: EAniSpd(T)=1       
     CASE 55:
      EAN(T)=24: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=10
     CASE 56: EAN(T)=6: STE(T)=1

     'THROWED UPDOWN --------------------------------------------------------------------
     CASE 60:
      EAN(T)=21: STE(T)=61: EAniDelay(T)=0: EAniSpd(T)=15
      IF ESide(T)=4 THEN ESide(T)=7 ELSE ESide(T)=6
      INC EX(T),-ESPDX(T)
     CASE 61:
      IF EAniDelay(T)>10 THEN INC STE(T)
     CASE 62:
      EAN(T)=22: STE(T)=52: EAniDelay(T)=0: EAniSpd(T)=10

     'LEANING AGAINST THE WALL ----------------------------------------------------------
     CASE 64:
      EAN(T)=35: EAniDelay(T)=0: EAniSPD(T)=10
      STE(T)=65
      IF EX(T)<235 THEN STE(T)=35
     CASE 65:
      EAN(T)=35: EAniDelay(T)=0: EAniSPD(T)=10
      STE(T)=64
      IF EX(T)<235 THEN STE(T)=35

     'SEATED ----------------------------------------------------------------------------
     CASE 66:
      EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
      STE(T)=67
      IF EX(T)<235 THEN STE(T)=35
     CASE 67:
      EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
      STE(T)=66
      IF EX(T)<235 THEN STE(T)=35

     'BLOCKING --------------------------------------------------------------------------
     CASE 68:
      EAN(T)=19: EAniDelay(T)=0: EAniSPD(T)=50
      STE(T)=69
      IF Hitting(EHIT(T))<=0 THEN STE(T)=1
     CASE 69:
      EAN(T)=19: EAniDelay(T)=0: EAniSPD(T)=50
      STE(T)=68
      IF Hitting(EHIT(T))<=0 THEN STE(T)=1

     'PUNCH -----------------------------------------------------------------------------
     CASE 70: EAN(T)=12: EAniDelay(T)=0: EAniSpd(T)=3: INC STE(T)
     CASE 71:       
      'PUNCH THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
      IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=14 AND Special(PL)=0 THEN
       'PLAY_SAMPLE 27,PL 'PUNCHED THE PLAYER!
       PLSFX(PL)=27
       INC Energy(PL),-ES_POW(T)
       PHurted(PL)=2
       SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
       INC HCombo(PL),350
       WhoE(PL)=T 'SET WHO HURTED THE PLAYER
       STE(T)=72: EAniDelay(T)=0: EAniSpd(T)=4
      ENDIF
     IF EAN(T)>15 THEN STE(T)=72
     CASE 72: IF EAN(T)>15 THEN STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=4

     'KICK ------------------------------------------------------------------------------
     CASE 75: EAN(T)=16: EAniDelay(T)=0: EAniSpd(T)=2: INC STE(T)
     CASE 76:       
      'KICK THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
      IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=18 AND Special(PL)=0 THEN
       'PLAY_SAMPLE 27,PL 'KICKED THE PLAYER!
       PLSFX(PL)=27
       INC Energy(PL),-ES_POW(T)
       PHurted(PL)=2
       SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
       INC HCombo(PL),75
       WhoE(PL)=T 'SET WHO HURTED THE PLAYER
       STE(T)=77: EAniDelay(T)=0: EAniSpd(T)=3
      ENDIF
     IF EAN(T)>=18 THEN STE(T)=77
     CASE 77: IF EAN(T)>=18 THEN STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=4

     'AXL / SLASH DON'T JUMP ------------------------------------------------------------
     CASE 80: STE(T)=1

     'ENEMY IS DEAD ---------------------------------------------------------------------
     CASE 100: EAniSpd(T)=0: IF EAN(T)>60 THEN EAN(T)=50: INC STE(T) ' FLASH BODY AGAIN
     CASE 101: IF EAN(T)>60 THEN EEnergy(T)=-98: STE(T)=0: RealY(T)=999: Exit Sub 'REMOVE DEAD ENEMY

     'GRAPPLED BY A PLAYER --------------------------------------------------------------
     CASE 120 TO 170:
      'RESIST IF GRAPPLED FOR A WHILE WITHOUT BEING ATTACK
      EAN(T)=22
      INC STE(T)
      FOR I=1 TO MAXPL 
       IF PlType(I)=3 AND SB THEN INC STE(T),-1 'HAGGAR KEEP GRAPPLE FOR MORE TIME
       'RELEASE IF PLAYER USE SPECIAL OR JUMP (CODY OR GUY)
       IF Special(I)=1 OR (PlType(I)<3 AND Jump(I)>0) THEN STE(T)=170: Grap(I)=0: GrapE(I)=0: Kick(I)=0: Punch(I)=1
       IF GrapE(I)=T THEN
        EX(T)=X(I)+(SIDE(I)=4)*8-(SIDE(I)=5)*8: RealY(T)=RealY(I)+4-(PlType(I)=3)*18
        IF PlType(I)=3 THEN
         EY(T)=Y(I): ESJMP(T)=0: ESPDY(T)=0
         INC EX(T),(SIDE(I)=4)*(32-(AN(I)=32)*24)-(SIDE(I)=5)*(32-(AN(I)=32)*24)
         IF AN(I)=32 THEN EAN(T)=21: EY(T)=Y(I)-10
         'PILE DRIVER ADJUST ENEMY POSITION AND SIDE
         SELECT CASE Jump(I)
          CASE 1,2,9 TO 10,21,22,29 TO 30: EY(T)=Y(I)+8
          CASE 38: ESIDE(T)=(SIDE(I)=4)*7+(SIDE(I)=5)*6        
          CASE 33:
           STE(T)=60
           ESPDX(T)=(SIDE(I)=4)*6-(SIDE(I)=5)*6: RealY(T)=RealY(I)
           EAniDelay(T)=0:EAniSpd(T)=1: ESJMP(T)=-6: ESPDY(T)=-6
           Grap(I)=0: GrapE(I)=0: Kick(I)=0: Punch(I)=1
           Exit Sub
         END SELECT
        ENDIF
        IF STE(T)>=170 THEN
         STE(T)=52: EAniDelay(T)=0:EAniSpd(T)=3: ESJMP(T)=-3: ESPDY(T)=-3: RealY(T)=RealY(I)
         Grap(I)=0: GrapE(I)=0: Combo(I)=0: Punch(I)=2: AniDelay(I)=0: AniSpd(I)=0
        ENDIF
       ENDIF
      NEXT I

     'RETURN TO THE ORIGINAL STATE IF SOMETHING GOES WRONG ON GAPPLE
     CASE >=171:
      STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0: ESPDY(T)=0

    END SELECT 'END ACTION SCRIPTS AXL / SLASH ------------------------------------------


  END SELECT 'END OF SELECT ENEMY TYPE --------------------------------------------------


  'GENERIC RULES FOR ALL THE ENEMIES ----------------------------------------------------

  INC EX(T),ESPDX(T)

  IF EX(T)>R_SCR THEN EX(T)=R_SCR
     
  'GRAVITY
  INC EY(T),ESJMP(T)

  'READ COLLISION - COLLIDED WITH OTHER THROWED ENEMY? IS_TR = IS THROWED?
  IS_TR=0
  IF ETR(T)=0 THEN
  'WHICH SIDE THE ENEMY MUST FALL?
   IF COLLIDE(0)=&HFF00FF THEN TESIDE=-1: IS_TR=1:InsertWait(0,T,2)
   IF COLLIDE(0)=&HFF00BF THEN TESIDE= 1: IS_TR=1:InsertWait(0,T,2)
  ELSE
   InsertWait(0,T,1)
  ENDIF

  'IF IS NOT A JUMP KICK, THEN ENEMY IS FALLING HURTED
  IF (STE(T)<80 OR STE(T)>=90) AND NOT(PlType(PL)=3 AND GrapE(PL)=T) THEN 
   'KO CONTROL - ENEMY FALLING
   IF EY(T)>0 THEN 
    ESJMP(T)=-ABS(ESJMP(T))\2.5: EY(T)=0: ESPDX(T)=ESPDX(T)/2
    EAN(T)=24: EAniDelay(T)=0: EAniSpd(T)=20: STE(T)=52
    IF ETR(T)>0 THEN
     'ONLY TO GET THE COORDINATES TO THE SMOKE
     PutEnemy(EX(T),RealY(T)+EY(T),EAN(T),ESide(T),EType(T),T,-2)
     ETR(T)=0: PLAY_SAMPLE 3,4 'HIT THE FLOOR
     InsertHit(XTHit-10-RND*10,YTHit,2) 'SMOKE
     InsertHit(XTHit+10+RND*10,YTHit,2)
     INC EEnergy(T),-7+ES_DEF(T) 'LOOSE ENERGY WHEN THROWED
     'DEAD SOUND AND SCORE
     IF EEnergy(T)<=0 THEN EEnergy(T)=-99: PLAY_SAMPLE 10,4: INC SCORE(PL),ESCORE(T): EXIT SUB
    ELSE
     IF ESJMP(T)<0 THEN
      'ONLY TO GET THE COORDINATES TO THE SMOKE
      PutEnemy(EX(T),RealY(T)+EY(T),EAN(T),ESide(T),EType(T),T,-2)
      PLAY_SAMPLE 3,4 'HIT THE FLOOR
      InsertHit(XTHit-10-RND*10,YTHit,2) 'SMOKE
      InsertHit(XTHit+10+RND*10,YTHit,2)
     ENDIF
    ENDIF
   ELSEIF EY(T)<0 THEN
    INC ESJMP(T),1.5 'GRAVITY FORCE
    STE(T)=51
   ENDIF
  ELSE 'BUT IF IS A JUMP KICK, APPLY GRAVITY
   IF EY(T)<0 THEN INC ESJMP(T),1.5 'GRAVITY FORCE
   IF EY(T)>0 THEN EY(T)=0
  ENDIF

  'FORCE KO (DEAD) IF NO ENERGY (WALKING OR GRAPPLED)
  IF EEnergy(T)<=0 AND (EAN(T)<=40 OR EAN(T)>=120) THEN IS_TR=2 

  'REMOVE ATTACK COLLISION FROM THE ENEMY IF OUT OF VERTICAL RANGE
  IF COLLIDE(0)>0 AND (RealY(T)<RealY(PL)-5 or RealY(T)>RealY(PL)+5) THEN COLLIDE(0)=0

  ' IF HURTED BY ANY PLAYER (I) -------------------------------------------------------

  FOR I=1 TO MAXPL ' * SCAN FOR BOTH PLAYERS *

   'CANCEL SCAN IF PLAYER ALREADY GRAPPLED OTHER ENEMY
   IF GrapE(I)<>T AND GrapE(I)>0 AND NOT(PlType(I)=3 AND AN(I)=32) THEN CONTINUE FOR 

   ' CONDITIONS TO BE HURTED:
   ' 1 - C_A: SPECIAL MOVE
   ' 2 - C_B: NOT JUMPING OR FALLING
   ' 3 - C_C: GRAPPLED OR ATTACKED BY ANY PLAYER
   ' 4 - C_D: ENEMY WAITING FOR RECEIVE OTHER COMBO (ECOMBO)
   ' 5 - DETECTED COLLISION PLAYER'S ATTACK (&HFF0000) OR IS_TR
   ' 6 - ANIMATION OF THE NEAR PLAYER MUST BE CHANGED (AN <> ANANT)
   C_A=(Special(I)=1 AND (STE(T)<50 OR STE(T)>62))
   C_B=(STE(T)<50 AND EY(T)=0 AND ESJMP(T)=0)
   C_C=(STE(T)>=120 AND GrapE(I)=T AND (Grap(I)=21 OR Grap(I)=22))
   C_D=(ECOMBO(T)<1)
   C_E=-300*(GrapE(I)=T AND PlType(I)=3 AND STE(T)>=120 AND Jump(PL)>30)
   IF (COLLIDE(I)=&HFF0000-C_E OR IS_TR) AND (AN(I)<>ANANT(I) OR C_A OR C_B OR C_C) AND C_D THEN

    Hit(I)=T
    EHIT(T)=I
    Hitting(I)=8

    'AXL / SLASH BLOCKING - REMOVE COLLISION AND EXIT SUB
    IF (Etype(T)=9 OR Etype(T)=10) THEN
     IF GrapE(I)<>T AND EAN(T)<=19 AND (Kick(I)>0 OR Punch(I)>0) THEN
      IF (RND<0.8 AND COLLIDE(I)>0) OR (STE(T)=68 OR STE(T)=69) THEN 
       InsertHit(XTHit,YTHit,1)
       COLLIDE(I)=0: STE(T)=68: PLAY_SAMPLE 29,3: EXIT SUB
      ENDIF
     ENDIF
    ENDIF
     
    'HIT AND LOOSE ENERGY ONLY IF IS NOT THROW OR GRAPPLE THE ENEMY
    IF Grap(I)<>21 AND Grap(I)<>22 THEN 
     InsertHit(XTHit,YTHit,1)
     InsertWait(I,T,2)
     INC EEnergy(T),-10+ES_DEF(T)
     IF C_A THEN INC EEnergy(T),-SPECIAL(I)*10: INC SCORE(I),300     
     STE(T)=50: EAniDelay(T)=0: EAniSpd(T)=10
     'SOME SOUND CONTROLE WHEN ENEMY IS HURTED:
     '1 - ENEMY PUNCHED SOUND OVERWRITING PREVIOUS PLAYER SOUND (LIKE THE ARCADE)
     '2 - IF IS A JUMP KICK, PLAY A KNEE SOUND STOPPING ANY ENEMY CHANNEL SOUND
     '3 - IF IT'S HURTED BY OTHER THROWED ENEMY THEN USE THE ONFLOOR SOUND (FASTER)
     IF Combo(I)<4 THEN
      IF Jump(I)=0 AND IS_TR<>1 THEN PLSFX(I)=27           '1
      IF Jump(I)>0 THEN PLSFX(I)=0: PLAY_SAMPLE 24,4,,100  '2
      IF IS_TR THEN PLAY_SAMPLE 3,3,30000,100              '3
     ENDIF
     INC SCORE(I),100
    ENDIF
    EAniDelay(T)=0: EAniSpd(T)=12

    'HITTED IN THE FACE OR IN THE STOMACH?
    IF Combo(I)<=2 THEN EAN(T)=22 ELSE EAN(T)=21
    ECOMBO(T)=5
    KO=0

    ' IF PLAYER IS HURTING ENEMY WHEN GRAPPLED
    IF Grap(I)=21 AND GrapE(I)=T THEN
     EX(T)=X(I)+(SIDE(I)=4)*8-(SIDE(I)=5)*8: RealY(T)=RealY(I)+6-(PlType(I)=3)*12
     IF PlType(I)=3 THEN INC EX(T),(SIDE(I)=4)*8-(SIDE(I)=5)*8
     ESide(T)=(SIDE(I)=4)*5+(SIDE(I)=5)*4
     INC SCORE(I),100
     INC Combo(I)
     InsertHit(XTHit,YTHit,2)
     InsertWait(I,T,2)
     Grap(I)=20: STE(T)=120: INC EEnergy(T),-15+ES_DEF(T): PLSFX(I)=24
     ' IF KILLED BY THE PLAYER OR COMBO WAS FINISHED
     IF Combo(I)>=3 OR EEnergy(T)<=0 THEN
      INC SCORE(I),100
      Grap(I)=0: GrapE(I)=0: KO=1: Combo(I)=0
      Punch(I)=1: AniDelay(I)=0: AniSpd(I)=1: Kick(I)=0
     ENDIF
    ENDIF

    ' THROW THE ENEMY WHEN PUNCHING AND KEEPING PRESSED UP OR DOWN 
    IF MVUD(I)<>0 AND (Combo(I)>=3-(PlType(I)=3) OR (Grap(I)=20 AND PlType(I)=3)) THEN
     INC SCORE(I),50
     EX(T)=X(I)+(SIDE(I)=4)*8-(SIDE(I)=5)*8: RealY(T)=RealY(I)-4
     Grap(I)=22: GrapE(I)=T: AN(I)=22: Hitting(I)=0
    ENDIF

    ' SET WHAT PLAYER IS THROWING THE ENEMY AND CALL THROW/SUPLEX ANIMATION
    IF (Grap(I)=22 AND GrapE(I)=T) THEN Combo(I)=0: KO=2: ETR(T)=I: Punch(I)=131

    ' HIT ENEMIES WHEN PILE DRIVING OTHER ENEMY
    IF PlType(I)=3 AND AN(I)=32 THEN
     Hit(I)=T
     EAniSpd(T)=999: EANiDelay(T)=0: ESJMP(T)=-10: EAN(T)=23
     ESPDY(T)=0 
     STE(T)=51: InsertWait(I,T,4)
     RealY(T)=RealY(I)-4
     ESPDX(T)=(SIDE(I)=4)*4-(SIDE(I)=5)*4
     Exit Sub
    ENDIF

    ' FALL WHEN:
    ' COMBO OR SPECIAL OR KICKED OR NO ENERGY OR COLLIDED WITH OTHER THROWED ENEMY
    IF KO OR AN(I)=18+(PlType(I)=1) OR C_A OR Kick(I)=1 OR EEnergy(T)<=0 OR IS_TR THEN
     Hit(I)=T
     STE(T)=51: EAniSpd(T)=999: EANiDelay(T)=0: ESJMP(T)=-10: EAN(T)=23
     ESPDY(T)=0 
     IF Punch(I)>100 AND Punch(I)<=110) THEN Punch(I)=1: Jump(I)=0: GrapE(I)=0: Grap(I)=0
  
     ' SET SIDE OF THE SHAPE AND THROWING
     IF KO=2 OR (MVUD(I)<>0 AND Combo(I)>=3) THEN       
      IF PlType(I)<3 THEN
       SIDE(I)=5-(SIDE(I)=5)
       MVLR(I)=1-(SIDE(I)=5)*2
      ENDIF
      STE(T)=60: InsertWait(I,T,3)
      ESJMP(T)=-12: RealY(T)=RealY(I)-4
      ESIDE(T)=(Side(I)=4)*5+(Side(I)=5)*4
      IF Combo(I)<3 THEN ESIDE(T)=5-(MVLR(I)=1): Side(I)=4+(MVLR(I)=1)
      'ENEMY THROWED SIDE
      ESPDX(T)=(ESIDE(T)=4)*10-(ESIDE(T)=5)*10
     ELSE       
      'ENEMY PUNCHED FALLING SIDE
      ESPDX(T)=(ESIDE(T)=5)*7-(ESIDE(T)=4)*7
     ENDIF

     'IF ENEMIES ATTACKED BY OTHERS THROWED - MAKE THEM ONLY FALL ONLY IN Y AXIS 
     IF IS_TR=1 THEN
      ESPDX(T)=(COLLIDE(0)=&HFF00BF)*6-(COLLIDE(0)=&HFF00FF)*6: INC SCORE(ETR(I)),50
     ENDIF
     ELSE
     INC AniSPD(I),2 'DELAY HIT ANIMATION FOR A WHILE
    ENDIF

   ENDIF
   ' END OF HURTING COLLISION DETECTION -----------------------------------------------------

   ' IS THE ENEMY GRAPPLED BY THE PLAYER?
   IF Grap(I)=0 AND GrapE(I)=0 THEN
    ' GRAPPLE ENEMY IF COLLIDED
    IF COLLIDE(I)=&HFFFF00 AND STE(T)<50 AND EY(T)=0 AND ESJMP(T)=0 AND MVLR(I)<>0 AND Punch(I)<100 THEN
     Hit(I)=T: GrapE(I)=T: Punch(I)=100: STE(T)=120: Grap(I)=20: Combo(I)=0
     EX(T)=X(I)+(SIDE(I)=4)*8-(SIDE(I)=5)*8: RealY(T)=RealY(I)+4-(PlType(I)=3)*14
     IF PlType(I)=3 THEN INC EX(T),(SIDE(I)=4)*32-(SIDE(I)=5)*32
     ESide(T)=(SIDE(I)=4)*5+(SIDE(I)=5)*4
    ENDIF
   ELSEIF GrapE(I)=T THEN 'IS THE ENEMY GRAPPLED?
    'FORCE ENEMY POSITION WHEN THROW OR SUPLEX
    SELECT CASE PlType(I)
  
     'GUY THROW
     CASE 1,2:
      IF AN(I)=22 THEN 'GRAPPLE
       ESide(T)=(SIDE(I)=4)*4+(SIDE(I)=5)*5
       EX(T)=X(I)+(SIDE(I)=4)*10-(SIDE(I)=5)*10: RealY(T)=RealY(I)-5
       EAN(T)=23: ESPDY(T)=0: ESJMP(T)=-10: EY(T)=-1
       ESPDX(T)=(SIDE(I)=5)*10-(SIDE(I)=4)*10       
       INC SCORE(I),10: INC EEnergy(T),-1
      ENDIF
      IF AN(I)=23 THEN 'THROW
       ESIDE(T)=(Side(I)=4)*4+(Side(I)=5)*5: RealY(T)=RealY(I)
       EAN(T)=23: STE(T)=51
       EAniDelay(T)=0: EAniSpd(T)=15
      ENDIF

     'HAGGAR SUPLEX 
     CASE 3:
      IF AN(I)=22 THEN
       EX(T)=X(I)+(SIDE(I)=4)*10-(SIDE(I)=5)*10: RealY(T)=RealY(I)-24
       ESide(T)=(SIDE(I)=4)*4+(SIDE(I)=5)*5
       EAN(T)=23: ESPDY(T)=0: ESJMP(T)=1: Special(I)=3
      ENDIF 
      IF AN(I)=23 THEN 'MAX SUPLEX
       EX(T)=X(I)+(SIDE(I)=5)*64-(SIDE(I)=4)*64: RealY(T)=RealY(I)-4
       ESide(T)=(SIDE(I)=4)*7+(SIDE(I)=5)*6
       EAN(T)=21: ESPDY(T)=0: ESJMP(T)=5: Special(I)=3
      ENDIF
      IF AN(I)=43 THEN 'GETUP
       ESPDX(T)=(SIDE(I)=5)*4-(SIDE(I)=4)*4: ESJMP(T)=-4: ESPDY(T)=-4
       ESide(T)=(SIDE(I)=4)*4+(SIDE(I)=5)*5
       Special(I)=0
       ESPDY(T)=0: EAN(T)=23: STE(T)=51
       INC SCORE(I),20
       INC EEnergy(T),-15+ES_DEF(T)
      ENDIF
    END SELECT 

   ENDIF 'END OF GRAPPLE VERIFICATION

  NEXT I ' * END OF PLAYER SCAN *
 
  'IF NOT ATTACKED, THEN ENEMY TRY TO ATTACK - ONLY WHEN IN THE VERTICAL RANGE
  IF (RealY(T)>=RealY(PL)-5 AND RealY(T)<=RealY(PL)+5) AND STE(T)<=40 THEN
   'ATTACK WHEN DISTANCE IS OK
   IF DIST>30 AND DIST<60 THEN 
    IF RND>0.95 THEN STE(T)=75 'KICK
    IF RND<0.05 THEN STE(T)=70 'PUNCH
    IF RND<0.01 THEN STE(T)=80 'JUMP KICK
   ENDIF
  ENDIF

  'THE ENEMY IS DEAD?
  IF EEnergy(T)>-99 AND EEnergy(T)<=0 THEN
   EEnergy(T)=-99: PLAY_SAMPLE 10,4 'DEAD SOUND
   INC SCORE(EHIT(T)),ESCORE(T) 'INC PLAYER SCORE
  ENDIF

 ENDIF ' END OF WAIT FOR HITS -----------------------------------------------------------  

END SUB

