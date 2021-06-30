' -- ROUND CUTSCENES ---

' Ending:
' 0 = STARTING SECTION
' 1 = FINISHING SECTION

SUB Round_1_Cutscenes(Ending)

 LOCAL PL,T

 INC OSDX,-10

 SELECT CASE Round

  ' ROUND 1 INTROS --------------------------------------------------------------------------------
  CASE 1:

   SELECT CASE Section

    'START OF THE STAGE ---- ROUND 1 CUTSCENE -----------------------------------------------------
    CASE 1:    

     ' ** SECTION 1 START: DAMND KIDNAPPED JESSICA **
     IF Ending=0 THEN 

      SELECT CASE OSDX
       CASE           10: STE(4)=0: STE(5)=0: STE(6)=0 'REMOVE PROCESSED ENEMIES
       CASE   20 TO  799:
        'SPECIAL MOVES TO BREAK THE DRUMCANS
        IF OSDX=790 THEN KALT=1: KCTRL=1

        'BREAK ALL DRUMCANS
        IF OSDX=700 THEN PAGE WRITE 35: CLS &HFF0000
        IF OSDX=600 THEN PAGE WRITE 35: CLS 0: PLAY_WAV "The Slums"
        IF OSDX=500 THEN OSDX=10: ClearEvents

        'DAMND WALKING BACKWARD
        INC EX(6),4
        INC EANIDelay(6)
        IF EANIDelay(6)>3 THEN 
         EANIDelay(6)=0: INC EAN(6)
         IF EAN(6)>105 THEN EAN(6)=100
        ENDIF

        FOR T=4 TO 5
         IF (OSDX<700 AND T=4) OR (T=5 AND OSDX<750) THEN
          ESIDE(T)=4: INC EX(T),4 'ENEMIES GO AWAY (DOUG AND BRAD)
          INC EANIDelay(T)
          IF EANIDelay(T)>2 THEN
           EANIDelay(T)=0
           INC EAN(T): IF EAN(T)>5 THEN EAN(T)=0
          ENDIF
         ENDIF
        NEXT T

       'PLAYERS WALKING TO BREAK THE DRUMCANS
       CASE 800 TO 850:
        FOR PL=1 TO 2
         INC X(PL), SPD(PL): MV=1: MVLR(PL)=1
        NEXT PL 

       CASE 1450 TO 1549: ShowRoundMap(SW,OSDX-1549) 'MAP UP
       CASE 1550 TO 2099: ShowRoundMap(SW,0)         'KEEP MAP
       CASE 2100 TO 2200:
        IF OSDX=2200 THEN PLAY_WAV "Slums Start",1
        ShowRoundMap(SW,2100-OSDX) 'MAP DOWN

      END SELECT 'END CASE OSDX

      'DAMND LAUGH
      IF OSDX=1550 THEN EAN(6)=110: PLAY_SAMPLE 30,3,,100
      IF OSDX>800 AND OSDX<1550 THEN      
       IF OSDX=1050 THEN PLAY_SAMPLE 30,3,,100
       INC EANIDelay(6)
       IF EANIDelay(6)>4 THEN 
        EANIDelay(6)=0
        IF EAN(6)=110 THEN EAN(6)=111 ELSE EAN(6)=110
       ENDIF
      ENDIF

      'SET OSD PANEL POSITION
      OSDP=OSDX-1300: IF OSDP<0 THEN OSDP=0

      'KEEP TEMPORARY ENEMIES STOPPED
      FOR T=4 TO 5
       EWAIT(T)=10
       IF OSDX>=750 AND T=5 THEN EAN(T)=9
       IF T=4 THEN
        IF OSDX=2100 THEN STE(T)=75: EANIDelay(T)=1 'START ENEMY KICK
        'DRUMCAN KICKED
        IF OSDX=2050 THEN
         ESPDX(14)=-4: ESJMP(14)=-4
         InsertHit(EX(14)+20,RealY(14)-50,1) 'HIT
         InsertHit(EX(14)+20,RealY(14),2)    'SMOKE
        ENDIF
        IF OSDX=1960 THEN ESPDX(14)=0: ESJMP(14)=0  'STOP DRUMCAN
        'ENEMY STOPPED
        IF OSDX>=2000 AND OSDX<=2100 THEN EWAIT(T)=0 
        IF OSDX>=700 AND EWAIT(T)=10 THEN EAN(T)=9 
       ENDIF
      NEXT T
      ESide(6)=5

     ' ** SECTION 1 ENDING: DOWNSTAIRS TO THE SLUMS GALLERY ** ------------------------------------
     ELSE

      ' REMOVE A BLOCK OF ANIMATED DOOR TO FIX THE DOWNSTAIRS SCENE FOREGROUND
      PAGE WRITE 12
      BOX 213,0,7,105,1,0,0

      ' INSERT SCENE INTO THE FOREGROUND
      PAGE WRITE 1
      BLIT 213,0,227,56,93,184,12,4
       
      GO=1
      ' A LITTLE PAUSE (LIKE THE ARCADE)
      IF OSDX>=9600 THEN GO=0: MV=0: FOR PL=1 TO MAXPL: AN(PL)=0: NEXT PL

      ' PLAYERS WALKING TO THE DOWNSTAIRS
      IF OSDX>7000 AND OSDX<9600 THEN
       FOR PL=1 TO MAXPL
        IF X(PL)<=200 THEN
         INC X(PL), SPD(PL): MV=1: MVLR(PL)= 1
         IF X(PL)>200 THEN X(PL)=200 ELSE GO=0
        ENDIF
        IF RealY(PL)<189 THEN INC RealY(PL), SPD(PL): MV=1: MVUD(PL)= 1: GO=0
        IF RealY(PL)>196 THEN INC RealY(PL),-SPD(PL): MV=1: MVUD(PL)=-1: GO=0
        IF RealY(PL)>=189 AND RealY(PL)<=196 THEN RealY(PL)=194: Y(PL)=0
       NEXT PL
      ENDIF
    
      IF GO THEN OSDX=7000
 
      ' GO DOWNSTAIRS
      IF OSDX=7000 THEN
       GO=0
       FOR PL=1 TO MAXPL 
        IF X(PL)<245 THEN T=4 ELSE T=(AN(PL) MOD 5 <=2)*3
        INC X(PL), T: MV=1: MVLR(PL)= 1
        IF X(PL)>240 THEN INC RealY(PL), T/1.3: MVUD(PL)= 1
        ' REACH THE LIMIT
        IF X(PL)>350 THEN INC GO
       NEXT PL
      ENDIF

      ' NEXT SECTION
      IF GO=MAXPL THEN FadeOut: Inc Section: LoadRound: OSDX=2210: Round_1_Cutscenes(0)

      FOR PL=1 TO MAXPL
       SIDE(PL)=4
      NEXT PL

     ENDIF 'ENDIF Ending ----------------------------------------------------------------


    'SECTION 2: SLUMS GALLERY ---------------------------------------------------------------------
    CASE 2:    

     ' ** SECTION 2 START: BREAKING THE DOOR **
     IF Ending=0 THEN

      'INTACT DOOR
      PAGE WRITE 1
      IF OSDX>=2100 THEN BLIT 117,105,29,74,15,128,12,4

      'FOREGROUND WALL
      BLIT 0,0,0,0,32,240,6,4
   
      SELECT CASE OSDX

       CASE 1740: OSDX=10

       'WALKING AFTER PUNCH
       CASE 500 TO 2050:
        GO=1
        FOR PL=1 TO MAXPL
         INC X(PL),4: MV=1: MVLR(PL)=1
         IF MAXPL>1 AND X(PL)>30 THEN INC RealY(MAXPL): MVUD(PL)=1
         IF X(PL)<60 THEN GO=0
        NEXT PL
        IF GO THEN OSDX=10

       'PUNCH AND BREAK THE DOOR
       CASE 2100:
        KSHIFT=1
        FOR II=0 TO 3
         SpawnObject(38,197,201+INT(RND*3.99),NUM): EY(NUM)=-40-II*15
         ESJMP(NUM)=-10+RND*(3+II*2): ESIDE(NUM)=5: EMV(NUM)=1
         ESPDX(NUM)=II*2+(RND*6-3)
        NEXT II
        PLAY_SAMPLE 2,4,22050

       'CHANGE MUSIC AND INSERT PLAYERS IN THE RIGHT PLACE
       CASE 2200:  
        PLAY_WAV "The Slums 2"
        MV=0
        FOR PL=1 TO MAXPL
         X(PL)=-20: RealY(PL)=193:Y(PL)=0
        NEXT PL
        FOR PL=1 TO MAXPL
         IF Energy(PL)>=0 THEN X(PL)=0-(PLType(PL)=3)*15: EXIT FOR
        NEXT PL

      END SELECT 'END SELECT OSDX

     ' ** SECTION 2 ENDING: BREAK DOOR AND UPSTAIRS TO THE SLUMS ** -------------------------------
     ELSE

      'BROKEN DOOR
      IF OSDX=6990 THEN PAGE WRITE 7: BLIT 101,105,244,74,15,124,12,0

      PAGE WRITE 1

      'FOREGROUND WALL
      ScrX=320
      BLIT 256,0,256,0,64,240,7,4
       
      ' A LITTLE PAUSE (LIKE THE ARCADE)
      IF OSDX>=9600 THEN GO=0: MV=0: FOR PL=1 TO MAXPL: AN(PL)=0: NEXT PL

      ' PLAYERS WALKING TO THE UPSTAIRS
      IF OSDX>7020 AND OSDX<9600 THEN
       GO=1
       FOR PL=1 TO MAXPL
        IF X(PL)<205-(PLType(PL)=3)*15 THEN
         INC X(PL), SPD(PL): MV=1: MVLR(PL)=1: GO=0
        ELSE
         X(PL)=205-(PLType(PL)=3)*15
        ENDIF
        IF RealY(PL)<193 THEN INC RealY(PL), SPD(PL): MV=1: MVUD(PL)= 1: GO=0
        IF RealY(PL)>201 THEN INC RealY(PL),-SPD(PL): MV=1: MVUD(PL)=-1: GO=0
        IF RealY(PL)>=193 AND RealY(PL)<=201 THEN RealY(PL)=197
       NEXT PL
       IF GO THEN OSDX=7000: MV=0: MVLR(PL)=0: AN(PL)=0
      ENDIF

       'PUNCH AND BREAK THE DOOR
      IF OSDX=7000 THEN
       KSHIFT=1
       FOR II=0 TO 3
        SpawnObject(250,197,201+INT(RND*3.99),NUM): EY(NUM)=-40-II*15
        ESJMP(NUM)=-10+RND*(3+II*2): ESIDE(NUM)=5: EMV(NUM)=1
        ESPDX(NUM)=-II*2-(RND*6-3)
       NEXT II
       PLAY_SAMPLE 2,4,22050
      ENDIF 

      ' GO UPSTAIRS
      GO=0
      IF OSDX<=6750 THEN
       FOR PL=1 TO MAXPL 
        INC X(PL), 4: MV=1: MVLR(PL)= 1
        'IF X(PL)>235 THEN INC RealY(PL), -T/1.3: MVUD(PL)= 1
        ' REACH THE LIMIT
        IF X(PL)>330 THEN INC GO
       NEXT PL
      ENDIF

      ' NEXT SECTION
      IF GO=MAXPL THEN FadeOut: Inc Section: LoadRound: OSDX=2210: Round_1_Cutscenes(0)

      FOR PL=1 TO MAXPL
       SIDE(PL)=4
      NEXT PL

     ENDIF 'ENDIF Ending ----------------------------------------------------------------


    'SECTION 3: SLUMS MAD GEAR LAIR ---------------------------------------------------------------
    CASE 3:    

     ' ** SECTION 3 START: UPSTAIRS TO THE SLUMS **
     IF Ending=0 THEN

      PAGE WRITE 1

      'FOREGROUND WALL (MIRRORED)
      IF OSDX>20 THEN
       BLIT 213,0,0,56,107,170,12,5
       BLIT 0,220,0,220,107,20,8,4
      ENDIF
  
      SELECT CASE OSDX

       'WALKING UPSTAIRS
       CASE 30 TO 2050:
        GO=1
        FOR PL=1 TO MAXPL
         IF X(PL)>80 THEN T=4 ELSE T=(AN(PL) MOD 5 <=2)*4: INC RealY(PL),-T/1.8
         INC X(PL),T: MV=1: MVLR(PL)=1
         IF MAXPL>1 AND X(PL)>135 THEN INC RealY(MAXPL),4: MVUD(PL)=1
         IF X(PL)<150 THEN GO=0
         IF RealY(PL)<194 THEN RealY(PL)=194
        NEXT PL
        IF GO THEN OSDX=10

       'CHANGE MUSIC AND INSERT PLAYERS IN THE RIGHT PLACE
       CASE 2200:  
        PLAY_WAV "The Slums"
        MV=0
        FOR PL=1 TO MAXPL
         X(PL)=-40: RealY(PL)=380:Y(PL)=0
        NEXT PL
        FOR PL=1 TO MAXPL
         IF Energy(PL)>=0 THEN X(PL)=-20: EXIT FOR
        NEXT PL
        ' REMOVE A BLOCK OF ANIMATED DOOR TO FIX THE DOWNSTAIRS SCENE FOREGROUND
        PAGE WRITE 12: BOX 213,0,7,105,1,0,0: PAGE WRITE 1

      END SELECT 'END SELECT OSDX
   
     ENDIF 'ENDIF Ending ----------------------------------------------------------------


   END SELECT 'END CASE Section

 END SELECT 'END CASE Round

 IF OSDX<=10 THEN
  ' BRING BACK THE CONTROL TO THE PLAYERS
  FOR T=1 TO MAXPL: CtrlType(T)=TCTYPE(T): NEXT T
 ELSE
  ' REMOVE THE CONTROL FROM THE PLAYERS
  FOR T=1 TO MAXPL: CtrlType(T)=-1: NEXT T
 ENDIF

END SUB

