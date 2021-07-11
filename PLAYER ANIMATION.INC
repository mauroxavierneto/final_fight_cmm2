
' --- GENERAL PLAYERS ANIMATION ROUTINES ---

SUB PlayerAnimation(PL)

 'IS ANY PLAYER HURTED? (THE SEQUENCE IS THE SAME FOR ALL) -----------------------------------
 If PHurted(PL)>0 then

  'DROP WEAPON
  DropWeapon(PL)
   
  If HCombo(PL)>100 OR (HCombo(PL)>0 and Jump(PL)>0) then HCombo(PL)=0: PHurted(PL)=18
  INC PHurted(PL),-1
  Kick(PL)=0: Punch(PL)=0: Hitting(PL)=0: GrapE(PL)=0: Grap(PL)=0: Combo(PL)=0
  TRT=5

  SELECT CASE PHurted(PL)
   CASE  0: 
    AniDelay(PL)=0: PHurted(PL)=0
    AN(PL)= 0: AniSpd(PL)=2: MVLR(PL)=0: Jump(PL)=0 : JumpY(PL)=0: JumpX(PL)=0
   CASE  1: 'PUNCHED
    AN(PL)=39: AniSpd(PL)=6: AniDelay(PL)=0: MVLR(PL)=0: Jump(PL)=0
    InsertHit(XH(PL),YH(PL),1)
    InsertWait(PL,WhoE(PL),3)
   
   CASE  9: 'FALLING HURTED SEQUENCE      
    AN(PL)=0: PHurted(PL)=0: AniSpd(PL)=5: AniDelay(PL)=0: Jump(PL)=1

   CASE 10: 'STANDING
    AN(PL)=43: AniSpd(PL)=10: AniDelay(PL)=0

   CASE 11: 'TRY TO GET UP
    AN(PL)=42: AniSpd(PL)=10: AniDelay(PL)=0
    MVLR(PL)=0: JumpY(PL)=0: JumpX(PL)=0: Jump(PL)=98
 
   CASE 12: 'LAST FALLING 
    AN(PL)=41: AniSpd(PL)=0: AniDelay(PL)=0: Jump(PL)=98: INC PHurted(PL)
    IF Y(PL)+RealY(PL)>=RealY(PL) THEN INC PHurted(PL),-1
    'DEAD
    IF Energy(PL)<=0 THEN PHurted(PL)=100

   CASE 13: 'HIT THE FLOOR AGAIN
    AN(PL)=41: AniSpd(PL)=4: AniDelay(PL)=0: JumpY(PL)=-4: Jump(PL)=98
    BURNED(PL)=0
    IF SIDE(PL)=4 THEN JumpX(PL)=-TRT*0.3 else JumpX(PL)=TRT*0.3
    'SOUND / READ COLLISION TO MAKE SMOKES
    PLAY_SAMPLE 3,PL
    PutPlayer(X(PL),RealY(PL)+Y(PL),AN(PL),Side(PL),PlType(PL),PL,-2)
    InsertHit(XTHit-10-RND*10,YTHit,2) 'SMOKE
    InsertHit(XTHit+10+RND*10,YTHit,2)

   CASE 14: 'FALLING AGAIN
    AN(PL)=41: AniSpd(PL)=0: AniDelay(PL)=0: Jump(PL)=98: INC PHurted(PL)
    IF Y(PL)+RealY(PL)>=RealY(PL) THEN INC PHurted(PL),-1
    IF SIDE(PL)=4 THEN JumpX(PL)=-TRT*0.6 else JumpX(PL)=TRT*0.6

   CASE 15: 'HIT THE FLOOR 
    AN(PL)=41: AniSpd(PL)=4: AniDelay(PL)=0: JumpY(PL)=-6: Jump(PL)=98
    BURNED(PL)=0
    IF SIDE(PL)=4 THEN JumpX(PL)=-TRT*0.3 else JumpX(PL)=TRT*0.3
    'SOUND / READ COLLISION TO MAKE SMOKES
    PLAY_SAMPLE 3,PL
    PutPlayer(X(PL),RealY(PL)+Y(PL),AN(PL),Side(PL),PlType(PL),PL,-2)
    InsertHit(XTHit-10-RND*10,YTHit,2) 'SMOKE
    InsertHit(XTHit+10+RND*10,YTHit,2)

   CASE 16: 'FALLING
    AN(PL)=40: AniSpd(PL)=0: AniDelay(PL)=0: Jump(PL)=98: INC PHurted(PL)

    IF BURNED(PL) THEN
     INC BURNED(PL): IF BURNED(PL)>3 THEN BURNED(PL)=1
     AN(PL)=79+BURNED(PL)
    ENDIF

    IF Y(PL)+RealY(PL)>=RealY(PL) THEN INC PHurted(PL),-1

   CASE 17: 'START FALLING
    IF SIDE(PL)>=6 THEN INC SIDE(PL),-2
    AN(PL)=40: AniSpd(PL)=0: AniDelay(PL)=0: Jump(PL)=98: JumpY(PL)=-8
    InsertHit(XH(PL),YH(PL),1)
    InsertWait(PL,WhoE(PL),3)
    IF SIDE(PL)=4 THEN JumpX(PL)=-TRT else JumpX(PL)=TRT
    'DEAD SOUND
    IF Energy(PL)<=0 THEN 
     SELECT CASE PlType(PL)
      CASE    GUY: PLAY_SAMPLE  8,PL,25000,9999
      CASE   CODY: PLAY_SAMPLE  8,PL,,9999
      CASE HAGGAR: PLAY_SAMPLE 22,PL,,9999
     END SELECT
    ENDIF

   CASE 70: 'FALLING FROM THE SKY
    INC PHurted(PL): MV=0
    AN(PL)=27
    'KO ALL ENEMIES AND GET UP PLAYER
    IF Y(PL)>=0 THEN
     PLAY_SAMPLE 3,PL,,9999: PLAY_SAMPLE 3,3,,9999: PLAY_SAMPLE 3,4,,9999
     KillEnemies(0,0): AN(PL)=42: PHurted(PL)=11: MV=1 
    ENDIF

   CASE 71: 'RESET - FALLING FROM THE SKY
    INC PLIVE(PL),-1: AniSpd(PL)=0: AniDelay(PL)=1
    IF PLIVE(PL)>=0 THEN Energy(PL)=110 ELSE PLIVE(PL)=0 'INSERT GAME OVER
    AN(PL)=27
    Y(PL)=-MM.VRES: JumpY(PL)=15: Jump(PL)=98: MV=0: JumpX(PL)=0

   CASE 72 TO 99: 'DEAD - FLASHING BODY
    AN(PL)=41
    Energy(PL)=0: MV=0: JumpX(PL)=0
    AniSpd(PL)=0: AniDelay(PL)=1

  END SELECT

 ENDIF 'END OF PLAYER HURTED SEQUENCES -------------------------------------------------------


 SELECT CASE PlType(PL)

  'GUY'S ANIMATION ---------------------------------------------------------------------------
  CASE 1:
   
   'GUY PUNCH / GRAPPLE / THROW --------------------------------------------------------------
   IF Punch(PL)>0 and Jump(PL)=0 then 

    INC Punch(PL),-1   
    SELECT CASE Punch(PL)

     CASE 200: 'GET AN ITEM
      AN(PL)=43: AniSpd(PL)=5: AniDelay(PL)=0
     CASE 199:
      AN(PL)= 0: AniSpd(PL)=2: AniDelay(PL)=0: Punch(PL)=0

     CASE 130: 'THROW ENEMY GRAPPLED - SOUND FIX
      AN(PL)=22: AniSpd(PL)=0: AniDelay(PL)=0: Grap(PL)=AN(PL)
      PLAY_SAMPLE 4,PL,,2000+Punch(PL)
     CASE 129: 'THROW ENEMY GRAPPLED
      AN(PL)=22: AniSpd(PL)=3: AniDelay(PL)=0: Grap(PL)=AN(PL)
     CASE 128: 'THROW ENEMY GRAPPLED - 2 
      AN(PL)=23: AniSpd(PL)=2: AniDelay(PL)=0: Grap(PL)=AN(PL)
     CASE 125: 'STOP THROW SEQUENCE
      AN(PL)=26: AniSpd(PL)=1: AniDelay(PL)=0: Grap(PL)=0: Punch(PL)=0: Jump(PL)=1: GrapE(PL)=0

     CASE 109: 'KICKING GRAPPLED ENEMY
      AN(PL)=21: AniSpd(PL)=3: AniDelay(PL)=0: Grap(PL)=AN(PL)
     CASE 105: 'STOP KICKING GRAPPLED ENEMY
      AN(PL)=20: AniSpd(PL)=10: AniDelay(PL)=0: Grap(PL)=AN(PL)
     CASE 101:
      Punch(PL)=110

     CASE 100: 'ENEMY GRAPPLED
      AN(PL)=20: AniSpd(PL)=5: AniDelay(PL)=0: Grap(PL)=AN(PL)
     CASE 30:
      Punch(PL)=1: Grap(PL)=0: GrapE(PL)=0

     'GUY PUNCHING SEQUENCE ----------------------------------------

     CASE 13: 'STARTING SECOND COMBO
       AN(PL)=15: AniSpd(PL)=3: AniDelay(PL)=0 
     CASE 12: 'LONG PUNCH (THIRD COMBO)
       AN(PL)=16: AniSpd(PL)=3: AniDelay(PL)=0
     CASE 11: 'ELBOW (FORTH COMBO)
       AN(PL)=17: AniSpd(PL)=3: AniDelay(PL)=0
     CASE 10: 'ELBOW PUNCH (FORTH COMBO)
       AN(PL)=18: AniSpd(PL)=3: AniDelay(PL)=0
     CASE 9: 'STARTING COMBO KICK
      AN(PL)=32: AniSpd(PL)=2: AniDelay(PL)=0: Combo(PL)=0
      INC X(PL),10*(SIDE(PL)=4)-10*(SIDE(PL)=5) 'PUSH PLAYER A LITTLE FORWARD
     CASE 8: 'STARTING COMBO KICK
      AN(PL)=33: AniSpd(PL)=2: AniDelay(PL)=0: Combo(PL)=0
     CASE 7: 'PRE-COMBO KICK SOUND LAG
      AN(PL)=34: AniSpd(PL)=2: AniDelay(PL)=0: PLAY_SAMPLE 15,3
      Combo(PL)=0: Hitting(PL)=0
     CASE 6: 'HIGH KICK COMBO
      AN(PL)=19: AniSpd(PL)=2: AniDelay(PL)=0: Combo(PL)=0: PLWait(PL)=0
     CASE 5: 'ALMOST NORMAL
      AN(PL)=36: AniSpd(PL)=2: AniDelay(PL)=0: Combo(PL)=0: PLWait(PL)=0
     CASE 4: 'RESET STATUS
      Punch(PL)=1: AniSpd(PL)=2: AniDelay(PL)=0
      INC X(PL),10*(SIDE(PL)=5)-10*(SIDE(PL)=4) 'RETURN PLAYER TO ORIGINAL COORDINATE

     CASE 3: 'PUNCHING (REPEAT 2X) / USING WEAPON
      AN(PL)=13: AniSpd(PL)=2: AniDelay(PL)=0
      IF WEAPON(PL)>0 THEN
       AN(PL)=70
       SELECT CASE Weapon(PL)
        CASE KATANA: AniSpd(PL)=6:  PLAY_SAMPLE 16,PL
        CASE KNIFE : AniSpd(PL)=7:  PLAY_SAMPLE 16,PL,30000
        CASE PIPE  : AniSpd(PL)=8: PLAY_SAMPLE 16,PL,19000
       END SELECT
      ENDIF
     CASE 2:
      AN(PL)=14: AniSpd(PL)=3: AniDelay(PL)=0
      IF Hitting(PL)>2 THEN INC Combo(PL): Hitting(PL)=5
      IF WEAPON(PL)>0 THEN       
       AN(PL)=71
       SELECT CASE Weapon(PL)
        CASE KATANA: AniSpd(PL)=5
        CASE KNIFE :
         AniSpd(PL)=6
         SpawnObject(X(PL)+(SIDE(PL)=4)*70-(SIDE(PL)=5)*70,RealY(PL),SIDE(PL)+KNIFE)
         WEAPON(PL)=0
        CASE PIPE  : AniSpd(PL)=8
       END SELECT
      ENDIF
     CASE 1:
      AN(PL)=13: AniSpd(PL)=2: AniDelay(PL)=0: IF Combo(PL)=2 THEN Punch(PL)=4
      IF WEAPON(PL)>0 THEN AN(PL)=0: Combo(PL)=0
     CASE 0:
      AN(PL)=0: AniSpd(PL)=3: AniDelay(PL)=0
    END SELECT

   ENDIF 'END OF GUY PUNCH / GRAPPLE / THROW SEQUENCES ---------------------------------------


   'GUY JUMPING / FIRE KICK JUMP -------------------------------------------------------------

   If Jump(PL)>0 and Phurted(PL)=0 then
    INC Jump(PL),-1

    'AIR KICK (NOT SPECIAL)
    IF (Jump(PL)>=2 and Jump(PL)<=29) and Kick(PL)=0 then
     IF KSHIFT AND (Kick(PL)=0) THEN
      Kick(PL)=1: Wait(PL)=4
      IF JumpX(PL)<>0 THEN Wait(PL)=15
      IF MVUD(PL)=1 AND Kick(PL)=1 THEN Kick(PL)=2: Wait(PL)=5
      IF Kick(PL)=1 THEN PLAY_SAMPLE 13,PL,,100
     ENDIF
    ENDIF

    ' JUMPING ANIMATION CONTROL
    SELECT CASE Jump(PL)
     ' SPECIAL
     CASE 50: AN(PL)=26: AniSpd(PL)=2: AniDelay(PL)=0: PLAY_SAMPLE 14,PL
     CASE 49: AN(PL)=32: AniSpd(PL)=2: AniDelay(PL)=0: JumpY(PL)=-11
     CASE 48: AN(PL)=33: AniSpd(PL)=2: AniDelay(PL)=0
     CASE 47: AN(PL)=34: AniSpd(PL)=2: AniDelay(PL)=0: INC JumpY(PL)
     CASE 46: AN(PL)=35: AniSpd(PL)=2: AniDelay(PL)=0
     CASE 45: AN(PL)=36: AniSpd(PL)=2: AniDelay(PL)=0: INC JumpY(PL)
     CASE 44: 'CHANGE SIDE
              AN(PL)=35: AniSpd(PL)=2: AniDelay(PL)=0
              IF SIDE(PL)=5 THEN SIDE(PL)=4 ELSE SIDE(PL)=5
     CASE 43: AN(PL)=34: AniSpd(PL)=2: AniDelay(PL)=0: INC JumpY(PL)
     CASE 42: 'CHANGE SIDE AGAIN
              AN(PL)=35: AniSpd(PL)=2: AniDelay(PL)=0: INC JumpY(PL)
              IF SIDE(PL)=5 THEN SIDE(PL)=4 ELSE SIDE(PL)=5
     CASE 41: AN(PL)=36: AniSpd(PL)=2: AniDelay(PL)=0: INC JumpY(PL)
     CASE 40: AN(PL)=26: AniSpd(PL)=2: AniDelay(PL)=0: Jump(PL)=2: Punch(PL)=0
      
     ' VERTICAL JUMP
     CASE 30: AN(PL)=26: AniSpd(PL)=3: AniDelay(PL)=0
     CASE 29: AN(PL)=27: AniSpd(PL)=3: AniDelay(PL)=0: JumpY(PL)=-11
     CASE 25 TO 28: AN(PL)=27: AniSpd(PL)=1
     CASE 21 TO 24: AN(PL)=30: AniSpd(PL)=3
     CASE 18 TO 20: AN(PL)=27: AniSpd(PL)=1
     CASE 17: AN(PL)=26: AniSpd(PL)=3: AniDelay(PL)=0
     CASE 16: AN(PL)= 0: AniSpd(PL)=3: MVLR(PL)=0: JumpY(PL)=0: Jump(PL)=0

     ' JUMPING AHEAD
     CASE 15: AN(PL)=26: AniSpd(PL)=2: AniDelay(PL)=0 'STARTING TO JUMP
     CASE 14: AN(PL)=27: AniSpd(PL)=0: AniDelay(PL)=0: JumpY(PL)=-11
     CASE 9 TO 13: AN(PL)=27: AniSpd(PL)=0: AniDelay(PL)=0
     CASE 7 TO 8:
      AniSpd(PL)=2: AniDelay(PL)=0
      AN(PL)=24: IF JumpX(PL)>0 THEN SIDE(PL)=4 ELSE SIDE(PL)=5      
     CASE 6: AniSpd(PL)=3: AN(PL)=25: IF JumpX(PL)>0 THEN SIDE(PL)=7 ELSE SIDE(PL)=6
     CASE 5: AN(PL)=24: IF JumpX(PL)>0 THEN SIDE(PL)=7 ELSE SIDE(PL)=6
     CASE 4: AN(PL)=44: IF JumpX(PL)>0 THEN SIDE(PL)=4 ELSE SIDE(PL)=5
     CASE 3: AN(PL)=27: AniSpd(PL)=2: AniDelay(PL)=0
     CASE 2: AN(PL)=27: AniSpd(PL)=1: AniDelay(PL)=0
     CASE 1:
      AN(PL)=26: AniSpd(PL)=2: AniDelay(PL)=0: JumpX(PL)=0
      IF Special(PL)=1 THEN Special(PL)=0
     CASE 0: AN(PL)= 0: AniSpd(PL)=2: MVLR(PL)=0: JumpY(PL)=0: JumpX(PL)=0
    END SELECT

    IF Kick(PL)>0 then
     'KICK JUMP AHEAD
     if JumpX(PL)<>0 then
      if Jump(PL)>1 then 
       AN(PL)=30: IF JumpX(PL)>0 THEN SIDE(PL)=4 ELSE SIDE(PL)=5
       if Kick(PL)=2 then AN(PL)=31 'KNEE
       if Kick(PL)=1 then 
        if AN(PL)=2 then AN(PL)=27
        if Jump(PL)=2 then AN(PL)=27
       endif
      else
       Kick(PL)=0
      endif
     else
     'KICK VERTICAL JUMP
      if Jump(PL)>=18 and Jump(PL)<=29 then 
       AN(PL)=27
       if Jump(PL)>=22 and Jump(PL)<=25 and Kick(PL)>0 then AN(PL)=28
       'KICK ONLY IF NOT KNEE
       if Kick(PL)=2 and MVUD(PL)<=0 then AN(PL)=29
      else
       Kick(PL)=0
      endif
     endif
    ENDIF 'END OF GUY JUMPING / FIRE KICK JUMP -----------------------------------------------


   'CODY'S ANIMATION -------------------------------------------------------------------------
   CASE 2:
    
    'CODY PUNCH / GRAPPLE / THROW ------------------------------------------------------------
    IF Punch(PL)>0 and Jump(PL)=0 then 

     INC Punch(PL),-1   
     SELECT CASE Punch(PL)

      CASE 200: 'GET AN ITEM
       AN(PL)=43: AniSpd(PL)=5: AniDelay(PL)=0
      CASE 199: Punch(PL)=1

      CASE 130: 'THROW ENEMY GRAPPLED - SOUND FIX
       AN(PL)=22: AniSpd(PL)= 0: AniDelay(PL)=0: Grap(PL)=AN(PL)
       PLAY_SAMPLE 4,PL,,255
      CASE 129: 'THROW ENEMY GRAPPLED
       AN(PL)=22: AniSpd(PL)= 3: AniDelay(PL)=0: Grap(PL)=AN(PL)
      CASE 128: 'THROW ENEMY GRAPPLED - 2 
       AN(PL)=23: AniSpd(PL)= 2: AniDelay(PL)=0: Grap(PL)=AN(PL)
      CASE 125: 'STOP THROW SEQUENCE
       AN(PL)=26: AniSpd(PL)= 1: AniDelay(PL)=0: Grap(PL)=0: Punch(PL)=0: Jump(PL)=1: GrapE(PL)=0

      CASE 109: 'KICKING GRAPPLED ENEMY
       AN(PL)=21: AniSpd(PL)= 3: AniDelay(PL)=0: Grap(PL)=AN(PL)
      CASE 105: 'STOP KICKING GRAPPLED ENEMY
       AN(PL)=20: AniSpd(PL)=10: AniDelay(PL)=0: Grap(PL)=AN(PL)
      CASE 101:
       Punch(PL)=110

      CASE 100: 'ENEMY GRAPPLED
       AN(PL)=20: AniSpd(PL)= 5: AniDelay(PL)=0: Grap(PL)=AN(PL)
      CASE  30:
       Punch(PL)=1: Grap(PL)= 0: GrapE(PL)=0

      'CODY PUNCHING SEQUENCE -----------------------------------------------------------

      CASE  12: 'STARTING SECOND COMBO
       AN(PL)=15: AniSpd(PL)= 3: AniDelay(PL)=0 
      CASE  11: 'LONG PUNCH (THIRD COMBO)
       AN(PL)=16: AniSpd(PL)= 4: AniDelay(PL)=0
       If Hitting(PL)>3 THEN Hitting(PL)=5: INC Combo(PL)
      CASE  10: 'RETURNING TO MAKE THE UPPERCUT
       AN(PL)=15: AniSpd(PL)= 2: AniDelay(PL)=0
      CASE   9: 'UPPERCUT SOUND (LAG)
       AN(PL)=17: AniSpd(PL)= 1: AniDelay(PL)=0: Combo(PL)=0
       PLAY_SAMPLE 7,PL,,100
      CASE   8: 'PRE-UPPERCUT
       AN(PL)=18: AniSpd(PL)= 3: AniDelay(PL)=0: Combo(PL)=0
      CASE   7: 'UPPERCUT! - FORTH COMBO
       AN(PL)=19: AniSpd(PL)= 8: AniDelay(PL)=0: Combo(PL)=0
       PLAY_SAMPLE 7,PL,,100: Hitting(PL)=0
      CASE   6: 'BACK FROM UPPERCUT
       AN(PL)=18: AniSpd(PL)= 3: AniDelay(PL)=0: Combo(PL)=0
      CASE   5: 'ALMOST NORMAL
       AN(PL)=13: AniSpd(PL)= 2: AniDelay(PL)=0: Combo(PL)=0
      CASE   4: 'RESET STATUS
                  AniSpd(PL)= 2: AniDelay(PL)=0: Punch(PL)=1

      CASE   3: 'PUNCHING (REPEAT 2X)
       AN(PL)=13: AniSpd(PL)=2: AniDelay(PL)=0
       IF WEAPON(PL)>0 THEN
        AN(PL)=70
        SELECT CASE Weapon(PL)
         CASE KATANA: AniSpd(PL)=8: PLAY_SAMPLE 16,PL
         CASE KNIFE : AniSpd(PL)=4: PLAY_SAMPLE 16,PL,30000
         CASE PIPE  : AniSpd(PL)=8: PLAY_SAMPLE 16,PL,19000
        END SELECT
       ENDIF
      CASE   2:
       AN(PL)=14: AniSpd(PL)=3: AniDelay(PL)=0
       If Hitting(PL)>1 THEN INC Combo(PL)
       IF WEAPON(PL)>0 THEN       
        AN(PL)=71
        SELECT CASE Weapon(PL)
         CASE KATANA: AniSpd(PL)=4
         CASE PIPE  : AniSpd(PL)=8
         CASE KNIFE :
          AniSpd(PL)=4: GO=1
          'THROW KNIFE IF THERE ARE NO ENEMIES NEAR THE PLAYER
          FOR T=4 TO 9
           IF STE(T)>0 THEN
            IF EX(T)>X(PL)-(SIDE(PL)=5)*160 AND EX(T)<X(PL)+(SIDE(PL)=4)*160 THEN
             IF RealY(T)>RealY(PL)-8 AND RealY(T)<RealY(PL)+8 THEN GO=0
            ENDIF
           ENDIF
          NEXT T
          IF GO THEN
           SpawnObject(X(PL)+(SIDE(PL)=4)*70-(SIDE(PL)=5)*70,RealY(PL),SIDE(PL)+KNIFE): WEAPON(PL)=0
          ENDIF
        END SELECT
       ENDIF
      CASE   1:
       AN(PL)=13: AniSpd(PL)=2: AniDelay(PL)=0
       IF WEAPON(PL)>0 THEN AN(PL)=0: Combo(PL)=0
      CASE   0:
       AN(PL)= 0: AniSpd(PL)=3: AniDelay(PL)=0
     END SELECT
    ENDIF 'END OF CODY PUNCH / GRAPPLE / THROW SEQUENCES -------------------------------------


    'CODY JUMPING / FIRE KICK JUMP -----------------------------------------------------------
    If Jump(PL)>0 and Phurted(PL)=0 then
     INC Jump(PL),-1

     'AIR KICK (NOT SPECIAL)
     IF (Jump(PL)>=2 and Jump(PL)<=29) and Kick(PL)=0 then
      IF KSHIFT AND (Kick(PL)=0) THEN
       Kick(PL)=1: Wait(PL)=4
       IF JumpX(PL)<>0 THEN Wait(PL)=15
       IF MVUD(PL)=1 AND Kick(PL)=1 THEN Kick(PL)=2: Wait(PL)=5
       IF Kick(PL)=1 THEN PLAY_SAMPLE 5,PL,,100
      ENDIF
     ENDIF

     ' ANIMATION CONTROL
     SELECT CASE Jump(PL)
      ' SPECIAL
      CASE 50: AN(PL)=26: AniSpd(PL)=2: AniDelay(PL)=0: PLAY_SAMPLE 6,PL
      CASE 49: AN(PL)=27: AniSpd(PL)=2: AniDelay(PL)=0: JumpY(PL)=-11
      CASE 48: AN(PL)=32: AniSpd(PL)=2: AniDelay(PL)=0
      CASE 47: AN(PL)=33: AniSpd(PL)=2: AniDelay(PL)=0
      CASE 46: AN(PL)=34: AniSpd(PL)=3: AniDelay(PL)=0
      CASE 45: AN(PL)=35: AniSpd(PL)=2: AniDelay(PL)=0
      CASE 44: AN(PL)=36: AniSpd(PL)=3: AniDelay(PL)=0
      CASE 43: AN(PL)=37: AniSpd(PL)=2: AniDelay(PL)=0
      CASE 42:
       AN(PL)=33: AniSpd(PL)=3: AniDelay(PL)=0: Jump(PL)=3: Punch(PL)=0
       IF SIDE(PL)=5 THEN SIDE(PL)=4 ELSE SIDE(PL)=5
      ' VERTICAL JUMP
      CASE 30: AN(PL)=26: AniSpd(PL)=3: AniDelay(PL)=0
      CASE 29: AN(PL)=27: AniSpd(PL)=0: AniDelay(PL)=0: JumpY(PL)=-10
      CASE 24 TO 28: AN(PL)=27: AniSpd(PL)=1
      CASE 21 TO 23: AN(PL)=30: AniSpd(PL)=3
      CASE 18 TO 20: AN(PL)=27: AniSpd(PL)=2
      CASE 17: AN(PL)=26: AniSpd(PL)=3: AniDelay(PL)=0
      CASE 16: AN(PL)= 0: AniSpd(PL)=3: MVLR(PL)=0: JumpY(PL)=0: Jump(PL)=0
      ' JUMPING AHEAD
      CASE 15: AN(PL)=26: AniSpd(PL)=1: AniDelay(PL)=0
      CASE 14: AN(PL)=29: AniSpd(PL)=2: AniDelay(PL)=0: JumpY(PL)=-11
      CASE 9 TO 13: AN(PL)=29: AniSpd(PL)=0: AniDelay(PL)=0
      CASE 7 TO 8:
       AniSpd(PL)=2: AniDelay(PL)=0
       AN(PL)=24: IF JumpX(PL)>0 THEN SIDE(PL)=4 ELSE SIDE(PL)=5      
      CASE 6: AN(PL)=25: IF JumpX(PL)>0 THEN SIDE(PL)=7 ELSE SIDE(PL)=6
      CASE 5: AN(PL)=24: IF JumpX(PL)>0 THEN SIDE(PL)=7 ELSE SIDE(PL)=6
      CASE 4: AN(PL)=25: IF JumpX(PL)>0 THEN SIDE(PL)=4 ELSE SIDE(PL)=5
      CASE 3: AN(PL)=29: AniSpd(PL)=4: AniDelay(PL)=0
      CASE 2: 
       AN(PL)=30: AniSpd(PL)=1: AniDelay(PL)=0
       IF Special(PL)=1 THEN Special(PL)=0: IF SIDE(PL)=5 THEN SIDE(PL)=4 ELSE SIDE(PL)=5
      CASE 1: AN(PL)=26: AniSpd(PL)=3: AniDelay(PL)=0: JumpX(PL)=0
      CASE 0: AN(PL)= 0: AniSpd(PL)=1: MVLR(PL)=0: JumpY(PL)=0: JumpX(PL)=0
     END SELECT

     IF Kick(PL)>0 then
      'KICK JUMP AHEAD
      if JumpX(PL)<>0 then
       if Jump(PL)>1 then 
        AN(PL)=34: IF JumpX(PL)>0 THEN SIDE(PL)=4 ELSE SIDE(PL)=5
        if Kick(PL)=2 then AN(PL)=31
        if Kick(PL)=1 then 
         if AN(PL)=2 then AN(PL)=33
         if Jump(PL)=2 then AN(PL)=33
        endif
       else
        Kick(PL)=0
       endif
      else
      'KICK VERTICAL JUMP
       if Jump(PL)>=18 and Jump(PL)<=29 then 
        AN(PL)=29
        if Kick(PL)=2 then AN(PL)=30
       else
        Kick(PL)=0
       endif
      endif
     ENDIF

    ENDIF 'END OF CODY JUMPING / FIRE KICK JUMP SEQUENCES ------------------------------------


   'HAGGAR'S ANIMATION -----------------------------------------------------------------------
   CASE 3:


    'HAGGAR PUNCH / GRAPPLE / THROW ----------------------------------------------------------
    IF Punch(PL)>0 and Jump(PL)=0 then 

     INC Punch(PL),-1   
     SELECT CASE Punch(PL)

      CASE 200: 'GET AN ITEM
       AN(PL)=43: AniSpd(PL)=5: AniDelay(PL)=0
      CASE 199: Punch(PL)=1

      CASE 130: 'SUPLEX ENEMY GRAPPLED - SOUND FIX
       AN(PL)=22: AniSpd(PL)= 0: AniDelay(PL)=0: Grap(PL)=AN(PL)
       PLAY_SAMPLE 20,PL,,255
      CASE 129: 'SUPLEX ENEMY GRAPPLED
       AN(PL)=22: AniSpd(PL)= 4: AniDelay(PL)=0: Grap(PL)=AN(PL)
      CASE 128: 'SUPLEX ENEMY GRAPPLED - 2 
       AN(PL)=23: AniSpd(PL)= 3: AniDelay(PL)=0: Grap(PL)=AN(PL): PLAY_SAMPLE 3,3,,255: SHAKE=10
      CASE 125: 'STOP SUPPLEX SEQUENCE
       AN(PL)=43: AniSpd(PL)= 3: AniDelay(PL)=0
      CASE 124: 'STOP SUPPLEX SEQUENCE
       AN(PL)=43: AniSpd(PL)= 3: AniDelay(PL)=0: Grap(PL)=0: Punch(PL)=0: Jump(PL)=1: GrapE(PL)=0

      CASE 109: 'HEAD BANG GRAPPLED ENEMY
       AN(PL)=21: AniSpd(PL)= 3: AniDelay(PL)=0: Grap(PL)=AN(PL)
      CASE 105: 'STOP KICKING GRAPPLED ENEMY
       AN(PL)=20: AniSpd(PL)=10: AniDelay(PL)=0: Grap(PL)=AN(PL)
      CASE 101:
       Punch(PL)=110

      CASE 100: 'ENEMY GRAPPLED
       AN(PL)=20: AniSpd(PL)= 5: AniDelay(PL)=0: Grap(PL)=AN(PL)
      CASE  30:
       Punch(PL)=1: Grap(PL)= 0: GrapE(PL)=0

      'HAGGAR PUNCHING SEQUENCE ---------------------------------------------------------

      CASE  10: 'STARTING STRONG PUNCH
       AN(PL)=16: AniSpd(PL)= 2: AniDelay(PL)=0 
      CASE   9: 'STARTING STRONG PUNCH
       AN(PL)=17: AniSpd(PL)= 3: AniDelay(PL)=0: Combo(PL)=0: Hitting(PL)=0
       IF MVUD(PL)=0 THEN PLAY_SAMPLE 21,PL,,999 'HAGGAR COMBO! (SND DELAY)
      CASE   8: 'LONG STRONG PUNCH
       AN(PL)=18: AniSpd(PL)= 5: AniDelay(PL)=0: Combo(PL)=0: Hitting(PL)=0
      CASE   7: 'RETURNING TO NORMAL
       AN(PL)=19: AniSpd(PL)= 3: AniDelay(PL)=0: Combo(PL)=0: Hitting(PL)=0
      CASE   6: 'RESET STATUS
                  AniSpd(PL)= 2: AniDelay(PL)=0: Punch(PL)=1: Combo(PL)=0: Hitting(PL)=0

      CASE   5: 'PUNCHING
       AN(PL)=13: AniSpd(PL)=1: AniDelay(PL)=0
       IF WEAPON(PL)>0 THEN
        AN(PL)=70
        SELECT CASE Weapon(PL)
         CASE KATANA: AniSpd(PL)=7: PLAY_SAMPLE 16,PL
         CASE KNIFE : AniSpd(PL)=7: PLAY_SAMPLE 16,PL,30000
         CASE PIPE  : AniSpd(PL)=6: PLAY_SAMPLE 16,PL,19000
        END SELECT
       ENDIF
      CASE   4:
       AN(PL)=14: AniSpd(PL)=2: AniDelay(PL)=0
       IF WEAPON(PL)>0 THEN       
        AN(PL)=71
        SELECT CASE Weapon(PL)
         CASE KATANA: AniSpd(PL)=6
         CASE KNIFE :
          AniSpd(PL)=6
          SpawnObject(X(PL)+(SIDE(PL)=4)*75-(SIDE(PL)=5)*75,RealY(PL),SIDE(PL)+KNIFE)
          WEAPON(PL)=0: Punch(PL)=1
         CASE PIPE  : AniSpd(PL)=5
        END SELECT
       ENDIF
      CASE   3:
       AN(PL)=15: AniSpd(PL)=3: AniDelay(PL)=0
       If Hitting(PL)>0 THEN INC Combo(PL)
       IF WEAPON(PL)>0 THEN AN(PL)=0: Combo(PL)=0: Punch(PL)=1
      CASE   2:
       AN(PL)=14: AniSpd(PL)=2: AniDelay(PL)=0
       If Combo(PL)=1 then Punch(PL)=11
      CASE   1:
       AN(PL)=13: AniSpd(PL)=1: AniDelay(PL)=0
      CASE   0:
       AN(PL)= 0: AniSpd(PL)=1: AniDelay(PL)=0
     END SELECT
    ENDIF 'END OF CODY PUNCH / GRAPPLE / THROW SEQUENCES -------------------------------------

    'HAGGAR JUMPING / FIRE KICK JUMP ---------------------------------------------------------
    If Jump(PL)>0 and Phurted(PL)=0 then
     INC Jump(PL),-1

     'AIR KICK (NOT SPECIAL)
     'IF (Jump(PL)>=2 and Jump(PL)<=29) and Kick(PL)=0 and Y(PL)<-1 then
     IF (Jump(PL)>=2 and Jump(PL)<=35) and Kick(PL)=0 and Y(PL)<-1 then
      IF KSHIFT AND (Kick(PL)=0) THEN
       Kick(PL)=1: Wait(PL)=2

       'CALL PILE DRIVER
       IF Grap(PL)=20 AND GrapE(PL)>0 AND Special(PL)=0 THEN
        Jump(PL)=40: Kick(PL)=3: Special(PL)=2: Wait(PL)=0
       ELSE 'CALL JUMP KICK OR SMASH
        IF JumpX(PL)<>0 THEN Wait(PL)=15
        IF MVUD(PL)=1 AND Kick(PL)=1 THEN Kick(PL)=2: Wait(PL)=5
        'JUMP KICK OR SMASH SOUND?
        IF Kick(PL)=1 THEN PLAY_SAMPLE 23,PL,,100 ELSE PLAY_SAMPLE 18,PL,,100
       ENDIF

      ENDIF
     ENDIF

     ' ANIMATION CONTROL
     SELECT CASE Jump(PL)
      ' SPECIAL
      CASE 50: AN(PL)=33: AniSpd(PL)=2: AniDelay(PL)=0: PLAY_SAMPLE 19,PL,,100
      CASE 49: AN(PL)=34: AniSpd(PL)=2: AniDelay(PL)=0
      CASE 48: AN(PL)=35: AniSpd(PL)=3: AniDelay(PL)=0
      CASE 47: AN(PL)=36: AniSpd(PL)=2: AniDelay(PL)=0
      CASE 46: AN(PL)=37: AniSpd(PL)=3: AniDelay(PL)=0
      CASE 45: AN(PL)=34: AniSpd(PL)=2: AniDelay(PL)=0
      CASE 44: AN(PL)=35: AniSpd(PL)=3: AniDelay(PL)=0
      CASE 43: AN(PL)=36: AniSpd(PL)=2: AniDelay(PL)=0
      CASE 42: AN(PL)=37: AniSpd(PL)=3: AniDelay(PL)=0
      CASE 41:
       AN(PL)=34: AniSpd(PL)=2: AniDelay(PL)=0: Jump(PL)=0: Punch(PL)=0: Special(PL)=0
      ' PILE DRIVER
      CASE 39 TO 40: AN(PL)=31: AniSpd(PL)=0: AniDelay(PL)=0: MV=0
      CASE 38: AN(PL)=26: AniSpd(PL)=1: AniDelay(PL)=0: PLAY_SAMPLE 17,PL,,100
      CASE 37: AN(PL)=32: AniSpd(PL)=1
      CASE 36: AN(PL)=32: AniSpd(PL)=35
      CASE 35:
       AN(PL)=26: AniSpd(PL)=2: MVLR(PL)=0: MV=0: Special(PL)=2: Kick(PL)=0: Y(PL)=0
       PLAY_SAMPLE 3,3,,100: JumpY(PL)=-10: JumpX(PL)=MVLR(PL)*2
      CASE 34: AN(PL)=26: AniSpd(PL)=1: AniDelay(PL)=0
      CASE 33: AN(PL)=26: AniSpd(PL)=15: AniDelay(PL)=0
      CASE 32: AN(PL)=24: AniSpd(PL)=3
      CASE 31: AN(PL)= 0: AniSpd(PL)=1: MVLR(PL)=0: MV=0: JumpY(PL)=0: Jump(PL)=0: Special(PL)=0
      ' VERTICAL JUMP
      CASE 29 TO 30: AN(PL)=24: AniSpd(PL)=2: AniDelay(PL)=0: MV=0
      CASE 28: AN(PL)=25: AniSpd(PL)=1: AniDelay(PL)=0: JumpY(PL)=-12-(Grap(PL)>0)*2
      CASE 24 TO 27: AN(PL)=26: AniSpd(PL)=4+(Grap(PL)>0)*1
      CASE 23: AN(PL)=25: AniSpd(PL)=5: AniDelay(PL)=0
      CASE 21 TO 22: AN(PL)=24: AniSpd(PL)=1: AniDelay(PL)=0
      CASE 20: AN(PL)= 0: AniSpd(PL)=3: MVLR(PL)=0: MV=0: JumpY(PL)=0: Jump(PL)=0: Special(PL)=0
      ' JUMPING AHEAD
      CASE 9 TO 10: AN(PL)=24: AniSpd(PL)=2: AniDelay(PL)=0: MV=0
      CASE 8: AN(PL)=25: AniSpd(PL)=1: AniDelay(PL)=0: JumpY(PL)=-12-(Grap(PL)>0)*2
      CASE 4 TO 7: AN(PL)=26: AniSpd(PL)=4+(Grap(PL)>0)*1
      CASE 3: AN(PL)=25: AniSpd(PL)=5: AniDelay(PL)=0
      CASE 1 TO 2: AN(PL)=24: AniSpd(PL)=1: AniDelay(PL)=0: MV=0
      CASE 0: AN(PL)= 0: AniSpd(PL)=3: MVLR(PL)=0: JumpY(PL)=0: Jump(PL)=0
     END SELECT

     IF Kick(PL)>0 AND Grap(PL)=0 then
      'KICK JUMP AHEAD
      if JumpX(PL)<>0 then
       if Jump(PL)>1 then 
        if Kick(PL)=2 then AN(PL)=29
        if Kick(PL)=1 and MVUD(PL)=0 then 
         if AN(PL)=2 then AN(PL)=28
         if Jump(PL)=2 then AN(PL)=24
        endif
       else
        Kick(PL)=0
       endif
      else
       'KICK VERTICAL JUMP
       if Jump(PL)>=23 and Jump(PL)<=29 then 
        if MVUD(PL)=0 then AN(PL)=27
       else
        AN(PL)=24
        Kick(PL)=0
       endif
      endif
     ENDIF

     'WHEN JUMPING WITH AN ENEMY GRAPPLED, CHANGE THE ANIMATION
     IF Grap(PL)>0 AND Jump(PL)<=30 THEN
      IF AN(PL)=25 OR AN(PL)=26 THEN AN(PL)=31
      IF AN(PL)=0 OR AN(PL)=24 THEN AN(PL)=30
      STE(GrapE(PL))=120 'RESET ENEMY TO FORCE HIM TO STILL GRAPPLED
     ENDIF

    ENDIF 'END OF HAGGAR JUMPING / FIRE KICK JUMP SEQUENCES ----------------------------------

   END SELECT

  endif 'END PHurted(PL)

END SUB


' SOME "FIXES" FOR PLAYER ANIMATION (RUNNING CONSTANTLY)

SUB FixPlayerAnimation(PL)
 
 SELECT CASE PlType(PL)
  'GUY'S ANIMATION FIXES
  CASE 1:
   ' ANIMATION FIXES
   INC Wait(PL),-1
   IF Wait(PL)<0 THEN
    Wait(PL)=0
    ' GUY VERTICAL JUMP
    if (Jump(PL)>=19 and Jump(PL)<=27) then
      if (Kick(PL)=1) and (JumpX(PL)=0) then 
       'KICK (29) OR MIDDLE ANIMATION KICK (28)
       if (Jump(PL)>=22 and Jump(PL)<=24) then AN(PL)=29 ELSE AN(PL)=28
      endif
      if (Kick(PL)=2) and (JumpX(PL)=0) then AN(PL)=31 'KNEE
    endif
   ENDIF
   ' GUY JUMP AHEAD
   if (Jump(PL)>=2 and Jump(PL)<=15) and (JumpX(PL)<>0) then
    if Kick(PL)=1 then 'KICK
     SELECT CASE Wait(PL)
      CASE  1 TO 14: AN(PL)=37 
      CASE  15 TO 17: AN(PL)=30 
     END SELECT
    endif
    if Kick(PL)=2 then 'KNEE
     SELECT CASE Wait(PL)
      CASE  1 TO  5: AN(PL)=31 
     END SELECT   
    endif
   endif
 
 'CODY'S ANIMATION FIXES
  CASE 2:
   ' ANIMATION FIXES
   INC Wait(PL),-1
   IF Wait(PL)<0 THEN
    Wait(PL)=0
    ' CODY VERTICAL JUMP
    if (Jump(PL)>=19 and Jump(PL)<=27) then
      if (Kick(PL)=1) and (JumpX(PL)=0) then AN(PL)=28 'KICK
      if (Kick(PL)=2) and (JumpX(PL)=0) then AN(PL)=31 'KNEE
    endif
   ENDIF
   ' CODY JUMP AHEAD
   if (Jump(PL)>=2 and Jump(PL)<=15) and (JumpX(PL)<>0) then
    if Kick(PL)=1 then 'KICK
     SELECT CASE Wait(PL)
      CASE  1 TO  8: AN(PL)=34 
      CASE  9 TO 12: AN(PL)=37 
      CASE 13 TO 15: AN(PL)=33 
     END SELECT
    endif
    if Kick(PL)=2 then 'KNEE
     SELECT CASE Wait(PL)
      CASE  1 TO  5: AN(PL)=30 
     END SELECT   
    endif
   endif

  'HAGGAR'S ANIMATION FIXES
  CASE 3:
   ' ANIMATION FIXES
   INC Wait(PL),-1
   IF Wait(PL)<0 THEN
    Wait(PL)=0
    ' HAGGAR VERTICAL JUMP
    if (Jump(PL)>=19 and Jump(PL)<=27) then
      if (Kick(PL)=1) and (JumpX(PL)=0) then AN(PL)=28 'KICK
    endif
    if (Jump(PL)>=19 and Jump(PL)<=27) then
      if (Kick(PL)=2) and (JumpX(PL)=0) then AN(PL)=29 'SMASH
    endif
   ENDIF
   ' HAGGAR JUMP AHEAD
   if (Jump(PL)>=2 and Jump(PL)<=27) and (JumpX(PL)<>0) then
    if Kick(PL)=1 and MVUD(PL)=0 then 'KICK
     SELECT CASE Wait(PL)
      CASE  1 TO  30: AN(PL)=28
     END SELECT
    endif
    if Kick(PL)=2 then 'SMASH
     SELECT CASE Wait(PL)
      CASE  1 TO 16: AN(PL)=26 
      CASE 17 TO 25: AN(PL)=29 
      CASE 26 TO 30: AN(PL)=26 
     END SELECT   
    endif
   endif

 END SELECT

END SUB


' INSERT A WAIT ON THE PLAYER AND ENEMY
' PAUSE THE MOVEMENTS OF PLAYER AND ENEMY TO GIVE A BETTER EFFECT (LIKE THE ARCADE)
SUB InsertWait(WPL,WEN,WT)
 IF PLWait(PL)=0 THEN PLWait(WPL)=WT
 IF EWAIT(WEN)=0 THEN EWAIT(WEN)=WT
END SUB


' PLAYER DROP ANY WEAPON
SUB DropWeapon(PL)
 IF WEAPON(PL)=0 THEN EXIT SUB
 SpawnObject(X(PL),RealY(PL),WEAPON(PL)+1): EY(NUM)=RealY(PL)-40
 WEAPON(PL)=0
END SUB

