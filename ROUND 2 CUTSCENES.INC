' -- ROUND CUTSCENES ---

' Ending:
' 0 = STARTING SECTION
' 1 = FINISHING SECTION

SUB Round_2_Cutscenes(Ending)

 LOCAL PL,T

 INC OSDX,-10

 SELECT CASE Section

  'START OF THE STAGE ---- ROUND 2-1 CUTSCENE ---------------------------------------------------
  CASE 1:    

   ' ** SECTION 1 START **
   IF Ending=0 THEN 

    'FOREGROUND COLUMN
    PAGE WRITE 1
    BLIT 0,0,-(scrx-240),0,48,MM.VRES,2,0
    
    IF OSDX>1930 AND OSDX<2150 THEN FOR PL=1 TO MAXPL: INC X(PL), 8: NEXT PL

    'PLAYERS WALKING
    IF OSDX>1550 AND OSDX<1830 THEN
     T=0
     FOR PL=1 TO MAXPL
      MV=1: MVLR(PL)=1: INC X(PL), SPD(PL)
      INC X(PL),-7
      ScrSide=7: PLSCR=0: ScrollLock=0
      'IF X(PL)>MM.HRES-120 THEN X(PL)=MM.HRES-120: ScrSide=SPD(PL): PLSCR=PL: ScrollLock=0
     NEXT PL 
    ENDIF

    'STOP PLAYERS AND SCROLL SCREEN
    IF OSDX<=1550 THEN
     FOR PL=1 TO MAXPL
      MV=0: MVLR(PL)=0: AN(PL)=0
      'INC X(PL),-3
     NEXT PL
     'ScrSide=3: PLSCR=0: ScrollLock=0
    ENDIF

    SELECT CASE OSDX
     CASE 1350: OSDX=10

     CASE 1550 TO 1649:
      ShowRoundMap(SW,OSDX-1649) 'MAP UP

     CASE 1650 TO 2099:
      ShowRoundMap(SW,0)         'KEEP MAP

     CASE 2100 TO 2200:
      PAGE WRITE 1
      'FADE IN
      T=(2200-OSDX)*10: IF T<255 THEN BOX AND_PIXELS 0,0,MM.HRES,MM.VRES,RGB(T,T,T)
      IF OSDX=2200 THEN
       GO=0: MV=0
       FOR PL=1 TO MAXPL
        RealY(PL)=190+(PL-1)*25
        Y(PL)=-(PlType(PL)=HAGGAR)*90
        X(PL)=-35-(PlType(PL)=HAGGAR)*90
        JumpForward(PL)
        AN(PL)=27
       NEXT PL
       LoadRoundMap(Round,0) 'LOAD INTRO MAP
      ENDIF
      IF OSDX=2190 THEN PLAY_WAV "Subway 1"
      ShowRoundMap(SW,0) 'MAP DOWN

    END SELECT 'END CASE OSDX

    'SET OSD PANEL POSITION
    OSDP=OSDX-1500: IF OSDP<0 THEN OSDP=0

   ' ** SECTION 1 ENDING: ENTERING INSIDE THE SUBWAY --------------------------------------------
   ELSE

    'STOP PLAYERS
    IF EVENT(40)=0 THEN
     EVENT(40)=1
     FOR PL=1 TO MAXPL
      MV=0: MVLR(PL)=0: AN(PL)=0
     NEXT PL
    ENDIF

    IF EVENT(40)>0 THEN INC EVENT(40)

    IF EVENT(40)=20 THEN 
     FOR PL=1 TO MAXPL
      DropWeapon(PL)
     NEXT PL
    ENDIF

    IF EVENT(40)>50 THEN 
     'GO TO THE SUBWAY DOOR
     GO=1
     FOR PL=1 TO MAXPL
      IF RealY(PL)>SMYA THEN INC RealY(PL),-SPD(PL): GO=0 'UP
      IF X(PL)>140 THEN Side(PL)=5: INC X(PL),-SPD(PL): MV=1: MVLR(PL)=-1: GO=0
      IF X(PL)<110 THEN Side(PL)=4: INC X(PL), SPD(PL): MV=1: MVLR(PL)= 1: GO=0
     NEXT PL

     ' NEXT SECTION
     IF GO=1 THEN FadeOut: PAGE WRITE 1: CLS 0: Inc Section: GoSection=1
    ENDIF

   ENDIF 'ENDIF Ending ----------------------------------------------------------------


  'INSIDE THE SUBWAY ----- ROUND 2-2 ------------------------------------------------------------
  CASE 2:    

   ' ** SECTION 2 START **
   IF Ending=0 THEN 

    'PLAYERS WALKING
    IF OSDX>1950 THEN
     FOR PL=1 TO MAXPL
      MV=1: MVLR(PL)=1: SIDE(PL)=4: INC X(PL), SPD(PL)
     NEXT PL 
    ELSE
    'STOP PLAYERS
     FOR PL=1 TO MAXPL
      MV=0: MVLR(PL)=0: AN(PL)=0
     NEXT PL: OSDX=10
    ENDIF

    IF OSDX>=2100 AND OSDX<=2200 THEN
     PAGE WRITE 1
     'FADE IN
     T=(2200-OSDX)*10: IF T<255 THEN BOX AND_PIXELS 0,0,MM.HRES,MM.VRES,RGB(T,T,T)
    ENDIF

    'RESTART MUSIC
    IF OSDX=2200 THEN
     'KILL_SOUND: PLAY MODFILE ".\SFX\SFX - ROUND 2.MOD",22050
     PLAY_WAV "Subway 1"
     'PLAY_SAMPLE 30,4,,9999,48
     GO=0: MV=0
     FOR PL=1 TO MAXPL
      RealY(PL)=210+(PL-1)*40
      X(PL)=-30-(PL-1)*20
     NEXT PL
    ENDIF

   ' ** SECTION 2 ENDING: INSIDE THE SUBWAY -----------------------------------------------------
   ELSE

    IF Event(2)=30 THEN PLAY_SAMPLE 31,4,,9999 'SUBWAY STOPPING SOUND
    INC Event(2),-0.20
    FOR PL=1 TO MAXPL
     DropWeapon(PL)
    NEXT PL

    'STOP PLAYERS
    FOR PL=1 TO MAXPL
     MV=0: MVLR(PL)=0: AN(PL)=0
    NEXT PL

    ' NEXT SECTION
    IF Event(2)<=0 THEN FadeOut: PAGE WRITE 1: CLS 0: Inc Section: GoSection=1

   ENDIF 'ENDIF Ending ----------------------------------------------------------------


  'OUTSIDE THE SUBWAY ----- ROUND 2-3 -----------------------------------------------------------
  CASE 3:

   ' ** SECTION 3 START **
   IF Ending=0 THEN 

    'PLAYERS WALKING
    IF OSDX>1950 THEN
     FOR PL=1 TO MAXPL
      MV=1: MVLR(PL)=1: SIDE(PL)=4: INC X(PL), SPD(PL)
     NEXT PL 
    ELSE
    'STOP PLAYERS
     FOR PL=1 TO MAXPL
      MV=0: MVLR(PL)=0: AN(PL)=0
     NEXT PL: OSDX=10
    ENDIF

    IF OSDX>=2100 AND OSDX<=2200 THEN
     PAGE WRITE 1
     'FADE IN
     T=(2200-OSDX)*10: IF T<255 THEN BOX AND_PIXELS 0,0,MM.HRES,MM.VRES,RGB(T,T,T)
    ENDIF

    'RESTART MUSIC
    IF OSDX=2200 THEN
     PLAY_WAV "Subway 2"
     GO=0: MV=0
     FOR PL=1 TO MAXPL
      RealY(PL)=210+(PL-1)*40
      X(PL)=-30-(PL-1)*20
     NEXT PL
    ENDIF

   ' ** SECTION 3 ENDING: OUTSIDE THE SUBWAY ----------------------------------------------------
   ELSE

    ' NEXT SECTION
    FadeOut: PAGE WRITE 1: CLS 0: Inc Section: GoSection=1

   ENDIF 'ENDIF Ending ----------------------------------------------------------------


 END SELECT 'END CASE Section

 IF OSDX<=10 THEN
  ' BRING BACK THE CONTROL TO THE PLAYERS
  FOR T=1 TO MAXPL: CtrlType(T)=TCTYPE(T): NEXT T: OSDX=0
 ELSE
  ' REMOVE THE CONTROL FROM THE PLAYERS
  FOR T=1 TO MAXPL: CtrlType(T)=-1: NEXT T
 ENDIF

END SUB

