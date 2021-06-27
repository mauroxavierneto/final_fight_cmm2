' --- GENERAL SHAPES / PSEUDO-SPRITES ROUTINES ---

' USED VIDEO PAGES:
'
'     0 - VISIBLE VIDEO PAGE
'     1 - MAIN FRAME BUFFER
'  2-20 - STAGE AND ANIMATIONS
' 21-24 - TEMPORARY THINGS
' 25-28 - PLAYER 1 SHAPES
' 29-32 - PLAYER 2 SHAPES
'    34 - PLAYERS COLLISION (FOR ENEMY ATTACKS)
'    35 - PLAYER 1 ATTACKS
'    36 - PLAYER 2 ATTACKS
'    37 - FONTS
'    38 - GENERAL OBJECTS
'    39 - GENERAL OBJECTS 2

' LOAD GENERAL ASSETS
SUB LoadAssets
 PAGE WRITE 37: CLS: LOAD PNG ".\IMAGES\OBJECTS\FONTS.PNG",,,1
 PAGE WRITE 38: CLS: LOAD PNG ".\IMAGES\OBJECTS\OBJECTS.PNG",,,1
 PAGE WRITE 39: CLS: LOAD PNG ".\IMAGES\OBJECTS\OBJECTS_2.PNG",,,1
END SUB

' LOAD PLAYER'S SHAPE PAGES "WHO" (1=GUY,2=CODY,3=HAGGAR) TO PLAYER "PL" (1-2)

SUB LoadPlayer(Who,PL)
 LOCAL P
 P=(PL-1)*4
 SELECT CASE Who
  'GUY
  CASE 1:
   PAGE WRITE 25+P: CLS: LOAD PNG ".\IMAGES\MAIN CHAR - GUY\GGRAPJUMP.PNG",,,1
   PAGE WRITE 26+P: CLS: LOAD PNG ".\IMAGES\MAIN CHAR - GUY\GSPECHURT.PNG",,,1
   PAGE WRITE 27+P: CLS: LOAD PNG ".\IMAGES\MAIN CHAR - GUY\GPUNCH.PNG",,,1
   PAGE WRITE 28+P: CLS: LOAD PNG ".\IMAGES\MAIN CHAR - GUY\GWALKING.PNG",,,1
  'CODY
  CASE 2:
   PAGE WRITE 25+P: CLS: LOAD PNG ".\IMAGES\MAIN CHAR - CODY\CGRAPJUMP.PNG",,,1
   PAGE WRITE 26+P: CLS: LOAD PNG ".\IMAGES\MAIN CHAR - CODY\CSPECHURT.PNG",,,1
   PAGE WRITE 27+P: CLS: LOAD PNG ".\IMAGES\MAIN CHAR - CODY\CPUNCH.PNG",,,1
   PAGE WRITE 28+P: CLS: LOAD PNG ".\IMAGES\MAIN CHAR - CODY\CWALKING.PNG",,,1
  'HAGGAR
  CASE 3:
   PAGE WRITE 25+P: CLS: LOAD PNG ".\IMAGES\MAIN CHAR - HAGGAR\HGRAPJUMP.PNG",,,1
   PAGE WRITE 26+P: CLS: LOAD PNG ".\IMAGES\MAIN CHAR - HAGGAR\HSPECHURT.PNG",,,1
   PAGE WRITE 27+P: CLS: LOAD PNG ".\IMAGES\MAIN CHAR - HAGGAR\HPUNCH.PNG",,,1
   PAGE WRITE 28+P: CLS: LOAD PNG ".\IMAGES\MAIN CHAR - HAGGAR\HWALKING.PNG",,,1
 END SELECT
END SUB


' INSERT A WAIT ON THE PLAYER AND ENEMY
' PAUSE THE MOVEMENTS OF PLAYER AND ENEMY TO GIVE A BETTER EFFECT (LIKE THE ARCADE)
SUB InsertWait(WPL,WEN,WT)
 IF PLWait(PL)=0 THEN PLWait(WPL)=WT
 IF EWAIT(WEN)=0 THEN EWAIT(WEN)=WT
END SUB


' INSERT A HIT
SUB InsertHit(x,y,tp,PL,EN)
 LOCAL T
 FOR T=0 TO 9
  IF AHit(T)=0 THEN
   XHit(T)=x: YHit(T)=y   
   'SET THE START AND THE END OF THE HIT SHAPE / HIT SPEED
   SELECT CASE tp
    CASE 1: AHit(T)= 1: EnHit(T)= 2: SPHit(T)=0.500 'SPARKLE HIT
    CASE 2: AHit(T)= 3: EnHit(T)=13: SPHit(T)=1.000 'SMOKE
    CASE 3: AHit(T)=14: EnHit(T)=23: SPHit(T)=0.075 'GO! GO!
   END SELECT
   EXIT SUB
  ENDIF
 NEXT T
END SUB


' HIT ANIMATION ROUTINE
SUB HitAnimation
 LOCAL T
 FOR T=0 TO 9
  IF AHit(T)>0 THEN
   IF AHIT(T)>0 THEN PutObject(XHit(T),YHit(T),INT(AHit(T)),4,1) 'INSERT SHAPE
   INC AHit(T),SPHit(T)
   IF SPHit(T)=0.075 AND AHit(T)<=INT(AHit(T))+SPHit(T) AND AHit(T)<=EnHit(T) THEN PLAY_SAMPLE 12,3
   IF INT(AHit(T))>=EnHit(T)+1 THEN AHit(T)=0 'END ANIMATION
  ENDIF
 NEXT T
END SUB


' LOAD PLAYER SHAPE NUMBER, ADJUST X,Y AND SIDE, THEN WRITE ON PAGE AND GET COLLISION WITH COLOR
' LAST PARAMETER FORCE SET THE OBJECT TO BE SHOWED OR ONLY TO GET COLLISION
' SHOW = -1 TO READ COLLISION, NO SHAPE IS DISPLAYED
' SHOW =  0 TO WRITE COLLISION AND NO SHAPE IS DISPLAYED
' SHOW =  1 TO SHOW SHAPE ONLY, DON'T WRITE OR READ COLLISION
' SHOW >  1 TO WRITE COLLISION BLOCK TO AN SELECT PAGE
SUB PutPlayer(xs,ys,num,s,Who,pl,SHOW)
 local I,T,xa,ya,xb,yb,sbx,sby,sx,sy,p,pb,tx,ty,tbx,tby,xt,yt,xxt,yyt,kx,ky,kt,SD,BX
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

 BX=&HFF0000: xa=-200: xb=-200: KX=-200: kt=40

 SELECT CASE Who
  CASE 1: 'GUY --------------------------------------------------------------------------
   SELECT CASE num
    'GUY ENERGY AVATAR
    CASE 99 : xa=200:ya=166:sx=49:sy=16:p=25 
    'GUY STOPPED
    CASE 0  : xa=  0:ya=  0:sx=62:sy=86:p=28
    'GUY WALKING - INSERT BOX TO GRAPPLE ENEMIES
    CASE 1  : xa= 62:ya=  0:sx=55:sy=87:p=28:tx= 4:ty=0:BX=&HFFFF00:
              kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
    CASE 2  : xa=117:ya=  0:sx=55:sy=87:p=28:tx= 8:ty=0:BX=&HFFFF00:
              kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
    CASE 3  : xa=172:ya=  0:sx=46:sy=87:p=28:tx=16:ty=0:BX=&HFFFF00:
              kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
    CASE 4  : xa=218:ya=  0:sx=29:sy=87:p=28:tx=14:ty=0:BX=&HFFFF00:
              kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
    CASE 5  : xa=247:ya=  0:sx=29:sy=87:p=28:tx= 8:ty=0:BX=&HFFFF00:
              kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20 
    CASE 6  : xa=276:ya=  0:sx=41:sy=87:p=28:tx=12:ty=0:BX=&HFFFF00:
              kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
    CASE 7  : xa=  0:ya= 88:sx=55:sy=87:p=28:tx= 6:ty=0:BX=&HFFFF00:
              kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
    CASE 8  : xa= 55:ya= 88:sx=55:sy=87:p=28:tx=10:ty=0:BX=&HFFFF00:
              kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
    CASE 9  : xa=110:ya= 88:sx=43:sy=87:p=28:tx=14:ty=0:BX=&HFFFF00:
              kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
    CASE 10 : xa=153:ya= 88:sx=28:sy=87:p=28:tx=10:ty=0:BX=&HFFFF00:
              kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
    CASE 11 : xa=181:ya= 88:sx=28:sy=87:p=28:tx=10:ty=0:BX=&HFFFF00:
              kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
    CASE 12 : xa=209:ya= 88:sx=40:sy=87:p=28:tx=12:ty=0:BX=&HFFFF00:
              kx=10-(MVUD(PL)<>0)*10:ky=5:kt=PS_GRP(PL)*20
    'GUY PUNCHING 
    CASE 13 : xa=  0:ya=0:sx= 64:sy=90:p=27:tx=-12:        
    CASE 14 : xa= 64:ya=0:sx= 81:sy=90:p=27:tx=-44:     kx=19:ky= 5
    'GUY EXTENDED PUNCH
    CASE 15 : xa=145:ya=0:sx= 65:sy=90:p=27:tx=-30:ty=-2 
    CASE 16 : xa=211:ya=0:sx=100:sy=90:p=27:tx=-62:ty=-2:kx=19:ky=15:kt=40
    'GUY ELBOW
    CASE 17 : xa=  0:ya=90:sx=77:sy=81:p=27:tx=-18:ty=2
    CASE 18 : xa= 77:ya=90:sx=88:sy=81:p=27:tx=-18:ty=2:kx=25:ky=10:kt=50':Combo(PL)=3
    'GUY COMBO (AND SPECIAL) 
    'SEQUENCE IS 32,33,34,19,36
    CASE 19 : xa=263:ya=145:sx=57:sy=95:p=26:tx=0:ty=-2:kx=35:ky=10:kt=60 'THIS IS FOR COMBO
    'GUY GRAPPLE / KNEELING / THROWING 
    CASE 20 : xa=  0:ya=154:sx=71:sy=86:p=25:tx=10
    CASE 21 : xa= 71:ya=157:sx=47:sy=82:p=25:tx= 2:BX=&HFF0000:kx=20:ky=0
    CASE 22 : xa=118:ya=173:sx=67:sy=67:p=25:tx= 4:BX=&HFF0000:kx=20:ky=0
    CASE 23 : xa=185:ya=193:sx=82:sy=47:p=25:tx= 0
    'GUY JUMPING AHEAD / VERTICAL
    CASE 24 : xa=201:ya=50:sx=75:sy= 56:p=25:     ty=-30
    CASE 25 : xa=276:ya= 0:sx=44:sy= 67:p=25:     ty=-30
    CASE 26 : xa=  0:ya= 0:sx=57:sy= 78:p=25:tx=0:ty= 0
    CASE 27 : xa= 57:ya= 0:sx=46:sy= 93:p=25:tx=2:ty=-9
    'GUY VERTICAL AIR KICK / AIR KNEE
    CASE 28 : xa=103:ya=  0:sx= 59:sy=86:p=25:tx=  4:ty=-18 
    CASE 29 : xa=162:ya=  0:sx= 63:sy=84:p=25:tx=  2:ty=-24:kx=10:ky=50
    CASE 30 : xa= 86:ya= 86:sx= 50:sy=69:p=25:tx=  2:ty=-24
    CASE 31 : xa=278:ya=152:sx= 42:sy=88:p=25:       ty= -9:kx= 7:ky=35 'AIR KNEE
    CASE 37 : xa=136:ya=106:sx=103:sy=52:p=25:tx=-40:ty=-40:kx=45:ky=40 'FULL AIR KICK
    CASE 44 : xa=  0:ya= 93:sx= 86:sy=58:p=25:tx=  0:ty=-30             'AIR LEAP
    CASE 45 : xa=276:ya= 68:sx= 44:sy=70:p=25                           'WALL JUMP
    'GUY SPECIAL (AND COMBO)
    CASE 32 : xa=  0:ya=0:sx=61:sy=77:p=26:tx= 32-10:ty=-0
    CASE 33 : xa= 61:ya=0:sx=52:sy=78:p=26:tx=  6-10:ty=-0
    CASE 34 : xa=113:ya=0:sx=49:sy=87:p=26:tx=  6-10:ty=-4
    CASE 35 : xa=162:ya=0:sx=80:sy=93:p=26:tx=-25-10:ty= 0: kx=30:ky=30:kt=50  'ROTATED FULL KICK
    CASE 36 : xa=242:ya=0:sx=48:sy=88:p=26:tx=  0-10:ty=-2
    'GUY HURT / ON THE FLOOR / STANDING UP
    CASE 38 : xa= 56:ya= 78:sx= 43:sy=80:p=26:tx=-4        'IN THE STOMACH
    CASE 39 : xa=  0:ya= 77:sx= 56:sy=88:p=26:tx= 6        'IN THE FACE
    CASE 40 : xa=152:ya=173:sx= 99:sy=57:p=26:tx= 0:ty=-12 'FALLING DOWN
    CASE 41 : xa= 99:ya= 93:sx=122:sy=27:p=26:tx= 0        'LYING ON THE FLOOR
    CASE 42 : xa= 99:ya=120:sx= 81:sy=40:p=26:tx= 0        'GET UP
    CASE 43 : xa=  0:ya=181:sx= 48:sy=59:p=26:tx=-2        'ALMOST GET UP (GET OBJECT)
   END SELECT 

  CASE 2: 'CODY -------------------------------------------------------------------------
   SELECT CASE num
    'CODY ENERGY AVATAR
    CASE 99 : xa=179:ya= 86:sx=49:sy=16:p=25
    'CODY STOPPED
    CASE 0  : xa=  0:ya=  0:sx=54:sy=93:p=27
    'CODY WALKING - INSERT BOX TO GRAPPLE ENEMIES
    CASE 1  : xa= 39:ya=104:sx=51:sy=95:p=28:tx=12:ty= 1:BX=&HFFFF00:
              kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 2  : xa= 90:ya=104:sx=62:sy=95:p=28:tx= 7:ty= 1:BX=&HFFFF00:
              kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 3  : xa=152:ya=104:sx=62:sy=95:p=28:tx= 7:ty= 1:BX=&HFFFF00:
              kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 4  : xa=214:ya=103:sx=51:sy=94:p=28:tx=16:ty= 0:BX=&HFFFF00:
              kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 5  : xa=265:ya=102:sx=32:sy=95:p=28:tx= 9:ty=-1:BX=&HFFFF00:
              kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 6  : xa= 0 :ya=  2:sx=35:sy=94:p=28:tx= 6:ty= 0:BX=&HFFFF00:
              kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 7  : xa= 35:ya=  3:sx=48:sy=93:p=28:tx= 9      :BX=&HFFFF00:
              kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 8  : xa= 83:ya=  3:sx=62:sy=93:p=28:tx= 7:ty= 0:BX=&HFFFF00:
              kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 9  : xa=145:ya=  2:sx=63:sy=94:p=28:tx= 8:ty= 0:BX=&HFFFF00:
              kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 10 : xa=208:ya=  2:sx=51:sy=94:p=28:tx=12      :BX=&HFFFF00:
              kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 11 : xa=259:ya=  1:sx=32:sy=95:p=28:tx= 9:ty=-1:BX=&HFFFF00:
              kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 12 : xa=  0:ya=103:sx=38:sy=94:p=28:tx= 3:ty= 0:BX=&HFFFF00:
              kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    'CODY PUNCHING 
    CASE 13 : xa= 54:ya=  2:sx= 64:sy=90:p=27:tx=- 8        
    CASE 14 : xa=118:ya=  2:sx= 84:sy=90:p=27:tx=-28:kx=19:ky= 5
    CASE 15 : xa=202:ya=  9:sx= 83:sy=79:p=27:tx=-34 
    CASE 16 : xa=  0:ya=116:sx=112:sy=77:p=27:tx=-48:kx=19:ky=15
    'CODY UPPERCUT
    CASE 17 : xa=112:ya=123:sx=76:sy= 69:p=27:tx=-18
    CASE 18 : xa=188:ya=103:sx=77:sy= 91:p=27:tx=-18:kx=25:ky=10:kt=60:Combo(PL)=3
    CASE 19 : xa=266:ya= 89:sx=55:sy=111:p=27:tx=- 4:                  Combo(PL)=0
    'CODY GRAPPLE / KNEELING / THROWING 
    CASE 20 : xa=  0:ya= 2:sx=77:sy=86:p=25:tx=10
    CASE 21 : xa= 77:ya= 8:sx=49:sy=77:p=25:tx= 2:BX=&HFF0000:kx=20:ky=0
    CASE 22 : xa=126:ya= 4:sx=63:sy=76:p=25:tx= 4:BX=&HFF0000:kx=20:ky=0
    CASE 23 : xa=189:ya=16:sx=59:sy=64:p=25:tx= 0
    'CODY JUMPING AHEAD / VERTICAL
    CASE 24 : xa=259:ya= 0:sx=61:sy= 65:p=25:     ty=-30
    CASE 25 : xa=255:ya=65:sx=65:sy= 61:p=25:     ty=-30
    CASE 26 : xa=  0:ya=98:sx=53:sy= 84:p=25:tx=0:ty=  0
    CASE 27 : xa= 53:ya=92:sx=42:sy=108:p=25:tx=2:ty= -6
    'CODY VERTICAL AIR KICK / AIR KNEE
    CASE 28 : xa= 96:ya=113:sx=61:sy=87:p=25:tx=2:ty=-18:kx=10:ky=50
    CASE 29 : xa=157:ya=113:sx=54:sy=87:p=25:tx=4:ty=-24
    CASE 30 : xa=211:ya=123:sx=52:sy=76:p=25:tx=2:ty=-24
    CASE 31 : xa=263:ya=129:sx=57:sy=63:p=25:     ty=-30:kx= 7:ky=35
    'CODY SPECIAL / AIR KICK
    CASE 32 : xa=  0:ya=  0:sx= 75:sy=81:p=26:tx=  5:ty= -8
    CASE 33 : xa= 75:ya=  0:sx= 60:sy=85:p=26:tx=  8:ty= -6:kx= 20:ky=40
    CASE 34 : xa=135:ya=  0:sx=120:sy=59:p=26:tx=-40:ty=-30:kx= 45:ky=40 'FULL AIR KICK
    CASE 35 : xa=118:ya=105:sx= 45:sy=70:p=26:tx=  0:ty=-24:kx=  0:ky=40 
    CASE 36 : xa=226:ya=132:sx= 94:sy=68:p=26:tx= 30:ty=-20:kx=-30:ky=40
    CASE 37 : xa=  0:ya= 82:sx= 61:sy=61:p=26:tx=  0:ty=-30:kx=-20:ky=40
    'CODY HURT / ON THE FLOOR / STANDING UP
    CASE 38 : xa=170:ya=101:sx= 55:sy=84:p=26:tx=-4        'IN THE STOMACH
    CASE 39 : xa=260:ya=  0:sx= 60:sy=96:p=26:tx= 6        'IN THE FACE
    CASE 40 : xa=  0:ya=147:sx= 95:sy=53:p=26:tx= 0:ty=-12 'FALLING DOWN
    CASE 41 : xa=136:ya= 59:sx=119:sy=37:p=26:tx= 0        'LYING ON THE FLOOR
    CASE 42 : xa=227:ya= 96:sx= 93:sy=35:p=26:tx= 0        'GET UP
    CASE 43 : xa= 63:ya= 86:sx= 51:sy=58:p=26:tx=-2        'ALMOST GET UP (GET OBJECT)
   END SELECT 

  CASE 3: 'HAGGAR -----------------------------------------------------------------------
   SELECT CASE num
    'HAGGAR ENERGY AVATAR
    CASE 99 : xa=171:ya=224:sx=49:sy=16:p=25

    'HAGGAR STOPPED
    CASE  0 : xb= 81:yb=  0:sbx=51:sby=60
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-17:ty=16
    'HAGGAR WALKING - INSERT BOX TO GRAPPLE ENEMIES
    CASE  1 : xb=132:yb=  0:sbx=36:sby=68:tbx=2
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-28:ty=16
              BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE  2 : xb=168:yb=  0:sbx=50:sby=67:tbx=-4
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-22:ty=16
              BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE  3 : xb=218:yb=  1:sbx=54:sby=66:tbx=-4
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-23:ty=16
              BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE  4 : xb=  0:yb= 49:sbx=58:sby=65:tbx=-6
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-21:ty=16
              BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE  5 : xb= 58:yb= 60:sbx=58:sby=65:tbx=-4
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-22:ty=16
              BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE  6 : xb=116:yb= 67:sbx=47:sby=64:tbx=14
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-40:ty=16
              BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE  7 : xb=163:yb= 67:sbx=37:sby=66:tbx=4
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-30:ty=16
              BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE  8 : xb=200:yb= 67:sbx=37:sby=65:tbx=-4
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-22:ty=16
              BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE  9 : xb=237:yb= 67:sbx=45:sby=66:tbx=0
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-26:ty=16
              BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 10 : xb=  0:yb=114:sbx=56:sby=66:tbx=-2
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-24:ty=16
              BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 11 : xb= 56:yb=125:sbx=51:sby=66:tbx=4
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-31:ty=16
              BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    CASE 12 : xb=107:yb=131:sbx=40:sby=66:tbx=6
              xa=  0:ya=  0:sx= 81:sy= 49:p=28:tx=-33:ty=16
              BX=&HFFFF00:kx=20-(MVUD(PL)<>0)*20:ky=15:kt=PS_GRP(PL)*15
    'HAGGAR PUNCHING 
    CASE 13 : xa=  0:ya=  0:sx= 57:sy=86:p=27:tx=  6
    CASE 14 : xa= 57:ya=  0:sx= 71:sy=86:p=27:tx=- 8
    CASE 15 : xa=128:ya=  0:sx=113:sy=84:p=27:tx=-52:kx=25:ky= 5:kt=60
    CASE 16 : xa=241:ya=  0:sx= 54:sy=99:p=27:tx=- 4
    CASE 17 : xa=  0:ya= 86:sx= 71:sy=89:p=27:tx=-18
    CASE 18 : xa= 71:ya= 86:sx=111:sy=81:p=27:tx=-48:kx=25:ky=10:kt=60:Combo(PL)=2
    CASE 19 : xa=182:ya= 99:sx= 71:sy=87:p=27:tx=-30:                  Combo(PL)=0
    'HAGGAR GRAPPLE
    CASE 20 : xb= 81:yb=  0:sbx=51:sby=60:pb=28
              xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-44:ty= 9
    'HAGGAR HEAD BANG
    CASE 21 : xb= 81:yb=  0:sbx=51:sby=60:pb=28
              xa=  0:ya=200:sx= 54:sy= 40:p =25:tx=-17:ty=16:BX=&HFF0000:kx=35:ky=-25:kt=50
    'HAGGAR SUPLEX
    CASE 22 : xa=102:ya=141:sx= 69:sy= 99:p =25:tx= 2':       BX=&HFF0000:kx=  0:ky=0:kt=40
    CASE 23 : xa=224:ya=192:sx= 96:sy= 49:p =25:tx= 0':       BX=&HFF0000:kx=-20:ky=0:kt=50
    'HAGGAR JUMPING AHEAD / VERTICAL
    CASE 24 : xa=  0:ya=  0:sx=63:sy= 85:p=25
    CASE 25 : xa= 63:ya=  0:sx=52:sy=100:p=25
    CASE 26 : xa=116:ya=  0:sx=55:sy= 78:p=25:     ty=-16
    CASE 27 : xa=171:ya=  0:sx=85:sy= 68:p=25:tx=2:ty= -6
    'HAGGAR VERTICAL AIR KICK / SMASH
    CASE 28 : xa=154:ya= 68:sx=123:sy=61:p=25:tx=-50:ty=-30:kx=38:ky=15:kt=50
    CASE 29 : xa=  0:ya=100:sx=128:sy=52:p=25:tx=-20:ty=-24:kx=0:ky=-20:kt=80
    'HAGGAR PILE DRIVER
    'SEQUENCE IS 30,31,26,32,26,24
    CASE 30 : xb=147:yb=133:sbx=56:sby=49:pb=28
              xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-44:ty=9
    CASE 31 : xb= 65:yb= 33:sbx=30:sby=67
              xa=  1:ya=153:sx= 72:sy= 45:p =25:tx=-46:ty=10
    CASE 32 : xa=232:ya=139:sx= 88:sy= 53:p =25:tx=-44:ty=-40:kx=0:ky=0:kt=70
    'HAGGAR SPECIAL 
    CASE 33 : xa=  0:ya=  0:sx= 67:sy=121:p=26:tx=  5:kx=  0:ky=10:kt=60
    CASE 34 : xa= 67:ya=  0:sx= 56:sy= 95:p=26:tx=- 5:kx=-10:ky=10:kt=60
    CASE 35 : xa=123:ya=  0:sx=102:sy= 93:p=26:tx=-50:kx= 20:ky=10:kt=60
    CASE 36 : xa=  0:ya=121:sx= 46:sy= 93:p=26:tx=  0:kx=-10:ky=10:kt=60
    CASE 37 : xa=108:ya= 95:sx=120:sy= 93:p=26:tx=  0:kx=-30:ky=10:kt=60
    'HAGGAR HURT / ON THE FLOOR / STANDING UP
    CASE 38 : xa=259:ya=  0:sx= 61:sy=77:p=26:tx=-4        'IN THE STOMACH
    CASE 39 : xb= 81:yb=  0:sbx=51:sby=60:pb=28            'IN THE FACE
              xa= 46:ya=168:sx= 74:sy= 46:p =26:tx=-26:ty=10
    CASE 40 : xa=228:ya=148:sx= 92:sy=92:p=26:tx= 0        'FALLING DOWN
    CASE 41 : xa= 12:ya=214:sx=133:sy=26:p=26:tx= 0        'LYING ON THE FLOOR
    CASE 42 : xa=145:ya=193:sx= 83:sy=47:p=26:tx= 0        'GET UP
    CASE 43 : xa=257:ya= 78:sx= 63:sy=69:p=26:tx=-2        'ALMOST GET UP (GET OBJECT)
    'HAGGAR WALKING WITH GRAPPLED ENEMY
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

 END SELECT 'END SELECT Who

 'ADJUST SIDE
 if s=4 OR s=6 THEN SD=1
 if s=5 OR s=7 THEN TX=-TX: TBX=-TBX: SD=-1

 ' FIX VIDEO PAGE WITH THE PLAYER NUMBER
 IF PL>0 THEN INC P,(PL-1)*4: IF PB>0 THEN INC PB,(PL-1)*4

 ' SET COORDINATES AS THE INFERIOR PART OF THE SHAPE AND
 ' MAKE A PERFECT FLIP WITHOUT TREMBLING WITH NON INTEGER NUMBERS
 IF SD=-1 THEN xxt=xs-CINT((sx+TX+tbx)/2) ELSE xxt=xs-(sx+TX+tbx)\2
 yyt=ys-sy+TY-(xb>-99)*(SBY-TBY)
 
 ' SET HIT POSITION ALWAYS ON THE CENTER
 XTHit=xxt+sx\2: YTHit=yyt+sy\3

 SELECT CASE SHOW
  CASE -1: ' SET HIT POSITION --------------------------------------
   XH(pl)=XTHit: YH(pl)=YTHit
   Exit Sub

  CASE 0: ' WRITE COLLISION BOX ------------------------------------
   PAGE WRITE 34     'COLLISION BOX TO BE ATTACKED
   BOX xxt,yyt,sx,sy,,&HFFFFFF,&HFFFFFF
   IF DEBUG THEN PAGE WRITE 1: BOX xxt,yyt,sx,sy,,&HFFFFFF,&HFFFFFF
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
   'TWO SHAPES TO MAKE ONE
   IF xb>-99 THEN
    'MAKE A PERFECT FLIP WITHOUT TREMBLING WITH NON INTEGER NUMBERS
    IF SD=-1 THEN xt=xs-CINT((sbx+TBX)/2) ELSE xt=xs-(sbx+TBX)\2
    yt=ys-sby+TBY: if pb=0 then pb=p
    BLIT xb,yb,xt,yt,sbx,sby,pb,s
   ENDIF
   BLIT xa,ya,xxt,yyt,sx,sy,p,s

 END SELECT

END SUB



' LOAD ENEMY SHAPE NUMBER, ADJUST X,Y AND SIDE, THEN WRITE ON PAGE AND GET COLLISION WITH COLOR
' LAST PARAMETER FORCE SET THE OBJECT TO BE SHOWED OR ONLY TO GET COLLISION
' SHOW = -1 TO READ COLLISION, NO SHAPE IS DISPLAYED
' SHOW =  0 TO WRITE COLLISION AND NO SHAPE IS DISPLAYED
' SHOW =  1 TO SHOW SHAPE ONLY, DON'T WRITE OR READ COLLISION
' SHOW >  1 TO WRITE COLLISION BLOCK TO AN SELECT PAGE
SUB PutEnemy(xs,ys,num,s,Who,pl,SHOW)
 local I,T,xa,ya,xb,yb,sbx,sby,sx,sy,p,pb,tx,ty,tbx,tby,xt,yt,xxt,yyt

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

 xa=-200: xb=-200

 SELECT CASE Who

  CASE 4 TO 6: 'BRED / JAKE / DUG -------------------------------------------------------
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
   END SELECT 'END BRED / JAKE / DUG
   INC ya,(Who-4)*93
   INC yb,(Who-4)*93

  CASE 7 TO 8: 'J / TWO P ---------------------------------------------------------------
   SELECT CASE num
    'ENERGY AVATAR
    CASE 99 : xa=0:ya=504:sx=59:sy=16:tx=-3:ty=0
    'STOPPED
    CASE  9 : xa=163:ya=508:sx=64:sy=91
    'WALKING (ALWAYS WITH ATTENTION)
    CASE 10 : xa=163:ya=508:sx=64:sy=49:tx=0:ty=0:xb=227:yb=504:sbx=38:sby=42:tbx= 0:tby=0
    CASE 11 : xa=163:ya=508:sx=64:sy=49:tx=0:ty=0:xb=227:yb=546:sbx=30:sby=43:tbx= 0:tby=0
    CASE 12 : xa=163:ya=508:sx=64:sy=49:tx=0:ty=0:xb=227:yb=504:sbx=38:sby=42:tbx= 0:tby=0
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
    'CASE  9 : xa=  0:ya=  0:sx= 0:sy= 0:tx=0:ty=0
    'CASE 10 : xa=  0:ya=  0:sx= 0:sy= 0:tx=0:ty=0
   END SELECT 'END J / TWO P
   INC xa,(who-7)*796
   INC xb,(who-7)*796

  CASE 9 TO 10: 'AXL / SLASH ------------------------------------------------------------
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
    CASE 22 : xa=911:ya=  6:sx=64:sy=100:tx=0 'IN THE FACE
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

   END SELECT 'END AXL / SLASH
   INC ya,(who-9)*107
   INC yb,(who-9)*107

  CASE 80: 'DAMND -----------------------------------------------------------------------
   SELECT CASE num
    'ENERGY AVATAR
    CASE 99 : xa=2:ya=1084:sx=60:sy=16:tx=-7:ty=0
    'STOPPED
    CASE  0 : xa=423:ya=1083: sx=86: sy=61: tx=-4: ty= 13:
              xb=192:yb=1083:sbx=73:sby=61:tbx= 0:tby=  0
    'WALKING / WALKING WITH JESSICA (ROUND 1-1)
    CASE  1,101 : xa=423:ya=1083: sx=86: sy=61: tx=-4: ty=13:
                  xb=265:yb=1083:sbx=62:sby=65:tbx=-4:tby= 0
    CASE  2,102 : xa=423:ya=1083: sx=86: sy=61: tx=-4: ty=12:
                  xb=327:yb=1083:sbx=51:sby=65:tbx= 2:tby= 0
    CASE  3,103 : xa=423:ya=1083: sx=86: sy=61: tx=-4: ty=12:
                  xb=378:yb=1083:sbx=45:sby=65:tbx= 8:tby= 0
    'LAUGHING / LAUGHING WITH JESSICA (ROUND 1-1)
    CASE  4,104 : xa=995:ya=1085: sx=86: sy=61: tx=-4: ty= 13:
                  xb=192:yb=1083:sbx=73:sby=61:tbx= 0:tby=  0
    CASE  5,105 : xa=505:ya=1144: sx=86: sy=54: tx=-4: ty= 13:
                  xb=192:yb=1083:sbx=73:sby=61:tbx= 0:tby=  0

   END SELECT 'END DAMND

  CASE 99: 'SPECIAL CASES ---------------------------------------------------------------
   SELECT CASE num
    'JESSICA ROUND 1 DAMND INTRO
    CASE 997: xa=1094:ya=1125:sx=51:sy=75:tx= 0:ty=0
    CASE 998: xa=1145:ya=1125:sx=49:sy=75:tx=-2:ty=0
    CASE 999: xa=1194:ya=1125:sx=51:sy=75:tx= 0:ty=0
   END SELECT 'END SPECIAL CASES

 END SELECT 'END SELECT Who

 'ADJUST SIDE
 if s=5 OR s=7 THEN TX=-TX: TBX=-TBX

 ' SET THE INFERIOR OF THE FIRST PART OF THE SHAPE
 xxt=xs-(sx+TX)\2: yyt=ys-sy+TY-(xb>-99)*(SBY-TBY)

 SELECT CASE SHOW
  CASE <=-1: ' SHOW = -1 TO READ COLLISION, NO SHAPE IS DISPLAYED ------------------------

   ' CHECK COLLISION - GET THE PIXELS FROM THE FIRST SHAPE ONLY
   FOR I=0 TO 2
    COLLIDE(I)=0 
    PAGE WRITE 34+I
    T=PIXEL(xxt+2   ,yyt+8):    IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    T=PIXEL(xxt-2+sx,yyt+8):    IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    T=PIXEL(xxt+sx\2,yyt+sy\2): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
   NEXT I
   'SET HIT POSITION ALWAYS BASED ONF THE FIRST PART OF THE SHAPE (FASTER)
   XTHit=xxt+sx\2: YTHit=yyt+sy\2

  CASE  0: ' SHOW =  0 TO WRITE COLLISION AND NO SHAPE IS DISPLAYED --------------------

   ' INSERT COLLISION BOX WHEN ENEMY IS THROWED
   IF ETR(PL)>0 THEN
    IF DEBUG THEN PAGE WRITE 1:BOX xxt-10,yyt-10,sx+20,sy+20,,&HFF00FF,&HFF00FF
    PAGE WRITE 34
    ' CHANGE THE COLOUR TO MAKES EASIER TO TELL THE SIDE OF THE ENEMY
    IF ESIDE(PL)=4 OR ESIDE(PL)=6 THEN
     BOX xxt-10,yyt-10,sx+20,sy+20,,&HFF00FF,&HFF00FF
    ELSE
     BOX xxt-10,yyt-10,sx+20,sy+20,,&HFF00BF,&HFF00BF
    ENDIF
    EXIT SUB
   ENDIF

  CASE  1: ' SHOW =  1 TO SHOW SHAPE ONLY, DON'T WRITE OR READ COLLISION ---------------

   PAGE WRITE 1
   'TWO SHAPES TO MAKE ONE
   IF xb>-99 THEN
    xt=xs-(sbx+TBX)\2: yt=ys-sby+TBY
    BLIT xb,yb,xt,yt,sbx,sby,FRAMEBUFFER,s
   ENDIF
   BLIT xa,ya,xxt,yyt,sx,sy,FRAMEBUFFER,s

 END SELECT 'END SELECT SHOW -----------------------------------------------------------


 'REMOVE COLLISION IF OUT OF Y AXIS WITH THE ENEMY
 IF SHOW=-1 THEN
  FOR I=1 TO 2
   T=(Grap(I)>0)*10 'EXTEND REAL Y WHEN GRAPPLE
   IF COLLIDE(I)>0 AND (RealY(pl)<RealY(I)-5-T or RealY(pl)>RealY(I)+5+T) THEN COLLIDE(I)=0
  NEXT I
 ENDIF

 'INSERT JESSICA ON THE DAMND HANDS
 IF Who=80 THEN
  SELECT CASE NUM
   CASE 101: PutEnemy(xs+10,ys-24,997,4,99,,1)
   CASE 102: PutEnemy(xs+ 9,ys-22,999,4,99,,1)
   CASE 103: PutEnemy(xs+ 9,ys-22,999,4,99,,1)
   CASE 104: PutEnemy(xs+10,ys-20,997,4,99,,1)
   CASE 105: PutEnemy(xs+ 5,ys-20,998,4,99,,1)
  END SELECT
 ENDIF

END SUB


' LOAD SHAPE NUMBER, ADJUST X,Y AND SIDE, THEN WRITE ON PAGE AND GET COLLISION WITH COLOR
' LAST PARAMETER FORCE SET THE OBJECT TO BE SHOWED OR ONLY TO GET COLLISION
' SHOW <> 0 TO NOT SHOW SHAPE AND READ COLLISION
' SHOW =  1 TO SHOW SHAPE ONLY, DON'T WRITE OR READ COLLISION
SUB PutObject(xs,ys,num,s,SHOW)
 local I,T,xa,ya,xxt,yyt,sx,sy,p,tx,ty
 'I,T - TEMPORARY VARIABLES
 '
 'FROM THE IMAGE TO BE COPIED / FROM A SECOND IMAGE TO MAKE ONE SHAPE: 
 'xa  - X
 'ya  - Y
 'sx  - WIDTH
 'sy  - HEIGHT
 'p   - VIDEO PAGE
 'tx  - X CORRECTION
 'ty  - Y CORRECTION
 'xt  - CENTER OF THE SHAPE

 IF s<4 THEN s=4
 SELECT CASE num
  'HITS 
  CASE 1  : xa=258:ya=199:sx=40:sy=41:p=38 'BIG  
  CASE 2  : xa=298:ya=212:sx=22:sy=28:p=38 'SMALL
  'SMOKE 
  CASE 3  : xa=232:ya=218:sx=26:sy=22:p=38:ty=-num 'BIG
  CASE 5  : xa=232:ya=218:sx=26:sy=22:p=38:ty=-num 'BIG
  CASE 7  : xa=232:ya=218:sx=26:sy=22:p=38:ty=-num 'BIG
  CASE 9  : xa=234:ya=198:sx=24:sy=20:p=38:ty=-num 'SMALL
  CASE 11 : xa=234:ya=198:sx=24:sy=20:p=38:ty=-num 'SMALL
  CASE 13 : xa=234:ya=198:sx=24:sy=20:p=38:ty=-num 'SMALL
  'GO! GO!
  CASE 14,16,18,20,22: xa=226:ya= 24:sx=32:sy=25:p=38:ty=-num 'GO!
  CASE 15,17,19,21,23: xa=158:ya=222:sx=29:sy=18:p=38:ty=-num 'HAND
  'TIME
  CASE 99 : xa=231:ya= 49:sx=31:sy=16 :p=38 

  'DESTRUCTIBLES ------------------------------------------------------------------------

  'DRUMCAN
  CASE -24: xa= 32:ya=224:sx=16:sy=16:p=38: AVA$="DRUMCAN" 'AVATAR
  CASE 24 : xa=152:ya= 30:sx=56:sy=71:p=38 'OK
  CASE 25 : xa=148:ya=101:sx=61:sy=48:p=38 'UPPER BROKEN
  CASE 26 : xa=126:ya=160:sx=61:sy=48:p=38 'LOWER BROKEN
  'TELEPHONE BOOTH
  CASE -27: xa= 64:ya=224:sx=16:sy= 16:p=38: AVA$="TEL` BOOTH" 'AVATAR
  CASE 27 : xa= 64:ya=  0:sx=80:sy=128:p=39 'OK
  CASE 28 : xa=144:ya=  0:sx=80:sy= 43:p=39 'UPPER BROKEN
  CASE 29 : xa=144:ya= 43:sx=80:sy= 50:p=39 'LOWER BROKEN
  'BARREL
  CASE -30: xa=48:ya=224:sx=16:sy=16:p=38: AVA$="BARREL" 'AVATAR
  CASE 30 : xa= 0:ya=  0:sx=58:sy=69:p=38 'OK
  CASE 31 : xa= 0:ya= 69:sx=59:sy=42:p=38:s=7 'UPPER BROKEN - NOT USED
  CASE 32 : xa= 0:ya= 69:sx=59:sy=42:p=38:s=4 'LOWER BROKEN
  'DUSTBIN
  CASE -33: xa= 0:ya=224:sx=16:sy=16:p=38: AVA$="DUSTBIN" 'AVATAR
  CASE 33 : xa=58:ya=  0:sx=42:sy=54:p=38 'OK
  CASE 34 : xa=59:ya= 54:sx=45:sy=56:p=38 'SMASHED
  'TIRES 
  CASE -35: xa= 16:ya=224:sx=16:sy=16:p=38: AVA$="TIRES" 'AVATAR
  CASE 35 : xa=104:ya=  0:sx=48:sy=55:p=38 'OK
  CASE 36 : xa=105:ya= 56:sx=44:sy=17:ty= 8:p=38 'NORMAL TIRE
  CASE 37 : xa=105:ya= 73:sx=44:sy=31:      p=38 'ALMOST ROTATED TIRE
  CASE 38 : xa=152:ya=  0:sx=39:sy=30:tx=-8:p=38 'INCLINED TIRE
  'FREIGHT
  CASE -39: xa= 48:ya=224:sx=16:sy=16:p=38: AVA$="FREIGHT" 'AVATAR
  CASE 39 : xa=224:ya=  0:sx=80:sy=92:p=39 'OK
  CASE 40 : xa=224:ya= 92:sx=80:sy=40:p=39 'LOWER BROKEN
  'BILLBOARD
  CASE -41: xa= 64:ya=224:sx=16:sy= 16:p=38: AVA$="BILLBOARD" 'AVATAR
  CASE 41 : xa=  0:ya=146:sx=64:sy= 94:p=39 'OK - LIGHT 1
  CASE 42 : xa= 64:ya=146:sx=64:sy= 94:p=39 'OK - LIGHT 2
  CASE 43 : xa=  0:ya=  0:sx=64:sy= 48:p=39 'UPPER BROKEN
  CASE 44 : xa=  0:ya= 48:sx=64:sy= 64:p=39 'LOWER BROKEN

  'POINTS -------------------------------------------------------------------------------

  'NAPKIN - 1000
  CASE -100 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="NAPKIN"
  CASE  100 : xa=  0:ya=132:sx=32:sy=11 :p=38
  'HAT - 1000
  CASE -101 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="HAT"
  CASE  101 : xa= 28:ya=118:sx=24:sy=13 :p=38 
  'HAMMER - 1000
  CASE -102 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="HAMMER"
  CASE  102 : xa=  0:ya=112:sx=27:sy=11 :p=38 
  'RADIO - 1000
  CASE -103 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="RADIO"
  CASE  103 : xa= 58:ya=130:sx=29:sy=16 :p=38 
  'TOPAZ - 1000
  CASE -104 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="TOPAZ"
  CASE  104 : xa= 67:ya=121:sx=16:sy= 9 :p=38 
  'YEN - 3000
  CASE -105 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="YEN"
  CASE  105 : xa=  0:ya=144:sx=15:sy=10 :p=38 
  'DOLLAR - 3000
  CASE -106 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="DOLLAR"
  CASE  106 : xa= 15:ya=143:sx=32:sy=11 :p=38 
  'WATCH - 3000
  CASE -107 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="WATCH"
  CASE  107 : xa= 32:ya=131:sx=26:sy=12 :p=38 
  'OPAL - 5000
  CASE -108 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="OPAL"
  CASE  108 : xa=  0:ya=123:sx=28:sy= 9 :p=38 
  'PEARL - 5000
  CASE -109 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="PEARL"
  CASE  109 : xa=  0:ya=155:sx=28:sy= 9 :p=38 
  'EMERALD - 5000
  CASE -110 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="EMERALD"
  CASE  110 : xa= 28:ya=155:sx=16:sy= 9 :p=38 
  'RUBY - 5000
  CASE -111 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="RUBY"
  CASE  111 : xa= 44:ya=153:sx=16:sy=11 :p=38 
  'GOLD BAR - 10000
  CASE -112 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="GOLD BAR"
  CASE  112 : xa= 60:ya=146:sx=32:sy=12 :p=38 
  'DIAMOND - 10000
  CASE -113 : xa=128:ya=224:sx=16:sy=16 :p=38: AVA$="DIAMOND"
  CASE  113 : xa= 52:ya=118:sx=15:sy=12 :p=38 

  'FOOD ---------------------------------------------------------------------------------

  'GUM - 1000
  CASE -120 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="GUM"
  CASE  120 : xa=  0:ya=214:sx= 8:sy= 5 :p=38 
  'GUM - 1000
  CASE -121 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="GUM"
  CASE  121 : xa=  0:ya=219:sx=16:sy= 5 :p=38 
  'SOFT DRINK - 1000
  CASE -122 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="SOFT DRINK"
  CASE  122 : xa= 16:ya=208:sx=14:sy=16 :p=38 
  'SOFT DRINK - 1000
  CASE -123 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="SOFT DRINK"
  CASE  123 : xa= 30:ya=208:sx=16:sy=16 :p=38 
  'BEER - 1000
  CASE -124 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="BEER"
  CASE  124 : xa= 46:ya=208:sx=17:sy=16 :p=38 
  'BEER - 1000
  CASE -125 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="BEER"
  CASE  120 : xa= 63:ya=212:sx=31:sy=12 :p=38 
  'BEER - 1000
  CASE -126 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="BEER"
  CASE  126 : xa= 94:ya=212:sx=30:sy=12 :p=38 
  'WHISKY - 1000
  CASE -127 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="WHISKY"
  CASE  127 : xa=124:ya=211:sx=31:sy=13 :p=38 
  'APPLE - 3000
  CASE -128 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="APPLE"
  CASE  128 : xa=  0:ya=194:sx=16:sy=14 :p=38 
  'BANANA - 3000
  CASE -129 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="BANANA"
  CASE  129 : xa= 16:ya=192:sx=29:sy=16 :p=38 
  'GRAPES - 3000
  CASE -130 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="GRAPES"
  CASE  130 : xa= 45:ya=192:sx=28:sy=16 :p=38 
  'ORANGE - 3000
  CASE -131 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="ORANGE"
  CASE  131 : xa= 73:ya=195:sx=16:sy=13 :p=38 
  'PINEAPPLE - 3000
  CASE -132 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="PINEAPPLE"
  CASE  132 : xa= 89:ya=192:sx=32:sy=16 :p=38 
  'HOT DOG - 5000
  CASE -133 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="HOT DOG"
  CASE  133 : xa=  0:ya=164:sx=32:sy=14 :p=38 
  'HAMBURGER - 5000
  CASE -134 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="HAMBURGER"
  CASE  134 : xa= 32:ya=164:sx=30:sy=15 :p=38 
  'SUSHI - 5000
  CASE -135 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="SUSHI"
  CASE  135 : xa= 63:ya=158:sx=29:sy=12 :p=38 
  'CURRY - 5000
  CASE -136 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="CURRY"
  CASE  136 : xa=122:ya=147:sx=30:sy=13 :p=38 
  'PIZZA - 5000
  CASE -137 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="PIZZA"
  CASE  137 : xa=  0:ya=178:sx=30:sy=14 :p=38 
  'STEAK - 10000
  CASE -138 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="STEAK"
  CASE  138 : xa= 30:ya=179:sx=32:sy=13 :p=38 
  'CHICKEN - 10000
  CASE -139 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="CHICKEN"
  CASE  139 : xa= 62:ya=170:sx=32:sy=22 :p=38 
  'BARBECUE - 10000
  CASE -140 : xa=112:ya=224:sx=16:sy=16 :p=38: AVA$="BARBECUE"
  CASE  140 : xa= 94:ya=170:sx=32:sy=22 :p=38 


  'BROKEN PIECES ------------------------------------------------------------------------
  
  'PIECES OF GLASS
  CASE 200 : xa=206:ya=210:sx=26:sy=30:p=38:      ty=-1:s=4
  CASE 201 : xa=188:ya=207:sx=17:sy=33:p=38:tx=-6      :s=4
  CASE 202 : xa=216:ya=173:sx=10:sy=37:p=38:tx= 6:ty= 2:s=4
  CASE 203 : xa=188:ya=207:sx=17:sy=33:p=38:tx=-6      :s=5
  CASE 204 : xa=206:ya=210:sx=26:sy=30:p=38:      ty=-1:s=5
  CASE 205 : xa=188:ya=207:sx=17:sy=33:p=38:tx=-6      :s=5
  CASE 206 : xa=216:ya=173:sx=10:sy=37:p=38:tx= 6:ty= 2:s=4
  CASE 207 : xa=206:ya=210:sx=26:sy=30:p=38:      ty=-1:s=4
  'PIECES OF WOOD
  CASE 208 : xa=226:ya=185:sx=32:sy=13:p=38:tx=-4:ty= 6:s=4 'FIRST BLOCK (PIECE)
  CASE 209 : xa=274:ya=178:sx=28:sy=21:p=38:      ty= 0:s=4
  CASE 210 : xa=226:ya=185:sx=32:sy=13:p=38:tx=-4:ty= 6:s=6
  CASE 211 : xa=274:ya=178:sx=28:sy=21:p=38:      ty= 0:s=6

  CASE 212 : xa=258:ya=173:sx=14:sy=26:p=38:            s=4 'SECOND BLOCK (STICK)
  CASE 213 : xa=304:ya=181:sx=16:sy=11:p=38:tx=-2:ty= 6:s=4
  CASE 214 : xa=258:ya=173:sx=14:sy=26:p=38:            s=6
  CASE 215 : xa=304:ya=181:sx=16:sy=11:p=38:tx=-2:ty= 6:s=6

  CASE 216 : xa=245:ya=169:sx=13:sy=16:p=38:            s=4 'THIRD BLOCK (SMALL PIECE)
  CASE 217 : xa=272:ya=169:sx=14:sy= 9:p=38:tx=-1:ty= 2:s=4
  CASE 218 : xa=245:ya=169:sx=13:sy=16:p=38:            s=5
  CASE 219 : xa=272:ya=169:sx=14:sy= 9:p=38:tx=-1:ty= 2:s=5

  CASE 220 : xa=304:ya=167:sx=14:sy=14:p=38:s=4             'FOURTH BLOCK (SMALL PIECE)
  CASE 221 : xa=304:ya=167:sx=14:sy=14:p=38:s=6
  CASE 222 : xa=304:ya=167:sx=14:sy=14:p=38:s=5
  CASE 223 : xa=304:ya=167:sx=14:sy=14:p=38:s=7

 END SELECT

 xxt=xs-(sx+TX)\2: yyt=ys-sy+TY
 
 IF SHOW=1 THEN
  PAGE WRITE 1
  BLIT xa,ya,xxt,yyt,sx,sy,p,s
 ELSE
  ' CHECK COLLISION - GET THE PIXELS FROM THE FIRST SHAPE ONLY
  FOR I=0 TO 2
   COLLIDE(I)=0
   IF OSDX>=620 OR (ys>RealY(I)-10 AND ys<RealY(I)+10) THEN
    PAGE WRITE 34+I
    T=PIXEL(xxt+sx\2,yyt-4): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    T=PIXEL(xxt+2,   yyt-4): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    T=PIXEL(xxt+sx-2,yyt-4): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    T=PIXEL(xxt+sx\2,yyt+sy\2): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    T=PIXEL(xxt+2,   yyt+sy\2): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    T=PIXEL(xxt+sx-2,yyt+sy\2): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
   ENDIF
  NEXT I
 ENDIF

 'SET HIT POSITION ALWAYS BASED ONF THE FIRST PART OF THE SHAPE (FASTER)
 XTHit=xxt+sx\2: YTHit=yyt+sy\2

END SUB

