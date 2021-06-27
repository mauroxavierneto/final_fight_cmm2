' -- GENERAL ROUND INTRO CONTROL ---

' Ending:
' 0 = STARTING SECTION
' 1 = FINISHING SECTION

SUB RoundIntro(Ending)

 LOCAL PL,T

 INC OSDX,-10

 SELECT CASE Round

  ' ROUND 1 INTROS --------------------------------------------------------------------------------
  CASE 1:

   SELECT CASE Section

    'START OF THE STAGE ---- ROUND 1 INTRO --------------------------------------------------------
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
         IF EAN(6)>104 THEN EAN(6)=101 
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
      IF OSDX=1550 THEN EAN(6)=104: PLAY_SAMPLE 30,3,,100
      IF OSDX>800 AND OSDX<1550 THEN      
       IF OSDX=1050 THEN PLAY_SAMPLE 30,3,,100
       INC EANIDelay(6)
       IF EANIDelay(6)>4 THEN 
        EANIDelay(6)=0: INC EAN(6)
        IF EAN(6)>105 THEN EAN(6)=104
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

      ' INSERT SCENE INTO THE FOREGROUND
      PAGE WRITE 1
      BLIT 227,0,227,56,93,184,12,4
       
      ' PLAYERS WALKING TO THE UPSTAIRS
      GO=1
      ' A LITTLE PAUSE (LIKE THE ARCADE)
      IF OSDX>=9600 THEN GO=0: MV=0: FOR PL=1 TO MAXPL: AN(PL)=0: NEXT PL
      IF OSDX>7000 AND OSDX<9600 THEN
       FOR PL=1 TO MAXPL
        IF X(PL)<=200 THEN
         INC X(PL), SPD(PL): MV=1: MVLR(PL)= 1
         IF X(PL)>200 THEN X(PL)=200 ELSE GO=0
        ENDIF
        IF RealY(PL)<189 THEN INC RealY(PL), SPD(PL): MV=1: MVUD(PL)= 1: GO=0
        IF RealY(PL)>194 THEN INC RealY(PL),-SPD(PL): MV=1: MVUD(PL)=-1: GO=0       
       NEXT PL
      ENDIF
    
      IF GO THEN OSDX=7000
 
      ' GO DOWNSTAIRS
      IF OSDX=7000 THEN
       GO=0
       FOR PL=1 TO MAXPL 
        IF X(PL)<245 THEN T=4 ELSE T=(AN(PL) MOD 5 <=2)*3
        INC X(PL), T: MV=1: MVLR(PL)= 1
        IF X(PL)>235 THEN INC RealY(PL), T/1.3: MVUD(PL)= 1
        ' REACH THE LIMIT
        IF X(PL)>350 THEN INC GO
       NEXT PL
      ENDIF

      ' NEXT SECTION
      IF GO=MAXPL THEN FadeOut: Inc Section: LoadRound: OSDX=2210: RoundIntro(0)

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
         InsertObject(38,197,201+INT(RND*3.99),NUM): EY(NUM)=-40-II*15
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
         IF Energy(PL)>=0 THEN X(PL)=0: EXIT FOR
        NEXT PL

      END SELECT 'END SELECT OSDX

     ENDIF 'ENDIF Ending --------------------------------------------------------------------------

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

