'HOLLY WOOD RED ENEMY CONTROLLER

SUB Enemy_HOLLY_WOOD_RED(T,PL)
 LOCAL II,TT

 IF EMV(T)>0 OR (STE(T)>=70 AND STE(T)<=100) THEN INC EAniDelay(T)
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
  IF EX(T)<-50 OR EX(T)>MM.HRES+50 THEN STE(T)=0: EEnergy(T)=-99: EXIT SUB

 ENDIF

 'ENEMY STATUS / ACTION SCRIPTS -----------------------------------------------------

 SELECT CASE STE(T)

  'WALKING --------------------------------------------------------------------------
  CASE 1 TO 40: 
   EAniSpd(T)=2
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
   ESPDX(T)=ESPDX(T)\2: IF EAniDelay(T)>20 OR EEnergy(T)<=0 THEN INC STE(T)
   EXIT SUB
  CASE 54:
   EAniDelay(T)=0: EAniSpd(T)=3: ESPDX(T)=0: STE(T)=100: EAN(T)=50: EXIT SUB ' DIE

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

  'THROW MOLOTOV ---------------------------------------------------------------------
  CASE 70,75: EAN(T)=70: EAniDelay(T)=0: EAniSpd(T)=4: INC STE(T): EXIT SUB
  CASE 76:
   IF EAN(T)>=72 THEN
    STE(T)=77: EAN(T)=72
    SpawnObject(EX(T),RealY(T)-45,209+PL,NUM)
    ESIDE(NUM)=ESIDE(T)
    ESPDX(NUM)=(ESIDE(T)=4)*3-(ESIDE(T)=5)*3
    EAniDelay(T)=0: EAniSpd(T)=200
   ENDIF
   EXIT SUB
  CASE 77:
   EAN(T)=72
   IF EAniSpd(T)>4 THEN
    STE(T)=40: EAniDelay(T)=0: EAniSpd(T)=4
    ESIDE(T)=(ESIDE(T)=4)*5+(ESIDE(T)=5)*4
   ENDIF
   EXIT SUB

  'DON'T DASH / AIR KNIFE ATTACK -----------------------------------------------------
  CASE 80,86: STE(T)=1: EXIT SUB

  'ENEMY IS DEAD ---------------------------------------------------------------------
  CASE 100: EAniSpd(T)=0: IF EAN(T)>60 THEN EAN(T)=50: INC STE(T) ' FLASH BODY AGAIN
  CASE 101: IF EAN(T)>60 THEN EEnergy(T)=-99: STE(T)=0: RealY(T)=999: Exit Sub 'REMOVE DEAD ENEMY

  'RETURN TO THE ORIGINAL STATE IF SOMETHING GOES WRONG ON GAPPLE
  CASE >=171:
   STE(T)=20: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0

  'FOR ALL OTHER CASES, GET UP!
  CASE ELSE: EAN(T)=1: STE(T)=1

 END SELECT 'END ACTION SCRIPTS HOLLY WOOD / EL GADO -------------------------------------------
 
END SUB


'DRAW HOLLY WOOD RED

SUB Draw_HOLLY_WOOD_RED(num,who)

 SELECT CASE num
  'ENERGY AVATAR
  CASE 99 : xa=1155:ya=898:sx=99:sy=16:tx=-54:ty=0
  'STOPPED
  CASE  0 : xa=1045:ya=787:sx=42:sy=53:tx=0:ty=15:xb=1214:yb=599:sbx=45:sby=58:tbx=-16:tby=0
  'WALKING
  CASE  1 : xa=1045:ya=787:sx=42:sy=53:tx=0:ty=15:xb=1051:yb=841:sbx=33:sby=59:tbx=- 8:tby=0
  CASE  2 : xa=1045:ya=787:sx=42:sy=53:tx=0:ty=15:xb=1193:yb=693:sbx=48:sby=58:tbx=-22:tby=0
  CASE  3 : xa=1045:ya=787:sx=42:sy=53:tx=0:ty=15:xb=1051:yb=841:sbx=33:sby=59:tbx=- 8:tby=0
  CASE  4 : xa=1045:ya=787:sx=42:sy=53:tx=0:ty=15:xb=1214:yb=599:sbx=45:sby=58:tbx=-16:tby=0
  CASE  5 : xa=1045:ya=787:sx=42:sy=53:tx=0:ty=15:xb=1095:yb=790:sbx=68:sby=59:tbx=-10:tby=0
  'HURT
  CASE 21 : xa=1167:ya=790:sx=59:sy=78:tx=0:ty=0 'IN THE STOMACH
  CASE 22 : xa=1133:ya=741:sx=51:sy=49:tx=8:ty=8:xb=1051:yb=841:sbx=33:sby=59:tbx=-8:tby=0 'FACE
  'FALLING
  CASE 23 : xa=1047:ya=900:sx=107:sy=62:tx=0:ty=-20 'FALLING DOWN
  CASE 24,50,52,54,56,58,60:
            xa= 924:ya=865:sx=127:sy=22:tx=0:ty=0   'LYING ON THE FLOOR / DEAD
  'THROWING A MOLOTOV
  CASE 70 : xa=1084:ya=849:sx=93:sy=50:tx= 12:ty=7:xb=1051:yb=841:sbx=33:sby=59:tbx=- 8:tby=0
  CASE 71 : xa=1226:ya=769:sx=35:sy=47:tx=-14:ty=7:xb=1214:yb=599:sbx=45:sby=58:tbx=-16:tby=0
  CASE 72 : xa=1133:ya=649:sx=81:sy=44:tx=-36:ty=7:xb=1095:yb=790:sbx=68:sby=59:tbx=-12:tby=0
  'BURNING
  CASE 80 : xa=  0:ya=993:sx=121:sy=72
  CASE 81 : xa=121:ya=993:sx=123:sy=72
  CASE 82 : xa=244:ya=993:sx=121:sy=72

 END SELECT 'END HOLLY WOOD MOLOTOV

END SUB
