#ifndef _STAGE_H
#define _STAGE_H

#include<stdlib.h>
#include<iostream>
#include<strstream>
#include<iomanip>
#include<string.h>
#include<signal.h>
#include<time.h>
#include<X11/Xlib.h>
#include"options/button.H"
#include"score.H"
#include"shipYard.H"
#include"../bitmaps/starDestroyerIcon.xbm"

// This code was originally written where 0<=RAND_MAX<=2^16-1. To prevent overflow issues, a 16 bit random function is used since rand()
//   returns a full 32 bit value. This provides a single convenient place to change the game random number generator to anything desired.
#define RAND_MAX_16 ((RAND_MAX)>>16)
class gary_rand{
  public:
    static inline int rand_16()
     {
      return rand()>>16;
     }
};

using namespace std;

extern Button button;
extern Score score;
extern ShipYard shipYard;

class PlayingField;
class Stage
 {friend class Button;
  friend class ShipYard;
  friend class PlayingField;

  public:

    Stage();
    ~Stage();

    inline Stage& DrawScore();
    inline Stage& DrawShipYard();
    inline Stage& DrawPlayingField();
    inline Stage& Refresh();

    Display* display;
    Window window;

    Pixmap icon;

    int shipYardWidth,
        shipYardHeight,
        autoRepeatState;

    int buttonX,
        buttonY;

    XFontStruct* buttonInfo,
               * errorInfo;

    static XColor windowBg,
                  shipYardBg,
                  buttonFg,
                  buttonBg;

  private:

    XFontStruct* titleInfo,
               * hiScoreInfo,
               * scoreInfo;

    GC titleGC,
       hiScoreGC,
       scoreGC,
       defaultGC;

    int windowWidth,
        windowHeight,
        titleX,
        titleY,
        hiScoreUserX,
        hiScoreUserY,
        hiScoreX,
        hiScoreY,
        scoreX,
        scoreY,
        shipYardX,
        shipYardY,
        playAreaX,
        playAreaY;

    struct sigaction action;

    static void terminate(int i);
 };

extern Stage stage;

#include"playingField.H"
#include"../objects/ships/shipGroup.H"
extern PlayingField playingField;

XColor Stage::windowBg={0,
                        46260,//180
                        46260,//180
                        46260,//180
                        DoRed|DoGreen|DoBlue},
       Stage::shipYardBg={0,
                          28527,//111
                          28527,//111
                          28527,//111
                          DoRed|DoGreen|DoBlue},
       Stage::buttonFg={0,
                        0,//0
                        0,//0
                        0,//0
                        DoRed|DoGreen|DoBlue},
       Stage::buttonBg={0,
                        46260,//180
                        46260,//180
                        46260,//180
                        DoRed|DoGreen|DoBlue};

inline Stage::Stage()
 {cout<<"XAsteroids is a Unix version of the original Atari Asteroids video game.  It features color, arbitrarily shaped drawables with interior decor, hidden line elimination, accurate collision detection, and dynamically selectable options including gravitation.  Game initialization requires a minute or two so please be patient.  If XAsteroids abnormally terminates the keyboard may no longer auto-repeat.  Auto-repeat can be reactivated by executing AutoRepeatOn."<<endl<<endl;
  if (!(display=XOpenDisplay(NULL)))
   {cout<<"Could not open display."<<endl;
    exit(1);
   }
  titleInfo=XLoadQueryFont(display,"white_shadow-48");
  buttonInfo=XLoadQueryFont(display,"-schumacher-clean-bold-r-normal--10-100-75-75-c-60-iso8859-1");
  hiScoreInfo=XLoadQueryFont(display,"-ibm-ergonomic-bold-r-normal--20-140-100-100-c-120-iso8859-9");
  scoreInfo=XLoadQueryFont(display,"-urw-courier-bold-r-normal--40-300-100-100-m-240-iso8859-9");
  errorInfo=XLoadQueryFont(display,"-adobe-helvetica-bold-r-normal--14-100-100-100-p-82-iso8859-1");
  if (!titleInfo||!buttonInfo||!hiScoreInfo||!scoreInfo||!errorInfo)
   {cout<<"Could not find font white_shadow-48, -schumacher-clean-bold-r-normal--10-100-75-75-c-60-iso8859-1, -ibm-ergonomic-bold-r-normal--20-140-100-100-c-120-iso8859-9, -urw-courier-bold-r-normal--40-300-100-100-m-240-iso8859-9, and/or -adobe-helvetica-bold-r-normal--14-100-100-100-p-82-iso8859-1.  Please run XAstSetup and retry XAsteroids."<<endl;
    exit(1);
   }
  int titleWidth=XTextWidth(titleInfo,"Asteroids",strlen("Asteroids"))
                 +2*titleInfo->max_bounds.width,
      hiScoreWidth=10*hiScoreInfo->max_bounds.width,
      scoreWidth=10*scoreInfo->max_bounds.width,
      headerWidth=titleWidth+2*(hiScoreWidth>scoreWidth
                                ? hiScoreWidth
                                : scoreWidth),
      headerHeight;
  windowWidth=(headerWidth>PlayingField::playArea.Width()
               ? headerWidth
               : PlayingField::playArea.Width())+30;
  headerHeight=2*(hiScoreInfo->max_bounds.ascent+hiScoreInfo->max_bounds.descent)+4;
  if (titleInfo->max_bounds.ascent+titleInfo->max_bounds.descent>headerHeight)
    headerHeight=titleInfo->max_bounds.ascent+titleInfo->max_bounds.descent;
  if (scoreInfo->max_bounds.ascent+scoreInfo->max_bounds.descent>headerHeight)
    headerHeight=scoreInfo->max_bounds.ascent+scoreInfo->max_bounds.descent;
  windowHeight=headerHeight+2*shipGroup.maxIconHeight+PlayingField::playArea.Height()+60;
  int temp=(windowWidth-titleWidth)/2;
  titleX=temp+titleInfo->max_bounds.width-titleInfo->max_bounds.lbearing;
  titleY=titleInfo->max_bounds.ascent+15;
  buttonX=buttonY=2;
  hiScoreUserX=(temp-hiScoreWidth)/2-hiScoreInfo->max_bounds.lbearing;
  hiScoreUserY=hiScoreInfo->max_bounds.ascent+15;
  hiScoreX=hiScoreUserX;
  hiScoreY=hiScoreUserY+hiScoreInfo->max_bounds.ascent+hiScoreInfo->max_bounds.descent+4;
  scoreX=titleX+titleWidth
         -titleInfo->max_bounds.width+titleInfo->max_bounds.lbearing
         +(temp-scoreWidth)/2-scoreInfo->max_bounds.lbearing;
  scoreY=scoreInfo->max_bounds.ascent+15;
  shipYardX=15;
  shipYardY=headerHeight+25;
  shipYardWidth=windowWidth-30;
  shipYardHeight=2*shipGroup.maxIconHeight+10;
  playAreaX=(windowWidth-PlayingField::playArea.Width())/2;
  playAreaY=headerHeight+shipYardHeight+35;
  int screen=DefaultScreen(display),
      background=XAllocColor(display,DefaultColormap(display,screen),&windowBg)
                ? windowBg.pixel
                : WhitePixel(display,screen);
  window=XCreateSimpleWindow(display,DefaultRootWindow(display),
                             (DisplayWidth(display,screen)-windowWidth)/2,
                             (DisplayHeight(display,screen)-windowHeight)/2,
                             windowWidth,windowHeight,
                             5, WhitePixel(display,screen),
                             background);
  icon=XCreateBitmapFromData(display,window,
                              (const char * const)starDestroyerIcon_bits,
                             starDestroyerIcon_width,starDestroyerIcon_height);
  titleGC=XCreateGC(display,window,NULL,0);
  XSetGraphicsExposures(display,titleGC,FALSE);
  XSetFont(display,titleGC,titleInfo->fid);
  XSetForeground(display,titleGC,BlackPixel(display,screen));
  XSetBackground(display,titleGC,background);
  hiScoreGC=XCreateGC(display,window,NULL,0);
  XSetGraphicsExposures(display,hiScoreGC,FALSE);
  XSetFont(display,hiScoreGC,hiScoreInfo->fid);
  XSetForeground(display,hiScoreGC,BlackPixel(display,screen));
  XSetBackground(display,hiScoreGC,background);
  scoreGC=XCreateGC(display,window,NULL,0);
  XSetGraphicsExposures(display,scoreGC,FALSE);
  XSetFont(display,scoreGC,scoreInfo->fid);
  XSetForeground(display,scoreGC,BlackPixel(display,screen));
  XSetBackground(display,scoreGC,background);
  defaultGC=XCreateGC(display,window,NULL,0);
  XSetGraphicsExposures(display,defaultGC,FALSE);
  XKeyboardState KBState;
  XGetKeyboardControl(display,&KBState);
  autoRepeatState=KBState.global_auto_repeat;
  action.sa_handler=Stage::terminate;
  action.sa_mask=0;
  action.sa_flags=0;
  sigaction(SIGINT,&action,NULL);
  sigaction(SIGQUIT,&action,NULL);
  sigaction(SIGABRT,&action,NULL);
  sigaction(SIGTERM,&action,NULL);
  time_t t=time(NULL);
  srand(t);
 }

inline Stage::~Stage()
 {if (autoRepeatState==AutoRepeatModeOn)
    XAutoRepeatOn(display);
  XFreeGC(display,defaultGC);
  XFreeGC(display,scoreGC);
  XFreeGC(display,hiScoreGC);
  XFreeGC(display,titleGC);
  XFreePixmap(display,icon);
  XDestroyWindow(display,window);
  XFreeFont(display,scoreInfo);
  XFreeFont(display,hiScoreInfo);
  XFreeFont(display,buttonInfo);
  XFreeFont(display,titleInfo);
  XCloseDisplay(display);
 }

inline Stage& Stage::DrawScore()
 {char str[10];
  ostrstream strout(str,sizeof(str)/sizeof(char));
  if (score.CurrentScore()>=score.TopTenScore(0))
   {strout<<setw(sizeof(str)/sizeof(char))<<score.CurrentName();
    XDrawImageString(display,window,hiScoreGC,
                     hiScoreUserX,hiScoreUserY,str,sizeof(str)/sizeof(char));
    strout.seekp(0);
    strout<<setw(sizeof(str)/sizeof(char))<<score.CurrentScore();
    XDrawImageString(display,window,hiScoreGC,
                     hiScoreX,hiScoreY,str,sizeof(str)/sizeof(char));
   }
  else
    strout<<setw(sizeof(str)/sizeof(char))<<score.CurrentScore();
  XDrawImageString(display,window,scoreGC,
                   scoreX,scoreY,str,sizeof(str)/sizeof(char));
  return *this;
 }

inline Stage& Stage::DrawShipYard()
 {XCopyArea(display,
            shipYard.GetYard(),
            window,
            defaultGC,
            0,0,
            shipYardWidth,shipYardHeight,
            shipYardX,shipYardY);
  return *this;
 }

inline Stage& Stage::DrawPlayingField()
 {XCopyArea(display,
            playingField.pixmap,
            window,
            defaultGC,
	    PlayingField::playArea.NorthWestCorner().x,PlayingField::playArea.NorthWestCorner().y,
	    PlayingField::playArea.Width(),PlayingField::playArea.Height(),
            playAreaX,playAreaY);
  return *this;
 }

inline Stage& Stage::Refresh()
 {XDrawString(display,window,titleGC,
              titleX,titleY,"Asteroids",strlen("Asteroids"));
  char str[10];
  ostrstream strout(str,sizeof(str)/sizeof(char));
  strout<<setw(sizeof(str)/sizeof(char))<<score.TopTenName(0);
  XDrawImageString(display,window,hiScoreGC,
                   hiScoreUserX,hiScoreUserY,str,sizeof(str)/sizeof(char));
  strout.seekp(0);
  strout<<setw(sizeof(str)/sizeof(char))<<score.TopTenScore(0);
  XDrawImageString(display,window,hiScoreGC,
                   hiScoreX,hiScoreY,str,sizeof(str)/sizeof(char));
  button.DrawButton();
  DrawScore().DrawShipYard().DrawPlayingField();
  return *this;
 }

void Stage::terminate(int i)
 {if (stage.autoRepeatState==AutoRepeatModeOn)
    XAutoRepeatOn(stage.display);
  struct sigaction action;
  action.sa_handler=SIG_DFL;
  action.sa_mask=0;
  action.sa_flags=0;
  sigaction(i,&action,NULL);
  raise(i);
 }

#endif
