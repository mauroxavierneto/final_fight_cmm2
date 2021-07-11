'DAMND ENEMY CONTROLLER

SUB Enemy_DAMND(T,PL)
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
  IF EY(T)=0 THEN EMV(T)=1

  IF STE(T)<1 THEN
   EBACK(T)=1: EBACKX(T)=1
   STE(T)=1 'KEEP STOPPED UNTIL BACK TO WALK RANDOMLY
   IF RND<0.3 THEN
    'ALWAYS WALKING WITH ATTENTION
    STE(T)=40
    IF RND>0.6 AND DIST<80 THEN 'MAYBE JUMP BACK IF NEAR PLAYER IS PUNCHING
     IF Punch(PL)>0 AND EBACK(T)<>-1 THEN EBACK(T)=-1: STE(T)=75
    ENDIF
   ENDIF
   IF DIST>80 AND RND>0.7 THEN STE(T)=73: EBACK(T)=1 'LAUGHING
  ELSE
   'GO BACKWARD IF TOO NEAR
   IF DIST<35 AND STE(T)<50 THEN EBACKX(T)=-1
   'GO TO DIRECTION OF THE NEAR PLAYER
   II=ESPD(T): TT=RealY(T)
   IF RealY(T)<=SMYA THEN INC RealY(T), ABS(ESPD(T))
   IF RealY(T)>=SMYB THEN INC RealY(T),-ABS(ESPD(T))
   IF RealY(T)>RealY(PL)+2 THEN INC RealY(T),-ESPD(T)
   IF RealY(T)<RealY(PL)-2 THEN INC RealY(T), ESPD(T)
   TT=(EBACKX(T)=-1)*60
   INC EX(T),((EX(T)<X(PL)-70+TT)*II*EBACKX(T))-((EX(T)>X(PL)+70-TT)*II*EBACKX(T))
   IF EX(T)<X(PL) THEN ESide(T)=4 ELSE ESide(T)=5
  ENDIF

 ELSE 'STE(T)>=50 - DON'T WALK! ---------------------------------
  ESPD(T)=0
 ENDIF

 'ENEMY STATUS / ACTION SCRIPTS -----------------------------------------------------

 SELECT CASE STE(T)

  'WALKING WITH ATTENTION -----------------------------------------------------------
  CASE 1 TO 40: 
   EAniSpd(T)=3
   ESPD(T)=((ES_SPD(T)+(5-EAN(T)))/2)*EBACK(T)
   IF EAN(T)<0 OR EAN(T)>5 THEN EAN(T)=0

  'GETTING UP ------------------------------------------------------------------------
  CASE 51: 'NOTHING
  CASE 52:
   EAN(T)=24: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=40
   'FIX ENEMY SIDE AFTER THROWED
   IF ESide(T)=6 THEN ESide(T)=4
   IF ESide(T)=7 THEN ESide(T)=5
  CASE 53:      
   ESPDX(T)=ESPDX(T)\2: IF EAniDelay(T)>20 OR EEnergy(T)<=0 THEN INC STE(T)
  CASE 54:
   EAN(T)=27: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=2: ESPDX(T)=0
   'ENEMY DEAD?
   IF EEnergy(T)<=0 THEN STE(T)=100: EAN(T)=50: EAniDelay(T)=0: EAniSpd(T)=1       
  CASE 55: IF EAniDelay(T)>=2 THEN EAniDelay(T)=0: EAN(T)=28: INC STE(T)
  CASE 56: IF EAN(T)>31 THEN EAniDelay(T)=0: EAN(T)=28: INC STE(T)
  CASE 57: IF EAN(T)>31 THEN INC STE(T): EAN(T)=26: EAniDelay(T)=0:EAniSpd(T)=10
  CASE 58: EAN(T)=26: IF EAniDelay(T)>=3 THEN EAniDelay(T)=0: INC STE(T)
  CASE 59: EAN(T)=21: IF EAniDelay(T)>=3 THEN EAniDelay(T)=0: STE(T)=1

  'THROWED UPDOWN --------------------------------------------------------------------
  CASE 60:
   EAN(T)=21: STE(T)=61: EAniDelay(T)=0: EAniSpd(T)=15
   IF ESide(T)=4 THEN ESide(T)=7 ELSE ESide(T)=6
   INC EX(T),-ESPDX(T)
  CASE 61:
   EAN(T)=21:IF EAniDelay(T)>10 THEN INC STE(T)
  CASE 62:
   EAN(T)=22: STE(T)=52: EAniDelay(T)=0: EAniSpd(T)=10

  'PUNCH -----------------------------------------------------------------------------
  CASE 70: EAN(T)=13: EAniDelay(T)=0: EAniSpd(T)=1: INC STE(T)
  CASE 71:       
   EAniSpd(T)=1
   'PUNCH THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
   IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=16 AND Special(PL)=0 THEN
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLAY_SAMPLE 27,PL,18000
    INC Energy(PL),-ES_POW(T)
    PHurted(PL)=2
    SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
    INC HCombo(PL),75
    WhoE(PL)=T 'SET WHO HURTED THE PLAYER
    STE(T)=72: EAniDelay(T)=0: EAniSpd(T)=4
   ENDIF
  IF EAN(T)>=19 THEN STE(T)=72
  CASE 72: IF EAN(T)>=19 THEN STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=4

  'LAUGHING --------------------------------------------------------------------------
  CASE 73: EAN(T)=10: ESHAD(T)=1: EAniDelay(T)=0: EAniSpd(T)=200: INC STE(T)
  CASE 74:
    ESHAD(T)=1
    SELECT CASE EAniDelay(T)
     CASE  6: EAN(T)=11: PLAY_SAMPLE 30,3
     CASE 12, 24, 36, 48: EAN(T)=10
     CASE 18, 30, 42, 54: EAN(T)=11
     CASE 60: STE(T)=1
    END SELECT

  'JUMP BACKWARD ---------------------------------------------------------------------
  CASE 75:
   EAN(T)=25: EAniDelay(T)=0: EAniSpd(T)=200: STE(T)=82
   IF EX(T)<X(PL) THEN ESIDE(T)=4 ELSE ESIDE(T)=5 'TURN TO THE PLAYER SIDE
   ESJMP(T)=-11: ESPDX(T)=(ESIDE(T)=5)*3-(ESIDE(T)=4)*3
  CASE 82:
   INC ESJMP(T),-0.8
   SELECT CASE EAniDelay(T)
    CASE  5: EAN(T)=34 
    CASE 10: EAN(T)=35: ESIDE(T)=(ESIDE(T)=4)*6+(ESIDE(T)=5)*7 'TURN 180` 
    CASE 15: EAN(T)=34
    CASE 20: EAN(T)=35: ESIDE(T)=(ESIDE(T)=6)*4+(ESIDE(T)=7)*5 'TURN BACK 
    CASE 25: EAN(T)=34
    CASE 30: EAN(T)=25: ESPDX(T)=0
    CASE 35: EAN(T)=25: ESJMP(T)=0: STE(T)=1: EAniSpd(T)=4: EAniDelay(T)=0
   END SELECT

  'JUMP TO THE WALL ------------------------------------------------------------------
  CASE 76: 'START
   EAN(T)=25: EAniDelay(T)=0: EAniSpd(T)=200: STE(T)=83
   ESIDE(T)=5: INC EMV(T)=2
   ESJMP(T)=-11: ESPDX(T)=ABS((1120-SCRX)-EX(T))/25
  CASE 83: 'JUMP

   'GO TO THE SUBWAY ENTRY WALL
   INC ESJMP(T),-0.85: EMV(T)=2   
   IF EX(T)>1120-SCRX THEN EX(T)=1120-SCRX
   IF EX(T)>1110-SCRX THEN IF EY(T)>-25 THEN EY(T)=-25
   IF RealY(T)>210 THEN INC RealY(T),-4
   IF RealY(T)<204 THEN INC RealY(T), 4

   SELECT CASE EAniDelay(T)
    CASE  5: EAN(T)=34 
    CASE 10: EAN(T)=35: ESIDE(T)=(ESIDE(T)=4)*6+(ESIDE(T)=5)*7 'TURN 180` 
    CASE 15: EAN(T)=34
    CASE 20: EAN(T)=35: ESIDE(T)=(ESIDE(T)=6)*4+(ESIDE(T)=7)*5 'TURN BACK 
    CASE 25: EAN(T)=34
    CASE 30: EAN(T)=25: ESPDX(T)=0
    CASE 35: EAN(T)=39: STE(T)=84: EAniSpd(T)=500: EAniDelay(T)=0 'SEAT
   END SELECT
  CASE 84: 'SEAT
   ESJMP(T)=-3: EY(T)=-20: RealY(T)=215
   SELECT CASE EAniDelay(T)
    CASE  20: EAN(T)=37 
    CASE  25: EAN(T)=38: PLAY_SAMPLE 31,3,,255 'WHISTLE TO CALL ENEMIES ROUND EVENT
    CASE  40: EAN(T)=37: EMV(T)=3 
    CASE  45: EAN(T)=39 
    CASE 200: STE(T)=80: 'GO JUMP KICK NEAR PLAYER
   END SELECT

  'JUMP KICK -------------------------------------------------------------------------
  CASE 80:
   EAN(T)=25: EAniDelay(T)=0: EAniSpd(T)=200: STE(T)=81
   IF EX(T)<X(PL) THEN ESIDE(T)=4 ELSE ESIDE(T)=5 'TURN TO THE PLAYER SIDE
   TT=DIST/25
   ESJMP(T)=-11: ESPDX(T)=(ESIDE(T)=4)*TT-(ESIDE(T)=5)*TT
  CASE 81:
   INC ESJMP(T),-0.9
   SELECT CASE EAniDelay(T)
    CASE  4: EAN(T)=34 
    CASE  8: EAN(T)=35 
    CASE 12: EAN(T)=34: ESIDE(T)=(ESIDE(T)=4)*6+(ESIDE(T)=5)*7 'TURN 180` 
    CASE 16: EAN(T)=35 
    CASE 20: EAN(T)=34: ESIDE(T)=(ESIDE(T)=6)*4+(ESIDE(T)=7)*5 'TURN BACK 
    CASE 24 TO 35:
     EAN(T)=36
     'KICK THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
     IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND Special(PL)=0 THEN
      InsertWait(PL,T,2)
      InsertHit(XH(PL),YH(PL),1) 'HIT
      PLAY_SAMPLE 24,PL,18000
      INC Energy(PL),-ES_POW(T)
      PHurted(PL)=2
      SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
      INC HCombo(PL),200
      WhoE(PL)=T 'SET WHO HURTED THE PLAYER
      'EAniDelay(T)=36
     ENDIF
    CASE 36: EAN(T)=25: ESPDX(T)=0
    CASE >=40: EAN(T)=25: ESJMP(T)=0: STE(T)=1: EAniSpd(T)=4: EAniDelay(T)=0
   END SELECT

  'ENEMY IS DEAD ---------------------------------------------------------------------
  CASE 100:
   EAniSpd(T)=0
   IF EAN(T)>60 THEN
    'KILL ALL OTHER ENEMIES WHEN DAMND DIES
    KillEnemies(1,T)
    EAN(T)=50: STE(T)=101 ' FLASH BODY AGAIN
   ENDIF
  CASE 101:
   IF EAN(T)>60 THEN
    'KILL ALL OTHER ENEMIES WHEN DAMND DIES (AGAIN)
    KillEnemies(1,T)
    EEnergy(T)=-99: STE(T)=0: RealY(T)=999: Exit Sub 'REMOVE DEAD ENEMY
   ENDIF

  'GRAPPLED BY A PLAYER --------------------------------------------------------------
  CASE 120 TO 170: GrapPlayer(T) 

  'RETURN TO THE ORIGINAL STATE IF SOMETHING GOES WRONG ON GAPPLE
  CASE >=171:
   STE(T)=40: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0

  'FOR ALL OTHER CASES, GET UP!
  CASE ELSE: EAN(T)=1: STE(T)=1

 END SELECT 'END ACTION DAMND -------------------------------------------------------
 
END SUB


'DRAW DAMND / DAMND FROM THE INTRO ROUND 1-1

SUB Draw_DAMND(num,who)

 SELECT CASE num
  'ENERGY AVATAR
  CASE 99 : xa=2:ya=1084:sx=60:sy=16:tx=-16
  'STOPPED / WALKING WITH JESSICA (ROUND 1-1)
  CASE  0,100: xa=423:ya=1083: sx=86: sy=61: tx=-4: ty=13:
               xb=192:yb=1083:sbx=73:sby=61:tbx= 0:tby= 0
  'WALKING / WALKING WITH JESSICA (ROUND 1-1)
  CASE  1,101: xa=423:ya=1083: sx=86: sy=61: tx=-4: ty=13:
               xb=265:yb=1083:sbx=62:sby=65:tbx=-4:tby= 0
  CASE  2,102: xa=423:ya=1083: sx=86: sy=61: tx=-4: ty=12:
               xb=327:yb=1083:sbx=51:sby=65:tbx= 2:tby= 0
  CASE  3,103: xa=423:ya=1083: sx=86: sy=61: tx=-4: ty=12:
               xb=378:yb=1083:sbx=45:sby=65:tbx= 8:tby= 0
  CASE  4,104: xa=423:ya=1083: sx=86: sy=61: tx=-4: ty=12:
               xb=327:yb=1083:sbx=51:sby=65:tbx= 2:tby= 0
  CASE  5,105: xa=423:ya=1083: sx=86: sy=61: tx=-4: ty=13:
               xb=265:yb=1083:sbx=62:sby=65:tbx=-4:tby= 0
  'LAUGHING / LAUGHING WITH JESSICA (ROUND 1-1)
  CASE 10,110: xa=995:ya=1085: sx=86: sy=61: tx=-4: ty=13:
               xb=192:yb=1083:sbx=73:sby=61:tbx= 0:tby= 0
  CASE 11,111: xa=505:ya=1144: sx=86: sy=54: tx=-4: ty=13:
               xb=192:yb=1083:sbx=73:sby=61:tbx= 0:tby= 0
  'PUNCHING
  CASE 13: xa= 192:ya=1148:sx =80: sy=51: tx= 20: ty=  0:
           xb= 102:yb=1083:sbx=90:sby=42:tbx=  0:tby=  0
  CASE 14: xa= 272:ya=1148:sx =53: sy=51: tx=  8: ty=  0:
           xb= 102:yb=1083:sbx=90:sby=42:tbx=  0:tby=  0
  CASE 15: xa= 325:ya=1148:sx =70: sy=51: tx=-20: ty=  0:
           xb= 102:yb=1083:sbx=90:sby=42:tbx=  0:tby=  0
  CASE 16: xa= 395:ya=1148:sx=110: sy=51: tx=-42: ty=  0:
           xb= 102:yb=1083:sbx=90:sby=42:tbx=  0:tby=  0
  CASE 17: xa= 325:ya=1148:sx =70: sy=51: tx=-20: ty=  0:
           xb= 102:yb=1083:sbx=90:sby=42:tbx=  0:tby=  0
  CASE 18: xa= 272:ya=1148:sx =53: sy=51: tx=  8: ty=  0:
           xb= 102:yb=1083:sbx=90:sby=42:tbx=  0:tby=  0
  CASE 19: xa= 192:ya=1148:sx =80: sy=51: tx= 20: ty=  0:
           xb= 102:yb=1083:sbx=90:sby=42:tbx=  0:tby=  0
  'HURT
  CASE 21: xa=677:ya=1083: sx=78: sy=41: tx=12: ty=  0: 'IN THE STOMACH
           xb=591:yb=1150:sbx=66:sby=49:tbx= 0:tby=  0
  CASE 22: xa=509:ya=1083: sx=78: sy=61: tx=-4: ty= 12: 'IN THE FACE
           xb=192:yb=1083:sbx=73:sby=61:tbx= 0:tby=  0
  'FALLING
  CASE 23: xa=978:ya=1146:sx=116:sy=53:tx=5:ty=-20 'FALLING DOWN
  CASE 24,50,52,54,56,58,60:
           xa=903:ya=1123:sx= 75:sy= 37:tx=140:ty=42 'LYING ON THE FLOOR / DEAD
           xb=924:yb=1083:sbx=70:sby=40:tbx= 0
  'GET UP
  CASE 25: xa=657:ya=1159: sx=70: sy=40: tx=10: ty= 85
           xb=423:yb=1083:sbx=86:sby=61:tbx= 0:tby=-26: 'GET UP
              
  CASE 26: xa=677:ya=1083: sx=78: sy=41:tx=-12: ty= 0: 'SUFFERING (AFTER STOMACH ANIMATION)
           xb=658:yb=1132:sbx=68:sby=27:tbx= 0:tby= 0
  CASE 27: xa=903:ya=1160:sx= 75:sy= 39:tx=140:ty=42 'LYING ON THE FLOOR / TRYING TO GET UP
           xb=924:yb=1083:sbx=70:sby=40:tbx= 0
  'SHAKING HEAD
  CASE 28: xa=729:ya=1128:sx= 58:sy= 71:tx=122:ty=42 'LYING ON THE FLOOR / SHAKING HEAD RIGHT
           xb=924:yb=1083:sbx=70:sby=40:tbx= 0
  CASE 29: xa=787:ya=1128:sx= 58:sy= 71:tx=122:ty=42 'LYING ON THE FLOOR / SHAKING HEAD FRONT
           xb=924:yb=1083:sbx=70:sby=40:tbx= 0
  CASE 30: xa=729:ya=1128:sx= 58:sy= 71:tx=122:ty=42 'LYING ON THE FLOOR / SHAKING HEAD RIGHT
           xb=924:yb=1083:sbx=70:sby=40:tbx= 0
  CASE 31: xa=845:ya=1128:sx= 58:sy= 71:tx=122:ty=42 'LYING ON THE FLOOR / SHAKING HEAD BACK
           xb=924:yb=1083:sbx=70:sby=40:tbx= 0
  'JUMPING
  CASE 34: xa= 129:ya=1131:sx= 63:sy=68:tx=0:ty=0
  CASE 35: xa=1245:ya=1136:sx= 68:sy=63:tx=0:ty=0
  CASE 36: xa=   1:ya=1123:sx=128:sy=76:tx=0:ty=0: xp=0: yp=42 'KICKING
  'WHISTLE
  CASE 37: xa=755:ya=1083: sx=82: sy=45: tx=-10: ty=  0:
           xb=589:yb=1083:sbx=73:sby=51:tbx=  0:tby=  0
  CASE 38: xa=841:ya=1083: sx=79: sy=45: tx=- 6: ty=  0:
           xb=589:yb=1083:sbx=73:sby=51:tbx=  0:tby=  0
  'SEATED AT THE WALL
  CASE 39: xa=505:ya=1144: sx=86: sy=54: tx=-10: ty= 15:
           xb=589:yb=1083:sbx=73:sby=51:tbx= 0 :tby=  0
  'BURNING
  CASE 80 : xa=  0:ya=993:sx=121:sy=72
  CASE 81 : xa=121:ya=993:sx=123:sy=72
  CASE 82 : xa=244:ya=993:sx=121:sy=72

  'JESSICA ROUND 1 DAMND INTRO
  CASE 997: xa=1094:ya=1125:sx=51:sy=75:tx= 0:ty=0
  CASE 998: xa=1145:ya=1125:sx=49:sy=75:tx=-2:ty=0
  CASE 999: xa=1194:ya=1125:sx=51:sy=75:tx= 0:ty=0

 END SELECT 'END DAMND

END SUB
