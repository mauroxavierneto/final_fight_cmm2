SUB Enemy_HOLLY_WOOD_EL_GADO(T,PL)
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
   INC EX(T),((EX(T)<X(PL)-70+TT)*II*EBACKX(T))-((EX(T)>X(PL)+70-TT)*II*EBACKX(T))
   IF EX(T)<X(PL) THEN ESide(T)=4 ELSE ESide(T)=5
  ENDIF

 ELSE 'STE(T)>=50 - DON'T WALK! ---------------------------------
  ESPD(T)=0
 ENDIF

 'ENEMY STATUS / ACTION SCRIPTS -----------------------------------------------------

 SELECT CASE STE(T)

  'WALKING --------------------------------------------------------------------------
  CASE 1 TO 40: 
   IF ESPD(T)=0 THEN STE(T)=1
   EAniSpd(T)=2
   ESPD(T)=ES_SPD(T)*EBACK(T)
   IF EAN(T)>5 THEN EAN(T)=0

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
   IF EEnergy(T)<=0 THEN STE(T)=100: EAN(T)=50: EAniDelay(T)=20: EAniSpd(T)=1
  CASE 55:
   EAN(T)=25: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=10
  CASE 56: EAN(T)=1: STE(T)=1

  'THROWED UPDOWN --------------------------------------------------------------------
  CASE 60:
   EAN(T)=21: STE(T)=61: EAniDelay(T)=0: EAniSpd(T)=15
   IF ESide(T)=4 THEN ESide(T)=7 ELSE ESide(T)=6
   INC EX(T),-ESPDX(T)
  CASE 61:
   IF EAniDelay(T)>10 THEN INC STE(T)
  CASE 62:
   EAN(T)=22: STE(T)=52: EAniDelay(T)=0: EAniSpd(T)=10

  'PUNCH -----------------------------------------------------------------------------
  CASE 70: EAN(T)=13: EAniDelay(T)=0: EAniSpd(T)=2: INC STE(T)
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
  IF EAN(T)>=15 THEN STE(T)=72
  CASE 72: IF EAN(T)>=15 THEN STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=4

  'STAB ------------------------------------------------------------------------------
  CASE 75: EAN(T)=73: EAniDelay(T)=0: EAniSpd(T)=1: INC STE(T)
  CASE 76:       
   'STAB THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
   IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=75 AND Special(PL)=0 THEN
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLSFX(PL)=24 'CHANGE THIS SOUND LATTER
    INC Energy(PL),-ES_POW(T)
    PHurted(PL)=2
    SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
    INC HCombo(PL),75
    WhoE(PL)=T 'SET WHO HURTED THE PLAYER
    STE(T)=77: EAniDelay(T)=0: EAniSpd(T)=3
   ENDIF
  IF EAN(T)>=77 THEN STE(T)=77: EAN(T)=77
  CASE 77: IF EAN(T)>=77 THEN STE(T)=1: EAN(T)=77: EAniDelay(T)=0: EAniSpd(T)=4

  'DASH ------------------------------------------------------------------------------
  CASE 80: 
   'TURN ENEMY TO DASH IN THE ENEMY POSITION
   IF EX(T)>X(PL) THEN ESIDE(T)=5 ELSE ESIDE(T)=4
   EAN(T)=25: EAniDelay(T)=0: EAniSpd(T)=20: INC STE(T)
  CASE 81: EAN(T)=25: IF EAniDelay(T)>7 THEN INC STE(T) 'WAIT CROUCHED
  CASE 82:
   EAN(T)=25: EAniDelay(T)=0: EAniSpd(T)=10: INC STE(T)
   ESPDX(T)=(ESide(T)=4)*8-(ESide(T)=5)*8
  CASE 83:
   EAN(T)=78
   INC EX(T),ESPDX(T) 'DASH!
   INC ESPDX(T),-SGN(ESPDX(T))*0.4
   'KICK THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
   IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND Special(PL)=0 THEN
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLSFX(PL)=24
    INC Energy(PL),-ES_POW(T)
    SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
    PHurted(PL)=2
    INC HCombo(PL),200
    WhoE(PL)=T 'SET WHO HURTED THE PLAYER
   ENDIF
   'WHEN SPEED IS OVER, STOP DASH
   IF (ESPDX(T)<=2 AND ESIDE(T)=4) OR (ESPDX(T)>=-2 AND ESIDE(T)=5) THEN STE(T)=84: EAniDelay(T)=0
  CASE 84:
   EAN(T)=25: EAniSpd(T)=10: INC STE(T)
   EY(T)=0: ESJMP(T)=0: ESPDX(T)=0: EBACKX(T)=0: EBACK(T)=0: ESPDX(T)=0
  CASE 85: IF EAniSpd(T)>=8 THEN STE(T)=1

  'AIR KNIFE ATTACK ------------------------------------------------------------------
  CASE 86: 
   'TURN ENEMY TO JUMP IN THE ENEMY POSITION
   IF EX(T)>X(PL) THEN ESIDE(T)=5 ELSE ESIDE(T)=4
   EAN(T)=25: EAniDelay(T)=0: EAniSpd(T)=20: INC STE(T)
  CASE 87: EAN(T)=25: IF EAniDelay(T)>15 THEN INC STE(T) 'WAIT CROUCHED
  CASE 88:
   EAN(T)=34: EAniDelay(T)=0: EAniSpd(T)=2: INC STE(T)
   ESPDX(T)=(ESide(T)=4)*7-(ESide(T)=5)*7:ESJMP(T)=-16
  CASE 89:
   INC EX(T),ESPDX(T) 'JUMP!
   INC ESPDX(T),-SGN(ESPDX(T))*0.06
   'KICK THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
   IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND Special(PL)=0 THEN
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLSFX(PL)=24
    INC Energy(PL),-ES_POW(T)
    SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
    PHurted(PL)=2
    INC HCombo(PL),200
    WhoE(PL)=T 'SET WHO HURTED THE PLAYER
   ENDIF
   'END MOVE AND TURN ENEMY BACK TO THE PLAYER
   IF EAN(T)>=40 THEN
    EAN(T)=40: STE(T)=90: EAniDelay(T)=0: EaniSpd(T)=40
   ENDIF
  CASE 90:
   EAN(T)=40 
   IF EAniDelay(T)>3 THEN
    ESPDX(T)=0: EAniDelay(T)=0: EaniSpd(T)=40
    EBACKX(T)=0: EBACK(T)=0: ESPDX(T)=0: INC STE(T)
   ENDIF 
  CASE 91: 
   IF EX(T)>X(PL) THEN ESIDE(T)=5 ELSE ESIDE(T)=4
   EAN(T)=25
   IF EAniDelay(T)>5 THEN
    EY(T)=0: ESJMP(T)=0
    STE(T)=1
   ENDIF

  'ENEMY IS DEAD ---------------------------------------------------------------------
  CASE 100: EAniSpd(T)=0: IF EAN(T)>60 THEN EAN(T)=50: INC STE(T) ' FLASH BODY AGAIN
  CASE 101: IF EAN(T)>60 THEN EEnergy(T)=-99: STE(T)=0: RealY(T)=999: Exit Sub 'REMOVE DEAD ENEMY

  'GRAPPLED BY A PLAYER --------------------------------------------------------------
  CASE 120 TO 170: GrapPlayer(T)

  'RETURN TO THE ORIGINAL STATE IF SOMETHING GOES WRONG ON GAPPLE
  CASE >=171:
   STE(T)=20: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0: ESPDY(T)=0

 END SELECT 'END ACTION SCRIPTS HOLLY WOOD / EL GADO -------------------------------------------
 
END SUB
