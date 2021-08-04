' BRED / JAKE / DUG ENEMY CONTROLLER

SUB Enemy_BRED_JAKE_DUG(T,PL)
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
  IF EX(T)<X(PL) THEN ESide(T)=4 ELSE ESide(T)=5

  IF STE(T)<1 THEN
   EBACK(T)=1: EBACKX(T)=1: STE(T)=1: EAN(T)=9: ESPD(T)=0 'KEEP STOPPED UNTIL BACK TO WALK RANDOMLY
   IF RND<0.07 THEN
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
   EXIT SUB

  'WALKING ---------------------------------------------------------------------------
  CASE 21 TO 40:
   EAniSpd(T)=5
   ESPD(T)=ES_SPD(T)*EBACK(T)
   IF EAN(T)>5 THEN EAN(T)=0
   IF STE(T)=21 AND DIST>120 THEN STE(T)=40
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
   EAN(T)=25: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=3: ESPDX(T)=0
   'ENEMY DEAD?
   IF EEnergy(T)<=0 THEN STE(T)=100: EAN(T)=50: EAniDelay(T)=0: EAniSpd(T)=1       
   EXIT SUB
  CASE 55:
   IF EAN(T)>33 THEN EAN(T)=0: STE(T)=1    
   EXIT SUB
  CASE 56: STE(T)=55: EXIT SUB

  'LEAVING THROUGH THE DOOR ----------------------------------------------------------
  CASE 57: ESide(T)=4: EAniDelay(T)=0: EAniSPD(T)=5: EAN(T)=35: INC STE(T): EXIT SUB
  CASE 58
   ESide(T)=4: INC RealY(T),0.35: IF EAN(T)>39 THEN EAN(T)=0: STE(T)=1
   EXIT SUB

  'THROWED UPDOWN --------------------------------------------------------------------
  CASE 60:
   EAN(T)=21: STE(T)=61: EAniDelay(T)=0: EAniSpd(T)=15
   IF ESide(T)=4 THEN ESide(T)=7 ELSE ESide(T)=6
   INC EX(T),-ESPDX(T)
   EXIT SUB
  CASE 61:
   EAN(T)=21:IF EAniDelay(T)>10 THEN INC STE(T)
   EXIT SUB
  CASE 62:
   EAN(T)=22: STE(T)=52: EAniDelay(T)=0: EAniSpd(T)=10
   EXIT SUB

  'GRAPPLED BY A PLAYER --------------------------------------------------------------
  CASE 120 TO 170: GrapPlayer(T): EXIT SUB

  'LEANING AGAINST THE WALL ----------------------------------------------------------
  CASE 64:
   EAN(T)=35: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=65
   EXIT SUB
  CASE 65:
   EAN(T)=35: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=64
   IF EX(T)<245+RXX THEN EAN(T)=0: STE(T)=1: EMV(T)=1
   EXIT SUB

  'SEATED ----------------------------------------------------------------------------
  CASE 66:
   EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=67: EMV(T)=0: ESIDE(T)=4
   IF EX(T)<245+RXX THEN STE(T)=64
   EXIT SUB
  CASE 67:
   EAN(T)=34: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=66: EMV(T)=0: ESIDE(T)=4
   IF EX(T)<245+RXX THEN STE(T)=64
   EXIT SUB

  'SEATED CROUCHED -------------------------------------------------------------------
  CASE 68:
   EAN(T)=6: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=69: EMV(T)=0
   IF EX(T)<245+RXX THEN STE(T)=64
   IF EX(T)<325+RXX AND COLLIDE(0)=&H00FFFF THEN STE(T)=75: EMV(T)=1 'KICK DRUMCAN
   EXIT SUB
  CASE 69:
   EAN(T)=6: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=68: EMV(T)=0
   IF EX(T)<245+RXX THEN STE(T)=64
   IF EX(T)<325+RXX AND COLLIDE(0)=&H00FFFF THEN STE(T)=75: EMV(T)=1 'KICK DRUMCAN
   EXIT SUB

  'PUNCH -----------------------------------------------------------------------------
  CASE 70: EAN(T)=13: EAniDelay(T)=0: EAniSpd(T)=4: INC STE(T): EXIT SUB
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
    STE(T)=72: EAniDelay(T)=0: EAniSpd(T)=4
   ENDIF
   IF EAN(T)>15 THEN STE(T)=72
   EXIT SUB
  CASE 72:
   IF EAN(T)>15 THEN STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=4
   EXIT SUB

  'KICK ------------------------------------------------------------------------------
  CASE 75: EAN(T)=16: EAniDelay(T)=0: EAniSpd(T)=1: INC STE(T): EXIT SUB
  CASE 76:       
   'KICK THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
   IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=18 AND Special(PL)=0 THEN
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLAY_SAMPLE 24,PL
    INC Energy(PL),-ES_POW(T)
    PHurted(PL)=2
    SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
    INC HCombo(PL),75
    WhoE(PL)=T 'SET WHO HURTED THE PLAYER
    STE(T)=77: EAniDelay(T)=0: EAniSpd(T)=3
   ENDIF
   IF EAN(T)>20 THEN STE(T)=77
   EXIT SUB
  CASE 77:
   IF EAN(T)>20 THEN STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=4
   EXIT SUB

  'JUMP KICKING ----------------------------------------------------------------------
  CASE 80: EAN(T)=6: EAniDelay(T)=0: EAniSpd(T)=5: INC STE(T): EXIT SUB
  CASE 81:
   IF EAN(T)=7 THEN
    EAniDelay(T)=0: EAniSpd(T)=80: INC STE(T)
    ESJMP(T)=-12: ESPDX(T)=(ESide(T)=4)*2-(ESide(T)=5)*2
   ENDIF
   EXIT SUB
  CASE 82:       
   EAN(T)=7
   INC EX(T),ESPDX(T)
   'KICK THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
   IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND Special(PL)=0 THEN
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLAY_SAMPLE 24,PL
    INC Energy(PL),-ES_POW(T)
    SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
    PHurted(PL)=2
    INC HCombo(PL),200
    WhoE(PL)=T 'SET WHO HURTED THE PLAYER
    STE(T)=83
   ENDIF
   IF EY(T)>=0 THEN STE(T)=83
   EXIT SUB
  CASE 83:
   IF EY(T)>=0 THEN
    EAN(T)=8: EAniDelay(T)=0: EAniSpd(T)=12: INC STE(T)
    EY(T)=0: ESJMP(T)=0: ESPDX(T)=0: EBACKX(T)=0: EBACK(T)=0: ESPDX(T)=0
   ENDIF
   EXIT SUB
  CASE 84:
   IF EAniSpd(T)>=8 THEN STE(T)=20
   EXIT SUB

  'ENEMY IS DEAD ---------------------------------------------------------------------
  CASE 100: EAniSpd(T)=0: IF EAN(T)>60 THEN EAN(T)=50: INC STE(T) ' FLASH BODY AGAIN
  CASE 101: IF EAN(T)>60 THEN EEnergy(T)=-99: STE(T)=0: RealY(T)=999: Exit Sub 'REMOVE DEAD ENEMY

  'RETURN TO THE ORIGINAL STATE IF SOMETHING GOES WRONG ON GAPPLE
  CASE >=171:
   STE(T)=20: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0

  'FOR ALL OTHER CASES, GET UP!
  CASE ELSE: EAN(T)=1: STE(T)=1

 END SELECT 'END ACTION SCRIPTS BRED / JAKE -----------------------------------------

END SUB


SUB Draw_BRED_JAKE_DUG(num,who)

 SELECT CASE num
  'ENERGY AVATAR
  CASE 99 : xa=0:ya=225:sx=51:sy=16:tx=-7:ty=0
  'WALKING
  CASE  0 : xa=143:ya=225:sx=41:sy=44:tx=5:ty=0:xb=143:yb=269:sbx=31:sby=46:tbx=15:tby=(who>4)
  CASE  1 : xa=143:ya=225:sx=41:sy=44:tx=5:ty=0:xb=184:yb=225:sbx=60:sby=46:tbx=16:tby=(who>4)
  CASE  2 : xa=143:ya=225:sx=41:sy=44:tx=5:ty=0:xb=184:yb=273:sbx=47:sby=45:tbx=31:tby=(who>4)-1
  CASE  3 : xa=143:ya=225:sx=41:sy=44:tx=5:ty=0:xb=244:yb=225:sbx=29:sby=47:tbx=13:tby=(who>4)
  CASE  4 : xa=143:ya=225:sx=41:sy=44:tx=5:ty=0:xb=231:yb=272:sbx=56:sby=46:tbx=10:tby=(who>4)
  CASE  5 : xa=143:ya=225:sx=41:sy=44:tx=5:ty=0:xb=273:yb=225:sbx=46:sby=47:tbx=28:tby=(who>4)
  'JUMP AND KICKING
  CASE  6 : xa= 0:ya=247:sx=56:sy=68:tx=  5
  CASE  7 : xa=56:ya=244:sx=87:sy=70:tx=-15
  CASE  8 : xa= 0:ya=247:sx=56:sy=68:tx=  5
  'WALKING WITH ATTENTION
  CASE  9 : xa=335:ya=242:sx=45:sy=30:tx=-5:ty=0:xb=319:yb=272:sbx=57:sby=46:tbx=15
  CASE 10 : xa=335:ya=242:sx=45:sy=30:tx=-5:ty=0:xb=380:yb=225:sbx=40:sby=46:tbx=12
  CASE 11 : xa=335:ya=242:sx=45:sy=30:tx=-5:ty=0:xb=380:yb=271:sbx=29:sby=46:tbx=11
  CASE 12 : xa=335:ya=242:sx=45:sy=30:tx=-5:ty=0:xb=380:yb=225:sbx=40:sby=46:tbx=12
  'PUNCHING
  CASE 13 : xa=420:ya=229:sx=62:sy=89:tx=  6
  CASE 14 : xa=482:ya=229:sx=95:sy=89:tx=-23
  CASE 15 : xa=420:ya=229:sx=62:sy=89:tx=  6
  'KICKING
  CASE 16 : xa=577:ya=226:sx=56:sy=92:tx= 0
  CASE 17 : xa=633:ya=226:sx=60:sy=92:tx= 0
  CASE 18 : xa=693:ya=226:sx=81:sy=92:tx=-9
  CASE 19 : xa=633:ya=226:sx=60:sy=92:tx= 0
  CASE 20 : xa=577:ya=226:sx=56:sy=92:tx= 0
  'HURT
  CASE 21 : xa=774:ya=244:sx= 52:sy=74:tx=3 'IN THE STOMACH
  CASE 22 : xa=826:ya=228:sx= 51:sy=90:tx=9 'IN THE FACE
  'FALLING
  CASE 23 : xa=877:ya=261:sx= 96:sy=57:tx=5:ty=-20 'FALLING DOWN
  CASE 24,50,52,54,56,58,60:
            xa=877:ya=225:sx=121:sy=27:tx=5        'LYING ON THE FLOOR / DEAD
  'GETTING UP / SHAKING HEAD
  CASE 25,27,29,31,33:
               xa= 973:ya=267:sx= 67:sy= 51:tx=  5
  CASE 26,30 : xb= 973:yb=267:sbx=67:sby=51:tbx= 5
               xa= 998:ya=226:sx= 15:sy= 23:tx=-48:          ty=20-(who=4)*2-(who=6)*4
  CASE 28,32 : xb= 973:yb=267:sbx=67:sby=51:tbx= 5
               xa=1014:ya=226:sx= 16:sy= 23:tx=-48-(who=6)*2:ty=20-(who=4)*2-(who=6)*4
  'SEATED
  CASE 34 : xa=1110:ya=241:sx=64:sy=78:tx=5 'ON THE BENCH / SUBWAY

  'LEAVING THROUGH THE DOOR / LEANING IN THE WALL
  CASE 35 : xa=1040:ya=228:sx=42:sy=44:tx=5:ty= 0:xb=1069:yb=273:sbx=31:sby=45:tbx= 8
  CASE 36 : xa=1040:ya=228:sx=42:sy=44:tx=5:ty= 1:xb=1040:yb=273:sbx=29:sby=45:tbx=12
  CASE 37 : xa=1040:ya=228:sx=42:sy=44:tx=5:ty= 0:xb=1069:yb=273:sbx=31:sby=45:tbx= 8
  CASE 38 : xa=1040:ya=228:sx=42:sy=44:tx=5:ty=-1:xb=1082:yb=227:sbx=28:sby=45:tbx= 3
  CASE 39 : xa=1040:ya=228:sx=42:sy=44:tx=5:ty= 0:xb=1069:yb=273:sbx=31:sby=45:tbx= 8
  'BURNING
  CASE 80 : xa=  0:ya=993:sx=121:sy=72
  CASE 81 : xa=121:ya=993:sx=123:sy=72
  CASE 82 : xa=244:ya=993:sx=121:sy=72

 END SELECT 'END BRED / JAKE / DUG

 if num<80 or num>82 then INC ya,(Who-4)*93: INC yb,(Who-4)*93

END SUB


