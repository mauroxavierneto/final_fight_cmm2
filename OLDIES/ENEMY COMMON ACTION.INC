   'ENEMY IS DEAD ---------------------------------------------------------------------
   CASE 100: EAniSpd(T)=0: IF EAN(T)>60 THEN EAN(T)=50: INC STE(T) ' FLASH BODY AGAIN
   CASE 101: IF EAN(T)>60 THEN EEnergy(T)=-98: STE(T)=0: RealY(T)=999: Exit Sub 'REMOVE DEAD ENEMY

   'GRAPPLED BY A PLAYER --------------------------------------------------------------
   CASE 120 TO 170:
    'RESIST IF GRAPPLED FOR A WHILE WITHOUT BEING ATTACK
    EAN(T)=22
    INC STE(T)
    FOR I=1 TO MAXPL 
     IF PlType(I)=3 AND SB THEN INC STE(T),-1 'HAGGAR KEEP GRAPPLE FOR MORE TIME
     'RELEASE IF PLAYER USE SPECIAL
     IF Special(I)=1 THEN STE(T)=170: Grap(I)=0: GrapE(I)=0: Kick(I)=0: Punch(I)=1
     IF GrapE(I)=T THEN
      EX(T)=X(I)+(SIDE(I)=4)*8-(SIDE(I)=5)*8: RealY(T)=RealY(I)+4-(PlType(I)=3)*18
      IF PlType(I)=3 THEN
       EY(T)=Y(I): ESJMP(T)=0: ESPDY(T)=0
       INC EX(T),(SIDE(I)=4)*(32-(AN(I)=32)*24)-(SIDE(I)=5)*(32-(AN(I)=32)*24)
       IF AN(I)=32 THEN EAN(T)=21: EY(T)=Y(I)-10
       'PILE DRIVER ADJUST ENEMY POSITION AND SIDE
       SELECT CASE Jump(I)
        CASE 1,2,9 TO 10,21,22,29 TO 30: EY(T)=Y(I)+8
        CASE 38: ESIDE(T)=(SIDE(I)=4)*7+(SIDE(I)=5)*6        
        CASE 33:
         STE(T)=60
         ESPDX(T)=(SIDE(I)=4)*6-(SIDE(I)=5)*6: RealY(T)=RealY(I)
         EAniDelay(T)=0:EAniSpd(T)=1: ESJMP(T)=-6: ESPDY(T)=-6
         Grap(I)=0: GrapE(I)=0: Kick(I)=0: Punch(I)=1
         Exit Sub
       END SELECT
      ENDIF
      IF STE(T)>=170 THEN
       STE(T)=52: EAniDelay(T)=0:EAniSpd(T)=3: ESJMP(T)=-3: ESPDY(T)=-3: RealY(T)=RealY(I)
       Grap(I)=0: GrapE(I)=0: Combo(I)=0: Punch(I)=2: AniDelay(I)=0: AniSpd(I)=0
      ENDIF
     ENDIF
    NEXT I

   'RETURN TO THE ORIGINAL STATE IF SOMETHING GOES WRONG ON GAPPLE
   CASE 171 TO 172:
    STE(T)=20: EAniDelay(T)=0: EAniSpd(T)=3: ESJMP(T)=0: ESPDY(T)=0




