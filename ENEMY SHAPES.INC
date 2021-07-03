' --- GENERAL SHAPES / PSEUDO-SPRITES ROUTINES FOR THE ENEMIES ---

' LOAD ENEMY SHAPE NUMBER, ADJUST X,Y AND SIDE, THEN WRITE ON PAGE AND GET COLLISION WITH COLOR
' LAST PARAMETER FORCE SET THE OBJECT TO BE SHOWED OR ONLY TO GET COLLISION
' SHOW = -1 TO READ COLLISION, NO SHAPE IS DISPLAYED
' SHOW =  0 TO WRITE COLLISION AND NO SHAPE IS DISPLAYED
' SHOW =  1 TO SHOW SHAPE ONLY, DON'T WRITE OR READ COLLISION
' SHOW >  1 TO WRITE COLLISION BLOCK TO AN SELECT PAGE
SUB PutEnemy(xs,ys,num,s,Who,pl,SHOW)
 local I,T,xa,ya,xb,yb,sbx,sby,sx,sy,p,pb,tx,ty,tbx,tby,xt,yt,xxt,yyt,xp,yp

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
 'xp,yp  - ADJUST ATTACK COLLISION 

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
    'BURNING
    CASE 80 : xa=  0:ya=993:sx=121:sy=72
    CASE 81 : xa=121:ya=993:sx=123:sy=72
    CASE 82 : xa=244:ya=993:sx=121:sy=72

   END SELECT 'END BRED / JAKE / DUG
   INC ya,(Who-4)*93
   INC yb,(Who-4)*93


  CASE 7, 8: 'J / TWO P -----------------------------------------------------------------
   SELECT CASE num
    'ENERGY AVATAR
    CASE 99 : xa=0:ya=504:sx=59:sy=16:tx=-14
    'STOPPED
    CASE  9 : xa=163:ya=508:sx=64:sy=91
    'WALKING (ALWAYS WITH ATTENTION)
    CASE 10 : xa=163:ya=508:sx=64:sy=49:tx=0:ty=0:xb=227:yb=504:sbx=38:sby=42:tbx=6:tby=0
    CASE 11 : xa=163:ya=508:sx=64:sy=49:tx=0:ty=0:xb=227:yb=546:sbx=30:sby=43:tbx=6:tby=0
    CASE 12 : xa=163:ya=508:sx=64:sy=49:tx=0:ty=0:xb=227:yb=504:sbx=38:sby=42:tbx=6:tby=0
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
    'BURNING
    CASE 80 : xa=  0:ya=993:sx=121:sy=72
    CASE 81 : xa=121:ya=993:sx=123:sy=72
    CASE 82 : xa=244:ya=993:sx=121:sy=72

   END SELECT 'END J / TWO P
   INC xa,(who-7)*796
   INC xb,(who-7)*796


  CASE 9, 10: 'AXL / SLASH --------------------------------------------------------------
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
    CASE 22 : xa=911:ya=  6:sx=64:sy=100:tx=0:yp=20 'IN THE FACE
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
    'BURNING
    CASE 80 : xa=  0:ya=993:sx=121:sy=72
    CASE 81 : xa=121:ya=993:sx=123:sy=72
    CASE 82 : xa=244:ya=993:sx=121:sy=72

   END SELECT 'END AXL / SLASH
   INC ya,(who-9)*107
   INC yb,(who-9)*107


  CASE 11 TO 12: 'HOLLY WOOD / EL GADO ----------------------------------------------------
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
   INC ya,(who-11)*100
   INC yb,(who-11)*100


  CASE 13: 'HOLLY WOOD MOLOTOV ---------------------------------------------------------
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


  CASE 14 TO 16: 'BILL BILL / G. ORIBER / WONG WHO --------------------------------------
   SELECT CASE num
    'ENERGY AVATAR
    CASE 99 : xa=1363:ya=838:sx=91:sy=16:tx=-cint(sx/2)
    'WALKING
    CASE  0 : xa=1288:ya=648:sx=68:sy=53:tx=0:ty=10:xb=1266:yb=599:sbx=77:sby=49:tbx= 2:tby=0
    CASE  1 : xa=1288:ya=648:sx=68:sy=53:tx=0:ty=10:xb=1343:yb=599:sbx=46:sby=49:tbx=10:tby=0
    CASE  2 : xa=1288:ya=648:sx=68:sy=53:tx=0:ty=10:xb=1418:yb=651:sbx=53:sby=49:tbx= 4:tby=0
    CASE  3 : xa=1288:ya=648:sx=68:sy=53:tx=0:ty=10:xb=1397:yb=599:sbx=49:sby=52:tbx= 6:tby=0
    'START TO RUN
    CASE  4 : xa=1251:ya=692:sx=84:sy=89:tx=0:ty=6
    'RUNNING
    CASE  5 : xa=1535:ya=681:sx=64:sy=36:tx=-12:ty=6:xb=1507:yb=717:sbx=92:sby=36:tbx=0:tby=0
    CASE  6 : xa=1535:ya=681:sx=64:sy=36:tx=-14:ty=4:xb=1460:yb=717:sbx=47:sby=38:tbx=0:tby=0
    CASE  7 : xa=1535:ya=681:sx=64:sy=36:tx=-12:ty=8:xb=1471:yb=681:sbx=64:sby=36:tbx=0:tby=0
    CASE  8 : xa=1535:ya=681:sx=64:sy=36:tx=- 8:ty=4:xb=1413:yb=700:sbx=47:sby=38:tbx=0:tby=0
    'KICKING
    CASE 16 : xa=1261:ya=781:sx=75:sy=52:tx=  0:ty=88:xb=1446:yb=599:sbx=60:sby=49:tbx=44:tby=-40
    CASE 17 : xa=1506:ya=599:sx=93:sy=82:tx=-16:ty=94:xb=1446:yb=599:sbx=60:sby=49:tbx=40:tby=-46
    CASE 18 : xa=1261:ya=781:sx=75:sy=52:tx=  0:ty=88:xb=1446:yb=599:sbx=60:sby=49:tbx=44:tby=-40
    'HURT
    CASE 21 : xa=1356:ya=651:sx=57:sy=80:tx=0 'IN THE STOMACH
    CASE 22 : xa=1454:ya=756:sx=77:sy=86:tx=0 'IN THE FACE

    'FALLING
    CASE 23 : xa=1353:ya=738:sx=101:sy=63:tx=5:ty=-20 'FALLING DOWN
    CASE 24,50,52,54,56,58,60:
              xa=1337:ya=801:sx=117:sy=37:tx=5        'LYING ON THE FLOOR / DEAD
    'GETTING UP
    CASE 25:  xa= 1531:ya=753:sx= 68:sy= 53:tx=0
    'BURNING
    CASE 80 : xa=  0:ya=993:sx=121:sy=72
    CASE 81 : xa=121:ya=993:sx=123:sy=72
    CASE 82 : xa=244:ya=993:sx=121:sy=72

   END SELECT 'BILL BILL / G. ORIBER / WONG WHO
   INC ya,(Who-14)*255
   INC yb,(Who-14)*255


  CASE 17 TO 18: 'POISON / ROXY ---------------------------------------------------------
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
    CASE 80 : xa=  0:ya=993:sx=121:sy=72
    CASE 81 : xa=121:ya=993:sx=123:sy=72
    CASE 82 : xa=244:ya=993:sx=121:sy=72

   END SELECT 'END POISON / ROXY
   INC ya,(Who-17)*94
   INC yb,(Who-17)*94

  CASE 80,81: 'DAMND / DAMND FROM THE INTRO ROUND 1-1 -----------------------------------
   SELECT CASE num
    'ENERGY AVATAR
    CASE 99 : xa=2:ya=1084:sx=60:sy=16:tx=-16
    'STOPPED / WALKING WITH JESSICA (ROUND 1-1)
    CASE  0,100: xa=423:ya=1083: sx=86: sy=61: tx=-4: ty= 13:
                  xb=192:yb=1083:sbx=73:sby=61:tbx= 0:tby=  0
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
    CASE 10,110: xa=995:ya=1085: sx=86: sy=61: tx=-4: ty= 13:
                   xb=192:yb=1083:sbx=73:sby=61:tbx= 0:tby=  0
    CASE 11,111: xa=505:ya=1144: sx=86: sy=54: tx=-4: ty= 13:
                   xb=192:yb=1083:sbx=73:sby=61:tbx= 0:tby=  0
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



