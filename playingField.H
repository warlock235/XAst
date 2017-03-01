#include"stage.H"
#include"options.H"
#include"shipBulletGroup.H"
#include"shipGroup.H"
#include"enemyBulletGroup.H"
#include"enemyGroup.H"
#include"rockGroup.H"

#ifndef _PLAYINGFIELD_H
#define _PLAYINGFIELD_H

#include<stdlib.h>
#include<iostream>
#include<strstream>
#include<iomanip>
#include<string.h>
#include<sys/time.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include"vector2d.H"
#include"box.H"
#include"linkedArray.H"
#include"movableObject.H"
#include"intersection2d.H"

class PlayingField
 {friend class Options;

  public:
    typedef int Boolean;
    enum {off, on};

    PlayingField();
    ~PlayingField();
    int PlayTheGame(const int level, int argc, char** argv);
    PlayingField& AddShip();
    PlayingField& RemoveShip();
    void AlterExtraShipScore(const int newExtraShipScore);
    void AlterUSecondsPerFrame(const int newUSecondsPerFrame);

    GC gc;
    Pixmap pixmap;

    Boolean lastHitFromAlly;
    int lastHitScore,
        framesSinceLastBullet,
        framesSinceEnemy,
        level;

    LinkedArray<MovableObject*> nonPermeableList;
    LinkedArray<MovableObject*> selfPermeableList;
    LinkedArray<MovableObject*> permeableList;

    static int uSecondsPerFrame,
               initialShips,
               extraShipScore;

    static double maxLinearVelocity,
                  universalGravitationalConst;

    static Boolean enemiesExist;

    static const Box playArea;


  private:

    Boolean RunGame(Options& options);
    void DrawGame();
    void NewRocksAndEnemy();
    Vector2d CalcGravityAcceleration(const MovableObject* const, const MovableObject* const);
    void SetGravityAcceleration();
    timeval ResumePlay(Intersector&);
    void GenHelpScreen();

    GC backgroundGC;

    int fontHeight,
        framesThisLevel,
        nextShipScore;

    double speedAdjust;

    Atom WM_PROTOCOLS,
         WM_DELETE_WINDOW;

    Intersector intersector;

    Boolean leftRotPending,
            rightRotPending,
            firing;

 };

extern PlayingField playingField;

int PlayingField::uSecondsPerFrame=62500,
    PlayingField::initialShips=3,
    PlayingField::extraShipScore=10000;

double PlayingField::maxLinearVelocity=28,
       PlayingField::universalGravitationalConst=0;

PlayingField::Boolean PlayingField::enemiesExist=PlayingField::on;

const Box PlayingField::playArea(640,512,Vector2d(320+2*ROCK::scale,256+2*ROCK::scale));

inline PlayingField::PlayingField(): lastHitFromAlly(off),
                                     lastHitScore(0),
                                     fontHeight(stage.hiScoreInfo->ascent+stage.hiScoreInfo->descent+4),
                                     framesSinceLastBullet(0),
                                     framesThisLevel(0),
                                     nextShipScore(extraShipScore),
                                     framesSinceEnemy(0),
                                     speedAdjust(uSecondsPerFrame/125E3),
                                     level(0),
                                     WM_PROTOCOLS(XInternAtom(stage.display,"WM_PROTOCOLS",FALSE)),
                                     WM_DELETE_WINDOW(XInternAtom(stage.display,"WM_DELETE_WINDOW",FALSE)),
                                     nonPermeableList(28),
                                     selfPermeableList(128),
                                     permeableList(28),
                                     intersector(nonPermeableList,selfPermeableList,permeableList),
                                     leftRotPending(off),
                                     rightRotPending(off),
                                     firing(off)
 {int screen=DefaultScreen(stage.display),
      blackPixel=BlackPixel(stage.display,screen);
  pixmap=XCreatePixmap(stage.display,stage.window,
		                   playArea.Width()+4*ROCK::scale,playArea.Height()+4*ROCK::scale,
                       DefaultDepth(stage.display,screen));
  gc=XCreateGC(stage.display,pixmap,0,NULL);
  XSetGraphicsExposures(stage.display,gc,FALSE);
  XSetFunction(stage.display,gc,GXor);
  XSetFont(stage.display,gc,stage.hiScoreInfo->fid);
  XSetForeground(stage.display,gc,WhitePixel(stage.display,screen));
  XSetBackground(stage.display,gc,blackPixel);
  backgroundGC=XCreateGC(stage.display,pixmap,0,NULL);
  XSetGraphicsExposures(stage.display,backgroundGC,FALSE);
  XSetForeground(stage.display,backgroundGC,blackPixel);
  GenHelpScreen();
 }

inline PlayingField::~PlayingField()
 {
   XFreeGC(stage.display,backgroundGC);
   XFreeGC(stage.display,gc);
   XFreePixmap(stage.display,pixmap);
 }

inline PlayingField& PlayingField::AddShip()
 {if (!shipGroup.hyper.hyperspacing)
    intersector.AddNonPermeable(shipGroup.ship,0);
  return *this;
 }

inline PlayingField& PlayingField::RemoveShip()
 {leftRotPending=rightRotPending=firing=off;
  intersector.RemoveNonPermeable(shipGroup.ship);
  if (shipGroup.thrust->thrusting)
   {intersector.RemovePermeable(shipGroup.thrust);
    shipGroup.ship->ObjectLiner().Acceleration()=Vector2d();
    shipGroup.thrust->thrusting=Thrust::off;
   }
  return *this;
 }

inline void PlayingField::NewRocksAndEnemy()
 {++framesSinceLastBullet;
  if (framesThisLevel*speedAdjust<3600)
    ++framesThisLevel;
  ++framesSinceEnemy;
  if (selfPermeableList.GetNumItems())
   {int framesThisLevelDenominator=14400*(8-level+selfPermeableList.GetNumItems());
    if (enemiesExist&&enemyGroup.enemyInactive&&
	      gary_rand::rand_16()<(RAND_MAX_16*framesThisLevel
                              /(framesThisLevelDenominator<=0 ? 1 : framesThisLevelDenominator)
                              +framesSinceEnemy/1024+framesSinceLastBullet)*speedAdjust)
      enemyGroup.NewEnemy(level);
   }
  else
   {int nonRockItems=nonPermeableList.GetNumItems()+permeableList.GetNumItems();
    if (!shipGroup.ship->dead&&(nonRockItems==1||
                               shipGroup.thrust->thrusting&&nonRockItems==2)||
        !nonRockItems)
      {rockGroup.NewROCKs();
       level++;
       framesThisLevel=0;
      }
   }
 }

inline void PlayingField::DrawGame()
 {stage.DrawScore();
  if (score.CurrentScore()>=nextShipScore)
   {shipYard.AddShip();
    stage.DrawShipYard();
    nextShipScore+=extraShipScore;
   }
  stage.DrawPlayingField();
  XFillRectangle(stage.display,pixmap,backgroundGC,
                 playArea.NorthWestCorner().x,playArea.NorthWestCorner().y,
                 playArea.Width(),playArea.Height());
 }

inline Vector2d PlayingField::CalcGravityAcceleration(const MovableObject* const obj1,
                                                      const MovableObject* const obj2)
 {Vector2d dist=obj2->CurrentBox().Center()-obj1->CurrentBox().Center();
  double distMagSquared=dist.MagnitudeSquared(),
         distMag,
         radiusAverage=.5*(obj1->ObjectRotator().Radius()+obj2->ObjectRotator().Radius()),
         radiusAverageSquared=radiusAverage*radiusAverage,
         c=maxLinearVelocity+0.1,
         cSquared=c*c,
         relativisticMass=obj2->ObjectRotator().Area()*sqrt(cSquared/(cSquared-obj2->ObjectLiner().VelocityMagnitude()
                                                                              *obj2->ObjectLiner().VelocityMagnitude())),
         uSecondPerFrameRatio;
  return distMagSquared ? (distMag=sqrt(distMagSquared),
                           uSecondPerFrameRatio=uSecondsPerFrame/6.25E4, // Scale the acceleration to the currwnt frame rate of the game. 16 fps is baseline.
                           (dist/distMag)*universalGravitationalConst
                           *(distMag<radiusAverage ? relativisticMass*distMag
                                                     /(radiusAverageSquared*radiusAverage) // Overlapping object gravitational acceleration
                                                   : relativisticMass/distMagSquared) // Non-overlapping object gravitational accelaration
                           *uSecondPerFrameRatio*uSecondPerFrameRatio)
                        : Vector2d();
 }

inline void PlayingField::SetGravityAcceleration()
 {if (universalGravitationalConst)
   {nonPermeableList.SetCurrentAtHead();
    for (int i=0;i<nonPermeableList.GetNumItems();++i)
     {Vector2d gravityAcceleration;
      const int itemIndex=nonPermeableList.GetItemIndex();
      MovableObject* const item1Addr=nonPermeableList.GetData();
      nonPermeableList.SetCurrentAtHead();
      for (int j=0;j<nonPermeableList.GetNumItems();++j)
       {const MovableObject* const item2Addr=nonPermeableList.GetData();
        if (item1Addr!=item2Addr)
          gravityAcceleration+=CalcGravityAcceleration(item1Addr,item2Addr);
        nonPermeableList.Next();
       }
      selfPermeableList.SetCurrentAtHead();
      for (int j=0;j<selfPermeableList.GetNumItems();++j)
       {gravityAcceleration+=CalcGravityAcceleration(item1Addr,
                                                     selfPermeableList.GetData());
        selfPermeableList.Next();
       }
      if (item1Addr==shipGroup.ship&&shipGroup.thrust->thrusting)
       {shipGroup.ship->ObjectLiner().Acceleration()=shipGroup.ship->ObjectLiner().Acceleration()
                                                     +gravityAcceleration;
        shipGroup.thrust->ObjectLiner().Acceleration()=shipGroup.ship->ObjectLiner().Acceleration();
       }
      else
        item1Addr->ObjectLiner().Acceleration()=gravityAcceleration;
      nonPermeableList.SetCurrentAtItem(itemIndex).Next();
     }
    selfPermeableList.SetCurrentAtHead();
    for (int i=0;i<selfPermeableList.GetNumItems();++i)
     {Vector2d gravityAcceleration;
      const int itemIndex=selfPermeableList.GetItemIndex();
      MovableObject* const item1Addr=selfPermeableList.GetData();
      nonPermeableList.SetCurrentAtHead();
      for (int j=0;j<nonPermeableList.GetNumItems();++j)
       {gravityAcceleration+=CalcGravityAcceleration(item1Addr,
                                                     nonPermeableList.GetData());
        nonPermeableList.Next();
       }
      selfPermeableList.SetCurrentAtHead();
      for (int j=0;j<selfPermeableList.GetNumItems();++j)
       {const MovableObject* const item2Addr=selfPermeableList.GetData();
        if (item1Addr!=item2Addr)
          gravityAcceleration+=CalcGravityAcceleration(item1Addr,item2Addr);
        selfPermeableList.Next();
       }
      item1Addr->ObjectLiner().Acceleration()=gravityAcceleration;
      selfPermeableList.SetCurrentAtItem(itemIndex).Next();
     }
   }
 }

inline timeval PlayingField::ResumePlay(Intersector& intersector)
 {XRaiseWindow(stage.display,stage.window);
  timeval time;
  gettimeofday(&time,NULL);
  leftRotPending=rightRotPending=firing=off;
  shipGroup.ship->ObjectRotator().AngularVelocity()=0;
  if (shipGroup.thrust->thrusting)
   {intersector.RemovePermeable(shipGroup.thrust);
    shipGroup.ship->ObjectLiner().Acceleration()=Vector2d();
    shipGroup.thrust->thrusting=Thrust::off;
   }
  XSync(stage.display,False);
  return time;
 }

inline PlayingField::Boolean PlayingField::RunGame(Options& options)
 {XRaiseWindow(stage.display,stage.window);
  nonPermeableList.Reset();
  selfPermeableList.Reset();
  permeableList.Reset();
  score.Reset();
  framesSinceLastBullet=0;
  framesThisLevel=0;
  nextShipScore=extraShipScore;
  framesSinceEnemy=0;
  for (int i=0;i<initialShips;++i)
    shipYard.AddShip();
  XFillRectangle(stage.display,pixmap,backgroundGC,
                 playArea.NorthWestCorner().x,playArea.NorthWestCorner().y,
                 playArea.Width(),playArea.Height());
  NewRocksAndEnemy();
  DrawGame();
  while(shipYard.NumShips())
   {shipYard.RemoveShip();
    stage.DrawShipYard();
    shipGroup.NewShip();
    leftRotPending=rightRotPending=firing=off;
    while(nonPermeableList.GetNumItems()||permeableList.GetNumItems())
     {timeval startTime,
              endTime;
      gettimeofday(&startTime,NULL);
      NewRocksAndEnemy();
      if (ShipBulletGroup::autoFire&&firing)
        shipBulletGroup.fireThisFrame=ShipBulletGroup::on;
      XSync(stage.display,False);
      XEvent event;
      char keyText[2];
      while(XEventsQueued(stage.display,QueuedAfterReading))
       {XNextEvent(stage.display,&event);
        switch(event.type)
         {case MappingNotify:   XRefreshKeyboardMapping((XMappingEvent*)&event);
                                break;
	  case LeaveNotify:     if (stage.autoRepeatState==AutoRepeatModeOn)
	                          XAutoRepeatOn(stage.display);
                                for(;;)
	                         {XNextEvent(stage.display,&event);
                                  if (event.type==EnterNotify)
				   {XAutoRepeatOff(stage.display);
                                    startTime=ResumePlay(intersector);
                                    break;
				   }
                                  else
				    switch (event.type)
				     {case MappingNotify: XRefreshKeyboardMapping((XMappingEvent*)&event);
                                                          break;
                                      case Expose:
                                      case MapNotify:     stage.Refresh();
                                                          break;
                                     }
	                         }
                                break;
	  case Expose:
	  case ConfigureNotify: stage.Refresh();
                                break;
          case KeyPress:        if (XLookupString((XKeyEvent*)&event,keyText,2,NULL,NULL)==1)
                                  if (!shipGroup.hyper.hyperspacing)
                                    switch(keyText[0])
                                     {case 'e': if (shipGroup.ship->ObjectRotator().AngularVelocity())
                                                  leftRotPending=True;
                                                else
				                 {shipGroup.ship->ObjectRotator().AngularVelocity()=
                                                    -shipGroup.ship->angularVelocity;
                                                  if (shipGroup.thrust->thrusting)
                                                    shipGroup.thrust->ObjectRotator().AngularVelocity()=
                                                      -shipGroup.ship->angularVelocity;
				                 }
                                                break;
				      case 'r': if (shipGroup.ship->ObjectRotator().AngularVelocity())
                                                  rightRotPending=True;
                                                else
				                 {shipGroup.ship->ObjectRotator().AngularVelocity()=
                                                    shipGroup.ship->angularVelocity;
                                                  if (shipGroup.thrust->thrusting)
                                                    shipGroup.thrust->ObjectRotator().AngularVelocity()=
                                                      shipGroup.ship->angularVelocity;
				                 }
                                                break;
                                      case 'o': shipGroup.NewThrust();
                                                shipGroup.thrust->thrusting=Thrust::on;
                                                intersector.AddPermeable(shipGroup.thrust,0);
                                                break;
                                      case 'p': shipBulletGroup.fireThisFrame=ShipBulletGroup::on;
                                                firing=on;
                                                break;
                                      case ' ': RemoveShip();
                                                shipGroup.NewHyper();
                                                break;
	                              case 'q': return on;
                                                break;
                                      case 'n':
                                      case 'h': goto ResetGameUpdateScoreAndReturn;
                                     }
                                  else
                                    switch(keyText[0])
                                     {case 'q': return on;
                                                break;
                                      case 'n':
                                      case 'h': goto ResetGameUpdateScoreAndReturn;
				                             }
                                break;
          case KeyRelease:      if (!shipGroup.hyper.hyperspacing)
                                  if (XLookupString((XKeyEvent*)&event,keyText,2,NULL,NULL)==1)
                                    switch (keyText[0])
                                     {case 'e': if (shipGroup.ship->ObjectRotator().AngularVelocity()<0)
                                                  if (rightRotPending)
                                                   {shipGroup.ship->ObjectRotator().AngularVelocity()=
                                                      shipGroup.ship->angularVelocity;
                                                    if (shipGroup.thrust->thrusting)
                                                      shipGroup.thrust->ObjectRotator().AngularVelocity()=
                                                        shipGroup.ship->angularVelocity;
                                                   }
                                                  else
                                                   {shipGroup.ship->ObjectRotator().AngularVelocity()=0;
                                                    if (shipGroup.thrust->thrusting)
                                                      shipGroup.thrust->ObjectRotator().AngularVelocity()=0;
                                                   }
                                                leftRotPending=False;
                                                break;
                                      case 'r': if (shipGroup.ship->ObjectRotator().AngularVelocity()>0)
                                                  if (leftRotPending)
                                                   {shipGroup.ship->ObjectRotator().AngularVelocity()=
                                                      -shipGroup.ship->angularVelocity;
                                                    if (shipGroup.thrust->thrusting)
                                                      shipGroup.thrust->ObjectRotator().AngularVelocity()=
                                                        -shipGroup.ship->angularVelocity;
                                                   }
                                                  else
                                                   {shipGroup.ship->ObjectRotator().AngularVelocity()=0;
                                                    if (shipGroup.thrust->thrusting)
                                                      shipGroup.thrust->ObjectRotator().AngularVelocity()=0;
                                                   }
                                                rightRotPending=False;
                                                break;
                                      case 'o': intersector.RemovePermeable(shipGroup.thrust);
                                                shipGroup.ship->ObjectLiner().Acceleration()=Vector2d();
                                                shipGroup.thrust->thrusting=Thrust::off;
                                                break;
                                      case 'p': shipBulletGroup.fireThisFrame=ShipBulletGroup::off;
                                                firing=off;
                                                break;
                                     }
                                break;
          case ButtonPress:     if (((XButtonPressedEvent*)&event)->button==Button1)
                                 {Boolean pointerButtonReleased=off,
                                          pointerInWindow=on;
                                  if (button.PointerOnButton(*(XButtonEvent*)&event))
	                                  button.PressButton();
                                  for (;;)
                                   {XNextEvent(stage.display,&event);
                                    if (event.type==ButtonRelease)
                                     {if (((XButtonReleasedEvent*)&event)->button==Button1)
                                       {if (button.PointerOnButton(*(XButtonEvent*)&event))
                                         {options.RealizeWindow();
                                          button.ReleaseButton();
                                         }
                                        pointerButtonReleased=on;
                                        if (pointerInWindow)
                                          break;
                                       }
                                     }
                                    else
                                      if (event.type==EnterNotify)
                                       {pointerInWindow=on;
                                        XAutoRepeatOff(stage.display);
                                        if (pointerButtonReleased)
                                          break;
                                       }
                                      else
                                        switch (event.type)
                                         {case MappingNotify:   XRefreshKeyboardMapping((XMappingEvent*)&event);
                                                                break;
                                          case LeaveNotify:     if (stage.autoRepeatState==AutoRepeatModeOn)
                                                                  XAutoRepeatOn(stage.display);
                                                                pointerInWindow=off;
                                                                break;
                                          case Expose:
                                          case MapNotify:       stage.Refresh();
                                                                break;
                                          case MotionNotify:    if (button.PointerOnButton(*(XPointerMovedEvent*)&event))
                                                                  button.PressButton();
                                                                else
                                                                  button.ReleaseButton();
                                                                break;
                                         }
                                   }
                                  startTime=ResumePlay(intersector);
                                 }
                                break;
          case ClientMessage:   if (((XClientMessageEvent*)&event)->message_type==WM_PROTOCOLS&&
                                    ((XClientMessageEvent*)&event)->data.l[0]==WM_DELETE_WINDOW)
                                  return on;
                                break;
         }
       }
      SetGravityAcceleration();
      intersector.Intersect();
      DrawGame();
      gettimeofday(&endTime,NULL);
      unsigned int diffTime=endTime.tv_usec-startTime.tv_usec+(endTime.tv_sec-startTime.tv_sec)*1000000;
      if (diffTime<uSecondsPerFrame)
        usleep(uSecondsPerFrame-diffTime);
     }
   }
  ResetGameUpdateScoreAndReturn: shipYard.ClearYard();
  stage.DrawShipYard();
  shipBulletGroup.Reset();
  enemyGroup.Reset();
  enemyBulletGroup.Reset();
  score.UpdateTopTen();
  int xPos=playArea.NorthWestCorner().x+(playArea.Width()-stage.hiScoreInfo->max_bounds.width*22)/2
           -stage.hiScoreInfo->max_bounds.lbearing,
      yPosSave=playArea.NorthWestCorner().y+(playArea.Height()-15*fontHeight+4)/2+stage.hiScoreInfo->ascent,
      yPos=yPosSave;
  char str[23];
  ostrstream strout(str,sizeof(str)/sizeof(char));
  for(int i=0;i<score.NumScores();++i)
   {strout<<score.TopTenName(i)<<setw(12-strlen(score.TopTenName(i)))<<" "
          <<setw(10)<<score.TopTenScore(i);
    str[22]='\0';
    strout.seekp(0);
    XDrawString(stage.display,pixmap,gc,xPos,yPos,str,strlen(str));
    yPos+=fontHeight;
   }
  XDrawString(stage.display,pixmap,gc,xPos,yPos=yPosSave+12*fontHeight,
              "        S -- start",strlen("        S -- start"));
  XDrawString(stage.display,pixmap,gc,xPos,yPos+=fontHeight,
              "        Q -- quit",strlen("        Q -- quit"));
  XDrawString(stage.display,pixmap,gc,xPos,yPos+=fontHeight,
              "        H -- help",strlen("        H -- help"));
  stage.DrawPlayingField();
  return off;
  }

inline int PlayingField::PlayTheGame(const int l, int argc, char** argv)
 {XSizeHints* sizeHints=XAllocSizeHints();
  sizeHints->min_width=sizeHints->max_width=sizeHints->base_width=stage.windowWidth;
  sizeHints->min_height=sizeHints->max_height=sizeHints->base_height=stage.windowHeight;
  sizeHints->width_inc=sizeHints->height_inc=0;
  sizeHints->win_gravity=CenterGravity;
  sizeHints->flags=PMinSize|PMaxSize|PResizeInc|PBaseSize|PWinGravity;
  char gameName[10]="Asteroids",
     * gameNameAddr=gameName;
  XTextProperty textProperty;
  XStringListToTextProperty(&gameNameAddr,1,&textProperty);
  XWMHints* windowHints=XAllocWMHints();
  windowHints->icon_pixmap=stage.icon;
  windowHints->flags=IconPixmapHint;
  XClassHint* classHint=XAllocClassHint();
  XSetWMProperties(stage.display,stage.window,&textProperty,&textProperty,
                   argv,argc,sizeHints,windowHints,classHint);
  XFree((char*)classHint);
  XFree((char*)windowHints);
  XFree((char*)sizeHints);
  XSetWMProtocols(stage.display,stage.window,&WM_DELETE_WINDOW,1);
  XAutoRepeatOff(stage.display);
  XSelectInput(stage.display,stage.window,EnterWindowMask|LeaveWindowMask
                                          |StructureNotifyMask|ExposureMask
                                          |KeyPressMask|KeyReleaseMask
                                          |ButtonPressMask|ButtonReleaseMask
                                          |Button1MotionMask);
  Options options(argc,argv);
  XMapRaised(stage.display,stage.window);
  XEvent event;
  int localHighScore=0;
  Boolean pointerButtonReleased=on,
          buttonActivated=off;
  for(;;)
   {XNextEvent(stage.display,&event);
    switch(event.type)
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
      case KeyPress:        if (pointerButtonReleased)
                             {char keyText[2];
                              if (XLookupString((XKeyEvent*)&event,keyText,2,NULL,NULL)==1)
                                switch(keyText[0])
                                 {case 's': level=l;
                                            Boolean earlyExit;
                                            earlyExit=RunGame(options);
                                            if (localHighScore<score.CurrentScore())
                                              localHighScore=score.CurrentScore();
                                            if (earlyExit)
                                              return localHighScore;
                                            break;
                                  case 'q': return localHighScore;
                                            break;
                                  case 'h': GenHelpScreen();
                                            stage.DrawPlayingField();
                                            break;
                                 }
                             }
                            break;
      case ButtonPress:     if (((XButtonPressedEvent*)&event)->button==Button1)
                             {pointerButtonReleased=off;
                              if (button.PointerOnButton(*(XButtonEvent*)&event))
                               {button.PressButton();
                                buttonActivated=on;
                               }
                             }
                            break;
      case ButtonRelease:   if (((XButtonReleasedEvent*)&event)->button==Button1)
                             {if (buttonActivated &&
                                  button.PointerOnButton(*(XButtonEvent*)&event))
                               {options.RealizeWindow();
                                button.ReleaseButton();
                               }
                              buttonActivated=off;
                              pointerButtonReleased=on;
                             }
                            break;
      case MotionNotify:    if (buttonActivated &&
                                button.PointerOnButton(*(XPointerMovedEvent*)&event))
                              button.PressButton();
                            else
                              button.ReleaseButton();
                            break;
      case ClientMessage:   if (((XClientMessageEvent*)&event)->message_type==WM_PROTOCOLS&&
                                ((XClientMessageEvent*)&event)->data.l[0]==WM_DELETE_WINDOW)
                              return localHighScore;
                            break;
     }
   }
 }

void PlayingField::GenHelpScreen()
 {XFillRectangle(stage.display,pixmap,backgroundGC,
                 playArea.NorthWestCorner().x,playArea.NorthWestCorner().y,
                 playArea.Width(),playArea.Height());
  int xPos=playArea.NorthWestCorner().x+(playArea.Width()
                                         -XTextWidth(stage.hiScoreInfo,
                                                     "        H -- help (this screen)",
                                                     strlen("        H -- help (this screen)")))/2
           -stage.hiScoreInfo->max_bounds.lbearing,
      yPos=playArea.NorthWestCorner().y+(playArea.Height()-12*fontHeight+4)/2+stage.hiScoreInfo->ascent;
  XDrawString(stage.display,pixmap,gc,xPos,yPos,
              "        S -- start",strlen("        S -- start"));
  XDrawString(stage.display,pixmap,gc,xPos,yPos+=fontHeight,
              "        Q -- quit",strlen("        Q -- quit"));
  XDrawString(stage.display,pixmap,gc,xPos,yPos+=2*fontHeight,
              "        E -- rotate left",strlen("        E -- rotate left"));
  XDrawString(stage.display,pixmap,gc,xPos,yPos+=fontHeight,
              "        R -- rotate right",strlen("        R -- rotate right"));
  XDrawString(stage.display,pixmap,gc,xPos,yPos+=fontHeight,
              "        O -- thrust",strlen("        O -- thrust"));
  XDrawString(stage.display,pixmap,gc,xPos,yPos+=fontHeight,
              "        P -- fire",strlen("        P -- fire"));
  XDrawString(stage.display,pixmap,gc,xPos,yPos+=fontHeight,
              "space bar -- hyperspace",strlen("space bar -- hyperspace"));
  XDrawString(stage.display,pixmap,gc,xPos,yPos+=2*fontHeight,
              "        N -- new game",strlen("        N -- new game"));
  XDrawString(stage.display,pixmap,gc,xPos,yPos+=2*fontHeight,
              "        H -- help (this screen)",strlen("        H -- help (this screen)"));
 }

inline void PlayingField::AlterExtraShipScore(const int newExtraShipScore)
 {nextShipScore=(score.CurrentScore()/newExtraShipScore+1)*newExtraShipScore;
 }

inline void PlayingField::AlterUSecondsPerFrame(const int newUSecondsPerFrame)
 {uSecondsPerFrame=newUSecondsPerFrame;
  speedAdjust=uSecondsPerFrame/125E3;
 }

#endif
