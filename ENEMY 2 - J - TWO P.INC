'J / TWO P ENEMY CONTROLLER

SUB Enemy_J_TWO_P(T,PL)
 LOCAL II,TT

 IF EMV(T)=1 OR (STE(T)>=70 AND STE(T)<=100) THEN INC EAniDelay(T)
 IF EAniDelay(T)>EAniSpd(T) THEN
  EAniDelay(T)=0
  INC EAN(T)
  IF STE(T)>20 AND STE(T)<52 THEN STE(T)=1
 ENDIF

 'WALKING
 IF STE(T)<50 AND EMV(T)>0 THEN 'CAN WALK OR MAKE ANY ATTACK? -----------------

  'DECREASE TO WALK
  INC STE(T),-1
  IF EX(T)<X(PL) THEN ESide(T)=4 ELSE ESide(T)=5

  IF STE(T)<1 THEN
   EBACK(T)=1: EBACKX(T)=1
   STE(T)=1: EAN(T)=0 'KEEP STOPPED UNTIL BACK TO WALK RANDOMLY
   IF RND<0.3 THEN
    'ALWAYS WALKING WITH ATTENTION
    STE(T)=20
    IF RND>0.6 AND DIST<80 THEN 'MAYBE GO BACK IF NEAR PLAYER IS PUNCHING
     IF Punch(PL)>0 AND EBACK(T)<>-1 THEN EBACK(T)=-1: STE(T)=20
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
   INC EX(T),((EX(T)<X(PL)-30+TT)*II*EBACKX(T))-((EX(T)>X(PL)+30-TT)*II*EBACKX(T))
  ENDIF

 ELSE 'STE(T)>=50 - DON'T WALK! ---------------------------------
  ESPD(T)=0
 ENDIF

 'ENEMY STATUS / ACTION SCRIPTS -----------------------------------------------------

 SELECT CASE STE(T)

  'WALKING WITH ATTENTION -----------------------------------------------------------
  CASE 1 TO 40: 
   EAniSpd(T)=3-(EBACK(T)=-1)*2
   ESPD(T)=((ES_SPD(T)+EAN(T)-1)/2)*EBACK(T)*((EBACK(T)=-1)*2+(EBACK(T)>=0))
   IF EAN(T)<0 OR EAN(T)>3 THEN EAN(T)=0
   EXIT SUB

  'GETTING UP ------------------------------------------------------------------------
  CASE 51: EXIT SUB 'NOTHING
  CASE 52:
   EAN(T)=24: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=30
   'FIX ENEMY SIDE AFTER THROWED
   IF ESide(T)=6 THEN ESide(T)=4
   IF ESide(T)=7 THEN ESide(T)=5
   EXIT SUB
  CASE 53:      
   ESPDX(T)=ESPDX(T)\2: IF EAniDelay(T)>20 OR EEnergy(T)<=0 THEN INC STE(T)
   EXIT SUB
  CASE 54:
   EAN(T)=24: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=3: ESPDX(T)=0
   'ENEMY DEAD?
   IF EEnergy(T)<=0 THEN STE(T)=100: EAN(T)=50: EAniDelay(T)=0: EAniSpd(T)=1       
   EXIT SUB
  CASE 55:
   EAN(T)=24: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=10
   EXIT SUB
  CASE 56: EAN(T)=0: STE(T)=1: EXIT SUB

  'THROWED UPDOWN --------------------------------------------------------------------
  CASE 60:
   EAN(T)=21: STE(T)=61: EAniDelay(T)=0: EAniSpd(T)=15
   IF ESide(T)=4 THEN ESide(T)=7 ELSE ESide(T)=6
   INC EX(T),-ESPDX(T)
   EXIT SUB
  CASE 61:
   IF EAniDelay(T)>10 THEN INC STE(T)
   EXIT SUB
  CASE 62:
   EAN(T)=22: STE(T)=52: EAniDelay(T)=0: EAniSpd(T)=10
   EXIT SUB

  'GRAPPLED BY A PLAYER --------------------------------------------------------------
  CASE 120 TO 170: GrapPlayer(T): EXIT SUB

  'LEANING AGAINST THE WALL ----------------------------------------------------------
  CASE 64:
   EAN(T)=35: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=65: EMV(T)=0
   EXIT SUB
  CASE 65:
   EAN(T)=35: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=64: EMV(T)=0
   IF EX(T)<245+RXX THEN EAN(T)=0: STE(T)=1: EMV(T)=1
   EXIT SUB

  'SEATED ----------------------------------------------------------------------------
  CASE 66:
   EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=67: EMV(T)=0
   IF EX(T)<245+RXX THEN EAN(T)=35: STE(T)=64
   EXIT SUB
  CASE 67:
   EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=66: EMV(T)=0
   IF EX(T)<245+RXX THEN EAN(T)=35: STE(T)=64
   EXIT SUB

  'PUNCH AND FAST BACKWARD -----------------------------------------------------------
  CASE 70: EAN(T)=13: EAniDelay(T)=0: EAniSpd(T)=2: INC STE(T): EXIT SUB
  CASE 71:       
   'PUNCH THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
   IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=14 AND Special(PL)=0 THEN
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLAY_SAMPLE 27,PL
    INC Energy(PL),-ES_POW(T)
    PHurted(PL)=2
    SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
    INC HCombo(PL),50
    WhoE(PL)=T 'SET WHO HURTED THE PLAYER
    STE(T)=72: EAniDelay(T)=0: EAniSpd(T)=3
   ENDIF
   IF EAN(T)>=15 THEN STE(T)=72
   EXIT SUB
  CASE 72:
   IF EAN(T)>=15 THEN EBACK(T)=-1: STE(T)=10: EAniDelay(T)=0: EAniSpd(T)=2
   EXIT SUB

  'J / TWO P DON'T KICK OR JUMP ----------------------------------
  CASE 75,80: STE(T)=1: EXIT SUB

  'ENEMY IS DEAD ---------------------------------------------------------------------
  CASE 100:
   EAniSpd(T)=0: IF EAN(T)>60 THEN EAN(T)=50: INC STE(T) ' FLASH BODY AGAIN
   EXIT SUB
  CASE 101: IF EAN(T)>60 THEN EEnergy(T)=-99: STE(T)=0: RealY(T)=999: Exit Sub 'REMOVE DEAD ENEMY

  'RETURN TO THE ORIGINAL STATE IF SOMETHING GOES WRONG ON GAPPLE
  CASE >=171:
   STE(T)=20: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0
  'FOR ALL OTHER CASES, GET UP!
  CASE ELSE: EAN(T)=1: STE(T)=1

 END SELECT 'END ACTION SCRIPTS J / TWO P --------------------------------------------
 
END SUB


' DRAW J / TWO P

SUB Draw_J_TWO_P(num,who)

 SELECT CASE num
  'ENERGY AVATAR
  CASE 99 : xa=0:ya=504:sx=59:sy=16:tx=-14
  'STOPPED
  CASE  0 : xa=163:ya=508:sx=64:sy=91
  'WALKING
  CASE  1 : xa=163:ya=508:sx=64:sy=49:tx=0:ty=0:xb=227:yb=504:sbx=38:sby=42:tbx=6:tby=0
  CASE  2 : xa=163:ya=508:sx=64:sy=49:tx=0:ty=0:xb=227:yb=546:sbx=30:sby=43:tbx=6:tby=0
  CASE  3 : xa=163:ya=508:sx=64:sy=49:tx=0:ty=0:xb=227:yb=504:sbx=38:sby=42:tbx=6:tby=0
  'PUNCHING
  CASE 13 : xa=265:ya=507:sx=61:sy=91:tx=  6
  CASE 14 : xa=326:ya=512:sx=98:sy=85:tx=-23
  CASE 15 : xa=265:ya=507:sx=61:sy=91:tx=  6
  'HURT
  CASE 21 : xa=573:ya=515:sx=53:sy=79:tx=3 'IN THE STOMACH
  CASE 22 : xa=630:ya=504:sx=49:sy=93:tx=9 'IN THE FACE
  'FALLING
  CASE 23 : xa=680:ya=541:sx= 97:sy=53:tx=5:ty=-20 'FALLING DOWN
  CASE 24,50,52,54,56,58,60:
            xa=680:ya=504:sx=116:sy=26:tx=5:ty=0   'LYING ON THE FLOOR / DEAD
  'GETTING UP
  CASE 25 : xa= 52:ya=544:sx=60:sy=55:tx=0:ty=0
  'SEATED
  CASE 34 : xa=  0:ya=536:sx=52:sy=63:tx=0:ty=0 'ON THE BENCH / FLOOR / SUBWAY
  'LEANING IN THE WALL
  CASE 35 : xa=116:ya=504:sx=47:sy=95:tx=0:ty=0
  'BURNING
  CASE 80 : xa=  0:ya=993:sx=121:sy=72
  CASE 81 : xa=121:ya=993:sx=123:sy=72
  CASE 82 : xa=244:ya=993:sx=121:sy=72

 END SELECT 'END J / TWO P

 if num<80 or num>82 then INC xa,(who-7)*796: INC xb,(who-7)*796

END SUB


