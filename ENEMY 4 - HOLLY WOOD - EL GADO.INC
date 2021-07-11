'HOLLY WOOD / EL GADO ENEMY CONTROLLER

SUB Enemy_HOLLY_WOOD_EL_GADO(T,PL,s)
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
   IF RND<0.2 THEN
    STE(T)=40: EAN(T)=0
    'WALKING
    IF RND>0.5 AND DIST<80 THEN 'MAYBE GO BACK IF NEAR PLAYER IS PUNCHING
     IF EBACKX(T)<>-1 THEN EBACKX(T)=-1: EBACK(T)=-1
    ENDIF
   ENDIF
  ELSE
   'GO BACKWARD IF TOO NEAR
   IF DIST<55 AND STE(T)<50 THEN EBACKX(T)=-1
   'GO TO DIRECTION OF THE NEAR PLAYER
   II=ESPD(T): TT=RealY(T)
   IF RealY(T)<=SMYA THEN INC RealY(T), ABS(ESPD(T))-(EBACKX(T)=-1)*5
   IF RealY(T)>=SMYB THEN INC RealY(T),-ABS(ESPD(T))+(EBACKX(T)=-1)*5
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
   ESPD(T)=ES_SPD(T)
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
    PLAY_SAMPLE 27,PL
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
    PLAY_SAMPLE 16,PL,30000 'CHANGE THIS SOUND LATTER
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
    PLAY_SAMPLE 24,PL
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
    PLAY_SAMPLE 16,PL,30000
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
   STE(T)=20: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0

  'FOR ALL OTHER CASES, GET UP!
  CASE ELSE: EAN(T)=1: STE(T)=1

 END SELECT 'END ACTION SCRIPTS HOLLY WOOD / EL GADO -------------------------------------------
 
END SUB


'DRAW HOLLY WOOD / EL GADO

SUB Draw_HOLLY_WOOD_EL_GADO(num,who,s)

 SELECT CASE num
  'ENERGY AVATAR
  CASE 99 : xa=0:ya=787:sx=99:sy=16:tx=-54:ty=0
  'STOPPED
  CASE  0 : xa=239:ya=787:sx=42:sy=53:tx=0:ty=15:xb=349:yb=787:sbx=45:sby=58:tbx=-16:tby=0
  'WALKING
  CASE  1 : xa=239:ya=787:sx=42:sy=53:tx=0:ty=15:xb=394:yb=787:sbx=33:sby=59:tbx=- 8:tby=0
  CASE  2 : xa=239:ya=787:sx=42:sy=53:tx=0:ty=15:xb=427:yb=787:sbx=48:sby=58:tbx=-22:tby=0
  CASE  3 : xa=239:ya=787:sx=42:sy=53:tx=0:ty=15:xb=394:yb=787:sbx=33:sby=59:tbx=- 8:tby=0
  CASE  4 : xa=239:ya=787:sx=42:sy=53:tx=0:ty=15:xb=349:yb=787:sbx=45:sby=58:tbx=-16:tby=0
  CASE  5 : xa=239:ya=787:sx=42:sy=53:tx=0:ty=15:xb=281:yb=787:sbx=68:sby=59:tbx=-10:tby=0
  'PUNCHING
  CASE 13 : xa=239:ya=845:sx=34:sy=42:tx=-18:ty=6:xb=394:yb=787:sbx=33:sby=59:tbx=-8:tby=0
  CASE 14 : xa=274:ya=849:sx=74:sy=38:tx=-56:ty=2:xb=394:yb=787:sbx=33:sby=59:tbx=-8:tby=0
  CASE 15 : xa=239:ya=845:sx=34:sy=42:tx=-18:ty=6:xb=394:yb=787:sbx=33:sby=59:tbx=-8:tby=0
  'HURT
  CASE 21 : xa=878:ya=787:sx=59:sy=78:tx=0:ty=0 'IN THE STOMACH
  CASE 22 : xa=596:ya=838:sx=51:sy=49:tx=8:ty=8:xb=394:yb=787:sbx=33:sby=59:tbx=-8:tby=0 'FACE
  'FALLING
  CASE 23 : xa=938:ya=787:sx=107:sy=62:tx=0:ty=-20 'FALLING DOWN
  CASE 24,50,52,54,56,58,60:
            xa=778:ya=865:sx=127:sy=22:tx=0:ty=0   'LYING ON THE FLOOR / DEAD
  'GETTING UP / READY TO ATTACK
  CASE 25 : xa=  0:ya=824:sx=56:sy=63:tx=0:ty=0
  'AIR KNIFE ATTACK
  CASE 34 : xa= 57:ya=817:sx= 78:sy=70:tx=0:ty=0
  CASE 35 : xa=135:ya=813:sx=104:sy=74:tx=0:ty=0
  CASE 36 : xa=844:ya=787:sx= 34:sy=67:tx=0:ty=0:xb=781:yb=787:sbx=63:sby=57:tbx=-12:tby=0
  CASE 37 : xa=844:ya=787:sx= 34:sy=67:tx=0:ty=0:xb=705:yb=787:sbx=75:sby=43:tbx=  0:tby=0
  CASE 38 : xa=844:ya=787:sx= 34:sy=67:tx=0:ty=0:xb=781:yb=787:sbx=63:sby=57:tbx=-12:tby=0: s=(s=5)*4+(s=4)*5
  CASE 39 : xa=135:ya=813:sx=104:sy=74:tx=0:ty=0:s=(s=5)*4+(s=4)*5
  CASE 40 : xa= 57:ya=817:sx= 78:sy=70:tx=0:ty=0:s=(s=5)*4+(s=4)*5
  'THROWING A KNIFE
  CASE 70 : xa=541:ya=787:sx=83:sy=50:tx= 12:ty=7:xb=394:yb=787:sbx=33:sby=59:tbx=- 8:tby=0
  CASE 71 : xa=561:ya=842:sx=35:sy=45:tx=-14:ty=7:xb=349:yb=787:sbx=45:sby=58:tbx=-16:tby=0
  CASE 72 : xa=624:ya=787:sx=81:sy=44:tx=-36:ty=7:xb=281:yb=787:sbx=68:sby=59:tbx=-12:tby=0
  'STAB
  CASE 73 : xa=475:ya=788:sx= 66:sy=52:tx=-24:ty=15:xb=394:yb=787:sbx=33:sby=59:tbx=- 8:tby=0
  CASE 74 : xa=475:ya=840:sx= 86:sy=47:tx=-44:ty=10:xb=394:yb=787:sbx=33:sby=59:tbx=- 8:tby=0
  CASE 75 : xa=348:ya=846:sx=103:sy=41:tx=-60:ty= 8:xb=427:yb=787:sbx=48:sby=58:tbx=-24:tby=0
  CASE 76 : xa=475:ya=840:sx= 86:sy=47:tx=-44:ty=10:xb=394:yb=787:sbx=33:sby=59:tbx=- 8:tby=0
  CASE 77 : xa=475:ya=788:sx= 66:sy=52:tx=-24:ty=15:xb=394:yb=787:sbx=33:sby=59:tbx=- 8:tby=0
  'DASH
  CASE 78 : xa=647:ya=841:sx=131:sy=46:tx=0:ty=0
  'BURNING
  CASE 80 : xa=  0:ya=993:sx=121:sy=72
  CASE 81 : xa=121:ya=993:sx=123:sy=72
  CASE 82 : xa=244:ya=993:sx=121:sy=72

 END SELECT 'END HOLLY WOOD / EL GADO
 if num<80 or num>82 then INC ya,(who-11)*100: INC yb,(who-11)*100

END SUB

