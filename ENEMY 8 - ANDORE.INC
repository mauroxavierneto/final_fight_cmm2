'ANDORE FAMILY

SUB Enemy_ANDORE(T,PL)
 LOCAL II,TT

 IF EMV(T)=1 OR (STE(T)>=70 AND STE(T)<=100) THEN INC EAniDelay(T)
 IF EAniDelay(T)>EAniSpd(T) THEN
  EAniDelay(T)=0
  IF STE(T)>1 THEN INC EAN(T)
  IF STE(T)>40 AND STE(T)<52 THEN STE(T)=1
 ENDIF

 'WALKING
 IF STE(T)<50 AND EMV(T)>0 THEN 'CAN WALK OR MAKE ANY ATTACK? -----------------

  'DECREASE TO WALK
  INC STE(T),-1
  IF EX(T)<X(PL) THEN ESide(T)=4 ELSE ESide(T)=5

  IF STE(T)<1 THEN
   EBACK(T)=1: EBACKX(T)=1
   STE(T)=1 'KEEP STOPPED UNTIL BACK TO WALK RANDOMLY 
   IF RND<0.04 THEN
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
   INC EX(T),((EX(T)<X(PL)-60+TT)*II*EBACKX(T))-((EX(T)>X(PL)+60-TT)*II*EBACKX(T))
  ENDIF

 ELSE 'STE(T)>=50 - DON'T WALK! ---------------------------------
  ESPD(T)=0
 ENDIF

 'ENEMY STATUS / ACTION SCRIPTS -----------------------------------------------------

 page write 1: ? STE(T)

 SELECT CASE STE(T)

  'WALKING --------------------------------------------------------------------------
  CASE 1 TO 40: 
   IF ESPD(T)=0 THEN STE(T)=1
   EAniSpd(T)=3
   ESPD(T)=ES_SPD(T)*EBACK(T)
   IF EAN(T)>5 THEN EAN(T)=0
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
   ESPDX(T)=ESPDX(T)\2: IF EAniDelay(T)>15 OR EEnergy(T)<=0 THEN INC STE(T)
   EXIT SUB
  CASE 54:
   EAN(T)=25: INC STE(T): EAniDelay(T)=0: EAniSpd(T)=20: ESPDX(T)=0
   'ENEMY DEAD?
   IF EEnergy(T)<=0 THEN STE(T)=100: EAN(T)=50: EAniDelay(T)=20: EAniSpd(T)=1
   EXIT SUB
  CASE 55:
   EAN(T)=25: IF EaniDelay(T)>5 THEN INC STE(T): EAniDelay(T)=0: EAniSpd(T)=15
   EXIT SUB
  CASE 56: EAN(T)=1: STE(T)=1: EXIT SUB

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
   EAN(T)=22: STE(T)=52: EAniDelay(T)=0: EAniSpd(T)=10: EXIT SUB

  'GRAPPLED BY A PLAYER --------------------------------------------------------------
  CASE 120 TO 170: GrapPlayer(T)

  'PUNCH------------------------------------------------------------------------------
  CASE 70: EAN(T)=11: EAniDelay(T)=0: EAniSpd(T)=10: INC STE(T): EXIT SUB
  CASE 71:
   EAN(T)=11: IF EAniSpd(T)>2 THEN EAniDelay(T)=0: EAniSpd(T)=4: INC STE(T)
   EXIT SUB
  CASE 72:
   'PUNCH THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
   IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND EAN(T)=12 AND Special(PL)=0 THEN
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLAY_SAMPLE 24,PL
    INC Energy(PL),-ES_POW(T)
    PHurted(PL)=2
    SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
    INC HCombo(PL),75
    WhoE(PL)=T 'SET WHO HURTED THE PLAYER
    STE(T)=73
   ENDIF
   IF EAN(T)>=13 THEN STE(T)=73
   EXIT SUB
  CASE 73: STE(T)=1: EAniDelay(T)=0: EAniSpd(T)=3: EXIT SUB

  'JUMP ON THE PLAYER IF HE IS IN THE GROUND -----------------------------------------
  CASE 80:
   IF AN(PL)<>41 THEN 'CANCEL JUMP IF PLAYER ISN'T HURTED IN THE GROUND
    TT=(ESIDE(T)=4)*10-(ESIDE(T)=5)*10
    IF (EX(T)+TT>X(PL)-20 AND EX(T)+TT<X(PL)+20 AND RealY(T)>RealY(PL)-5 AND RealY(T)<RealY(PL)+5 AND Energy(PL)>0) AND Special(PL)=0 THEN
     STE(T)=85 'PLAYER IS NEAR ENOUGH AND ANDORE DO A PILE DRIVER
    ELSE
     STE(T)= 1 'ISN'T NEAR THEN DOES NOTHING
    ENDIF
    EXIT SUB
   ENDIF
   IF EX(T)<X(PL) THEN ESIDE(T)=4 ELSE ESIDE(T)=5 'TURN TO THE PLAYER SIDE
   EAN(T)=25: EAniDelay(T)=0: EAniSpd(T)=30: STE(T)=81
   EXIT SUB
  CASE 81:
   EAN(T)=25: IF EAniSpd(T)>10 THEN STE(T)=82
   EXIT SUB
  CASE 82:
   EAN(T)=1: EAniDelay(T)=0: EAniSpd(T)=500: STE(T)=83
   TT=DIST/25
   ESJMP(T)=-15: ESPDX(T)=(ESIDE(T)=4)*TT-(ESIDE(T)=5)*TT
   EXIT SUB
  CASE 83: 'JUMP  
   IF RealY(T)>RealY(PL)+2 THEN INC RealY(T),-1
   IF RealY(T)<RealY(PL)-2 THEN INC RealY(T)
   INC ESJMP(T),-0.5
   'HURT THE PLAYER ONLY IF IS NOT USING A SPECIAL MOVE
   IF (EX(T)>X(PL)-24 AND EX(T)<X(PL)+24 AND RealY(T)>RealY(PL)-5 AND RealY(T)<RealY(PL)+5 AND EY(T)>-20 AND Energy(PL)>0) AND Special(PL)=0 THEN
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLAY_SAMPLE 24,PL,18000
    INC Energy(PL),-ES_POW(T)
    PHurted(PL)=2: SHAKE=10
    SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
    INC HCombo(PL),200
    WhoE(PL)=T 'SET WHO HURTED THE PLAYER
   ENDIF
   IF ESJMP(T)<0 THEN EAN(T)=25 ELSE EAN(T)=15
   IF EY(T)>=0 THEN EAN(T)=25: ESPDX(T)=0:ESJMP(T)=-15: STE(T)=84 'JUMP AGAIN
   EXIT SUB
  CASE 84:
   EAN(T)=25: IF EY(T)>=0 THEN EY(T)=0:EAN(T)=0:ESJMP(T)=0:STE(T)=1:EAniSpd(T)=4:EAniDelay(T)=0
   EXIT SUB

  'ANDORE RUN ------------------------------------------------------------------------
  CASE 75: 
   'IF THE PLAYER IS TOO NEAR AND IS HURTED IN THE GROUND TRY TO JUMP IN TO HIM
   IF DIST<85 THEN STE(T)=80: EXIT SUB 

   'TURN ENEMY TO RUN IN THE ENEMY POSITION
   IF EX(T)>X(PL) THEN ESIDE(T)=5 ELSE ESIDE(T)=4
   EAN(T)=4: EAniDelay(T)=0: EAniSpd(T)=10: STE(T)=76: PLAY_SAMPLE 11,4,22050 'SCREAM
   EXIT SUB
  CASE 76:
   EAN(T)=4: IF EAniDelay(T)>1 THEN INC STE(T) 'PREPARE TO RUN
   EXIT SUB
  CASE 77:
   EAN(T)=6: EAniDelay(T)=0: EAniSpd(T)=2: INC STE(T): EMV(T)=1
   ESPDX(T)=(ESide(T)=4)*3-(ESide(T)=5)*3: PLAY_SAMPLE 25,3,,100: 'RUNNING SOUND
   EXIT SUB
  CASE 78:
   IF EAN(T)>9 THEN EAN(T)=6: INC EMV(T)
   INC EX(T),ESPDX(T) 'RUN!
   'SMASH CHEST THE PLAYER ONLY IF IS NOT ALREADY BE HURTED AND NOT USING SPECIAL MOVE
   IF COLLIDE(0)=&HFFFFFF AND PHurted(PL)=0 AND Special(PL)=0 THEN
    EAN(T)=10: EMV(T)=5
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLAY_SAMPLE 24,PL
    INC Energy(PL),-ES_POW(T)
    SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'CHANGE PLAYER SIDE
    PHurted(PL)=2
    INC HCombo(PL),200
    EAniDelay(T)=0: EAniSpd(T)=200
    ESPDX(T)=(ESIDE(T)=4)*8-(ESIDE(T)=5)*8 'MAKE ANDORE SLIDE WHEN SMASH CHEST THE PLAYER
    WhoE(PL)=T 'SET WHO HURTED THE PLAYER
   ENDIF
   'STOP RUNNING
   IF EMV(T)>=3 THEN STE(T)=79
   EXIT SUB
  CASE 79:
   IF EMV(T)=5 THEN
    EAN(T)=10 'SMASH CHEST?
    INC ESPDX(T),(ESIDE(T)=5)-(ESIDE(T)=4)
    IF ESPDX(T)=0 THEN EMV(T)=1
   ELSE
    EAniSpd(T)=4: STE(T)=1: EMV(T)=1: EAniDelay(T)=0: EAniSpd(T)=2
    EY(T)=0: ESJMP(T)=0: ESPDX(T)=0: EBACKX(T)=0: EBACK(T)=0: ESPDX(T)=0
   ENDIF
   EXIT SUB

  'PILE DRIVER ! ---------------------------------------------------------------------
  CASE 85: 'GRAPLE THE PLAYER
   IF EX(T)<X(PL) THEN ESIDE(T)=4 ELSE ESIDE(T)=5 'TURN TO THE PLAYER SIDE
   SIDE(PL)=(ESIDE(T)=4)*5+(ESIDE(T)=5)*4
   EAN(T)=18: EAniDelay(T)=0: EAniSpd(T)=30: STE(T)=86
   Andore_Pile_Driver(0,T,PL)
   AN(PL)=39
   EXIT SUB
  CASE 86: 'WAIT
   EAN(T)=18: IF EAniSpd(T)>10 THEN STE(T)=87
   Andore_Pile_Driver(0,T,PL)
   AN(PL)=39
   EXIT SUB
  CASE 87: 'START PILE DRIVE (JUMP)
   PLAY_SAMPLE 11,4,22050 'SCREAM
   IF SIDE(PL)=4 THEN SIDE(PL)=6 'ROTATE PLAYER
   IF SIDE(PL)=5 THEN SIDE(PL)=7
   Andore_Pile_Driver(1,T,PL)
   EAN(T)=1: EAniDelay(T)=0: EAniSpd(T)=500: STE(T)=88
   TT=DIST/25
   ESJMP(T)=-15: ESPDX(T)=(ESIDE(T)=4)*TT-(ESIDE(T)=5)*TT
   EXIT SUB
  CASE 88: 'JUMP  
   Andore_Pile_Driver(1,T,PL)
   INC ESJMP(T),-0.5
   IF EY(T)>=0 THEN 'JUMP AGAIN AND HURT THE PLAYER
    EAN(T)=25:ESPDX(T)=0:ESJMP(T)=-15: STE(T)=89 
    InsertWait(PL,T,2)
    InsertHit(XH(PL),YH(PL),1) 'HIT
    PLAY_SAMPLE 24,PL,18000
    INC Energy(PL),-Energy(PL)\2-10
    PHurted(PL)=2: SHAKE=10
    SIDE(PL)=(ESide(T)=4)*5+(ESide(T)=5)*4 'RESTORE PLAYER SIDE
    INC HCombo(PL),250
    WhoE(PL)=T 'SET WHO HURTED THE PLAYER
   ENDIF
   EAN(T)=25
   EXIT SUB
  CASE 89:
   EAN(T)=25
   IF EY(T)>=0 THEN
    EY(T)=0:EAN(T)=0:ESJMP(T)=0:STE(T)=1:EAniSpd(T)=4:EAniDelay(T)=0
    CtrlType(PL)=TCType(PL) 'BRING BACK THE PLAYER'S CNTROL
   ENDIF
   EXIT SUB

  'ENEMY IS DEAD ---------------------------------------------------------------------
  CASE 100: EAniSpd(T)=0: IF EAN(T)>60 THEN EAN(T)=50: INC STE(T) ' FLASH BODY AGAIN
  CASE 101: IF EAN(T)>60 THEN EEnergy(T)=-99: STE(T)=0: RealY(T)=999: Exit Sub 'REMOVE DEAD ENEMY

  'RETURN TO THE ORIGINAL STATE IF SOMETHING GOES WRONG ON GAPPLE
  CASE >=171:
   STE(T)=20: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0

  'FOR ALL OTHER CASES, GET UP!
  CASE ELSE: EAN(T)=1: STE(T)=1

 END SELECT 'END ACTION SCRIPTS BILL BULL / G. ORIBER / WONG WHO -------------------------------
 
END SUB


'DRAW ANDORE FAMILY

SUB Draw_ANDORE(num,who)

 SELECT CASE num

  'ENERGY AVATAR
  CASE 99 : xa=1426:ya=171:sx= 92:sy=16:tx=-48
  'WALKING
  CASE  0 : xa=1220:ya=173:sx= 67:sy=52:tx=0:ty=0:xb=1552:yb=  0:sbx=36:sby=61:tbx=18:tby=0
  CASE  1 : xa=1220:ya=173:sx= 67:sy=52:tx=0:ty=1:xb=1265:yb=  0:sbx=69:sby=61:tbx=14:tby=0 
  CASE  2 : xa=1220:ya=173:sx= 67:sy=52:tx=0:ty=2:xb=1334:yb=  0:sbx=59:sby=61:tbx=38:tby=0 
  CASE  3 : xa=1220:ya=173:sx= 67:sy=52:tx=0:ty=1:xb=1393:yb=  0:sbx=36:sby=61:tbx=18:tby=0 
  CASE  4 : xa=1220:ya=173:sx= 67:sy=52:tx=0:ty=2:xb=1429:yb=  0:sbx=68:sby=61:tbx=14:tby=-2 
  CASE  5 : xa=1220:ya=173:sx= 67:sy=52:tx=0:ty=0:xb=1497:yb=  0:sbx=55:sby=61:tbx=32:tby=0
  'RUNNING
  CASE  6 : xa=1460:ya=117:sx= 74:sy=50:tx=0:ty=0:xb=1174:yb=117:sbx=84:sby=54:tbx=54:tby=0
  CASE  7 : xa=1460:ya=117:sx= 74:sy=50:tx=0:ty=0:xb=1258:yb=112:sbx=41:sby=61:tbx=54:tby=0
  CASE  8 : xa=1460:ya=117:sx= 74:sy=50:tx=0:ty=0:xb=1299:yb=112:sbx=87:sby=57:tbx=58:tby=0
  CASE  9 : xa=1460:ya=117:sx= 74:sy=50:tx=0:ty=0:xb=1556:yb=196:sbx=43:sby=55:tbx=64:tby=0
  'SMASH RUN
  CASE 10 : xa=1174:ya=171:sx= 46:sy=59:tx=16:ty=5:xb=1552:yb=  0:sbx=36:sby=61:tbx= 0:tby=0
  'PUNCHING
  CASE 11,13 : xa=1372:ya= 61:sx= 91:sy=50:tx=0:ty=2:xb=1429:yb=  0:sbx=68:sby=61:tbx=10:tby=0
  CASE 12 : xa=1260:ya= 61:sx=112:sy=51:tx=-40:ty=0:xb=1497:yb=  0:sbx=55:sby=61:tbx=64-40:tby=0
  'JUMPING / 25 - GETTING UP
  CASE 14,25 : xa=1220:ya=173:sx=67:sy=52:tx=0:ty=0:xb=1541:yb= 61:sbx=58:sby=43:tbx=10:tby=0 'PREP
  CASE 15 : xa=1174:ya=  0:sx=91:sy=64:tx=0:ty=0 'FALLING HARD
  'STRANGLING
  CASE 16 : xa=1174:ya= 64:sx= 86:sy=53:tx=0:ty=0:xb=1497:yb=  0:sbx=55:sby=61:tbx=64:tby=0'GET
  CASE 17 : xa=1386:ya=111:sx= 74:sy=59:tx=0:ty=0:xb=1497:yb=  0:sbx=55:sby=61:tbx=56:tby=0'UP
  CASE 18 : xa=1463:ya= 61:sx= 62:sy=56:tx=0:ty=0:xb=1497:yb=  0:sbx=55:sby=61:tbx=48:tby=0'NEAR
  'HURT
  CASE 21,22 : xa=1538:ya=104:sx=61:sy=92:tx=0
  'FALLING
  CASE 23 : xa=1287:ya=173:sx=117:sy=67:tx=5:ty=-20 'FALLING DOWN
  CASE 24,50,52,54,56,58,60:
            xa=1408:ya=196:sx=148:sy=34:tx=5        'LYING ON THE FLOOR / DEAD
  'BURNING
  CASE 80 : xa=  0:ya=993:sx=121:sy=72
  CASE 81 : xa=121:ya=993:sx=123:sy=72
  CASE 82 : xa=244:ya=993:sx=121:sy=72

 END SELECT 

 if num<80 or num>82 then INC ya,(Who-19)*251: INC yb,(Who-19)*251

END SUB

' KEEP THE PLAYER GRAPPLED IN A PILE DRIVER
SUB Andore_Pile_Driver(TP,T,PL)
 LOCAL TT
 CtrlType(PL)=-1 'REMOVE PLAYER'S CONTROL
 PHurted(PL)=19
 JumpX(PL)=0: JumpY(PL)=0
 AN(PL)=38
 TT=(PlType(PL)=HAGGAR)*10-(PlType(PL)=GUY)*2
 IF TP=0 THEN
  X(PL)=EX(T)+(ESIDE(T)=4)*(6+TT)-(ESIDE(T)=5)*(6+TT)
  RealY(PL)=RealY(T)-2
  Y(PL)=EY(T)-30+ESJMP(T)+(PlType(PL)=HAGGAR)*3-(PlType(PL)=GUY)*5
 ELSE
  X(PL)=EX(T)+(ESIDE(T)=4)*15-(ESIDE(T)=5)*15
  RealY(PL)=RealY(T)+2
  Y(PL)=EY(T)+ESJMP(T)+(PlType(PL)=HAGGAR)*3
 ENDIF
END SUB

