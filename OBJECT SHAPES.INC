' --- GENERAL SHAPE / PSEUDO-SPRITES ROUTINES FOR THE OBJECTS ---

' LOAD SHAPE NUMBER, ADJUST X,Y AND SIDE, THEN WRITE ON PAGE AND GET COLLISION WITH COLOR
' LAST PARAMETER FORCE SET THE OBJECT TO BE SHOWED OR ONLY TO GET COLLISION
' SHOW <> 0 TO NOT SHOW SHAPE AND READ COLLISION AND INSERT BLOCK COLLISION
' SHOW =  1 TO SHOW SHAPE ONLY, DON'T WRITE OR READ COLLISION
SUB PutObject(xs,ys,num,s,SHOW)
 local I,T',xa,ya,xxt,yyt,sx,sy,p,tx,ty
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

 p=0: xa =0: ya =0: sx=0: sy=0: xxt=0: yyt=0: tx=0: ty=0

 IF s<4 THEN s=4
 SELECT CASE num
  'HITS 
  CASE 1 : xa=258:ya=199:sx=40:sy=41:p=38 'BIG  
  CASE 2 : xa=298:ya=212:sx=22:sy=28:p=38 'SMALL
  'SMOKE
  CASE 3 TO 13: ShowSmoke(num,s) 
  'GO! GO!
  CASE 14 TO 23:
   IF NUM MOD 2 THEN
    xa=158:ya=222:sx=29:sy=18:p=38:ty=-num 'HAND
   ELSE 
    xa=226:ya= 24:sx=32:sy=25:p=38:ty=-num 'GO!
   ENDIF
  'TIME
  CASE 99 : xa=231:ya= 49:sx=31:sy=16 :p=38 

  CASE 200 TO 207: ShowPiecesGlass(num,s)
  CASE 208 TO 223: ShowPiecesWood(num,s)
  CASE 260 TO 269: ShowMolotovFire(num,s)
  CASE -24,24 TO 26: ShowDrumcan(num,s) 
  CASE -27,27 TO 29: ShowTelBooth(num,s) 
  CASE -30,30 TO 32: ShowBarrel(num,s) 
  CASE -33,33 TO 34: ShowDustbin(num,s) 
  CASE -35,35 TO 38: ShowTires(num,s) 
  CASE -39,39 TO 40: ShowFreight(num,s) 
  CASE -41,41 TO 43: ShowBillboard(num,s) 
  CASE -113 TO -100,100 TO 113: ShowPoints(num,s) 
  CASE -140 TO -120,120 TO 140: ShowFood(num,s)  
  CASE -270,272 TO 272: ShowDrumcan(num,s) 
  CASE 250 TO 257: ShowMolotov(num,s)
  CASE 270 TO 272: ShowBlood(num,s)
  CASE -280,280 TO 289: ShowKatana(num,s)
  CASE -290,290 TO 299,310: ShowKnife(num,s)
  CASE -300,300 TO 309: ShowPipe(num,s)
 END SELECT

 if s=5 then tx=-tx
 xxt=xs-(sx+TX)\2: yyt=ys-sy+TY

 IF SHOW<1 THEN
  ' CHECK COLLISION - GET THE PIXELS FROM THE FIRST SHAPE ONLY
  FOR I=0 TO 2
   COLLIDE(I)=0
   IF OSDX>=620 OR ((ys>RealY(I)-10 AND ys<RealY(I)+10) OR I=0) THEN
    PAGE WRITE 34+I
    T=PIXEL(xs+sx\2-tx\2,yyt+8):    IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    T=PIXEL(xs-sx\2-tx\2,yyt+8):    IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    T=PIXEL(xs+sx\2-tx\2,yyt+sy\2): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    T=PIXEL(xs-sx\2-tx\2,yyt+sy\2): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
    T=PIXEL(xs          ,yyt+sy\2): IF T>0 AND COLLIDE(I)=0 THEN COLLIDE(I)=T
   ENDIF
  NEXT I
 ELSE 'WRITE AND DON'T CHECK COLLISION
  PAGE WRITE 1
  BLIT xa,ya,xxt,yyt,sx,sy,p,s
 ENDIF

 'SET HIT POSITION ALWAYS BASED ON THE FIRST PART OF THE SHAPE (FASTER)
 XTHit=xxt+sx\2: YTHit=yyt+sy\2

END SUB

'SMOKE
SUB ShowSmoke(num,s)
 SELECT CASE num
  CASE 3  : xa=232:ya=218:sx=26:sy=22:p=38:ty=-num 'BIG
  CASE 5  : xa=232:ya=218:sx=26:sy=22:p=38:ty=-num 'BIG
  CASE 7  : xa=232:ya=218:sx=26:sy=22:p=38:ty=-num 'BIG
  CASE 9  : xa=234:ya=198:sx=24:sy=20:p=38:ty=-num 'SMALL
  CASE 11 : xa=234:ya=198:sx=24:sy=20:p=38:ty=-num 'SMALL
  CASE 13 : xa=234:ya=198:sx=24:sy=20:p=38:ty=-num 'SMALL
 END SELECT
END SUB

'DESTRUCTIBLES ------------------------------------------------------------------------

'DRUMCAN
SUB ShowDrumcan(num,s)
 SELECT CASE num
  CASE -24: xa= 32:ya=224:sx=16:sy=16:p=38: AVA$="DRUMCAN" 'AVATAR
  CASE 24 : xa=152:ya= 30:sx=56:sy=71:p=38 'OK
  CASE 25 : xa=148:ya=101:sx=61:sy=48:p=38 'UPPER BROKEN
  CASE 26 : xa=126:ya=160:sx=61:sy=48:p=38 'LOWER BROKEN
 END SELECT
END SUB

'TELEPHONE BOOTH
SUB ShowTelBooth(num,s)
 SELECT CASE num
  CASE -27: xa= 64:ya=224:sx=16:sy= 16:p=38: AVA$="TEL` BOOTH" 'AVATAR
  CASE 27 : xa= 64:ya=  0:sx=80:sy=128:p=33 'OK
  CASE 28 : xa=144:ya=  0:sx=80:sy= 43:p=33 'UPPER BROKEN
  CASE 29 : xa=144:ya= 43:sx=80:sy= 50:p=33 'LOWER BROKEN
 END SELECT
END SUB

'BARREL
SUB ShowBarrel(num,s)
 SELECT CASE num
  CASE -30: xa=48:ya=224:sx=16:sy=16:p=38: AVA$="BARREL" 'AVATAR
  CASE 30 : xa= 0:ya=  0:sx=58:sy=69:p=38 'OK
  CASE 31 : xa= 0:ya= 69:sx=59:sy=42:p=38:s=7 'UPPER BROKEN - NOT USED
  CASE 32 : xa= 0:ya= 69:sx=59:sy=42:p=38:s=4 'LOWER BROKEN
 END SELECT
END SUB

'DUSTBIN
SUB ShowDustbin(num,s)
 SELECT CASE num
  CASE -33: xa= 0:ya=224:sx=16:sy=16:p=38: AVA$="DUSTBIN" 'AVATAR
  CASE 33 : xa=58:ya=  0:sx=42:sy=54:p=38 'OK
  CASE 34 : xa=59:ya= 54:sx=45:sy=56:p=38 'SMASHED
 END SELECT
END SUB

'TIRES 
SUB ShowTires(num,s)
 SELECT CASE num
  CASE -35: xa= 16:ya=224:sx=16:sy=16:p=38: AVA$="TIRES" 'AVATAR
  CASE 35 : xa=104:ya=  0:sx=48:sy=55:p=38 'OK
  CASE 36 : xa=105:ya= 56:sx=44:sy=17:ty= 8:p=38 'NORMAL TIRE
  CASE 37 : xa=105:ya= 73:sx=44:sy=31:      p=38 'ALMOST ROTATED TIRE
  CASE 38 : xa=152:ya=  0:sx=39:sy=30:tx=-8:p=38 'INCLINED TIRE
 END SELECT
END SUB

'FREIGHT
SUB ShowFreight(num,s)
 SELECT CASE num
  CASE -39: xa= 48:ya=224:sx=16:sy=16:p=38: AVA$="FREIGHT" 'AVATAR
  CASE 39 : xa=224:ya=  0:sx=80:sy=92:p=33 'OK
  CASE 40 : xa=240:ya= 92:sx=80:sy=40:p=33 'LOWER BROKEN
 END SELECT
END SUB

'BILLBOARD
SUB ShowBillboard(num,s)
 SELECT CASE num
  CASE -41: xa= 64:ya=224:sx=16:sy= 16:p=38: AVA$="BILLBOARD" 'AVATAR
  CASE 41 : xa=  0:ya= 64:sx=64:sy= 94:p=33:'OK - LIGHT 1
            xxt=xs-(sx+TX)\2: yyt=ys-sy+TY: BLIT 311,0,xxt+49,yyt+1,9,78,p,s            
  CASE 42 : xa=  0:ya= 64:sx=64:sy= 94:p=33:'OK - LIGHT 2
            xxt=xs-(sx+TX)\2: yyt=ys-sy+TY: BLIT 311,4,xxt+49,yyt+1,9,78,p,s            
  CASE 43 : xa=  0:ya=  0:sx=64:sy= 64:p=33 'LOWER BROKEN
 END SELECT
END SUB

'POINTS -------------------------------------------------------------------------------

SUB ShowPoints(num,s)
 SELECT CASE num
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
 END SELECT
END SUB

'FOOD ---------------------------------------------------------------------------------

SUB ShowFood(num,s)
 SELECT CASE num
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
  CASE  136 : xa= 92:ya=157:sx=30:sy=13 :p=38 
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
 END SELECT
END SUB

'BROKEN PIECES ------------------------------------------------------------------------

'PIECES OF GLASS
SUB ShowPiecesGlass(num,s)
 SELECT CASE num
  CASE 200 : xa=206:ya=210:sx=26:sy=30:p=38:      ty=-1:s=4
  CASE 201 : xa=188:ya=207:sx=17:sy=33:p=38:tx=-6      :s=4
  CASE 202 : xa=216:ya=173:sx=10:sy=37:p=38:tx= 6:ty= 2:s=4
  CASE 203 : xa=188:ya=207:sx=17:sy=33:p=38:tx=-6      :s=5
  CASE 204 : xa=206:ya=210:sx=26:sy=30:p=38:      ty=-1:s=5
  CASE 205 : xa=188:ya=207:sx=17:sy=33:p=38:tx=-6      :s=5
  CASE 206 : xa=216:ya=173:sx=10:sy=37:p=38:tx= 6:ty= 2:s=4
  CASE 207 : xa=206:ya=210:sx=26:sy=30:p=38:      ty=-1:s=4
 END SELECT
END SUB

'PIECES OF WOOD
SUB ShowPiecesWood(num,s)
 SELECT CASE num
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
END SUB

'MOLOTOV
SUB ShowMolotov(num,s)
 SELECT CASE num
  CASE 250 : xa=300:ya=192:sx=20:sy=20:p=38                   '  | 1
  CASE 251 : xa=188:ya=185:sx=27:sy=22:p=38                   '  / 2
  CASE 252 : xa=231:ya=116:sx=20:sy=20:p=38                   '  - 3
  CASE 253 : xa=209:ya=109:sx=22:sy=27:p=38                   '  \ 4
  CASE 254 : xa=300:ya=192:sx=20:sy=20:p=38:if s=4 then s=7 else if s=5 then s=6 '  | 5
  CASE 255 : xa=188:ya=185:sx=27:sy=22:p=38:if s=4 then s=7 else if s=5 then s=6 '  / 6
  CASE 256 : xa=231:ya=116:sx=20:sy=20:p=38:if s=4 then s=7 else if s=5 then s=6 '  - 7
  CASE 257 : xa=209:ya=109:sx=22:sy=27:p=38:if s=4 then s=7 else if s=5 then s=6 '  \ 8
 END SELECT
END SUB

'MOLOTOV FIRE
SUB ShowMolotovFire(num,s)
 SELECT CASE num
  CASE 260 : xa=64:ya=128:sx=14:sy=24:p=33
  CASE 261 : xa=78:ya=128:sx=23:sy=32:p=33
  CASE 262 : xa= 1:ya=163:sx=30:sy=57:p=33
  CASE 263 : xa=64:ya=128:sx=14:sy=24:p=33
  CASE 264 : xa=32:ya=158:sx=31:sy=62:p=33
  CASE 265 : xa=64:ya=128:sx=14:sy=24:p=33
  CASE 266 : xa= 1:ya=163:sx=30:sy=57:p=33
  CASE 267 : xa=64:ya=128:sx=14:sy=24:p=33
  CASE 268 : xa=32:ya=158:sx=31:sy=62:p=33
  CASE 269 : xa=78:ya=128:sx=14:sy=24:p=33
 END SELECT
END SUB

'BLOOD
SUB ShowBlood(num,s)
 SELECT CASE num
  CASE 270 : xa= 0:ya=223:sx= 7:sy=13:p=33:tx=16
  CASE 271 : xa= 8:ya=223:sx=12:sy=14:p=33:tx=32:ty=-8
  CASE 272 : xa=23:ya=221:sx=19:sy=19:p=33:tx=48:ty=-16
 END SELECT
END SUB

'KATANA
SUB ShowKatana(num,s)
 SELECT CASE num
  CASE -280: xa= 80:ya=224:sx=16:sy=16:p=38: AVA$="KATANA" 'AVATAR
  CASE 280 : xa=258:ya= 21:sx=62:sy=15:p=38       '_ GROUND
  CASE 281 : xa=208:ya= 31:sx= 9:sy=78:p=38:ty=34 '| 1
  CASE 282 : xa=262:ya= 65:sx=58:sy=31:p=38:ty=15 '/ 2
  CASE 283 : xa=242:ya=  0:sx=78:sy= 9:p=38       '- 3
  CASE 284 : xa=263:ya= 36:sx=57:sy=29:p=38:ty=15 '\ 4
  CASE 285 : xa=208:ya= 31:sx= 9:sy=78:p=38:ty=34:if s=4 then s=7 else if s=5 then s=6 '| 5
  CASE 286 : xa=262:ya= 65:sx=58:sy=31:p=38:ty=15:if s=4 then s=7 else if s=5 then s=6 '/ 6
  CASE 287 : xa=242:ya=  0:sx=78:sy= 9:p=38:      if s=4 then s=7 else if s=5 then s=6 '- 7
  CASE 288 : xa=263:ya= 36:sx=57:sy=29:p=38:ty=15:if s=4 then s=7 else if s=5 then s=6 '\ 8
  CASE 289 : xa=262:ya=  0:sx=58:sy= 9:p=38       '- 3 
 END SELECT
END SUB

'KNIFE
SUB ShowKnife(num,s)
 SELECT CASE num
  CASE -290: xa= 80:ya=224:sx=16:sy=16:p=38: AVA$="KNIFE" 'AVATAR
  CASE 290 : xa=191:ya=  0:sx=27:sy= 8:p=38      '_ GROUND
  CASE 291 : xa=201:ya=162:sx= 8:sy=15:p=38      '| 1
  CASE 292 : xa=248:ya= 86:sx=14:sy=14:p=38      '/ 2
  CASE 293 : xa=246:ya= 65:sx=16:sy= 9:p=38      '- 3
  CASE 294 : xa=247:ya= 74:sx=15:sy=12:p=38      '\ 4
  CASE 295 : xa=201:ya=162:sx= 8:sy=15:p=38:ty=7:if s=4 then s=7 else if s=5 then s=6 '| 5
  CASE 296 : xa=248:ya= 86:sx=14:sy=14:p=38:ty=7:if s=4 then s=7 else if s=5 then s=6 '/ 6
  CASE 297 : xa=246:ya= 65:sx=16:sy= 9:p=38:     if s=4 then s=7 else if s=5 then s=6 '- 7
  CASE 298 : xa=247:ya= 74:sx=15:sy=12:p=38:     if s=4 then s=7 else if s=5 then s=6 '\ 8
  CASE 299 : xa=146:ya=149:sx=23:sy= 8:p=38 '- 'THROW
  CASE 310 : xa=201:ya=162:sx= 8:sy=23:p=38      '| 1 - FULL
 END SELECT
END SUB

'PIPE
SUB ShowPipe(num,s)
 SELECT CASE num
  CASE -300: xa= 96:ya=224:sx=16:sy=16:p=38: AVA$="PIPE" 'AVATAR
  CASE 300 : xa=240:ya=  9:sx=80:sy=12:p=38       '_ GROUND
  CASE 301 : xa=217:ya= 29:sx= 8:sy=80:p=38:ty=40 '| 1
  CASE 302 : xa=209:ya=136:sx=62:sy=33:p=38:ty=16 '/ 2
  CASE 303 : xa=240:ya=102:sx=80:sy= 8:p=38       '- 3
  CASE 304 : xa=271:ya=116:sx=49:sy=51:p=38:ty=25 '\ 4
  CASE 305 : xa=217:ya= 29:sx= 8:sy=80:p=38:ty=40:if s=4 then s=7 else if s=5 then s=6 '| 5
  CASE 306 : xa=209:ya=136:sx=62:sy=33:p=38:ty=16:if s=4 then s=7 else if s=5 then s=6 '/ 6
  CASE 307 : xa=240:ya=102:sx=80:sy= 8:p=38:      if s=4 then s=7 else if s=5 then s=6 '- 7
  CASE 308 : xa=271:ya=116:sx=49:sy=51:p=38:ty=25:if s=4 then s=7 else if s=5 then s=6 '\ 8
  CASE 309 : xa=259:ya=102:sx=61:sy= 8:p=38:tx=-4:if s=4 then s=7 else if s=5 then s=6 '- 7
 END SELECT
END SUB
