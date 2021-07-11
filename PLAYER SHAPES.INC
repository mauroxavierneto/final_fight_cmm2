' --- GENERAL SHAPES / PSEUDO-SPRITES ROUTINES FOR THE PLAYERS ---

' LOAD PLAYER SHAPE NUMBER, ADJUST X,Y AND SIDE, THEN WRITE ON PAGE AND GET COLLISION WITH COLOR
' LAST PARAMETER FORCE SET THE OBJECT TO BE SHOWED OR ONLY TO GET COLLISION
' SHOW = -1 TO READ COLLISION, NO SHAPE IS DISPLAYED
' SHOW =  0 TO WRITE COLLISION AND NO SHAPE IS DISPLAYED
' SHOW =  1 TO SHOW SHAPE ONLY, DON'T WRITE OR READ COLLISION
' SHOW >  1 TO WRITE COLLISION BLOCK TO AN SELECT PAGE
SUB PutPlayer(xs,ys,num,s,Who,pl,SHOW)
 local I,T',xa,ya,xb,yb,sbx,sby,sx,sy,p,pb,tx,ty,tbx,tby,xt,yt,xxt,yyt,kx,ky,kt,SD,BX
 'I,T - TEMPORARY VARIABLES
 '
 'FROM THE IMAGE TO BE COPIED / FROM A SECOND IMAGE TO MAKE ONE SHAPE: 
 'xa,xb  - X
 'ya,yb  - Y
 'sx,sbx - WIDTH
 'sy,sby - HEIGHT
 'p,pb   - VIDEO PAGE
 'tx,tbx - X CORRECTION
 'ty,tby - Y CORRECTION
 'xt,yt  - CENTER OF THE SHAPE
 'kx,ky  - SIZE OF THE COLLISION BLOCK
 'SD     - CHANGE SIDE OF THE COLLISION BLOCK
 'BX     - COLOUR OF THE COLLISION BLOCK

 BX=&HFF0000: xa=-200: xb=-200: kx=-200: ky=0: kt=40
 xb=0:yb=0:sbx=0:sby=0:sx=0:sy=0:p=0:pb=0:tx=0:ty=0:tbx=0:tby=0:xt=0:yt=0:xxt=0:yyt=0:SD=0
 xo=0:yo=0: zo=0

 SELECT CASE Who
  CASE 1: 'GUY --------------------------------------------------------------------------
   SELECT CASE num
    'GUY ENERGY AVATAR
    CASE 99 : xa=200:ya=166:sx=49:sy=16:p=25 
    'GUY STOPPED
    CASE 0  : xa=  0:ya=  0:sx=62:sy=86:p=28: xo=-20: yo=-78: zo=8
    'GUY WALKING
    CASE 1 TO 12: ShowGuyWalking(num,PL)
    'GUY PUNCHING 
    CASE 13 : xa=  0:ya=0:sx= 64:sy=90:p=27:tx=-12:        
    CASE 14 : xa= 64:ya=0:sx= 81:sy=90:p=27:tx=-44:     kx=15:ky= 5: kt=50
    'GUY EXTENDED PUNCH
    CASE 15 : xa=145:ya=0:sx= 65:sy=90:p=27:tx=-30:ty=-2 
    CASE 16 : xa=211:ya=0:sx=100:sy=90:p=27:tx=-62:ty=-2:kx=19:ky=15:kt=40
    'GUY ELBOW
    CASE 17 : xa=  0:ya=90:sx=77:sy=81:p=27:tx=-18:ty=2
    CASE 18 : xa= 77:ya=90:sx=88:sy=81:p=27:tx=-18:ty=2:kx=25:ky=10:kt=50
    'GUY COMBO (AND SPECIAL) 
    'SEQUENCE IS 32,33,34,19,36
    CASE 19 : xa=263:ya=145:sx=57:sy=95:p=26:tx=0:ty=-2:kx=35:ky=10:kt=60 'THIS IS FOR COMBO
    'GUY GRAPPLE / KNEELING / THROWING 
    CASE 20 TO 23: ShowGuyGKT(num,PL)   
    'GUY JUMPING AHEAD / VERTICAL
    CASE 24 TO 27: ShowGuyJumping(num,PL,s)
    'GUY VERTICAL AIR KICK / AIR KNEE
    CASE 27 TO 31,37,44,45: ShowGuyVKick(num,PL)
    'GUY SPECIAL (AND COMBO)
    CASE 32 TO 36: ShowGuySpecial(num,PL)
    'GUY HURT / ON THE FLOOR / STANDING UP
    CASE 38 TO 43: ShowGuyHurtStand(num,PL)
    'GUY USING WEAPON
    CASE 70 : xa=165:ya=92:sx=56:sy=79:p=27:tx= -8:ty=0: xo=-22:yo=-72:zo=7
    CASE 71 : xa=221:ya=93:sx=87:sy=78:p=27:tx=-46:ty=0: xo=81:yo=-38:zo=3:
     SELECT CASE WEAPON(PL)
      CASE KATANA: kx=57: ky=-10: kt=80
      CASE   PIPE: kx=61: ky=-10: kt=80: inc yo
     END SELECT
    'GUY BURNING
    CASE 80 TO 82: ShowGuyBurning(num,PL)

   END SELECT 

  CASE 2: 'CODY -------------------------------------------------------------------------
   SELECT CASE num
    'CODY ENERGY AVATAR
    CASE 99 : xa=179:ya= 86:sx=49:sy=16:p=25
    'CODY STOPPED
    CASE 0  : xa=  0:ya=  0:sx=54:sy=93:p=27: xo=-21: yo=-85: zo=8:
              IF WEAPON(PL)=PIPE THEN inc xo,3: inc yo,2
    'CODY WALKING - INSERT BOX TO GRAPPLE ENEMIES
    CASE 1 TO 12: ShowCodyWalking(num,PL)
    'CODY PUNCHING 
    CASE 13 TO 16: ShowCodyPunching(num,PL)
    'CODY UPPERCUT
    CASE 17 TO 19: ShowCodyUppercut(num,PL)
    'CODY GRAPPLE / KNEELING / THROWING 
    CASE 20 TO 23: ShowCodyGKT(num,PL)
    'CODY JUMPING AHEAD / VERTICAL
    CASE 24 TO 27: ShowCodyJumping(num,PL)
    'CODY VERTICAL AIR KICK / AIR KNEE
    CASE 28 TO 31: ShowCodyVKick(num,PL)
    'CODY SPECIAL / AIR KICK
    CASE 32 TO 37: ShowCodySpecial(num,PL)
    'CODY HURT / ON THE FLOOR / STANDING UP
    CASE 38 TO 43: ShowCodyHurtStand(num,PL)
    'CODY USING WEAPON
    CASE 70 : xa=  0:ya=207:sx=  35:sy= 33:tx= -20: ty  =0: p=27:
              xb=202:yb= 40:sbx= 83:sby=48:tbx=-34: xo=22-(s=5)*82:yo=-26:zo=7
    CASE 71 : xa= 35:ya=194:sx=  82:sy= 46:tx= -76: ty =17: p=27:
              xb=  0:yb=145:sbx= 68:sby=48:tbx=-24: xo=127-(s=5)*68:yo=18:zo=3
     SELECT CASE WEAPON(PL)
      CASE KATANA: kx=53: ky=-10: kt=80
      CASE  KNIFE: kx=20: ky=-10: kt=80
      CASE   PIPE: kx=58: ky=-10: kt=80: inc xo,-1: inc yo,-1
     END SELECT
    'CODY BURNING
    CASE 80 TO 82: ShowCodyBurning(num,PL)
   END SELECT 

  CASE 3: 'HAGGAR -----------------------------------------------------------------------
   SELECT CASE num
    'HAGGAR ENERGY AVATAR
    CASE 99 : xa=171:ya=224:sx=49:sy=16:p=25

    'HAGGAR STOPPED
    CASE  0 : xb= 81:yb=  0:sbx=51:sby=60
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-17:ty=16: xo=4-(s=5)*50:yo=-17:zo=1
     IF WEAPON(PL)>KATANA THEN INC xo,2-(s=5): INC yo: IF WEAPON(PL)=KNIFE THEN zo=20: inc yo,21
    'HAGGAR WALKING - INSERT BOX TO GRAPPLE ENEMIES
    CASE 1 TO 12:
     ShowHaggarWalking(num,PL,s)
     IF WEAPON(PL)>KATANA THEN INC xo,1-(s=5): INC yo: IF WEAPON(PL)=KNIFE THEN zo=20: inc yo,21
    'HAGGAR PUNCHING 
    CASE 13 TO 19: ShowHaggarPunching(num,PL)
    'HAGGAR GRAPPLE
    CASE 20 : xb= 81:yb=  0:sbx=51:sby=60:pb=28
              xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-44:ty= 9
    'HAGGAR HEAD BANG
    CASE 21 : xb= 81:yb=  0:sbx=51:sby=60:pb=28
              xa=  0:ya=200:sx= 54:sy= 40:p =25:tx=-17:ty=16:BX=&HFF0000:kx=25:ky=-25:kt=70
    'HAGGAR SUPLEX
    CASE 22 : xa=102:ya=141:sx= 69:sy= 99:p =25:tx= 2
    CASE 23 : xa=224:ya=192:sx= 96:sy= 49:p =25:tx= 0': ETR(GrapE(PL))=1
    'HAGGAR JUMPING AHEAD / VERTICAL
    CASE 24 TO 27: ShowHaggarJumping(num,PL)
    'HAGGAR VERTICAL AIR KICK / SMASH
    CASE 28 : xa=154:ya= 68:sx=123:sy=61:p=25:tx=-50:ty=-30:kx=38:ky=15:kt=50:xo=-12:yo=-41:zo=2
    CASE 29 : xa=  0:ya=100:sx=128:sy=52:p=25:tx=-20:ty=-24:kx=0:ky=-20:kt=80:xo= 57:yo=-67:zo=4
    'HAGGAR PILE DRIVER
    'SEQUENCE IS 30,31,26,32,26,24
    CASE 30 TO 32: ShowHaggarPileDriver(num,PL)
    'HAGGAR SPECIAL 
    CASE 33 TO 37: ShowHaggarSpecial(num,PL)
    'HAGGAR HURT / ON THE FLOOR / STANDING UP
    CASE 38 TO 43: ShowHaggarHurtStand(num,PL)
    'HAGGAR WALKING WITH GRAPPLED ENEMY
    CASE 51 TO 62: ShowHaggarWGrappled(num,PL)
    'HAGGAR USING WEAPON
    CASE 70 : xa=  0:ya= 86:sx= 71:sy=89:p=27:tx=-18: xo= 1:yo=-83:zo=7:
              IF WEAPON(PL)=PIPE THEN zo=9: inc xo,-21+(s=5)*5: inc yo
    CASE 71 : xa= 71:ya= 86:sx=111:sy=81:p=27:tx=-48: xo=98:yo=-47:zo=3:
     SELECT CASE WEAPON(PL)
      CASE KATANA: kx=70: ky=-10: kt=80
      CASE   PIPE: kx=74: ky=-10: kt=80: inc xo,-1: inc yo,-1
     END SELECT
    'HAGGAR BURNING
    CASE 80 TO 82: ShowHaggarBurning(num,PL)
   END SELECT 

 END SELECT 'END SELECT Who

 IF WEAPON(PL)>0 THEN
  IF WEAPON(PL)=PIPE THEN
   SELECT CASE zo
    CASE 1: inc yo,-8
    CASE 2: inc xo,3: inc yo,-2
    CASE 3: inc xo,4
    CASE 4: inc yo,8
    CASE 7: inc xo,-5
    CASE 8: inc xo,2: inc yo,-9
    CASE 9: inc yo
   END SELECT
  ENDIF
  IF WEAPON(PL)=KNIFE THEN
   SELECT CASE zo
    CASE 1: inc yo,13
    CASE 2: inc xo,-9: inc yo,5
    CASE 3: inc xo,-7
    CASE 4: inc xo,-5: inc yo,5
    CASE 7: inc xo,5: inc yo
    CASE 8: inc xo,7: inc yo,5
   END SELECT
  ENDIF
 ENDIF

 'ADJUST SIDE
 if s=4 OR s=6 THEN SD=1
 if s=5 OR s=7 THEN TX=-TX: TBX=-TBX: xo=-xo: SD=-1

 ' FIX VIDEO PAGE WITH THE PLAYER NUMBER
 IF PL>0 THEN INC P,(PL-1)*4: IF PB>0 THEN INC PB,(PL-1)*4

 ' SET COORDINATES AS THE INFERIOR PART OF THE SHAPE AND
 ' MAKE A PERFECT FLIP WITHOUT TREMBLING WITH FLOATING POINT NUMBERS
 IF SD=-1 THEN xxt=xs-CINT((sx+TX+tbx)/2) ELSE xxt=xs-(sx+TX+tbx)\2
 yyt=ys-sy+TY-(xb>-99)*(SBY-TBY)
 
 ' SET HIT POSITION ALWAYS ON THE CENTER
 XTHit=xxt+sx\2: YTHit=yyt+sy\3

 SELECT CASE SHOW
  CASE -1: ' SET HIT POSITION --------------------------------------
   XH(pl)=XTHit: YH(pl)=YTHit
   Exit Sub

  CASE 0: ' WRITE COLLISION BOX ------------------------------------
   PAGE WRITE 34  'COLLISION BOX TO BE ATTACKED ONLY WHEN NOT USING ANY SPECIAL OR THROWING
   IF SPECIAL(PL)=0 AND AN(PL)<>22 AND AN(PL)<>23 THEN 
    BOX xxt,yyt,sx,sy+sby\2,,&HFFFFFF,&HFFFFFF
    IF DEBUG THEN PAGE WRITE 1: BOX xxt,yyt,sx,sy+sby\2,,&HFFFFFF,&HFFFFFF
   ENDIF
   IF kx>-99 AND num<99 THEN
    PAGE WRITE 34+PL
    'COLLISION BOX TO ATTACK
    BOX xxt+sx\2+kx*SD-kt\2,yyt+ky,kt,kt,,BX,BX
    IF DEBUG THEN PAGE WRITE 1: BOX xxt+sx\2+kx*SD-kt\2,yyt+ky,kt,kt,,BX,BX
   ENDIF
   'COLLISION BOX TO GET ITEMS ON THE FLOOR
   IF AN(PL)<=12 THEN
    PAGE WRITE 34+PL
    BOX xxt+sx\2-16,ys-16,32,22,,&H00FF00,&H00FF00
    PAGE WRITE 1
    IF DEBUG THEN BOX xxt+sx\2-16,ys-16,32,22,,&H00FF00,&H00FF00
   ENDIF

  CASE  1: ' SHOW SHAPE --------------------------------------------
   PAGE WRITE 1
   'SHADOW
   IF NUM<>99 AND Y(PL)<-1 THEN
    T=sx\((sx<64)+(sx>=64)*2)+Y(PL)\2: IF T<30 THEN T=30
    CIRCLE xxt+sx\2,RealY(PL)-3,T/10,1,5,&H202020,&H202020
   ENDIF

   'TWO SHAPES TO MAKE ONE
   IF xb>-99 THEN
    'MAKE A PERFECT FLIP WITHOUT TREMBLING WITH NON INTEGER NUMBERS
    IF SD=-1 THEN xt=xs-CINT((sbx+TBX)/2) ELSE xt=xs-(sbx+TBX)\2
    yt=ys-sby+TBY: if pb=0 then pb=p
    IF pb<0 THEN BLIT xb,yb,xt,yt,sbx,sby,framebuffer,s ELSE BLIT xb,yb,xt,yt,sbx,sby,pb,s
   ENDIF
   IF p<0 THEN BLIT xa,ya,xxt,yyt,sx,sy,framebuffer,s ELSE BLIT xa,ya,xxt,yyt,sx,sy,p,s

   IF zo>0 AND WEAPON(PL)>0 THEN t=s: PutObject(xt+xo,yt+yo,WEAPON(PL)+130+zo,t,1)

 END SELECT

END SUB


'GUY WALKING - INSERT BOX TO GRAPPLE ENEMIES
SUB ShowGuyWalking(num,PL)
 SELECT CASE Num
  CASE 1  : xa= 62:ya=  0:sx=55:sy=87:p=28:tx= 4:ty=0:BX=&HFFFF00:
            kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
            xo=26:yo=-50:zo=2
  CASE 2  : xa=117:ya=  0:sx=55:sy=87:p=28:tx= 8:ty=0:BX=&HFFFF00:
            kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
            xo=24:yo=-49:zo=2
  CASE 3  : xa=172:ya=  0:sx=46:sy=87:p=28:tx=16:ty=0:BX=&HFFFF00:
            kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
            xo=21:yo=-48:zo=2
  CASE 4  : xa=218:ya=  0:sx=29:sy=87:p=28:tx=14:ty=0:BX=&HFFFF00:
            kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
            xo=19:yo=-38:zo=3
  CASE 5  : xa=247:ya=  0:sx=29:sy=87:p=28:tx= 8:ty=0:BX=&HFFFF00:
            kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20 
            xo=16:yo=-39:zo=3
  CASE 6  : xa=276:ya=  0:sx=41:sy=87:p=28:tx=12:ty=0:BX=&HFFFF00:
            kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
            xo=12:yo=-39:zo=3
  CASE 7  : xa=  0:ya= 88:sx=55:sy=87:p=28:tx= 6:ty=0:BX=&HFFFF00:
            kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
            xo=6:yo=-38:zo=3
  CASE 8  : xa= 55:ya= 88:sx=55:sy=87:p=28:tx=10:ty=0:BX=&HFFFF00:
            kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
            xo=12:yo=-39:zo=3
  CASE 9  : xa=110:ya= 88:sx=43:sy=87:p=28:tx=14:ty=0:BX=&HFFFF00:
            kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
            xo=17:yo=-39:zo=3
  CASE 10 : xa=153:ya= 88:sx=28:sy=87:p=28:tx=10:ty=0:BX=&HFFFF00:
            kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
            xo=20:yo=-38:zo=3
  CASE 11 : xa=181:ya= 88:sx=28:sy=87:p=28:tx=10:ty=0:BX=&HFFFF00:
            kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
            xo=19:yo=-49:zo=2
  CASE 12 : xa=209:ya= 88:sx=40:sy=87:p=28:tx=12:ty=0:BX=&HFFFF00:
            kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
            xo=24:yo=-51:zo=2
 END SELECT
END SUB

'GUY GRAPPLE / KNEELING / THROWING 
SUB ShowGuyGKT(num,PL)
 SELECT CASE Num
  CASE 20 : xa=  0:ya=154:sx=71:sy=86:p=25:tx=10
  CASE 21 : xa= 71:ya=157:sx=47:sy=82:p=25:tx= 2:BX=&HFF0000:kx=10:ky=0: kt=50
  CASE 22 : xa=118:ya=173:sx=67:sy=67:p=25:tx= 4:BX=&HFF0000:kx=10:ky=0: kt=50
  CASE 23 : xa=185:ya=193:sx=82:sy=47:p=25:tx= 0
 END SELECT
END SUB

'GUY JUMPING AHEAD / VERTICAL
SUB ShowGuyJumping(num,PL,s)
 SELECT CASE Num
  CASE 24 : xa=201:ya=50:sx=75:sy= 56:p=25:     ty=-30: xo= 27:yo=-65:zo=2: if s>5 then inc yo,15
  CASE 25 : xa=276:ya= 0:sx=44:sy= 67:p=25:     ty=-30: xo= 13:yo=-79:zo=1: if s>5 then inc yo,40
  CASE 26 : xa=  0:ya= 0:sx=57:sy= 78:p=25:tx=0:ty= 0:  xo=-19:yo=-74:zo=8
  CASE 27 : xa= 57:ya= 0:sx=46:sy= 93:p=25:tx=2:ty=-9:  xo=- 9:yo=-97:zo=8
 END SELECT
END SUB

'GUY VERTICAL AIR KICK / AIR KNEE
SUB ShowGuyVKick(num,PL)
 SELECT CASE Num
  CASE 28 : xa=103:ya=  0:sx= 59:sy=86:p=25:tx=  4:ty=-18: xo=- 2:yo=-84:zo=1
  CASE 29 : xa=162:ya=  0:sx= 63:sy=84:p=25:tx=  2:ty=-24: kx=10:ky=50: xo=-23:yo=-81:zo=8
  CASE 30 : xa= 86:ya= 86:sx= 50:sy=69:p=25:tx=  2:ty=-24: xo=-11:yo=-80:zo=1
  CASE 31 : xa=278:ya=152:sx= 42:sy=88:p=25:       ty= -9: kx= 7:ky=35        'AIR KNEE
  CASE 37 : xa=136:ya=106:sx=103:sy=52:p=25:tx=-40:ty=-40: kx=45:ky=40:xo=-33:yo=-63:zo=7 'FULL AIR KICK
  CASE 44 : xa=  0:ya= 93:sx= 86:sy=58:p=25:tx=  0:ty=-30: xo=-29:yo=-80:zo=7 'AIR LEAP
  CASE 45 : xa=276:ya= 68:sx= 44:sy=70:p=25:xo=- 7:yo=-57: zo=1               'WALL JUMP
 END SELECT
END SUB

'GUY SPECIAL (AND COMBO)
SUB ShowGuySpecial(num,PL)
 SELECT CASE Num
  CASE 32 : xa=  0:ya=0:sx=61:sy=77:p=26:tx= 32-10:ty=-0
  CASE 33 : xa= 61:ya=0:sx=52:sy=78:p=26:tx=  6-10:ty=-0
  CASE 34 : xa=113:ya=0:sx=49:sy=87:p=26:tx=  6-10:ty=-4
  CASE 35 : xa=162:ya=0:sx=80:sy=93:p=26:tx=-25-10:ty= 0: kx=30:ky=30:kt=50  'ROTATED FULL KICK
  CASE 36 : xa=242:ya=0:sx=48:sy=88:p=26:tx=  0-10:ty=-2
 END SELECT
END SUB

'GUY HURT / ON THE FLOOR / STANDING UP
SUB ShowGuyHurtStand(num,PL)
 SELECT CASE Num
  CASE 38 : xa= 56:ya= 78:sx= 43:sy=80:p=26:tx=-4        'IN THE STOMACH
  CASE 39 : xa=  0:ya= 77:sx= 56:sy=88:p=26:tx= 6        'IN THE FACE
  CASE 40 : xa=152:ya=173:sx= 99:sy=57:p=26:tx= 0:ty=-12 'FALLING DOWN
  CASE 41 : xa= 99:ya= 93:sx=122:sy=27:p=26:tx= 0        'LYING ON THE FLOOR
  CASE 42 : xa= 99:ya=120:sx= 81:sy=40:p=26:tx= 0        'GET UP
  CASE 43 : xa=  0:ya=181:sx= 48:sy=59:p=26:tx=-2        'ALMOST GET UP (GET OBJECT)
 END SELECT
END SUB

'GUY BURNING
SUB ShowGuyBurning(num,PL)
 SELECT CASE num
  CASE 80 : xa=  0:ya=993:sx=121:sy=72:p=-1
  CASE 81 : xa=121:ya=993:sx=123:sy=72:p=-1
  CASE 82 : xa=244:ya=993:sx=121:sy=72:p=-1
 END SELECT
END SUB

'CODY WALKING - INSERT BOX TO GRAPPLE ENEMIES
SUB ShowCodyWalking(num,PL)
 SELECT CASE num
  CASE 1  : xa= 39:ya=104:sx=51:sy=95:p=28:tx=12:ty= 1:BX=&HFFFF00:
            kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*20
            xo=24: yo=-57: zo=2
  CASE 2  : xa= 90:ya=104:sx=62:sy=95:p=28:tx= 7:ty= 1:BX=&HFFFF00:
            kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*20
            xo=29: yo=-58: zo=2
  CASE 3  : xa=152:ya=104:sx=62:sy=95:p=28:tx= 7:ty= 1:BX=&HFFFF00:
            kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*20
            xo=27: yo=-55: zo=2
  CASE 4  : xa=214:ya=103:sx=51:sy=94:p=28:tx=16:ty= 0:BX=&HFFFF00:
            kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*20
            xo=28: yo=-41: zo=3
  CASE 5  : xa=265:ya=102:sx=32:sy=95:p=28:tx= 9:ty=-1:BX=&HFFFF00:
            kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*20
            xo=21: yo=-43: zo=3
  CASE 6  : xa= 0 :ya=  2:sx=35:sy=94:p=28:tx= 6:ty= 0:BX=&HFFFF00:
            kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*20
            xo=15: yo=-44: zo=3
  CASE 7  : xa= 35:ya=  3:sx=48:sy=93:p=28:tx= 9      :BX=&HFFFF00:
            kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*20
            xo= 8: yo=-42: zo=3
  CASE 8  : xa= 83:ya=  3:sx=62:sy=93:p=28:tx= 7:ty= 0:BX=&HFFFF00:
            kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*20
            xo= 4: yo=-41: zo=3
  CASE 9  : xa=145:ya=  2:sx=63:sy=94:p=28:tx= 8:ty= 0:BX=&HFFFF00:
            kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*20
            xo= 8: yo=-53: zo=2
  CASE 10 : xa=208:ya=  2:sx=51:sy=94:p=28:tx=12      :BX=&HFFFF00:
            kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*20
            xo=13: yo=-53: zo=2
  CASE 11 : xa=259:ya=  1:sx=32:sy=95:p=28:tx= 9:ty=-1:BX=&HFFFF00:
            kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*20
            xo=18: yo=-54: zo=2
  CASE 12 : xa=  0:ya=103:sx=38:sy=94:p=28:tx= 3:ty= 0:BX=&HFFFF00:
            kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*20
            xo=23: yo=-54: zo=2
 END SELECT
END SUB


'CODY PUNCHING 
SUB ShowCodyPunching(num,PL)
 SELECT CASE num
  CASE 13 : xa= 54:ya=  2:sx= 64:sy=90:p=27:tx=- 8        
  CASE 14 : xa=118:ya=  2:sx= 84:sy=90:p=27:tx=-28:kx=19:ky= 5:kt=50
  CASE 15 : xa=202:ya=  7:sx= 83:sy=81:p=27:tx=-34 
  CASE 16 : xa=  0:ya=116:sx=112:sy=77:p=27:tx=-48:kx=19:ky=10:kt=50
 END SELECT
END SUB

'CODY UPPERCUT
SUB ShowCodyUppercut(num,PL)
 SELECT CASE num
  CASE 17 : xa=112:ya=123:sx=76:sy= 69:p=27:tx=-18
  CASE 18 : xa=188:ya=103:sx=77:sy= 91:p=27:tx=-18:kx=25:ky=10:kt=60:Combo(PL)=3
  CASE 19 : xa=266:ya= 89:sx=55:sy=111:p=27:tx=- 4:                  Combo(PL)=0
 END SELECT
END SUB

'CODY GRAPPLE / KNEELING / THROWING 
SUB ShowCodyGKT(num,PL)
 SELECT CASE num
  CASE 20 : xa=  0:ya= 2:sx=77:sy=86:p=25:tx=10
  CASE 21 : xa= 77:ya= 8:sx=49:sy=77:p=25:tx= 2:BX=&HFF0000:kx=15:ky=0: kt=50
  CASE 22 : xa=126:ya= 4:sx=63:sy=76:p=25:tx= 4:BX=&HFF0000:kx=15:ky=0: kt=50
  CASE 23 : xa=189:ya=16:sx=59:sy=64:p=25:tx= 0
 END SELECT
END SUB

'CODY JUMPING AHEAD / VERTICAL
SUB ShowCodyJumping(num,PL)
 SELECT CASE num
  CASE 24 : xa=259:ya= 0:sx=61:sy= 65:p=25:     ty=-30:xo= 23:yo=- 49:zo=3: if s>5 then inc yo,15
  CASE 25 : xa=255:ya=65:sx=65:sy= 61:p=25:     ty=-30:xo= 11:yo=- 79:zo=1: if s>5 then inc yo,40
  CASE 26 : xa=  0:ya=98:sx=53:sy= 84:p=25:tx=0:ty=  0:xo=-21:yo=- 76:zo=8
  CASE 27 : xa= 53:ya=92:sx=42:sy=108:p=25:tx=2:ty= -6:xo=-11:yo=-117:zo=8
 END SELECT
END SUB

'CODY VERTICAL AIR KICK / AIR KNEE
SUB ShowCodyVKick(num,PL)
 SELECT CASE num
  CASE 28 : xa= 96:ya=113:sx=61:sy=87:p=25:tx=2:ty=-18:kx=10:ky=50:xo= 8:yo=-68:zo=2
  CASE 29 : xa=157:ya=113:sx=54:sy=87:p=25:tx=4:ty=-24:xo= 2:yo=-93:zo=1
  CASE 30 : xa=211:ya=123:sx=52:sy=76:p=25:tx=2:ty=-24:xo=12:yo=-89:zo=2
  CASE 31 : xa=263:ya=129:sx=57:sy=63:p=25:     ty=-30:kx= 7:ky=35:xo=11:yo=-41:zo=3
 END SELECT
END SUB

'CODY SPECIAL / AIR KICK
SUB ShowCodySpecial(num,PL)
 SELECT CASE num
  CASE 32 : xa=  0:ya=  0:sx= 75:sy=81:p=26:tx=  5:ty= -8
  CASE 33 : xa= 75:ya=  0:sx= 60:sy=85:p=26:tx=  8:ty= -6:kx= 20:ky=40
  CASE 34 : xa=135:ya=  0:sx=120:sy=59:p=26:tx=-40:ty=-30:kx= 45:ky=40:xo=-48:yo=-82:zo=8'FULL AIR KICK
  CASE 35 : xa=118:ya=105:sx= 45:sy=70:p=26:tx=  0:ty=-24:kx=  0:ky=40 
  CASE 36 : xa=226:ya=132:sx= 94:sy=68:p=26:tx= 30:ty=-20:kx=-30:ky=40
  CASE 37 : xa=  0:ya= 82:sx= 61:sy=61:p=26:tx=  0:ty=-30:kx=-20:ky=40
 END SELECT
END SUB

'CODY HURT / ON THE FLOOR / STANDING UP
SUB ShowCodyHurtStand(num,PL)
 SELECT CASE num
  CASE 38 : xa=170:ya=101:sx= 55:sy=84:p=26:tx=-4        'IN THE STOMACH
  CASE 39 : xa=260:ya=  0:sx= 60:sy=96:p=26:tx= 6        'IN THE FACE
  CASE 40 : xa=  0:ya=147:sx= 95:sy=53:p=26:tx= 0:ty=-12 'FALLING DOWN
  CASE 41 : xa=136:ya= 59:sx=119:sy=37:p=26:tx= 0        'LYING ON THE FLOOR
  CASE 42 : xa=227:ya= 96:sx= 93:sy=35:p=26:tx= 0        'GET UP
  CASE 43 : xa= 63:ya= 86:sx= 51:sy=58:p=26:tx=-2        'ALMOST GET UP (GET OBJECT)
 END SELECT
END SUB

'CODY BURNING
SUB ShowCodyBurning(num,PL)
 SELECT CASE num
  CASE 80 : xa=  0:ya=993:sx=121:sy=72:p=-1
  CASE 81 : xa=121:ya=993:sx=123:sy=72:p=-1
  CASE 82 : xa=244:ya=993:sx=121:sy=72:p=-1
 END SELECT
END SUB

'HAGGAR WALKING - INSERT BOX TO GRAPPLE ENEMIES
SUB ShowHaggarWalking(num,PL,S)
 SELECT CASE num
  CASE  1 : xb=132:yb=  0:sbx=36:sby=68:tbx= 2: xo= 4-(s=5)*35:yo=-17:zo=1
            xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-28:ty=16
            BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
  CASE  2 : xb=168:yb=  0:sbx=50:sby=67:tbx=-4: xo= 8-(s=5)*49:yo=-17:zo=1
            xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-22:ty=16
            BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
  CASE  3 : xb=218:yb=  1:sbx=54:sby=66:tbx=-4: xo=10-(s=5)*53:yo=-17:zo=1
            xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-23:ty=16
            BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
  CASE  4 : xb=  0:yb= 49:sbx=58:sby=65:tbx=-6: xo=11-(s=5)*57:yo=-17:zo=1
            xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-21:ty=16
            BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
  CASE  5 : xb= 58:yb= 60:sbx=58:sby=65:tbx=-4: xo=12-(s=5)*57:yo=-17:zo=1
            xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-22:ty=16
            BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
  CASE  6 : xb=116:yb= 67:sbx=47:sby=64:tbx=14: xo=15-(s=5)*46:yo=-17:zo=1
            xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-40:ty=16
            BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
  CASE  7 : xb=163:yb= 67:sbx=37:sby=66:tbx= 4: xo= 5-(s=5)*36:yo=-17:zo=1
            xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-30:ty=16
            BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
  CASE  8 : xb=200:yb= 67:sbx=37:sby=65:tbx=-4: xo= 1-(s=5)*36:yo=-17:zo=1
            xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-22:ty=16
            BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
  CASE  9 : xb=237:yb= 67:sbx=45:sby=66:tbx= 0: xo= 7-(s=5)*44:yo=-17:zo=1
            xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-26:ty=16
            BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
  CASE 10 : xb=  0:yb=114:sbx=56:sby=66:tbx=-2: xo=12-(s=5)*55:yo=-17:zo=1
            xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-24:ty=16
            BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
  CASE 11 : xb= 56:yb=125:sbx=51:sby=66:tbx= 4: xo=12-(s=5)*50:yo=-17:zo=1
            xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-31:ty=16
            BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
  CASE 12 : xb=107:yb=131:sbx=40:sby=66:tbx= 6: xo= 8-(s=5)*39:yo=-17:zo=1
            xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-33:ty=16
            BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
 END SELECT
END SUB


'HAGGAR PUNCHING 
SUB ShowHaggarPunching(num,PL)
 SELECT CASE num
  CASE 13 : xa=  0:ya=  0:sx= 57:sy=86:p=27:tx=  6
  CASE 14 : xa= 57:ya=  0:sx= 71:sy=86:p=27:tx=- 8
  CASE 15 : xa=128:ya=  0:sx=113:sy=84:p=27:tx=-52:kx=25:ky= 5:kt=60
  CASE 16 : xa=241:ya=  0:sx= 54:sy=99:p=27:tx=- 4
  CASE 17 : xa=  0:ya= 86:sx= 71:sy=89:p=27:tx=-18
  CASE 18 : xa= 71:ya= 86:sx=111:sy=81:p=27:tx=-48:kx=25:ky=10:kt=60:Combo(PL)=2
  CASE 19 : xa=182:ya= 99:sx= 71:sy=87:p=27:tx=-30:                  Combo(PL)=0
 END SELECT
END SUB


'HAGGAR JUMPING AHEAD / VERTICAL
SUB ShowHaggarJumping(num,PL)
 SELECT CASE num
  CASE 24 : xa=  0:ya=  0:sx=63:sy= 85:p=25:             xo=-23:yo=-57:zo=1
  CASE 25 : xa= 63:ya=  0:sx=52:sy=100:p=25:             xo= 24:yo=-83:zo=2
  CASE 26 : xa=116:ya=  0:sx=55:sy= 78:p=25:     ty=-16: xo=- 8:yo=-68:zo=1
  CASE 27 : xa=171:ya=  0:sx=85:sy= 68:p=25:tx=2:ty= -6: xo=-15:yo=-32:zo=2
 END SELECT
END SUB


'HAGGAR PILE DRIVER
'SEQUENCE IS 30,31,26,32,26,24
SUB ShowHaggarPileDriver(num,PL)
 SELECT CASE num
  CASE 30 : xb=147:yb=133:sbx=56:sby=49:pb=28
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-44:ty=9
  CASE 31 : xb= 65:yb= 33:sbx=30:sby=67
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-46:ty=10
  CASE 32 : xa=232:ya=139:sx= 88:sy= 53:p =25:tx=-44:ty=-40:kx=0:ky=0:kt=70
 END SELECT
END SUB

'HAGGAR SPECIAL 
SUB ShowHaggarSpecial(num,PL)
 SELECT CASE num
  CASE 33 : xa=  0:ya=  0:sx= 67:sy=121:p=26:tx=  5:kx=  0:ky=10:kt=60
  CASE 34 : xa= 67:ya=  0:sx= 56:sy= 95:p=26:tx=- 5:kx=-10:ky=10:kt=60
  CASE 35 : xa=123:ya=  0:sx=102:sy= 93:p=26:tx=-50:kx= 20:ky=10:kt=60
  CASE 36 : xa=  0:ya=121:sx= 46:sy= 93:p=26:tx=  0:kx=-10:ky=10:kt=60
  CASE 37 : xa=108:ya= 95:sx=120:sy= 93:p=26:tx=  0:kx=-30:ky=10:kt=60
 END SELECT
END SUB

'HAGGAR HURT / ON THE FLOOR / STANDING UP
SUB ShowHaggarHurtStand(num,PL)
 SELECT CASE num
  CASE 38 : xa=259:ya=  0:sx= 61:sy=77:p=26:tx=-4        'IN THE STOMACH
  CASE 39 : xb= 81:yb=  0:sbx=51:sby=60:pb=28            'IN THE FACE
            xa= 46:ya=168:sx= 74:sy= 46:p =26:tx=-26:ty=10
  CASE 40 : xa=228:ya=148:sx= 92:sy=92:p=26:tx= 0        'FALLING DOWN
  CASE 41 : xa= 12:ya=214:sx=133:sy=26:p=26:tx= 0        'LYING ON THE FLOOR
  CASE 42 : xa=145:ya=193:sx= 83:sy=47:p=26:tx= 0        'GET UP
  CASE 43 : xa=257:ya= 78:sx= 63:sy=69:p=26:tx=-2        'ALMOST GET UP (GET OBJECT)
 END SELECT
END SUB

'HAGGAR WALKING WITH GRAPPLED ENEMY
SUB ShowHaggarWGrappled(num,PL)
 SELECT CASE num
  CASE 51 : xb=132:yb=  0:sbx=36:sby=68:tbx=2:pb=28
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-28-27:ty= 9
  CASE 52 : xb=168:yb=  0:sbx=50:sby=67:tbx=-4:pb=28 
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-22-27:ty= 9
  CASE 53 : xb=218:yb=  1:sbx=54:sby=66:tbx=-4:pb=28
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-23-27:ty= 9
  CASE 54 : xb=  0:yb= 49:sbx=58:sby=65:tbx=-6:pb=28
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-21-27:ty= 9
  CASE 55 : xb= 58:yb= 60:sbx=58:sby=65:tbx=-4:pb=28
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-22-27:ty= 9
  CASE 56 : xb=116:yb= 67:sbx=47:sby=64:tbx=14:pb=28
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-40-27:ty= 9
  CASE 57 : xb=163:yb= 67:sbx=37:sby=66:tbx=4:pb=28
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-30-27:ty= 9
  CASE 58 : xb=200:yb= 67:sbx=37:sby=65:tbx=-4:pb=28
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-22-27:ty= 9
  CASE 59 : xb=237:yb= 67:sbx=45:sby=66:tbx=0:pb=28
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-26-27:ty= 9
  CASE 60 : xb=  0:yb=114:sbx=56:sby=66:tbx=-2:pb=28
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-24-27:ty= 9
  CASE 61 : xb= 56:yb=125:sbx=51:sby=66:tbx=4:pb=28
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-31-27:ty= 9
  CASE 62 : xb=107:yb=131:sbx=40:sby=66:tbx=6:pb=28
            xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-33-27:ty= 9
 END SELECT
END SUB

'HAGGAR BURNING
SUB ShowHaggarBurning(num,PL)
 SELECT CASE num
  CASE 80 : xa=  0:ya=993:sx=121:sy=72:p=-1
  CASE 81 : xa=121:ya=993:sx=123:sy=72:p=-1
  CASE 82 : xa=244:ya=993:sx=121:sy=72:p=-1
 END SELECT
END SUB


