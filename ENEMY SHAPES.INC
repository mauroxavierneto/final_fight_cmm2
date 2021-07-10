' --- GENERAL SHAPES / PSEUDO-SPRITES ROUTINES FOR THE ENEMIES ---

' LOAD ENEMY SHAPE NUMBER, ADJUST X,Y AND SIDE, THEN WRITE ON PAGE AND GET COLLISION WITH COLOR
' LAST PARAMETER FORCE SET THE OBJECT TO BE SHOWED OR ONLY TO GET COLLISION
' SHOW = -1 TO READ COLLISION, NO SHAPE IS DISPLAYED
' SHOW =  0 TO WRITE COLLISION AND NO SHAPE IS DISPLAYED
' SHOW =  1 TO SHOW SHAPE ONLY, DON'T WRITE OR READ COLLISION
' SHOW >  1 TO WRITE COLLISION BLOCK TO AN SELECT PAGE
SUB PutEnemy(xs,ys,num,s,Who,pl,SHOW)
 local I,T

',xa,ya,xb,yb,sbx,sby,sx,sy,tx,ty,tbx,tby,xt,yt,xxt,yyt,xp,yp

 'I,T - TEMPORARY VARIABLES
 '
 'FROM THE IMAGE TO BE COPIED / FROM A SECOND IMAGE TO MAKE ONE SHAPE: 
 'xa,xb  - X
 'ya,yb  - Y
 'sx,sbx - WIDTH
 'sy,sby - HEIGHT
 'tx,tbx - X CORRECTION
 'ty,tby - Y CORRECTION
 'xt,yt  - CENTER OF THE SHAPE
 'xp,yp  - ADJUST ATTACK COLLISION 

 xa=-200: xb=-200
 xb=0:yb=0:sbx=0:sby=0:sx=0:sy=0:tx=0:ty=0:tbx=0:tby=0:xp=0:yp=0:xt=0:yt=0:xxt=0:yyt=0

 SELECT CASE Who

  CASE  4 TO  6: Draw_BRED_JAKE_DUG(num,who)
  CASE  7,    8: Draw_J_TWO_P(num,who)
  CASE  9,   10: Draw_AXL_SLASH(num,who)
  CASE 11 TO 12: Draw_HOLLY_WOOD_EL_GADO(num,who,s)
  CASE 13      : Draw_HOLLY_WOOD_RED(num,who)
  CASE 14 TO 16: Draw_BILL_ORIBER_WONG(num,who)
  CASE 17 TO 18: Draw_POISON_ROXY(num,who)
  CASE 80,   81: Draw_DAMND(num,who)

 END SELECT 'END SELECT Who

 'ADJUST SIDE
 IF S=5 OR S=7 THEN TX=-TX: TBX=-TBX: xp=-xp

 'ADJUST VERTICAL FLIP
 IF S>5 AND XB>-99 THEN
  T=XA: XA=XB : XB=T
  T=YA: YA=YB : YB=T
  T=SX: SX=SBX: SBX=T
  T=SY: SY=SBY: SBY=T
  T=TX: TX=TBX: TBX=T
  'T=TY: TY=TBY: TBY=T
  'TY=-TY: TBY=-TBY
 ENDIF

 ' SET THE SUPERIOR PART OF THE SHAPE
 xxt=xs-(sx+TX)\2: yyt=ys-sy+TY-(xb>-99)*(SBY-TBY)

 IF num=50 THEN EEnergy(PL)=-99

 SELECT CASE SHOW
  CASE <=-1: ' SHOW = -1 TO READ COLLISION, NO SHAPE IS DISPLAYED ------------------------

   ' CHECK COLLISION - GET THE PIXELS FROM THE FIRST SHAPE ONLY
   FOR I=0 TO 2
    COLLIDE(I)=0     
    PAGE WRITE 34+I 
    T=PIXEL(xs+xp+sx\2-tx\2,yyt+yp+sy\2): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    T=PIXEL(xs+xp-sx\2-tx\2,yyt+yp+sy\2): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    T=PIXEL(xs+xp-tx\2     ,yyt+yp+8+(WHO>=80)*32): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    'T=PIXEL(xs+xp-tx\2     ,RealY(pl)): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
   NEXT I
   'SET HIT POSITION ALWAYS BASED ON THE FIRST PART OF THE SHAPE (FASTER)
   XTHit=xxt+sx\2: YTHit=yyt+sy\2

  CASE  0: ' SHOW =  0 TO WRITE COLLISION AND NO SHAPE IS DISPLAYED --------------------

   ' INSERT COLLISION BOX WHEN ENEMY IS THROWED
   IF ETR(PL)>0 THEN
    IF DEBUG THEN
     PAGE WRITE 1:BOX xxt-10,yyt-10,sx+sbx+20,sy+sby+20,,&HFF00FF,&HFF00FF
    ENDIF
    PAGE WRITE 34
    ' CHANGE THE COLOUR TO MAKES EASIER TO TELL THE SIDE OF THE ENEMY
    IF ESPDX(PL)<0 THEN
     BOX xxt-10,yyt-10,sx+sbx+20,sy+sby+20,,&HFF00FF,&HFF00FF
    ELSE
     BOX xxt-10,yyt-10,sx+sbx+20,sy+sby+20,,&HFF00BF,&HFF00BF
    ENDIF
    EXIT SUB
   ENDIF

  CASE  1: ' SHOW =  1 TO SHOW SHAPE ONLY, DON'T WRITE OR READ COLLISION ---------------

   PAGE WRITE 1
   'SHADOW
   IF NUM<>99 AND EY(PL)<-1 THEN
    T=sx\((sx<64)+(sx>=64)*2)+EY(PL)\2: IF T<30 THEN T=30
    CIRCLE xxt+sx\2,RealY(PL)-3,T/10,1,5,&H202020,&H202020
   ENDIF

   'TWO SHAPES TO MAKE ONE
   IF xb>-99 THEN
    xt=xs-(sbx+TBX)\2: yt=ys-sby+TBY
    BLIT xb,yb,xt,yt,sbx,sby,FRAMEBUFFER,s
   ENDIF
   BLIT xa,ya,xxt,yyt,sx,sy,FRAMEBUFFER,s

   IF DEBUG THEN
    PIXEL xs+sx\2-tx\2+xp,yyt+yp+sy\2, RGB(255,0,0)
    PIXEL xs-sx\2-tx\2+xp,yyt+yp+sy\2, RGB(255,0,0)
    PIXEL xs     -tx\2+xp,yyt+yp+8+(WHO>=80)*32, RGB(255,0,0)
    'PIXEL xs     -tx\2+xp,RealY(pl), RGB(255,0,0)
   ENDIF

 END SELECT 'END SELECT SHOW -----------------------------------------------------------


 'REMOVE COLLISION IF OUT OF Y AXIS WITH THE ENEMY
 IF SHOW=-1 THEN
  FOR I=1 TO 2
   T=(Grap(I)>0)*10 'EXTEND REAL Y WHEN GRAPPLE
   IF COLLIDE(I)>0 AND (RealY(pl)<RealY(I)-5-T or RealY(pl)>RealY(I)+5+T) THEN COLLIDE(I)=0
  NEXT I
 ENDIF

 'INSERT JESSICA ON THE DAMND HANDS
 IF Who=81 THEN
  SELECT CASE NUM
   CASE 100: PutEnemy(xs+10,ys-24,997,4,99,,1)
   CASE 101: PutEnemy(xs+10,ys-24,997,4,99,,1)
   CASE 102: PutEnemy(xs+ 9,ys-22,999,4,99,,1)
   CASE 103: PutEnemy(xs+ 9,ys-22,999,4,99,,1)
   CASE 104: PutEnemy(xs+ 9,ys-22,999,4,99,,1)
   CASE 105: PutEnemy(xs+10,ys-24,997,4,99,,1)
   CASE 110: PutEnemy(xs+10,ys-20,997,4,99,,1)
   CASE 111: PutEnemy(xs+ 5,ys-20,998,4,99,,1)
  END SELECT
 ENDIF

END SUB

