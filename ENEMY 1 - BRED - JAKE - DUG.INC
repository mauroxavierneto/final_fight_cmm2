SUB Enemy_BRED_JAKE_DUG(T,PL)
 LOCAL II,TT

 IF EMV(T)=1 OR (STE(T)>=70 AND STE(T)<=99) THEN INC EAniDelay(T)
 IF EAniDelay(T)>EAniSpd(T) THEN
  EAniDelay(T)=0
  INC EAN(T)
  IF STE(T)>40 AND STE(T)<52 THEN STE(T)=1
 ENDIF

 'WALKING
 IF STE(T)<50 AND EMV(T)>0 THEN 'CAN WALK OR MAKE ANY ATTACK? -----------------

  'DECREASE TO WALK
  INC STE(T),-1

  IF STE(T)<1 THEN
   EBACK(T)=1: EBACKX(T)=1
   STE(T)=1: EAN(T)=9 'KEEP STOPPED UNTIL BACK TO WALK RANDOMLY
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
   INC EX(T),((EX(T)<X(PL)-45+TT)*II*EBACKX(T))-((EX(T)>X(PL)+45-TT)*II*EBACKX(T))
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
  CASE 51: 'NOTHING 
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
   EAN(T)=21:IF EAniDelay(T)>10 THEN INC STE(T)
  CASE 62:
   EAN(T)=22: STE(T)=52: EAniDelay(T)=0: EAniSpd(T)=10

  'LEANING AGAINST THE WALL ----------------------------------------------------------
  CASE 64:
   EAN(T)=35: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=65
   IF EX(T)<245+RXX THEN STE(T)=35
  CASE 65:
   EAN(T)=35: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=64
   IF EX(T)<245+RXX THEN STE(T)=35

  'SEATED ----------------------------------------------------------------------------
  CASE 66:
   EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=67: EMV(T)=0
   IF EX(T)<245+RXX THEN STE(T)=65
  CASE 67:
   EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=66: EMV(T)=0
   IF EX(T)<245+RXX THEN STE(T)=65

  'SEATED CROUCHED -------------------------------------------------------------------
  CASE 68:
   EAN(T)=6: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=69: EMV(T)=0
   IF EX(T)<245+RXX THEN STE(T)=65
  CASE 69:
   EAN(T)=6: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=68: EMV(T)=0
   IF EX(T)<245+RXX THEN STE(T)=65

  'PUNCH -----------------------------------------------------------------------------
  CASE 70: EAN(T)=13: EAniDelay(T)=0: EAniSpd(T)=4: INC STE(T)
  CASE 71:       
   'PUNCH THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
   IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=14 AND Special(PL)=0 THEN
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
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
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
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
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
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
  CASE 101: IF EAN(T)>60 THEN EEnergy(T)=-99: STE(T)=0: RealY(T)=999: Exit Sub 'REMOVE DEAD ENEMY

  'GRAPPLED BY A PLAYER --------------------------------------------------------------
  CASE 120 TO 170: GrapPlayer(T) 

  'RETURN TO THE ORIGINAL STATE IF SOMETHING GOES WRONG ON GAPPLE
  CASE >=171:
   STE(T)=20: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0: ESPDY(T)=0

  'FOR ALL OTHER CASES, GET UP!
  CASE ELSE: EAN(T)=1: STE(T)=1

 END SELECT 'END ACTION SCRIPTS BRED / JAKE -----------------------------------------

END SUB
