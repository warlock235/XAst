#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<iomanip>
#include<strstream>
#include<fstream>
#include<X11/Intrinsic.h>
#include<X11/StringDefs.h>
#include<X11/Shell.h>
#include<Xm/Protocols.h>
#include<Xm/Xm.h>
#include<Xm/Form.h>
#include<Xm/SeparatoG.h>
#include<Xm/PushBG.h>
#include<Xm/Scale.h>
#include<Xm/RowColumn.h>
#include<Xm/ToggleB.h>
#include<Xm/ToggleBG.h>
#include<Xm/LabelG.h>
#include<Xm/TextF.h>
#include<Xm/FileSB.h>
#include<Xm/MessageB.h>

#include"../../bitmaps/ROCKScoringIcon.xbm"
#include"../../bitmaps/ROckScoringIcon.xbm"
#include"../../bitmaps/rockScoringIcon.xbm"
#include"../../bitmaps/ENEMYScoringIcon.xbm"
#include"../../bitmaps/enemyScoringIcon.xbm"
#include"../../bitmaps/bulletScoringIcon.xbm"

#ifndef _OPTIONS_H
#define _OPTIONS_H

class Ship;
class Thrust;
class Options
 {typedef int Boolean;
  enum {off, on};

  public:
    inline Options(int argc, char** argv);
    inline ~Options();
    inline void RealizeWindow();


  private:
    static void CloseCallback(Widget,XtPointer,XtPointer);
    static void ReadFromFile(Widget,XtPointer,XtPointer);
    static void WriteToFile(Widget,XtPointer,XtPointer);
    static void ResetDefaults(Widget,XtPointer,XtPointer);
    static void ApplyFramesPerSecond(Widget,XtPointer,XtPointer);
    static void SetIntEnterValue(Widget,XtPointer,XtPointer);
    static void SetFloatEnterValue(Widget,XtPointer,XtPointer);
    static void VerifyIntTextField(Widget,XtPointer,XtPointer);
    static void VerifyFloatTextField(Widget,XtPointer,XtPointer);
    static void ApplyGlobalMaxVel(Widget,XtPointer,XtPointer);
    static void ApplyUniversalGravitationalConstant(Widget,XtPointer,XtPointer);
    static void ApplyRelativisticMass(Widget,XtPointer,XtPointer);
    static void ApplyStarDestroyerShipShape(Widget,XtPointer,XtPointer);
    static void ApplyNCC1701AShipShape(Widget,XtPointer,XtPointer);
    static void ApplyNCC1701DShipShape(Widget,XtPointer,XtPointer);
    static void ApplyShipAccel(Widget,XtPointer,XtPointer);
    static void ApplyShipMaxVel(Widget,XtPointer,XtPointer);
    static void ApplyShipRotationalVel(Widget,XtPointer,XtPointer);
    static void ApplyHyperspaceDestructRate(Widget,XtPointer,XtPointer);
    static void ApplyInitialShips(Widget,XtPointer,XtPointer);
    static void ApplyExtraShipScore(Widget,XtPointer,XtPointer);
    static void ApplyAutoFire(Widget,XtPointer,XtPointer);
    static void ApplyShipBulletVel(Widget,XtPointer,XtPointer);
    static void ApplyShipBulletDuration(Widget,XtPointer,XtPointer);
    static void ApplyNumShipBullets(Widget,XtPointer,XtPointer);
    static void ApplyROCKMinVel(Widget,XtPointer,XtPointer);
    static void ApplyROCKMaxVel(Widget,XtPointer,XtPointer);
    static void ApplyROCKMaxRotationalVel(Widget,XtPointer,XtPointer);
    static void ApplyInitialROCKs(Widget,XtPointer,XtPointer);
    static void ApplyNewROCKsPerLevel(Widget,XtPointer,XtPointer);
    static void ApplyTransparentRocks(Widget,XtPointer,XtPointer);
    static void ApplyEnemiesExist(Widget,XtPointer,XtPointer);
    static void ApplyENEMYMinVel(Widget,XtPointer,XtPointer);
    static void ApplyENEMYMaxVel(Widget,XtPointer,XtPointer);
    static void ApplyenemyMinVel(Widget,XtPointer,XtPointer);
    static void ApplyenemyMaxVel(Widget,XtPointer,XtPointer);
    static void ApplyEnemyBulletVel(Widget,XtPointer,XtPointer);
    static void ApplyEnemyBulletDuration(Widget,XtPointer,XtPointer);
    static void ApplyNumEnemyBullets(Widget,XtPointer,XtPointer);
    static void ReadWriteOptions(Widget,XtPointer,XtPointer);
    static void CancelFileSelect(Widget,XtPointer,XtPointer);
    static void FileExistsWrite(Widget,XtPointer,XtPointer);
    static void CancelFileExistsQuestion(Widget,XtPointer,XtPointer);
    static void CancelFileError(Widget,XtPointer,XtPointer);


    inline void CreateScoringIconPixmaps(const unsigned char* const bitmapData,
                                         const int width, const int height, const int color,
                                         Pixmap& pixmap);
    inline void CreateToggleButtonPixmaps(const unsigned char* const bitmapData,
                                          const int width, const int height, const int color,
                                          Pixmap& selectedPixmap, Pixmap& notSelectedPixmap);

    inline void AlterFramesPerSecond(const double newUSecondsPerFrame);
    inline void AlterGlobalMaxVel(const double newMaxVel);
    inline void AlterUniversalGravitationalConstant(const double newUniversalGravitationalConst);
    inline void AlterRelativisticMass(const Boolean relMass);
    inline void AlterShipShape(Ship& newip,Thrust& newrust);
    inline void AlterShipAccel(const double newAccel);
    inline void AlterShipMaxVel(const double newMaxVel);
    inline void AlterShipRotationalVel(const double newRotVel);
    inline void AlterHyperspaceDestructRate(const double newDestructRate);
    inline void AlterInitialShips(const int newInitialShips);
    inline void AlterExtraShipScore(const int newExtraShipScore);
    inline void AlterAutoFire(const Boolean automaticFire);
    inline void AlterShipBulletVel(const double newVel);
    inline void AlterShipBulletDuration(const int newDurtation);
    inline void AlterNumShipBullets(const int newNumBullets);
    inline void AlterROCKMinVel(const double newMinVel);
    inline void AlterROCKMaxVel(const double newMaxVel);
    inline void AlterROCKMaxRotationalVel(const double newRotationalVel);
    inline void AlterInitialROCKs(const int newInitialROCKs);
    inline void AlterNewROCKsPerLevel(const int newROCKsPerLevel);
    inline void AlterTransparentRocks(const Boolean transparentRocks);
    inline void AlterEnemiesExist(const Boolean newEnemiesExist);
    inline void AlterENEMYMinVel(const double newMinVel);
    inline void AlterENEMYMaxVel(const double newMaxVel);
    inline void AlterenemyMinVel(const double newMinVel);
    inline void AlterenemyMaxVel(const double newMaxVel);
    inline void AlterEnemyBulletVel(const double newVel);
    inline void AlterEnemyBulletDuration(const int newDurtation);
    inline void AlterNumEnemyBullets(const int newNumBullets);

    inline void SetWidgetChildrenColors(Widget& parent,const Pixel foreground,
                                                       const Pixel background,
                                                       const Pixel topShadowColor,
                                                       const Pixel bottomShadowColor,
                                                       const Pixel troughColor);
    inline void ReadOptions();
    inline void WriteOptions();
    inline void SetWidgetFields();
    inline void SetTextWidget(Widget widget,const char* const str);
    inline void SetScore(Widget, const int score);
    inline const char* const MakeString(const int n);
    inline const char* const MakeString(const double d);

    XtAppContext appContext;
    Widget shell,
           mainForm,
           exit,
           verticalSeparator1,
           horizontalSeparator1,
           readFromFile,
           writeToFile,
           resetDefaults,
           horizontalSeparator2,
           framesPerSecondLabel,
           framesPerSecondScale,
           globalMaxVelLabel,
           globalMaxVelValue,
           universalGravitationalConstantLabel,
           universalGravitationalConstantValue,
           horizontalSeparator3,
           scoringLabel,
           ROCKScoreLabel,
           ROCKPixmapLabel,
           ROckScoreLabel,
           ROckPixmapLabel,
           rockScoreLabel,
           rockPixmapLabel,
           ENEMYScoreLabel,
           ENEMYPixmapLabel,
           enemyScoreLabel,
           enemyPixmapLabel,
           bulletScoreLabel,
           bulletPixmapLabel,
           relativisticMass,
           verticalSeparator2,
           horizontalSeparator4,
           shipShapeLabel,
           shipShape,
           shipStarDestroyer,
           shipNCC1701A,
           shipNCC1701D,
           hyperspaceDestructRateLabel1,
           hyperspaceDestructRateLabel2,
           hyperspaceDestructRateValue,
           shipAccelLabel,
           shipAccelValue,
           shipMaxVelLabel,
           shipMaxVelValue,
           shipRotationalVelLabel,
           shipRotationalVelValue,
           initialShipsLabel,
           initialShipsScale,
           extraShipScoreLabel,
           extraShipScoreValue,
           autoFire,
           shipBulletVelLabel,
           shipBulletVelValue,
           shipBulletDurationLabel,
           shipBulletDurationValue,
           numShipBulletsLabel,
           numShipBulletsScale,
           horizontalSeparator5,
 	         ROCKMinVelLabel,
           ROCKMinVelValue,
 	         ROCKMaxVelLabel,
           ROCKMaxVelValue,
	         ROCKMaxRotationalVelLabel1,
	         ROCKMaxRotationalVelLabel2,
           ROCKMaxRotationalVelValue,
	         initialROCKsLabel,
           initialROCKsScale,
           newROCKsPerLevelLabel,
           newROCKsPerLevelScale,
           transparentRocks,
           enemiesExist,
           verticalSeparator3,
           horizontalSeparator6,
	         ENEMYMinVelLabel,
           ENEMYMinVelValue,
	         ENEMYMaxVelLabel,
           ENEMYMaxVelValue,
	         enemyMinVelLabel,
           enemyMinVelValue,
	         enemyMaxVelLabel,
           enemyMaxVelValue,
           horizontalSeparator7,
           enemyBulletVelLabel,
           enemyBulletVelValue,
           enemyBulletDurationLabel,
           enemyBulletDurationValue,
           numEnemyBulletsLabel,
           numEnemyBulletsScale,
           fileSelectionDialog,
           fileExistsQuestionDialog,
           fileErrorDialog;

    static const double defaultGlobalMaxVel,
                        minGlobalMaxVel,
                        maxGlobalMaxVel,
                        defaultUniversalGravitationalConstant,
                        minUniversalGravitationalConstant,
                        maxUniversalGravitationalConstant,
                        defaultHyperspaceDestructRate,
                        minHyperspaceDestructRate,
                        maxHyperspaceDestructRate,
                        defaultShipAccel,
                        minShipAccel,
                        maxShipAccel,
                        defaultShipMaxVel,
                        minShipMaxVel,
                        maxShipMaxVel,
                        defaultShipRotationalVel,
                        minShipRotationalVel,
                        maxShipRotationalVel,
                        defaultShipBulletVel,
                        minShipBulletVel,
                        maxShipBulletVel,
                        defaultROCKMinVel,
                        minROCKMinVel,
                        maxROCKMinVel,
                        defaultROCKMaxVel,
                        minROCKMaxVel,
                        maxROCKMaxVel,
                        defaultROCKMaxRotationalVel,
                        minROCKMaxRotationalVel,
                        maxROCKMaxRotationalVel,
                        defaultENEMYMinVel,
                        minENEMYMinVel,
                        maxENEMYMinVel,
                        defaultENEMYMaxVel,
                        minENEMYMaxVel,
                        maxENEMYMaxVel,
                        defaultenemyMinVel,
                        minenemyMinVel,
                        maxenemyMinVel,
                        defaultenemyMaxVel,
                        minenemyMaxVel,
                        maxenemyMaxVel,
                        defaultEnemyBulletVel,
                        minEnemyBulletVel,
                        maxEnemyBulletVel;

    static const int defaultUSecondsPerFrame,
                     defaultInitialShips,
                     minInitialShips,
                     maxInitialShips,
                     defaultExtraShipScore,
                     minExtraShipScore,
                     maxExtraShipScore,
                     defaultShipBulletDuration,
                     minShipBulletDuration,
                     maxShipBulletDuration,
                     defaultNumShipBullets,
                     minNumShipBullets,
                     maxNumShipBullets,
                     defaultInitialROCKs,
                     minInitialROCKs,
                     maxInitialROCKs,
                     defaultNewROCKsPerLevel,
                     minNewROCKsPerLevel,
                     maxNewROCKsPerLevel,
                     defaultEnemyBulletDuration,
                     minEnemyBulletDuration,
                     maxEnemyBulletDuration,
                     defaultNumEnemyBullets,
                     minNumEnemyBullets,
                     maxNumEnemyBullets,
                     defaultROCKScore,
                     defaultROckScore,
                     defaultrockScore,
                     defaultENEMYScore,
                     defaultenemyScore,
                     defaultEnemyBulletScore;

    static const Boolean defaultRelativisticMass,
                         defaultOpaqueRocks,
                         defaultAutoFire,
                         defaultEnemiesExist;

    static const int weightGlobalMaxVel,
                     weightUniversalGravitationalConstant,
                     weightShipAccel,
                     weightShipMaxVel,
                     weightShipRotationalVel,
                     weightHyperspaceDestructRate,
                     weightInitialShips,
                     weightExtraShipScore,
                     weightShipShape,
                     weightAutoFire,
                     weightShipBulletVel,
                     weightShipBulletDuration,
                     weightNumShipBullets,
                     weightROCKMinVel,
                     weightROCKMaxVel,
                     weightROCKMaxRotationalVel,
                     weightInitialROCKs,
                     weightNewROCKsPerLevel,
                     weightOpaqueRocks,
                     weightEnemiesExist,
                     weightENEMYMinVel,
                     weightENEMYMaxVel,
                     weightenemyMinVel,
                     weightenemyMaxVel,
                     weightEnemyBulletVel,
                     weightEnemyBulletDuration,
                     weightNumEnemyBullets,
                     weightTotal;

    XmFontList fontList;

    Pixmap ROCKIconPixmap,
           ROckIconPixmap,
           rockIconPixmap,
           ENEMYIconPixmap,
           enemyIconPixmap,
           bulletIconPixmap,
           starDestroyerSelectedPixmap,
           starDestroyerNotSelectedPixmap,
           NCC1701ASelectedPixmap,
           NCC1701ANotSelectedPixmap,
           NCC1701DSelectedPixmap,
           NCC1701DNotSelectedPixmap;

    int intEnterValue,
        intExitValue;

    double floatEnterValue,
           floatExitValue,
           lastScoreFactor;

    char str[25],
        * filename;

    Boolean exitFlag,
            valueChanged;

    typedef int IOIndicator;
    enum {noIOInProgress,readInProgress,writeInProgress};
    IOIndicator IOState;
 };

#include"../stage.H"
#include"../shipYard.H"
#include"../../objects/ships/shipBulletGroup.H"
#include"../../objects/ships/shipGroup.H"
#include"../../objects/enemies/enemyGroup.H"
#include"../../objects/enemies/enemyBulletGroup.H"
#include"../../objects/rocks/rockGroup.H"
#include"../playingField.H"

const double Options::defaultGlobalMaxVel=PlayingField::maxLinearVelocity,
             Options::minGlobalMaxVel=0,
             Options::maxGlobalMaxVel=.5*PlayingField::playArea.Height(),
             Options::defaultUniversalGravitationalConstant=PlayingField::universalGravitationalConst,
             Options::minUniversalGravitationalConstant=-15,
             Options::maxUniversalGravitationalConstant=15,
             Options::defaultHyperspaceDestructRate=Hyper::percentDestructRate,
             Options::minHyperspaceDestructRate=0,
             Options::maxHyperspaceDestructRate=100,
             Options::defaultShipAccel=Ship::acceleration,
             Options::minShipAccel=Options::minGlobalMaxVel,
             Options::maxShipAccel=Options::maxGlobalMaxVel,
             Options::defaultShipMaxVel=Ship::maxVelocity,
             Options::minShipMaxVel=Options::minGlobalMaxVel,
             Options::maxShipMaxVel=Options::maxGlobalMaxVel,
             Options::defaultShipRotationalVel=Ship::angularVelocity,
             Options::minShipRotationalVel=Options::minGlobalMaxVel
                                           /(4*20.6155 /* Radius of shipgroup.NCC1701D */),
             Options::maxShipRotationalVel=Options::maxGlobalMaxVel
                                           /(4*20.6155 /* Radius of shipgroup.NCC1701D */),
             Options::defaultShipBulletVel=ShipBullet::velocity,
             Options::minShipBulletVel=Options::minGlobalMaxVel,
             Options::maxShipBulletVel=Options::maxGlobalMaxVel,
             Options::defaultROCKMinVel=ROCK::minVelocity,
             Options::minROCKMinVel=Options::minGlobalMaxVel,
             Options::maxROCKMinVel=Options::maxGlobalMaxVel,
             Options::defaultROCKMaxVel=ROCK::maxVelocity,
             Options::minROCKMaxVel=Options::minGlobalMaxVel,
             Options::maxROCKMaxVel=Options::maxGlobalMaxVel,
             Options::defaultROCKMaxRotationalVel=ROCK::maxAngularVelocity,
             Options::minROCKMaxRotationalVel=0,
             Options::maxROCKMaxRotationalVel=Options::maxGlobalMaxVel/(4*ROCK::scale),
             Options::defaultENEMYMinVel=ENEMY::minVelocity,
             Options::minENEMYMinVel=Options::minGlobalMaxVel,
             Options::maxENEMYMinVel=Options::maxGlobalMaxVel,
             Options::defaultENEMYMaxVel=ENEMY::maxVelocity,
             Options::minENEMYMaxVel=Options::minGlobalMaxVel,
             Options::maxENEMYMaxVel=Options::maxGlobalMaxVel,
             Options::defaultenemyMinVel=enemy::minVelocity,
             Options::minenemyMinVel=Options::minGlobalMaxVel,
             Options::maxenemyMinVel=Options::maxGlobalMaxVel,
             Options::defaultenemyMaxVel=enemy::maxVelocity,
             Options::minenemyMaxVel=Options::minGlobalMaxVel,
             Options::maxenemyMaxVel=Options::maxGlobalMaxVel,
             Options::defaultEnemyBulletVel=EnemyBullet::velocity,
             Options::minEnemyBulletVel=Options::minGlobalMaxVel,
             Options::maxEnemyBulletVel=Options::maxGlobalMaxVel;

const int Options::defaultUSecondsPerFrame=PlayingField::uSecondsPerFrame,
          Options::defaultInitialShips=PlayingField::initialShips,
          Options::minInitialShips=1,
          Options::maxInitialShips=50,
          Options::defaultExtraShipScore=PlayingField::extraShipScore,
          Options::minExtraShipScore=5000,
          Options::maxExtraShipScore=1000000,
          Options::defaultShipBulletDuration=ShipBullet::numFrames,
          Options::minShipBulletDuration=1,
          Options::maxShipBulletDuration=1000,
          Options::defaultNumShipBullets=ShipBulletGroup::numBullets,
          Options::minNumShipBullets=1,
          Options::maxNumShipBullets=16,
          Options::defaultInitialROCKs=RockGroup::initialROCKs,
          Options::minInitialROCKs=1,
          Options::maxInitialROCKs=RockGroup::maxROCKs,
          Options::defaultNewROCKsPerLevel=RockGroup::ROCKsPerLevel,
          Options::minNewROCKsPerLevel=0,
          Options::maxNewROCKsPerLevel=8,
          Options::defaultEnemyBulletDuration=EnemyBullet::numFrames,
          Options::minEnemyBulletDuration=1,
          Options::maxEnemyBulletDuration=1000,
          Options::defaultNumEnemyBullets=EnemyBulletGroup::numBullets,
          Options::minNumEnemyBullets=0,
          Options::maxNumEnemyBullets=10,
          Options::defaultROCKScore=ROCK::score,
          Options::defaultROckScore=ROck::score,
          Options::defaultrockScore=rock::score,
          Options::defaultENEMYScore=ENEMY::score,
          Options::defaultenemyScore=enemy::score,
          Options::defaultEnemyBulletScore=EnemyBullet::score;

const Options::Boolean Options::defaultOpaqueRocks=RockGroup::opaqueRocks,
                       Options::defaultRelativisticMass=PlayingField::relativisticMass,
                       Options::defaultAutoFire=ShipBulletGroup::autoFire,
                       Options::defaultEnemiesExist=PlayingField::enemiesExist;

const int Options::weightGlobalMaxVel=40,
          Options::weightUniversalGravitationalConstant=100,
          Options::weightShipAccel=15,
          Options::weightShipMaxVel=7,
          Options::weightShipRotationalVel=25,
          Options::weightHyperspaceDestructRate=250,
          Options::weightInitialShips=3500,
          Options::weightExtraShipScore=500,
          Options::weightShipShape=5,
          Options::weightAutoFire=2000,
          Options::weightShipBulletVel=10,
          Options::weightShipBulletDuration=5,
          Options::weightNumShipBullets=9000,
          Options::weightROCKMinVel=20,
          Options::weightROCKMaxVel=40,
          Options::weightROCKMaxRotationalVel=1,
          Options::weightInitialROCKs=30,
          Options::weightNewROCKsPerLevel=40,
          Options::weightOpaqueRocks=2,
          Options::weightEnemiesExist=150,
          Options::weightENEMYMinVel=20,
          Options::weightENEMYMaxVel=30,
          Options::weightenemyMinVel=30,
          Options::weightenemyMaxVel=40,
          Options::weightEnemyBulletVel=10,
          Options::weightEnemyBulletDuration=10,
          Options::weightNumEnemyBullets=1000,
          Options::weightTotal=Options::weightGlobalMaxVel
                               +Options::weightUniversalGravitationalConstant
                               +Options::weightShipAccel
                               +Options::weightShipMaxVel
                               +Options::weightShipRotationalVel
                               +Options::weightHyperspaceDestructRate
                               +Options::weightInitialShips
                               +Options::weightExtraShipScore
                               +Options::weightShipShape
                               +Options::weightAutoFire
                               +Options::weightShipBulletVel
                               +Options::weightShipBulletDuration
                               +Options::weightNumShipBullets
                               +Options::weightROCKMinVel
                               +Options::weightROCKMaxVel
                               +Options::weightROCKMaxRotationalVel
                               +Options::weightInitialROCKs
                               +Options::weightNewROCKsPerLevel
                               +Options::weightOpaqueRocks
                               +Options::weightEnemiesExist
                               +Options::weightENEMYMinVel
                               +Options::weightENEMYMaxVel
                               +Options::weightenemyMinVel
                               +Options::weightenemyMaxVel
                               +Options::weightEnemyBulletVel
                               +Options::weightEnemyBulletDuration
                               +Options::weightNumEnemyBullets;

inline Options::Options(int argc, char** argv): exitFlag(on),
                                                  valueChanged(off),
                                                  lastScoreFactor(1),
                                                  IOState(noIOInProgress)
 {XtToolkitInitialize();
  appContext=XtCreateApplicationContext();
  XtDisplayInitialize(appContext,stage.display,
                      "XAsteroids",argv[0],NULL,0,&argc,argv);

  Pixel background=stage.windowBg.pixel,
        foreground=BlackPixel(stage.display,DefaultScreen(stage.display));
  XmString string;

/********** Create Shell Widget **********/

  XmFontListEntry fontListEntry=XmFontListEntryCreate(XmFONTLIST_DEFAULT_TAG,
                                                      XmFONT_IS_FONT,stage.buttonInfo);
  fontList=XmFontListAppendEntry(NULL,fontListEntry);
  XmFontListEntryFree(&fontListEntry);
  fontListEntry=XmFontListEntryCreate("errorFont",
                                      XmFONT_IS_FONT,stage.errorInfo);
  fontList=XmFontListAppendEntry(fontList,fontListEntry);
  XmFontListEntryFree(&fontListEntry);
  shell=XtVaAppCreateShell("XAsteroids",argv[0],applicationShellWidgetClass,stage.display,
                           XmNbackground,background,
                           XmNiconPixmap,stage.icon,
                           XmNiconName,"Options",
                           XmNtitle,"Asteroids Options",
                           XmNdeleteResponse,XmDO_NOTHING,
                           XmNbuttonFontList,fontList,
                           XmNlabelFontList,fontList,
                           XmNtextFontList,fontList,
                           XmNkeyboardFocusPolicy,XmPOINTER,
                           NULL);
  XmAddWMProtocolCallback(shell,playingField.WM_DELETE_WINDOW,
                          CloseCallback,(caddr_t)this);


/********** Create Form Widget **********/

  mainForm=XtVaCreateManagedWidget("mainForm",xmFormWidgetClass,shell,
                                   XmNbackground,background,
                                   XmNforeground,foreground,
                                   XmNmarginWidth,5,
                                   XmNmarginHeight,5,
                                   NULL);


/********** Create Exit PushButton Gadget **********/

  string=XmStringCreateLocalized("Exit");
  exit=XtVaCreateManagedWidget("exit",xmPushButtonGadgetClass,mainForm,
                               XmNbackground,background,
                               XmNforeground,foreground,
                               XmNwidth,220,
                               XmNheight,30,
                               XmNlabelString,string,
                               XmNtopAttachment,XmATTACH_FORM,
                               XmNbottomAttachment,XmATTACH_NONE,
                               XmNleftAttachment,XmATTACH_FORM,
                               XmNrightAttachment,XmATTACH_NONE,
                               NULL);
  XmStringFree(string);
  XtAddCallback(exit,XmNactivateCallback,CloseCallback,this);


/********** Create Vertical Separator 1 Gadget **********/

  verticalSeparator1=XtVaCreateManagedWidget("verticalSeparator1",xmSeparatorGadgetClass,mainForm,
                                             XmNbackground,background,
                                             XmNforeground,foreground,
                                             XmNsensitive,FALSE,
                                             XmNwidth,14,
                                             XmNorientation,XmVERTICAL,
                                             XmNshadowThickness,4,
                                             XmNtopAttachment,XmATTACH_FORM,
                                             XmNbottomAttachment,XmATTACH_FORM,
                                             XmNleftAttachment,XmATTACH_WIDGET,
                                             XmNleftWidget,exit,
                                             XmNrightAttachment,XmATTACH_NONE,
                                             NULL);


/********** Create Horizontal Separator 1 Gadget **********/

  horizontalSeparator1=XtVaCreateManagedWidget("horizontalSeparator1",xmSeparatorGadgetClass,mainForm,
                                               XmNbackground,background,
                                               XmNforeground,foreground,
                                               XmNsensitive,FALSE,
                                               XmNheight,30,
                                               XmNshadowThickness,4,
                                               XmNtopAttachment,XmATTACH_WIDGET,
                                               XmNtopWidget,exit,
                                               XmNbottomAttachment,XmATTACH_NONE,
                                               XmNleftAttachment,XmATTACH_FORM,
                                               XmNrightAttachment,XmATTACH_WIDGET,
                                               XmNrightWidget,verticalSeparator1,
                                               NULL);

/********** Create Read From File PushButton Gadget **********/

  string=XmStringCreateLocalized("Read From File");
  readFromFile=XtVaCreateManagedWidget("readFromFile",xmPushButtonGadgetClass,mainForm,
                                       XmNbackground,background,
                                       XmNforeground,foreground,
                                       XmNwidth,110,
                                       XmNlabelString,string,
                                       XmNtopAttachment,XmATTACH_WIDGET,
                                       XmNtopWidget,horizontalSeparator1,
                                       XmNbottomAttachment,XmATTACH_NONE,
                                       XmNleftAttachment,XmATTACH_FORM,
                                       XmNrightAttachment,XmATTACH_NONE,
                                       NULL);
  XmStringFree(string);
  XtAddCallback(readFromFile,XmNactivateCallback,ReadFromFile,this);


/********** Create Write To File PushButton Gadget **********/

  string=XmStringCreateLocalized("Write To File");
  writeToFile=XtVaCreateManagedWidget("writeToFile",xmPushButtonGadgetClass,mainForm,
                                      XmNbackground,background,
                                      XmNforeground,foreground,
                                      XmNlabelString,string,
                                      XmNtopAttachment,XmATTACH_WIDGET,
                                      XmNtopWidget,horizontalSeparator1,
                                      XmNbottomAttachment,XmATTACH_NONE,
                                      XmNleftAttachment,XmATTACH_WIDGET,
                                      XmNleftWidget,readFromFile,
                                      XmNrightAttachment,XmATTACH_WIDGET,
                                      XmNrightWidget,verticalSeparator1,
                                      NULL);
  XmStringFree(string);
  XtAddCallback(writeToFile,XmNactivateCallback,WriteToFile,this);


/********** Create Reset Defaults PushButton Gadget **********/

  string=XmStringCreateLocalized("Reset Defaults");
  resetDefaults=XtVaCreateManagedWidget("resetDefaults",xmPushButtonGadgetClass,mainForm,
                                        XmNbackground,background,
                                        XmNforeground,foreground,
                                        XmNlabelString,string,
                                        XmNtopAttachment,XmATTACH_WIDGET,
                                        XmNtopWidget,readFromFile,
                                        XmNbottomAttachment,XmATTACH_NONE,
                                        XmNleftAttachment,XmATTACH_FORM,
                                        XmNrightAttachment,XmATTACH_WIDGET,
                                        XmNrightWidget,verticalSeparator1,
                                        NULL);
  XmStringFree(string);
  XtAddCallback(resetDefaults,XmNactivateCallback,ResetDefaults,this);


/********** Create Horizontal Separator 2 Gadget **********/

  horizontalSeparator2=XtVaCreateManagedWidget("horizontalSeparator2",xmSeparatorGadgetClass,mainForm,
                                               XmNbackground,background,
                                               XmNforeground,foreground,
                                               XmNsensitive,FALSE,
                                               XmNheight,30,
                                               XmNshadowThickness,4,
                                               XmNtopAttachment,XmATTACH_WIDGET,
                                               XmNtopWidget,resetDefaults,
                                               XmNbottomAttachment,XmATTACH_NONE,
                                               XmNleftAttachment,XmATTACH_FORM,
                                               XmNrightAttachment,XmATTACH_WIDGET,
                                               XmNrightWidget,verticalSeparator1,
                                               NULL);


/********** Create Frames Per Second Label Gadget **********/

  string=XmStringCreateLocalized("Frames Per Second");
  framesPerSecondLabel=XtVaCreateManagedWidget("framesPerSecondLabel",
                                               xmLabelGadgetClass,mainForm,
                                               XmNbackground,background,
                                               XmNforeground,foreground,
                                               XmNlabelString,string,
                                               XmNtopAttachment,XmATTACH_WIDGET,
                                               XmNtopWidget,horizontalSeparator2,
                                               XmNbottomAttachment,XmATTACH_NONE,
                                               XmNleftAttachment,XmATTACH_FORM,
                                               XmNrightAttachment,XmATTACH_WIDGET,
                                               XmNrightWidget,verticalSeparator1,
	                                             NULL);
  XmStringFree(string);

/********** Create Frames Per Second Scale Widget **********/

  framesPerSecondScale=XtVaCreateManagedWidget("framesPerSecondScale",
                                               xmScaleWidgetClass,mainForm,
                                               XmNbackground,background,
                                               XmNforeground,foreground,
                                               XmNminimum,16,
                                               XmNmaximum,72,
                                               XmNorientation,XmHORIZONTAL,
                                               XmNshowValue,TRUE,
					                                     XmNvalue,int(1E6/PlayingField::uSecondsPerFrame+.5),
                                               XmNtopAttachment,XmATTACH_WIDGET,
                                               XmNtopWidget,framesPerSecondLabel,
                                               XmNbottomAttachment,XmATTACH_NONE,
                                               XmNleftAttachment,XmATTACH_FORM,
                                               XmNrightAttachment,XmATTACH_WIDGET,
                                               XmNrightWidget,verticalSeparator1,
                                               NULL);
  XtAddCallback(framesPerSecondScale,XmNvalueChangedCallback,ApplyFramesPerSecond,this);


/********** Create Global Maximum Velocity Label Gadget **********/

  string=XmStringCreateLocalized("Global Maximum Velocity (pixels/sec)");
  globalMaxVelLabel=XtVaCreateManagedWidget("globalMaxVelLabel",
                                            xmLabelGadgetClass,mainForm,
                                            XmNbackground,background,
                                            XmNforeground,foreground,
                                            XmNmarginTop,7,
                                            XmNlabelString,string,
                                            XmNtopAttachment,XmATTACH_WIDGET,
                                            XmNtopWidget,framesPerSecondScale,
                                            XmNbottomAttachment,XmATTACH_NONE,
                                            XmNleftAttachment,XmATTACH_FORM,
                                            XmNrightAttachment,XmATTACH_WIDGET,
                                            XmNrightWidget,verticalSeparator1,
	                                          NULL);
  XmStringFree(string);


/********** Create Global Maximum Velocity TextField Widget **********/

  MakeString(1E6*PlayingField::maxLinearVelocity/PlayingField::uSecondsPerFrame);
  globalMaxVelValue=XtVaCreateManagedWidget("globalMaxVelValue",
                                            xmTextFieldWidgetClass,mainForm,
                                            XmNbackground,background,
                                            XmNforeground,foreground,
                                            XmNbackground,background,
                                            XmNforeground,foreground,
                                            XmNvalue,str,
                                            XmNcursorPosition,strlen(str),
                                            XmNtopAttachment,XmATTACH_WIDGET,
                                            XmNtopWidget,globalMaxVelLabel,
                                            XmNbottomAttachment,XmATTACH_NONE,
                                            XmNleftAttachment,XmATTACH_FORM,
                                            XmNrightAttachment,XmATTACH_WIDGET,
                                            XmNrightWidget,verticalSeparator1,
                                            NULL);
  XtAddCallback(globalMaxVelValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(globalMaxVelValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(globalMaxVelValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(globalMaxVelValue,XmNlosingFocusCallback,ApplyGlobalMaxVel,this);


/********** Create Universal Gravitational Constant Label Gadget **********/

  string=XmStringCreateLocalized("Universal Gravitational Constant");
  universalGravitationalConstantLabel=XtVaCreateManagedWidget(
                                            "universalGravitationalConstantLabel",
                                            xmLabelGadgetClass,mainForm,
                                            XmNbackground,background,
                                            XmNforeground,foreground,
                                            XmNmarginTop,7,
                                            XmNlabelString,string,
                                            XmNtopAttachment,XmATTACH_WIDGET,
                                            XmNtopWidget,globalMaxVelValue,
                                            XmNbottomAttachment,XmATTACH_NONE,
                                            XmNleftAttachment,XmATTACH_FORM,
                                            XmNrightAttachment,XmATTACH_WIDGET,
                                            XmNrightWidget,verticalSeparator1,
	                                          NULL);
  XmStringFree(string);


/********** Create Universal Gravitational Constant TextField Widget **********/

  MakeString(PlayingField::universalGravitationalConst);
  universalGravitationalConstantValue=XtVaCreateManagedWidget(
                                            "universalGravitationalConstantValue",
                                            xmTextFieldWidgetClass,mainForm,
                                            XmNbackground,background,
                                            XmNforeground,foreground,
                                            XmNvalue,str,
                                            XmNcursorPosition,strlen(str),
                                            XmNtopAttachment,XmATTACH_WIDGET,
                                            XmNtopWidget,universalGravitationalConstantLabel,
                                            XmNbottomAttachment,XmATTACH_NONE,
                                            XmNleftAttachment,XmATTACH_FORM,
                                            XmNrightAttachment,XmATTACH_WIDGET,
                                            XmNrightWidget,verticalSeparator1,
                                            NULL);
  XtAddCallback(universalGravitationalConstantValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(universalGravitationalConstantValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(universalGravitationalConstantValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(universalGravitationalConstantValue,XmNlosingFocusCallback,
                ApplyUniversalGravitationalConstant,this);


/********** Create Horizontal Separator 3 Gadget **********/

  horizontalSeparator3=XtVaCreateManagedWidget("horizontalSeparator3",xmSeparatorGadgetClass,mainForm,
                                               XmNbackground,background,
                                               XmNforeground,foreground,
                                               XmNsensitive,FALSE,
                                               XmNheight,30,
                                               XmNshadowThickness,4,
                                               XmNtopAttachment,XmATTACH_WIDGET,
                                               XmNtopWidget,universalGravitationalConstantValue,
                                               XmNbottomAttachment,XmATTACH_NONE,
                                               XmNleftAttachment,XmATTACH_FORM,
                                               XmNrightAttachment,XmATTACH_WIDGET,
                                               XmNrightWidget,verticalSeparator1,
                                               NULL);


/********** Create Scoring Label Gadget **********/

  string=XmStringCreateLocalized("Object Score Values");
  scoringLabel=XtVaCreateManagedWidget("scoringLabel",
                                       xmLabelGadgetClass,mainForm,
                                       XmNbackground,background,
                                       XmNforeground,foreground,
                                       XmNlabelString,string,
                                       XmNtopAttachment,XmATTACH_WIDGET,
                                       XmNtopWidget,horizontalSeparator3,
                                       XmNbottomAttachment,XmATTACH_NONE,
                                       XmNleftAttachment,XmATTACH_FORM,
                                       XmNrightAttachment,XmATTACH_WIDGET,
                                       XmNrightWidget,verticalSeparator1,
	                                     NULL);
  XmStringFree(string);


/********** Create ROCK Score Label Gadget **********/

  ROCKScoreLabel=XtVaCreateManagedWidget("ROCKScoreLabel",
                                          xmLabelGadgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNwidth,ROCKScoringIcon_width+32,
                                          XmNmarginWidth,10,
                                          XmNmarginHeight,0,
                                          XmNmarginTop,8,
                                          XmNmarginLeft,5,
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,scoringLabel,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_FORM,
                                          XmNrightAttachment,XmATTACH_NONE,
                                          NULL);
  SetScore(ROCKScoreLabel,ROCK::score);


/********** Create ROCK Pixmap Label Gadget **********/

  CreateScoringIconPixmaps(ROCKScoringIcon_bits,ROCKScoringIcon_width,ROCKScoringIcon_height,
			   RockGroup::RockColor.pixel,ROCKIconPixmap);
  ROCKPixmapLabel=XtVaCreateManagedWidget("ROCKPixmapLabel",
                                          xmLabelGadgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNmarginWidth,10,
                                          XmNmarginLeft,5,
                                          XmNlabelType,XmPIXMAP,
                                          XmNlabelPixmap,ROCKIconPixmap,
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,ROCKScoreLabel,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_FORM,
                                          XmNrightAttachment,XmATTACH_NONE,
	                                        NULL);


/********** Create ROck Score Label Gadget **********/

  ROckScoreLabel=XtVaCreateManagedWidget("ROckScoreLabel",
                                          xmLabelGadgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNwidth,ROCKScoringIcon_width+32,
                                          XmNmarginWidth,10,
                                          XmNmarginHeight,0,
                                          XmNmarginTop,8,
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,scoringLabel,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_WIDGET,
                                          XmNleftWidget,ROCKScoreLabel,
                                          XmNrightAttachment,XmATTACH_NONE,
                                          NULL);
  SetScore(ROckScoreLabel,ROck::score);


/********** Create ROck Pixmap Label Gadget **********/

  CreateScoringIconPixmaps(ROckScoringIcon_bits,ROckScoringIcon_width,ROckScoringIcon_height,
			   RockGroup::RockColor.pixel,ROckIconPixmap);
  ROckPixmapLabel=XtVaCreateManagedWidget("ROckPixmapLabel",
                                          xmLabelGadgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNmarginWidth,10,
                                          XmNlabelType,XmPIXMAP,
                                          XmNlabelPixmap,ROckIconPixmap,
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,ROckScoreLabel,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_WIDGET,
                                          XmNleftWidget,ROCKPixmapLabel,
                                          XmNrightAttachment,XmATTACH_NONE,
	                                        NULL);


/********** Create rock Score Label Gadget **********/

  rockScoreLabel=XtVaCreateManagedWidget("rockScoreLabel",
                                          xmLabelGadgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNwidth,ROCKScoringIcon_width+32,
                                          XmNmarginWidth,10,
                                          XmNmarginHeight,0,
                                          XmNmarginTop,8,
                                          XmNmarginRight,5,
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,scoringLabel,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_WIDGET,
                                          XmNleftWidget,ROckScoreLabel,
                                          XmNrightAttachment,XmATTACH_NONE,
                                          NULL);
  SetScore(rockScoreLabel,rock::score);


/********** Create rock Pixmap Label Gadget **********/

  CreateScoringIconPixmaps(rockScoringIcon_bits,rockScoringIcon_width,rockScoringIcon_height,
			   RockGroup::RockColor.pixel,rockIconPixmap);
  rockPixmapLabel=XtVaCreateManagedWidget("rockPixmapLabel",
                                          xmLabelGadgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNmarginWidth,10,
                                          XmNmarginRight,5,
                                          XmNlabelType,XmPIXMAP,
                                          XmNlabelPixmap,rockIconPixmap,
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,ROckScoreLabel,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_WIDGET,
                                          XmNleftWidget,ROckPixmapLabel,
                                          XmNrightAttachment,XmATTACH_WIDGET,
                                          XmNrightWidget,verticalSeparator1,
	                                        NULL);


/********** Create ENEMY Score Label Gadget **********/

  ENEMYScoreLabel=XtVaCreateManagedWidget("ENEMYScoreLabel",
                                          xmLabelGadgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNwidth,ROCKScoringIcon_width+32,
                                          XmNmarginWidth,10,
                                          XmNmarginHeight,0,
                                          XmNmarginTop,10,
                                          XmNmarginLeft,5,
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,ROCKPixmapLabel,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_FORM,
                                          XmNrightAttachment,XmATTACH_NONE,
                                          NULL);
  SetScore(ENEMYScoreLabel,ENEMY::score);


/********** Create ENEMY Pixmap Label Gadget **********/

  CreateScoringIconPixmaps(ENEMYScoringIcon_bits,ENEMYScoringIcon_width,ENEMYScoringIcon_height,
			   ENEMY::color.pixel,ENEMYIconPixmap);
  ENEMYPixmapLabel=XtVaCreateManagedWidget("ENEMYPixmapLabel",
                                           xmLabelGadgetClass,mainForm,
                                           XmNbackground,background,
                                           XmNforeground,foreground,
                                           XmNmarginWidth,10,
                                           XmNmarginLeft,5,
                                           XmNlabelType,XmPIXMAP,
                                           XmNlabelPixmap,ENEMYIconPixmap,
                                           XmNtopAttachment,XmATTACH_WIDGET,
                                           XmNtopWidget,ENEMYScoreLabel,
                                           XmNbottomAttachment,XmATTACH_NONE,
                                           XmNleftAttachment,XmATTACH_FORM,
                                           XmNrightAttachment,XmATTACH_NONE,
	                                         NULL);


/********** Create enemy Score Label Gadget **********/

  enemyScoreLabel=XtVaCreateManagedWidget("enemyScoreLabel",
                                          xmLabelGadgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNwidth,ROCKScoringIcon_width+32,
                                          XmNmarginWidth,10,
                                          XmNmarginHeight,0,
                                          XmNmarginTop,10,
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,ROckPixmapLabel,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_WIDGET,
                                          XmNleftWidget,ENEMYScoreLabel,
                                          XmNrightAttachment,XmATTACH_NONE,
                                          NULL);
  SetScore(enemyScoreLabel,enemy::score);


/********** Create enemy Pixmap Label Gadget **********/

  CreateScoringIconPixmaps(enemyScoringIcon_bits,enemyScoringIcon_width,enemyScoringIcon_height,
			   enemy::color.pixel,enemyIconPixmap);
  enemyPixmapLabel=XtVaCreateManagedWidget("enemyPixmapLabel",
                                           xmLabelGadgetClass,mainForm,
                                           XmNbackground,background,
                                           XmNforeground,foreground,
                                           XmNmarginWidth,10,
                                           XmNlabelType,XmPIXMAP,
                                           XmNlabelPixmap,enemyIconPixmap,
                                           XmNtopAttachment,XmATTACH_WIDGET,
                                           XmNtopWidget,enemyScoreLabel,
                                           XmNbottomAttachment,XmATTACH_NONE,
                                           XmNleftAttachment,XmATTACH_WIDGET,
                                           XmNleftWidget,ENEMYPixmapLabel,
                                           XmNrightAttachment,XmATTACH_NONE,
	                                         NULL);


/********** Create bullet Score Label Gadget **********/

  bulletScoreLabel=XtVaCreateManagedWidget("bulletScoreLabel",
                                           xmLabelGadgetClass,mainForm,
                                           XmNbackground,background,
                                           XmNforeground,foreground,
                                           XmNwidth,ROCKScoringIcon_width+32,
                                           XmNmarginWidth,10,
                                           XmNmarginHeight,0,
                                           XmNmarginTop,10,
                                           XmNmarginRight,5,
                                           XmNtopAttachment,XmATTACH_WIDGET,
                                           XmNtopWidget,rockPixmapLabel,
                                           XmNbottomAttachment,XmATTACH_NONE,
                                           XmNleftAttachment,XmATTACH_WIDGET,
                                           XmNleftWidget,enemyScoreLabel,
                                           XmNrightAttachment,XmATTACH_NONE,
                                           NULL);
  SetScore(bulletScoreLabel,EnemyBullet::score);


/********** Create bullet Pixmap Label Gadget **********/

  CreateScoringIconPixmaps(bulletScoringIcon_bits,bulletScoringIcon_width,bulletScoringIcon_height,
			   EnemyBulletGroup::color.pixel,bulletIconPixmap);
  bulletPixmapLabel=XtVaCreateManagedWidget("bulletPixmapLabel",
                                            xmLabelGadgetClass,mainForm,
                                            XmNbackground,background,
                                            XmNforeground,foreground,
                                            XmNmarginWidth,10,
                                            XmNmarginRight,5,
                                            XmNlabelType,XmPIXMAP,
                                            XmNlabelPixmap,bulletIconPixmap,
                                            XmNtopAttachment,XmATTACH_WIDGET,
                                            XmNtopWidget,bulletScoreLabel,
                                            XmNbottomAttachment,XmATTACH_NONE,
                                            XmNleftAttachment,XmATTACH_WIDGET,
                                            XmNleftWidget,enemyPixmapLabel,
                                            XmNrightAttachment,XmATTACH_WIDGET,
                                            XmNrightWidget,verticalSeparator1,
                                            NULL);


/********** Create Relativistic Mass Toggle Button Gadget **********/

string=XmStringCreateLocalized("Relativistic Mass (Global\n  Maximum Velocity = 0.999c)");
relativisticMass=XtVaCreateManagedWidget("relativisticMass",
                                         xmToggleButtonGadgetClass,mainForm,
                                         XmNbackground,background,
                                         XmNforeground,foreground,
                                         XmNmarginRight,35,
                                         XmNlabelString,string,
                                         XmNindicatorSize,20,
                                         XmNset,PlayingField::relativisticMass,
                                         XmNtopAttachment,XmATTACH_FORM,
                                         XmNbottomAttachment,XmATTACH_NONE,
                                         XmNleftAttachment,XmATTACH_WIDGET,
                                         XmNleftWidget,verticalSeparator1,
                                         XmNrightAttachment,XmATTACH_NONE,
                                         NULL);
XmStringFree(string);
XtAddCallback(relativisticMass,XmNvalueChangedCallback,ApplyRelativisticMass,this);


/********** Create Vertical Separator 2 Gadget **********/

verticalSeparator2=XtVaCreateManagedWidget("verticalSeparator2",
                                           xmSeparatorGadgetClass,mainForm,
                                           XmNbackground,background,
                                           XmNforeground,foreground,
                                           XmNsensitive,FALSE,
                                           XmNwidth,14,
                                           XmNorientation,XmVERTICAL,
                                           XmNshadowThickness,4,
                                           XmNtopAttachment,XmATTACH_FORM,
                                           XmNbottomAttachment,XmATTACH_FORM,
                                           XmNleftAttachment,XmATTACH_WIDGET,
                                           XmNleftWidget,relativisticMass,
                                           XmNrightAttachment,XmATTACH_NONE,
                                           NULL);


/********** Create Horizontal Separator 4 Gadget **********/

horizontalSeparator4=XtVaCreateManagedWidget("horizontalSeparator4",
                                             xmSeparatorGadgetClass,mainForm,
                                             XmNbackground,background,
                                             XmNforeground,foreground,
                                             XmNsensitive,FALSE,
                                             XmNheight,20,
                                             XmNshadowThickness,4,
                                             XmNtopAttachment,XmATTACH_WIDGET,
                                             XmNtopWidget,relativisticMass,
                                             XmNbottomAttachment,XmATTACH_NONE,
                                             XmNleftAttachment,XmATTACH_WIDGET,
                                             XmNleftWidget,verticalSeparator1,
                                             XmNrightAttachment,XmATTACH_WIDGET,
                                             XmNrightWidget,verticalSeparator2,
                                             NULL);


/********** Create Ship Shape Label Gadget **********/

  string=XmStringCreateLocalized("Ship Shape");
  shipShapeLabel=XtVaCreateManagedWidget("shipShapeLabel",
                                         xmLabelGadgetClass,mainForm,
                                         XmNbackground,background,
                                         XmNforeground,foreground,
                                         XmNwidth,232,
                                         XmNlabelString,string,
                                         XmNtopAttachment,XmATTACH_WIDGET,
                                         XmNtopWidget,horizontalSeparator4,
                                         XmNbottomAttachment,XmATTACH_NONE,
                                         XmNleftAttachment,XmATTACH_WIDGET,
                                         XmNleftWidget,verticalSeparator1,
                                         XmNrightAttachment,XmATTACH_NONE,
	                                       NULL);
  XmStringFree(string);


/********** Create Ship Shape Row Column Widget **********/

  shipShape=XtVaCreateManagedWidget("shipShape",xmRowColumnWidgetClass,mainForm,
                                    XmNbackground,background,
                                    XmNforeground,foreground,
                                    XmNmarginWidth,34,
                                    XmNmarginHeight,0,
                                    XmNspacing,15,
                                    XmNisHomogeneous,TRUE,
                                    XmNentryClass,xmToggleButtonGadgetClass,
                                    XmNorientation,XmHORIZONTAL,
                                    XmNnumColumns,1,
                                    XmNradioBehavior,TRUE,
                                    XmNtopAttachment,XmATTACH_WIDGET,
                                    XmNtopWidget,shipShapeLabel,
                                    XmNbottomAttachment,XmATTACH_NONE,
                                    XmNleftAttachment,XmATTACH_WIDGET,
                                    XmNleftWidget,verticalSeparator1,
                                    XmNrightAttachment,XmATTACH_WIDGET,
                                    XmNrightWidget,verticalSeparator2,
                                    NULL);


/********** Create Ship Star Destroyer Toggle Button Gadget **********/

  CreateToggleButtonPixmaps(shipGroup.starDestroyer.icon,
                            shipGroup.starDestroyer.iconWidth,
                            shipGroup.starDestroyer.iconHeight,
                            shipGroup.starDestroyer.iconColor.pixel,
                            starDestroyerSelectedPixmap,
                            starDestroyerNotSelectedPixmap);
  shipStarDestroyer=XtVaCreateManagedWidget("shipStarDestroyer",
                                            xmToggleButtonGadgetClass,shipShape,
                                            XmNbackground,background,
                                            XmNforeground,foreground,
                                            XmNshadowThickness,2,
                                            XmNset,shipGroup.ship==&shipGroup.starDestroyer,
                                            XmNindicatorOn,FALSE,
                                            XmNselectPixmap,starDestroyerSelectedPixmap,
                                            XmNlabelType,XmPIXMAP,
                                            XmNlabelPixmap,starDestroyerNotSelectedPixmap,
                                            NULL);
  XtAddCallback(shipStarDestroyer,XmNvalueChangedCallback,ApplyStarDestroyerShipShape,this);


/********** Create Ship NCC1701A Toggle Button Gadget **********/

  CreateToggleButtonPixmaps(shipGroup.NCC1701A.icon,
                            shipGroup.NCC1701A.iconWidth,
                            shipGroup.NCC1701A.iconHeight,
                            shipGroup.NCC1701A.iconColor.pixel,
                            NCC1701ASelectedPixmap,
                            NCC1701ANotSelectedPixmap);
  shipNCC1701A=XtVaCreateManagedWidget("shipNCC1701A",
                                       xmToggleButtonGadgetClass,shipShape,
                                       XmNshadowThickness,2,
                                       XmNset,shipGroup.ship==&shipGroup.NCC1701A,
                                       XmNindicatorOn,FALSE,
                                       XmNselectPixmap,NCC1701ASelectedPixmap,
                                       XmNlabelType,XmPIXMAP,
                                       XmNlabelPixmap,NCC1701ANotSelectedPixmap,
                                       NULL);
  XtAddCallback(shipNCC1701A,XmNvalueChangedCallback,ApplyNCC1701AShipShape,this);


/********** Create Ship NCC1701D Toggle Button Gadget **********/

  CreateToggleButtonPixmaps(shipGroup.NCC1701D.icon,
                            shipGroup.NCC1701D.iconWidth,
                            shipGroup.NCC1701D.iconHeight,
                            shipGroup.NCC1701D.iconColor.pixel,
                            NCC1701DSelectedPixmap,
                            NCC1701DNotSelectedPixmap);
  shipNCC1701D=XtVaCreateManagedWidget("shipNCC1701D",
                                       xmToggleButtonGadgetClass,shipShape,
                                       XmNbackground,background,
                                       XmNforeground,foreground,
                                       XmNshadowThickness,2,
                                       XmNset,shipGroup.ship==&shipGroup.NCC1701D,
                                       XmNindicatorOn,FALSE,
                                       XmNselectPixmap,NCC1701DSelectedPixmap,
                                       XmNlabelType,XmPIXMAP,
                                       XmNlabelPixmap,NCC1701DNotSelectedPixmap,
                                       NULL);
  XtAddCallback(shipNCC1701D,XmNvalueChangedCallback,ApplyNCC1701DShipShape,this);


/********** Create Ship Acceleration Label Gadget **********/

  string=XmStringCreateLocalized("Ship Acceleration (pixels/sec/sec)");
  shipAccelLabel=XtVaCreateManagedWidget("shipAccelLabel",
                                          xmLabelGadgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNmarginTop,10,
                                          XmNlabelString,string,
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,shipShape,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_WIDGET,
                                          XmNleftWidget,verticalSeparator1,
                                          XmNrightAttachment,XmATTACH_WIDGET,
                                          XmNrightWidget,verticalSeparator2,
	                                        NULL);
  XmStringFree(string);


/********** Create Ship Acceleration TextField Widget **********/

  MakeString(1E12*Ship::acceleration
             /(double(PlayingField::uSecondsPerFrame)*PlayingField::uSecondsPerFrame));
  shipAccelValue=XtVaCreateManagedWidget("shipAccelValue",
                                          xmTextFieldWidgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNvalue,str,
                                          XmNcursorPosition,strlen(str),
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,shipAccelLabel,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_WIDGET,
                                          XmNleftWidget,verticalSeparator1,
                                          XmNrightAttachment,XmATTACH_WIDGET,
                                          XmNrightWidget,verticalSeparator2,
                                          NULL);
  XtAddCallback(shipAccelValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(shipAccelValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(shipAccelValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(shipAccelValue,XmNlosingFocusCallback,ApplyShipAccel,this);


/********** Create Ship Maximum Velocity Label Gadget **********/

  string=XmStringCreateLocalized("Ship Maximum Velocity (pixels/sec)");
  shipMaxVelLabel=XtVaCreateManagedWidget("shipMaxVelLabel",
                                          xmLabelGadgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNmarginTop,7,
                                          XmNlabelString,string,
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,shipAccelValue,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_WIDGET,
                                          XmNleftWidget,verticalSeparator1,
                                          XmNrightAttachment,XmATTACH_WIDGET,
                                          XmNrightWidget,verticalSeparator2,
                                          NULL);
  XmStringFree(string);


/********** Create Ship Maximum Velocity TextField Widget **********/

  MakeString(1E6*Ship::maxVelocity/PlayingField::uSecondsPerFrame);
  shipMaxVelValue=XtVaCreateManagedWidget("shipMaxVelValue",
                                          xmTextFieldWidgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNvalue,str,
                                          XmNcursorPosition,strlen(str),
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,shipMaxVelLabel,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_WIDGET,
                                          XmNleftWidget,verticalSeparator1,
                                          XmNrightAttachment,XmATTACH_WIDGET,
                                          XmNrightWidget,verticalSeparator2,
                                          NULL);
  XtAddCallback(shipMaxVelValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(shipMaxVelValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(shipMaxVelValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(shipMaxVelValue,XmNlosingFocusCallback,ApplyShipMaxVel,this);


/********** Create Ship Rotational Velocity Label Gadget **********/

  string=XmStringCreateLocalized("Ship Rotational Velocity (radians/sec)");
  shipRotationalVelLabel=XtVaCreateManagedWidget("shipRotationalVelLabel",
                                                 xmLabelGadgetClass,mainForm,
                                                 XmNbackground,background,
                                                 XmNforeground,foreground,
                                                 XmNmarginTop,7,
                                                 XmNlabelString,string,
                                                 XmNtopAttachment,XmATTACH_WIDGET,
                                                 XmNtopWidget,shipMaxVelValue,
                                                 XmNbottomAttachment,XmATTACH_NONE,
                                                 XmNleftAttachment,XmATTACH_WIDGET,
                                                 XmNleftWidget,verticalSeparator1,
                                                 XmNrightAttachment,XmATTACH_WIDGET,
                                                 XmNrightWidget,verticalSeparator2,
                                                 NULL);
  XmStringFree(string);


/********** Create Ship Rotational Velocity TextField Widget **********/

  MakeString(1E6*Ship::angularVelocity/PlayingField::uSecondsPerFrame);
  shipRotationalVelValue=XtVaCreateManagedWidget("shipRotationalVelValue",
                                                 xmTextFieldWidgetClass,mainForm,
                                                 XmNbackground,background,
                                                 XmNforeground,foreground,
                                                 XmNvalue,str,
                                                 XmNcursorPosition,strlen(str),
                                                 XmNtopAttachment,XmATTACH_WIDGET,
                                                 XmNtopWidget,shipRotationalVelLabel,
                                                 XmNbottomAttachment,XmATTACH_NONE,
                                                 XmNleftAttachment,XmATTACH_WIDGET,
                                                 XmNleftWidget,verticalSeparator1,
                                                 XmNrightAttachment,XmATTACH_WIDGET,
                                                 XmNrightWidget,verticalSeparator2,
                                                 NULL);
  XtAddCallback(shipRotationalVelValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(shipRotationalVelValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(shipRotationalVelValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(shipRotationalVelValue,XmNlosingFocusCallback,ApplyShipRotationalVel,this);


/********** Create Hyperspace Destruct Rate Label 1 Label Gadget **********/

  string=XmStringCreateLocalized("Hyperspace Destruct Rate");
  hyperspaceDestructRateLabel1=XtVaCreateManagedWidget("hyperspaceDestructRateLabel1",
                                                       xmLabelGadgetClass,mainForm,
                                                       XmNbackground,background,
                                                       XmNforeground,foreground,
                                                       XmNmarginTop,7,
                                                       XmNlabelString,string,
                                                       XmNtopAttachment,XmATTACH_WIDGET,
                                                       XmNtopWidget,shipRotationalVelValue,
                                                       XmNbottomAttachment,XmATTACH_NONE,
                                                       XmNleftAttachment,XmATTACH_WIDGET,
                                                       XmNleftWidget,verticalSeparator1,
                                                       XmNrightAttachment,XmATTACH_WIDGET,
                                                       XmNrightWidget,verticalSeparator2,
	                                                     NULL);
  XmStringFree(string);


/********** Create Hyperspace Destruct Rate Label 2 Label Gadget *********/

  string=XmStringCreateLocalized("(cumulative % chance of destruction)");
  hyperspaceDestructRateLabel2=XtVaCreateManagedWidget("hyperspaceDestructRateLabel2",
                                                       xmLabelGadgetClass,mainForm,
                                                       XmNbackground,background,
                                                       XmNforeground,foreground,
                                                       XmNlabelString,string,
                                                       XmNmarginHeight,0,
                                                       XmNmarginBottom,2,
                                                       XmNtopAttachment,XmATTACH_WIDGET,
                                                       XmNtopWidget,hyperspaceDestructRateLabel1,
                                                       XmNbottomAttachment,XmATTACH_NONE,
                                                       XmNleftAttachment,XmATTACH_WIDGET,
                                                       XmNleftWidget,verticalSeparator1,
                                                       XmNrightAttachment,XmATTACH_WIDGET,
                                                       XmNrightWidget,verticalSeparator2,
	                                                     NULL);
  XmStringFree(string);


/********** Create Hyperspace Destruct Rate Text Field Widget **********/

  MakeString(Hyper::percentDestructRate);
  hyperspaceDestructRateValue=XtVaCreateManagedWidget("hyperspaceDestructRateValue",
                                                      xmTextFieldWidgetClass,mainForm,
                                                      XmNbackground,background,
                                                      XmNforeground,foreground,
                                                      XmNvalue,str,
                                                      XmNcursorPosition,strlen(str),
                                                      XmNtopAttachment,XmATTACH_WIDGET,
                                                      XmNtopWidget,hyperspaceDestructRateLabel2,
                                                      XmNbottomAttachment,XmATTACH_NONE,
                                                      XmNleftAttachment,XmATTACH_WIDGET,
                                                      XmNleftWidget,verticalSeparator1,
                                                      XmNrightAttachment,XmATTACH_WIDGET,
                                                      XmNrightWidget,verticalSeparator2,
                                                      NULL);
  XtAddCallback(hyperspaceDestructRateValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(hyperspaceDestructRateValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(hyperspaceDestructRateValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(hyperspaceDestructRateValue,XmNlosingFocusCallback,ApplyHyperspaceDestructRate,this);


/********** Create Initial Ships Label Gadget **********/

  string=XmStringCreateLocalized("Initial Number of Ships");
  initialShipsLabel=XtVaCreateManagedWidget("initialShipsLabel",
                                            xmLabelGadgetClass,mainForm,
                                            XmNbackground,background,
                                            XmNforeground,foreground,
                                            XmNmarginTop,7,
                                            XmNlabelString,string,
                                            XmNtopAttachment,XmATTACH_WIDGET,
                                            XmNtopWidget,hyperspaceDestructRateValue,
                                            XmNbottomAttachment,XmATTACH_NONE,
                                            XmNleftAttachment,XmATTACH_WIDGET,
                                            XmNleftWidget,verticalSeparator1,
                                            XmNrightAttachment,XmATTACH_WIDGET,
                                            XmNrightWidget,verticalSeparator2,
                                            NULL);
  XmStringFree(string);

/********** Create Initial Ships Scale Widget **********/

  initialShipsScale=XtVaCreateManagedWidget("initialShipsScale",
                                            xmScaleWidgetClass,mainForm,
                                            XmNbackground,background,
                                            XmNforeground,foreground,
                                            XmNminimum,minInitialShips,
                                            XmNmaximum,maxInitialShips,
                                            XmNorientation,XmHORIZONTAL,
                                            XmNshowValue,TRUE,
                                            XmNvalue,PlayingField::initialShips,
                                            XmNtopAttachment,XmATTACH_WIDGET,
                                            XmNtopWidget,initialShipsLabel,
                                            XmNbottomAttachment,XmATTACH_NONE,
                                            XmNleftAttachment,XmATTACH_WIDGET,
                                            XmNleftWidget,verticalSeparator1,
                                            XmNrightAttachment,XmATTACH_WIDGET,
                                            XmNrightWidget,verticalSeparator2,
                                            NULL);
  XtAddCallback(initialShipsScale,XmNvalueChangedCallback,ApplyInitialShips,this);


/********** Create Extra Ship Score Label Gadget **********/

  string=XmStringCreateLocalized("Extra Ship Score");
  extraShipScoreLabel=XtVaCreateManagedWidget("extraShipScoreLabel",
                                              xmLabelGadgetClass,mainForm,
                                              XmNbackground,background,
                                              XmNforeground,foreground,
                                              XmNmarginTop,7,
                                              XmNlabelString,string,
                                              XmNtopAttachment,XmATTACH_WIDGET,
                                              XmNtopWidget,initialShipsScale,
                                              XmNbottomAttachment,XmATTACH_NONE,
                                              XmNleftAttachment,XmATTACH_WIDGET,
                                              XmNleftWidget,verticalSeparator1,
                                              XmNrightAttachment,XmATTACH_WIDGET,
                                              XmNrightWidget,verticalSeparator2,
                                              NULL);
  XmStringFree(string);


/********** Create Extra Ship Score TextField Widget **********/

  MakeString(PlayingField::extraShipScore);
  extraShipScoreValue=XtVaCreateManagedWidget("extraShipScoreValue",
                                              xmTextFieldWidgetClass,mainForm,
                                              XmNbackground,background,
                                              XmNforeground,foreground,
                                              XmNvalue,str,
                                              XmNcursorPosition,strlen(str),
                                              XmNtopAttachment,XmATTACH_WIDGET,
                                              XmNtopWidget,extraShipScoreLabel,
                                              XmNbottomAttachment,XmATTACH_NONE,
                                              XmNleftAttachment,XmATTACH_WIDGET,
                                              XmNleftWidget,verticalSeparator1,
                                              XmNrightAttachment,XmATTACH_WIDGET,
                                              XmNrightWidget,verticalSeparator2,
                                              NULL);
  XtAddCallback(extraShipScoreValue,XmNfocusCallback,SetIntEnterValue,this);
  XtAddCallback(extraShipScoreValue,XmNactivateCallback,VerifyIntTextField,this);
  XtAddCallback(extraShipScoreValue,XmNlosingFocusCallback,VerifyIntTextField,this);
  XtAddCallback(extraShipScoreValue,XmNlosingFocusCallback,ApplyExtraShipScore,this);


/********** Create Automatic Fire Toggle Button Gadget **********/

  string=XmStringCreateLocalized("Automatic Firing");
  autoFire=XtVaCreateManagedWidget("autoFire",
                                   xmToggleButtonGadgetClass,mainForm,
                                   XmNbackground,background,
                                   XmNforeground,foreground,
                                   XmNheight,40,
                                   XmNmarginRight,81,
                                   XmNlabelString,string,
                                   XmNindicatorSize,20,
                                   XmNset,ShipBulletGroup::autoFire,
                                   XmNtopAttachment,XmATTACH_WIDGET,
                                   XmNtopWidget,extraShipScoreValue,
                                   XmNbottomAttachment,XmATTACH_NONE,
                                   XmNleftAttachment,XmATTACH_WIDGET,
                                   XmNleftWidget,verticalSeparator1,
                                   XmNrightAttachment,XmATTACH_WIDGET,
                                   XmNrightWidget,verticalSeparator2,
                                   NULL);
  XmStringFree(string);
  XtAddCallback(autoFire,XmNvalueChangedCallback,ApplyAutoFire,this);


/********** Create Ship Bullet Velocity Label Gadget **********/

  string=XmStringCreateLocalized("Ship Bullet Velocity (pixels/sec)");
  shipBulletVelLabel=XtVaCreateManagedWidget("shipBulletVelLabel",
                                             xmLabelGadgetClass,mainForm,
                                             XmNbackground,background,
                                             XmNforeground,foreground,
                                             XmNwidth,208,
                                             XmNlabelString,string,
                                             XmNtopAttachment,XmATTACH_FORM,
                                             XmNbottomAttachment,XmATTACH_NONE,
                                             XmNleftAttachment,XmATTACH_WIDGET,
                                             XmNleftWidget,verticalSeparator2,
                                             XmNrightAttachment,XmATTACH_NONE,
                                             NULL);
  XmStringFree(string);


/********** Create Vertical Separator 3 Gadget **********/

  verticalSeparator3=XtVaCreateManagedWidget("verticalSeparator3",xmSeparatorGadgetClass,mainForm,
                                             XmNbackground,background,
                                             XmNforeground,foreground,
                                             XmNsensitive,FALSE,
                                             XmNwidth,14,
                                             XmNorientation,XmVERTICAL,
                                             XmNshadowThickness,4,
                                             XmNtopAttachment,XmATTACH_FORM,
                                             XmNbottomAttachment,XmATTACH_FORM,
                                             XmNleftAttachment,XmATTACH_WIDGET,
                                             XmNleftWidget,shipBulletVelLabel,
                                             XmNrightAttachment,XmATTACH_NONE,
                                             NULL);


/********** Create Ship Bullet Velocity TextField Widget **********/

  MakeString(1E6*ShipBullet::velocity/PlayingField::uSecondsPerFrame);
  shipBulletVelValue=XtVaCreateManagedWidget("shipBulletVelValue",
                                              xmTextFieldWidgetClass,mainForm,
                                              XmNbackground,background,
                                              XmNforeground,foreground,
                                              XmNvalue,str,
                                              XmNcursorPosition,strlen(str),
                                              XmNtopAttachment,XmATTACH_WIDGET,
                                              XmNtopWidget,shipBulletVelLabel,
                                              XmNbottomAttachment,XmATTACH_NONE,
                                              XmNleftAttachment,XmATTACH_WIDGET,
                                              XmNleftWidget,verticalSeparator2,
                                              XmNrightAttachment,XmATTACH_WIDGET,
                                              XmNrightWidget,verticalSeparator3,
                                              NULL);
  XtAddCallback(shipBulletVelValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(shipBulletVelValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(shipBulletVelValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(shipBulletVelValue,XmNlosingFocusCallback,ApplyShipBulletVel,this);


/********** Create Ship Bullet Duration Label Gadget **********/

  string=XmStringCreateLocalized("Ship Bullet Duration (seconds)");
  shipBulletDurationLabel=XtVaCreateManagedWidget("shipBulletDurationLabel",
                                             xmLabelGadgetClass,mainForm,
                                             XmNbackground,background,
                                             XmNforeground,foreground,
                                             XmNmarginTop,7,
                                             XmNlabelString,string,
                                             XmNtopAttachment,XmATTACH_WIDGET,
                                             XmNtopWidget,shipBulletVelValue,
                                             XmNbottomAttachment,XmATTACH_NONE,
                                             XmNleftAttachment,XmATTACH_WIDGET,
                                             XmNleftWidget,verticalSeparator2,
                                             XmNrightAttachment,XmATTACH_WIDGET,
                                             XmNrightWidget,verticalSeparator3,
                                             NULL);
  XmStringFree(string);


/********** Create Ship Bullet Duration TextField Widget **********/

  MakeString(1E-6*ShipBullet::numFrames*PlayingField::uSecondsPerFrame);
  shipBulletDurationValue=XtVaCreateManagedWidget("shipBulletDurationValue",
                                                  xmTextFieldWidgetClass,mainForm,
                                                  XmNbackground,background,
                                                  XmNforeground,foreground,
                                                  XmNvalue,str,
                                                  XmNcursorPosition,strlen(str),
                                                  XmNtopAttachment,XmATTACH_WIDGET,
                                                  XmNtopWidget,shipBulletDurationLabel,
                                                  XmNbottomAttachment,XmATTACH_NONE,
                                                  XmNleftAttachment,XmATTACH_WIDGET,
                                                  XmNleftWidget,verticalSeparator2,
                                                  XmNrightAttachment,XmATTACH_WIDGET,
                                                  XmNrightWidget,verticalSeparator3,
                                                  NULL);
  XtAddCallback(shipBulletDurationValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(shipBulletDurationValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(shipBulletDurationValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(shipBulletDurationValue,XmNlosingFocusCallback,ApplyShipBulletDuration,this);


/********** Create Number of Ship Bullets Label Gadget **********/

  string=XmStringCreateLocalized("Number of Ship Bullets");
  numShipBulletsLabel=XtVaCreateManagedWidget("numShipBulletsLabel",
                                              xmLabelGadgetClass,mainForm,
                                              XmNbackground,background,
                                              XmNforeground,foreground,
                                              XmNmarginTop,7,
                                              XmNlabelString,string,
                                              XmNtopAttachment,XmATTACH_WIDGET,
                                              XmNtopWidget,shipBulletDurationValue,
                                              XmNbottomAttachment,XmATTACH_NONE,
                                              XmNleftAttachment,XmATTACH_WIDGET,
                                              XmNleftWidget,verticalSeparator2,
                                              XmNrightAttachment,XmATTACH_WIDGET,
                                              XmNrightWidget,verticalSeparator3,
                                              NULL);
  XmStringFree(string);

/********** Create Number of Ship Bullets Scale Widget **********/

  numShipBulletsScale=XtVaCreateManagedWidget("numShipBulletsScale",
                                              xmScaleWidgetClass,mainForm,
                                              XmNbackground,background,
                                              XmNforeground,foreground,
                                              XmNminimum,minNumShipBullets,
                                              XmNmaximum,maxNumShipBullets,
                                              XmNorientation,XmHORIZONTAL,
                                              XmNshowValue,TRUE,
					      XmNvalue,ShipBulletGroup::numBullets,
                                              XmNtopAttachment,XmATTACH_WIDGET,
                                              XmNtopWidget,numShipBulletsLabel,
                                              XmNbottomAttachment,XmATTACH_NONE,
                                              XmNleftAttachment,XmATTACH_WIDGET,
                                              XmNleftWidget,verticalSeparator2,
                                              XmNrightAttachment,XmATTACH_WIDGET,
                                              XmNrightWidget,verticalSeparator3,
                                              NULL);
  XtAddCallback(numShipBulletsScale,XmNvalueChangedCallback,ApplyNumShipBullets,this);


/********** Create Horizontal Separator 4 Gadget **********/

  horizontalSeparator5=XtVaCreateManagedWidget("horizontalSeparator5",xmSeparatorGadgetClass,mainForm,
                                               XmNbackground,background,
                                               XmNforeground,foreground,
                                               XmNsensitive,FALSE,
                                               XmNheight,30,
                                               XmNshadowThickness,4,
                                               XmNtopAttachment,XmATTACH_WIDGET,
                                               XmNtopWidget,numShipBulletsScale,
                                               XmNbottomAttachment,XmATTACH_NONE,
                                               XmNleftAttachment,XmATTACH_WIDGET,
                                               XmNleftWidget,verticalSeparator2,
                                               XmNrightAttachment,XmATTACH_WIDGET,
                                               XmNrightWidget,verticalSeparator3,
                                               NULL);


/********** Create ROCK Minimum Velocity Label Gadget **********/

  string=XmStringCreateLocalized("ROCK Minimum Velocity (pixels/sec)");
  ROCKMinVelLabel=XtVaCreateManagedWidget("ROCKMinVelLabel",
                                          xmLabelGadgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNlabelString,string,
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,horizontalSeparator5,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_WIDGET,
                                          XmNleftWidget,verticalSeparator2,
                                          XmNrightAttachment,XmATTACH_WIDGET,
                                          XmNrightWidget,verticalSeparator3,
                                          NULL);
  XmStringFree(string);


/********** Create ROCK Minimum Velocity TextField Widget **********/

  MakeString(1E6*ROCK::minVelocity/PlayingField::uSecondsPerFrame);
  ROCKMinVelValue=XtVaCreateManagedWidget("ROCKMinVelValue",
                                          xmTextFieldWidgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNvalue,str,
                                          XmNcursorPosition,strlen(str),
                                          XmNtopAttachment,XmATTACH_WIDGET,
					  XmNtopWidget,ROCKMinVelLabel,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_WIDGET,
                                          XmNleftWidget,verticalSeparator2,
                                          XmNrightAttachment,XmATTACH_WIDGET,
                                          XmNrightWidget,verticalSeparator3,
                                          NULL);
  XtAddCallback(ROCKMinVelValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(ROCKMinVelValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(ROCKMinVelValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(ROCKMinVelValue,XmNlosingFocusCallback,ApplyROCKMinVel,this);


/********** Create ROCK Maximum Velocity Label Gadget **********/

  string=XmStringCreateLocalized("ROCK Maximum Velocity (pixels/sec)");
  ROCKMaxVelLabel=XtVaCreateManagedWidget("ROCKMaxVelLabel",
                                          xmLabelGadgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNmarginTop,7,
                                          XmNlabelString,string,
                                          XmNtopAttachment,XmATTACH_WIDGET,
                                          XmNtopWidget,ROCKMinVelValue,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_WIDGET,
                                          XmNleftWidget,verticalSeparator2,
                                          XmNrightAttachment,XmATTACH_WIDGET,
                                          XmNrightWidget,verticalSeparator3,
                                          NULL);
  XmStringFree(string);


/********** Create ROCK Maximum Velocity TextField Widget **********/

  MakeString(1E6*ROCK::maxVelocity/PlayingField::uSecondsPerFrame);
  ROCKMaxVelValue=XtVaCreateManagedWidget("ROCKMaxVelValue",
                                          xmTextFieldWidgetClass,mainForm,
                                          XmNbackground,background,
                                          XmNforeground,foreground,
                                          XmNvalue,str,
                                          XmNcursorPosition,strlen(str),
                                          XmNtopAttachment,XmATTACH_WIDGET,
					                                XmNtopWidget,ROCKMaxVelLabel,
                                          XmNbottomAttachment,XmATTACH_NONE,
                                          XmNleftAttachment,XmATTACH_WIDGET,
                                          XmNleftWidget,verticalSeparator2,
                                          XmNrightAttachment,XmATTACH_WIDGET,
                                          XmNrightWidget,verticalSeparator3,
                                          NULL);
  XtAddCallback(ROCKMaxVelValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(ROCKMaxVelValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(ROCKMaxVelValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(ROCKMaxVelValue,XmNlosingFocusCallback,ApplyROCKMaxVel,this);


/********** Create ROCK Maximum Rotational Velocity Label 1 Label Gadget **********/

  string=XmStringCreateLocalized("ROCK Maximum Rotational Velocity");
  ROCKMaxRotationalVelLabel1=XtVaCreateManagedWidget("ROCKMaxRotationalVelLabel1",
                                                     xmLabelGadgetClass,mainForm,
                                                     XmNbackground,background,
                                                     XmNforeground,foreground,
                                                     XmNmarginTop,7,
                                                     XmNlabelString,string,
                                                     XmNtopAttachment,XmATTACH_WIDGET,
                                                     XmNtopWidget,ROCKMaxVelValue,
                                                     XmNbottomAttachment,XmATTACH_NONE,
                                                     XmNleftAttachment,XmATTACH_WIDGET,
                                                     XmNleftWidget,verticalSeparator2,
                                                     XmNrightAttachment,XmATTACH_WIDGET,
                                                     XmNrightWidget,verticalSeparator3,
                                                     NULL);
  XmStringFree(string);


/********** Create ROCK Maximum Rotational Velocity Label 2 Label Gadget *********/

  string=XmStringCreateLocalized("(radians/sec)");
  ROCKMaxRotationalVelLabel2=XtVaCreateManagedWidget("ROCKMaxRotationalVelLabel2",
                                                     xmLabelGadgetClass,mainForm,
                                                     XmNbackground,background,
                                                     XmNforeground,foreground,
                                                     XmNlabelString,string,
                                                     XmNmarginHeight,0,
                                                     XmNmarginBottom,2,
                                                     XmNtopAttachment,XmATTACH_WIDGET,
                                                     XmNtopWidget,ROCKMaxRotationalVelLabel1,
                                                     XmNbottomAttachment,XmATTACH_NONE,
                                                     XmNleftAttachment,XmATTACH_WIDGET,
                                                     XmNleftWidget,verticalSeparator2,
                                                     XmNrightAttachment,XmATTACH_WIDGET,
                                                     XmNrightWidget,verticalSeparator3,
	                                                   NULL);
  XmStringFree(string);


/********** Create ROCK Maximum Rotational Velocity TextField Widget **********/

  MakeString(1E6*ROCK::maxAngularVelocity/PlayingField::uSecondsPerFrame);
  ROCKMaxRotationalVelValue=XtVaCreateManagedWidget("ROCKMaxRotationalVelValue",
                                                    xmTextFieldWidgetClass,mainForm,
                                                    XmNbackground,background,
                                                    XmNforeground,foreground,
                                                    XmNvalue,str,
                                                    XmNcursorPosition,strlen(str),
                                                    XmNtopAttachment,XmATTACH_WIDGET,
					                                          XmNtopWidget,ROCKMaxRotationalVelLabel2,
                                                    XmNbottomAttachment,XmATTACH_NONE,
                                                    XmNleftAttachment,XmATTACH_WIDGET,
                                                    XmNleftWidget,verticalSeparator2,
                                                    XmNrightAttachment,XmATTACH_WIDGET,
                                                    XmNrightWidget,verticalSeparator3,
                                                    NULL);
  XtAddCallback(ROCKMaxRotationalVelValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(ROCKMaxRotationalVelValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(ROCKMaxRotationalVelValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(ROCKMaxRotationalVelValue,XmNlosingFocusCallback,ApplyROCKMaxRotationalVel,this);


/********** Create Initial ROCKs Label Gadget **********/

  string=XmStringCreateLocalized("Initial Number of ROCKs");
  initialROCKsLabel=XtVaCreateManagedWidget("initialROCKsLabel",
                                            xmLabelGadgetClass,mainForm,
                                            XmNbackground,background,
                                            XmNforeground,foreground,
                                            XmNmarginTop,7,
                                            XmNlabelString,string,
                                            XmNtopAttachment,XmATTACH_WIDGET,
                                            XmNtopWidget,ROCKMaxRotationalVelValue,
                                            XmNbottomAttachment,XmATTACH_NONE,
                                            XmNleftAttachment,XmATTACH_WIDGET,
                                            XmNleftWidget,verticalSeparator2,
                                            XmNrightAttachment,XmATTACH_WIDGET,
                                            XmNrightWidget,verticalSeparator3,
                                            NULL);
  XmStringFree(string);

/********** Create Initial ROCKs Scale Widget **********/

  initialROCKsScale=XtVaCreateManagedWidget("initialROCKsScale",
                                            xmScaleWidgetClass,mainForm,
                                            XmNbackground,background,
                                            XmNforeground,foreground,
                                            XmNminimum,minInitialROCKs,
	                                    XmNmaximum,maxInitialROCKs,
                                            XmNorientation,XmHORIZONTAL,
                                            XmNshowValue,TRUE,
					    XmNvalue,RockGroup::initialROCKs,
                                            XmNtopAttachment,XmATTACH_WIDGET,
                                            XmNtopWidget,initialROCKsLabel,
                                            XmNbottomAttachment,XmATTACH_NONE,
                                            XmNleftAttachment,XmATTACH_WIDGET,
                                            XmNleftWidget,verticalSeparator2,
                                            XmNrightAttachment,XmATTACH_WIDGET,
                                            XmNrightWidget,verticalSeparator3,
                                            NULL);
  XtAddCallback(initialROCKsScale,XmNvalueChangedCallback,ApplyInitialROCKs,this);


/********** Create New ROCKs Per Level Label Gadget **********/

  string=XmStringCreateLocalized("Number of New ROCKs Per Level");
  newROCKsPerLevelLabel=XtVaCreateManagedWidget("newROCKsPerLevelLabel",
                                                xmLabelGadgetClass,mainForm,
                                                XmNbackground,background,
                                                XmNforeground,foreground,
                                                XmNmarginTop,7,
                                                XmNlabelString,string,
                                                XmNtopAttachment,XmATTACH_WIDGET,
                                                XmNtopWidget,initialROCKsScale,
                                                XmNbottomAttachment,XmATTACH_NONE,
                                                XmNleftAttachment,XmATTACH_WIDGET,
                                                XmNleftWidget,verticalSeparator2,
                                                XmNrightAttachment,XmATTACH_WIDGET,
                                                XmNrightWidget,verticalSeparator3,
                                                NULL);
  XmStringFree(string);

/********** Create New ROCKs Per Level Scale Widget **********/

  newROCKsPerLevelScale=XtVaCreateManagedWidget("newROCKsPerLevelScale",
                                                xmScaleWidgetClass,mainForm,
                                                XmNbackground,background,
                                                XmNforeground,foreground,
                                                XmNminimum,minNewROCKsPerLevel,
					                                      XmNmaximum,maxNewROCKsPerLevel,
                                                XmNorientation,XmHORIZONTAL,
                                                XmNshowValue,TRUE,
					                                      XmNvalue,RockGroup::ROCKsPerLevel,
                                                XmNtopAttachment,XmATTACH_WIDGET,
                                                XmNtopWidget,newROCKsPerLevelLabel,
                                                XmNbottomAttachment,XmATTACH_NONE,
                                                XmNleftAttachment,XmATTACH_WIDGET,
                                                XmNleftWidget,verticalSeparator2,
                                                XmNrightAttachment,XmATTACH_WIDGET,
                                                XmNrightWidget,verticalSeparator3,
                                                NULL);
  XtAddCallback(newROCKsPerLevelScale,XmNvalueChangedCallback,ApplyNewROCKsPerLevel,this);


/********** Create transparent Rocks Toggle Button Gadget **********/

  string=XmStringCreateLocalized("Transparent Rocks");
  transparentRocks=XtVaCreateManagedWidget("transparentRocks",
                                           xmToggleButtonGadgetClass,mainForm,
                                           XmNbackground,background,
                                           XmNforeground,foreground,
                                           XmNheight,40,
                                           XmNmarginRight,51,
                                           XmNlabelString,string,
                                           XmNindicatorSize,20,
					                                 XmNset,!RockGroup::opaqueRocks,
                                           XmNtopAttachment,XmATTACH_WIDGET,
                                           XmNtopWidget,newROCKsPerLevelScale,
                                           XmNbottomAttachment,XmATTACH_NONE,
                                           XmNleftAttachment,XmATTACH_WIDGET,
                                           XmNleftWidget,verticalSeparator2,
                                           XmNrightAttachment,XmATTACH_WIDGET,
                                           XmNrightWidget,verticalSeparator3,
                                           NULL);
  XmStringFree(string);
  XtAddCallback(transparentRocks,XmNvalueChangedCallback,ApplyTransparentRocks,this);


/********** Create Enemies Exist Toggle Button Gadget **********/

  string=XmStringCreateLocalized("Enemy Ships Exist");
  enemiesExist=XtVaCreateManagedWidget("enemiesExist",
                                       xmToggleButtonGadgetClass,mainForm,
                                       XmNbackground,background,
                                       XmNforeground,foreground,
                                       XmNheight,30,
                                       XmNmarginRight,57,
                                       XmNlabelString,string,
                                       XmNindicatorSize,20,
 				                               XmNset,PlayingField::enemiesExist,
                                       XmNtopAttachment,XmATTACH_FORM,
                                       XmNbottomAttachment,XmATTACH_NONE,
                                       XmNleftAttachment,XmATTACH_WIDGET,
                                       XmNleftWidget,verticalSeparator3,
                                       XmNrightAttachment,XmATTACH_FORM,
                                       NULL);
 XmStringFree(string);
 XtAddCallback(enemiesExist,XmNvalueChangedCallback,ApplyEnemiesExist,this);


/********** Create Horizontal Separator 5 Gadget **********/

  horizontalSeparator6=XtVaCreateManagedWidget("horizontalSeparator6",xmSeparatorGadgetClass,mainForm,
                                               XmNbackground,background,
                                               XmNforeground,foreground,
                                               XmNsensitive,FALSE,
                                               XmNheight,20,
					                                     XmNshadowThickness,4,
                                               XmNtopAttachment,XmATTACH_WIDGET,
                                               XmNtopWidget,enemiesExist,
                                               XmNbottomAttachment,XmATTACH_NONE,
                                               XmNleftAttachment,XmATTACH_WIDGET,
                                               XmNleftWidget,verticalSeparator3,
                                               XmNrightAttachment,XmATTACH_FORM,
                                               NULL);


/********** Create ENEMY Minimum Velocity Label Gadget **********/

  string=XmStringCreateLocalized("ENEMY Minimum Velocity (pixels/sec)");
  ENEMYMinVelLabel=XtVaCreateManagedWidget("ENEMYMinVelLabel",
                                           xmLabelGadgetClass,mainForm,
                                           XmNbackground,background,
                                           XmNforeground,foreground,
                                           XmNmarginTop,5,
                                           XmNlabelString,string,
                                           XmNtopAttachment,XmATTACH_WIDGET,
                                           XmNtopWidget,horizontalSeparator6,
                                           XmNbottomAttachment,XmATTACH_NONE,
                                           XmNleftAttachment,XmATTACH_WIDGET,
                                           XmNleftWidget,verticalSeparator3,
                                           XmNrightAttachment,XmATTACH_FORM,
                                           NULL);
  XmStringFree(string);


/********** Create ENEMY Minimum Velocity TextField Widget **********/

  MakeString(1E6*ENEMY::minVelocity/PlayingField::uSecondsPerFrame);
  ENEMYMinVelValue=XtVaCreateManagedWidget("ENEMYMinVelValue",
                                           xmTextFieldWidgetClass,mainForm,
                                           XmNbackground,background,
                                           XmNforeground,foreground,
                                           XmNvalue,str,
                                           XmNcursorPosition,strlen(str),
                                           XmNtopAttachment,XmATTACH_WIDGET,
                                           XmNtopWidget,ENEMYMinVelLabel,
                                           XmNbottomAttachment,XmATTACH_NONE,
                                           XmNleftAttachment,XmATTACH_WIDGET,
                                           XmNleftWidget,verticalSeparator3,
                                           XmNrightAttachment,XmATTACH_FORM,
                                           NULL);
  XtAddCallback(ENEMYMinVelValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(ENEMYMinVelValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(ENEMYMinVelValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(ENEMYMinVelValue,XmNlosingFocusCallback,ApplyENEMYMinVel,this);


/********** Create ENEMY Maximum Velocity Label Gadget **********/

  string=XmStringCreateLocalized("ENEMY Maximum Velocity (pixels/sec)");
  ENEMYMaxVelLabel=XtVaCreateManagedWidget("ENEMYMaxVelLabel",
                                           xmLabelGadgetClass,mainForm,
                                           XmNbackground,background,
                                           XmNforeground,foreground,
                                           XmNmarginTop,7,
                                           XmNlabelString,string,
                                           XmNtopAttachment,XmATTACH_WIDGET,
                                           XmNtopWidget,ENEMYMinVelValue,
                                           XmNbottomAttachment,XmATTACH_NONE,
                                           XmNleftAttachment,XmATTACH_WIDGET,
                                           XmNleftWidget,verticalSeparator3,
                                           XmNrightAttachment,XmATTACH_FORM,
                                           NULL);
  XmStringFree(string);


/********** Create ENEMY Maximum Velocity TextField Widget **********/

  MakeString(1E6*ENEMY::maxVelocity/PlayingField::uSecondsPerFrame);
  ENEMYMaxVelValue=XtVaCreateManagedWidget("ENEMYMaxVelValue",
                                           xmTextFieldWidgetClass,mainForm,
                                           XmNbackground,background,
                                           XmNforeground,foreground,
                                           XmNvalue,str,
                                           XmNcursorPosition,strlen(str),
                                           XmNtopAttachment,XmATTACH_WIDGET,
                                           XmNtopWidget,ENEMYMaxVelLabel,
                                           XmNbottomAttachment,XmATTACH_NONE,
                                           XmNleftAttachment,XmATTACH_WIDGET,
                                           XmNleftWidget,verticalSeparator3,
                                           XmNrightAttachment,XmATTACH_FORM,
                                           NULL);
  XtAddCallback(ENEMYMaxVelValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(ENEMYMaxVelValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(ENEMYMaxVelValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(ENEMYMaxVelValue,XmNlosingFocusCallback,ApplyENEMYMaxVel,this);


/********** Create enemy Minimum Velocity Label Gadget **********/

  string=XmStringCreateLocalized("enemy Minimum Velocity (pixels/sec)");
  enemyMinVelLabel=XtVaCreateManagedWidget("enemyMinVelLabel",
                                           xmLabelGadgetClass,mainForm,
                                           XmNbackground,background,
                                           XmNforeground,foreground,
                                           XmNmarginTop,7,
                                           XmNlabelString,string,
                                           XmNtopAttachment,XmATTACH_WIDGET,
                                           XmNtopWidget,ENEMYMaxVelValue,
                                           XmNbottomAttachment,XmATTACH_NONE,
                                           XmNleftAttachment,XmATTACH_WIDGET,
                                           XmNleftWidget,verticalSeparator3,
                                           XmNrightAttachment,XmATTACH_FORM,
                                           NULL);
  XmStringFree(string);


/********** Create enemy Minimum Velocity TextField Widget **********/

  MakeString(1E6*enemy::minVelocity/PlayingField::uSecondsPerFrame);
  enemyMinVelValue=XtVaCreateManagedWidget("enemyMinVelValue",
                                           xmTextFieldWidgetClass,mainForm,
                                           XmNbackground,background,
                                           XmNforeground,foreground,
                                           XmNvalue,str,
                                           XmNcursorPosition,strlen(str),
                                           XmNtopAttachment,XmATTACH_WIDGET,
                                           XmNtopWidget,enemyMinVelLabel,
                                           XmNbottomAttachment,XmATTACH_NONE,
                                           XmNleftAttachment,XmATTACH_WIDGET,
                                           XmNleftWidget,verticalSeparator3,
                                           XmNrightAttachment,XmATTACH_FORM,
                                           NULL);
  XtAddCallback(enemyMinVelValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(enemyMinVelValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(enemyMinVelValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(enemyMinVelValue,XmNlosingFocusCallback,ApplyenemyMinVel,this);


/********** Create enemy Maximum Velocity Label Gadget **********/

  string=XmStringCreateLocalized("enemy Maximum Velocity (pixels/sec)");
  enemyMaxVelLabel=XtVaCreateManagedWidget("enemyMaxVelLabel",
                                           xmLabelGadgetClass,mainForm,
                                           XmNbackground,background,
                                           XmNforeground,foreground,
                                           XmNmarginTop,7,
                                           XmNlabelString,string,
                                           XmNtopAttachment,XmATTACH_WIDGET,
                                           XmNtopWidget,enemyMinVelValue,
                                           XmNbottomAttachment,XmATTACH_NONE,
                                           XmNleftAttachment,XmATTACH_WIDGET,
                                           XmNleftWidget,verticalSeparator3,
                                           XmNrightAttachment,XmATTACH_FORM,
                                           NULL);
  XmStringFree(string);


/********** Create enemy Maximum Velocity TextField Widget **********/

  MakeString(1E6*enemy::maxVelocity/PlayingField::uSecondsPerFrame);
  enemyMaxVelValue=XtVaCreateManagedWidget("enemyMaxVelValue",
                                           xmTextFieldWidgetClass,mainForm,
                                           XmNbackground,background,
                                           XmNforeground,foreground,
                                           XmNvalue,str,
                                           XmNcursorPosition,strlen(str),
                                           XmNtopAttachment,XmATTACH_WIDGET,
                                           XmNtopWidget,enemyMaxVelLabel,
                                           XmNbottomAttachment,XmATTACH_NONE,
                                           XmNleftAttachment,XmATTACH_WIDGET,
                                           XmNleftWidget,verticalSeparator3,
                                           XmNrightAttachment,XmATTACH_FORM,
                                           NULL);
  XtAddCallback(enemyMaxVelValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(enemyMaxVelValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(enemyMaxVelValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(enemyMaxVelValue,XmNlosingFocusCallback,ApplyenemyMaxVel,this);


/********** Create Horizontal Separator 6 Gadget **********/

  horizontalSeparator7=XtVaCreateManagedWidget("horizontalSeparator7",xmSeparatorGadgetClass,mainForm,
                                               XmNbackground,background,
                                               XmNforeground,foreground,
                                               XmNsensitive,FALSE,
                                               XmNheight,30,
					                                     XmNshadowThickness,4,
                                               XmNtopAttachment,XmATTACH_WIDGET,
                                               XmNtopWidget,enemyMaxVelValue,
                                               XmNbottomAttachment,XmATTACH_NONE,
                                               XmNleftAttachment,XmATTACH_WIDGET,
                                               XmNleftWidget,verticalSeparator3,
                                               XmNrightAttachment,XmATTACH_FORM,
                                               NULL);


/********** Create Enemy Bullet Velocity Label Gadget **********/

  string=XmStringCreateLocalized("Enemy Bullet Velocity (pixels/sec)");
  enemyBulletVelLabel=XtVaCreateManagedWidget("enemyBulletVelLabel",
                                             xmLabelGadgetClass,mainForm,
                                             XmNbackground,background,
                                             XmNforeground,foreground,
                                             XmNlabelString,string,
                                             XmNtopAttachment,XmATTACH_WIDGET,
                                             XmNtopWidget,horizontalSeparator7,
                                             XmNbottomAttachment,XmATTACH_NONE,
                                             XmNleftAttachment,XmATTACH_WIDGET,
                                             XmNleftWidget,verticalSeparator3,
                                             XmNrightAttachment,XmATTACH_FORM,
                                             NULL);
  XmStringFree(string);


/********** Create Enemy Bullet Velocity TextField Widget **********/

  MakeString(1E6*EnemyBullet::velocity/PlayingField::uSecondsPerFrame);
  enemyBulletVelValue=XtVaCreateManagedWidget("enemyBulletVelValue",
                                              xmTextFieldWidgetClass,mainForm,
                                              XmNbackground,background,
                                              XmNforeground,foreground,
                                              XmNvalue,str,
                                              XmNcursorPosition,strlen(str),
                                              XmNtopAttachment,XmATTACH_WIDGET,
                                              XmNtopWidget,enemyBulletVelLabel,
                                              XmNbottomAttachment,XmATTACH_NONE,
                                              XmNleftAttachment,XmATTACH_WIDGET,
                                              XmNleftWidget,verticalSeparator3,
                                              XmNrightAttachment,XmATTACH_FORM,
                                              NULL);
  XtAddCallback(enemyBulletVelValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(enemyBulletVelValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(enemyBulletVelValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(enemyBulletVelValue,XmNlosingFocusCallback,ApplyEnemyBulletVel,this);


/********** Create Enemy Bullet Duration Label Gadget **********/

  string=XmStringCreateLocalized("Enemy Bullet Duration (seconds)");
  enemyBulletDurationLabel=XtVaCreateManagedWidget("enemyBulletDurationLabel",
                                                   xmLabelGadgetClass,mainForm,
                                                   XmNbackground,background,
                                                   XmNforeground,foreground,
                                                   XmNmarginTop,7,
                                                   XmNlabelString,string,
                                                   XmNtopAttachment,XmATTACH_WIDGET,
                                                   XmNtopWidget,enemyBulletVelValue,
                                                   XmNbottomAttachment,XmATTACH_NONE,
                                                   XmNleftAttachment,XmATTACH_WIDGET,
                                                   XmNleftWidget,verticalSeparator3,
                                                   XmNrightAttachment,XmATTACH_FORM,
                                                   NULL);
  XmStringFree(string);


/********** Create Enemy Bullet Duration TextField Widget **********/

  MakeString(1E-6*EnemyBullet::numFrames*PlayingField::uSecondsPerFrame);
  enemyBulletDurationValue=XtVaCreateManagedWidget("enemyBulletDurationValue",
                                                  xmTextFieldWidgetClass,mainForm,
                                                  XmNbackground,background,
                                                  XmNforeground,foreground,
                                                  XmNvalue,str,
                                                  XmNcursorPosition,strlen(str),
                                                  XmNtopAttachment,XmATTACH_WIDGET,
                                                  XmNtopWidget,enemyBulletDurationLabel,
                                                  XmNbottomAttachment,XmATTACH_NONE,
                                                  XmNleftAttachment,XmATTACH_WIDGET,
                                                  XmNleftWidget,verticalSeparator3,
                                                  XmNrightAttachment,XmATTACH_FORM,
                                                  NULL);
  XtAddCallback(enemyBulletDurationValue,XmNfocusCallback,SetFloatEnterValue,this);
  XtAddCallback(enemyBulletDurationValue,XmNactivateCallback,VerifyFloatTextField,this);
  XtAddCallback(enemyBulletDurationValue,XmNlosingFocusCallback,VerifyFloatTextField,this);
  XtAddCallback(enemyBulletDurationValue,XmNlosingFocusCallback,ApplyEnemyBulletDuration,this);


/********** Create Number of Enemy Bullets Label Gadget **********/

  string=XmStringCreateLocalized("Number of Enemy Bullets");
  numEnemyBulletsLabel=XtVaCreateManagedWidget("numEnemyBulletsLabel",
                                               xmLabelGadgetClass,mainForm,
                                               XmNbackground,background,
                                               XmNforeground,foreground,
                                               XmNmarginTop,7,
                                               XmNlabelString,string,
                                               XmNtopAttachment,XmATTACH_WIDGET,
                                               XmNtopWidget,enemyBulletDurationValue,
                                               XmNbottomAttachment,XmATTACH_NONE,
                                               XmNleftAttachment,XmATTACH_WIDGET,
                                               XmNleftWidget,verticalSeparator3,
                                               XmNrightAttachment,XmATTACH_FORM,
                                               NULL);
  XmStringFree(string);

/********** Create Number of Enemy Bullets Scale Widget **********/

  numEnemyBulletsScale=XtVaCreateManagedWidget("numEnemyBulletsScale",
                                               xmScaleWidgetClass,mainForm,
                                               XmNbackground,background,
                                               XmNforeground,foreground,
                                               XmNminimum,minNumEnemyBullets,
                                               XmNmaximum,maxNumEnemyBullets,
                                               XmNorientation,XmHORIZONTAL,
                                               XmNshowValue,TRUE,
	                                             XmNvalue,EnemyBulletGroup::numBullets,
                                               XmNtopAttachment,XmATTACH_WIDGET,
                                               XmNtopWidget,numEnemyBulletsLabel,
                                               XmNbottomAttachment,XmATTACH_NONE,
                                               XmNleftAttachment,XmATTACH_WIDGET,
                                               XmNleftWidget,verticalSeparator3,
                                               XmNrightAttachment,XmATTACH_FORM,
                                               NULL);
  XtAddCallback(numEnemyBulletsScale,XmNvalueChangedCallback,ApplyNumEnemyBullets,this);

/********** Create File Selection Box Widget **********/

  Arg args[10];
  int n=0;
  XtSetArg(args[n],XmNtitle,"Asteroids Option File Selection"); ++n;
  XtSetArg(args[n],XmNbackground,background); ++n;
  XtSetArg(args[n],XmNforeground,foreground); ++n;
  XtSetArg(args[n],XmNdeleteResponse,XmDO_NOTHING); ++n;
  XtSetArg(args[n],XmNkeyboardFocusPolicy,XmPOINTER); ++n;
  XtSetArg(args[n],XmNwidth,600); ++n;
  XtSetArg(args[n],XmNheight,400); ++n;
  XtSetArg(args[n],XmNresizePolicy,XmRESIZE_GROW); ++n;
  string=XmStringCreateLocalized("XAstOpts/*.XAstOpt");
  XtSetArg(args[n],XmNdirMask,string); ++n;
  fileSelectionDialog=XmCreateFileSelectionDialog(mainForm,"fileSelectionDialog",args,n);
  XmStringFree(string);
  XmAddWMProtocolCallback(XtParent(fileSelectionDialog),playingField.WM_DELETE_WINDOW,
                          CancelFileSelect,(caddr_t)this);
  XtUnmanageChild(XmFileSelectionBoxGetChild(fileSelectionDialog,XmDIALOG_HELP_BUTTON));
  Pixel topShadowColor,
        bottomShadowColor;
  XtVaGetValues(readFromFile,XmNtopShadowColor,&topShadowColor,
                             XmNbottomShadowColor,&bottomShadowColor,
                             NULL);
  XColor troughColor;
  troughColor.pixel=bottomShadowColor;
  XQueryColor(stage.display,DefaultColormap(stage.display,DefaultScreen(stage.display)),
              &troughColor);
  troughColor.red=(troughColor.red+stage.windowBg.red)/2;
  troughColor.green=(troughColor.green+stage.windowBg.green)/2;
  troughColor.blue=(troughColor.blue+stage.windowBg.blue)/2;
  troughColor.flags=DoRed|DoGreen|DoBlue;
  XAllocColor(stage.display,DefaultColormap(stage.display,DefaultScreen(stage.display)),
              &troughColor);
  SetWidgetChildrenColors(fileSelectionDialog,foreground,background,
                                              topShadowColor,bottomShadowColor,
                                              troughColor.pixel);
  XtAddCallback(fileSelectionDialog,XmNokCallback,ReadWriteOptions,this);
  XtAddCallback(fileSelectionDialog,XmNcancelCallback,CancelFileSelect,this);

/********** Create File Exists Question Message Box Widget **********/

  n=0;
  XtSetArg(args[n],XmNtitle,"Asteroids File Exists Question"); ++n;
  XtSetArg(args[n],XmNbackground,background); ++n;
  XtSetArg(args[n],XmNforeground,foreground); ++n;
  XtSetArg(args[n],XmNdeleteResponse,XmDO_NOTHING); ++n;
  XtSetArg(args[n],XmNkeyboardFocusPolicy,XmPOINTER); ++n;
  XtSetArg(args[n],XmNnoResize,TRUE); ++n;
  string=XmStringCreateLocalized("Yes");
  XtSetArg(args[n],XmNokLabelString,string); ++n;
  XmString string2=XmStringCreateLocalized("No");
  XtSetArg(args[n],XmNcancelLabelString,string2); ++n;
  fileExistsQuestionDialog=XmCreateQuestionDialog(fileSelectionDialog,
                                                  "fileExistsQuestionDialog",args,n);
  XmStringFree(string2);
  XmStringFree(string);
  XtVaSetValues(fileExistsQuestionDialog,
                XmNdefaultButton,XmMessageBoxGetChild(fileExistsQuestionDialog,XmDIALOG_CANCEL_BUTTON),
                NULL);
  XmAddWMProtocolCallback(XtParent(fileExistsQuestionDialog),playingField.WM_DELETE_WINDOW,
                          CancelFileExistsQuestion,(caddr_t)this);
  XtUnmanageChild(XmMessageBoxGetChild(fileExistsQuestionDialog,XmDIALOG_HELP_BUTTON));
  SetWidgetChildrenColors(fileExistsQuestionDialog,foreground,background,
                                                   topShadowColor,bottomShadowColor,
                                                   troughColor.pixel);
  XtAddCallback(fileExistsQuestionDialog,XmNokCallback,FileExistsWrite,this);
  XtAddCallback(fileExistsQuestionDialog,XmNcancelCallback,CancelFileExistsQuestion,this);

/********** Create File Error Message Box Widget **********/

  n=0;
  XtSetArg(args[n],XmNtitle,"Asteroids Option File Error"); ++n;
  XtSetArg(args[n],XmNbackground,background); ++n;
  XtSetArg(args[n],XmNforeground,foreground); ++n;
  XtSetArg(args[n],XmNdeleteResponse,XmDO_NOTHING); ++n;
  XtSetArg(args[n],XmNkeyboardFocusPolicy,XmPOINTER); ++n;
  XtSetArg(args[n],XmNnoResize,TRUE); ++n;
  string=XmStringCreateLtoR("An I/O error occurred accessing the specified options file.\n\nGenerally this results from at attempt to read an incorrectly formatted\noptions file or an attempt to write when insufficient disk space is available.","errorFont");
  XtSetArg(args[n],XmNmessageString,string); ++n;
  string2=XmStringCreateLocalized("Continue");
  XtSetArg(args[n],XmNokLabelString,string2); ++n;
  fileErrorDialog=XmCreateErrorDialog(fileSelectionDialog,"fileErrorDialog",args,n);
  XmStringFree(string2);
  XmStringFree(string);
  XmAddWMProtocolCallback(XtParent(fileErrorDialog),playingField.WM_DELETE_WINDOW,
                          CancelFileError,(caddr_t)this);
  XtUnmanageChild(XmMessageBoxGetChild(fileErrorDialog,XmDIALOG_CANCEL_BUTTON));
  XtUnmanageChild(XmMessageBoxGetChild(fileErrorDialog,XmDIALOG_HELP_BUTTON));
  XtVaSetValues(XmMessageBoxGetChild(fileErrorDialog,XmDIALOG_OK_BUTTON),
                  XmNshowAsDefault,0,
                  XmNdefaultButtonShadowThickness,0,
                  NULL);
  SetWidgetChildrenColors(fileErrorDialog,foreground,background,
                                          topShadowColor,bottomShadowColor,
                                          troughColor.pixel);
  XtAddCallback(fileErrorDialog,XmNokCallback,CancelFileError,this);
 }

inline Options::~Options()
 {
  XFreePixmap(stage.display,bulletIconPixmap);
  XFreePixmap(stage.display,enemyIconPixmap);
  XFreePixmap(stage.display,ENEMYIconPixmap);
  XFreePixmap(stage.display,rockIconPixmap);
  XFreePixmap(stage.display,ROckIconPixmap);
  XFreePixmap(stage.display,ROCKIconPixmap);
  XFreePixmap(stage.display,NCC1701DNotSelectedPixmap);
  XFreePixmap(stage.display,NCC1701DSelectedPixmap);
  XFreePixmap(stage.display,NCC1701ANotSelectedPixmap);
  XFreePixmap(stage.display,NCC1701ASelectedPixmap);
  XFreePixmap(stage.display,starDestroyerNotSelectedPixmap);
  XFreePixmap(stage.display,starDestroyerSelectedPixmap);
  XmFontListFree(fontList);
  /*XtDestroyApplicationContext(appContext);*/ //Apparently this operation is implicit in Xorg implementation
 }

void Options::CreateScoringIconPixmaps(const unsigned char* const bitmapData,
                                       const int width, const int height, const int color,
                                       Pixmap& pixmap)
 {GC gc=XCreateGC(stage.display,stage.window,0,NULL);
  XSetGraphicsExposures(stage.display,gc,FALSE);
  Pixmap bitmap=XCreateBitmapFromData(stage.display,stage.window,
                                      (const char * const)bitmapData,width,height);
  int iconWidth=ROCKScoringIcon_width+10,
      iconHeight=ROCKScoringIcon_height+10;
  pixmap=XCreatePixmap(stage.display,stage.window,
                       iconWidth,iconHeight,
                       DefaultDepth(stage.display,DefaultScreen(stage.display)));
  XSetBackground(stage.display,gc,BlackPixel(stage.display,DefaultScreen(stage.display)));
  XSetForeground(stage.display,gc,BlackPixel(stage.display,DefaultScreen(stage.display)));
  XFillRectangle(stage.display,pixmap,gc,0,0,
                 iconWidth,iconHeight);
  XSetForeground(stage.display,gc,color);
  XCopyPlane(stage.display,bitmap,pixmap,gc,0,0,width,height,
             (iconWidth-width)/2,(iconHeight-height)/2,
             1);
  XFreePixmap(stage.display,bitmap);
  XFreeGC(stage.display,gc);
 }

void Options::CreateToggleButtonPixmaps(const unsigned char* const bitmapData,
                                       const int width, const int height, const int color,
                                       Pixmap& selectedPixmap, Pixmap& notSelectedPixmap)
 {GC gc=XCreateGC(stage.display,stage.window,0,NULL);
  XSetGraphicsExposures(stage.display,gc,FALSE);
  Pixmap bitmap=XCreateBitmapFromData(stage.display,stage.window,
                                      (const char * const)bitmapData,width,height);
  int buttonWidth=shipGroup.maxIconWidth+10,
      buttonHeight=shipGroup.maxIconHeight+10;
  selectedPixmap=XCreatePixmap(stage.display,stage.window,
                               buttonWidth,buttonHeight,
                               DefaultDepth(stage.display,DefaultScreen(stage.display)));
  notSelectedPixmap=XCreatePixmap(stage.display,stage.window,
                                  buttonWidth,buttonHeight,
                                  DefaultDepth(stage.display,DefaultScreen(stage.display)));
  XSetBackground(stage.display,gc,BlackPixel(stage.display,DefaultScreen(stage.display)));
  XSetForeground(stage.display,gc,BlackPixel(stage.display,DefaultScreen(stage.display)));
  XFillRectangle(stage.display,selectedPixmap,gc,0,0,
                 buttonWidth,buttonHeight);
  XSetForeground(stage.display,gc,color);
  XCopyPlane(stage.display,bitmap,selectedPixmap,gc,0,0,width,height,
             (buttonWidth-width)/2,(buttonHeight-height)/2,
             1);
  XSetBackground(stage.display,gc,stage.shipYardBg.pixel);
  XSetForeground(stage.display,gc,stage.shipYardBg.pixel);
  XFillRectangle(stage.display,notSelectedPixmap,gc,0,0,
                 buttonWidth,buttonHeight);
  XSetForeground(stage.display,gc,color);
  XCopyPlane(stage.display,bitmap,notSelectedPixmap,gc,0,0,width,height,
             (buttonWidth-width)/2,(buttonHeight-height)/2,
             1);
  XFreePixmap(stage.display,bitmap);
  XFreeGC(stage.display,gc);
 }

inline void Options::SetWidgetChildrenColors(Widget& parent,const Pixel foreground,
                                                            const Pixel background,
                                                            const Pixel topShadowColor,
                                                            const Pixel bottomShadowColor,
                                                            const Pixel troughColor)
 {WidgetList widgetList;
  Cardinal numWidgets=0;
  XtVaGetValues(parent,XmNchildren,&widgetList,
                       XmNnumChildren,&numWidgets,
                       NULL);
  for (int n=0; n<numWidgets; ++n)
   {XtVaSetValues(widgetList[n],
                  XmNbackground,background,
                  XmNforeground,foreground,
                  XmNtopShadowColor,topShadowColor,
                  XmNbottomShadowColor,bottomShadowColor,
                  XmNtroughColor,troughColor,
                  NULL);
    SetWidgetChildrenColors(widgetList[n],foreground,
                                          background,
                                          topShadowColor,
                                          bottomShadowColor,
                                          troughColor);
   }
 }

inline void Options::RealizeWindow()
 {exitFlag=off;
  XtRealizeWidget(shell);
  XWindowAttributes windowAttributes;
  XGetWindowAttributes(XtDisplay(shell),XtWindow(shell),&windowAttributes);
  XtVaSetValues(shell,XmNminWidth,windowAttributes.width,
                      XmNminHeight,windowAttributes.height,
                      XmNmaxWidth,windowAttributes.width,
                      XmNmaxHeight,windowAttributes.height,
                      NULL);
  XEvent event;
  do
   {XtAppNextEvent(appContext,&event);
    if (event.xany.window==stage.window)
     {switch(event.type)
      {case MappingNotify:   XRefreshKeyboardMapping((XMappingEvent*)&event);
                             break;
       case LeaveNotify:     if (stage.autoRepeatState==AutoRepeatModeOn)
                               XAutoRepeatOn(stage.display);
                             break;
       case EnterNotify:     XAutoRepeatOff(stage.display);
                             break;
       case Expose:
       case MapNotify:
       case ConfigureNotify: stage.Refresh();
                             break;
       case ClientMessage:   if (((XClientMessageEvent*)&event)->message_type==
                                 playingField.WM_PROTOCOLS&&
                                 ((XClientMessageEvent*)&event)->data.l[0]==
                                 playingField.WM_DELETE_WINDOW)
                              {XPutBackEvent(stage.display,&event);
                               XtUnrealizeWidget(shell);
                               return;
                              }
                             break;
      }
     }
    else
      XtDispatchEvent(&event);
   }
  while(!exitFlag);
  XtUnrealizeWidget(shell);
 }

void Options::CloseCallback(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->IOState!=noIOInProgress)
    CancelFileSelect(NULL,clientData,NULL);
  ((Options*)clientData)->exitFlag=on;
 }

void Options::ReadFromFile(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->IOState==noIOInProgress)
   {((Options*)clientData)->IOState=readInProgress;
    XtSetSensitive(((Options*)clientData)->writeToFile,FALSE);
    XtManageChild(((Options*)clientData)->fileSelectionDialog);
   }
 }

void Options::WriteToFile(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->IOState==noIOInProgress)
   {((Options*)clientData)->IOState=writeInProgress;
    XtSetSensitive(((Options*)clientData)->readFromFile,FALSE);
    XtManageChild(((Options*)clientData)->fileSelectionDialog);
   }
 }

void Options::ReadWriteOptions(Widget widget,XtPointer clientData,XtPointer callbackData)
 {XmStringContext context;
  XmStringCharSet charset;
  XmStringDirection direction;
  ::Boolean separator;
  XmStringInitContext(&context,((XmSelectionBoxCallbackStruct*)callbackData)->value);
  XmStringGetNextSegment(context,&((Options*)clientData)->filename,&charset,&direction,&separator);
  XmStringFreeContext(context);
  try
   {if (((Options*)clientData)->IOState==readInProgress)
     {((Options*)clientData)->ReadOptions();
      CancelFileSelect(NULL,clientData,NULL);
     }
    else
     {ifstream ifile(((Options*)clientData)->filename,ios::in);
      if (ifile)
       {ifile.close();
        char fnQuestion[47]=" already exists.\n\nDo you wish to overwrite it?";
        char* fnCopy=new char[strlen(((Options*)clientData)->filename)+strlen(fnQuestion)+1];
        XmString string=XmStringCreateLtoR(strcat(strcpy(fnCopy,((Options*)clientData)->filename),fnQuestion),
                                           "errorFont");
        XtVaSetValues(((Options*)clientData)->fileExistsQuestionDialog,
                      XmNmessageString,string,
                      NULL);
        XmStringFree(string);
        delete [] fnCopy;
        XtSetSensitive(XmFileSelectionBoxGetChild(widget,
                                                  XmDIALOG_OK_BUTTON),
                       FALSE);
        XtManageChild(((Options*)clientData)->fileExistsQuestionDialog);
       }
      else
       {ifile.close();
        ((Options*)clientData)->WriteOptions();
        CancelFileSelect(NULL,clientData,NULL);
       }
     }
   }
  catch(...)
   {XtSetSensitive(XmFileSelectionBoxGetChild(widget,
                                              XmDIALOG_OK_BUTTON),
                   FALSE);
    XtManageChild(((Options*)clientData)->fileErrorDialog);
   }
 }

void Options::FileExistsWrite(Widget widget,XtPointer clientData,XtPointer)
 {try
   {((Options*)clientData)->WriteOptions();
    CancelFileSelect(NULL,clientData,NULL);
   }
  catch(...)
   {XtUnmanageChild(widget);
    XtManageChild(((Options*)clientData)->fileErrorDialog);
   }
 }

void excep(const ios& s)
 {if (!s.good())
    throw 42;
 }

inline istream& operator>>(istream& f,void (*const excep)(const ios&))
 {excep(f);
  return f;
 }

inline ostream& operator<<(ostream& f,void (*const excep)(const ios&))
 {excep(f);
  return f;
 }

void Options::ReadOptions()
 {double filedGlobalMaxVel,
         filedUniversalGravitationalConstant,
         filedHyperspaceDestructRate,
         filedShipAccel,
         filedShipMaxVel,
         filedShipRotationalVel,
         filedShipBulletVel,
         filedROCKMinVel,
         filedROCKMaxVel,
         filedROCKMaxRotationalVel,
         filedENEMYMinVel,
         filedENEMYMaxVel,
         filedenemyMinVel,
         filedenemyMaxVel,
         filedEnemyBulletVel;

  int filedUSecondsPerFrame,
      filedShipType,
      filedInitialShips,
      filedExtraShipScore,
      filedShipBulletDuration,
      filedNumShipBullets,
      filedInitialROCKs,
      filedNewROCKsPerLevel,
      filedEnemyBulletDuration,
      filedNumEnemyBullets;

  Boolean filedRelativisticMass,
          filedOpaqueRocks,
          filedAutoFire,
          filedEnemiesExist;

  ifstream ifile(filename,ios::in);
  if (ifile)
    ifile >>filedUSecondsPerFrame               >>excep
          >>filedGlobalMaxVel                   >>excep
          >>filedUniversalGravitationalConstant >>excep
          >>filedRelativisticMass               >>excep
          >>filedShipType                       >>excep
          >>filedShipMaxVel                     >>excep
          >>filedShipAccel                      >>excep
          >>filedShipRotationalVel              >>excep
          >>filedHyperspaceDestructRate         >>excep
          >>filedInitialShips                   >>excep
          >>filedExtraShipScore                 >>excep
          >>filedAutoFire                       >>excep
          >>filedShipBulletVel                  >>excep
          >>filedShipBulletDuration             >>excep
          >>filedNumShipBullets                 >>excep
          >>filedROCKMaxVel                     >>excep
          >>filedROCKMinVel                     >>excep
          >>filedROCKMaxRotationalVel           >>excep
          >>filedInitialROCKs                   >>excep
          >>filedNewROCKsPerLevel               >>excep
          >>filedOpaqueRocks                    >>excep
          >>filedEnemiesExist                   >>excep
          >>filedENEMYMaxVel                    >>excep
          >>filedENEMYMinVel                    >>excep
          >>filedenemyMaxVel                    >>excep
          >>filedenemyMinVel                    >>excep
          >>filedEnemyBulletVel                 >>excep
          >>filedEnemyBulletDuration            >>excep
          >>filedNumEnemyBullets                >>excep;
  else
    throw 42;

  if (PlayingField::uSecondsPerFrame!=filedUSecondsPerFrame)
   {XmScaleSetValue(framesPerSecondScale,1E6/filedUSecondsPerFrame);
    AlterFramesPerSecond(filedUSecondsPerFrame);
   }

  if (PlayingField::maxLinearVelocity!=filedGlobalMaxVel)
    AlterGlobalMaxVel(filedGlobalMaxVel);

  if (PlayingField::universalGravitationalConst!=filedUniversalGravitationalConstant)
    AlterUniversalGravitationalConstant(filedUniversalGravitationalConstant);

  if (PlayingField::relativisticMass!=filedRelativisticMass)
   {XmToggleButtonSetState(relativisticMass,filedRelativisticMass,FALSE);
    AlterRelativisticMass(filedRelativisticMass);
   }

  switch (filedShipType)
   {default: if (ShipGroup::ship!=&shipGroup.starDestroyer
                 ||ShipGroup::thrust!=&shipGroup.starDestroyerThrust)
              {XmToggleButtonSetState(shipNCC1701A,FALSE,FALSE);
               XmToggleButtonSetState(shipNCC1701D,FALSE,FALSE);
               XmToggleButtonSetState(shipStarDestroyer,TRUE,FALSE);
               AlterShipShape(shipGroup.starDestroyer,shipGroup.starDestroyerThrust);
              }
             break;
    case 1:  if (ShipGroup::ship!=&shipGroup.NCC1701A
                 ||ShipGroup::thrust!=&shipGroup.NCC1701AThrust)
              {XmToggleButtonSetState(shipNCC1701D,FALSE,FALSE);
               XmToggleButtonSetState(shipStarDestroyer,FALSE,FALSE);
               XmToggleButtonSetState(shipNCC1701A,TRUE,FALSE);
               AlterShipShape(shipGroup.NCC1701A,shipGroup.NCC1701AThrust);
              }
             break;
    case 2:  if (ShipGroup::ship!=&shipGroup.NCC1701D
                 ||ShipGroup::thrust!=&shipGroup.NCC1701DThrust)
              {XmToggleButtonSetState(shipNCC1701A,FALSE,FALSE);
               XmToggleButtonSetState(shipStarDestroyer,FALSE,FALSE);
               XmToggleButtonSetState(shipNCC1701D,TRUE,FALSE);
               AlterShipShape(shipGroup.NCC1701D,shipGroup.NCC1701DThrust);
              }
             break;
   }

  if (Ship::maxVelocity!=filedShipMaxVel)
    AlterShipMaxVel(filedShipMaxVel);

  if (Ship::acceleration!=filedShipAccel)
    AlterShipAccel(filedShipAccel);

  if (Ship::angularVelocity!=filedShipRotationalVel)
    AlterShipRotationalVel(filedShipRotationalVel);

  if (Hyper::percentDestructRate!=filedHyperspaceDestructRate)
    AlterHyperspaceDestructRate(filedHyperspaceDestructRate);

  if (PlayingField::initialShips!=filedInitialShips)
   {XmScaleSetValue(initialShipsScale,filedInitialShips);
    AlterInitialShips(filedInitialShips);
   }

  if (PlayingField::extraShipScore!=filedExtraShipScore)
    AlterExtraShipScore(filedExtraShipScore);

  if (ShipBulletGroup::autoFire!=filedAutoFire)
   {XmToggleButtonSetState(autoFire,filedAutoFire,FALSE);
    AlterAutoFire(filedAutoFire);
   }

  if (ShipBullet::velocity!=filedShipBulletVel)
    AlterShipBulletVel(filedShipBulletVel);

  if (ShipBullet::numFrames!=filedShipBulletDuration)
    AlterShipBulletDuration(filedShipBulletDuration);

  if (ShipBulletGroup::numBullets!=filedNumShipBullets)
   {XmScaleSetValue(numShipBulletsScale,filedNumShipBullets);
    AlterNumShipBullets(filedNumShipBullets);
   }

  if (ROCK::maxVelocity!=filedROCKMaxVel)
    AlterROCKMaxVel(filedROCKMaxVel);

  if (ROCK::minVelocity!=filedROCKMinVel)
    AlterROCKMinVel(filedROCKMinVel);

  if (ROCK::maxAngularVelocity!=filedROCKMaxRotationalVel)
    AlterROCKMaxRotationalVel(filedROCKMaxRotationalVel);

  if (RockGroup::initialROCKs!=filedInitialROCKs)
   {XmScaleSetValue(initialROCKsScale,filedInitialROCKs);
    AlterInitialROCKs(filedInitialROCKs);
   }

  if (RockGroup::ROCKsPerLevel!=filedNewROCKsPerLevel)
   {XmScaleSetValue(newROCKsPerLevelScale,filedNewROCKsPerLevel);
    AlterNewROCKsPerLevel(filedNewROCKsPerLevel);
   }

  if (RockGroup::opaqueRocks!=filedOpaqueRocks)
   {XmToggleButtonSetState(transparentRocks,!filedOpaqueRocks,FALSE);
    AlterTransparentRocks(!filedOpaqueRocks);
   }

  if (PlayingField::enemiesExist!=filedEnemiesExist)
   {XmToggleButtonSetState(enemiesExist,filedEnemiesExist,FALSE);
    AlterEnemiesExist(filedEnemiesExist);
   }

  if (ENEMY::maxVelocity!=filedENEMYMaxVel)
   {AlterENEMYMaxVel(filedENEMYMaxVel);
    if (PlayingField::enemiesExist)
      if (PlayingField::universalGravitationalConst)
        SetTextWidget(ENEMYMaxVelValue,
                      MakeString(1E6*PlayingField::maxLinearVelocity/PlayingField::uSecondsPerFrame));
      else
        SetTextWidget(ENEMYMaxVelValue,
                      MakeString(1E6*ENEMY::maxVelocity/PlayingField::uSecondsPerFrame));
   }

  if (ENEMY::minVelocity!=filedENEMYMinVel)
   {AlterENEMYMinVel(filedENEMYMinVel);
    if (PlayingField::enemiesExist)
      SetTextWidget(ENEMYMinVelValue,
                    MakeString(1E6*ENEMY::minVelocity/PlayingField::uSecondsPerFrame));
   }

  if (enemy::maxVelocity!=filedenemyMaxVel)
   {AlterenemyMaxVel(filedenemyMaxVel);
    if (PlayingField::enemiesExist)
      if (PlayingField::universalGravitationalConst)
        SetTextWidget(enemyMaxVelValue,
                      MakeString(1E6*PlayingField::maxLinearVelocity/PlayingField::uSecondsPerFrame));
      else
        SetTextWidget(enemyMaxVelValue,
                      MakeString(1E6*enemy::maxVelocity/PlayingField::uSecondsPerFrame));
   }

  if (enemy::minVelocity!=filedenemyMinVel)
   {AlterenemyMinVel(filedenemyMinVel);
    if (PlayingField::enemiesExist)
      SetTextWidget(enemyMinVelValue,
                    MakeString(1E6*enemy::minVelocity/PlayingField::uSecondsPerFrame));
   }

  if (EnemyBullet::velocity!=filedEnemyBulletVel)
   {AlterEnemyBulletVel(filedEnemyBulletVel);
    if (PlayingField::enemiesExist)
      SetTextWidget(enemyBulletVelValue,MakeString(1E6*EnemyBullet::velocity
                                                   /PlayingField::uSecondsPerFrame));
   }

  if (EnemyBullet::numFrames!=filedEnemyBulletDuration)
   {AlterEnemyBulletDuration(filedEnemyBulletDuration);
    if (PlayingField::enemiesExist)
      SetTextWidget(enemyBulletDurationValue,MakeString(1E-6*EnemyBullet::numFrames
                                                        *PlayingField::uSecondsPerFrame));
   }

  if (EnemyBulletGroup::numBullets!=filedNumEnemyBullets)
   {XmScaleSetValue(numEnemyBulletsScale,filedNumEnemyBullets);
    AlterNumEnemyBullets(filedNumEnemyBullets);
   }
  SetWidgetFields();
 }

void Options::WriteOptions()
 {ofstream ofile(filename,ios::out);
  if (ofile)
   {ofile.setf(ios::scientific,ios::floatfield);
    ofile.precision(16);
    ofile <<PlayingField::uSecondsPerFrame            <<excep<<'\n'<<excep
          <<PlayingField::maxLinearVelocity           <<excep<<'\n'<<excep
          <<PlayingField::universalGravitationalConst <<excep<<'\n'<<excep
          <<PlayingField::relativisticMass            <<excep<<'\n'<<excep
          <<(ShipGroup::ship==&shipGroup.NCC1701D
               ? 2
	             : ShipGroup::ship==&shipGroup.NCC1701A
                   ? 1
	                 : 0)                               <<excep<<'\n'<<excep
          <<Ship::maxVelocity                         <<excep<<'\n'<<excep
          <<Ship::acceleration                        <<excep<<'\n'<<excep
          <<Ship::angularVelocity                     <<excep<<'\n'<<excep
          <<Hyper::percentDestructRate                <<excep<<'\n'<<excep
          <<PlayingField::initialShips                <<excep<<'\n'<<excep
          <<PlayingField::extraShipScore              <<excep<<'\n'<<excep
          <<ShipBulletGroup::autoFire                 <<excep<<'\n'<<excep
          <<ShipBullet::velocity                      <<excep<<'\n'<<excep
          <<ShipBullet::numFrames                     <<excep<<'\n'<<excep
          <<ShipBulletGroup::numBullets               <<excep<<'\n'<<excep
          <<ROCK::maxVelocity                         <<excep<<'\n'<<excep
          <<ROCK::minVelocity                         <<excep<<'\n'<<excep
          <<ROCK::maxAngularVelocity                  <<excep<<'\n'<<excep
          <<RockGroup::initialROCKs                   <<excep<<'\n'<<excep
          <<RockGroup::ROCKsPerLevel                  <<excep<<'\n'<<excep
          <<RockGroup::opaqueRocks                    <<excep<<'\n'<<excep
          <<PlayingField::enemiesExist                <<excep<<'\n'<<excep
          <<ENEMY::maxVelocity                        <<excep<<'\n'<<excep
          <<ENEMY::minVelocity                        <<excep<<'\n'<<excep
          <<enemy::maxVelocity                        <<excep<<'\n'<<excep
          <<enemy::minVelocity                        <<excep<<'\n'<<excep
          <<EnemyBullet::velocity                     <<excep<<'\n'<<excep
          <<EnemyBullet::numFrames                    <<excep<<'\n'<<excep
          <<EnemyBulletGroup::numBullets              <<excep<<'\n'<<excep;
   }
  else
    throw 42;
 }

void Options::CancelFileSelect(Widget,XtPointer clientData,XtPointer)
 {CancelFileExistsQuestion(NULL,clientData,NULL);
  CancelFileError(NULL,clientData,NULL);
  XtUnmanageChild(((Options*)clientData)->fileSelectionDialog);
  if (((Options*)clientData)->IOState==readInProgress)
    XtSetSensitive(((Options*)clientData)->writeToFile,TRUE);
  else
    XtSetSensitive(((Options*)clientData)->readFromFile,TRUE);
  ((Options*)clientData)->IOState=noIOInProgress;
 }

void Options::CancelFileExistsQuestion(Widget,XtPointer clientData,XtPointer)
 {XtUnmanageChild(((Options*)clientData)->fileExistsQuestionDialog);
  XtSetSensitive(XmFileSelectionBoxGetChild(((Options*)clientData)->fileSelectionDialog,
                                            XmDIALOG_OK_BUTTON),
                 TRUE);
 }

void Options::CancelFileError(Widget,XtPointer clientData,XtPointer)
 {XtUnmanageChild(((Options*)clientData)->fileErrorDialog);
  XtSetSensitive(XmFileSelectionBoxGetChild(((Options*)clientData)->fileSelectionDialog,
                                            XmDIALOG_OK_BUTTON),
                 TRUE);
 }

void Options::ResetDefaults(Widget,XtPointer clientData,XtPointer)
 {if (PlayingField::uSecondsPerFrame!=defaultUSecondsPerFrame)
   {XmScaleSetValue(((Options*)clientData)->framesPerSecondScale,1E6/defaultUSecondsPerFrame);
    ((Options*)clientData)->AlterFramesPerSecond(defaultUSecondsPerFrame);
   }

  if (PlayingField::maxLinearVelocity!=defaultGlobalMaxVel)
    ((Options*)clientData)->AlterGlobalMaxVel(defaultGlobalMaxVel);

  if (PlayingField::universalGravitationalConst!=defaultUniversalGravitationalConstant)
    ((Options*)clientData)->AlterUniversalGravitationalConstant(defaultUniversalGravitationalConstant);

  if (PlayingField::relativisticMass!=defaultRelativisticMass)
   {XmToggleButtonSetState(((Options*)clientData)->relativisticMass,defaultRelativisticMass,FALSE);
    ((Options*)clientData)->AlterRelativisticMass(defaultRelativisticMass);
   }

  if (ShipGroup::ship!=&shipGroup.starDestroyer||ShipGroup::thrust!=&shipGroup.starDestroyerThrust)
   {XmToggleButtonSetState(((Options*)clientData)->shipNCC1701A,FALSE,FALSE);
    XmToggleButtonSetState(((Options*)clientData)->shipNCC1701D,FALSE,FALSE);
    XmToggleButtonSetState(((Options*)clientData)->shipStarDestroyer,TRUE,FALSE);
    ((Options*)clientData)->AlterShipShape(shipGroup.starDestroyer,shipGroup.starDestroyerThrust);
   }

  if (Ship::maxVelocity!=defaultShipMaxVel)
    ((Options*)clientData)->AlterShipMaxVel(defaultShipMaxVel);

  if (Ship::acceleration!=defaultShipAccel)
    ((Options*)clientData)->AlterShipAccel(defaultShipAccel);

  if (Ship::angularVelocity!=defaultShipRotationalVel)
    ((Options*)clientData)->AlterShipRotationalVel(defaultShipRotationalVel);

  if (Hyper::percentDestructRate!=defaultHyperspaceDestructRate)
    ((Options*)clientData)->AlterHyperspaceDestructRate(defaultHyperspaceDestructRate);

  if (PlayingField::initialShips!=defaultInitialShips)
   {XmScaleSetValue(((Options*)clientData)->initialShipsScale,defaultInitialShips);
    ((Options*)clientData)->AlterInitialShips(defaultInitialShips);
   }

  if (PlayingField::extraShipScore!=defaultExtraShipScore)
    ((Options*)clientData)->AlterExtraShipScore(defaultExtraShipScore);

  if (ShipBulletGroup::autoFire!=defaultAutoFire)
   {XmToggleButtonSetState(((Options*)clientData)->autoFire,defaultAutoFire,FALSE);
    ((Options*)clientData)->AlterAutoFire(defaultAutoFire);
   }

  if (ShipBullet::velocity!=defaultShipBulletVel)
    ((Options*)clientData)->AlterShipBulletVel(defaultShipBulletVel);

  if (ShipBullet::numFrames!=defaultShipBulletDuration)
    ((Options*)clientData)->AlterShipBulletDuration(defaultShipBulletDuration);

  if (ShipBulletGroup::numBullets!=defaultNumShipBullets)
   {XmScaleSetValue(((Options*)clientData)->numShipBulletsScale,defaultNumShipBullets);
    ((Options*)clientData)->AlterNumShipBullets(defaultNumShipBullets);
   }

  if (ROCK::maxVelocity!=defaultROCKMaxVel)
    ((Options*)clientData)->AlterROCKMaxVel(defaultROCKMaxVel);

  if (ROCK::minVelocity!=defaultROCKMinVel)
    ((Options*)clientData)->AlterROCKMinVel(defaultROCKMinVel);

  if (ROCK::maxAngularVelocity!=defaultROCKMaxRotationalVel)
    ((Options*)clientData)->AlterROCKMaxRotationalVel(defaultROCKMaxRotationalVel);

  if (RockGroup::initialROCKs!=defaultInitialROCKs)
   {XmScaleSetValue(((Options*)clientData)->initialROCKsScale,defaultInitialROCKs);
    ((Options*)clientData)->AlterInitialROCKs(defaultInitialROCKs);
   }

  if (RockGroup::ROCKsPerLevel!=defaultNewROCKsPerLevel)
   {XmScaleSetValue(((Options*)clientData)->newROCKsPerLevelScale,defaultNewROCKsPerLevel);
    ((Options*)clientData)->AlterNewROCKsPerLevel(defaultNewROCKsPerLevel);
   }

  if (RockGroup::opaqueRocks!=defaultOpaqueRocks)
   {XmToggleButtonSetState(((Options*)clientData)->transparentRocks,!defaultOpaqueRocks,FALSE);
    ((Options*)clientData)->AlterTransparentRocks(!defaultOpaqueRocks);
   }

  if (PlayingField::enemiesExist!=defaultEnemiesExist)
   {XmToggleButtonSetState(((Options*)clientData)->enemiesExist,defaultEnemiesExist,FALSE);
    ((Options*)clientData)->AlterEnemiesExist(defaultEnemiesExist);
   }

  if (ENEMY::maxVelocity!=defaultENEMYMaxVel)
    ((Options*)clientData)->AlterENEMYMaxVel(defaultENEMYMaxVel);

  if (ENEMY::minVelocity!=defaultENEMYMinVel)
    ((Options*)clientData)->AlterENEMYMinVel(defaultENEMYMinVel);

  if (enemy::maxVelocity!=defaultenemyMaxVel)
    ((Options*)clientData)->AlterenemyMaxVel(defaultenemyMaxVel);

  if (enemy::minVelocity!=defaultenemyMinVel)
    ((Options*)clientData)->AlterenemyMinVel(defaultenemyMinVel);

  if (EnemyBullet::velocity!=defaultEnemyBulletVel)
    ((Options*)clientData)->AlterEnemyBulletVel(defaultEnemyBulletVel);

  if (EnemyBullet::numFrames!=defaultEnemyBulletDuration)
    ((Options*)clientData)->AlterEnemyBulletDuration(defaultEnemyBulletDuration);

  if (EnemyBulletGroup::numBullets!=defaultNumEnemyBullets)
   {XmScaleSetValue(((Options*)clientData)->numEnemyBulletsScale,defaultNumEnemyBullets);
    ((Options*)clientData)->AlterNumEnemyBullets(defaultNumEnemyBullets);
   }

  ((Options*)clientData)->SetWidgetFields();
 }

void Options::ApplyFramesPerSecond(Widget widget,XtPointer clientData,XtPointer)
 {int newFramesPerSec;
  XmScaleGetValue(widget,&newFramesPerSec);
  double uSecondsPerFrame=1E6/newFramesPerSec;
  if (uSecondsPerFrame!=PlayingField::uSecondsPerFrame)
   {((Options*)clientData)->AlterFramesPerSecond(uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::SetIntEnterValue(Widget widget,XtPointer clientData,XtPointer)
 {char* intStr=XmTextFieldGetString(widget);
  ((Options*)clientData)->intEnterValue=atoi(intStr);
  XtFree(intStr);
  ((Options*)clientData)->valueChanged=off;
 }

void Options::SetFloatEnterValue(Widget widget,XtPointer clientData,XtPointer)
 {char* doubleStr=XmTextFieldGetString(widget);
  ((Options*)clientData)->floatEnterValue=atof(doubleStr);
  XtFree(doubleStr);
  ((Options*)clientData)->valueChanged=off;
 }

void Options::VerifyIntTextField(Widget widget,XtPointer clientData,XtPointer)
 {char* intStr=XmTextFieldGetString(widget);
  ((Options*)clientData)->intExitValue=atoi(intStr);
  XtFree(intStr);
  char intStr2[11];
  ostrstream strout(intStr2,sizeof(intStr2)/sizeof(char));
  strout<<((Options*)clientData)->intExitValue<<'\0';
  XmTextFieldSetString(widget,intStr2);
  XmTextFieldSetInsertionPosition(widget,strlen(intStr2));
  ((Options*)clientData)->valueChanged=((Options*)clientData)->intEnterValue!=
                                       ((Options*)clientData)->intExitValue;
 }

void Options::VerifyFloatTextField(Widget widget,XtPointer clientData,XtPointer)
 {char* doubleStr=XmTextFieldGetString(widget);
  ((Options*)clientData)->floatExitValue=atof(doubleStr);
  XtFree(doubleStr);
  char doubleStr2[25];
  ostrstream strout(doubleStr2,sizeof(doubleStr2)/sizeof(char));
  strout<<setprecision(17)<<((Options*)clientData)->floatExitValue<<'\0';
  XmTextFieldSetString(widget,doubleStr2);
  XmTextFieldSetInsertionPosition(widget,strlen(doubleStr2));
  ((Options*)clientData)->valueChanged=((Options*)clientData)->floatEnterValue!=
                                       ((Options*)clientData)->floatExitValue;
 }

void Options::ApplyGlobalMaxVel(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterGlobalMaxVel(fabs(((Options*)clientData)->floatExitValue)
                                              *1E-6*PlayingField::uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyUniversalGravitationalConstant(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterUniversalGravitationalConstant(((Options*)clientData)->floatExitValue);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyRelativisticMass(Widget widget,XtPointer clientData,XtPointer)
 {((Options*)clientData)->AlterRelativisticMass(XmToggleButtonGetState(widget));
  ((Options*)clientData)->SetWidgetFields();
 }

void Options::ApplyStarDestroyerShipShape(Widget,XtPointer clientData,XtPointer)
 {if (ShipGroup::ship!=&shipGroup.starDestroyer||ShipGroup::thrust!=&shipGroup.starDestroyerThrust)
   {((Options*)clientData)->AlterShipShape(shipGroup.starDestroyer,shipGroup.starDestroyerThrust);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyNCC1701AShipShape(Widget,XtPointer clientData,XtPointer)
 {if (ShipGroup::ship!=&shipGroup.NCC1701A||ShipGroup::thrust!=&shipGroup.NCC1701AThrust)
   {((Options*)clientData)->AlterShipShape(shipGroup.NCC1701A,shipGroup.NCC1701AThrust);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyNCC1701DShipShape(Widget,XtPointer clientData,XtPointer)
 {if (ShipGroup::ship!=&shipGroup.NCC1701D||ShipGroup::thrust!=&shipGroup.NCC1701DThrust)
   {((Options*)clientData)->AlterShipShape(shipGroup.NCC1701D,shipGroup.NCC1701DThrust);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyShipAccel(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterShipAccel(fabs(((Options*)clientData)->floatExitValue)*1E-12
                                           *PlayingField::uSecondsPerFrame*PlayingField::uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyShipMaxVel(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterShipMaxVel(fabs(((Options*)clientData)->floatExitValue)*1E-6
                                            *PlayingField::uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyShipRotationalVel(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterShipRotationalVel(fabs(((Options*)clientData)->floatExitValue)
                                                   *1E-6*PlayingField::uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyHyperspaceDestructRate(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterHyperspaceDestructRate(fabs(((Options*)clientData)->floatExitValue));
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyInitialShips(Widget widget,XtPointer clientData,XtPointer)
 {int newInitialShips;
  XmScaleGetValue(widget,&newInitialShips);
  if (newInitialShips!=PlayingField::initialShips)
   {((Options*)clientData)->AlterInitialShips(newInitialShips);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyExtraShipScore(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterExtraShipScore(abs(((Options*)clientData)->intExitValue));
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyAutoFire(Widget widget,XtPointer clientData,XtPointer)
 {((Options*)clientData)->AlterAutoFire(XmToggleButtonGetState(widget));
  ((Options*)clientData)->SetWidgetFields();
 }

void Options::ApplyShipBulletVel(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterShipBulletVel(fabs(((Options*)clientData)->floatExitValue)*1E-6
                                               *PlayingField::uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyShipBulletDuration(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterShipBulletDuration(fabs(((Options*)clientData)->floatExitValue)*1E6
                                                    /PlayingField::uSecondsPerFrame+.5);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyNumShipBullets(Widget widget,XtPointer clientData,XtPointer)
 {int newNumShipBullets;
  XmScaleGetValue(widget,&newNumShipBullets);
  if (newNumShipBullets!=ShipBulletGroup::numBullets)
   {((Options*)clientData)->AlterNumShipBullets(newNumShipBullets);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyROCKMinVel(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterROCKMinVel(fabs(((Options*)clientData)->floatExitValue)
                                            *1E-6*PlayingField::uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyROCKMaxVel(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterROCKMaxVel(fabs(((Options*)clientData)->floatExitValue)
                                            *1E-6*PlayingField::uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyROCKMaxRotationalVel(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterROCKMaxRotationalVel(fabs(((Options*)clientData)->floatExitValue)
                                                      *1E-6*PlayingField::uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyInitialROCKs(Widget widget,XtPointer clientData,XtPointer)
 {int newInitialROCKs;
  XmScaleGetValue(widget,&newInitialROCKs);
  if (newInitialROCKs!=RockGroup::initialROCKs)
   {((Options*)clientData)->AlterInitialROCKs(newInitialROCKs);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyNewROCKsPerLevel(Widget widget,XtPointer clientData,XtPointer)
 {int newROCKsPerLevel;
  XmScaleGetValue(widget,&newROCKsPerLevel);
  if (newROCKsPerLevel!=RockGroup::ROCKsPerLevel)
   {((Options*)clientData)->AlterNewROCKsPerLevel(newROCKsPerLevel);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyTransparentRocks(Widget widget,XtPointer clientData,XtPointer)
 {((Options*)clientData)->AlterTransparentRocks(XmToggleButtonGetState(widget));
  ((Options*)clientData)->SetWidgetFields();
 }

void Options::ApplyEnemiesExist(Widget widget,XtPointer clientData,XtPointer)
 {((Options*)clientData)->AlterEnemiesExist(XmToggleButtonGetState(widget));
  ((Options*)clientData)->SetWidgetFields();
 }

void Options::ApplyENEMYMinVel(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterENEMYMinVel(fabs(((Options*)clientData)->floatExitValue)
                                             *1E-6*PlayingField::uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyENEMYMaxVel(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterENEMYMaxVel(fabs(((Options*)clientData)->floatExitValue)
                                             *1E-6*PlayingField::uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyenemyMinVel(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterenemyMinVel(fabs(((Options*)clientData)->floatExitValue)
                                             *1E-6*PlayingField::uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyenemyMaxVel(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterenemyMaxVel(fabs(((Options*)clientData)->floatExitValue)
                                             *1E-6*PlayingField::uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyEnemyBulletVel(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterEnemyBulletVel(fabs(((Options*)clientData)->floatExitValue)*1E-6
                                                *PlayingField::uSecondsPerFrame);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyEnemyBulletDuration(Widget,XtPointer clientData,XtPointer)
 {if (((Options*)clientData)->valueChanged)
   {((Options*)clientData)->AlterEnemyBulletDuration(fabs(((Options*)clientData)->floatExitValue)*1E6
                                                     /PlayingField::uSecondsPerFrame+.5);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::ApplyNumEnemyBullets(Widget widget,XtPointer clientData,XtPointer)
 {int newNumEnemyBullets;
  XmScaleGetValue(widget,&newNumEnemyBullets);
  if (newNumEnemyBullets!=EnemyBulletGroup::numBullets)
   {((Options*)clientData)->AlterNumEnemyBullets(newNumEnemyBullets);
    ((Options*)clientData)->SetWidgetFields();
   }
 }

void Options::AlterFramesPerSecond(const double newUSecondsPerFrame)
 {double velocityAdjustRatio=newUSecondsPerFrame/PlayingField::uSecondsPerFrame,
         maxLinearVelocity=PlayingField::maxLinearVelocity*velocityAdjustRatio;

  playingField.AlterUSecondsPerFrame(newUSecondsPerFrame);

  AlterGlobalMaxVel(.5*PlayingField::playArea.Height());
  if (!PlayingField::universalGravitationalConst)
    shipGroup.ResetVelocityLimits(.5*PlayingField::playArea.Height());

  shipGroup.AdjustFramesPerSec(velocityAdjustRatio);
  Ship::maxVelocity*=velocityAdjustRatio;
  Ship::acceleration*=velocityAdjustRatio*velocityAdjustRatio;
  Ship::angularVelocity*=velocityAdjustRatio;

  shipBulletGroup.AdjustFramesPerSec(velocityAdjustRatio);
  ShipBullet::velocity*=velocityAdjustRatio;
  ShipBullet::numFrames/=velocityAdjustRatio;

  enemyGroup.AdjustFramesPerSec(velocityAdjustRatio);
  ENEMY::minVelocity*=velocityAdjustRatio;
  ENEMY::maxVelocity*=velocityAdjustRatio;
  enemy::minVelocity*=velocityAdjustRatio;
  enemy::maxVelocity*=velocityAdjustRatio;

  enemyBulletGroup.AdjustFramesPerSec(velocityAdjustRatio);
  EnemyBullet::velocity*=velocityAdjustRatio;
  EnemyBullet::numFrames/=velocityAdjustRatio;

  rockGroup.AdjustFramesPerSec(velocityAdjustRatio);
  ROCK::minVelocity*=velocityAdjustRatio;
  ROCK::maxVelocity*=velocityAdjustRatio;
  ROCK::maxAngularVelocity*=velocityAdjustRatio;

  AlterGlobalMaxVel(maxLinearVelocity);
  if (!PlayingField::universalGravitationalConst)
    shipGroup.ResetVelocityLimits(Ship::maxVelocity);
 }

void Options::AlterGlobalMaxVel(const double newMV)
 {double newMaxVel=newMV;
  if (newMaxVel>.5*PlayingField::playArea.Height())
    newMaxVel=.5*PlayingField::playArea.Height();
  PlayingField::maxLinearVelocity=newMaxVel;

  if (Ship::maxVelocity>newMaxVel||
      PlayingField::universalGravitationalConst)
   {shipGroup.ResetVelocityLimits(newMaxVel);
    Ship::maxVelocity=newMaxVel;
    if (Ship::acceleration>newMaxVel)
      Ship::acceleration=newMaxVel;
    if (Ship::angularVelocity>shipGroup.ship->ObjectRotator().MaxAngularVelocity())
      Ship::angularVelocity=shipGroup.ship->ObjectRotator().MaxAngularVelocity();
   }

  shipBulletGroup.ResetVelocityLimits(newMaxVel);
  if (ShipBullet::velocity>newMaxVel)
    ShipBullet::velocity=newMaxVel;

  enemyGroup.ResetVelocityLimits(newMaxVel);
  if (ENEMY::minVelocity>newMaxVel)
    ENEMY::minVelocity=newMaxVel;
  if (ENEMY::maxVelocity>newMaxVel)
    ENEMY::maxVelocity=newMaxVel;
  if (enemy::minVelocity>newMaxVel)
    enemy::minVelocity=newMaxVel;
  if (enemy::maxVelocity>newMaxVel)
    enemy::maxVelocity=newMaxVel;

  enemyBulletGroup.ResetVelocityLimits(newMaxVel);
  if (EnemyBullet::velocity>newMaxVel)
    EnemyBullet::velocity=newMaxVel;

  rockGroup.ResetVelocityLimits(newMaxVel);
  if (ROCK::minVelocity>newMaxVel)
    ROCK::minVelocity=newMaxVel;
  if (ROCK::maxVelocity>newMaxVel)
    ROCK::maxVelocity=newMaxVel;
  if (ROCK::maxAngularVelocity>newMaxVel/(4*ROCK::scale))
    ROCK::maxAngularVelocity=newMaxVel/(4*ROCK::scale);
 }

void Options::AlterUniversalGravitationalConstant(const double newUniversalGravitationalConst)
 {PlayingField::universalGravitationalConst=newUniversalGravitationalConst;
  if (PlayingField::universalGravitationalConst<minUniversalGravitationalConstant)
    PlayingField::universalGravitationalConst=minUniversalGravitationalConstant;
  if (PlayingField::universalGravitationalConst>maxUniversalGravitationalConstant)
    PlayingField::universalGravitationalConst=maxUniversalGravitationalConstant;
  if (PlayingField::universalGravitationalConst)
   shipGroup.ResetVelocityLimits(PlayingField::maxLinearVelocity);
  else
   {shipGroup.ResetVelocityLimits(Ship::maxVelocity);
    shipBulletGroup.ResetVelocity(ShipBullet::velocity);
    rockGroup.ResetMaxVelocity(ROCK::maxVelocity);
    enemyGroup.ResetENEMYMaxVelocity(ENEMY::maxVelocity);
    enemyGroup.ResetenemyMaxVelocity(enemy::maxVelocity);
    enemyBulletGroup.ResetVelocity(EnemyBullet::velocity);
   }
  XtSetSensitive(shipMaxVelLabel,!PlayingField::universalGravitationalConst);
  XtSetSensitive(shipMaxVelValue,!PlayingField::universalGravitationalConst);
  XtSetSensitive(shipBulletVelLabel,!PlayingField::universalGravitationalConst);
  XtSetSensitive(shipBulletVelValue,!PlayingField::universalGravitationalConst);
  XtSetSensitive(ROCKMaxVelLabel,!PlayingField::universalGravitationalConst);
  XtSetSensitive(ROCKMaxVelValue,!PlayingField::universalGravitationalConst);
  XtSetSensitive(ENEMYMaxVelLabel,PlayingField::enemiesExist&&!PlayingField::universalGravitationalConst);
  XtSetSensitive(ENEMYMaxVelValue,PlayingField::enemiesExist&&!PlayingField::universalGravitationalConst);
  XtSetSensitive(enemyMaxVelLabel,PlayingField::enemiesExist&&!PlayingField::universalGravitationalConst);
  XtSetSensitive(enemyMaxVelValue,PlayingField::enemiesExist&&!PlayingField::universalGravitationalConst);
  XtSetSensitive(enemyBulletVelLabel,PlayingField::enemiesExist&&!PlayingField::universalGravitationalConst);
  XtSetSensitive(enemyBulletVelValue,PlayingField::enemiesExist&&!PlayingField::universalGravitationalConst);
 }

void Options::AlterRelativisticMass(const Options::Boolean relMass)
 {PlayingField::relativisticMass=relMass;
 }

void Options::AlterShipShape(Ship& newip,Thrust& newrust)
 {newip.CurrentBox().MoveBox(shipGroup.ship->CurrentBox().Center()
                              -newip.CurrentBox().Center());
  newip.ObjectLiner().Velocity()=shipGroup.ship->ObjectLiner().Velocity();
  newip.ObjectLiner().Acceleration()=shipGroup.ship->ObjectLiner().Acceleration();
  newip.ObjectRotator().Angle()=shipGroup.ship->ObjectRotator().Angle();
  newip.ObjectRotator().AngularVelocity()=0;
  if (Ship::angularVelocity>newip.ObjectRotator().MaxAngularVelocity())
    Ship::angularVelocity=newip.ObjectRotator().MaxAngularVelocity();
  newip.dead=shipGroup.ship->dead;
  playingField.RemoveShip();
  ShipGroup::ship=&newip;
  ShipGroup::thrust=&newrust;
  playingField.AddShip();
  shipYard.AlterIcon(newip.icon,
	             newip.iconWidth,newip.iconHeight,
                     newip.iconColor);
  stage.DrawShipYard();
 }

void Options::AlterShipAccel(const double newAccel)
 {shipGroup.ResetAccelerationLimits(Ship::acceleration=newAccel>PlayingField::maxLinearVelocity
                                                       ? PlayingField::maxLinearVelocity
                                                       : newAccel);
 }

void Options::AlterShipMaxVel(const double newMaxVel)
 {shipGroup.ResetVelocityLimits(Ship::maxVelocity=newMaxVel>PlayingField::maxLinearVelocity
                                                  ? PlayingField::maxLinearVelocity
                                                  : newMaxVel);
 }

void Options::AlterShipRotationalVel(const double newRotVel)
 {shipGroup.ResetAngularVelocity(Ship::angularVelocity=
                                 newRotVel>shipGroup.ship->ObjectRotator().MaxAngularVelocity()
                                         ? shipGroup.ship->ObjectRotator().MaxAngularVelocity()
                                         : newRotVel);
 }

void Options::AlterHyperspaceDestructRate(const double newDestructRate)
 {Hyper::percentDestructRate=newDestructRate>maxHyperspaceDestructRate ? maxHyperspaceDestructRate
                                                                       : newDestructRate;
  Hyper::destructRate=RAND_MAX_16*Hyper::percentDestructRate/100;
 }

void Options::AlterInitialShips(const int newInitialShips)
 {int i=(2*newInitialShips*shipYard.NumShips()+PlayingField::initialShips)/(2*PlayingField::initialShips);
  shipYard.ClearYard();
  for (;i--;)
    shipYard.AddShip();
  PlayingField::initialShips=newInitialShips;
  stage.DrawShipYard();
 }

void Options::AlterExtraShipScore(const int newExtraShipScore)
 {playingField.AlterExtraShipScore(PlayingField::extraShipScore=newExtraShipScore<minExtraShipScore
                                                                ? minExtraShipScore
                                                                : newExtraShipScore>maxExtraShipScore
                                                                  ? maxExtraShipScore
                                                                  : newExtraShipScore);
 }

void Options::AlterAutoFire(const Options::Boolean automaticFire)
 {ShipBulletGroup::autoFire=automaticFire;
 }

void Options::AlterShipBulletVel(const double newVel)
 {ShipBullet::velocity=newVel>PlayingField::maxLinearVelocity
                       ? PlayingField::maxLinearVelocity
                       : newVel<minShipBulletVel
                         ? minShipBulletVel
                         : newVel;
  shipBulletGroup.ResetVelocity(ShipBullet::velocity);
 }

void Options::AlterShipBulletDuration(const int newDuration)
 {shipBulletGroup.ResetBulletDuration(ShipBullet::numFrames=newDuration>maxShipBulletDuration
                                                            ? maxShipBulletDuration
                                                            : newDuration<minShipBulletDuration
                                                              ? minShipBulletDuration
                                                              : newDuration);
 }

void Options::AlterNumShipBullets(const int newNumBullets)
 {ShipBulletGroup::numBullets=newNumBullets;
 }

void Options::AlterROCKMinVel(const double newMinVel)
 {rockGroup.ResetMinVelocity(ROCK::minVelocity=newMinVel>ROCK::maxVelocity ? ROCK::maxVelocity
                                                                           : newMinVel);
 }

void Options::AlterROCKMaxVel(const double newMaxVel)
 {rockGroup.ResetMaxVelocity(ROCK::maxVelocity=newMaxVel>PlayingField::maxLinearVelocity
                                               ? PlayingField::maxLinearVelocity
                                               : newMaxVel);
  if (ROCK::minVelocity>ROCK::maxVelocity)
    rockGroup.ResetMinVelocity(ROCK::minVelocity=ROCK::maxVelocity);
 }

void Options::AlterROCKMaxRotationalVel(const double newRotationalVel)
 {rockGroup.ResetMaxAngularVelocity(ROCK::maxAngularVelocity=
                                    newRotationalVel>PlayingField::maxLinearVelocity/(4*ROCK::scale)
                                    ? PlayingField::maxLinearVelocity/(4*ROCK::scale)
                                    : newRotationalVel);
 }

void Options::AlterInitialROCKs(const int newInitialROCKs)
 {RockGroup::initialROCKs=newInitialROCKs;
 }

void Options::AlterNewROCKsPerLevel(const int newROCKsPerLevel)
 {RockGroup::ROCKsPerLevel=newROCKsPerLevel;
 }

void Options::AlterTransparentRocks(const Options::Boolean transparentRocks)
 {RockGroup::opaqueRocks=!transparentRocks;
 }

void Options::AlterEnemiesExist(const Options::Boolean newEnemiesExist)
 {PlayingField::enemiesExist=newEnemiesExist;
  XtSetSensitive(ENEMYMinVelLabel,newEnemiesExist);
  XtSetSensitive(ENEMYMinVelValue,newEnemiesExist);
  XtSetSensitive(ENEMYMaxVelLabel,newEnemiesExist&&!PlayingField::universalGravitationalConst);
  XtSetSensitive(ENEMYMaxVelValue,newEnemiesExist&&!PlayingField::universalGravitationalConst);
  XtSetSensitive(enemyMinVelLabel,newEnemiesExist);
  XtSetSensitive(enemyMinVelValue,newEnemiesExist);
  XtSetSensitive(enemyMaxVelLabel,newEnemiesExist&&!PlayingField::universalGravitationalConst);
  XtSetSensitive(enemyMaxVelValue,newEnemiesExist&&!PlayingField::universalGravitationalConst);
  XtSetSensitive(enemyBulletVelLabel,newEnemiesExist&&!PlayingField::universalGravitationalConst);
  XtSetSensitive(enemyBulletVelValue,newEnemiesExist&&!PlayingField::universalGravitationalConst);
  XtSetSensitive(enemyBulletDurationLabel,newEnemiesExist);
  XtSetSensitive(enemyBulletDurationValue,newEnemiesExist);
  XtSetSensitive(numEnemyBulletsLabel,newEnemiesExist);
  XtSetSensitive(numEnemyBulletsScale,newEnemiesExist);
 }

void Options::AlterENEMYMinVel(const double newMinVel)
 {enemyGroup.ResetENEMYMinVelocity(ENEMY::minVelocity=newMinVel>ENEMY::maxVelocity
                                                      ? ENEMY::maxVelocity
                                                      : newMinVel);
 }

void Options::AlterENEMYMaxVel(const double newMaxVel)
 {enemyGroup.ResetENEMYMaxVelocity(ENEMY::maxVelocity=newMaxVel>PlayingField::maxLinearVelocity
                                                      ? PlayingField::maxLinearVelocity
                                                      : newMaxVel);
  if (ENEMY::minVelocity>ENEMY::maxVelocity)
    enemyGroup.ResetENEMYMinVelocity(ENEMY::minVelocity=ENEMY::maxVelocity);
 }

void Options::AlterenemyMinVel(const double newMinVel)
 {enemyGroup.ResetenemyMinVelocity(enemy::minVelocity=newMinVel>enemy::maxVelocity
                                                      ? enemy::maxVelocity
                                                      : newMinVel);
 }

void Options::AlterenemyMaxVel(const double newMaxVel)
 {enemyGroup.ResetenemyMaxVelocity(enemy::maxVelocity=newMaxVel>PlayingField::maxLinearVelocity
                                                      ? PlayingField::maxLinearVelocity
                                                      : newMaxVel);
  if (enemy::minVelocity>enemy::maxVelocity)
    enemyGroup.ResetenemyMinVelocity(enemy::minVelocity=enemy::maxVelocity);
 }

void Options::AlterEnemyBulletVel(const double newVel)
 {EnemyBullet::velocity=newVel>PlayingField::maxLinearVelocity
                        ? PlayingField::maxLinearVelocity
                        : newVel<minEnemyBulletVel
                          ? minEnemyBulletVel
                          : newVel;
  enemyBulletGroup.ResetVelocity(EnemyBullet::velocity);
 }

void Options::AlterEnemyBulletDuration(const int newDuration)
 {enemyBulletGroup.ResetBulletDuration(EnemyBullet::numFrames=newDuration>maxEnemyBulletDuration
                                                              ? maxEnemyBulletDuration
                                                              : newDuration<minEnemyBulletDuration
                                                                ? minEnemyBulletDuration
                                                                : newDuration);
 }

void Options::AlterNumEnemyBullets(const int newNumBullets)
 {EnemyBulletGroup::numBullets=newNumBullets;
 }

void Options::SetWidgetFields()
 {int localWeightTotal=weightTotal;
  SetTextWidget(globalMaxVelValue,
                MakeString(1E6*PlayingField::maxLinearVelocity/PlayingField::uSecondsPerFrame));
  double scoreFactor=weightGlobalMaxVel
                     *(PlayingField::maxLinearVelocity-minGlobalMaxVel)
                     /(defaultGlobalMaxVel-minGlobalMaxVel);

  SetTextWidget(universalGravitationalConstantValue,
                MakeString(PlayingField::universalGravitationalConst));
  int localWeightUniversalGravitationalConstant;
  if (PlayingField::universalGravitationalConst&&PlayingField::relativisticMass)
   {localWeightUniversalGravitationalConstant=weightUniversalGravitationalConstant*3.4;
    localWeightTotal+=localWeightUniversalGravitationalConstant-weightUniversalGravitationalConstant;
   }
  else
    localWeightUniversalGravitationalConstant=weightUniversalGravitationalConstant;
  scoreFactor+=localWeightUniversalGravitationalConstant
               *(PlayingField::universalGravitationalConst-minUniversalGravitationalConstant)
               /(defaultUniversalGravitationalConstant-minUniversalGravitationalConstant);

  scoreFactor+=weightShipShape
               *(shipGroup.ship->ObjectRotator().Radius()-shipGroup.starDestroyer.ObjectRotator().Radius()+1);

  SetTextWidget(shipAccelValue,
                MakeString(1E12*Ship::acceleration
                           /(double(PlayingField::uSecondsPerFrame)*PlayingField::uSecondsPerFrame)));
  scoreFactor+=weightShipAccel
               *(maxShipAccel-Ship::acceleration)
               /(maxShipAccel-defaultShipAccel);

  if (PlayingField::universalGravitationalConst)
    SetTextWidget(shipMaxVelValue,MakeString(1E6*PlayingField::maxLinearVelocity
                                             /PlayingField::uSecondsPerFrame));
  else
    SetTextWidget(shipMaxVelValue,MakeString(1E6*Ship::maxVelocity/PlayingField::uSecondsPerFrame));
  scoreFactor+=weightShipMaxVel
              *(maxShipMaxVel-Ship::maxVelocity)
              /(maxShipMaxVel-defaultShipMaxVel);

  SetTextWidget(shipRotationalVelValue,
                MakeString(1E6*Ship::angularVelocity/PlayingField::uSecondsPerFrame));
  scoreFactor+=weightShipRotationalVel
               *(maxShipRotationalVel-Ship::angularVelocity)
               /(maxShipRotationalVel-defaultShipRotationalVel);

  SetTextWidget(hyperspaceDestructRateValue,MakeString(Hyper::percentDestructRate));
  scoreFactor+=weightHyperspaceDestructRate
               *(Hyper::percentDestructRate-minHyperspaceDestructRate)
               /(defaultHyperspaceDestructRate-minHyperspaceDestructRate);

  scoreFactor+=weightInitialShips
               *double(maxInitialShips-PlayingField::initialShips)
               /(maxInitialShips-defaultInitialShips);

  SetTextWidget(extraShipScoreValue,MakeString(PlayingField::extraShipScore));
  scoreFactor+=weightExtraShipScore
               *double(PlayingField::extraShipScore-minExtraShipScore)
               /(defaultExtraShipScore-minExtraShipScore);

  scoreFactor+=weightAutoFire*!ShipBulletGroup::autoFire;

  SetTextWidget(shipBulletVelValue,MakeString(1E6*ShipBullet::velocity
                                              /PlayingField::uSecondsPerFrame));
  scoreFactor+=weightShipBulletVel
               *(maxShipBulletVel-ShipBullet::velocity)
               /(maxShipBulletVel-defaultShipBulletVel);

  SetTextWidget(shipBulletDurationValue,MakeString(1E-6*ShipBullet::numFrames*PlayingField::uSecondsPerFrame));
  scoreFactor+=weightShipBulletDuration
               *double(maxShipBulletDuration-ShipBullet::numFrames)
               /(maxShipBulletDuration-defaultShipBulletDuration);

  scoreFactor+=weightNumShipBullets
               *double(maxNumShipBullets-ShipBulletGroup::numBullets)
               /(maxNumShipBullets-defaultNumShipBullets);

  SetTextWidget(ROCKMinVelValue,
                MakeString(1E6*ROCK::minVelocity/PlayingField::uSecondsPerFrame));
  scoreFactor+=weightROCKMinVel
               *(ROCK::minVelocity-minROCKMinVel)
               /(defaultROCKMinVel-minROCKMinVel);

  if (PlayingField::universalGravitationalConst)
    SetTextWidget(ROCKMaxVelValue,
		              MakeString(1E6*PlayingField::maxLinearVelocity/PlayingField::uSecondsPerFrame));
  else
    SetTextWidget(ROCKMaxVelValue,
                  MakeString(1E6*ROCK::maxVelocity/PlayingField::uSecondsPerFrame));
  scoreFactor+=weightROCKMaxVel
               *(ROCK::maxVelocity-minROCKMaxVel)
               /(defaultROCKMaxVel-minROCKMaxVel);

  SetTextWidget(ROCKMaxRotationalVelValue,
                MakeString(1E6*ROCK::maxAngularVelocity/PlayingField::uSecondsPerFrame));
  scoreFactor+=weightROCKMaxRotationalVel
               *(ROCK::maxAngularVelocity-minROCKMaxRotationalVel)
               /(defaultROCKMaxRotationalVel-minROCKMaxRotationalVel);

  scoreFactor+=weightInitialROCKs
               *double(RockGroup::initialROCKs-minInitialROCKs)
               /(defaultInitialROCKs-minInitialROCKs);

  scoreFactor+=weightNewROCKsPerLevel
               *double(RockGroup::ROCKsPerLevel-minNewROCKsPerLevel)
               /(defaultNewROCKsPerLevel-minNewROCKsPerLevel);

  scoreFactor+=weightOpaqueRocks*RockGroup::opaqueRocks;

  if (PlayingField::enemiesExist)
   {scoreFactor+=weightEnemiesExist;

    SetTextWidget(ENEMYMinVelValue,
                  MakeString(1E6*ENEMY::minVelocity/PlayingField::uSecondsPerFrame));
    scoreFactor+=weightENEMYMinVel
                 *(ENEMY::minVelocity-minENEMYMinVel)
                 /(defaultENEMYMinVel-minENEMYMinVel);

    if (PlayingField::universalGravitationalConst)
      SetTextWidget(ENEMYMaxVelValue,
                    MakeString(1E6*PlayingField::maxLinearVelocity/PlayingField::uSecondsPerFrame));
    else
      SetTextWidget(ENEMYMaxVelValue,
                    MakeString(1E6*ENEMY::maxVelocity/PlayingField::uSecondsPerFrame));
    scoreFactor+=weightENEMYMaxVel
                 *(ENEMY::maxVelocity-minENEMYMaxVel)
                 /(defaultENEMYMaxVel-minENEMYMaxVel);

    SetTextWidget(enemyMinVelValue,
                  MakeString(1E6*enemy::minVelocity/PlayingField::uSecondsPerFrame));
    scoreFactor+=weightenemyMinVel
                 *(enemy::minVelocity-minenemyMinVel)
                 /(defaultenemyMinVel-minenemyMinVel);

    if (PlayingField::universalGravitationalConst)
      SetTextWidget(enemyMaxVelValue,
                    MakeString(1E6*PlayingField::maxLinearVelocity/PlayingField::uSecondsPerFrame));
    else
      SetTextWidget(enemyMaxVelValue,
                    MakeString(1E6*enemy::maxVelocity/PlayingField::uSecondsPerFrame));
    scoreFactor+=weightenemyMaxVel
                 *(enemy::maxVelocity-minenemyMaxVel)
                 /(defaultenemyMaxVel-minenemyMaxVel);

    SetTextWidget(enemyBulletVelValue,MakeString(1E6*EnemyBullet::velocity
                                                 /PlayingField::uSecondsPerFrame));
    scoreFactor+=weightEnemyBulletVel
                 *(EnemyBullet::velocity-minEnemyBulletVel)
                 /(defaultEnemyBulletVel-minEnemyBulletVel);

    SetTextWidget(enemyBulletDurationValue,MakeString(1E-6*EnemyBullet::numFrames
                                                      *PlayingField::uSecondsPerFrame));
    scoreFactor+=weightEnemyBulletDuration
                 *double(EnemyBullet::numFrames-minEnemyBulletDuration)
                 /(defaultEnemyBulletDuration-minEnemyBulletDuration);

    scoreFactor+=weightNumEnemyBullets
                 *double(EnemyBulletGroup::numBullets-minNumEnemyBullets)
                 /(defaultNumEnemyBullets-minNumEnemyBullets);
   }

  scoreFactor/=localWeightTotal;

  if (!(ROCK::score=defaultROCKScore*scoreFactor+.5)) ROCK::score=1;
  if (!(ROck::score=defaultROckScore*scoreFactor+.5)) ROck::score=1;
  if (!(rock::score=defaultrockScore*scoreFactor+.5)) rock::score=1;
  rockGroup.ResetScore(scoreFactor/lastScoreFactor);
  SetScore(ROCKScoreLabel,ROCK::score);
  SetScore(ROckScoreLabel,ROck::score);
  SetScore(rockScoreLabel,rock::score);

  if (!(ENEMY::score=defaultENEMYScore*scoreFactor+.5)) ENEMY::score=1;
  if (!(enemy::score=defaultenemyScore*scoreFactor+.5)) enemy::score=1;
  enemyGroup.ResetScore(scoreFactor/lastScoreFactor);
  SetScore(ENEMYScoreLabel,ENEMY::score);
  SetScore(enemyScoreLabel,enemy::score);

  if (!(EnemyBullet::score=defaultEnemyBulletScore*scoreFactor+.5)) EnemyBullet::score=1;
  SetScore(bulletScoreLabel,EnemyBullet::score);

  lastScoreFactor=scoreFactor;
 }

inline void Options::SetTextWidget(Widget widget,const char* const str)
 {XmTextFieldSetString(widget,(char*)str);
  XmTextFieldSetInsertionPosition(widget,strlen(str));
 }

inline void Options::SetScore(Widget widget, const int score)
 {XmString string;
  string=XmStringCreateLocalized((char*)MakeString(score));
  XtVaSetValues(widget,XmNlabelString,string,NULL);
  XtVaSetValues(widget,XmNwidth,ROCKScoringIcon_width+32,NULL);
  XmStringFree(string);
 }

inline const char* const Options::MakeString(const int n)
 {ostrstream strout(str,sizeof(str)/sizeof(char));
  strout<<n<<'\0';
  return str;
 }

inline const char* const Options::MakeString(const double d)
 {ostrstream strout(str,sizeof(str)/sizeof(char));
  strout<<setprecision(17)<<d<<'\0';
  return str;
 }

#endif
