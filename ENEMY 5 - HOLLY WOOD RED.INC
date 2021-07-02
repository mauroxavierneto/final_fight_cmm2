SUB Enemy_HOLLY_WOOD_RED(T,PL)
 LOCAL II,TT

 IF EMV(T)>0 OR (STE(T)>=70 AND STE(T)<=99) THEN INC EAniDelay(T)
 IF EAniDelay(T)>EAniSpd(T) THEN
  EAniDelay(T)=0
  INC EAN(T)
  IF STE(T)>40 AND STE(T)<52 THEN STE(T)=1
 ENDIF

 'WALKING
 IF STE(T)<50 AND EMV(T)>0 THEN 'CAN WALK OR MAKE ANY ATTACK? -----------------

  'DECREASE TO WALK
  INC STE(T),-1
  IF STE(T)<1 THEN STE(T)=40

  'WALK THEN GO BACK WHEN NEAR THE PLAYER
  IF EX(T)<X(PL)+100 AND ESide(T)=5 AND EMV(T)=1 THEN STE(T)=75: EMV(T)=2
  IF EX(T)>X(PL)-100 AND ESide(T)=4 AND EMV(T)=1 THEN STE(T)=75: EMV(T)=2

  INC EX(T),(ESide(T)=4)*6-(ESide(T)=5)*6
  IF EX(T)<-30 OR EX(T)>360 THEN STE(T)=0

 ENDIF

 'ENEMY STATUS / ACTION SCRIPTS -----------------------------------------------------

 SELECT CASE STE(T)

  'WALKING --------------------------------------------------------------------------
  CASE 1 TO 40: 
   EAniSpd(T)=2
   IF EAN(T)>5 THEN EAN(T)=0

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
   EAniDelay(T)=0: EAniSpd(T)=3: ESPDX(T)=0: STE(T)=100: EAN(T)=50 ' DIE

  'THROWED UPDOWN --------------------------------------------------------------------
  CASE 60:
   EAN(T)=21: STE(T)=61: EAniDelay(T)=0: EAniSpd(T)=15
   IF ESide(T)=4 THEN ESide(T)=7 ELSE ESide(T)=6
   INC EX(T),-ESPDX(T)
  CASE 61:
   IF EAniDelay(T)>10 THEN INC STE(T)
  CASE 62:
   EAN(T)=22: STE(T)=52: EAniDelay(T)=0: EAniSpd(T)=10

  'THROW MOLOTOV TOO INSTEAD PUNCHING ------------------------------------------------
  CASE 70: STE(T)=75

  'THROW MOLOTOV ---------------------------------------------------------------------
  CASE 75: EAN(T)=70: EAniDelay(T)=0: EAniSpd(T)=4: INC STE(T)
  CASE 76:
   IF EAN(T)>=72 THEN
    STE(T)=77: EAN(T)=72
    SpawnObject(EX(T),RealY(T)-40,209+PL,NUM)    
    ESPDX(NUM)=(ESIDE(T)=4)*3-(ESIDE(T)=5)*3
    EAniDelay(T)=0: EAniSpd(T)=200
   ENDIF
  CASE 77:
   EAN(T)=72
   IF EAniSpd(T)>4 THEN
    STE(T)=40: EAniDelay(T)=0: EAniSpd(T)=4
    ESIDE(T)=(ESIDE(T)=4)*5+(ESIDE(T)=5)*4
   ENDIF

  'DON'T DASH ------------------------------------------------------------------------
  CASE 80: STE(T)=1
  'DON'T MAKE A AIR KNIFE ATTACK -----------------------------------------------------
  CASE 86: STE(T)=1

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

 END SELECT 'END ACTION SCRIPTS HOLLY WOOD / EL GADO -------------------------------------------
 
END SUB
