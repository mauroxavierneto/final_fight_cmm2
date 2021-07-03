'POISON / ROXY ENEMY CONTROLLER

SUB Enemy_POISON_ROXY(T,PL)
 LOCAL II,TT

 IF EMV(T)=1 OR (STE(T)>=70 AND STE(T)<=99) THEN INC EAniDelay(T)
 IF EAniDelay(T)>EAniSpd(T) THEN
  EAniDelay(T)=0
  INC EAN(T)
  IF STE(T)>20 AND STE(T)<52 THEN STE(T)=1
 ENDIF

 'WALKING
 IF STE(T)<50 AND EMV(T)>0 THEN 'CAN WALK OR MAKE ANY ATTACK? -----------------

  'DECREASE TO WALK
  INC STE(T),-1
  INC RealY(T),ESPDY(T)

  IF STE(T)<1 THEN
   EBACK(T)=1: EBACKX(T)=1: EAN(T)=0
   STE(T)=1 'KEEP STOPPED UNTIL BACK TO WALK RANDOMLY
   IF RND<0.7 THEN
    'ALWAYS WALKING WITH ATTENTION
    STE(T)=20
    IF RND>0.6 AND DIST<80 THEN 'MAYBE GO BACK IF NEAR PLAYER IS PUNCHING
     IF Punch(PL)>0 AND EBACK(T)<>-1 THEN STE(T)=90': EBACKX(T)=-1 
    ENDIF
   ENDIF
  ELSE
   'GO BACKWARD IF TOO NEAR
   IF DIST<35 AND STE(T)<50 AND RND>0.85 THEN STE(T)=90
   'GO TO DIRECTION OF THE NEAR PLAYER
   II=ESPD(T): TT=RealY(T)
   IF RealY(T)<=SMYA THEN INC RealY(T), ABS(ESPD(T)): ESPDY(T)=0
   IF RealY(T)>=SMYB THEN INC RealY(T),-ABS(ESPD(T)): ESPDY(T)=0

   'USE ESPDX AND ESPDY TO MAKE THE MOVEMENT MORE CIRCULAR
   IF RealY(T)>RealY(PL)+2 THEN INC ESPDY(T),-0.4
   IF RealY(T)<RealY(PL)-2 THEN INC ESPDY(T), 0.4
   IF EX(T)<X(PL)-50 THEN INC ESPDX(T), 0.2
   IF EX(T)>X(PL)+50 THEN INC ESPDX(T),-0.2

   IF EX(T)<X(PL) THEN ESide(T)=4 ELSE ESide(T)=5
  ENDIF

 ELSE 'STE(T)>=50 - DON'T WALK! ---------------------------------
  ESPD(T)=0
  ESPDY(T)=0
 ENDIF

 'ENEMY STATUS / ACTION SCRIPTS -----------------------------------------------------

 SELECT CASE STE(T)

  'WALKING WITH ATTENTION -----------------------------------------------------------
  CASE 1 TO 40: 
   IF ESPD(T)=0 THEN STE(T)=1
   EAniSpd(T)=3
   ESPD(T)=ES_SPD(T)*EBACK(T)
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
   EAN(T)=24: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=3: ESPDX(T)=0
   'ENEMY DEAD?
   IF EEnergy(T)<=0 THEN STE(T)=100: EAN(T)=50: EAniDelay(T)=0: EAniSpd(T)=1       
  CASE 55:
   EAN(T)=25: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=10
  CASE 56: EAN(T)=0: STE(T)=1

  'THROWED UPDOWN --------------------------------------------------------------------
  CASE 60:
   EAN(T)=21: STE(T)=61: EAniDelay(T)=0: EAniSpd(T)=15
   IF ESide(T)=4 THEN ESide(T)=7 ELSE ESide(T)=6
   INC EX(T),-ESPDX(T)
  CASE 61:
   IF EAniDelay(T)>10 THEN INC STE(T)
  CASE 62:
   EAN(T)=22: STE(T)=52: EAniDelay(T)=0: EAniSpd(T)=10

  'CROUCHED --------------------------------------------------------------------------
  CASE 66:
   EAN(T)=25: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=67: EMV(T)=0: ESPDX(T)=0
   IF EX(T)<245 THEN STE(T)=1
  CASE 67:
   EAN(T)=25: EAniDelay(T)=0: EAniSPD(T)=10
   STE(T)=66: EMV(T)=0: ESPDX(T)=0
   IF EX(T)<245 THEN STE(T)=1

  'PUNCH -----------------------------------------------------------------------------
  CASE 70: EAN(T)=13: EAniDelay(T)=0: EAniSpd(T)=4: INC STE(T): ESPDX(T)=0
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
  CASE 72: IF EAN(T)>15 THEN STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=4

  'KICK -----------------------------------------------------------------------------
  CASE 75: EAN(T)=16: EAniDelay(T)=0: EAniSpd(T)=2: INC STE(T): ESPDX(T)=0
  CASE 76:       
   'PUNCH THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
   IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=18 AND Special(PL)=0 THEN
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLAY_SAMPLE 24,PL
    INC Energy(PL),-ES_POW(T)
    PHurted(PL)=2
    SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
    INC HCombo(PL),350
    WhoE(PL)=T 'SET WHO HURTED THE PLAYER
    STE(T)=77: EAniDelay(T)=0: EAniSpd(T)=3
   ENDIF
  IF EAN(T)>19 THEN STE(T)=77
  CASE 77: IF EAN(T)>19 THEN STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=3

  'ACROBATIC JUMP KICK ---------------------------------------------------------------
  CASE 80: 
   'TURN ENEMY TO JUMP IN THE ENEMY POSITION
   IF EX(T)>X(PL) THEN ESIDE(T)=5 ELSE ESIDE(T)=4
   EAN(T)=25: EAniDelay(T)=0: EAniSpd(T)=20: INC STE(T): ESPDX(T)=0
  CASE 81:
   EAN(T)=25:
    IF EAniDelay(T)>5 THEN 'WAIT CROUCHED THEN START TO JUMP
     EAN(T)=25: EAniDelay(T)=0: EAniSpd(T)=20: INC STE(T)
     ESPDX(T)=(ESide(T)=4)*3-(ESide(T)=5)*3:ESJMP(T)=-13
    ENDIF
  CASE 82: 
   EAN(T)=34
   INC EX(T),ESPDX(T): INC ESPDX(T),-SGN(ESPDX(T))*0.06: INC ESJMP(T),-0.75
   IF EAniDelay(T)>4 THEN
    EAN(T)=37: INC STE(T): EAniDelay(T)=0: ESIDE(T)=(ESIDE(T)=4)*7+(ESIDE(T)=5)*6 'ROTATE 180`
   ENDIF
  CASE 83:
   EAN(T)=37
   INC EX(T),ESPDX(T): INC ESPDX(T),-SGN(ESPDX(T))*0.06: INC ESJMP(T),-0.75
   IF EAniDelay(T)>4 THEN EAN(T)=40: INC STE(T): EAniDelay(T)=0      
  CASE 84:
   INC EX(T),ESPDX(T): INC ESPDX(T),-SGN(ESPDX(T))*0.06: INC ESJMP(T),-0.75
   EAN(T)=40
   IF EAniDelay(T)>4 THEN
    EAN(T)=37: INC STE(T): EAniDelay(T)=0: ESIDE(T)=(ESIDE(T)=7)*4+(ESIDE(T)=6)*5 'TURN BACK 180`
   ENDIF
  CASE 85:
   INC EX(T),ESPDX(T): INC ESPDX(T),-SGN(ESPDX(T))*0.06: INC ESJMP(T),-0.75
   EAN(T)=37: IF EAniDelay(T)>4 THEN INC STE(T): EAniDelay(T)=0
  CASE 86: 'ATTACK!
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
   ENDIF
   INC EX(T),ESPDX(T): INC ESPDX(T),-SGN(ESPDX(T))*0.06: INC ESJMP(T),-0.75
   EAN(T)=38: IF EAniDelay(T)>10 THEN INC STE(T): EAniDelay(T)=0
  CASE 87:
   INC EX(T),ESPDX(T): INC ESPDX(T),-SGN(ESPDX(T))*0.06: INC ESJMP(T),-0.75
   EAN(T)=37: IF EAniDelay(T)>2 THEN INC STE(T): EAniDelay(T)=0
  CASE 88:
   EAN(T)=25 
   IF EAniDelay(T)>3 THEN
    ESPDX(T)=0: EAniDelay(T)=0: EaniSpd(T)=40
    EBACKX(T)=0: EBACK(T)=0: EY(T)=0: ESJMP(T)=0: STE(T)=1
   ENDIF

  'ACROBATIC BACKFLIP ----------------------------------------------------------------
  CASE 90: 
   'TURN ENEMY TO JUMP IN THE ENEMY POSITION
   IF EX(T)>X(PL) THEN ESIDE(T)=5 ELSE ESIDE(T)=4
   EAN(T)=23: EAniDelay(T)=1: EAniSpd(T)=100: INC STE(T)
   ESPDX(T)=(ESide(T)=5)*2-(ESide(T)=4)*2:ESJMP(T)=-7
  CASE 91:
   INC EX(T),ESPDX(T)': INC ESPDX(T),-SGN(ESPDX(T))*0.06
   INC ESJMP(T),-0.5
   SELECT CASE EAniDelay(T)
    CASE  4: EAN(T)=23
    CASE  8: EAN(T)=39
    CASE 12: EAN(T)=35
    CASE 16 TO 19: EAN(T)=36: ESPDX(T)=0
    CASE 20: EAN(T)=35: ESPDX(T)=(ESide(T)=5)*2-(ESide(T)=4)*2:ESJMP(T)=-14 'JUMP AGAIN
    CASE 24: EAN(T)=39: ESIDE(T)=(ESIDE(T)=4)*7+(ESIDE(T)=5)*6 'ROTATE 180`
    CASE 28: EAN(T)=37: ESIDE(T)=(ESIDE(T)=7)*4+(ESIDE(T)=6)*5 'TURN BACK 180`
    CASE 32: EAN(T)=40: ESIDE(T)=(ESIDE(T)=4)*7+(ESIDE(T)=5)*6 'ROTATE 180`
    CASE 36: EAN(T)=37
    CASE 40: EAN(T)=40: ESIDE(T)=(ESIDE(T)=7)*4+(ESIDE(T)=6)*5 'TURN BACK 180`
    CASE 44: EAN(T)=37
    CASE 48: EAN(T)=25: INC STE(T): EaniDelay(T)=0
   END SELECT
  CASE 92:
   EAN(T)=25 
   IF EAniDelay(T)>3 THEN
    EAN(T)=25 
    ESPDX(T)=0: EAniDelay(T)=0: EaniSpd(T)=40
    EBACKX(T)=0: EBACK(T)=0: EY(T)=0: ESJMP(T)=0: STE(T)=1
   ENDIF

  'ENEMY IS DEAD ---------------------------------------------------------------------
  CASE 100: EAniSpd(T)=0: IF EAN(T)>60 THEN EAN(T)=50: INC STE(T) ' FLASH BODY AGAIN
  CASE 101: IF EAN(T)>60 THEN EEnergy(T)=-99: STE(T)=0: RealY(T)=999: Exit Sub 'REMOVE DEAD ENEMY

  'GRAPPLED BY A PLAYER --------------------------------------------------------------
  CASE 120 TO 170: GrapPlayer(T)

  'RETURN TO THE ORIGINAL STATE IF SOMETHING GOES WRONG ON GAPPLE
  CASE >=171:
   STE(T)=20: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0

  'FOR ALL OTHER CASES, GET UP!
  CASE ELSE: EAN(T)=1: STE(T)=1

 END SELECT 'END ACTION SCRIPTS POISON / ROXY ----------------------------------------
 
END SUB


'DRAW POISON / ROXY

SUB Draw_POISON_ROXY(num,who)

 SELECT CASE num
  'ENERGY AVATAR
  CASE 99 : xa=1008:ya=599:sx=67:sy=16:tx=-22:ty=0
  'WALKING
  CASE  0 : xa= 51:ya=599:sx=43:sy=94:tx=-8:ty= 0
  CASE  1 : xa= 94:ya=602:sx=39:sy=91:tx=10:ty=-3
  CASE  2 : xa=133:ya=601:sx=28:sy=92:tx= 0:ty=-2
  CASE  3 : xa=161:ya=600:sx=45:sy=93:tx=-4:ty=-1
  CASE  4 : xa=206:ya=599:sx=43:sy=94:tx= 6:ty= 0
  CASE  5 : xa=249:ya=599:sx=29:sy=94:tx= 0:ty= 0
  'PUNCHING
  CASE 13 : xa=785:ya=599:sx=60:sy=44:tx= 34:ty=0:xb=992:yb=639:sbx=69:sby=54:tbx=0:tby=0
  CASE 14 : xa=537:ya=603:sx=73:sy=30:tx=-36:ty=1:xb=992:yb=639:sbx=69:sby=54:tbx=0:tby=0
  CASE 15 : xa=612:ya=604:sx=42:sy=29:tx=- 8:ty=1:xb=992:yb=639:sbx=69:sby=54:tbx=0:tby=0
  'KICKING
  CASE 16 : xa=278:ya=600:sx=49:sy=93:tx= 30:ty=0
  CASE 17 : xa=327:ya=600:sx=64:sy=94:tx=-20:ty=0
  CASE 18 : xa=433:ya=599:sx=60:sy=18:tx=-48:ty=35:xb=493:yb=607:sbx=44:sby=86:tbx=40:tby=0
  CASE 19 : xa=327:ya=600:sx=64:sy=94:tx=-20:ty=0
  CASE 20 : xa=278:ya=600:sx=49:sy=93:tx= 30:ty=0
  'HURT
  CASE 21 : xa=729:ya=607:sx= 56:sy=86:tx=3 'IN THE STOMACH
  CASE 22 : xa=680:ya=607:sx= 49:sy=86:tx=9 'IN THE FACE
  'FALLING
  CASE 23 : xa=785:ya=646:sx=100:sy=47:tx=5:ty=-20 'FALLING DOWN
  CASE 24,50,52,54,56,58,60:
            xa=845:ya=612:sx=122:sy=21:tx=5        'LYING ON THE FLOOR / DEAD
  'GETTING UP / CROUCHED     
  CASE 25:  xa=  0:ya=632:sx= 51:sy=61:tx=5
  'ACROBATICS
  CASE 34 : xa= 391:ya=617:sx=102:sy=76:tx= 0:ty=0
  CASE 35 : xa=1047:ya=607:sx= 86:sy=69:tx=88:ty=0:xb=967:yb=599:sbx=40:sby=34:tbx= 0: tby= 0
  CASE 36 : xa=1047:ya=607:sx= 86:sy=69:tx=80:ty=0:xb=  4:yb=599:sbx=47:sby=29:tbx= 0: tby= 0
  CASE 37 : xa= 537:ya=633:sx= 48:sy=60:tx= 0:ty=0
  CASE 38 : xa= 585:ya=633:sx= 96:sy=60:tx= 0:ty=0
  CASE 39 : xa= 885:ya=633:sx=107:sy=60:tx= 0:ty=0
  CASE 40 : xa=1133:ya=599:sx= 60:sy=47:tx= 0:ty=0
  'BURNING
  CASE 80 : xa=  0:ya=993:sx=121:sy=72:who=17
  CASE 81 : xa=121:ya=993:sx=123:sy=72:who=17
  CASE 82 : xa=244:ya=993:sx=121:sy=72:who=17

 END SELECT 'END POISON / ROXY
 INC ya,(Who-17)*94
 INC yb,(Who-17)*94

END SUB

