' AXL / SLASH ENEMY CONTROLLER

SUB Enemy_AXL_SLASH(T,PL)
 LOCAL II,TT

 IF EMV(T)=1 OR (STE(T)>=70 AND STE(T)<=100) THEN INC EAniDelay(T)
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
   IF EAN(T)>6 THEN EAN(T)=1

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
   STE(T)=65: EMV(T)=0
   IF EX(T)<245+RXX THEN STE(T)=35: EMV(T)=1
  CASE 65:
   EAN(T)=35: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=64: EMV(T)=0
   IF EX(T)<245+RXX THEN STE(T)=35: EMV(T)=1

  'SEATED ----------------------------------------------------------------------------
  CASE 66:
   EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=67: EMV(T)=0
   IF EX(T)<245+RXX THEN STE(T)=35: EMV(T)=1
  CASE 67:
   EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=66: EMV(T)=0
   IF EX(T)<245+RXX THEN STE(T)=35: EMV(T)=1

  'BLOCKING --------------------------------------------------------------------------
  CASE 68:
   EAN(T)=19: EAniDelay(T)=0: EAniSPD(T)=50
   STE(T)=69
   IF EHURT(T)<=0 THEN STE(T)=1
  CASE 69:
   EAN(T)=19: EAniDelay(T)=0: EAniSPD(T)=50
   STE(T)=68
   IF EHURT(T)<=0 THEN STE(T)=1

  'PUNCH -----------------------------------------------------------------------------
  CASE 70: EAN(T)=12: EAniDelay(T)=0: EAniSpd(T)=2: INC STE(T)
  CASE 71:       
   'PUNCH THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
   IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=14 AND Special(PL)=0 THEN
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLAY_SAMPLE 27,PL
    INC Energy(PL),-ES_POW(T)
    PHurted(PL)=2
    SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
    INC HCombo(PL),350
    WhoE(PL)=T 'SET WHO HURTED THE PLAYER
    STE(T)=72: EAniDelay(T)=0: EAniSpd(T)=3
   ENDIF
  IF EAN(T)>15 THEN STE(T)=72
  CASE 72: IF EAN(T)>15 THEN STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=3

  'KICK ------------------------------------------------------------------------------
  CASE 75: EAN(T)=16: EAniDelay(T)=0: EAniSpd(T)=2: INC STE(T)
  CASE 76:       
   'KICK THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
   IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=18 AND Special(PL)=0 THEN
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLAY_SAMPLE 27,PL
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
  CASE 101: IF EAN(T)>60 THEN EEnergy(T)=-99: STE(T)=0: RealY(T)=999: Exit Sub 'REMOVE DEAD ENEMY

  'GRAPPLED BY A PLAYER --------------------------------------------------------------
  CASE 120 TO 170: GrapPlayer(T)

  'RETURN TO THE ORIGINAL STATE IF SOMETHING GOES WRONG ON GAPPLE
  CASE >=171:
   STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0

  'FOR ALL OTHER CASES, GET UP!
  CASE ELSE: EAN(T)=1: STE(T)=1

 END SELECT 'END ACTION SCRIPTS AXL / SLASH ------------------------------------------
 
 END SUB


' DRAW AXL / SLASH

SUB Draw_AXL_SLASH(num,who)

 SELECT CASE num
  'ENERGY AVATAR
  CASE 99 : xa=0:ya=-(who=10):sx=59:sy=16:tx=-14:ty=0
  'STOPPED
  CASE  0 : xa=114:ya=7:sx=67:sy=99:tx=0:ty=0 
  'WALKING 
  CASE  1 : xa=114:ya=7:sx=67:sy=42:xb=181:yb=  0:sbx=52:sby=56:tbx= 22:if who=10 then INC yb,5
  CASE  2 : xa=114:ya=7:sx=67:sy=42:xb=181:yb= 56:sbx=36:sby=56:tbx= -2:if who=10 then INC yb,5
  CASE  3 : xa=114:ya=7:sx=67:sy=42:xb=233:yb=  0:sbx=64:sby=56:tbx= -6:if who=10 then INC yb,5
  CASE  4 : xa=114:ya=7:sx=67:sy=42:xb=217:yb= 56:sbx=51:sby=56:tbx= 14:if who=10 then INC yb,5
  CASE  5 : xa=114:ya=7:sx=67:sy=42:xb=297:yb=  0:sbx=33:sby=56:tbx=  0:if who=10 then INC yb,5
  CASE  6 : xa=114:ya=7:sx=67:sy=42:xb=268:yb= 56:sbx=64:sby=56:tbx=  0:if who=10 then INC yb,5
  'PUNCH
  CASE 12 : xa=462:ya=  0:sx=64:sy=106:tx=-10: if who=10 then xa=462:ya=107-107
  CASE 13 : xa=398:ya=  0:sx=64:sy=116:tx=-10: if who=10 then xa=334:ya=91-107
  CASE 14 : xa=526:ya= 16:sx=99:sy= 90:tx=-44
  CASE 15 : xa=625:ya= 20:sx=75:sy= 86:tx=-20
  'KICKING
  CASE 16 : xa=700:ya= 12:sx=53:sy=95:tx=  0
  CASE 17 : xa=753:ya= 16:sx=99:sy=90:tx=-30
  CASE 18 : xa=700:ya= 12:sx=53:sy=95:tx=  0
  'BLOCKING
  CASE 19 : xa=332:ya=  0:sx=54:sy=91:tx=0:ty=0: if who=10 then xa=398: ya=116-107: sy=92
  'HURT
  CASE 21 : xa=852:ya= 21:sx=59:sy= 84:tx=0 'IN THE STOMACH
  CASE 22 : xa=911:ya=  6:sx=64:sy=100:tx=0:yp=20 'IN THE FACE
  'FALLING
  CASE 23 : xa=975:ya= 41:sx=112:sy=59:tx=0:ty=0    'FALLING DOWN
  CASE 24,50,52,54,56,58,60:
            xa=975:ya=  0:sx=128:sy=26:tx=0:ty=0    'LYING ON THE FLOOR / DEAD
  'GETTING UP
  CASE 25 : xa=1087:ya=52:sx= 71:sy= 54:tx=0:ty=0
  'SEATED
  CASE 34 : xa=  0:ya= 42:sx= 62:sy= 64:tx=0:ty=0 'ON THE BENCH / FLOOR / SUBWAY
  'LEANING IN THE WALL
  CASE 35 : xa= 62:ya=  4:sx= 52:sy=102:tx=0:ty=0
  'BURNING
  CASE 80 : xa=  0:ya=993:sx=121:sy=72
  CASE 81 : xa=121:ya=993:sx=123:sy=72
  CASE 82 : xa=244:ya=993:sx=121:sy=72

 END SELECT 'END AXL / SLASH

 if num<80 or num>82 then INC ya,(who-9)*107: INC yb,(who-9)*107

END SUB


